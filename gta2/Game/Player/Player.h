
#ifndef __PLAYER_CLASS_H_
#define __PLAYER_CLASS_H_
#include "../global.h" 


class Player{
	public:
		Player *CurrentPlayer;
		Player* NextPlayer;
		short CountPlayer;
		void* Forw;//  движение 
		VehiclePool* PoolVehicle;
		short SW;
		int TypeWeapon;
		short FW;
		short Armo;
		short WeaponNext;
		Car* CarPlayer;
		int  PlayerID;
		byte AllControlStatus;
		byte EnterControlStatus;
		Gang *Respect;
		int StatusFlag;
		int MoneyValue;
		int timeSecond;
		Car* CarPlayerPrev;
		int Revs;
		int ID, IDs;
		int Debug;
		int MultiPlayerMode;
		byte DeathReason;
		void* Sound;
		byte DoDebugKeys1;
		byte DoDebugKeys;
		bool Key_UP, Key_Down, Key_Right, Key_Left, Key_PrevWeapon, Key_NextWeapon, Key_DebugKey1, Key_DebugKey2, Forward, Backward,
				RotateLeft, RotateRight, Enter, Jump, NextWeaponZ, PrevWeaponX, KeySpecial, KeySpecial2, AttackIsChanged;
		byte NextPlayerId;
		CameraOrPhysics* Camera;
		AudioManager* audioManager;
		CameraOrPhysics* Camera1, Camera2;
		int Camera_X_View, Camera_Y_View, Camera_Z_View;
		int AuxGameCameraX, AuxGameCameraY, AuxGameCameraZ;
		Ped *MainPed;
		Ped *PassengerTransport;
		Car* CarPrev2;
		short Damage,Reload, Electrofinger, Invisibility;
		//int Money,  Lives,  MultiPlayer;
		PlayerSlotSlave *Money, *Lives,*MultiPlayer; //  нужна реализация 
		PowerUP PowerType[18];
		Weapon  WeaponArray[28];
		short SelectWeapon;
		bool quit1;
		Ped  *PedNext;
		bool NetworkPlayer=false;
		//wchar_t  PlaerName[8];  неизвестное 

		int State;
		byte Gan;
		Player();
		~Player();
		byte GivePowerUp(int PowerType);
		void SetMultiPlayer(byte Multi);
		int  AddLives(int Lives);
		void StartGame();

		
};	

#endif