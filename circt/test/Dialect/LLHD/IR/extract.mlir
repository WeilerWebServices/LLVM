// RUN: circt-opt %s -mlir-print-op-generic -split-input-file -verify-diagnostics | circt-opt | circt-opt | FileCheck %s

// CHECK-LABEL: @extract_slice_integers
// CHECK-SAME: %[[CI1:.*]]: i1
// CHECK-SAME: %[[CI32:.*]]: i32
func @extract_slice_integers(%cI1 : i1, %cI32 : i32) {
  // CHECK-NEXT: %{{.*}} = llhd.extract_slice %[[CI1]], 0 : i1 -> i1
  %0 = llhd.extract_slice %cI1, 0 : i1 -> i1
  // CHECK-NEXT: %{{.*}} = llhd.extract_slice %[[CI32]], 0 : i32 -> i5
  %1 = llhd.extract_slice %cI32, 0 : i32 -> i5

  return
}

// CHECK-LABEL: @extract_slice_signals
// CHECK-SAME: %[[SI1:.*]]: !llhd.sig<i1>
// CHECK-SAME: %[[SI32:.*]]: !llhd.sig<i32>
func @extract_slice_signals (%sI1 : !llhd.sig<i1>, %sI32 : !llhd.sig<i32>) -> () {
  // CHECK-NEXT: %{{.*}} = llhd.extract_slice %[[SI1]], 0 : !llhd.sig<i1> -> !llhd.sig<i1>
  %0 = llhd.extract_slice %sI1, 0 : !llhd.sig<i1> -> !llhd.sig<i1>
  // CHECK-NEXT: %{{.*}} = llhd.extract_slice %[[SI32]], 0 : !llhd.sig<i32> -> !llhd.sig<i5>
  %1 = llhd.extract_slice %sI32, 0 : !llhd.sig<i32> -> !llhd.sig<i5>

  return
}

// CHECK-LABEL: @extract_slice_array_signals
// CHECK-SAME: %[[ARRAY5:.*]]: !llhd.sig<!llhd.array<5xi1>>
// CHECK-SAME: %[[ARRAY1:.*]]: !llhd.sig<!llhd.array<1xi32>>
func @extract_slice_array_signals (%array5 : !llhd.sig<!llhd.array<5xi1>>, %array1 : !llhd.sig<!llhd.array<1xi32>>) -> () {
  // CHECK-NEXT: %{{.*}} = llhd.extract_slice %[[ARRAY5]], 2 : !llhd.sig<!llhd.array<5xi1>> -> !llhd.sig<!llhd.array<3xi1>>
  %0 = llhd.extract_slice %array5, 2 : !llhd.sig<!llhd.array<5xi1>> -> !llhd.sig<!llhd.array<3xi1>>
  // CHECK-NEXT: %{{.*}} = llhd.extract_slice %[[ARRAY1]], 0 : !llhd.sig<!llhd.array<1xi32>> -> !llhd.sig<!llhd.array<1xi32>>
  %1 = llhd.extract_slice %array1, 0 : !llhd.sig<!llhd.array<1xi32>> -> !llhd.sig<!llhd.array<1xi32>>

  return
}

// CHECK-LABEL: @dyn_extract_slice_integers
// CHECK-SAME: %[[CI1:.*]]: i1,
// CHECK-SAME: %[[CI32:.*]]: i32,
// CHECK-SAME: %[[IND0:.*]]: i5,
// CHECK-SAME: %[[IND1:.*]]: i10
func @dyn_extract_slice_integers(%cI1 : i1, %cI32 : i32, %i0 : i5, %i1 : i10) {
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[CI1]], %[[IND0]] : (i1, i5) -> i1
  %0 = llhd.dyn_extract_slice %cI1, %i0 : (i1, i5) -> i1
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[CI32]], %[[IND1]] : (i32, i10) -> i15
  %1 = llhd.dyn_extract_slice %cI32, %i1 : (i32, i10) -> i15

  return
}

