#ifndef __CARSPREFABS_H_
#define __CARSPREFABS_H_



//#include "Global.h"
#include "Car.h"
class Car;

class CarsPrefabs{
    private:
		Car *Car2;
		Car *Car3;
      
        int CarArr[306];
        unsigned short CarsCount;
        unsigned short field_E0C2;
    public:
    CarsPrefabs();
    ~CarsPrefabs();
    unsigned short GetCarsCount();
    Car* GetCar();
    Car* InsertCarAtFront(Car *pCar);
};

#endif // !__CARSPREFABS_H_