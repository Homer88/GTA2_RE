#ifndef __cS140_H__
#define __cS140_H__

#include <assert.h>

struct S140
{
	short field0;
	short field2;
	short field4;
	short field6;
	char str[100];
};
static_assert(sizeof(S140) == 108, "ERROR MENU PAGE");




#endif // !1
