/* APPLE LOCAL file radar 4577849 */
/* Test for encoding of type strings for instance variables and 
   properties of type id <P1, ..., Pn> */
/* APPLE LOCAL radar 4899595 */
/* { dg-options "-fno-objc-new-property -mmacosx-version-min=10.5" } */
/* { dg-do compile { target *-*-darwin* } } */

@protocol X, Y, Z;
@class Foo;

@protocol Proto
@property (dynamic) id <X> x;
@property (dynamic) id <X, Y> xy;
@property (dynamic) id <X, Y, Z> xyz;
@property(dynamic)  Foo <X, Y, Z> *fooxyz;
@end

@interface Intf <Proto>
{
id <X> IVAR_x;
id <X, Y> IVAR_xy;
id <X, Y, Z> IVAR_xyz;
Foo <X, Y, Z> *IVAR_Fooxyz;
}
@end

@implementation Intf @end


/* { dg-final { scan-assembler ".ascii.*T\@.*<X><Y><Z>.*" } } */
/* { dg-final { scan-assembler ".ascii.*T\@.*Foo<X><Y><Z>.*" } } */

/**
This protocol should generate the following metadata:

struct objc_property_list __Protocol_Test_metadata = {
  sizeof(struct objc_property), 4,
  {
    { "x", "T@\"<X>\",&" },
    { "xy", "T@\"<X><Y>\",&" },
    { "xyz", "T@\"<X><Y><Z>\",&" },
    { "fooxyz", "T@\"Foo<X><Y><Z>\",&" }
  }
};

"T@\"<X><Y><Z>\",D
*/
