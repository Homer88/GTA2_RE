
//реализация классов с машинами
#include "../Player/Player.h"
#include "../Ped/Ped.h" 
#include "../Hud/Hud.h"

#include "../../Engine/Object/Object.h"
#include "../../Engine/Text/Text.h"
//#include "../../Engine/SpriteMain/SpriteMain.h"

#include "Car.h"
extern Text *gText;
extern Object *gObject;
Car gCar;
char gKeyBuffer[512];


Car::Car(){
    this->Mask = 0;
}

Car::~Car(){
this->LastCar=0;
//this->SpriteS1=0;
//this->EngineStruct=0;
}

void Car::DestroyAllTurrets(){

}

void Car::sub_421460(){

}
void Car::Reset(){

}


void Car::AddRoofAntenna(){

}


void Car::AddRoofGun(){
    int a,b,c;
    short d;
    gObject->SpawnObject(a,b,c,d);
    // еще функции

}

void Car::AddRoofTankTurret(){

}

void Car::AddRoofWaterGun(){

}

int Car::SetTrafficCarType(void *param1 ){
    return 0;
}

void Car::ChangeTrafficType(void *param1 ){

}

short Car::CollisionOnCar(int Damage){
    unsigned short _DamageCount;

    if (GetFullDamage())
        return 0;
    
    if (Damage==32000)
        ExplodeCar(19);

    return _DamageCount;
}

bool Car::GetFullDamage(){
    return this->Damage == 32001;
}

// 0x0040F890 IDA/BN Car::GetFullDamegeCar: *(+0x74)==0x7D01. RE uses Damage field by name.
bool Car::GetFullDamegeCar() {
    return this->Damage == 32001;
}

void * Car::GetEngineData(int pararm){
    return 0;//(void*)(gCarEngines.GetEngineValue(this->CarType)+44);


}

void Car::ExplodeCar(int a){

}


bool Car::IsDriverPlayer(){
    Ped *PedDriver;
    PedDriver=this->Driver;
    return PedDriver && PedDriver->isPlayer;

}

bool Car::isFileTruck(){
    return this->CarType == FireTruck;
}

// 0x00411910 IDA/BN: CarType==GunJeep(0x16). RE field-name impl (was JEEP, parity fix).
bool Car::isGunJeep(){
    return this->CarType == GunJeep;
}

bool Car::isTank(){
    
    return this->CarType == Tank;
}

// Проверяет, является ли транспорт рельсовым (поезд или вагон) 
bool Car::IsTrainOrTrainCarriage(){

    int     _CarType = this->CarType;
    return _CarType == TRAIN ||
           _CarType == TRAINCAB ||
           _CarType == TRAINFB  ||
           _CarType == BOXCAR;
}

// 0x00403BC0 IDA/BN Car::IsSpecialVehicle: CarType==SWATVAN(0x34) || CarType==BANKVAN(4). RE field-name impl.
bool Car::IsSpecialVehicle() {
    int ct = this->CarType;
    return ct == SWATVAN || ct == BANKVAN;
}
void Car::SetPosition(int X, int Y, int Z){

   // this->SpriteCar->SetPosition(X,Y,Z);

}

char  Car::UpdateDamageCooldown(){

    if (this->DamageShotTimer){
        this->DamageShotTimer--;
        if (!this->DamageShotTimer){
            this->lastDamagingPed=0; // Обнуление пешехода, связанного с уроном
            this->DamageType = DAMAGE_NONE; // Сброс типа урона
        }

    }
    return this->DamageShotTimer;
}

// 0x004215F0 IDA: if Mask==2||4||3 Mask=1. RE field-name impl (previous body was no-op).
void Car::SetMask() {
    int _Mask = this->Mask;
    if (_Mask == 2 || _Mask == 4 || _Mask == 3)
        this->Mask = 1;
}

// 0x00447EA0 IDA/BN Car::SetMask1: Mask=1. RE field-name impl.
void Car::SetMask1() {
    this->Mask = 1;
}

void Car::SetHornDefault() {

    this->horn = 0;
}

