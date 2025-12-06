#ifndef __PLAYDAT_H_
#define __PLAYDAT_H_

#include <assert.h>
#include "PlayerSlotSave.h"

class PlayerData {
public:
	PlayerSlotSave pPlayerSlotSave[8];

	PlayerData();
	void WriteFileNamePlayer(int PlayerSlot);
};

#endif // !__PLAYDAT_H_