// CHECK-LABEL: @dyn_extract_slice_signals
// CHECK-SAME: %[[SI1:.*]]: !llhd.sig<i1>,
// CHECK-SAME: %[[SI32:.*]]: !llhd.sig<i32>,
// CHECK-SAME: %[[IND0:.*]]: i5,
// CHECK-SAME: %[[IND1:.*]]: i10
func @dyn_extract_slice_signals (%sI1 : !llhd.sig<i1>, %sI32 : !llhd.sig<i32>, %i0 : i5, %i1 : i10) {
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[SI1]], %[[IND0]] : (!llhd.sig<i1>, i5) -> !llhd.sig<i1>
  %0 = llhd.dyn_extract_slice %sI1, %i0 : (!llhd.sig<i1>, i5) -> !llhd.sig<i1>
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[SI32]], %[[IND1]] : (!llhd.sig<i32>, i10) -> !llhd.sig<i5>
  %1 = llhd.dyn_extract_slice %sI32, %i1 : (!llhd.sig<i32>, i10) -> !llhd.sig<i5>

  return
}

// CHECK-LABEL: @dyn_extract_slice_array_signals
// CHECK-SAME: %[[SI1:.*]]: !llhd.sig<!llhd.array<5xi1>>,
// CHECK-SAME: %[[SI32:.*]]: !llhd.sig<!llhd.array<1xi32>>,
// CHECK-SAME: %[[IND0:.*]]: i5,
// CHECK-SAME: %[[IND1:.*]]: i10
func @dyn_extract_slice_array_signals (%sI1 : !llhd.sig<!llhd.array<5xi1>>, %sI32 : !llhd.sig<!llhd.array<1xi32>>, %i0 : i5, %i1 : i10) {
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[SI1]], %[[IND0]] : (!llhd.sig<!llhd.array<5xi1>>, i5) -> !llhd.sig<!llhd.array<2xi1>>
  %0 = llhd.dyn_extract_slice %sI1, %i0 : (!llhd.sig<!llhd.array<5xi1>>, i5) -> !llhd.sig<!llhd.array<2xi1>>
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[SI32]], %[[IND1]] : (!llhd.sig<!llhd.array<1xi32>>, i10) -> !llhd.sig<!llhd.array<1xi32>>
  %1 = llhd.dyn_extract_slice %sI32, %i1 : (!llhd.sig<!llhd.array<1xi32>>, i10) -> !llhd.sig<!llhd.array<1xi32>>

  return
}

// CHECK-LABEL: @dyn_extract_slice_vec
// CHECK-SAME: %[[V1:.*]]: !llhd.array<1xi1>,
// CHECK-SAME: %[[V10:.*]]: !llhd.array<10xi1>,
// CHECK-SAME: %[[IND0:.*]]: i5,
// CHECK-SAME: %[[IND1:.*]]: i10
func @dyn_extract_slice_vec(%v1 : !llhd.array<1xi1>, %v10 : !llhd.array<10xi1>, %i0 : i5, %i1 : i10) {
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[V1]], %[[IND0]] : (!llhd.array<1xi1>, i5) -> !llhd.array<1xi1>
  %0 = llhd.dyn_extract_slice %v1, %i0 : (!llhd.array<1xi1>, i5) -> !llhd.array<1xi1>
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_slice %[[V10]], %[[IND1]] : (!llhd.array<10xi1>, i10) -> !llhd.array<5xi1>
  %1 = llhd.dyn_extract_slice %v10, %i1 : (!llhd.array<10xi1>, i10) -> !llhd.array<5xi1>

  return
}

// CHECK-LABEL: @extract_element_arrays
// CHECK-SAME: %[[ARRAY1:.*]]: !llhd.array<1xi1>
// CHECK-SAME: %[[ARRAY5:.*]]: !llhd.array<5xi32>
func @extract_element_arrays(%array1 : !llhd.array<1xi1>, %array5 : !llhd.array<5xi32>) {
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[ARRAY1]], 0 : !llhd.array<1xi1> -> i1
  %0 = llhd.extract_element %array1, 0 : !llhd.array<1xi1> -> i1
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[ARRAY5]], 4 : !llhd.array<5xi32> -> i32
  %1 = llhd.extract_element %array5, 4 : !llhd.array<5xi32> -> i32

  return
}

// CHECK-LABEL: @extract_element_tuples
// CHECK-SAME: %[[TUP:.*]]: tuple<i1, i2, i3>
func @extract_element_tuples(%tup : tuple<i1, i2, i3>) {
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[TUP]], 0 : tuple<i1, i2, i3> -> i1
  %0 = llhd.extract_element %tup, 0 : tuple<i1, i2, i3> -> i1
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[TUP]], 2 : tuple<i1, i2, i3> -> i3
  %1 = llhd.extract_element %tup, 2 : tuple<i1, i2, i3> -> i3

  return
}

