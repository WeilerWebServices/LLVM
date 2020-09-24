// RUN: handshake-runner %s | FileCheck %s
// RUN: circt-opt -create-dataflow %s | handshake-runner | FileCheck %s
// CHECK: 10

module {
  func @main() -> i32 {
    %c0 = constant 0 : index
    %c1 = constant 1 : index
    %c3 = constant 3 : index
    %c4 = constant 4 : index
    %c5_i32 = constant 5 : i32
    %0 = alloc() : memref<64xi32>
    %1 = alloc() : memref<64xi32>
    br ^bb1(%c0 : index)
  ^bb1(%2: index):  // 2 preds: ^bb0, ^bb2
    %3 = cmpi "slt", %2, %c4 : index
    cond_br %3, ^bb2, ^bb3
  ^bb2: // pred: ^bb1
    store %c5_i32, %0[%2] : memref<64xi32>
    %4 = addi %2, %c1 : index
    br ^bb1(%4 : index)
  ^bb3: // pred: ^bb1
    br ^bb4(%c0 : index)
  ^bb4(%5: index):  // 2 preds: ^bb3, ^bb5
    %6 = cmpi "slt", %5, %c4 : index
    cond_br %6, ^bb5, ^bb6
  ^bb5: // pred: ^bb4
    %7 = load %0[%5] : memref<64xi32>
    %8 = addi %7, %7 : i32
    store %8, %1[%5] : memref<64xi32>
    %9 = addi %5, %c1 : index
    br ^bb4(%9 : index)
  ^bb6: // pred: ^bb4
    %10 = load %1[%c3] : memref<64xi32>
    return %10 : i32
  }
}
