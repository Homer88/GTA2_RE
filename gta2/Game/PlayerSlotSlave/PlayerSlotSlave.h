
#ifndef __PLAYER_SLOT_SLAVE__H_
#define __PLAYER_SLOT_SLAVE__H_
class PlayerSlotSlave{
	
	public:
		unsigned int Value;
		int ActiveArenaSlot;
		//ArenaSlots ArenaSlotArray[3];
		wchar_t PlayerName[8];
		PlayerSlotSlave();
		unsigned int  GetValue();
		void   SetValue(unsigned int Value);
		void   SetMultiPlayer(unsigned int Value);
		unsigned int GetMultiPlayer();
		
};	

#endif