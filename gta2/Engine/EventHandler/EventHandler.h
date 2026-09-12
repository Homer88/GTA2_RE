
#ifndef __EVENTHANDLER_H_
#define __EVENTHANDLER_H_


class EventHandler{
    public:

    // 0x004210B0
    int IsUncollidable(void);
    // 0x00425760
    int IsCarFlagSet(void);
    // 0x00482490
    int Reset(void);
    // 0x00482560
    int ClearCheckpoints(void);
    // 0x00482790
    int SetOwnerID(void);
    // 0x00482BE0
    int UpdateSpriteFrame(void);
    // 0x00483BA0
    int KnockDoor(void);
    // 0x00483C40
    int UpdateEvents(void);
    // 0x00483D50
    int UpdateWeapon(void);
    // 0x00484910
    int Destroy(void);
    // 0x00484DD0
    int ApplyCollision(void);
    // 0x00485C90
    int SpawnExplosionFX(void);
    // 0x00486390
    int HandleImpact(void);
    // 0x004932D0
    int HandlePedImpact(void);


// ==== импорт имён из gm ====
    // 20 функций
    // 0x0041D030: EventHandler::ScalarDelete
    void ScalarDelete();
    // 0x004824C0: EventHandler::GetRenderFlags
    void GetRenderFlags();
    // 0x00482540: EventHandler::IsCheckpointActive
    void IsCheckpointActive();
    // 0x004827D0: EventHandler::ResolvePlayer
    void ResolvePlayer();
    // 0x004828B0: EventHandler::IsActive
    void IsActive();
    // 0x00482960: EventHandler::SetDamageType
    void SetDamageType();
    // 0x00482A90: EventHandler::SetSubObject
    void SetSubObject();
    // 0x00482B20: EventHandler::Init
    void Init();
    // 0x00482BA0: EventHandler::GetGlassPosition
    void GetGlassPosition();
    // 0x00482BD0: EventHandler::ClearUpdateFlag
    void ClearUpdateFlag();
    // 0x00482C00: EventHandler::SetField26
    void SetField26();
    // 0x00482C10: EventHandler::CheckSubStructInactive
    void CheckSubStructInactive();
    // 0x00482C30: EventHandler::SetSpriteConfig
    void SetSpriteConfig();
    // 0x00482C50: EventHandler::GetPosition
    void GetPosition();
    // 0x00482D90: EventHandler::GetDirection
    void GetDirection();
    // 0x00483500: EventHandler::ComputeZone
    void ComputeZone();
    // 0x004837F0: EventHandler::TriggerCarExplosion
    void TriggerCarExplosion();
    // 0x00483880: EventHandler::ProcessSpriteCollision
    void ProcessSpriteCollision();
    // 0x00483C00: EventHandler::SetCheckpoint
    void SetCheckpoint();
    // 0x004973E0: EventHandler::CanBeTargeted
    void CanBeTargeted();

    // 0x004827C0
    // (gm) ������: MissionManager::SetLevelCrossing -> EventHandler::SetState2
    void SetState2(int arg0);
};
#endif // !__EVENTHANDLER_H_