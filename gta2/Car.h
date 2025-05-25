#ifndef __CAR_H
#define __CAR_H

enum CarModel
{
  ALFA = 0,
  ALLARD = 1,
  AMDB4 = 2,
  APC = 3,
  BANKVAN = 4,
  BMW = 5,
  BOXCAR = 6,
  BOXTRUCK = 7,
  BUG = 8,
  Car10 = 9,
  BUICK = 10,
  BUS = 11,
  COPCAR = 12,
  DART = 13,
  EDSEL = 14,
  Car16 = 15,
  FIAT = 16,
  FireTruck = 17,
  GRAHAM = 18,
  GT24640 = 19,
  Car21 = 20,
  GTRUCK = 21,
  GunJeep = 22,
  HOTDOG = 23,
  HOTDOG_D1 = 24,
  HOTDOG_D2 = 25,
  HOTDOG_D3 = 26,
  ICECREAM = 27,
  ISETLIMO = 28,
  ISETTA = 29,
  JEEP = 30,
  JEFFREY = 31,
  LIMO = 32,
  LIMO2 = 33,
  MEDICAR = 34,
  MERC = 35,
  MESSER = 36,
  MIURA = 37,
  MONSTER = 38,
  MORGAN = 39,
  MORRIS = 40,
  PICKUP = 41,
  RTYPE = 42,
  SPIDER = 44,
  SPRITE = 45,
  STINGRAY = 46,
  STRATOS = 47,
  STRATOSB = 48,
  STRIPETB = 49,
  STYPE = 50,
  STYPECAB = 51,
  SWATVAN = 52,
  T2000GT = 53,
  Tank = 54,
  TANKER = 55,
  Taxi = 56,
  TBIRD = 57,
  TOWTRUCK = 58,
  TRAIN = 59,
  TRAINCAB = 60,
  TRAINFB = 61,
  TRANCEAM = 62,
  TRUKCAB1 = 63,
  TRUKCAB2 = 64,
  TRUKCONT = 65,
  TRUKTRNS = 66,
  TVVAN = 67,
  VAN = 68,
  VESPA = 69,
  VTYPE = 70,
  WBTWIN = 71,
  WRECK0 = 72,
  WRECK1 = 73,
  WRECK2 = 74,
  WRECK3 = 75,
  WRECK4 = 76,
  WRECK5 = 77,
  WRECK6 = 78,
  WRECK7 = 79,
  WRECK8 = 80,
  WRECK9 = 81,
  XK120 = 82,
  ZCX5 = 83,
  EDSELFBI = 84,
  HOTDOG_D4 = 85,
  KRSNABUS = 86,
  MODEL_NUM_CAR_MODELS = 87,
};

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


class Car{
   public:
        Turrel *Turrel;
        Passenger *Passenger;
        CAR_LIGHTS_AND_DOORS_BITSTATE carLights;
        CarDoor CarDoor[4];
        Car *LastCar;
        SpriteS1 *SpriteS1;
        Ped *Driver;
        Player *Physics;
        EngineStruct* EngineStruct;
        Model *Model;
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
        CarModel CarType;
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
        CAR_ENGINE_STATE engineState;
        TRAFFIC_CAR_TYPE trafficCarType;
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
        byte currentUpgradeSound;
        bool isTurretBeingRotated;
        __declspec(align(4)) char field_B8;
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
        int sub_424630(void *);
        void sub_420840(void *);
        void* sub_41F730(int param);
        bool IsDriverPlayer();
        bool isFileTruck();
        bool isGunJeep();
        bool isTank();
        bool IsTrainOrTrainCarriage();
        void SetPosition(int X, int Y, int Z);
        char UpdateDamageCooldown();
        






};











#endif