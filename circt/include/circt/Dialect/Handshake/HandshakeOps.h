//===- Ops.h - Handshake MLIR Operations -----------------------------*- C++
//-*-===//
//
// Copyright 2019 The CIRCT Authors.
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
// =============================================================================
//
// This file defines convenience types for working with handshake operations.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_HANDSHAKEOPS_OPS_H_
#define CIRCT_HANDSHAKEOPS_OPS_H_

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
namespace handshake {

using namespace mlir;
class TerminatorOp;

class HandshakeOpsDialect : public Dialect {
public:
  HandshakeOpsDialect(MLIRContext *context);
  static StringRef getDialectNamespace() { return "handshake"; }
};

#include "circt/Dialect/Handshake/HandshakeInterfaces.h.inc"

#define GET_OP_CLASSES
#include "circt/Dialect/Handshake/HandshakeOps.h.inc"

// template <typename T> struct FunctionPass : public OperationPass<T, FuncOp> {
//   /// The polymorphic API that runs the pass over the currently held
//   function. virtual void runOnFunction() = 0;

//   /// The polymorphic API that runs the pass over the currently held
//   operation. void runOnOperation() final {
//     if (!getFunction().isExternal())
//       runOnFunction();
//   }

//   /// Return the current module being transformed.
//   FuncOp getFunction() { return this->getOperation(); }
// };

} // end namespace handshake
} // end namespace circt
#endif // MLIR_HANDSHAKEOPS_OPS_H_
