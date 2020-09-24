//===----------------------------------------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//
//
// This file contains data structures (which we typically call "descriptors")
// that are emitted by the compiler and must be kept in sync with the compiler
// code that creates them in LowerToLLVM.cpp.
//
//===----------------------------------------------------------------------===//

#ifndef NPCOMP_LIB_RUNTIME_COMPILERDATASTRUCTURES_H
#define NPCOMP_LIB_RUNTIME_COMPILERDATASTRUCTURES_H

#include <cstdint>

namespace npcomprt {

// All arguments are packed into this type-erased form for being invoked. See
// LowerToLLVM.cpp for more details.
typedef void ABIFunc(void **, void **);

struct FuncDescriptor {
  // The length of the function name.
  std::int32_t nameLen;
  // The name of the function, to allow lookup.
  const char *name;
  // This is a raw function pointer to the function's entry point as
  // emitted by the compiler.
  ABIFunc *functionPtr;
  // The number of inputs to the function.
  std::int32_t numInputs;
  // The number of outputs of the function.
  std::int32_t numOutputs;
  // TODO: Add arg/result descriptors and other metadata.
  // With those descriptors we can do type and shape checking for each
  // argument.
};

// The top-level entry point of the module metadata emitted by the
// compiler. Unlike all the other descriptors here, external code does handle
// this type (albeit through an opaque pointer).
struct ModuleDescriptor {
  std::int32_t numFuncDescriptors;
  FuncDescriptor *functionDescriptors;
};

// Static data representing a global variable (together with its shape).
struct GlobalDescriptor {
  std::int32_t numExtents;
  std::int32_t *extents;
  void *data;
};

} // namespace npcomprt

#endif // NPCOMP_LIB_RUNTIME_COMPILERDATASTRUCTURES_H