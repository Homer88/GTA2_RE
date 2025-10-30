#ifndef __GAME_H__
#define __GAME_H__
#include <assert.h>
#include "cPlayer.h"


struct Game{
	bool Status;
	Player* pPlayer[6];
	Player* CurrentPlayer;
	char	CurrentPlayerNumber;
	char	ID;
	char	fi_22;
	char	NumberPlayer;
	char	PlayerInFocus;
	char	fi_25;
	char	field_26;
	char	field_27;
	int		field_28;
	int		State;
	char	field_30;
	char	field_31;
	char	field_32;
	char	field_33;
	int		SkipPolice;
	Player* Player;
	char	gSkilPolice;
	char	field_3D;
	char	field_3E;
	char	field_3F;
};

static_assert(sizeof(Game) == 0x40, "ERROR GAME Struct");



#endif // !__GAME_H__

