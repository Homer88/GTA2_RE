#ifndef __S136_H__
#define __S136_H__

#include <assert.h>


struct S136
{
	char Visible;
	char PlayerArena;
	short field_2;
	short field_4;
	wchar_t str[50];
	short filed_6A;
	short filed_6C;
};

static_assert(sizeof(S136) == 0x6E, "ERROR MENU STRUCT");

#endif // !__S136_H

