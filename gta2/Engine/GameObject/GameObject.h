
#ifndef __GAMEOBJECT_H_
#define __GAMEOBJECT_H_


class GameObject{
    public:

    // 0x00403900
    int GetVehicle(void);
    // 0x00403910
    int LinkTo(void);
    // 0x004338E0
    int SetPed(void);
    // 0x00433910
    int set_ped_state_1(void);
    // 0x00433920
    int SetSpeed(void);
    // 0x00433A40
    int GetRotation(void);
    // 0x00433A50
    int SetAnimationFrame(void);
    // 0x00433A80
    int GetDoorState(void);
    // 0x00433AC0
    int RefreshSprite(void);
    // 0x00491E40
    int Destroy(void);
    // 0x00493690
    int DropObject(void);
    // 0x00493850
    int AllocateSprite(void);
    // 0x004938A0
    int ApplyEffect(void);
    // 0x00494180
    int UpdateHeight(void);
    // 0x00496880
    int UpdatePed(void);
    // 0x004995A0
    int FindPath(void);
    // 0x0049A560
    int ProcessPedestrian(void);
    // 0x0049B0D0
    int ProcessVehicle(void);


// ==== импорт имён из gm ====
    // 33 функций
    // 0x004338D0: GameObject::GetSprite
    void GetSprite();
    // 0x00433A70: GameObject::SetParam
    void SetParam();
    // 0x00433AA0: GameObject::IsActive
    void IsActive();
    // 0x00433AB0: GameObject::SetActive
    void SetActive();
    // 0x00433AD0: GameObject::ClearFlag
    void ClearFlag();
    // 0x00433AE0: GameObject::SetFireFlag
    void SetFireFlag();
    // 0x00433AF0: GameObject::ClearFireFlag
    void ClearFireFlag();
    // 0x00491DE0: GameObject::ResetFireState
    void ResetFireState();
    // 0x00491EE0: GameObject::WorldToGridX
    void WorldToGridX();
    // 0x00491EF0: GameObject::TurnRight
    void TurnRight();
    // 0x00491F00: GameObject::TurnLeft
    void TurnLeft();
    // 0x00491F80: GameObject::IsTurnAllowed
    void IsTurnAllowed();
    // 0x004920A0: GameObject::UpdateHitch
    void UpdateHitch();
    // 0x00492170: GameObject::GetId
    void GetId();
    // 0x00492190: GameObject::IsPathClear
    void IsPathClear();
    // 0x00492400: GameObject::StartMoving
    void StartMoving();
    // 0x004928B0: GameObject::Steer
    void Steer();
    // 0x00492C20: GameObject::GetSpawnIndex
    void GetSpawnIndex();
    // 0x00492C30: GameObject::UpdatePerpendicular
    void UpdatePerpendicular();
    // 0x00492CB0: GameObject::SetTargetPed
    void SetTargetPed();
    // 0x00492CC0: GameObject::GetAttackRadius
    void GetAttackRadius();
    // 0x00492CE0: GameObject::GetPlayerOne
    void GetPlayerOne();
    // 0x00492CF0: GameObject::GetPlayerTwo
    void GetPlayerTwo();
    // 0x00492D00: GameObject::FindNextTile
    void FindNextTile();
    // 0x00492FD0: GameObject::IsInTaxi
    void IsInTaxi();
    // 0x00493610: GameObject::CanReactToPlayer
    void CanReactToPlayer();
    // 0x00493780: GameObject::GetPedAndSpawnPoint
    void GetPedAndSpawnPoint();
    // 0x00495980: GameObject::UpdateMovement
    void UpdateMovement();
    // 0x00496500: GameObject::FindPathBackToNode
    void FindPathBackToNode();
    // 0x00497480: GameObject::CanTargetSprite
    void CanTargetSprite();
    // 0x0049C680: GameObject::IsTileBlocked
    void IsTileBlocked();
    // 0x0049C9D0: GameObject::SetNodeTarget
    void SetNodeTarget();
    // 0x0049CB60: GameObject::CanMoveToNode
    void CanMoveToNode();

    // 0x0049DD30
    // (gm) ������: Player::SetEnergyMax -> GameObject::SetCarDamageColour
    void SetCarDamageColour(int arg0);
};
#endif // !__GAMEOBJECT_H_