// 0x00411970 IDA/BN: horn>0 && (unsigned char)horn<=0xF8. RE field-name impl; horn field exists in RE Car.
bool Car::CarIsHornActive() {
    unsigned char h = (unsigned char)this->horn;
    return h > 0 && h <= 0xF8u;
}

// 0x00411990 IDA: if (horn<=0xF8) return horn else 0. RE field-name impl.
unsigned char Car::CarGetHornValue() {
    unsigned char h = (unsigned char)this->horn;
    return (h <= 0xF8u) ? h : 0;
}

// 0x00420330 IDA/BN: if (horn && horn!=0xF8) horn--. RE field-name impl.
void Car::DecrementHorn() {
    unsigned char h = (unsigned char)this->horn;
    if (h != 0 && h != 0xF8u) this->horn = (char)(h - 1);
}

// 0x004218F0 - guarded RE impl by field name. BN/IDA: return *(this+0x8D) & 1.
// RE Car has field_8D; offset in RE is different from IDA, but semantic name matches BN decompile.
char Car::GetCarFlag() {
    return (this->field_8D & 1);
}

// 0x004218E0 - guarded RE impl by field name. BN/IDA: *(this+0x8D) &= 0xFE.
void Car::ClearCarFlag() {
    this->field_8D &= (char)0xFE;
}

// 0x00421560 - guarded partial RE impl by field name. BN/IDA: *(this+0x76)=0; *(this+0x7C)=arg2.
// RE Car has field_76/field_7C; offsets differ from IDA, but names/types align with BN decompile.
void Car::MakeDriveable1(int arg2) {
    this->field_76 = 0;
    this->field_7C = arg2;
}

// 0x004A9AD0 IDA/BN Car::getBonusDamage: return field_76. RE field-name impl (RE offset differs from IDA).
short Car::getBonusDamage() {
    return this->field_76;
}
bool Car::isEDSELFBI() {

    return this->CarType == EDSELFBI;
}

int Car::GetCarModel() {

    return this->CarType;
}

// 0x00411940 IDA/BN Car::GetModelCar: return *(+0x84) CarType. RE field-name impl.
int Car::GetModelCar() {
    return this->CarType;
}

// 0x004118B0 IDA/BN Car::GetDriver: return *(+0x54). RE field-name impl.
Ped* Car::GetDriver() {
    return this->Driver;
}

bool Car::isCopCar() {
    
    int  _CarModel = this->CarType;

    return _CarModel == COPCAR
        || _CarModel == SWATVAN
        || _CarModel == EDSELFBI;
}

// 0x0041F6E0 IDA/BN Car::IsCopCar: COPCAR(0xC)||SWATVAN(0x34)||EDSELFBI(0x54). RE field-name impl.
bool Car::IsCopCar() {
    int ct = this->CarType;
    return ct == COPCAR || ct == SWATVAN || ct == EDSELFBI;
}

// 0x00421790 IDA/BN Car::isCopCar_00421790: CarType==COPCAR only. RE field-name impl.
bool Car::isCopCar_00421790() {
    return this->CarType == COPCAR;
}

bool Car::isMask7(){

    return this->Mask == 7;
}

// 0x004214D0 IDA/BN: return Mask==7. RE field-name impl.
bool Car::GetMask7() {
    return this->Mask == 7;
}

// 0x004214E0 IDA/BN: Mask=7. RE field-name impl.
void Car::SetMask7() {
    this->Mask = 7;
}

// 0x004215B0 IDA/BN: return Mask==5. RE field-name impl.
bool Car::IsMask5() {
    return this->Mask == 5;
}

// 0x004215C0 IDA: Driver && Driver->isPlayer && Ped::GetOccupation(Driver)!=EMPTY. RE field-name impl.
bool Car::IsPlayerOccupant() {
    Ped* driver = this->Driver;
    return driver && driver->isPlayer && driver->GetOccupation() != (int)EMPTY;
}


bool Car::isMedicCar(){

    return this->CarType == MEDICAR;
}

bool  Car::isSWATVAN(){
    return this->CarType == SWATVAN;
}


bool Car::isGT24640(){

    return this->CarType == GT24640;
}

// 0x004217D0 IDA/BN Car::GetGT24640: CarType==GT24640(0x13). RE field-name impl.
bool Car::GetGT24640() {
    return this->CarType == GT24640;
}

