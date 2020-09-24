// RUN: circt-translate %s -emit-verilog -verify-diagnostics | FileCheck %s --strict-whitespace

firrtl.circuit "M1" {
  firrtl.module @M1(%x : !firrtl.uint<8>,
                    %y : !firrtl.flip<uint<8>>,
                    %z : i8) {
    %c42 = rtl.constant (42 : i8) : i8
    %c5 = rtl.constant (5 : i8) : i8
    %a = rtl.add %z, %c42 : i8
    %b = rtl.mul %a, %c5 : i8
    %c = firrtl.stdIntCast %b : (i8) -> !firrtl.uint<8>
    firrtl.connect %y, %c : !firrtl.flip<uint<8>>, !firrtl.uint<8>

    %d = rtl.mul %z, %z, %z : i8
    %e = rtl.mod %d, %c5 : i8
    %f = rtl.concat %e, %z, %d : (i8, i8, i8) -> i8
    %g = firrtl.stdIntCast %f : (i8) -> !firrtl.uint<8>
    firrtl.connect %y, %g : !firrtl.flip<uint<8>>, !firrtl.uint<8>
  }

  // CHECK-LABEL: module M1(
  // CHECK-NEXT:    input  [7:0] x,
  // CHECK-NEXT:    output [7:0] y,
  // CHECK-NEXT:    input  [7:0] z);
  // CHECK-EMPTY:
  // CHECK-NEXT:    assign y = (z + 8'h2A) * 8'h5;
  // CHECK-NEXT:    wire [7:0] _T = z * z * z;
  // CHECK-NEXT:    assign y = {_T % 8'h5, z, _T};
  // CHECK-NEXT:  endmodule


   firrtl.module @M2(%x : i8,
                     %y : i8,
                     %z : i8) {
    %c42 = rtl.constant (42 : i8) : i8
    rtl.connect %x, %c42 : i8

    %w1 = rtl.wire { name = "foo" } : i8
    rtl.connect %w1, %y : i8
    rtl.connect %z, %w1 : i8
  }

  // CHECK-LABEL: module M2(
  // CHECK-NEXT:    input [7:0] x, y, z);
  // CHECK-EMPTY:
  // CHECK-NEXT:    wire [7:0] foo;
  // CHECK-EMPTY:
  // CHECK-NEXT:    assign x = 8'h2A;
  // CHECK-NEXT:    assign foo = y;
  // CHECK-NEXT:    assign z = foo;
  // CHECK-NEXT:  endmodule

  firrtl.module @M3(%x : !firrtl.uint<8>,
                    %y : !firrtl.flip<uint<8>>,
                    %z : i8, %q : i16) {
    %c42 = rtl.constant (42 : i8) : i8
    %c5 = rtl.constant (5 : i8) : i8
    %ext_z = rtl.extract %q from 8 : (i16) -> i8
    %a = rtl.add %z, %c42 : i8
    %v1 = rtl.and %a, %c42, %c5 : i8
    %v2 = rtl.or %a, %v1 : i8
    %v3 = rtl.xor %v1, %v2, %c42, %ext_z : i8
    %c = firrtl.stdIntCast %v3 : (i8) -> !firrtl.uint<8>
    firrtl.connect %y, %c : !firrtl.flip<uint<8>>, !firrtl.uint<8>
  }

  // CHECK-LABEL: module M3(
  // CHECK-NEXT:  input  [7:0]  x,
  // CHECK-NEXT:  output [7:0]  y,
  // CHECK-NEXT:  input  [7:0]  z,
  // CHECK-NEXT:  input  [15:0] q);
  // CHECK-EMPTY:
  // CHECK-NEXT:  wire [7:0] _T = z + 8'h2A;
  // CHECK-NEXT:  wire [7:0] _T_0 = _T & 8'h2A & 8'h5;
  // CHECK-NEXT:  assign y = _T_0 ^ (_T | _T_0) ^ 8'h2A ^ q[15:8];
  // CHECK-NEXT:endmodule

  rtl.module @B(%a: i1 {rtl.direction = "in"}, 
                %b: i1 {rtl.direction = "out"}, 
                %c: i1 {rtl.direction = "out"}) {
    %0 = rtl.or %a, %a : i1
    %1 = rtl.and %a, %a : i1
    rtl.connect %b, %0 : i1
    rtl.connect %c, %1 : i1
  }

  // CHECK-LABEL: module B(
  // CHECK-NEXT:   input  a,
  // CHECK-NEXT:   output b, c);
  // CHECK-EMPTY: 
  // CHECK-NEXT:   assign b = a | a;
  // CHECK-NEXT:   assign c = a & a;
  // CHECK-NEXT: endmodule

  rtl.module @A(%d: i1 {rtl.direction = "in"}, 
                %e: i1 {rtl.direction = "in"}, 
                %f: i1 {rtl.direction = "out"}) {
    %0 = rtl.and %d, %e : i1
    rtl.connect %f, %0 : i1

    %1 = rtl.mux %d, %d, %e : i1
    rtl.connect %f, %1 : i1
  }
  // CHECK-LABEL: module A(
  // CHECK-NEXT:  input  d, e,
  // CHECK-NEXT:  output f);
  // CHECK-EMPTY:
  // CHECK-NEXT:  assign f = d & e;
  // CHECK-NEXT:  assign f = d ? d : e;
  // CHECK-NEXT: endmodule

  rtl.module @AB(%w: i1 {rtl.direction = "in"}, 
                 %x: i1 {rtl.direction = "in"}, 
                 %y: i1 {rtl.direction = "out"},
                 %z: i1 {rtl.direction = "out"}) {

    %w1 = rtl.wire : i1
    %w2 = rtl.wire : i1

    rtl.instance "a1" @A(%w, %w1, %w2) : i1, i1, i1
    rtl.instance "b1" @B(%w2, %w1, %y) : i1, i1, i1

    rtl.connect %z, %x : i1
  }
  //CHECK-LABEL: module AB(
  //CHECK-NEXT:   input  w, x,
  //CHECK-NEXT:   output y, z);
  //CHECK-EMPTY: 
  //CHECK-NEXT:   wire _T;
  //CHECK-NEXT:   wire _T_0;
  //CHECK-EMPTY: 
  //CHECK-NEXT: A a1 (
  //CHECK-NEXT:     .d (w),
  //CHECK-NEXT:     .e (_T),
  //CHECK-NEXT:     .f (_T_0)
  //CHECK-NEXT:   )
  //CHECK-NEXT: B b1 (
  //CHECK-NEXT:     .a (_T_0),
  //CHECK-NEXT:     .b (_T),
  //CHECK-NEXT:     .c (y)
  //CHECK-NEXT:   )
  //CHECK-NEXT:   assign z = x;
  //CHECK-NEXT: endmodule

  // The "_T" value is singly used, but Verilog can't bit extract out of a not,
  // so an explicit temporary is required.

  // CHECK-LABEL: module ExtractCrash(
  // CHECK: wire [3:0] _T = ~a;
  // CHECK-NEXT: assign b = _T[3:2];
  firrtl.module @ExtractCrash(%a: !firrtl.uint<4>, %b: !firrtl.flip<uint<1>>) {
    %26 = firrtl.not %a : (!firrtl.uint<4>) -> !firrtl.uint<4>
    %27 = firrtl.stdIntCast %26 : (!firrtl.uint<4>) -> i4
    %28 = rtl.extract %27 from 2 : (i4) -> i2
    %29 = firrtl.stdIntCast %b : (!firrtl.flip<uint<1>>) -> i1
    %30 = firrtl.stdIntCast %28 : (i2) -> !firrtl.uint<2>
    firrtl.connect %b, %30 : !firrtl.flip<uint<1>>, !firrtl.uint<2>
  }

  rtl.module @shl(%a: i1 {rtl.direction = "in"},
                  %b: i1 {rtl.direction = "out"}) {
    %0 = rtl.shl %a, %a : i1
    rtl.connect %b, %0 : i1
  }

  // CHECK-LABEL:  module shl(
  // CHECK-NEXT:   input  a,
  // CHECK-NEXT:   output b);
  // CHECK-EMPTY:
  // CHECK-NEXT:   assign b = a << a;
  // CHECK-NEXT: endmodule

}
