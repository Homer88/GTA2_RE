//реализация классов с машинами
#include "Global.h"
#include "Car.h"

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
    eTaxi = 56,
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

Car::Car(){
    this->Mask = 0;

}

Car::~Car(){
this->LastCar=0;
//this->SpriteS1=0;
//this->EngineStruct=0;
}

void Car::sub_4BF000(){

}

void Car::sub_421460(){

}
void Car::sub_424620(){

}


void Car::AddRoofAntenna(){

}


void Car::AddRoofGun(){
    int a,b,c;
    short d;
    gObject.SpawnObject(a,b,c,d);
    // еще функции

}

void Car::AddRoofTankTurret(){

}

void Car::AddRoofWaterGun(){

}

int Car::sub_424630(void *param1 ){
    return 0;
}

void Car::sub_420840(void *param1 ){

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

void * Car::sub_41F730(int pararm){
    return 0;//(void*)(gCarEngines.sub_4327E0(this->CarType)+44);


}

void Car::ExplodeCar(int a){

}


bool Car::IsDriverPlayer(){
    Ped *PedDriver;
    PedDriver=this->Driver;
    return PedDriver && PedDriver->Player;

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

this->SpriteS1->SetPosition(X,Y,Z);
//this->Physics->
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


class Player* Car::GetPlayer(){

    return this->Driver->Player;
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
       // if (!this->sub_424010(this))
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
    return gText.Bsearch((wchar_t*)gKeyBuffer);
}