bool Car::isTVVAN(){

    return this->CarType == TVVAN;
}

// 0x00447EC0 IDA/BN Car::is_truck: CarType==TRUKTRNS. RE field-name impl.
bool Car::is_truck() {
    return this->CarType == TRUKTRNS;
}


// 0x00421870 IDA/BN Car::GetPlayer: return Driver->isPlayer. RE field-name impl.
Player* Car::GetPlayer(){
    if (!this->Driver) return NULL;
    return this->Driver->isPlayer;
}
void Car::SetSound( int a2)
{
    this->currentUpgradeSound = a2;
}

char Car::HandleMaskTransition()
{
    switch (this->Mask)
    {
    case 2:
       // if (!this->CheckDriver(this))
        ///    return 0;
        //goto LABEL_5;
    case 3:
    LABEL_5:
        this->Mask = 5;
        return 0;
    case 4:
        this->Mask = 2;
        return 0;
    case 5:
        this->Mask = 6;
        return 1;
    default:
        return 0;
    }
}


void  Car::isMask4()
{
    int _Mask= this->Mask;
    if (_Mask != 5 && _Mask != 2 && _Mask != 3)
        this->Mask = 4;
}

void  Car::isMask3()
{
    if (this->Mask != 5)
        this->Mask = 3;
}

bool Car::isMask()
{
    int _Mask; // eax

    _Mask = this->Mask;
    return _Mask == 2 || _Mask == 4 || _Mask == 3;
}

bool  Car::isJeep()
{
    return this->CarType == JEEP;
}

bool Car::isAPC()
{
    return this->CarType == APC;
}

bool  Car::isTaxi()
{
    int  _CarType; // eax

    _CarType = this->CarType;
    return _CarType == eTaxi || _CarType == STYPECAB;
}

// 0x00421610 IDA/BN: return CarType==TRAIN(0x3B). RE field-name impl (CarType offset differs from IDA).
bool Car::IsTrain() {
    return this->CarType == TRAIN;
}


void*  Car::GetInfoByTypeCar()
{
    strcpy(gKeyBuffer, ("car%d%c%c", this->CarType, 0, 0));
    return gText->Bsearch((wchar_t*)gKeyBuffer);
}

// 0x00423590 - guarded RE impl. IDA: checks pPed->isPlayer (+0x15C), Player::GetCurrentPlayer,
// Car::GetInfoByTypeCar, Hud::SetMessageText(gHud,...). RE layout differs; use RE field names only.
void Car::ShowCarInfo(Ped* pPed) {
    if (!pPed) return;
    Player* isPlayer = pPed->isPlayer;
    if (!isPlayer) return;
    if (!isPlayer->GetCurrentPlayer()) return;
    wchar_t* info = (wchar_t*)GetInfoByTypeCar();
    extern Hud* gHud;
    if (gHud && info) gHud->SetMessageText(info);
}

// 0x004221D0 - guarded partial RE impl. IDA: if clearing driver and Car.Player(+0x58) set, may call
// Player::GetCarControlFlag/SetControlFlags; then stores Driver. RE has no confirmed Car.Player(+0x58)
// or Player control-flag layout, so we only update Driver pointer. Do not synthesize control flags.
void Car::SetDriver(Ped* pPed) {
    // Guarded: preserve IDA-observable Driver field update; skip unconfirmed +0x58/control-flag side effects.
    this->Driver = pPed;
}

// 0x004235D0 - guarded partial RE impl. IDA: Driver->isPlayer, occupation!=EMPTY => ResetMessage+RestoreOnFootWeapons;
// if this->Player SetAttackChanged; SetDriver(0); SetHornDefault. RE Car has no confirmed Player@+0x58 field.
void Car::OnPlayerExit() {
    Ped* driver = this->Driver;
    if (!driver) return;
    Player* isPlayer = driver->isPlayer;
    if (isPlayer) {
        if (driver->GetOccupation() != (int)EMPTY) {
            if (isPlayer->GetCurrentPlayer()) {
                extern Hud* gHud;
                if (gHud) gHud->ResetMessage();
            }
            isPlayer->RestoreOnFootWeapons();
        }
        // IDA: if (this->Player) Player::SetAttackChanged(Player). RE Car has no confirmed Player@+0x58; skipped.
    }
    // IDA: Car::SetDriver(this,0); SetHornDefault(this)
    SetDriver(nullptr);
    SetHornDefault();
}

