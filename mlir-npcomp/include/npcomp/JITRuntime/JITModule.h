//===------------------------------------------------------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef NPCOMP_JITRUNTIME_JITMODULE_H
#define NPCOMP_JITRUNTIME_JITMODULE_H

#include "mlir/ExecutionEngine/ExecutionEngine.h"
#include "mlir/IR/Module.h"
#include "npcomp/runtime/UserAPI.h"
#include "llvm/ADT/ArrayRef.h"
#include "llvm/ADT/SmallVector.h"
#include "llvm/ADT/StringRef.h"
#include "llvm/Support/Error.h"

#include <memory>

namespace mlir {
class PassManager;
} // namespace mlir

namespace npcomp {
// Wrapper around npcomprt data structures and a JITted module, facilitating
// interaction.
class JITModule {
public:
  /// Populates a PassManager with a pipeline that performs backend compilation.
  /// The resulting module can be passed to fromCompiledModule().
  static void buildBackendCompilationPipeline(mlir::PassManager &pm,
                                              bool optimize = false);

  /// Constructs a JITModule from a compiled Module.
  /// The module should be the result of having run the backend compilation
  /// pipeline successfully.
  static llvm::Expected<std::unique_ptr<JITModule>>
  fromCompiledModule(mlir::ModuleOp module,
                     llvm::ArrayRef<llvm::StringRef> sharedLibs);

  llvm::Expected<llvm::SmallVector<npcomprt::Ref<npcomprt::Tensor>, 6>>
  invoke(llvm::StringRef functionName,
         llvm::ArrayRef<npcomprt::Ref<npcomprt::Tensor>> inputs);

private:
  JITModule();
  std::unique_ptr<mlir::ExecutionEngine> engine;
  npcomprt::ModuleDescriptor *descriptor;
};
} // namespace npcomp

#endif // NPCOMP_JITRUNTIME_JITMODULE_H
