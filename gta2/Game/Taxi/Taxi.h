
#ifndef __TAXI_H_
#define __TAXI_H_


class Taxi{
    public:

    // 0x004330A0
    int FindClosestCar(void);
    // 0x00433160
    int Clear(void);
    // 0x00434970
    int IsEmpty(void);
    // 0x004C0980
    int Reset(void);
    // 0x004C09B0
    int Init(void);
};

#endif // !__TAXI_H_