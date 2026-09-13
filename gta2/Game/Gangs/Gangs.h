
//Structure S117 0x005EB898
#ifndef __GANGS_H_
#define __GANGS_H_
#include "../Gang/Gang.h"

class  Gangs{
public: 

	bool Status;
	Gang ArrayGang[10];
	//class Gang *pGang;

	Gangs();
	~Gangs();
	Gang* GetNextGang();
	Gang* GetFirstUsedGang();
		  
};






#endif