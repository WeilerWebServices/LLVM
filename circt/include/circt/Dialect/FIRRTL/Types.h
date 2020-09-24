//===- FIRRTL/IR/Ops.h - FIRRTL dialect -------------------------*- C++ -*-===//
//
// This file defines an MLIR dialect for the FIRRTL IR.
//
//===----------------------------------------------------------------------===//

#ifndef CIRCT_DIALECT_FIRRTL_TYPES_H
#define CIRCT_DIALECT_FIRRTL_TYPES_H

#include "mlir/IR/Types.h"

namespace circt {
namespace firrtl {
namespace detail {
struct WidthTypeStorage;
struct FlipTypeStorage;
struct BundleTypeStorage;
struct VectorTypeStorage;
} // namespace detail.

using namespace mlir;

class ClockType;
class ResetType;
class AsyncResetType;
class SIntType;
class UIntType;
class AnalogType;
class FlipType;
class BundleType;
class FVectorType;

// This is a common base class for all FIRRTL types.
class FIRRTLType : public Type {
public:
  void print(raw_ostream &os) const;

  /// Return true if this is a "passive" type - one that contains no "flip"
  /// types recursively within itself.
  bool isPassiveType();

  /// Return this type with any flip types recursively removed from itself.
  FIRRTLType getPassiveType();

  /// Return this type with all ground types replaced with UInt<1>.  This is
  /// used for `mem` operations.
  FIRRTLType getMaskType();

  /// If this is an IntType, AnalogType, or sugar type for a single bit (Clock,
  /// Reset, etc) then return the bitwidth.  Return -1 if the is one of these
  /// types but without a specified bitwidth.  Return -2 if this isn't a simple
  /// type.
  int32_t getBitWidthOrSentinel();

  /// Support method to enable LLVM-style type casting.
  static bool classof(Type type) {
    return type.isa<ClockType, ResetType, AsyncResetType, SIntType, UIntType,
                    AnalogType, FlipType, BundleType, FVectorType>();
  }

  /// Return true if this is a valid "reset" type.
  bool isResetType();

protected:
  using Type::Type;
};

//===----------------------------------------------------------------------===//
// Ground Types Without Parameters
//===----------------------------------------------------------------------===//

/// `firrtl.Clock` describe wires and ports meant for carrying clock signals.
class ClockType
    : public FIRRTLType::TypeBase<ClockType, FIRRTLType, DefaultTypeStorage> {
public:
  using Base::Base;
  static ClockType get(MLIRContext *context) { return Base::get(context); }
};

/// `firrtl.Reset`.
/// TODO(firrtl spec): This is not described in the FIRRTL spec.
class ResetType
    : public FIRRTLType::TypeBase<ResetType, FIRRTLType, DefaultTypeStorage> {
public:
  using Base::Base;
  static ResetType get(MLIRContext *context) { return Base::get(context); }
};
/// `firrtl.AsyncReset`.
/// TODO(firrtl spec): This is not described in the FIRRTL spec.
class AsyncResetType : public FIRRTLType::TypeBase<AsyncResetType, FIRRTLType,
                                                   DefaultTypeStorage> {
public:
  using Base::Base;
  static AsyncResetType get(MLIRContext *context) { return Base::get(context); }
};

//===----------------------------------------------------------------------===//
// Width Qualified Ground Types
//===----------------------------------------------------------------------===//

template <typename ConcreteType, typename ParentType>
class WidthQualifiedType
    : public FIRRTLType::TypeBase<ConcreteType, ParentType,
                                  detail::WidthTypeStorage> {
public:
  using FIRRTLType::TypeBase<ConcreteType, ParentType,
                             detail::WidthTypeStorage>::Base::Base;

  /// Return the width of this type, or -1 if it has none specified.
  int32_t getWidthOrSentinel() {
    auto width = static_cast<ConcreteType *>(this)->getWidth();
    return width.hasValue() ? width.getValue() : -1;
  }
};

class SIntType;
class UIntType;

/// This is the common base class between SIntType and UIntType.
class IntType : public FIRRTLType {
public:
  using FIRRTLType::FIRRTLType;

  /// Return a SIntType or UInt type with the specified signedness and width.
  static IntType get(MLIRContext *context, bool isSigned, int32_t width = -1);

  bool isSigned() { return isa<SIntType>(); }
  bool isUnsigned() { return isa<UIntType>(); }

  /// Return true if this integer type has a known width.
  bool hasWidth() { return getWidth().hasValue(); }

  /// Return the bitwidth of this type or None if unknown.
  Optional<int32_t> getWidth();

