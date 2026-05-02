#ifndef __GAME__H_
#define __GAME__H_

#include "Player.h"

class Game {
private:
	int a;
public:
	bool Status;
	//GameStatus *Status;
	 class Player  *pPlayer[6];
	 class Player *CurentPlayer;
	 char CurentPlayer__;
	 byte ID;
	
	BYTE NumPlayers;
	char PlayerInFocus;
	int State;
	int SkipPolice;
	class Player *pPlayer1;
	bool pSkipPolice;
	int MaxIdx;


	Game();
	~Game();
	void* InitPlayerOrTimer();

};

#endif // !__GAME__H



