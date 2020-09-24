//===------------------------------------------------------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef NPCOMP_CONVERSION_PASSES_H
#define NPCOMP_CONVERSION_PASSES_H

namespace mlir {
namespace NPCOMP {

/// Registers all NPCOMP conversion passes.
void registerConversionPasses();

} // namespace NPCOMP
} // namespace mlir

#endif // NPCOMP_CONVERSION_PASSES_H
