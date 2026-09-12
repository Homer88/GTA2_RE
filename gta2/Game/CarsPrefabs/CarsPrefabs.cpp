#include "CarsPrefabs.h"
#include "../Car/Car.h"


    // 0x0040F390
CarsPrefabs gCarsPrefabs;

CarsPrefabs::CarsPrefabs(){}

CarsPrefabs::~CarsPrefabs(){}

unsigned short CarsPrefabs::GetCarsCount(){

    return this->CarsCount;
}

// 0x00420E50

Car* CarsPrefabs::GetCar(){
    
    return this->Car3;
}


Car* CarsPrefabs::InsertCarAtFront(Car *pCar){

    pCar->LastCar=this->Car2;
    this->Car2=pCar;
    return this->Car2;
}
void* CarsPrefabs::ConstructSinLookupTable(int arg0){
        return 0;
    }


    // 0x0040F400


void* CarsPrefabs::GetDriver(void){
        return 0;
    }


    // 0x0040F410


int CarsPrefabs::GetOtherCar(int param_1,int param_2){
        return 0;
    }


    // 0x0040F430


void CarsPrefabs::LinkCars(int arg0,int param_2){

    }


    // 0x0040F450


void CarsPrefabs::AttachPlayers(void){

    }


    // 0x0040F470


void CarsPrefabs::RemovePlayers(void){

    }


    // 0x0040F490


int CarsPrefabs::InitializeCarPrefab(void){
        return 0;
    }


    // 0x0040F4B0


int CarsPrefabs::DereferencePointer(int arg0){
        return 0;
    }


    // 0x0040F4E0


bool CarsPrefabs::CompareGreaterOrEqual(short arg0){
        return 0;
    }


    // 0x0040F500


int CarsPrefabs::GetPrefabValue(void){
        return 0;
    }


    // 0x0040F520


int CarsPrefabs::GetPrefabData(void){
        return 0;
    }


    // 0x00420E40


void CarsPrefabs::InitToZero(int arg0){

    }








    // 0x00420E60


void CarsPrefabs::LinkedListZeroInit(int arg0){

    }


    // 0x00420E70


int CarsPrefabs::S1(void){
        return 0;
    }


    // 0x00420F20


int CarsPrefabs::AddCar(void){
        return 0;
    }


    // 0x00420F30


int CarsPrefabs::RemoveCar(void){
        return 0;
    }


    // 0x00424FF0


int CarsPrefabs::FindSpawnPoint(void){
        return 0;
    }


    // 0x004253C0


int CarsPrefabs::S10(void){
        return 0;
    }


    // 0x004253E0


int CarsPrefabs::S4(void){
        return 0;
    }


    // 0x00425400


int CarsPrefabs::S5_Destruct(void){
        return 0;
    }


    // 0x004254A0


int CarsPrefabs::GetCarEnd(void){
        return 0;
    }


    // 0x00426AC0


int CarsPrefabs::ActualSpawnCar(void){
        return 0;
    }


    // 0x00426D90


int CarsPrefabs::S2(void){
        return 0;
    }


    // 0x00426DB0


int CarsPrefabs::S5(void){
        return 0;
    }


    // 0x0042A2D0


int CarsPrefabs::UpdateCars(void){
        return 0;
    }


    // 0x0045AD30