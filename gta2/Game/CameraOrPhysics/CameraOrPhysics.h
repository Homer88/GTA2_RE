#ifndef __CAMERAORPHYSICS_H_
#define __CAMERAORPHYSICS_H_

#include <cstdint>

// IDA: CameraOrPhysics is 0xC88 bytes. cameraPosTarget[80] at 0, stride 0x28.
// Index at 0xC80, cameraPosTarget2 at 0xC84. sub_4BA2C0 reads a5 from
// cameraPosTarget[4].field_4 (+0xA8 absolute) as int BaseCar[0].field value.
struct CameraOrPhysics_PosTarget {
    std::uint32_t fild;            // +0x00
    std::uint32_t field_4;         // +0x04 (IDA name; absolute +0xA8 for [4])
    std::uint32_t CameraOrPhysics; // +0x08
    std::uint32_t Car;             // +0x0C
    std::uint32_t field_10;        // +0x10
    std::uint32_t field_14;        // +0x14
    std::uint32_t S32;             // +0x18
    std::uint32_t Player;          // +0x1C
    std::uint32_t field_20;        // +0x20
    std::uint32_t field_24;        // +0x24
};
static_assert(sizeof(CameraOrPhysics_PosTarget) == 0x28, "CameraOrPhysics_PosTarget size");

class CameraOrPhysics{
    public:
    CameraOrPhysics_PosTarget cameraPosTarget[80]; // +0x000
    std::uint32_t Index;                           // +0xC80
    std::uint32_t cameraPosTarget2;                // +0xC84

    CameraOrPhysics();

    // 0x0041F580 - minimal IDA-faithful subset: sets defaults and calls SetWindowDimensions.
    void Init();

    // Debug-only: closer BA2C0 a5 source. IDA reads
    // gCameraOrPhysics_5E3CC4->cameraPosTarget[4].field_4 as BaseCar[0].field value.
    int GetBA2C0A5Value(bool& ok) const;

    // 0x0040FE50
    int SetPararm(void);
    // 0x0040FE60
    int DMAudio(void);
    // 0x0041E010
    int SetFollowTarget(void);
    // 0x0041E410
    int UpdateCurrentState(void);
    // 0x0041EA10
    int ProcessActions(void);
    // 0x0041EAC0
    int thunk_FUN_0041e7a0(void);
    // 0x0041F410
    int FocusOnObject(void);
    // 0x00433E90
    int IsActive(void);
    // 0x00475B60 IDA/BN CameraOrPhysics::ResetAccuracy: cameraPosTarget[1].CameraOrPhysics=1. RE field-name impl.
    void ResetAccuracy();

    // 0x004A5070 IDA/BN CameraOrPhysics::SetActive: cameraPosTarget[1].field_10 = 2. RE field-name impl.
    void SetActive();


// ==== methods from gm ====
    // 0x004023E0: CameraOrPhysics::UpdateTransform
    void UpdateTransform();
    // 0x0041F180: CameraOrPhysics::CheckSpriteOnScreen
    void CheckSpriteOnScreen();
    // 0x004A4CF0: CameraOrPhysics::ReleaseTarget
    void ReleaseTarget();
    // 0x004A5090: CameraOrPhysics::SetTargetPosition
    void SetTargetPosition();

    // 0x0041EB70 - debug/compat minimal init for cameraPosTarget[4].field_4 (+0xA8)
    void SetWindowDimensions(unsigned int windowWidth, int windowHeight);
};
static_assert(sizeof(CameraOrPhysics) == 0xC88, "CameraOrPhysics size");


extern CameraOrPhysics* gCameraOrPhysics;
// Debug-only alias observed in IDA as gCameraOrPhysics_5E3CC4; set under GTA2_TEXT_GBH.
// Not authoritative for full RE runtime semantics.
extern CameraOrPhysics* gCameraOrPhysics_5E3CC4;
#endif // !__CAMERAORPHYSICS_H_
