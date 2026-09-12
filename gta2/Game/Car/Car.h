
#ifndef ___CAR__H__
#define ___CAR__H__




#include <windows.h>

class Sprite;
class Ped;
class Player;



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
    Car  *LastCar;
    Sprite *SpriteCar;
    Ped *Driver;
    //Player *Physics;
    //EngineStruct* EngineStruct;
    //Model *Model;
    //Player *PlayerDiver;
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
    void DestroyAllTurrets();
    void sub_421460();
    void Reset();
    int SetTrafficCarType(void*);
    void ChangeTrafficType(void*);
    void* GetEngineData(int param);
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
    void Repair() {};
    Player* GetPlayer();
    //class Player* GetPlayer();
    int  GetCarModel();
    void SetSound(int a2);
    char HandleMaskTransition();
    void isMask4();
    void isMask3();
    bool isMask();
    void* GetInfoByTypeCar();
    // 0x00411950
    // (gm) old: Car::ClearTurretMuzzle -> Car::ConsumePendingEvent0xac
    void ConsumePendingEvent0xac();
    // 0x004119C0
    // (gm) old: Car::IsField9cFour -> Car::IsCarState4
    int IsCarState4();
    // 0x004119D0
    // (gm) old: Car::ClearExitedPassenger -> Car::ConsumePendingEvent0xb4
    void ConsumePendingEvent0xb4();
    // 0x0041E460
    // (gm) old: Car::IsPartOfCarChain -> Car::IsObjectAttached
    int IsObjectAttached();
    // 0x0041E480
    // (gm) old: Car::IsSpritePartOfCar -> Car::IsMySprite
    int IsMySprite();
    // 0x0041F980
    // (gm) old: EncodePositionValue (kept; fp <<14)
    void EncodePositionValue(int param_1);
    // 0x0041F990
    // (gm) old: EncodeCoord16 (kept; fp short <<14)
    void EncodeCoord16(unsigned int param_1);
    // 0x0041FC70
    // (gm) old: GetCarPosition -> Car::GetCarSpritePtr (returns car sprite)
    int GetCarSpritePtr();
    // 0x0049E3A0
    // (gm) old: Player::SetInfiniteAmmo -> Car::ScaleTurretAndPassengers (fp scale)
    void ScaleTurretAndPassengers(int* param_1);
    // 0x0049EFD0
    // (gm) old: Player::GetWeaponType2 / SetFlag -> Car::ClearFlag2000 (clears 0x2000)
    void ClearFlag2000();




