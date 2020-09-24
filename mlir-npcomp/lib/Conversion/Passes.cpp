//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#include "npcomp/Conversion/Passes.h"

#include "npcomp/Conversion/BasicpyToStd/Passes.h"
#include "npcomp/Conversion/NumpyToTCF/Passes.h"
#include "npcomp/Conversion/TCFToTCP/TCFToTCP.h"

//===----------------------------------------------------------------------===//
// Pass registration
//===----------------------------------------------------------------------===//

namespace {
#define GEN_PASS_REGISTRATION
#include "npcomp/Conversion/Passes.h.inc"
} // end namespace

void mlir::NPCOMP::registerConversionPasses() { ::registerPasses(); }