// 0x00411950 IDA/BN GetAndClearFieldAC: result=field_AC; field_AC=0; return result.
// Guarded RE impl by field name. RE Car has field_AC (offset differs from IDA +0xAC), semantic name matches.
int Car::ConsumePendingEvent0xac() {
    int result = this->field_AC;
    this->field_AC = 0;
    return result;
}

// 0x00421900 IDA/BN Car::SetFieldAC: *(+0xAC)=arg. RE field-name impl; field_AC exists in RE Car.
void Car::SetFieldAC(int value) {
    this->field_AC = (char)value;
}

// 0x00421200 IDA/BN Car::ClearFieldAD: *(+0xAD)=0. RE field-name impl; field_AD exists in RE Car.
void Car::ClearFieldAD() {
    this->field_AD = 0;
}

// 0x004119C0 IDA/BN IsEngineState4: return *(+0x9C)==4.
// Guarded no-op: RE Car has no confirmed engineState/field_9C; raw IDA offset unsafe on RE layout.
int Car::IsCarState4() {
    return 0;
}

// 0x004119D0 IDA/BN TakeField0xB4: result=*(+0xB4); *(+0xB4)=0; return result.
// Guarded no-op: RE Car has no confirmed field_B4; raw IDA offset unsafe on RE layout.
char Car::ConsumePendingEvent0xb4() {
    return 0;
}

// 0x0041E460 IDA/BN IsTrailerMaster: TrailerCtrl && TrailerCtrl->Car0 == this.
// Guarded no-op: RE Car has TrailerCtrl as int; TrailerCtrl struct layout/Car0 field not confirmed in RE headers.
bool Car::IsObjectAttached() {
    return false;
}

// 0x0041E480 IDA IsSpritePartOfCar(SpriteS1*): checks Car sprite/Driver/GameObject ownership.
// Guarded stub: RE sprite/driver/gameobject ownership graph not fully confirmed; avoid raw IDA offsets/field access.
bool Car::IsMySprite(void* /*sprite*/) {
    return false;
}
// 0x00475C10 IDA/BN Car::SetLocksDoor: if(locksDoor!=4) locksDoor=1. RE field-name impl.
void Car::SetLocksDoor() {
    if (this->locksDoor != 4) this->locksDoor = 1;
}

// 0x00475C30 IDA/BN Car::SetLocksDoor_4: locksDoor=4. RE field-name impl.
void Car::SetLocksDoor_4() {
    this->locksDoor = 4;
}

// 0x00475C40 IDA/BN Car::SetLocksDoor2: if(locksDoor!=4) locksDoor=2. RE field-name impl.
void Car::SetLocksDoor2() {
    if (this->locksDoor != 4) this->locksDoor = 2;
}

// 0x00475C60 IDA/BN Car::SetLocksDoor5: if(locksDoor!=4) locksDoor=5. RE field-name impl.
void Car::SetLocksDoor5() {
    if (this->locksDoor != 4) this->locksDoor = 5;
}

// 0x00475C80 IDA/BN Car::SetLocksDoor3: if(locksDoor!=4) locksDoor=3. RE field-name impl.
void Car::SetLocksDoor3() {
    if (this->locksDoor != 4) this->locksDoor = 3;
}

// 0x00421890 IDA/BN Car::SetCarFlag: PhysicsBitmask |= arg. RE field-name impl.
void Car::SetCarFlag(short flag) {
    this->PhysicsBitmask = (short)(this->PhysicsBitmask | flag);
}

// 0x004761F0 IDA/BN Car::ClearFlag: PhysicsBitmask &= ~arg. RE field-name impl.
void Car::ClearFlag(short flag) {
    this->PhysicsBitmask = (short)(this->PhysicsBitmask & ~flag);
}

// 0x004762C0 IDA/BN Car::SetFlag80: SetCarFlag(0x80).
void Car::SetFlag80() { this->SetCarFlag((short)0x80); }

