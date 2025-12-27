#ifndef __GANG_H_
#define __GANG_H_

#include "Car.h"
#include "Weapon.h"




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
  char WarMaskGang[10];
  int X;
  int Y;
  int Z;
  int NextGang;
  bool Visible;
  char field_13A;
  char field_13B;
  int  CarType;
  char CarRemap;
	Gang();
	~Gang();
	
};






#endif