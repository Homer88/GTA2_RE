
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


// ==== Ð¸Ð¼Ð¿Ð¾Ñ€Ñ‚ Ð¸Ð¼Ñ‘Ð½ Ð¸Ð· gm ====
    // 3 Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¹
    // 0x004B3110: SpawnPoint::InitFromPoint1
    void InitFromPoint1();
    // 0x004B3130: SpawnPoint::InitFromPoint2
    void InitFromPoint2();
    // 0x004BA620: SpawnPoint::DecodeSpawnData
    void DecodeSpawnData();


    // 0x0049E540
    // (gm) ñòàðûé: Player::IsTileBlockedPlayer -> SpawnPoint::IsSlotActive
    int IsSlotActive(int arg0, int arg1);
    // 0x0049E570
    // (gm) ñòàðûé: Player::IsTileOneWay -> SpawnPoint::IsSlotFree
    int IsSlotFree(int arg0, int arg1);
};
#endif // !__SPAWNPOINT_H_