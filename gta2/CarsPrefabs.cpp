#include "CarsPrefabs.h"
#include "Car.h"

CarsPrefabs::CarsPrefabs(){

}

CarsPrefabs::~CarsPrefabs(){

}

unsigned short CarsPrefabs::GetCarsCount(){

    return this->CarsCount;
}


Car* CarsPrefabs::GetCar(){
    
    return this->Car3;
}

Car* CarsPrefabs::InsertCarAtFront(Car *pCar){

    pCar->LastCar=this->Car2;
    this->Car2=pCar;
    return this->Car2;
}