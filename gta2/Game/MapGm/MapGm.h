#ifndef __MAP_GM_H_
#define __MAP_GM_H_


class MapGm{
	public:
	int  GetPlayerSlotSave();
	int  GetPlayerArena();
	void  SetPlayerArena(int slot);
	int GetBonusStage();
	int DecodeBonusStage(int, int, int);
	void SetBonusStage(int BonusStage);
};

#endif //__MAP_GM_H_