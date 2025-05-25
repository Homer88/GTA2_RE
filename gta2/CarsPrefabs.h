#ifndef ___CARSPREFABS_H_
#define ___CARSPREFABS_H_

class CarsPrefabs{
    private:
        Car *Car2;
        Car *Car3;
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
#endif