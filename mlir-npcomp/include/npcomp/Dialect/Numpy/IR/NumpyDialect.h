//===- NumpyDialect.h - Core numpy dialect ----------------------*- C++ -*-===//
//
// This file is licensed under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef NPCOMP_DIALECT_NUMPY_IR_NUMPY_DIALECT_H
#define NPCOMP_DIALECT_NUMPY_IR_NUMPY_DIALECT_H

#include "mlir/IR/Dialect.h"
#include "mlir/IR/StandardTypes.h"
#include "npcomp/Typing/Analysis/CPA/Interfaces.h"

namespace mlir {
namespace NPCOMP {
namespace Numpy {

namespace detail {
struct NdArrayTypeStorage;
} // namespace detail

/// The singleton type representing an unknown dtype.
class AnyDtypeType : public Type::TypeBase<AnyDtypeType, Type, TypeStorage> {
public:
  using Base::Base;

  static AnyDtypeType get(MLIRContext *context) { return Base::get(context); }
};

class NdArrayType
    : public Type::TypeBase<NdArrayType, Type, detail::NdArrayTypeStorage,
                            NPCOMPTypingTypeMapInterface::Trait> {
public:
  using Base::Base;

  /// Constructs an NdArray with a dtype and no shape. Setting the dtype
  /// to !basicpy.UnknownType will print as ?.
  static NdArrayType get(Type dtype,
                         llvm::Optional<ArrayRef<int64_t>> shape = llvm::None);

  /// Returns whether the dtype is a concrete type (versus
  /// !basicpy.UnknownType).
  bool hasKnownDtype();
  Type getDtype();

  /// If the shape has been partially specified, this will have a value.
  /// unknown dimensions are -1.
  llvm::Optional<ArrayRef<int64_t>> getOptionalShape();

  /// Converts to an equivalent TensorType.
  TensorType toTensorType();

  // CPA::TypeMapInterface methods.
  Typing::CPA::TypeNode *mapToCPAType(Typing::CPA::Context &context);
};

} // namespace Numpy
} // namespace NPCOMP
} // namespace mlir

#include "npcomp/Dialect/Numpy/IR/NumpyOpsDialect.h.inc"

#endif // NPCOMP_DIALECT_NUMPY_IR_NUMPY_DIALECT_H
