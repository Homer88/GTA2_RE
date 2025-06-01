#pragma once

#include "Global.h"
#include "Car.h"

class CarsPrefabs{
    private:
		extern Car *Car2;
		extern Car *Car3;
		Car CarArr306[306];
        unsigned short CarsCount;
        unsigned short field_E0C2;
    public:
    CarsPrefabs();
    ~CarsPrefabs();
    unsigned short GetCarsCount();
    Car* GetCar();
    Car* InsertCarAtFront(Car *pCar);
};