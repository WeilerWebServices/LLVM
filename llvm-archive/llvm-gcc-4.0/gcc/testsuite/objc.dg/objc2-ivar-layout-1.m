/* APPLE LOCAL file radar 5109807 */
/* Test that ivar layout bytestream info is generated as expected in the the test 
   extracted from AppKit */
/* { dg-do run { target *-*-darwin* } } */
/* { dg-options "-mmacosx-version-min=10.5 -framework Foundation -fobjc-gc" } */
/* { dg-skip-if "" { *-*-darwin* } { "-m64" } { "" } } */

#include <Foundation/Foundation.h>

@interface NSFileLocationComponent : NSObject { 
    @private

    id _specifierOrStandardizedPath;
    BOOL _carbonCatalogInfoAndNameAreValid;             
    FSCatalogInfoBitmap _carbonCatalogInfoMask;         
    struct FSCatalogInfo _carbonCatalogInfo;
    HFSUniStr255 _carbonName;
    id _name;                                    
    id _containerComponent;       
    id _presentableName;                         
    id _iconAsAttributedString;   
}
@end

@implementation NSFileLocationComponent @end

const char expected [] = {0x02, 0x10, 0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,
				   0x04, 0};

int main()
{
	int i = 0;
	const char *ivar_layout_string = (const char*)class_getIvarLayout([NSFileLocationComponent class]);
	if (strcmp (ivar_layout_string, expected))
	  abort ();
	return 0;
}
