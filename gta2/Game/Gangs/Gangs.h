
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

	// 0x0045DC70 IDA/BN Gangs::SetGang: return &Gang[Gang]. RE field-name impl; C++ indexing uses RE Gang stride.
	Gang* SetGang(GANG gang);
		  
};

extern Gangs* gGangs;




#endif