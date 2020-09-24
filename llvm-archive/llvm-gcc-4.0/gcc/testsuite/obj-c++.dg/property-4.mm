/* APPLE LOCAL file radar 4505126 */
/* Test lookup of properties in categories. */
/* Program should compile with no error or warning. */
/* { dg-do compile { target *-*-darwin* } } */
/* APPLE LOCAL radar 4899595 */
/* { dg-options "-fno-objc-new-property -mmacosx-version-min=10.5 -fobjc-abi-version=2" } */
#import <Cocoa/Cocoa.h>

@interface NSWindow (Properties)
@property(readonly) NSSize size;
@property(bycopy, dynamic) NSString* title;
@end

@implementation NSWindow (Properties)

- (NSSize)size {
    return _frame.size;
}

@end

int main(int argc, char **argv) {
    NSAutoreleasePool *pool = [NSAutoreleasePool new];

    NSWindow *window = [[NSWindow new] autorelease];
    window.title = @"test1";
    NSLog(@"window.title = %@", window.title);
    NSSize size = window.size;

    [pool drain];
    return 0;
}

