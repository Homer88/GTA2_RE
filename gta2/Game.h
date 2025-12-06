#ifndef __GAME__H_
#define __GAME__H_

#include "Player.h"
class Player;



class Game {
private:

public:
	bool Status;
	//GameStatus *Status;
	 Player  *pPlayer[6];
	 Player *CurentPlayer;
	 char CurentPlayer__;
	 byte ID;
	
	BYTE NumPlayers;
	char PlayerInFocus;
	int State;
	int SkipPolice;
	Player *pPlayer1;
	bool pSkipPolice;
	int MaxIdx;


	Game();
	~Game();
	void* InitPlayerOrTimer();

};

#endif // !__GAME__H



