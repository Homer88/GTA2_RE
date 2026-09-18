#ifndef __cKeyState__H_
#define __cKeyState__H_
#include <assert.h>

#pragma pack(push, 1)
struct KeyState
{
	unsigned char left;
	unsigned char Right;
	unsigned char up;
	unsigned char down;
	unsigned char enter;
	unsigned char esc;
	unsigned char del;
};
#pragma pack(pop)

static_assert(sizeof(KeyState) == 7, "Error Size KeyState");
#endif // !__cKeyState__H_