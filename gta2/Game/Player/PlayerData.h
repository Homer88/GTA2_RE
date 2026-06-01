#ifndef __PLAYER_DATA_H_
#define __PLAYER_DATA_H_
#include "..\Player\PlayerSlotSlave.h"

class PlayerData{
	public:
		PlayerSlotSlave PlayerSlotSave[8];
		void WriteFileNamePlayer(unsigned short);
};



#endif