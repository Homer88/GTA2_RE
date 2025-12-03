#ifndef __cPlayerName_H__
#define __cPlayerName_H__

#include <assert.h>

struct PlayerName
{
	wchar_t strPlayerName[8];
	

};

static_assert(sizeof(PlayerName) == 16, "ERROR PlayerName");
#endif // !__cPlayerName_H__