// ==== импорт имён из gm ====
    // 68 функций
    // 0x00411820: Car::GetField0x60
    void GetField0x60();
    // 0x00411830: Car::GetEventFlag
    void GetEventFlag();
    // 0x00411840: Car::GetField0x84
    void GetField0x84();
    // 0x00411850: Car::GetField0x88
    void GetField0x88();
    // 0x00411870: Car::IsIdleStopped
    void IsIdleStopped();
    // 0x004119B0: Car::HasAttachmentAt0x84
    void HasAttachmentAt0x84();
    // 0x00411A20: Car::GetField0x24
    void GetField0x24();
    // 0x00411A30: Car::GetField0x28
    void GetField0x28();
    // 0x00421130: Car::IsTimerElapsed
    void IsTimerElapsed();
    // 0x00421150: Car::GetVelocity
    void GetVelocity();
    // 0x00421190: Car::SetField74
    void SetField74();
    // 0x004211E0: Car::GetSpeedPair
    void GetSpeedPair();
    // 0x00421200: Car::ClearFieldAD
    void ClearFieldAD();
    // 0x00421210: Car::SetHazardLights
    void SetHazardLights();
    // 0x00421230: Car::SetIndicatorLeft
    void SetIndicatorLeft();
    // 0x00421250: Car::SetIndicatorRight
    void SetIndicatorRight();
    // 0x00421530: Car::SetFieldA6
    void SetFieldA6();
    // 0x00421B90: Car::GetEngineSoundValue
    void GetEngineSoundValue();
    // 0x00421C00: Car::GetScreenPosition
    void GetScreenPosition();
    // 0x00421CB0: Car::GetCarName
    void GetCarName();
    // 0x00421CF0: Car::GetScreenPositionOffset
    void GetScreenPositionOffset();
    // 0x00421E00: Car::GetDisplayValue
    void GetDisplayValue();
    // 0x00421EF0: Car::GetRemapColor
    void GetRemapColor();
    // 0x00422020: Car::RandomRemap
    void RandomRemap();
    // 0x004221A0: Car::IndicatorLeftOn
    void IndicatorLeftOn();
    // 0x004221B0: Car::IndicatorRightOn
    void IndicatorRightOn();
    // 0x004224A0: Car::CheckLineOfSight
    void CheckLineOfSight();
    // 0x00423180: Car::ApplySteeringInput
    void ApplySteeringInput();
    // 0x00423C30: Car::UpdateCarLights
    void UpdateCarLights();
    // 0x00424660: Car::AddDrivenCar
    void AddDrivenCar();
    // 0x00424680: Car::AddTrafficCar
    void AddTrafficCar();
    // 0x00424E30: Car::CanPedEnterCar
    void CanPedEnterCar();
    // 0x00424F80: Car::ShouldRemoveCar
    void ShouldRemoveCar();
    // 0x00425790: Car::GetEngineState
    void GetEngineState();
    // 0x00425D60: Car::CanBeDrivenByPed
    void CanBeDrivenByPed();
    // 0x0042AB90: Car::SetBrakingOn
    void SetBrakingOn();
    // 0x0042ABA0: Car::SetBrakingOff
    void SetBrakingOff();
    // 0x0042ABB0: Car::ResetInput
    void ResetInput();
    // 0x0042ABC0: Car::SetStateOne
    void SetStateOne();
    // 0x0042ABE0: Car::SetStateTwo
    void SetStateTwo();
    // 0x0042AC00: Car::ClearStateFlags
    void ClearStateFlags();
    // 0x0042AC20: Car::IsFlag1
    void IsFlag1();
    // 0x0042AC30: Car::IsFlag2
    void IsFlag2();
    // 0x0042AC40: Car::IsFlag4
    void IsFlag4();
    // 0x0042AC50: Car::IsFlag8
    void IsFlag8();
    // 0x0042AC60: Car::IsFlag32
    void IsFlag32();
    // 0x0042AC70: Car::SetFlag1
    void SetFlag1();
    // 0x0042AC80: Car::SetFlag2
    void SetFlag2();
    // 0x0042AC90: Car::SetFlag4
    void SetFlag4();
    // 0x0042ACA0: Car::ClearFlag1
    void ClearFlag1();
    // 0x0042ACB0: Car::ClearFlagBit1
    void ClearFlagBit1();
    // 0x0042ACC0: Car::ClearFlag4
    void ClearFlag4();
    // 0x0042ACD0: Car::ClearFlag8
    void ClearFlag8();
    // 0x0042ADA0: Car::DecideTurnDirection
    void DecideTurnDirection();
    // 0x0042B8A0: Car::UpdateTrafficControl
    void UpdateTrafficControl();
    // 0x00447E90: Car::SetAlarmTimer
    void SetAlarmTimer();
    // 0x00447F00: Car::IsValidParkingVehicle
    void IsValidParkingVehicle();
    // 0x00475AA0: Car::IsSpecialModel
    void IsSpecialModel();
    // 0x00475C60: Car::SetLocksDoor5
    void SetLocksDoor5();
    // 0x004762C0: Car::SetFlag80
    void SetFlag80();
    // 0x004762D0: Car::SetFlag200
    void SetFlag200();
    // 0x004762F0: Car::ClearFlag100
    void ClearFlag100();
    // 0x00476300: Car::ClearFlag200
    void ClearFlag200();
    // 0x00476310: Car::ClearFlag400
    void ClearFlag400();
    // 0x004A51B0: Car::SetLightMode
    void SetLightMode();
    // 0x004B3150: Car::CheckDoorEntry
    void CheckDoorEntry();
    // 0x004BEB30: Car::GetTurretWeaponIndex
    void GetTurretWeaponIndex();
    // 0x004C4BF0: Car::AddTurret
    void AddTurret();



















    // 0x00411860
    // (gm) ������: Car::GetField9c -> Car::GetField0x9c
    int GetField0x9c();
    // 0x00411A10
    // (gm) ������: Car::GetCarModelPointer -> Car::GetSpawnPoint
    int GetSpawnPoint();
    // 0x0041F770
    // (gm) ������: Car::GetEnginePower -> Car::GetCarValue
    int GetCarValue(int arg0);
    // 0x0041F830
    // (gm) ������: Car::IsDriverTargetInView -> Car::HasDriver
    int HasDriver(int arg0);
    // 0x0041F8A0
    // (gm) ������: Car::UpdateAllDoors -> Car::UpdateDoors
    void UpdateDoors();
    // 0x0041FBD0
    // (gm) ������: Car::SpawnAndDestroyObject -> Car::SpawnAttachedObject
    void SpawnAttachedObject(int arg1);
    // 0x00420920
    // (gm) ������: Car::TurrelUpdateSprites -> Car::DeactivateTrafficCar
    void DeactivateTrafficCar();
    // 0x004213B0
    // (gm) ������: Car::GetTurrel2 -> Car::HornOff
    void HornOff(int arg0);
    // 0x004222A0
    // (gm) ������: Car::GetCarFlag8 -> Car::CheckPlayerDriveable
    int CheckPlayerDriveable(int arg0);
    // 0x004228C0
    // (gm) ������: Car::GetCarFlag -> Car::SirenOn
    void SirenOn();
    // 0x00422920
    // (gm) ������: Car::GetCarFlag2 -> Car::SirenPhase1
    void SirenPhase1(int arg0);
    // 0x004229E0
    // (gm) ������: Car::GetCarFlag3 -> Car::SirenPhase2
    void SirenPhase2(int arg0);
    // 0x00422AA0
    // (gm) ������: Car::GetCarFlag4 -> Car::SirenPhase3
    void SirenPhase3(int arg0);
    // 0x00422BD0
    // (gm) ������: Car::GetCarFlag5 -> Car::SirenPhase4
    void SirenPhase4(int arg0);
    // 0x00423850
    // (gm) ������: Car::GetCarFlag6 -> Car::UpdateSiren
    void UpdateSiren();
    // 0x00423B80
    // (gm) ������: Car::GetCarFlag8b -> Car::UpdateSirenPhase
    void UpdateSirenPhase(int arg0);
    // 0x00423E30
    // (gm) ������: Car::GetCarFlag7 -> Car::UpdateSecondaryLights
    void UpdateSecondaryLights(int arg0);
    // 0x0042B350
    // (gm) ������: Car_ResolveStuck -> Car::FollowPath
    void FollowPath(int arg0);
    // 0x0042C8B0
    // (gm) ������: Car_ParkCar -> Car::UpdateAI
    void UpdateAI();
};
#endif // !___CAR__H__




