// RUN: handshake-runner %s 2,3,4,5 | FileCheck %s
// BROKEN: circt-opt -create-dataflow %s | handshake-runner - 2,3,4,5 | FileCheck %s
// CHECK: 2 2,3,4,5 

module {
  func @main(%0 : memref<4xi32>) -> i32{
    %c0 = constant 0 : index
    %1 = load %0[%c0] : memref<4xi32>
    return %1 : i32
    }

}
