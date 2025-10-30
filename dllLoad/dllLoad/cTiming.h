#ifndef __TIMING__H_
#define __TIMING__H_

#include <assert.h>
#include "cS36.h"

struct Timeng{
	int uns; /// не знаю
	unsigned int TimerGetTime;
	int uns1;
	int uns2;
	unsigned int TimerGetTime1;
	int uns3;
	S36 structS36[5];

};

static_assert(sizeof(Timeng)== 0x54, "ERROR SIZE Timeng");

#endif