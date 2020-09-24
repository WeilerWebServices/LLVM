//===- Engine.cpp - Simulator Engine class implementation -------*- C++ -*-===//
//
// This file implements the Engine class.
//
//===----------------------------------------------------------------------===//

#include "State.h"

#include "circt/Conversion/LLHDToLLVM/LLHDToLLVM.h"
#include "circt/Dialect/LLHD/Simulator/Engine.h"

#include "mlir/ExecutionEngine/ExecutionEngine.h"
#include "mlir/Pass/Pass.h"
#include "mlir/Pass/PassManager.h"
#include "mlir/Transforms/DialectConversion.h"

#include "llvm/Support/TargetSelect.h"

using namespace mlir;
using namespace llhd::sim;

Engine::Engine(llvm::raw_ostream &out, ModuleOp module, MLIRContext &context,
               std::string root)
    : out(out), root(root) {
  state = std::make_unique<State>();

  buildLayout(module);

  auto rootEntity = module.lookupSymbol<EntityOp>(root);

  // Insert explicit instantiation of the design root.
  OpBuilder insertInst =
      OpBuilder::atBlockTerminator(&rootEntity.getBody().getBlocks().front());
  insertInst.create<InstOp>(rootEntity.getBlocks().front().back().getLoc(),
                            llvm::None, root, root, ArrayRef<Value>(),
                            ArrayRef<Value>());

  // Add the 0-time event.
  state->queue.push(Slot(Time()));

  mlir::PassManager pm(&context);
  pm.addPass(llhd::createConvertLLHDToLLVMPass());
  if (failed(pm.run(module))) {
    llvm::errs() << "failed to convert module to LLVM";
    exit(EXIT_FAILURE);
  }

  this->module = module;

  llvm::InitializeNativeTarget();
  llvm::InitializeNativeTargetAsmPrinter();
  auto maybeEngine = mlir::ExecutionEngine::create(this->module);
  assert(maybeEngine && "failed to create JIT");
  engine = std::move(*maybeEngine);
}

Engine::~Engine() = default;

void Engine::dumpStateLayout() { state->dumpLayout(); }

void Engine::dumpStateSignalTriggers() { state->dumpSignalTriggers(); }

int Engine::simulate(int n) {
  assert(engine && "engine not found");
  assert(state && "state not found");

  SmallVector<void *, 1> arg({&state});
  // Initialize tbe simulation state.
  auto invocationResult = engine->invoke("llhd_init", arg);
  if (invocationResult) {
    llvm::errs() << "Failed invocation of llhd_init: " << invocationResult;
    return -1;
  }

  // Dump the signals' initial values.
  for (size_t i = 0, e = state->signals.size(); i < e; ++i) {
    state->dumpSignal(out, i);
  }

  int i = 0;

  // Keep track of the instances that need to wakeup.
  std::vector<std::string> wakeupQueue;
  // All instances are run in the first cycle.
  for (auto k : state->instances.keys())
    wakeupQueue.push_back(k.str());

  while (!state->queue.empty()) {
    if (n > 0 && i >= n) {
      break;
    }
    auto pop = state->popQueue();

    // Update the simulation time.
    assert(state->time < pop.time || pop.time.time == 0);
    state->time = pop.time;

    // Apply the signal changes and dump the signals that actually changed
    // value.
    for (auto change : pop.changes) {
      // Get a buffer to apply the changes on.
      Signal *curr = &(state->signals[change.first]);
      APInt buff(curr->size * 8,
                 ArrayRef<uint64_t>(reinterpret_cast<uint64_t *>(curr->value),
                                    curr->size));

      // Apply all the changes to the buffer, in order of execution.
      for (auto drive : change.second) {
        if (drive.second.getBitWidth() < buff.getBitWidth())
          buff.insertBits(drive.second, drive.first);
        else
          buff = drive.second;
      }

      // Skip if the updated signal value is equal to the initial value.
      if (std::memcmp(curr->value, buff.getRawData(), curr->size) == 0)
        continue;

      // Apply the signal update.
      std::memcpy(curr->value, buff.getRawData(),
                  state->signals[change.first].size);

      // Trigger all sensitive instances.
      // The owner is always triggered.
      wakeupQueue.push_back(state->signals[change.first].owner);
      // Add sensitive instances.
      for (auto inst : state->signals[change.first].triggers) {
        // Skip if the process is not currently sensible to the signal.
        if (!state->instances[inst].isEntity) {
          auto &sensList = state->instances[inst].sensitivityList;
          auto it = std::find_if(sensList.begin(), sensList.end(),
                                 [&change](SignalDetail &s) {
                                   return s.globalIndex == change.first;
                                 });
          if (sensList.end() != it &&
              state->instances[inst].procState->senses[it - sensList.begin()] ==
                  0)
            continue;
        }
        wakeupQueue.push_back(inst);
      }

      // Dump the updated signal.
      state->dumpSignal(out, change.first);
    }

    // TODO: don't wakeup a process instances if already woken up by an observed
    // signal.
    // Add scheduled process resumes to the wakeup queue.
    for (auto inst : pop.scheduled) {
      wakeupQueue.push_back(inst);
    }

    // Run the instances present in the wakeup queue.
    for (auto inst : wakeupQueue) {
      auto name = state->instances[inst].unit;
      auto signalTable = state->instances[inst].sensitivityList.data();

      // Gather the instance arguments for unit invocation.
      SmallVector<void *, 3> args;
      if (state->instances[inst].isEntity)
        args.assign({&state, &signalTable});
      else {
        args.assign({&state, &state->instances[inst].procState, &signalTable});
      }
      // Run the unit.
      auto invocationResult = engine->invoke(name, args);
      if (invocationResult) {
        llvm::errs() << "Failed invocation of " << root << ": "
                     << invocationResult;
        return -1;
      }
    }

    // Clear wakeup queue.
    wakeupQueue.clear();
    i++;
  }
  llvm::errs() << "Finished after " << i << " steps.\n";
  return 0;
}

