#ifndef __S55_H__
#define __S55_H__

#include <assert.h>

struct S55
{
	int field_0;
	int field_4;
	int field_8;
	int arr_6000[6000];
	unsigned char gap5DCC[47987];
	char field_1193F;
	int field_11940;

};

static_assert(sizeof(S55) == 0x11944, "Error Size Structure S55");
static  S55* gS55 = (S55*)0x005e6688;

#endif // !__S55_H__

