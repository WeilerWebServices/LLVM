/* APPLE LOCAL file radar 4533107 */
/* Test for correct name lookup in presence of multiple protocols. */
/* APPLE LOCAL radar 4899595 */
/* { dg-options "-fno-objc-new-property -mmacosx-version-min=10.5 -std=c99" } */
/* { dg-do compile { target *-*-darwin* } } */

@protocol NSCoding
@end

@protocol LKObject <NSCoding>
@end

@protocol LKTiming
@property double duration;
@end

@interface LKAnimation <LKObject, LKTiming>
@end

static void test (void)
{
    LKAnimation *anim;
    anim.duration = 1.0;
}