// CHECK-LABEL: @extract_element_signals_of_arrays
// CHECK-SAME: %[[ARRAY1:.*]]: !llhd.sig<!llhd.array<1xi1>>
// CHECK-SAME: %[[ARRAY5:.*]]: !llhd.sig<!llhd.array<5xi32>>
func @extract_element_signals_of_arrays(%array1 : !llhd.sig<!llhd.array<1xi1>>, %array5 : !llhd.sig<!llhd.array<5xi32>>) {
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[ARRAY1]], 0 : !llhd.sig<!llhd.array<1xi1>> -> !llhd.sig<i1>
  %0 = llhd.extract_element %array1, 0 : !llhd.sig<!llhd.array<1xi1>> -> !llhd.sig<i1>
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[ARRAY5]], 4 : !llhd.sig<!llhd.array<5xi32>> -> !llhd.sig<i32>
  %1 = llhd.extract_element %array5, 4 : !llhd.sig<!llhd.array<5xi32>> -> !llhd.sig<i32>

  return
}

// CHECK-LABEL: @extract_element_signals_of_tuples
// CHECK-SAME: %[[TUP:.*]]: !llhd.sig<tuple<i1, i2, i3>>
func @extract_element_signals_of_tuples(%tup : !llhd.sig<tuple<i1, i2, i3>>) {
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[TUP]], 0 : !llhd.sig<tuple<i1, i2, i3>> -> !llhd.sig<i1>
  %0 = llhd.extract_element %tup, 0 : !llhd.sig<tuple<i1, i2, i3>> -> !llhd.sig<i1>
  // CHECK-NEXT: %{{.*}} = llhd.extract_element %[[TUP]], 2 : !llhd.sig<tuple<i1, i2, i3>> -> !llhd.sig<i3>
  %1 = llhd.extract_element %tup, 2 : !llhd.sig<tuple<i1, i2, i3>> -> !llhd.sig<i3>

  return
}

// CHECK-LABEL: @dyn_extract_element_arrays
// CHECK-SAME: %[[INDEX:.*]]: i32
// CHECK-SAME: %[[ARRAY1:.*]]: !llhd.array<1xi1>
// CHECK-SAME: %[[ARRAY5:.*]]: !llhd.array<5xi32>
func @dyn_extract_element_arrays(%index : i32, %array1 : !llhd.array<1xi1>, %array5 : !llhd.array<5xi32>) {
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_element %[[ARRAY1]], %[[INDEX]] : (!llhd.array<1xi1>, i32) -> i1
  %0 = llhd.dyn_extract_element %array1, %index : (!llhd.array<1xi1>, i32) -> i1
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_element %[[ARRAY5]], %[[INDEX]] : (!llhd.array<5xi32>, i32) -> i32
  %1 = llhd.dyn_extract_element %array5, %index : (!llhd.array<5xi32>, i32) -> i32

  return
}

// CHECK-LABEL: @dyn_extract_element_signals_of_arrays
// CHECK-SAME: %[[INDEX:.*]]: i32
// CHECK-SAME: %[[ARRAY1:.*]]: !llhd.sig<!llhd.array<1xi1>>
// CHECK-SAME: %[[ARRAY5:.*]]: !llhd.sig<!llhd.array<5xi32>>
func @dyn_extract_element_signals_of_arrays(%index : i32, %array1 : !llhd.sig<!llhd.array<1xi1>>, %array5 : !llhd.sig<!llhd.array<5xi32>>) {
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_element %[[ARRAY1]], %[[INDEX]] : (!llhd.sig<!llhd.array<1xi1>>, i32) -> !llhd.sig<i1>
  %0 = llhd.dyn_extract_element %array1, %index : (!llhd.sig<!llhd.array<1xi1>>, i32) -> !llhd.sig<i1>
  // CHECK-NEXT: %{{.*}} = llhd.dyn_extract_element %[[ARRAY5]], %[[INDEX]] : (!llhd.sig<!llhd.array<5xi32>>, i32) -> !llhd.sig<i32>
  %1 = llhd.dyn_extract_element %array5, %index : (!llhd.sig<!llhd.array<5xi32>>, i32) -> !llhd.sig<i32>

  return
}

// -----

