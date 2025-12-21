#ifndef __S137_H__
#define __S137_H__

#include <assert.h>

struct S137
{
	short field_0;
	short X;
	short Y;
};

static_assert(sizeof(S137) == 6, "ERROR MENU STRUCT");


#endif