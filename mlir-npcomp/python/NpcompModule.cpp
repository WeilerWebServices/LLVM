//===- native.cpp - MLIR Python bindings ----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include <cstddef>
#include <unordered_map>

#include "npcomp/Python/MlirInit.h"
#include "npcomp/Python/NpcompModule.h"
#include "npcomp/Python/PybindUtils.h"
#include "llvm/Support/CommandLine.h"

#ifdef NPCOMP_ENABLE_REFJIT
#include "npcomp/Backend/RefJIT/PythonModule.h"
#endif

#ifdef NPCOMP_ENABLE_IREE
#include "npcomp/Backend/IREE/PythonModule.h"
#endif

namespace mlir {
namespace npcomp {
namespace python {

void defineLLVMModule(pybind11::module m) {
  m.def("print_help_message", []() { llvm::cl::PrintHelpMessage(); });
  m.def("add_option",
        [](std::string name, llvm::Optional<std::string> value) {
          auto options_map = llvm::cl::getRegisteredOptions();
          auto found_it = options_map.find(name);
          if (found_it == options_map.end()) {
            std::string message = "Unknown LLVM option: ";
            message.append(name);
            throw py::raiseValueError(message.c_str());
          }

          std::string value_sr = value ? *value : "";
          found_it->getValue()->addOccurrence(1, name, value_sr);
        },
        py::arg("name"), py::arg("value") = llvm::Optional<std::string>());
  m.def("reset_option",
        [](std::string name) {
          auto options_map = llvm::cl::getRegisteredOptions();
          auto found_it = options_map.find(name);
          if (found_it == options_map.end()) {
            std::string message = "Unknown LLVM option: ";
            message.append(name);
            throw py::raiseValueError(message.c_str());
          }
          found_it->getValue()->setDefault();
        },
        py::arg("name"));
}

PYBIND11_MODULE(_npcomp, m) {
  // Guard the once init to happen once per process (vs module, which in
  // mondo builds can happen multiple times).
  static bool llvm_init_baton = ([]() { return npcompMlirInitialize(); })();
  (void)(llvm_init_baton);

  m.doc() = "Npcomp native python bindings";

  auto llvm_m = m.def_submodule("llvm", "LLVM interop");
  defineLLVMModule(llvm_m);

  // "mlir" module.
  auto mlir_m = m.def_submodule("mlir", "MLIR interop");
  auto mlir_ir_m = mlir_m.def_submodule("ir");
  defineMlirIrModule(mlir_ir_m);
  // Note: not "pass" because it is a reserved word
  auto mlir_pass_m = mlir_m.def_submodule("passes");
  defineMlirPassModule(mlir_pass_m);
  auto mlir_dialect_m = mlir_m.def_submodule("dialect");
  defineMlirCoreDialects(mlir_dialect_m);

  // Outer "_npcomp" module
  auto npcomp_dialect = m.def_submodule("dialect", "NPComp custom dialects");
  defineNpcompDialect(npcomp_dialect);

  // Optional backend modules.
  auto backend_m = m.def_submodule("backend", "Backend support");
  (void)backend_m;

#ifdef NPCOMP_ENABLE_REFJIT
  auto refjit_m =
      backend_m.def_submodule("refjit", "Reference CPU Jit Backend");
  ::npcomp::python::defineBackendRefJitModule(refjit_m);
#endif

#ifdef NPCOMP_ENABLE_IREE
  auto iree_m = backend_m.def_submodule("iree", "IREE backend support");
  defineBackendIREEModule(iree_m);
#endif
}

} // namespace python
} // namespace npcomp
} // namespace mlir