func @illegal_array_to_signal(%array : !llhd.array<3xi32>) {
  // expected-error @+1 {{failed to verify that 'target' and 'result' have to be both either signless integers, signals or arrays with the same element type}}
  %0 = llhd.extract_slice %array, 0 : !llhd.array<3xi32> -> !llhd.sig<!llhd.array<3xi32>>

  return
}

// -----

func @illegal_signal_to_array(%sig : !llhd.sig<!llhd.array<3xi32>>) {
  // expected-error @+1 {{failed to verify that 'target' and 'result' have to be both either signless integers, signals or arrays with the same element type}}
  %0 = llhd.extract_slice %sig, 0 : !llhd.sig<!llhd.array<3xi32>> -> !llhd.array<3xi32>

  return
}

// -----

func @illegal_array_element_type_mismatch(%sig : !llhd.sig<!llhd.array<3xi32>>) {
  // expected-error @+1 {{failed to verify that 'target' and 'result' have to be both either signless integers, signals or arrays with the same element type}}
  %0 = llhd.extract_slice %sig, 0 : !llhd.sig<!llhd.array<3xi32>> -> !llhd.sig<!llhd.array<2xi1>>

  return
}

// -----

func @illegal_result_array_too_big(%sig : !llhd.sig<!llhd.array<3xi32>>) {
  // expected-error @+1 {{'start' + size of the slice have to be smaller or equal to the 'target' size}}
  %0 = llhd.extract_slice %sig, 0 : !llhd.sig<!llhd.array<3xi32>> -> !llhd.sig<!llhd.array<4xi32>>

  return
}

// -----

func @illegal_int_to_sig(%c : i32) {
  // expected-error @+1 {{failed to verify that 'target' and 'result' have to be both either signless integers, signals or arrays with the same element type}}
  %0 = llhd.extract_slice %c, 0 : i32 -> !llhd.sig<i10>

  return
}

// -----

func @illegal_sig_to_int(%s : !llhd.sig<i32>) {
  // expected-error @+1 {{failed to verify that 'target' and 'result' have to be both either signless integers, signals or arrays with the same element type}}
  %0 = llhd.extract_slice %s, 0 : !llhd.sig<i32> -> i10

  return
}

// -----

func @illegal_out_too_big(%c : i32) {
  // expected-error @+1 {{failed to verify that 'start' + size of the slice have to be smaller or equal to the 'target' size}}
  %0 = llhd.extract_slice %c, 0 : i32 -> i40

  return
}

// -----

func @illegal_array_to_signal(%array : !llhd.array<3xi32>, %index : i32) {
  // expected-error @+1 {{'target' and 'result' types have to match apart from their width}}
  %0 = llhd.dyn_extract_slice %array, %index : (!llhd.array<3xi32>, i32) -> !llhd.sig<!llhd.array<3xi32>>

  return
}

// -----

func @illegal_signal_to_array(%sig : !llhd.sig<!llhd.array<3xi32>>, %index: i32) {
  // expected-error @+1 {{'target' and 'result' types have to match apart from their width}}
  %0 = llhd.dyn_extract_slice %sig, %index : (!llhd.sig<!llhd.array<3xi32>>, i32) -> !llhd.array<3xi32>

  return
}

// -----

func @illegal_array_element_type_mismatch(%sig : !llhd.sig<!llhd.array<3xi32>>, %index : i32) {
  // expected-error @+1 {{'target' and 'result' types have to match apart from their width}}
  %0 = llhd.dyn_extract_slice %sig, %index : (!llhd.sig<!llhd.array<3xi32>>, i32) -> !llhd.sig<!llhd.array<2xi1>>

  return
}

// -----

func @illegal_result_array_too_big(%sig : !llhd.sig<!llhd.array<3xi32>>, %index : i32) {
  // expected-error @+1 {{the result width cannot be larger than the target operand width}}
  %0 = llhd.dyn_extract_slice %sig, %index : (!llhd.sig<!llhd.array<3xi32>>, i32) -> !llhd.sig<!llhd.array<4xi32>>

  return
}

// -----

func @dyn_extract_slice_illegal_conversion(%s : !llhd.sig<i32>, %i : i1) {
  // expected-error @+1 {{'llhd.dyn_extract_slice' op failed to verify that 'target' and 'result' types have to match apart from their width}}
  %0 = llhd.dyn_extract_slice %s, %i : (!llhd.sig<i32>, i1) -> i10

  return
}

