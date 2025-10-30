#ifndef __PLAYER_DATA_GAMES_H_
#define __PLAYER_DATA_GAMES_H_
#include <assert.h>

struct PlayerData{
	int field;
	int field_4;
	int field_8;
	int field_C;
	short field_10;
	char a[0x2BAE];
};

static_assert(sizeof(PlayerData) == 0x2bc0, "ERROR PLAYER DATA." );

#endif // !__PLAYER_DATA_GAMES_H_

