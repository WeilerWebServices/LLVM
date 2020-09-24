//RUN: circt-opt %s --convert-llhd-to-llvm --split-input-file | FileCheck %s

// CHECK-LABEL: @dummy_i1
func @dummy_i1 (%0 : i1) {
  return
}

// CHECK-LABEL: @dummy_i32
func @dummy_i32 (%0 : i32)  {
  return
}

// CHECK-LABEL: @dummy_time
func @dummy_time (%0 : !llhd.time) {
  return
}

// CHECK-LABEL:   llvm.func @convert_persistent_value(
// CHECK-SAME:                                        %[[VAL_0:.*]]: !llvm.ptr<i8>,
// CHECK-SAME:                                        %[[VAL_1:.*]]: !llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>,
// CHECK-SAME:                                        %[[VAL_2:.*]]: !llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>) {
// CHECK:           %[[VAL_3:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_4:.*]] = llvm.getelementptr %[[VAL_2]]{{\[}}%[[VAL_3]]] : (!llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>, !llvm.i32) -> !llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>
// CHECK:           %[[VAL_5:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_6:.*]] = llvm.getelementptr %[[VAL_2]]{{\[}}%[[VAL_5]]] : (!llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>, !llvm.i32) -> !llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>
// CHECK:           %[[VAL_7:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_8:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_9:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_7]], %[[VAL_8]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<i32>
// CHECK:           %[[VAL_10:.*]] = llvm.load %[[VAL_9]] : !llvm.ptr<i32>
// CHECK:           llvm.br ^bb1
// CHECK:         ^bb1:
// CHECK:           %[[VAL_11:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_12:.*]] = llvm.icmp "eq" %[[VAL_10]], %[[VAL_11]] : !llvm.i32
// CHECK:           llvm.cond_br %[[VAL_12]], ^bb2, ^bb4
// CHECK:         ^bb2:
// CHECK:           %[[VAL_13:.*]] = llvm.mlir.constant(false) : !llvm.i1
// CHECK:           %[[VAL_14:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_15:.*]] = llvm.mlir.constant(3 : i32) : !llvm.i32
// CHECK:           %[[VAL_16:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_17:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_14]], %[[VAL_15]], %[[VAL_16]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.ptr<i1>
// CHECK:           llvm.store %[[VAL_13]], %[[VAL_17]] : !llvm.ptr<i1>
// CHECK:           %[[VAL_18:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_19:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_20:.*]] = llvm.mlir.constant(3 : i32) : !llvm.i32
// CHECK:           %[[VAL_21:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_22:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_19]], %[[VAL_20]], %[[VAL_21]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.ptr<i32>
// CHECK:           llvm.store %[[VAL_18]], %[[VAL_22]] : !llvm.ptr<i32>
// CHECK:           %[[VAL_23:.*]] = llvm.mlir.constant(dense<[0, 0, 1]> : vector<3xi32>) : !llvm.array<3 x i32>
// CHECK:           %[[VAL_24:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_25:.*]] = llvm.mlir.constant(3 : i32) : !llvm.i32
// CHECK:           %[[VAL_26:.*]] = llvm.mlir.constant(2 : i32) : !llvm.i32
// CHECK:           %[[VAL_27:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_24]], %[[VAL_25]], %[[VAL_26]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.ptr<array<3 x i32>>
// CHECK:           llvm.store %[[VAL_23]], %[[VAL_27]] : !llvm.ptr<array<3 x i32>>
// CHECK:           llvm.br ^bb3
// CHECK:         ^bb3:
// CHECK:           %[[VAL_28:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_29:.*]] = llvm.mlir.constant(3 : i32) : !llvm.i32
// CHECK:           %[[VAL_30:.*]] = llvm.mlir.constant(2 : i32) : !llvm.i32
// CHECK:           %[[VAL_31:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_28]], %[[VAL_29]], %[[VAL_30]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.ptr<array<3 x i32>>
// CHECK:           %[[VAL_32:.*]] = llvm.load %[[VAL_31]] : !llvm.ptr<array<3 x i32>>
// CHECK:           %[[VAL_33:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_34:.*]] = llvm.mlir.constant(3 : i32) : !llvm.i32
// CHECK:           %[[VAL_35:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_36:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_33]], %[[VAL_34]], %[[VAL_35]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.ptr<i32>
// CHECK:           %[[VAL_37:.*]] = llvm.load %[[VAL_36]] : !llvm.ptr<i32>
// CHECK:           %[[VAL_38:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_39:.*]] = llvm.mlir.constant(3 : i32) : !llvm.i32
// CHECK:           %[[VAL_40:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_41:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_38]], %[[VAL_39]], %[[VAL_40]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<2 x i1>>, struct<(i1, i32, array<3 x i32>)>)>>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.ptr<i1>
// CHECK:           %[[VAL_42:.*]] = llvm.load %[[VAL_41]] : !llvm.ptr<i1>
// CHECK:           llvm.call @dummy_i1(%[[VAL_42]]) : (!llvm.i1) -> ()
// CHECK:           llvm.call @dummy_i32(%[[VAL_37]]) : (!llvm.i32) -> ()
// CHECK:           llvm.call @dummy_time(%[[VAL_32]]) : (!llvm.array<3 x i32>) -> ()
// CHECK:           llvm.br ^bb3
// CHECK:         ^bb4:
// CHECK:           llvm.return
// CHECK:         }
llhd.proc @convert_persistent_value () -> (%out0 : !llhd.sig<i1>, %out1 : !llhd.sig<i32>) {
  br ^entry
^entry:
  %0 = llhd.const 0 : i1
  %1 = llhd.const 0 : i32
  %2 = llhd.const #llhd.time<0ns, 0d, 1e> : !llhd.time
  br ^resume
^resume:
  call @dummy_i1(%0) : (i1) -> ()
  call @dummy_i32(%1) : (i32) -> ()
  call @dummy_time(%2) : (!llhd.time) -> ()
  br ^resume
}

