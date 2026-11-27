
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

bool Car::isGunJeep(){
    return this->CarType == JEEP;
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

void Car::SetMask() {
    int _Mask = this->Mask;
    if (_Mask == 2
        || _Mask == 4
        || _Mask == 3)
        this->Mask;
}

void Car::SetHornDefault() {

    this->horn = 0;
}
bool Car::isEDSELFBI() {

    return this->CarType == EDSELFBI;
}

int Car::GetCarModel() {

    return this->CarType;
}

bool Car::isCopCar() {
    
    int  _CarModel = this->CarType;

    return _CarModel == COPCAR
        || _CarModel == SWATVAN
        || _CarModel == EDSELFBI;
}

bool Car::isMask7(){

    return this->Mask == 7;
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

bool Car::isTVVAN(){

    return this->CarType == TVVAN;
}


Player* Car::GetPlayer(){
 
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

// 0x004235D0 - guarded partial RE impl. IDA: Driver->isPlayer, occupation!=EMPTY => ResetMessage+RestoreOnFootWeapons;
// if this->Player SetAttackChanged; SetDriver(0); SetHornDefault. RE Car has no confirmed Player@+0x58/SetDriver.
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
        // IDA: if (this->Player) Player::SetAttackChanged(Player). RE Car has no confirmed Player field; skipped.
    }
    // IDA: Car::SetDriver(this,0); SetHornDefault(this)
    // SetDriver not present in RE; do not null driver blindly without confirmed ownership.
    SetHornDefault();
}