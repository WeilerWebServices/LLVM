/* Test for handling of struct-returning methods
   for the Mac OS X ("NeXT") runtime (which uses specialized entry
   points).  */
/* Contributed by Ziemowit Laski <zlaski@apple.com>.  */
/* { dg-do compile { target *-*-darwin* } } */
/* APPLE LOCAL radar 4492976 */
/* { dg-skip-if "" { *-*-darwin* } { "-m64" } { "" } } */

/* APPLE LOCAL radar 4894756 */
#include "../objc/execute/Object2.h"

struct astruct {
  float a, b;
  /* APPLE LOCAL begin testing */
  char c;
} glob = { 1.0, 2.0, 'a' };
/* APPLE LOCAL end testing */

struct bstruct {
  float a, b, c, d, e, f;
} globb = { 1, 2, 3, 4, 5, 6 };

@interface foo : Object
- (struct astruct) stret;
- (struct bstruct) stretb;
@end

@implementation foo : Object
- (struct astruct) stret { return glob; }
- (struct bstruct) stretb { return globb; }
@end

@interface bar: foo
- (struct astruct) stret;
- (struct bstruct) stretb;
@end

@implementation bar
- (struct astruct) stret { return [super stret]; }
- (struct bstruct) stretb { return [super stretb]; }
@end

struct astruct afunc(foo *foo_obj) {
  return [foo_obj stret];
}

/* { dg-final { scan-assembler "objc_msgSend_stret" } } */
/* { dg-final { scan-assembler "objc_msgSendSuper_stret" } } */

/* { dg-final { scan-assembler-not "objc_msgSend\[^_S\]" } } */
/* { dg-final { scan-assembler-not "objc_msgSendSuper\[^_\]" } } */

