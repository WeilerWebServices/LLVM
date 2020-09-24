// RUN: handshake-runner %s | FileCheck %s
// RUN: circt-opt -create-dataflow %s | handshake-runner | FileCheck %s
// CHECK: 0

module {
  func @main() -> index {
    %c0 = constant 0 : index
    %c1 = constant 1 : index
    %c10 = constant 10 : index
    %0 = alloc() : memref<100xi32>
    %1 = alloc() : memref<100xi32>
    %2 = alloc() : memref<100xi32>
    br ^bb1(%c0 : index)
  ^bb1(%3: index):	// 2 preds: ^bb0, ^bb2
    %4 = cmpi "slt", %3, %c10 : index
    cond_br %4, ^bb2, ^bb3
  ^bb2:	// pred: ^bb1
    %5 = load %0[%3] : memref<100xi32>
    %6 = load %1[%3] : memref<100xi32>
    %7 = index_cast %5 : i32 to index
    %8 = load %2[%7] : memref<100xi32>
    %9 = addi %8, %6 : i32
    store %9, %2[%7] : memref<100xi32>
    %10 = addi %3, %c1 : index
    br ^bb1(%10 : index)
  ^bb3:	// pred: ^bb1
    return %c0 : index
  }
}