  /// Return the width of this type, or -1 if it has none specified.
  int32_t getWidthOrSentinel() {
    auto width = getWidth();
    return width.hasValue() ? width.getValue() : -1;
  }

  static bool classof(Type type) {
    return type.isa<SIntType>() || type.isa<UIntType>();
  }
};

/// A signed integer type, whose width may not be known.
class SIntType : public WidthQualifiedType<SIntType, IntType> {
public:
  using WidthQualifiedType::WidthQualifiedType;

  /// Get an with a known width, or -1 for unknown.
  static SIntType get(MLIRContext *context, int32_t width = -1);

  /// Return the bitwidth of this type or None if unknown.
  Optional<int32_t> getWidth();
};

/// An unsigned integer type, whose width may not be known.
class UIntType : public WidthQualifiedType<UIntType, IntType> {
public:
  using WidthQualifiedType::WidthQualifiedType;

  /// Get an with a known width, or -1 for unknown.
  static UIntType get(MLIRContext *context, int32_t width = -1);

  /// Return the bitwidth of this type or None if unknown.
  Optional<int32_t> getWidth();
};

// `firrtl.Analog` can be attached to multiple drivers.
class AnalogType : public WidthQualifiedType<AnalogType, FIRRTLType> {
public:
  using WidthQualifiedType::WidthQualifiedType;

  /// Get an with a known width, or -1 for unknown.
  static AnalogType get(MLIRContext *context, int32_t width = -1);

  /// Return the bitwidth of this type or None if unknown.
  Optional<int32_t> getWidth();
};

//===----------------------------------------------------------------------===//
// Flip Type
//===----------------------------------------------------------------------===//

class FlipType : public FIRRTLType::TypeBase<FlipType, FIRRTLType,
                                             detail::FlipTypeStorage> {
public:
  using Base::Base;

  FIRRTLType getElementType();

  static FIRRTLType get(FIRRTLType element);
};

//===----------------------------------------------------------------------===//
// Bundle Type
//===----------------------------------------------------------------------===//

/// BundleType is an aggregate of named elements.  This is effectively a struct
/// for FIRRTL.
class BundleType : public FIRRTLType::TypeBase<BundleType, FIRRTLType,
                                               detail::BundleTypeStorage> {
public:
  using Base::Base;

  // Each element of a bundle, which is a name and type.
  using BundleElement = std::pair<Identifier, FIRRTLType>;

  static FIRRTLType get(ArrayRef<BundleElement> elements, MLIRContext *context);

  ArrayRef<BundleElement> getElements();

  size_t getNumElements() { return getElements().size(); }

  /// Look up an element by name.  This returns None on failure.
  llvm::Optional<BundleElement> getElement(StringRef name);
  FIRRTLType getElementType(StringRef name);

  /// Return true if this is a "passive" type - one that contains no "flip"
  /// types recursively within itself.
  bool isPassiveType();

  /// Return this type with any flip types recursively removed from itself.
  FIRRTLType getPassiveType();
};

//===----------------------------------------------------------------------===//
// FVector Type
//===----------------------------------------------------------------------===//

/// VectorType is a fixed size collection of elements, like an array.
class FVectorType : public FIRRTLType::TypeBase<FVectorType, FIRRTLType,
                                                detail::VectorTypeStorage> {
public:
  using Base::Base;

  static FIRRTLType get(FIRRTLType elementType, unsigned numElements);

  FIRRTLType getElementType();
  unsigned getNumElements();

  /// Return true if this is a "passive" type - one that contains no "flip"
  /// types recursively within itself.
  bool isPassiveType();

  /// Return this type with any flip types recursively removed from itself.
  FIRRTLType getPassiveType();
};

} // namespace firrtl
} // namespace circt

namespace llvm {

// Type hash just like pointers.
template <>
struct DenseMapInfo<circt::firrtl::FIRRTLType> {
  using FIRRTLType = circt::firrtl::FIRRTLType;
  static FIRRTLType getEmptyKey() {
    auto pointer = llvm::DenseMapInfo<void *>::getEmptyKey();
    return FIRRTLType(static_cast<mlir::Type::ImplType *>(pointer));
  }
  static FIRRTLType getTombstoneKey() {
    auto pointer = llvm::DenseMapInfo<void *>::getTombstoneKey();
    return FIRRTLType(static_cast<mlir::Type::ImplType *>(pointer));
  }
  static unsigned getHashValue(FIRRTLType val) { return mlir::hash_value(val); }
  static bool isEqual(FIRRTLType LHS, FIRRTLType RHS) { return LHS == RHS; }
};

} // namespace llvm

#endif // CIRCT_DIALECT_FIRRTL_TYPES_H
