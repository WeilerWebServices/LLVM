// RUN: llhd-sim %s | FileCheck %s

// CHECK: 0ns 0d 0e  root/bool  0x01
// CHECK-NEXT: 0ns 0d 0e  root/fair  0xff00
// CHECK-NEXT: 0ns 0d 0e  root/ginormous 0x000000000000000000000008727f6369aaf83ca15026747af8c7f196ce3f0ad2

llhd.entity @root () -> () {
  %small = llhd.const 1 : i1
  %r = llhd.const 0xff00 : i16
  %b = llhd.const 12345678901234567890123456789012345678901234567890 : i256
  %1 = llhd.sig "bool" %small : i1
  %2 = llhd.sig "fair" %r : i16
  %3 = llhd.sig "ginormous" %b : i256
}
