#ifndef __S19__H__
#define __S19__H__

#include <assert.h>

struct S19
{
	int A;

};

static_assert (sizeof(S19) == 0x4, "Error Size S19");
static S19* gS19;
void SetPararam_0(S19* pS19);
#endif // !__S19__H__