// -----

func @dyn_extract_slice_illegal_out_too_wide(%c : i32, %i : i1) {
  // expected-error @+1 {{'llhd.dyn_extract_slice' op failed to verify that the result width cannot be larger than the target operand width}}
  %0 = llhd.dyn_extract_slice %c, %i : (i32, i1) -> i40

  return
}

// -----

func @dyn_extract_slice_illegal_vec_element_conversion(%c : !llhd.array<1xi1>, %i : i1) {
  // expected-error @+1 {{'llhd.dyn_extract_slice' op failed to verify that 'target' and 'result' types have to match apart from their width}}
  %0 = llhd.dyn_extract_slice %c, %i : (!llhd.array<1xi1>, i1) -> !llhd.array<1xi10>

  return
}

// -----

func @extract_element_array_index_out_of_bounds(%array : !llhd.array<3xi1>) {
  // expected-error @+1 {{'index' has to be smaller than the width of the 'target' type}}
  %0 = llhd.extract_element %array, 3 : !llhd.array<3xi1> -> i1

  return
}

// -----

func @extract_element_tuple_index_out_of_bounds(%tup : tuple<i1, i2, i3>) {
  // expected-error @+1 {{'index' has to be smaller than the width of the 'target' type}}
  %0 = llhd.extract_element %tup, 3 : tuple<i1, i2, i3> -> i3

  return
}

// -----

func @extract_element_array_type_mismatch(%array : !llhd.array<3xi1>) {
  // expected-error @+1 {{'result' type must match the type of 'target' at position 'index', or in case 'target' is a signal, it must be a signal of the underlying type of 'target' at position 'index'}}
  %0 = llhd.extract_element %array, 0 : !llhd.array<3xi1> -> i2

  return
}

// -----

func @extract_element_tuple_type_mismatch(%tup : tuple<i1, i2, i3>) {
  // expected-error @+1 {{'result' type must match the type of 'target' at position 'index', or in case 'target' is a signal, it must be a signal of the underlying type of 'target' at position 'index'}}
  %0 = llhd.extract_element %tup, 0 : tuple<i1, i2, i3> -> i2

  return
}

// -----

func @extract_element_signal_type_mismatch(%sig : !llhd.sig<tuple<i1, i2, i3>>) {
  // expected-error @+1 {{'result' type must match the type of 'target' at position 'index', or in case 'target' is a signal, it must be a signal of the underlying type of 'target' at position 'index'}}
  %0 = llhd.extract_element %sig, 0 : !llhd.sig<tuple<i1, i2, i3>> -> !llhd.sig<i2>

  return
}

// -----

func @extract_element_illegal_signal_alias(%sig : !llhd.sig<tuple<i1, i2, i3>>) {
  // expected-error @+1 {{'result' type must match the type of 'target' at position 'index', or in case 'target' is a signal, it must be a signal of the underlying type of 'target' at position 'index'}}
  %0 = llhd.extract_element %sig, 0 : !llhd.sig<tuple<i1, i2, i3>> -> i1

  return
}

// -----

func @dyn_extract_element_array_type_mismatch(%index : i2, %array : !llhd.array<3xi1>) {
  // expected-error @+1 {{'result' must be the element type of the 'target' array, in case 'target' is a signal of an array, 'result' also is a signal of the array element type}}
  %0 = llhd.dyn_extract_element %array, %index : (!llhd.array<3xi1>, i2) -> i2

  return
}

// -----

func @dyn_extract_element_signal_type_mismatch(%index : i2, %sig : !llhd.sig<!llhd.array<3xi1>>) {
  // expected-error @+1 {{'result' must be the element type of the 'target' array, in case 'target' is a signal of an array, 'result' also is a signal of the array element type}}
  %0 = llhd.dyn_extract_element %sig, %index : (!llhd.sig<!llhd.array<3xi1>>, i2) -> !llhd.sig<i2>

  return
}

// -----

func @dyn_extract_element_illegal_signal_alias(%index : i2, %sig : !llhd.sig<!llhd.array<3xi1>>) {
  // expected-error @+1 {{'result' must be the element type of the 'target' array, in case 'target' is a signal of an array, 'result' also is a signal of the array element type}}
  %0 = llhd.dyn_extract_element %sig, %index : (!llhd.sig<!llhd.array<3xi1>>, i2) -> i1

  return
}
