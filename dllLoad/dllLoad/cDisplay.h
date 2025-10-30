#ifndef __DISPLAY__H_
#define __DISPLAY__H_

#include <assert.h>
#include "cS19.h"

struct Display
{

	S19 structS19[7];

};

static_assert(sizeof(Display)== 0x1c, "Error Size Display");

static Display* gDisplay = (Display*)0x005e8b80;

#endif // !__Display__H_

