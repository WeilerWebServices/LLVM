//===- RewritePtr.cpp --------------------------------------------------- -===//
// 
//                          The SAFECode Compiler
//
// This file was developed by the LLVM research group and is distributed under
// the University of Illinois Open Source License. See LICENSE.TXT for details.
// 
//===----------------------------------------------------------------------===//
//
// This file implements functions to rewrite out of bounds pointers.
//
//===----------------------------------------------------------------------===//

#include "PoolAllocator.h"
#include "DebugReport.h"
#include "RewritePtr.h"

#include "safecode/Runtime/BBRuntime.h"
#include "llvm/ADT/DenseMap.h"

#include <cstdio>
#include <map>

extern FILE * ReportLog;
 

NAMESPACE_SC_BEGIN

DebugPoolTy OOBPool;

// Map between rewrite pointer and source file information
llvm::DenseMap<void *, const char*>  RewriteSourcefile;
llvm::DenseMap<void *, unsigned>     RewriteLineno;
std::map<const void *, const void *> RewrittenPointers;

// Record from which object an OOB pointer originates
llvm::DenseMap<void *, std::pair<void *, void * > > RewrittenObjs;

//
// Function: rewrite_ptr()
//
// Description:
//  Take the given pointer and rewrite it to an Out Of Bounds (OOB) pointer.
//
// Inputs:
//  Pool       - The pool in which the pointer should be located (but isn't).
//               This value can be NULL if the caller doesn't know the pool.
//  p          - The pointer that needs to be rewritten.
//  ObjStart   - The address of the first valid byte of the object.
//  ObjEnd     - The address of the last valid byte of the object.
//  SourceFile - The name of the source file in which the check requesting the
//               rewrite is located.
//  lineno     - The line number within the source file in which the check
//               requesting the rewrite is located.
//
void *
rewrite_ptr (DebugPoolTy * Pool,
             const void * p,
             void * ObjStart,
             void * ObjEnd,
             const char * SourceFile,
             unsigned lineno) {

  static unsigned char * invalidptr = 0;

  //
  // If this pointer has already been rewritten, do not rewrite it again.
  //
  if (RewrittenPointers.find (p) != RewrittenPointers.end()) {
    return const_cast<void*>(RewrittenPointers[p]);
  }

  //
  // Calculate a new rewrite pointer.
  //
  if (invalidptr == 0) invalidptr = (unsigned char*)InvalidLower;
  ++invalidptr;

  //
  // Ensure that we haven't run out of rewrite pointers.
  //
  void* P = invalidptr;
  if ((uintptr_t) P == InvalidUpper) {
    fprintf (stderr, "rewrite: out of rewrite ptrs: %p %p, pc=%p\n",
             (void *) InvalidLower, (void *) InvalidUpper, invalidptr);
    fflush (stderr);
    return const_cast<void*>(p);
  }

  //
  // If no pool was specified (as is the case for an ExactCheck), use a
  // special Out of Bounds Pointer pool.
  //
  if (!Pool) Pool = &OOBPool;

  //
  // Determine if this pointer value has already been rewritten.  If so, just
  // return the previously rewritten value.  Otherwise, insert a mapping from
  // rewrite pointer to original pointer into the pool.
  //
  Pool->OOB.insert (invalidptr, ((unsigned char *)(invalidptr)), const_cast<void*>(p));

  //
  // If debugging tool support is enabled, then insert it into the global
  // OOB pool as well; this will ensure that we can find the pointer on a
  // memory protection violation (on faults, we don't have Pool handle
  // information).
  //
  if (logregs) {
    fprintf (ReportLog, "rewrite: %p: %p -> %p\n", (void*) Pool, p, invalidptr);
    fflush (ReportLog);
  }

  OOBPool.OOB.insert (invalidptr, ((unsigned char *)(invalidptr)), const_cast<void*>(p));
  RewriteSourcefile[invalidptr] = SourceFile;
  RewriteLineno[invalidptr] = lineno;
  RewrittenPointers[p] = invalidptr;
  RewrittenObjs[invalidptr] = std::make_pair(ObjStart, ObjEnd);
  return invalidptr;
}

NAMESPACE_SC_END
using namespace safecode;
//
// Function: getActualValue()
//
// Description:
//  If src is an out of object pointer, get the original value.
//
void *
pchk_getActualValue (DebugPoolTy * Pool, void * p) {
  //
  // If the pointer is not within the rewrite pointer range, then it is not a
  // rewritten pointer.  Simply return its current value.
  //
  if (((uintptr_t)p <= InvalidLower) || ((uintptr_t)p >= InvalidUpper)) {
    return p;
  }

  void * src = 0;
  void* tag = 0;
  void * end = 0;

  //
  // Look for the pointer in the pool's OOB pointer list.  If we find it,
  // return its actual value.
  //
  if (Pool && (Pool->OOB.find(p, src, end, tag))) {
    if (logregs) {
      fprintf (ReportLog, "getActualValue(1): %p: %p -> %p\n", (void*)Pool, p, tag);
      fflush (ReportLog);
    }
    return tag;
  }

  //
  // If we can't find the pointer in the pool's OOB list, perhaps it's in the
  // global OOB Pool (this can happen when it's rewritten by an exact check).
  //
  if (OOBPool.OOB.find (p, src, end, tag)) {
    if (logregs) {
      fprintf (ReportLog, "getActualValue(2): %p: %p -> %p\n", (void*)&OOBPool, p, tag);
      fflush (ReportLog);
    }
    return tag;
  }

  //
  // If we can't find the pointer, no worries.  If the program tries to use the
  // pointer, another SAFECode checks should flag a failure.  In this case,
  // just return the pointer.
  //
  if (logregs) {
    fprintf (ReportLog, "getActualValue(3): %p: %p -> %p\n", (void*)Pool, p, p);
    fflush (ReportLog);
  }
  return p;
}

