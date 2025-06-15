#pragma once

#include "Global.h"

class Game{
	private:

	public:
		bool Status;
		 //GameStatus *Status;
	//	 Player *pPlayer[6];
		// Player *CurentPlayer;
		// char CurentPlayer__;
		// byte ID;
		// char field_22;
  BYTE NumPlayers;
  char PlayerInFocus;
  char field_25;
  char field_26;
  char field_27;
  int field_28;
  int State;
  char field_30;
  char field_31;
  char field_32;
  char field_33;
  int SkipPolice;
  //Player *Player;
  char gSkilPolice;
  char field_3D;
  char field_3E;
  char field_3F;

		Game();
		~Game();
		void* InitPlayerOrTimer();

};



