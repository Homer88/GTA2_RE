#ifndef __GANG_H_
#define __GANG_H_

#include "Car.h"


enum GANG{
			Yakuza               = 0u,
			Zaibatsu_Corporation = 1u,
			Loonies              = 2u,
			GANG_3               = 3u,
			GANG_4               = 4u,
			GANG_5               = 5u,
			GANG_6               = 6u,
			GANG_7               = 7u,
			GANG_8               = 8u,
			GANG_9               = 9u,
			GANG_10              = 10u,
};


class  Gang{
public: 
	
  bool  Status;
  int CurrentGang;
  char NameGang[10];
  char remap;
  char pad;
  class Weapon *Weapon1;
  class Weapon *Weapon2;
  class Weapon *Weapon3;
  bool MaxOut;
  char Reting;
  int Prestige;
  unsigned short field_120;
  char WarMaskGang[10];
  int X;
  int Y;
  int Z;
  GANG NextGang;
  bool Visible;
  char field_13A;
  char field_13B;
  int  CarType;
  char CarRemap;
  char field_141;
  char field_142;
  char field_0;
	Gang();
	~Gang();
	
};






#endif