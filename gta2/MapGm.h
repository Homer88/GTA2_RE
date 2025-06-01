#ifndef ___MAPGM_H_
#define ___MAPGM_H_


class MapGm{
public:
	
	char gmpFile[256];
	char styFile[256];
	char sctiptFile[256];
	char SaveFile[256];
	char playerArena;
	char bonusStage;
	char field_0x402;
	unsigned char  PlayerSlotSave;
	char field_404;
	char field_405;
	char field_406;
	char field_407;
	int Arr10i[10];
	int field_430;
	int field_434;
	short field_438;
	unsigned char field_43A;
	unsigned char  field_43B;
	short FragLimit;
	char field_43E;
	char field_43F;
	char field_440;
	char field_441;
	char field_442;
	char field_443;
	char field_444;
	char field_445;
	char field_446;
	char field_447;
	char field_448;
	char field_449;
	char field_44A;
	char field_44B;
	char field_44C;
	char field_44D;
	char field_44E;
	char field_44F;
	char field_450;
	char field_451;
	char field_452;
	char field_453;
	char field_454;
	char field_455;
	char field_456;
	char field_457;
	char field_458;
	char field_459;
	char field_45A;
	char field_45B;
	char field_45C;
	char field_45D;
	char field_45E;
	char field_45F;
	char field_460;
	char field_461;
	char field_462;
	char field_463;
	char field_464;
	char field_465;
	char field_466;
	char field_467;
	char field_468;
	char field_469;
	char field_46A;
	char field_46B;
	char field_46C;
	char field_46D;
	char field_46E;
	char field_46F;
	char field_470;
	char field_471;
	char field_472;
	char field_473;
	char field_474;
	char field_475;
	char field_476;
	char field_477;
	char field_478;
	char field_479;
	char field_47A;
	char field_47B;
	char field_47C;
	char field_47D;
	char field_47E;
	char field_47F;
	char field_480;
	char field_481;
	char field_482;
	char field_483;
	char field_484;
	char field_485;
	char field_486;
	char field_487;
	char field_488;
	char field_489;
	char field_48A;
	char field_48B;
	char field_48C;
	char field_48D;
	char field_48E;
	char field_48F;
	char field_490;
	char field_491;
	char field_492;
	char field_493;
	char field_494;
	char field_495;
	char field_496;
	char field_497;
	char field_498;
	char field_499;
	char field_49A;
	char field_49B;
	char field_49C;
	char field_49D;
	char field_49E;
	char field_49F;
	char field_4A0;
	char field_4A1;
	char field_4A2;
	char field_4A3;
	char field_4A4;
	char field_4A5;
	char field_4A6;
	char field_4A7;
	char field_4A8;
	char field_4A9;
	char field_4AA;
	char field_4AB;
	char field_4AC;
	char field_4AD;
	char field_4AE;
	char field_4AF;
	char field_4B0;
	char field_4B1;
	char field_4B2;
	char field_4B3;
	char field_4B4;
	char field_4B5;
	char field_4B6;
	char field_4B7;
	char field_4B8;
	char gap4B9[183];
	char field_570;
	char field_571;
	char field_572;
	char field_573;
	int field_574;
	int field_578;
	
	//MapGm();
	//~MapGm();
	
	int LoadFileResurce();
	char* GetMapName();
	void SetMapName(char* NameFile);
	char* GetStyleName();
	void SetStyleName(char* NameFile);
	char* GetScriptName();
	void SetScriptName(char* NameFile);
	char* GetSaveFile();
	void SetSaveFile(char* NameFile);
	void SetPlayerArena(int PlayerArena);
	void SetBonusStage(int BonusStage);
	void Set_FUN_0045E4B0(int Param);
	void SetPlayerSlotSave(int PlayerSlot);
	void Set_FUN_0045E4D0(int Param);
	void Set_FUN_0045E630();
	
	
	
	
	
	
	
	};

#endif
