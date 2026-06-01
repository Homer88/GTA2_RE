#include "Gang.h"

enum GANG {
	Yakuza = 0u,
	Zaibatsu_Corporation = 1u,
	Loonies = 2u,
	GANG_3 = 3u,
	GANG_4 = 4u,
	GANG_5 = 5u,
	GANG_6 = 6u,
	GANG_7 = 7u,
	GANG_8 = 8u,
	GANG_9 = 9u,
	GANG_10 = 10u,
};

Gang::Gang() {
	this->Status=false;
	this->CurrentGang = Yakuza;
	this->remap = 1;



}

Gang::~Gang() {

}