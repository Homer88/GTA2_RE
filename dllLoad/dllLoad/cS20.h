#ifndef __S20_H_
#define __S20_H_

#include <assert.h>
#include "cS20_01.h"

struct S20
{
	S20_01 ARR_1000[1000];
	int field_2EE0;
};

static_assert (sizeof(S20)== 0x2ee4, "Error Size S20");
static S20* gS20 = (S20*)0x00672578;

void SetPararm_0x2ee0(S20* pS20);


#endif // !__S20_H_

