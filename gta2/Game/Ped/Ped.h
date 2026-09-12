
#ifndef __PED_H_
#define __PED_H_

#include "../Player/Player.h"


   
   

class Ped{
    

    public:
        void* S200[50];
        GameObject* GameObject0;
        int f13C;
        Car* CarCurrent1;
        Ped* PedCurrent;
        Ped* Driver;
        Ped* LinkedPed;
        Car* pVehicle;
        Car* CurrentVehicle;
        Car* TargetCarForEnter;
        Player *isPlayer;
        Ped* NextPed;
        //S169* S169;  надо проверить новое имя 
        GameObject* GameObject1;
        Car* CurrentCar2;
        Weapon* CurrentWeapon;
        Weapon* Weapon1;
        Weapon* Weapon2;
        Gang* pGang;
        Ped* DriverPed;
        Ped* LastCharPunched;
        Ped* f18C;
        //S94* S94;
        Ped* Ped3;
        Ped* ElvisLeader;
        int PositionX, PositionY, PositionZ;
        int PositionX1, PositionY1, PositionZ1;
        int X, Y, Z;
        Ped* DriverPed1;
        int ID;
        int IdPed;
        unsigned short Invulnerability;
        int ActionState1;
        unsigned short PoliceStar;
        unsigned short F20C;
        short Health;
        short Objectivetimer;
        short CarStateTimer;
        unsigned int Flags;
        char DamageState;
        byte ExitAnimState;
        int TypeSearch;
        byte CarId;
        int StatusPed;
       // Remap pRemap;
        int TargetCarDoor;
        byte AnimationState;
        int ActionState;
        int CurrentAction;
        int TypeGraphic;
        int GangCarModel;
        int StatePed;
        int SavedState;
        int DamageType;
       

