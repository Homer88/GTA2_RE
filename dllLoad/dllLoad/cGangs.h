#ifndef __GANGS_H__
#define __GANGS_H__

#include <assert.h>


#include "cGang.h"

struct Gangs {
	Gang structGang[10];
};

static_assert (sizeof(Gangs)== 0xCA8, "ERROR SIZE GANG");

static Gangs* gGangs = (Gangs*)0x005EB898;

#endif // !__GANG_H__
