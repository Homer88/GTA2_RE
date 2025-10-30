#ifndef __S9__H__
#define __S9__H__

#include <assert.h>


struct S9{
	char arr_24[24];
};

static_assert(sizeof(S9) == 0x18, "ERROR SIZE Structure S9");

S9* constructS9(S9* thisS9);


#endif // !__S9__H__
