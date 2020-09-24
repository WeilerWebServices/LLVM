//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This is the public-facing interface for interacting with the npcomp
// runtime.
//
// This functionality is totally firewalled from the compiler codebase, so
// even if things superficially look similar, remember that there are no
// LLVM utilities here, memory allocation should be kept to a minimum, etc.
//
// npcomp/runtime/Support.h provides some minimal LLVM-like support code to keep
// the API familiar.
//
//===----------------------------------------------------------------------===//

#ifndef NPCOMP_RUNTIME_USERAPI_H
#define NPCOMP_RUNTIME_USERAPI_H

#include "npcomp/runtime/Support.h"
#include <atomic>
#include <cstdlib>

namespace npcomprt {

// Reference-counted handle to a type with a `refCount` member.
template <typename T> class Ref {
public:
  Ref() { ptr = nullptr; }
  // Creates a Ref and increments the refcount by 1.
  // rawPtr must be allocated with std::malloc.
  Ref(T *rawPtr) {
    ptr = rawPtr;
    ptr->refCount += 1;
  }
  Ref(const Ref &other) {
    ptr = other.ptr;
    incref(ptr);
  }
  Ref(Ref &&other) { ptr = other.takePtr(); }
  Ref &operator=(const Ref &other) {
    if (&other == this)
      return *this;
    decref(ptr);
    ptr = other.ptr;
    incref(ptr);
    return *this;
  }
  Ref &operator=(Ref &&other) {
    if (&other == this)
      return *this;
    decref(ptr);
    ptr = other.takePtr();
    return *this;
  }
  ~Ref() { decref(ptr); }

  T &operator*() const { return *ptr; }
  T *operator->() const { return ptr; }
  T *get() const { return ptr; }

  T *takePtr() {
    auto *ret = ptr;
    ptr = nullptr;
    return ret;
  }

private:
  static void incref(T *ptr) {
    if (!ptr)
      return;
    ptr->refCount += 1;
  }
  static void decref(T *ptr) {
    if (!ptr)
      return;
    if (ptr->refCount.fetch_sub(1) == 1) {
      ptr->~T();
      std::free(static_cast<void *>(ptr));
    }
  }
  T *ptr;
};

// The available data types.
enum class ElementType : std::int32_t {
  F32,
};
std::int32_t getElementTypeByteSize(ElementType type);

// Representation of a tensor.
class Tensor {
public:
  // Due to tail-allocated objects, this struct should never be directly
  // constructed.
  Tensor() = delete;

  // Create a Tensor with the given extents and element type, with a buffer
  // holding a copy of `data`.
  static Ref<Tensor> create(ArrayRef<std::int32_t> extents,
                            ElementType elementType, void *data);
  // Same as `create`, but returns a raw pointer.
  static Tensor *createRaw(ArrayRef<std::int32_t> extents,
                           ElementType elementType, void *data);

  ElementType getElementType() const { return elementType; }
  std::int32_t getRank() const { return rank; }
  void *getData() const { return data; }
  template <typename T> T *getData() const { return static_cast<T *>(data); }
  std::int32_t getExtent(int dimension) const {
    return getExtents()[dimension];
  }
  ArrayRef<std::int32_t> getExtents() const {
    auto extents = const_cast<Tensor *>(this)->getMutableExtents();
    return ArrayRef<std::int32_t>(extents.data(), extents.size());
  }
  // Returns the number of bytes occupied by the data representing this tensor.
  // The total allocated amount might be higher to allow e.g. for alignment
  // nudging.
  std::int32_t getDataByteSize() const;
  ~Tensor() { std::free(allocatedPtr); }

private:
  MutableArrayRef<std::int32_t> getMutableExtents() {
    auto *tail = reinterpret_cast<std::int32_t *>(this + 1);
    return MutableArrayRef<std::int32_t>(tail, rank);
  }
  // Reference count management.
  template <typename T> friend class Ref;
  std::atomic<int> refCount{0};

  ElementType elementType;
  // The number of dimensions of this Tensor.
  // There are `rank` tail-allocated std::int32_t values representing the
  // tensor extents.
  std::int32_t rank;
  // The buffer base.
  void *data;
  // The raw pointer returned by the allocator (currently assumed to be
  // malloc), suitable for freeing the buffer.
  void *allocatedPtr;

  // Sizes are tail-allocated.
};

//===----------------------------------------------------------------------===//
// Module loading.
// This is the main entry point that users interact with.
//===----------------------------------------------------------------------===//

// Metadata for a particular function.
// TODO: Add arg types.
struct FunctionMetadata {
  std::int32_t numInputs;
  std::int32_t numOutputs;
};

// Opaque forward declaration of module descriptor type. This is the type
// created by the compiler in the module binary.
struct ModuleDescriptor;

// Maximum input or output arity.
constexpr static int kMaxArity = 20;

// Low-level invocation API. The number of inputs and outputs should be correct
// and match the results of getMetadata.
void invoke(ModuleDescriptor *moduleDescriptor, StringRef functionName,
            ArrayRef<Ref<Tensor>> inputs, MutableArrayRef<Ref<Tensor>> outputs);

// Metadata for function `functionName`.
//
// Returns failure if functionName wasn't found.
LogicalResult getMetadata(ModuleDescriptor *moduleDescriptor,
                          StringRef functionName,
                          FunctionMetadata &outMetadata);

} // namespace npcomprt

#endif // NPCOMP_RUNTIME_USERAPI_H
