// RUN: llhd-sim %s | FileCheck %s

// CHECK: 0ns 0d 0e  root/shr  0x08
// CHECK-NEXT: 0ns 0d 0e  root/shl  0x01
// CHECK-NEXT: 1ns 0d 0e  root/shr  0x0c
// CHECK-NEXT: 1ns 0d 0e  root/shl  0x02
// CHECK-NEXT: 2ns 0d 0e  root/shr  0x0e
// CHECK-NEXT: 2ns 0d 0e  root/shl  0x04
// CHECK-NEXT: 3ns 0d 0e  root/shr  0x0f
// CHECK-NEXT: 3ns 0d 0e  root/shl  0x08
// CHECK-NEXT: 4ns 0d 0e  root/shl  0x00

llhd.entity @root () -> () {
  %time = llhd.const #llhd.time<1ns, 0d, 0e> : !llhd.time

  %init = llhd.const 8 : i4
  %hidden = llhd.const 1 : i2
  %amnt = llhd.const 1 : i1

  %sig = llhd.sig "shr" %init : i4
  %prbd = llhd.prb %sig : !llhd.sig<i4>
  %shr = llhd.shr %prbd, %hidden, %amnt : (i4, i2, i1) -> i4
  llhd.drv %sig, %shr after %time : !llhd.sig<i4>

  %init1 = llhd.const 1 : i4
  %hidden1 = llhd.const 0 : i1
  %amnt1 = llhd.const 1 : i1

  %sig1 = llhd.sig "shl" %init1 : i4
  %prbd1 = llhd.prb %sig1 : !llhd.sig<i4>
  %shl = llhd.shl %prbd1, %hidden1, %amnt1 : (i4, i1, i1) -> i4
  llhd.drv %sig1, %shl after %time : !llhd.sig<i4>
}
