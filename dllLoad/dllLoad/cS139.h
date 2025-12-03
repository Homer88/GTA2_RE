#ifndef __cS139_H__
#define __cS139_H__

#include <assert.h>

#include "cS140.h"


struct S139
{
	short index;
	S140 sS140[600];
};
static_assert(sizeof(S139) == 0xFD22, "ERROR MENU PAGE");


#endif // !