    // 0x003F1004
    int FindNearestPlayer(void);
    // 0x00403920
    int SetSearchMode(void);
    // 0x00403930
    int SetAIController(void);
    // 0x00403940
    int SetAssignedCarIndex(void);
    // 0x00403950
    int ClearFlags(void);
    // 0x00403960
    int UpdateState(void);
    // 0x00403970
    int SetCurrentOccupation(void);
    // 0x00403980
    int GetOccupation(void);
    // 0x00403990
    int GetCurrentState(void);
    // 0x004039A0
    void  SetHealth(unsigned short Health);
    // 0x004039B0
    int SetTargetCarDoorIndex(void);
    // 0x004039C0
    int GetFlags1(void);
    // 0x004039D0
    int GetFlags2(void);
    // 0x004039E0
    int GetDamageState(void);
    // 0x004039F0
    int GetSub_4039F0(void);
    // 0x00403A00
    int GetPositionX(void);
    // 0x00403A10
    int GetPositionY(void);
    // 0x00403A20
    int ResetSpecialParam(void);
    // 0x00403A30
    int ResetToDefaults(void);
    // 0x00403A50
    int SetFlags(void);
    // 0x00403A60
    int GetAnimationState(void);
    // 0x00403A70
    int SetAnimationState(void);
    // 0x00403A80
    int GetActionParam();
    // 0x00403A90
    int GetCurrentAction(void);
    // 0x00403AA0
    int EnterCar(void);
    // 0x00403AC0
    int SetAsDriver(void);
    // 0x00403AD0
    int GetPassenger(void);
    // 0x00403AE0
    int SetLinkedPedestrian(void);
    // 0x00403B00
    int SetTargetVehicle(void);
    // 0x00403B10
    int GetCurrentCar(void);
    // 0x00403B20
    int GetCarStateTimer(void);
    // 0x00403B30
    int GetActionState(void);
    // 0x00403B40
    int SetVehicleDamageState(void);
    // 0x00403B50
    int SetExitAnimationState(void);
    // 0x00403B60
    int GetDeadPed(void);
    // 0x00403B70
    int GetExitAnimState(void);
    // 0x00403B80
    int IsInsideVehicle(void);
    // 0x00403B90
    int GetStance(void);
    // 0x00416B50
    int GetPositionZ(void);
    // 0x00416B60
    int GetCarPlayers(void);
    // 0x00416B80
    int GetPosition(void);
    // 0x0041B0A0
    bool  IsPlayerControlled();
    // 0x0041B0B0
    int GetAndResetFlag(void);
    // 0x00420B50
    int GetMissionThreadId(void);
    // 0x00420B60
    int GetIdPlayer(void);
    // 0x00420B70
    int GetSearchType(void);
    // 0x00420B80
    void  SetPoliceNoStar();
    // 0x00420B90
    int CarSystemManager_SelectTraffic(void);
    // 0x00433190
    int GetOccupationPolice(void);
    // 0x004331D0
    int Set_4331D0(void);
    // 0x004331E0
    int IsCriminal(void);
    // 0x00433220
    int RemoveGameObject(void);
    // 0x00433250
    int SpawnMarker(void);
    // 0x00433270
    int TransitionState(void);
    // 0x004332B0
    int SetState(void);
    // 0x00433380
    int IsSearchingPlayer(void);
    // 0x004333A0
    int HasSearchType(void);
    // 0x004333C0
    int SetOccupationAGENT(void);
    // 0x00433430
    int IsTileRoad(void);
    // 0x00433470
    int HasArrowYMinus(void);
    // 0x004334A0
    int IsTileSolid(void);
    // 0x004334D0
    int HasArrowYPlus(void);
    // 0x00433500
    int HasArrowXMinus(void);
    // 0x00433530
    int HasBidirectionalArrow(void);
    // 0x00433580
    int ProcessCommand(void);
    // 0x00433650
    int SetIdleAction(void);
    // 0x00433B40
    int Get_433B40(void);
    // 0x00433B50
    int DisableGameObject(void);
    // 0x00433B70
    int GetHealthPlayer(void);
    // 0x00433B80
    int SetParam(void);
    // 0x00433BA0
    int GetRemap(void);
    // 0x00433BB0
    int SetFlag(void);
    // 0x00433BC0
    int SetGraphicType(void);
    // 0x00433BD0
    int IncrementCounter(void);
    // 0x00433BF0
    int SetLinkedPed(void);
    // 0x00433C10
    int SetRemap_0(void);
    // 0x00433C80
    int SetActionState(void);
    // 0x00433C90
    int GetOCcupationIsElvis(void);
    // 0x00433CB0
    int GetPedFromSprite(void);
    // 0x00433DA0
    int IsInAction(void);
    // 0x00433DC0
    int GetPoliceStar(void);
    // 0x00433DD0
    int SetNextAction(void);
    // 0x00433DF0
    int ResetPedState(void);
    // 0x00433E50
    int UpdateIdleTimer(void);
    // 0x00433EB0
    int ProcessCarDamage(void);
    // 0x00434160
    int GetCarSearchRange(void);
    // 0x00434180
    int UpdateRecovery(void);
    // 0x004341D0
    int ProcessAI(void);
    // 0x00434300
    int GetInCar(void);
    // 0x00434740
    int StopAtObstacle(void);
    // 0x004347D0
    int ReleaseCarriedPed(void);
    // 0x00434870
    int StopCarryingPed(void);
    // 0x00434980
    int StartCarExit(void);
    // 0x00434A30
    int MakeCarDriveable(void);
    // 0x00434B40
    int StartExitAnim(void);
    // 0x00434B80
    int GetSprite(void);
    // 0x00434C00
    int GetCopStars(void);
    // 0x00434C40
    unsigned short SetPoliceStarLevel(unsigned short CopLevel);
    // 0x00434CD0
    int HandleWantedEvent(void);
    // 0x00434D70
    int GetCombatWeapon(void);
    // 0x00434E60
    int GetCopWeapon(void);
    // 0x00434FF0
    int UpdateGangRespect(void);
    // 0x004353D0
    int UpdateWantedLevel(void);
    // 0x00435490
    int GroupChangeLeader(void);
    // 0x004354C0
    int ReleasePedFromPlayer(void);
    // 0x004354F0
    int IsInTrain(void);
    // 0x00435720
    int BasicCleanup(void);
    // 0x00435B80
    int CleanupAndUpdateOccupationCounts(void);
    // 0x00435C80
    int SetPedTeleportTarget(void);
    // 0x00435CE0
    int ProcessDamage(void);
    // 0x00435E90
    int EnableInvisibility(void);
    // 0x00435EB0
    int DisableInvisibility(void);
    // 0x00435EE0
    int SetSpriteFlags(void);
    // 0x00435F00
    int ClearCarDoorTarget(void);
    // 0x00435F20
    int SetSpriteDoorFlag(void);
    // 0x00435F40
    int HealPed();
    // 0x00435FA0
    int CreatePlayer(void);
    // 0x00436070
    int PutPedInCarRelated(void);
    // 0x004360C0
    int SetPedPosition(void);
    // 0x00436220
    int SetDoubleDamage(void);
    // 0x00436250
    int DropWeaponPickup(void);
    // 0x00436460
    int FaceTargetPosition(void);
    // 0x00436830
    int RemoveActiveWeapon(void);
    // 0x00436860
    int RemoveSpareWeapon(void);
    // 0x00436890
    int UpdateSpriteDrawState(void);
    // 0x00437010
    int EngagePed(void);
    // 0x004371D0
    int ShouldAttackPed(void);
    // 0x00437670
    int IsTargetInView(void);
    // 0x00437BE0
    int GetTargetPed(void);
    // 0x00437EC0
    int CheckObjectiveCar(void);
    // 0x004390F0
    int ApplyKnockback(void);
    // 0x00439190
    int ProcessCollision(void);
    // 0x00439780
    int UpdateCarDamageState2(void);
    // 0x00439810
    int UpdateCarDamageState(void);
    // 0x004398B0
    int ReleaseCarriedPedOnHit(void);
    // 0x00439970
    int UpdateCarriedPed(void);
    // 0x00439D30
    int DragCarriedPed(void);
    // 0x00439E60
    int ProcessEnterCar(void);
    // 0x0043A210
    int AbortEnterCar(void);
    // 0x0043A290
    int MoveToTarget(void);
    // 0x0043A340
    int WalkToTarget(void);
    // 0x0043A3C0
    int ProcFollowPath(void);
    // 0x0043A490
    int ProcCrossRoad(void);
    // 0x0043A550
    int ProcCrossStreet1(void);
    // 0x0043A660
    int ProcCrossStreet2(void);
    // 0x0043A770
    int ProcCrossStreet3(void);
    // 0x0043A880
    int ProcCrossStreet4(void);
    // 0x0043A990
    int ProcBoardTrain(void);
    // 0x0043AA10
    int ProcChasePlayer(void);
    // 0x0043AB10
    int GetCopLevel(void);
    // 0x0043AD10
    int GiveWeapon(void);
    // 0x0043AEE0
    int CopyPed(void);
    // 0x0043B560
    int ReleaseCarDoor(void);
    // 0x0043B570
    int PlacePedOnTile(void);
    // 0x0043B7C0 void __fastcall
    void PlayRandomGesture(int arg0);  // (gm) старый: PickRoadDirection -> PlayRandomGesture
    // 0x0043B9D0
    int ProcSpawnTrainRider(void);
    // 0x0043BB50
    int CleanupPed(void);
    // 0x0043BBC0
    int SetObjective(void);
    // 0x0043BEC0
    int SetRampageCriminal(void);
    // 0x0043C110
    int AreAnyPedActive(void);
    // 0x0043C480
    int ProcGetInCar(void);
    // 0x0043D1C0
    int ProcEnterCar(void);
    // 0x0043D830
    int SetNPCWeapon(void);
    // 0x0043D880
    int ReportKill(void);
    // 0x0043E140
    int PlacePed(void);
    // 0x0043E350
    int EnterCarAsPassenger(void);
    // 0x0043E3A0
    int ComputeFacingRotation(void);
    // 0x0043E650
    int CleanUp(void);
    // 0x0043E8B0
    int ProcMugger(void);
    // 0x0043EAF0
    int ProcTrainAgent(void);
    // 0x0043EBC0
    int ProcCop(void);
    // 0x0043EC30
    int AbandonVehicle(void);
    // 0x0043ECC0
    int SearchForPed(void);
    // 0x0043F180
    int SyncWithGameObject(void);
    // 0x0043F340
    int ProcessCombat(void);
    // 0x0043FD10
    int ProcessCar(void);
    // 0x0043FEE0
    int ProcGetOnPublicTransport(void);
    // 0x004402C0
    int CopyPedAttributes(void);
    // 0x00440350
    int GroupCreate(void);
    // 0x004411B0
    int KillPed(void);
    // 0x004419E0
    int TakeDamage(void);
    // 0x00441A30
    int HandleDamage(void);
    // 0x00441F10
    int ResetPed(void);
    // 0x00442050
    int ProcCarThief(void);
    // 0x00442420
    int ProcTaxiPassenger(void);
    // 0x004427E0
    int ProcBusPassenger(void);
    // 0x00442A40
    int ProcDriver(void);
    // 0x00442DE0
    int ProcessByOccupation(void);
    // 0x00443170
    int ProcessByState(void);
    // 0x004436A0
    int ProcAttackTarget(void);
    // 0x00443C30
    int ProcExitCar(void);
    // 0x004440F0
    int ProcExitToTaxi(void);
    // 0x004441B0
    int ProcWalk(void);
    // 0x00444900
    int ProcWalkIdle(void);
    // 0x00444910
    int ProcWalkPlayer(void);
    // 0x00444920
    int ProcWalkArea(void);
    // 0x00444930
    int CreateGroup(void);
    // 0x00444A70
    int ProcDie(void);
    // 0x00444B50
    int PunchPed(void);
    // 0x00444D00
    int ProcessByAction(void);
    // 0x00445230
    int ProcGunCombat(void);
    // 0x00445330
    int Process(void);
    // 0x004454D0
    int ProcessStateAction(void);
    // 0x004454E0
    int Tick(void);
    // 0x00445C30
    int GetNearestPassenger(void);
    // 0x00450CB0
    int getCarDamageState(void);
    // 0x00472FD0
    int IsCarIndexUnassigned(void);
    // 0x00476840
    int SetupTrace(void);
    // 0x00482080
    int SetMoneyValue(void);
    // 0x00493000
    int SetZone(void);
    // 0x004A5040
    int IsTargetCarDoor(void);
    // 0x004A5050
    int SetHealthFullPlayer(void);
    // 0x004A5060
    int SetStatusFlag(void);
    // 0x004AF860
    int SetCar(void);
    // 0x004AF880
    int SetCar2(void);
    // 0x004C6750
    int ShowMessageToPlayer(void);


// ==== импорт имён из gm ====
    // 30 функций
    // 0x00433320: Ped::EnterAsPassenger
    void EnterAsPassenger();
    // 0x00433B00: Ped::IsCarried
    void IsCarried();
    // 0x00433B60: Ped::FetchActionState
    void FetchActionState();
    // 0x00433BE0: Ped::ClearTarget
    void ClearTarget();
    // 0x00433C50: Ped::SetActionParam
    void SetActionParam();
    // 0x00433C60: Ped::SetActionParam2
    void SetActionParam2();
    // 0x00433C70: Ped::SetActionParam3
    void SetActionParam3();
    // 0x00433D00: Ped::FindCarToEnter
    void FindCarToEnter();
    // 0x004340D0: Ped::GetCarYaw
    void GetCarYaw();
    // 0x004340F0: Ped::GetCarPosZ
    void GetCarPosZ();
    // 0x00434130: Ped::SetCarSpeed
    void SetCarSpeed();
    // 0x00434140: Ped::IsInCarSeat
    void IsInCarSeat();
    // 0x004341B0: Ped::GetCarDoorPed
    void GetCarDoorPed();
    // 0x004343B0: Ped::GetCarIndex
    void GetCarIndex();
    // 0x004348E0: Ped::GetCarAngle
    void GetCarAngle();
    // 0x004349A0: Ped::IsCarDoorOccupied
    void IsCarDoorOccupied();
    // 0x00434AF0: Ped::IsSamePlayer
    void IsSamePlayer();
    // 0x00435460: Ped::AppendActionKeys
    void AppendActionKeys();
    // 0x00435D90: Ped::EnterCarDoor
    void EnterCarDoor();
    // 0x00436BF0: Ped::UpdateFacing
    void UpdateFacing();
    // 0x0043AD50: Ped::PlacePedAtPosition
    void PlacePedAtPosition();
    // 0x0043BEB0: Ped::SetAiCheckCar
    void SetAiCheckCar();
    // 0x0043BED0: Ped::SetAiCheckCarChase
    void SetAiCheckCarChase();
    // 0x004400A0: Ped::SpawnPedGroup
    void SpawnPedGroup();
    // 0x004404E0: Ped::SpawnPedGroupFour
    void SpawnPedGroupFour();
    // 0x0044A320: Ped::IsVisibleToPlayer
    void IsVisibleToPlayer();
    // 0x004BB020: Ped::IsPathBlocked
    void IsPathBlocked();
    // 0x004BB560: Ped::IsBlockedBySprite
    void IsBlockedBySprite();
    // 0x004BD350: Ped::CheckStandingSurface
    void CheckStandingSurface();
    // 0x004BDD40: Ped::GetGroundContactFlags
    void GetGroundContactFlags();
};
#endif // !__PED_H_