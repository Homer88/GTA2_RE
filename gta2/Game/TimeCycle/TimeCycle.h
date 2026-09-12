
#ifndef __TIMECYCLE_H_
#define __TIMECYCLE_H_


class TimeCycle{
    public:

    // 0x00474E80
    int FindFreeSlot(void);
    // 0x00474EA0
    int CreateCar(void);
    // 0x00474ED0
    int QueueTimeChange(void);
    // 0x00476BC0
    int ProcessCreatedObjects(void);
    // 0x00476D20
    int CreatePed2(void);
};

#endif // !__TIMECYCLE_H_