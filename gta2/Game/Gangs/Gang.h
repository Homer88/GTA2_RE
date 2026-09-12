
#ifndef __GANG_H_
#define __GANG_H_





class  Gang{
public: 
	
  bool  Status;
  int CurrentGang;
  char NameGang[10];
  char remap;
  char pad;
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
	
  class Weapon *Weapon3;
  class Weapon *Weapon2;
  class Weapon *Weapon1;
};

#endif