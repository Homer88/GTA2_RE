#ifndef __CSPRITES1__H_
#define __CSPRITES1__H_

#include <stddef.h>

struct SpriteS1;
struct SpriteS3;
struct GameObject;

// ---------------------------------------------------------------------------
// CarTransforms == IDA "S3" element. Source: gta2.exe.h:5090-5108.
// Element size 60 (0x3C): Construct(this->S3_arr5031, 60, 5031, ...)
// (gta2.exe.c:155626).  Packs naturally to 0x3C (3 pad bytes between
// field_28 and sprite_type).  NOTE: a live SpriteS1* returned by
// SpriteS1::sub_421000(gSpriteS1) addresses the element MINUS 4, i.e.
//   SpriteS1* + 0x04 == &S3_arr5031[0] == the CarTransforms.
// ---------------------------------------------------------------------------
struct CarTransforms
{
    SpriteS1*      SpriteS1_;     // 0x00 back-pointer to owning SpriteS1
    GameObject*    GameObject;    // 0x04 owner (GameObject::sub_493850 -> SetGameObject)
    SpriteS3*      SpriteS3;      // 0x08 Car* when sprite_type == 2 (SetCar/GetCar)
    CarTransforms* NextElement;   // 0x0C
    int            PositionX;     // 0x10 world X
    int            PositionY;     // 0x14 world Y
    int            PositionZ;     // 0x18 world Z
    int            spriteId;      // 0x1C HIWORD = remap set by sub_4206C0
    short          Remap;         // 0x20
    short          field_22;      // 0x22
    int            field_24;      // 0x24
    char           field_28;      // 0x28 (+3 pad to 0x2C)
    int            sprite_type;   // 0x2C 3=GameObject 2=Car 1/4/5=sprite object
    int            field_30;      // 0x30 SetTo2 writes 2
    int            field_34;      // 0x34
    int            field_38;      // 0x38
};

static_assert(sizeof(CarTransforms) == 0x3C, "CarTransforms size 60");
static_assert(offsetof(CarTransforms, PositionX) == 0x10, "CarTransforms PositionX");
static_assert(offsetof(CarTransforms, sprite_type) == 0x2C, "CarTransforms sprite_type");

// ---------------------------------------------------------------------------
// SpriteS1 == IDA gta2.exe.h:4144-4148.  Single instance (gSpriteS1) at
// 0x0066FF1C, size 0x49B28 (kGlobals entry S38).
//   4 + 5031 * 0x3C = 4 + 0x49B24 = 0x49B28
// Layout proof (SpriteS1* P -> S3_arr5031[0] == CarTransforms, so CarTransforms
// lives at P+4):
//   sub_420600 writes x/y/z via P->S3_arr5031[0].PositionX/Y/Z  = P+0x14/18/1C
//   raw reads at gta2.exe.c:121959 use *(SpriteS1* + 20/24/28) = P+0x14/18/1C  OK
//   sub_4206F0 sets sprite_type at P+0x30 (== CarTransforms+0x2C)           OK
//   SetCar/SetGameObject store the owner at P+0x08 (== CarTransforms+0x04)   OK
// The dump prints sprite_type at +0x30; for a GameObject's sprite it must be 3.
// ---------------------------------------------------------------------------
struct SpriteS1
{
    SpriteS1*      FirstElement;      // 0x00 freelist head (only valid on the pool base)
    CarTransforms  S3_arr5031[5031];  // 0x04
};

static_assert(sizeof(SpriteS1) == 0x49B28, "SpriteS1 size 0x49B28");
static_assert(offsetof(SpriteS1, S3_arr5031) == 0x04, "SpriteS1 array base");

#endif // !__CSPRITES1__H_
