#ifndef __PED__H__
#define __PED__H__

#include <assert.h>
#include <stdio.h>

#include "cS200.h"
#include "cCar.h"
#include "cGameObject.h"
#include "cPlayer.h"
#include "cWeapon.h"


enum OCUPATION :unsigned char {
	OCCUPATION_PLAYER = 0u,
	OCCUPATION_EMPTY = 1u,
	OCCUPATION_2 = 2u,
	OCCUPATION_DUMMY = 3u,
	OCCUPATION_4 = 4u,
	OCCUPATION_DRIVER = 5u,
	OCCUPATION_PSYCHO = 14u,
	OCCUPATION_MUGGER = 15u,
	OCCUPATION_CARTHIEF = 16u,
	OCCUPATION_BANK_ROBBER = 17u,
	OCCUPATION_CRIMINAL = 18u,
	OCCUPATION_ELVIS = 22u,
	OCCUPATION_POLICE = 24u,
	OCCUPATION_SWAT = 25u,
	OCCUPATION_FBI = 26u,
	OCCUPATION_ARMY = 27u,
	OCCUPATION_GUARD = 28u,
	OCCUPATION_GUARD_AGAINST_PLAYER = 32u,
	OCCUPATION_CRIMINAL_TYPE1 = 33u,
	OCCUPATION_CRIMINAL_TYPE2 = 34u,
	OCCUPATION_SPECIAL_GROUP_MEMBER = 35u,
	OCCUPATION_TANK_DRIVER = 36u,
	OCCUPATION_37 = 37u,
	OCCUPATION_FIREMAN = 38u,
	OCCUPATION_ROAD_BLOCK_TANK_MAN = 39u,
	OCCUPATION_DRONE = 41u,
	OCCUPATION_42 = 42u,
	OCCUPATION_STAND_STILL_BLOKE = 43u,
	OCCUPATION_ELVIS_LEADER = 44u,
	OCCUPATION_REFUGEES = 45u,
	OCCUPATION_ANY_LAW_ENFORCEMENT = 46u,
	OCCUPATION_ANY_EMERGENCY_SERVICE_MAN = 47u,
	OCCUPATION_ANY_GANG_MEMBER = 48u,
	OCCUPATION_ANY_ELVIS = 49u,
	OCCUPATION_50 = 50u,
	OCCUPATION_NONE = 51u

};

enum PedActions :unsigned int {
	ACTION_ENTERING_CAR = 1u,
	ACTION_EXITING_CAR = 59u
};

enum PedState : unsigned int {
	PEDSTATE_MOVE_TURN = 0u,
	PEDSTATE_ENTER_CAR = 3u,
	PEDSTATE_EXIT_CAR = 4u,
	PEDSTATE_IDLE = 7u,
	PEDSTATE_FALL = 8u,
	PEDSTATE_DEAD = 9u,
	PEDSTATE_IN_CAR = 10u
};

enum Remap :unsigned char {
	REMAP_COP = 0u,
	REMAP_GREEN_COP = 1u,
	REMAP_RED_COP = 2u,
	REMAP_YELLOW_COP = 3u,
	REMAP_ARMY = 4u,
	REMAP_REDNECK_1 = 5u,
	REMAP_REDNECK_2 = 6u,
	REMAP_SCIENTIST = 7u,
	REMAP_ZAIBATSU = 8u,
	REMAP_KRISHNA = 9u,
	REMAP_RUSSIAN = 10u,
	REMAP_LOONIE = 11u,
	REMAP_ELVIS = 12u,
	REMAP_YAKUZA = 13u,
	REMAP_FIRE_FIGHTER = 14u,
	REMAP_CAR_JACKER = 15u,
	REMAP_MEDIC = 16u,
	REMAP_PICKPOCKET = 17u,
	REMAP_BLUE_PEDESTRIAN = 18u,
	REMAP_LIGHT_BLUE_PEDESTRIAN = 19u,
	REMAP_RED_PEDESTRIAN = 20u,
	REMAP_PEDESTRIAN = 21u,
	REMAP_PRISONER = 22u,
	REMAP_HULK = 23u,
	REMAP_HULK_GREEN = 24u,
	REMAP_PLAYER = 25u,
	REMAP_NAKED_PEDESTRIAN = 26u,
};
enum FlagPed : unsigned char {

};
struct Ped {
	S200 structS200[49];
	unsigned int Counter;
	unsigned char uns0[145];
	unsigned short uns1;
	unsigned short uns2;
	unsigned short uns3;
	unsigned short uns4;
	unsigned short uns5;
	char uns6;
	char uns7;
	int uns8;
	int uns9;
	int uns10;
	Ped *structPed;
	Ped *structPed1;
	Ped *LinkerPed;
	Car *structCar;
	Car *ObjectiveTargetCar;
	Car* TargetCarForEnter;
	Player* CurentPlayer;
	struct Ped* NextPed;
	int *Class4;
	GameObject* CurrentGameObject;
	Car* CarCurrent; //0x16c
	struct Weapon* SelectWeapon;
	struct Weapon* Weapon1;
	struct Weapon* Weapon2;
	void* uns13;
	Ped* PedDriver;
	void* uns15;
	void* uns16;
	void* uns17;
	void* uns18;
	void* uns19;
	Ped* Ped3;
	void* uns20;
	void* uns21;
	void* uns22;
	void* uns23;
	int	PositionX;
	int	PositionY;
	int	PositionZ;
	Ped* Ped4;
	void* uns30;
	void* uns31;
	void* uns32;
	void* uns33;
	void* uns34;
	void* uns35;
	void* uns36;
	void* SpriteS1;
	Car* Car1;
	Car* Car2;
	void* uns40;
	void* uns41;
	void* uns42;
	void* uns43;
	void* uns44;
	void* uns45;
	void* uns46;
	int ID;
	int PedID;
	short uns49;
	short PoliceStar;
	short uns50;
	short uns51;
	short uns52;
	short uns53;
	short uns54;
	short Health;//  здоровье
	short uns56;
	short uns57;
	FlagPed  FlagPed;
	char  uns59;
	char  uns60;
	char  uns61;
	void* uns62;
	unsigned char usn63;
	unsigned char CarDamageState;
	//0x226
	unsigned char ExitAnimState;
	char uns66;
	char uns67;
	char uns68;
	char uns69;
	char uns70;
	//0x22c
	void* uns71;
	// 0x230
	void* uns72;

	char uns73;
	char uns74;
	char uns75;
	char uns76;
	void* SearchType;
	unsigned char IndexPed;
	char uns79;
	char uns80;
	char uns81;
	OCUPATION Occupation;
	Remap RemapEnum;
	//0x245
	char uns84;
	char uns85;
	char uns86;
	int TargetCarDoor;
	unsigned char Index;
	char uns90;
	char uns91;
	char uns92;
	void* uns93;
	void* uns94;
	int State;
	int CurrentAction;
	char uns100;
	char uns101;
	char uns102;
	char uns103;
	char uns104;
	char uns105;
	char uns106;
	char uns107;
	char uns108;
	char uns109;
	char uns110;
	char uns111;
	//0x26c
	void* GraphicType;
	//0x270
	void* uns270;
	//0x274
	void* GangCarModel;
	//0x278
	PedState CurrentState;
	//0x27C
	void* field_0x27C;
	//0x280
	PedState SavedState;
	//0x284
	void* field_0x284;
	//0x288
	void* field_0x288;
	//0x28C
	void* field_0x28C;
	//0x290
	void* field_0x290;
};
static_assert (sizeof(Ped) == 660, "SIZE PED ERROR"); // размер Ped

static struct Ped* gPed;









#endif
