#include "gta2_shim.h"

// Module: other, Class: VideoModeEntry
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x004c4d20: VideoModeEntry::sub_4C4D20
// IDA: VideoModeEntry::sub_4C4D20
// Ghidra: FUN_004c4d20
void gta2::VideoModeEntry_sub_4C4D20(void *self)
{
  int iVar1;
  bool bVar2;
  PedModel *pS21_3;
  PedModel *pS21;
  PedModel *pS21_1;
  
                              // WARNING: Load size is inaccurate
  iVar1 = *self;
  pS21 = gPedModel;
  while( true ) {
    for (; pS21_1 = gPedModel, gPedModel = pS21, iVar1 != 0;
        iVar1 = *(int *)(iVar1 + 4)) {
      gta2::CameraManager_Push(pS21_1,iVar1);
      pS21 = gPedModel;
      gPedModel = pS21_1;
    }
    bVar2 = gta2::CameraManager_IsEmpty(pS21_1);
    if (bVar2) break;
    pS21_3 = (PedModel *)gta2::CameraManager_Pop(pS21_1);
    gta2::SpriteS1_sub_4BE060((struct SpriteS1 *)pS21_3->field0_0x0);
    iVar1 = *(int *)&pS21_3->field_0x8;
    pS21 = gPedModel;
  }
  return;
}


// 0x004c4d60: VideoModeEntry::sub_4C4D60
// IDA: VideoModeEntry::sub_4C4D60
// Ghidra: ---
void gta2::VideoModeEntry_sub_4C4D60(struct VideoModeEntry *self)
{
  gta2::RenderManager_Set_sub_4C4B70(gRenderManager);
  self->field_0 = 0;
}


// 0x004c4df0: VideoModeEntry::VideoModeEntry
// IDA: VideoModeEntry::VideoModeEntry
// Ghidra: ---
VideoModeEntry * gta2::VideoModeEntry_VideoModeEntry(struct VideoModeEntry *self)
{
  struct RenderManager *pS20; // eax
  struct RenderManager *_pS20; // eax
  struct CameraManager *pS21; // eax

  if ( !gRenderManager )
  {
    pS20 = (struct RenderManager *)gta2::operator_new(0x2EE4u);
    if ( pS20 )
      _pS20 = gta2::RenderManager_RenderManager(pS20);
    else
      _pS20 = 0;
    gRenderManager = _pS20;
  }
  if ( !gCameraManager )
  {
    pS21 = (struct CameraManager *)gta2::operator_new(0xFA4u);
    if ( pS21 )
    {
      gCameraManager = gta2::CameraManager_CameraManager(pS21);
      gta2::VideoModeEntry_sub_4C4D60(self);
      return self;
    }
    gCameraManager = 0;
  }
  gta2::VideoModeEntry_sub_4C4D60(self);
  return self;
}


// 0x004c4e60: VideoModeEntry::sub_4C4E60
// IDA: VideoModeEntry::sub_4C4E60
// Ghidra: ---
LPVOID gta2::VideoModeEntry_sub_4C4E60(struct VideoModeEntry *self)
{
  LPVOID result; // eax

  if ( gRenderManager )
  {
    result = gta2::RenderManager_RenderManager_des(gRenderManager, 1);
    gRenderManager = 0;
  }
  if ( gCameraManager )
  {
    result = gta2::CameraManager_CameraManager_desc(gCameraManager, 1);
    gCameraManager = 0;
  }
  return result;
}



