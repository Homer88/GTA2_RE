#ifndef __PLAYER_H__
#define __PLAYER_H__
#include <assert.h>

enum StarPolice {
	StarPolice_0=0u,
	StarPolice_1 = 600u,                  /// Одна звезда
	StarPolice_2 = 1600u,                 /// Две звезды 
	StarPolice_3 = 3000u,
	StarPolice_4 = 5000u,
	StarPolice_5 = 8000u,
	StarPolice_6 = 12000u,
};


enum WantedLevel {
	Level_0 = 0u,
	Level_1 = 1u,
	Level_2 = 2u,
	Level_3 = 3u,
	Level_4 = 4u,
	Level_5 = 5u,
	Level_6 = 6u,
};

struct Player {
	char a[0x20];
};
static_assert (sizeof(Player) == 0x20, "ERROR PLAYER");


#endif // !__PLAYER_H__

