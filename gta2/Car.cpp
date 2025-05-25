//реализация классов с машинами

#include "Car.h"
#include "CarDoor.h"
#include "Object.h"
#include "Global.h"

Car::Car(){

}

Car::~Car(){
this->LastCar=0;
this->SpriteS1=0;
this->EngineStruct=0;
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
    return (void*)(gCarEngines.sub_4327E0(this->CarType)+44);


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

    CarModel _CarType= this->CarType;
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