#ifndef __GAMEOBJECT__H_
#define __GAMEOBJECT__H_

#include <assert.h>

struct GameObject{
	char a[0x4b];
};

static_assert(sizeof(GameObject) == 0x4b, "ERROR SIZE GameObject");
#endif // !__GameObject__H_