// CHECK-LABEL:   llvm.func @convert_resume(
// CHECK-SAME:                              %[[VAL_0:.*]]: !llvm.ptr<i8>,
// CHECK-SAME:                              %[[VAL_1:.*]]: !llvm.ptr<struct<(ptr<i8>, i32, ptr<array<1 x i1>>, struct<()>)>>,
// CHECK-SAME:                              %[[VAL_2:.*]]: !llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>) {
// CHECK:           %[[VAL_3:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_4:.*]] = llvm.getelementptr %[[VAL_2]]{{\[}}%[[VAL_3]]] : (!llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>, !llvm.i32) -> !llvm.ptr<struct<(ptr<i8>, i64, i64, i64)>>
// CHECK:           %[[VAL_5:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_6:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_7:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_5]], %[[VAL_6]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<1 x i1>>, struct<()>)>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<i32>
// CHECK:           %[[VAL_8:.*]] = llvm.load %[[VAL_7]] : !llvm.ptr<i32>
// CHECK:           llvm.br ^bb1
// CHECK:         ^bb1:
// CHECK:           %[[VAL_9:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_10:.*]] = llvm.icmp "eq" %[[VAL_8]], %[[VAL_9]] : !llvm.i32
// CHECK:           llvm.cond_br %[[VAL_10]], ^bb4, ^bb2
// CHECK:         ^bb2:
// CHECK:           %[[VAL_11:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_12:.*]] = llvm.icmp "eq" %[[VAL_8]], %[[VAL_11]] : !llvm.i32
// CHECK:           llvm.cond_br %[[VAL_12]], ^bb3, ^bb5
// CHECK:         ^bb3:
// CHECK:           %[[VAL_13:.*]] = llvm.mlir.constant(dense<[0, 0, 1]> : vector<3xi32>) : !llvm.array<3 x i32>
// CHECK:           %[[VAL_14:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_15:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_16:.*]] = llvm.mlir.constant(2 : i32) : !llvm.i32
// CHECK:           %[[VAL_17:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_14]], %[[VAL_16]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<1 x i1>>, struct<()>)>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<ptr<array<1 x i1>>>
// CHECK:           %[[VAL_18:.*]] = llvm.load %[[VAL_17]] : !llvm.ptr<ptr<array<1 x i1>>>
// CHECK:           %[[VAL_19:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_20:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i1
// CHECK:           %[[VAL_21:.*]] = llvm.getelementptr %[[VAL_18]]{{\[}}%[[VAL_14]], %[[VAL_19]]] : (!llvm.ptr<array<1 x i1>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<i1>
// CHECK:           llvm.store %[[VAL_20]], %[[VAL_21]] : !llvm.ptr<i1>
// CHECK:           %[[VAL_22:.*]] = llvm.extractvalue %[[VAL_13]][0 : i32] : !llvm.array<3 x i32>
// CHECK:           %[[VAL_23:.*]] = llvm.extractvalue %[[VAL_13]][1 : i32] : !llvm.array<3 x i32>
// CHECK:           %[[VAL_24:.*]] = llvm.extractvalue %[[VAL_13]][2 : i32] : !llvm.array<3 x i32>
// CHECK:           %[[VAL_25:.*]] = llvm.bitcast %[[VAL_1]] : !llvm.ptr<struct<(ptr<i8>, i32, ptr<array<1 x i1>>, struct<()>)>> to !llvm.ptr<i8>
// CHECK:           %[[VAL_26:.*]] = llvm.mlir.constant(1 : i32) : !llvm.i32
// CHECK:           %[[VAL_27:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_14]], %[[VAL_15]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<1 x i1>>, struct<()>)>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<i32>
// CHECK:           llvm.store %[[VAL_26]], %[[VAL_27]] : !llvm.ptr<i32>
// CHECK:           %[[VAL_28:.*]] = llvm.call @llhd_suspend(%[[VAL_0]], %[[VAL_25]], %[[VAL_22]], %[[VAL_23]], %[[VAL_24]]) : (!llvm.ptr<i8>, !llvm.ptr<i8>, !llvm.i32, !llvm.i32, !llvm.i32) -> !llvm.void
// CHECK:           llvm.return
// CHECK:         ^bb4:
// CHECK:           %[[VAL_29:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_30:.*]] = llvm.mlir.constant(2 : i32) : !llvm.i32
// CHECK:           %[[VAL_31:.*]] = llvm.getelementptr %[[VAL_1]]{{\[}}%[[VAL_29]], %[[VAL_30]]] : (!llvm.ptr<struct<(ptr<i8>, i32, ptr<array<1 x i1>>, struct<()>)>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<ptr<array<1 x i1>>>
// CHECK:           %[[VAL_32:.*]] = llvm.load %[[VAL_31]] : !llvm.ptr<ptr<array<1 x i1>>>
// CHECK:           %[[VAL_33:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i32
// CHECK:           %[[VAL_34:.*]] = llvm.mlir.constant(0 : i32) : !llvm.i1
// CHECK:           %[[VAL_35:.*]] = llvm.getelementptr %[[VAL_32]]{{\[}}%[[VAL_29]], %[[VAL_33]]] : (!llvm.ptr<array<1 x i1>>, !llvm.i32, !llvm.i32) -> !llvm.ptr<i1>
// CHECK:           llvm.store %[[VAL_34]], %[[VAL_35]] : !llvm.ptr<i1>
// CHECK:           llvm.return
// CHECK:         ^bb5:
// CHECK:           llvm.return
// CHECK:         }
llhd.proc @convert_resume (%in0 : !llhd.sig<i1>) -> () {
  br ^entry
^entry:
  %t = llhd.const #llhd.time<0ns, 0d, 1e> : !llhd.time
  llhd.wait for %t, ^resume
^resume:
  llhd.halt
}
