
#ifndef __EVENTHANDLER_H_
#define __EVENTHANDLER_H_


class SpriteS1;

// Partial IDA layout (0x2C bytes). Not all fields/semantics confirmed.
class EventHandler {
public:
    EventHandler* NextElement = nullptr; // +0
    SpriteS1* SpriteS1 = nullptr;        // +4
    EventHandler* pEventHandler = nullptr; // +8 (node/ref in IDA naming is reused)
    void* S65 = nullptr;                  // +0C
    void* Car = nullptr;                  // +10
    int field_14 = 0;                     // +14
    void* S63_1 = nullptr;                // +18
    char field_1C = 0;                    // +1C
    char field_1D = 0;
    char field_1E = 0;
    char field_1F = 0;
    int field_20 = 0;                     // +20
    void* S202 = nullptr;                 // +24
    char field_28 = 0;                    // +28
    char field_29 = 0;
    char field_2A = 0;
    char field_2B = 0;

    int IsUncollidable(void);
    int IsCarFlagSet(void);
    int Reset(void);
    int ClearCheckpoints(void);
    int SetOwnerID(unsigned char id);
    int SetOwnerID(void); // legacy stub
    int UpdateSpriteFrame(void);
    int KnockDoor(void);
    int UpdateEvents(void);
    int UpdateWeapon(void);
    int Destroy(void);
    int ApplyCollision(void);
    int SpawnExplosionFX(void);
    int HandleImpact(void);
    int HandlePedImpact(void);

    void ScalarDelete();
    void GetRenderFlags();
    void IsCheckpointActive();
    void ResolvePlayer();
    void IsActive();
    void SetDamageType();
    void SetSubObject();
    void Init();
    void GetGlassPosition();
    void ClearUpdateFlag();
    void SetField26();
    void CheckSubStructInactive();
    void SetSpriteConfig();
    void GetPosition();
    void GetDirection();
    void ComputeZone();
    void TriggerCarExplosion();
    void ProcessSpriteCollision();
    void SetCheckpoint();
    void CanBeTargeted();
    void SetState2(int arg0);

    int AddToCheckpoints(); // IDA 0x482630
};

extern EventHandler* gEventHandler;
#endif // !__EVENTHANDLER_H_