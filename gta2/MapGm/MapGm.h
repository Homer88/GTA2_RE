#ifndef __MAP_GM_H_
#define __MAP_GM_H_


class MapGm{
	public:
	int  GetPlayerSlotSave();
	int  GetPlayerArena();
	int GetBonusStage();
	int DecodeBonusStage(int, int, int);
};

#endif //__MAP_GM_H_