#ifndef ___CAR___H_
#define ___CAR___H_

#include <assert.h>

// Car struct (IDA gta2.exe.h:3279). Size 0x132 (306 bytes), verified:
// active cars pool = operator_new(0xD264); Construct(CGameEntity, 176, 306, ...)
// => 176 cars x 0x132.
// Missing tail beyond IDA fields (0xBC..0x131) is kept as raw gap array.

struct Ped;
struct Player;
struct Car;
struct Passenger;
struct PlayerStats;
struct CarDoor;
struct SpriteS1;
struct EngineStruct;
struct Model;

enum CarModel : unsigned char {
    ALFA = 0,
    ALLARD = 1,
    AMDB4 = 2,
    APC = 3,
    BANKVAN = 4,
    BMW = 5,
    BOXCAR = 6,
    BOXTRUCK = 7,
    BUG = 8,
    CAR9 = 9,
    BUICK = 10,
    BUS = 11,
    COPCAR = 12,
    DART = 13,
    EDSEL = 14,
    FIAT = 16,
    FIRETRUK = 17,
    GRAHAM = 18,
    GT24640 = 19,
    GTRUCK = 21,
    GUNJEEP = 22,
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
    TANK = 54,
    TANKER = 55,
    TAXI = 56,
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

struct CarDoor_St {
    unsigned char AnimationFrame[4];
    int doorState;
    Ped* PedInDoor;
    unsigned char field_C;
    char rezerv_1;
    char rezerv_2;
    char Rezerv_3;
};
static_assert(sizeof(CarDoor_St) == 0x10, "CarDoor size");

struct Car {
#pragma pack(push, 1)
    void* pCar;                      // +0x00 Car* Car
    Passenger* Passenger;
    PlayerStats* PlayerStats;
    CarDoor_St CarDoor[4];
    Car* LastCar;
    SpriteS1* CarSprite;
    Ped* Driver;
    Player* Player;
    EngineStruct* EngineStruct;
    Model* Model;
    void* TrailerCtrl;
    int field_68;
    int ID;
    Ped* lastDamagingPed;
    short Damage;
    short field_76;
    short PhysicsBitmask;
    char field_7A;
    char field_7B;
    int SearchType;
    char field_80;
    char field_81;
    char field_82;
    char field_83;
    int CarType;              // 0x84 (CarModel enum, int32)
    int Mask;
    char FireState;
    char field_8D;
    char AlarmTime;
    char field_8F;
    int DamageType;
    char DamageShotTimer;
    char PlayerId;
    char field_96;
    char field_97;
    int locksDoor;
    int engineState;
    int trafficCarType;
    char sirenState;
    char sirenPhase;
    char field_A6;
    char horn;
    char field_A8;
    char FireTimer;
    char field_AA;
    char field_AB;
    int field_AC;
    int field_B0;
    void* currentUpgradeSound;
    char field_B8;
    char field_B9;
    char field_BA;
    char gapBB;
    char gapBC[0x76]; // 0xBC..0x131 (tail beyond IDA, keeps total 0x132)
#pragma pack(pop)
};
static_assert(sizeof(Car) == 0x132, "Car size 0x132");

#endif