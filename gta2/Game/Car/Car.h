#ifndef ___CAR__H__
#define ___CAR__H__




#include "..\global.h"

class Ped;
class SpriteS1;



enum  DamageType
{
  DAMAGE_NONE = 0u,
  DAMAGE_BY_VEHICLE = 1u,
  DAMAGE_BY_TRAIN_TRACKS = 2u,
  DAMAGE_BY_OWN_VEHICLE = 3u,
  DAMAGE_BY_EXPLOSION = 4u,
  DAMAGE_BY_DROWNING = 5u,
  DAMAGE_BY_POLICE = 6u,
  DAMAGE_BY_DUMMY_CAR = 7u,
  DAMAGE_BY_PUBLIC_TRANSPORT = 8u,
  DAMAGE_BY_UNKNOWN_WEAPON = 9u,
  DAMAGE_BY_PUNCH = 10u,
  DAMAGE_BY_GUN = 11u,
  DAMAGE_BY_CAR_BOMB = 12u,
  DAMAGE_BY_FIRE = 13u,
  DAMAGE_BY_FLAMETHROWER = 14u,
  DAMAGE_BY_GRENADE = 15u,
  DAMAGE_BY_MOLOTOV = 16u,
  DAMAGE_BY_ROCKET_LAUNCHER = 17u,
  DAMAGE_BY_ELECTRO_WEAPON = 18u,
  DAMAGE_BY_SHOTGUN = 19u,
  DAMAGE_BY_WATER_CANNON = 20u,
  DAMAGE_BY_CAR_MINE = 21u,
  DAMAGE_BY_ANY_FOOT_WEAPON = 22u,
  DAMAGE_BY_ANY_WEAPON = 23u,
};


class Car {
public:
    //Turrel *Turrel;
   /// Passenger *Passenger;
    //CAR_LIGHTS_AND_DOORS_BITSTATE carLights;
   // CarDoor CarDoor[4];
    Car* LastCar;
    SpriteS1 *SpriteS1;
    Ped *Driver;
    //Player *Physics;
    //EngineStruct* EngineStruct;
    //Model *Model;
    int TrailerCtrl;
    int field_68;
    int ID;
    Ped *lastDamagingPed;                 /// наносит урон
    short Damage;
    __int16 field_76;
    __int16 PhysicsBitmask;
    char field_7A;
    char field_7B;
    int field_7C;
    char field_80;
    char field_81;
    char field_82;
    char field_83;
    int  CarType;
    int Mask;
    char FireState;
    char field_8D;
    char AlarmTime;
    char field_8F;
    DamageType DamageType;
    char DamageShotTimer;
    char PlayerId;
    char field_96;
    char field_97;
    int locksDoor;
    //CAR_ENGINE_STATE engineState;
    //TRAFFIC_CAR_TYPE trafficCarType;
    char sirenState;
    char sirenPhase;
    char field_A6;
    char horn;
    char field_A8;
    char FireTimer;
    char field_AA;
    char field_AB;
    char field_AC;
    char field_AD;
    char field_AE;
    char field_AF;
    int field_B0;
    int  currentUpgradeSound;
    bool isTurretBeingRotated;
    char field_B8;
    char field_B9;
    char field_BA;
    char field_0;


    // конструктор 
    Car();
    ~Car();

    void AddRoofAntenna();
    void AddRoofGun();
    void AddRoofTankTurret();
    void AddRoofWaterGun();
    short CollisionOnCar(int Damage);
    bool GetFullDamage();
    void ExplodeCar(int a);
    void sub_4BF000();
    void sub_421460();
    void sub_424620();
    int sub_424630(void*);
    void sub_420840(void*);
    void* sub_41F730(int param);
    bool IsDriverPlayer();
    bool isAPC();
    bool isFileTruck();
    bool isJeep();
    bool isGunJeep();
    bool isCopCar();
    bool isMask7();
    bool isMedicCar();
    bool isSWATVAN();
    bool isTaxi();
    bool isTank();
    bool isEDSELFBI();
    bool isGT24640();
    bool isTVVAN();
    bool IsTrainOrTrainCarriage();
    void SetPosition(int X, int Y, int Z);
    char UpdateDamageCooldown();
    void SetMask();
    void SetHornDefault();
    class Player* GetPlayer();
    int  GetCarModel();
    void SetSound(int a2);
    char HandleMaskTransition();
    void isMask4();
    void isMask3();
    bool isMask();
    void* GetInfoByTypeCar();

};

#endif // !___CAR__H__