// 0x004762D0 IDA/BN Car::SetFlag200: SetCarFlag(0x200).
void Car::SetFlag200() { this->SetCarFlag((short)0x200); }

// 0x004762F0 IDA/BN Car::ClearFlag100: ClearFlag(0x100).
void Car::ClearFlag100() { this->ClearFlag((short)0x100); }

// 0x00476300 IDA/BN Car::ClearFlag200: ClearFlag(0x200).
void Car::ClearFlag200() { this->ClearFlag((short)0x200); }

// 0x00476310 IDA/BN Car::ClearFlag400: ClearFlag(0x400).
void Car::ClearFlag400() { this->ClearFlag((short)0x400); }

// 0x004218A0 IDA/BN Car::SetTankFlag: SetCarFlag(8).
void Car::SetTankFlag() { this->SetCarFlag((short)8); }

// 0x0042ACA0 IDA/BN Car::ClearFlag1: field_A6 &= ~1. RE field-name impl.
void Car::ClearFlag1() { this->field_A6 = (char)(this->field_A6 & (char)~1); }

// 0x0042ACB0 IDA/BN Car::ClearFlagBit1: field_A6 &= ~2. RE field-name impl.
void Car::ClearFlagBit1() { this->field_A6 = (char)(this->field_A6 & (char)~2); }

// 0x0042ACC0 IDA/BN Car::ClearFlag4: field_A6 &= ~4. RE field-name impl.
void Car::ClearFlag4() { this->field_A6 = (char)(this->field_A6 & (char)~4); }

// 0x0042ACD0 IDA/BN Car::ClearFlag8: field_A6 &= ~8. RE field-name impl.
void Car::ClearFlag8() { this->field_A6 = (char)(this->field_A6 & (char)~8); }

// 0x0042AC70 IDA/BN Car::SetFlag1: field_A6 |= 1. RE field-name impl.
void Car::SetFlag1() { this->field_A6 = (char)(this->field_A6 | 1); }

// 0x0042AC80 IDA/BN Car::SetFlag2: field_A6 |= 2. RE field-name impl.
void Car::SetFlag2() { this->field_A6 = (char)(this->field_A6 | 2); }

// 0x0042AC90 IDA/BN Car::SetFlag4: field_A6 |= 4. RE field-name impl.
void Car::SetFlag4() { this->field_A6 = (char)(this->field_A6 | 4); }

// 0x0042AC20 IDA/BN Car::IsFlag1: (field_A6 & 1)==1. RE field-name impl.
bool Car::IsFlag1() { return (this->field_A6 & 1) == 1; }

// 0x0042AC30 IDA/BN Car::IsFlag2: (field_A6 & 2)==2. RE field-name impl.
bool Car::IsFlag2() { return (this->field_A6 & 2) == 2; }

// 0x0042AC40 IDA/BN Car::IsFlag4: (field_A6 & 4)==4. RE field-name impl.
bool Car::IsFlag4() { return (this->field_A6 & 4) == 4; }

// 0x0042AC50 IDA/BN Car::IsFlag8: (field_A6 & 8)==8. RE field-name impl.
bool Car::IsFlag8() { return (this->field_A6 & 8) == 8; }

// 0x0042AC60 IDA/BN Car::IsFlag32: (field_A6 & 0x20)==0x20. RE field-name impl.
bool Car::IsFlag32() { return (this->field_A6 & 0x20) == 0x20; }

// 0x00421540 IDA/BN Car::SetLightOn: field_A6 |= 0x20. RE field-name impl.
void Car::SetLightOn() { this->field_A6 = (char)(this->field_A6 | 0x20); }

// 0x00421550 IDA/BN Car::SetLightOff: field_A6 &= ~0x20. RE field-name impl.
void Car::SetLightOff() { this->field_A6 = (char)(this->field_A6 & (char)~0x20); }

// 0x0042AB90 IDA/BN Car::SetBrakingOn: field_AD=1. RE field-name impl.
void Car::SetBrakingOn() {
    this->field_AD = 1;
}

// 0x0042ABA0 IDA/BN Car::SetBrakingOff: field_AD=-1. RE field-name impl.
void Car::SetBrakingOff() {
    this->field_AD = (char)-1;
}
