//===- StaticLogic.h - StaticLogic Definitions ------------------*- C++ -*-===//
//
// Copyright 2020 The CIRCT Authors.
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//===----------------------------------------------------------------------===//

#ifndef CIRCT_STATICLOGIC_OPS_H_
#define CIRCT_STATICLOGIC_OPS_H_

#include "mlir/IR/Attributes.h"
#include "mlir/IR/Builders.h"
#include "mlir/IR/Dialect.h"
#include "mlir/IR/Function.h"
#include "mlir/IR/OpDefinition.h"
#include "mlir/IR/OpImplementation.h"
#include "mlir/IR/Operation.h"
#include "mlir/IR/RegionKindInterface.h"
#include "mlir/IR/StandardTypes.h"
#include "mlir/IR/TypeSupport.h"
#include "mlir/IR/Types.h"
#include "mlir/Interfaces/SideEffectInterfaces.h"
#include "mlir/Pass/Pass.h"

namespace circt {
namespace staticlogic {

using namespace mlir;

class StaticLogicDialect : public Dialect {
public:
  StaticLogicDialect(MLIRContext *context);
  static StringRef getDialectNamespace() { return "staticlogic"; }
};

#define GET_OP_CLASSES
#include "circt/Dialect/StaticLogic/StaticLogic.h.inc"

} // namespace staticlogic
} // namespace circt

#endif // CIRCT_STATICLOGIC_OPS_H_
