#ifndef __SPAWNPOINT_H_
#define __SPAWNPOINT_H_

class SpawnPoint{

    public:

    // 0x00401B40
    int SubtractSprite(void);
    // 0x00401B60
    int WorldCoordinateToScreenCoord(void);
    // 0x004037A0
    int HasActivePeds(void);
    // 0x004038F0
    int GetInUse(void);
    // 0x00403BE0
    int UpdateAll(void);
    // 0x00403C40
    int IsGroupAlive(void);
    // 0x00403DA0
    int ProcessPeds(void);
    // 0x00403E90
    int UpdatePedStates(void);
    // 0x00403FB0
    int PutPedsInCar(void);
    // 0x00404120
    int SwapPed(void);
    // 0x00404450
    int GetLastPed(void);
    // 0x00404480
    int SpawnPointGetPedStance(void);
    // 0x00404490
    int FindClosestPed(void);
    // 0x00404840
    int IsGroupInCar(void);
    // 0x00404D40
    int RemovePed(void);
    // 0x00404EF0
    int LinkPedsToLeader(void);
    // 0x00405240
    int PutGroupInVehicle(void);
};

#endif // !__SPAWNPOINT_H_