void Engine::buildLayout(ModuleOp module) {
  // Start from the root entity.
  auto rootEntity = module.lookupSymbol<EntityOp>(root);
  assert(rootEntity && "root entity not found!");

  // Build root instance, the parent and instance names are the same for the
  // root.
  Instance rootInst(root, root);
  rootInst.unit = root;

  // Recursively walk the units starting at root.
  walkEntity(rootEntity, rootInst);

  // The root is always an instance.
  rootInst.isEntity = true;
  // Store the root instance.
  state->instances[rootInst.name] = rootInst;

  // Add triggers to signals.
  for (auto &inst : state->instances) {
    for (auto trigger : inst.getValue().sensitivityList) {
      state->signals[trigger.globalIndex].triggers.push_back(
          inst.getKey().str());
    }
  }
}

void Engine::walkEntity(EntityOp entity, Instance &child) {
  entity.walk([&](Operation *op) {
    assert(op);

    // Add a signal to the signal table.
    if (auto sig = dyn_cast<SigOp>(op)) {
      uint64_t index = state->addSignal(sig.name().str(), child.name);
      child.sensitivityList.push_back(
          SignalDetail({nullptr, 0, child.sensitivityList.size(), index}));
    }

    // Build (recursive) instance layout.
    if (auto inst = dyn_cast<InstOp>(op)) {
      // Skip self-recursion.
      if (inst.callee() == child.name)
        return;
      if (auto e =
              op->getParentOfType<ModuleOp>().lookupSymbol(inst.callee())) {
        Instance newChild(inst.name().str(), child.name);
        newChild.unit = inst.callee().str();
        newChild.nArgs = inst.getNumOperands();

        // Add instance arguments to sensitivity list. The first nArgs signals
        // in the sensitivity list represent the unit's arguments, while the
        // following ones represent the unit-defined signals.
        llvm::SmallVector<Value, 8> args;
        args.insert(args.end(), inst.inputs().begin(), inst.inputs().end());
        args.insert(args.end(), inst.outputs().begin(), inst.outputs().end());

        for (size_t i = 0, e = args.size(); i < e; ++i) {
          // The signal comes from an instance's argument.
          if (auto blockArg = args[i].dyn_cast<BlockArgument>()) {
            auto detail = child.sensitivityList[blockArg.getArgNumber()];
            detail.instIndex = i;
            newChild.sensitivityList.push_back(detail);
          } else if (auto sig = dyn_cast<SigOp>(args[i].getDefiningOp())) {
            // The signal comes from one of the instance's owned signals.
            auto it = std::find_if(
                child.sensitivityList.begin(), child.sensitivityList.end(),
                [&](SignalDetail &detail) {
                  return state->signals[detail.globalIndex].name ==
                             sig.name() &&
                         state->signals[detail.globalIndex].owner == child.name;
                });
            if (it != child.sensitivityList.end()) {
              auto detail = *it;
              detail.instIndex = i;
              newChild.sensitivityList.push_back(detail);
            }
          }
        }

        // Recursively walk a new entity, otherwise it is a process and cannot
        // define new signals or instances.
        if (auto ent = dyn_cast<EntityOp>(e)) {
          newChild.isEntity = true;
          walkEntity(ent, newChild);
        } else {
          newChild.isEntity = false;
        }

        // Store the created instance.
        state->instances[newChild.name] = newChild;
      }
    }
  });
}
