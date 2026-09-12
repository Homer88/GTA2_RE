
#ifndef __AICONTROLLER_H_
#define __AICONTROLLER_H_


class AIController{
    public:

    // 0x004035B0
    int Int(void);
    // 0x004038E0
    int Initialize(void);
    // 0x00404400
    int AssignPed(void);
    // 0x004045D0
    int Update(void);
    // 0x004046F0
    int ProcessPed(void);
    // 0x00405760
    int ExecuteAction(void);
    // 0x00433360
    int SetIndexPed(void);
    // 0x00433370
    int IsGroupInVehicle(void);
    // 0x004AEE70
    int PolicePlaceRoadblock(void);
    // 0x004C4A30
    int TrafficLigthStructAddCarToPhase(void);
};

#endif // !__AICONTROLLER_H_