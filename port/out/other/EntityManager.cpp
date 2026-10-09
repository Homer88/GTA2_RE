#include "gta2_shim.h"

// Module: other, Class: EntityManager
// Functions: 41
// Source: unified (IDA+Ghidra)

// 0x0046b5e0: EntityManager::sub_46B5E0
// IDA: EntityManager::sub_46B5E0
// Ghidra: FUN_0046b5e0
undefined1 gta2::EntityManager_sub_46B5E0(int param_1,undefined4 param_2)
{
  switch(param_2) {
  case 0:
    return 0xff;
  case 1:
    return *(undefined1 *)(param_1 + 0xc);
  case 2:
    return *(undefined1 *)(param_1 + 0xe);
  case 3:
    return *(undefined1 *)(param_1 + 0xf);
  default:
    return 0;
  }
}


// 0x0046b620: EntityManager::Defaut
// IDA: EntityManager::Defaut
// Ghidra: ---
char gta2::EntityManager_Defaut(struct EntityManager *self, unsigned __int8 a2)
{
  char v2; // dl
  char v3; // al
  char v4; // dl
  char result; // al
  char v6; // [esp+Bh] [ebp-5h]
  char v7; // [esp+Fh] [ebp-1h]
  char a2a; // [esp+14h] [ebp+4h]

  v6 = 2 * a2 / 3;
  v2 = -1 - 4 * a2;
  a2a = 5 * (51 - a2);
  v7 = v2 + 2 * v6;
  self->field_E = v2;
  self->field_C = v7;
  self->field_10 = v2;
  v3 = v2 + 3 * v6;
  self->field_D = a2a - 3 * v6;
  self->field_F = a2a - v6;
  self->field_11 = a2a - 2 * v6;
  self->field_12 = v6 + v2;
  v4 = v6 + v2;
  self->field_13 = a2a - v6;
  self->field_17 = v3;
  self->field_14 = v4;
  self->field_18 = v4;
  self->field_15 = a2a;
  self->field_19 = a2a - v6;
  result = a2a;
  self->field_16 = a2a - 2 * v6;
  self->field_1A = v7;
  self->field_1B = a2a;
  return result;
}


// 0x0046bb40: EntityManager::sub_46BB40
// IDA: EntityManager::sub_46BB40
// Ghidra: ---
void gta2::EntityManager_sub_46BB40(struct EntityManager *self)
{
  self->field_2F00 = 0;
}


// 0x0046bb90: EntityManager::sub_46BB90
// IDA: EntityManager::sub_46BB90
// Ghidra: FUN_0046bb90
void gta2::EntityManager_sub_46BB90(int param_1,undefined4 *param_2,undefined4 *param_3)
{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = *(int *)(param_1 + 0x2efc);
  *(undefined4 *)(param_1 + 0x1c + iVar1 * 8) = *param_2;
  iVar1 = param_1 + 0x1c + iVar1 * 8;
  *(undefined4 *)(iVar1 + 4) = *param_3;
  iVar2 = *(int *)(param_1 + 0x2efc);
  do {
    iVar2 = iVar2 + -1;
    if (iVar2 < 0) {
      *(int *)(param_1 + 0x2efc) = *(int *)(param_1 + 0x2efc) + 1;
      return;
    }
    iVar3 = FUN_0046bb60(iVar1);
  } while (iVar3 == 0);
  return;
}


// 0x0046bd40: EntityManager::sub_46BD40
// IDA: EntityManager::sub_46BD40
// Ghidra: FUN_0046bd40
void gta2::EntityManager_sub_46BD40(undefined4 *param_1,undefined4 *param_2,SpriteS1 *param_3)
{
  float10 fVar1;
  float10 fVar2;
  SpriteS1 *extraout_var;
  SpriteS1 *pSVar3;
  
  pSVar3 = param_3;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffe4,_DAT_006633ac);
  FUN_0046bbf0((void *)*param_2,(PedStats *)*param_1,(PedStats *)*param_2,
               extraout_var,(int)pSVar3);
  fVar1 = gta2::PedStats_EncodedFloatToRegularFloat(param_1);
  fVar2 = gta2::PedStats_EncodedFloatToRegularFloat(&DAT_00663504);
  param_3->FirstElement =
       (SpriteS1 *)
       (float)((float10)(uint)gCameraOrPhysics->ScreenY +
              fVar2 * (float10)(float)fVar1);
  fVar1 = gta2::PedStats_EncodedFloatToRegularFloat(param_2);
  fVar2 = gta2::PedStats_EncodedFloatToRegularFloat(&DAT_00663504);
  param_3->Matrix3DArray[0].SpriteS1 =
       (SpriteS1 *)
       (float)((float10)(uint)gCameraOrPhysics->ScreenH +
              fVar2 * (float10)(float)fVar1);
  fVar1 = gta2::PedStats_EncodedFloatToRegularFloat(&DAT_006635fc);
  param_3->Matrix3DArray[0].Car = (Car *)(float)fVar1;
  return;
}


// 0x0046bdf0: EntityManager::sub_46BDF0
// IDA: EntityManager::sub_46BDF0
// Ghidra: FUN_0046bdf0
void gta2::EntityManager_sub_46BDF0(void *self,PedStats *pS17_a1,PedStats *pS17,SpriteS1 *param_3)
{
  float10 fVar1;
  float10 fVar2;
  SpriteS1 *pSVar3;
  
  pSVar3 = param_3;
  gta2::S202_sub_41F980((SpriteS1 *)&stack0xffffffe4,_DAT_006633a0);
  FUN_0046bbf0((void *)pS17->DAT_005eb854,(PedStats *)pS17_a1->DAT_005eb854,
               (PedStats *)pS17->DAT_005eb854,self,(int)pSVar3);
  fVar1 = gta2::PedStats_EncodedFloatToRegularFloat(pS17_a1);
  fVar2 = gta2::PedStats_EncodedFloatToRegularFloat(&gS17_V3);
  param_3->FirstElement =
       (SpriteS1 *)
       (float)((float10)(uint)gCameraOrPhysics->ScreenY +
              fVar2 * (float10)(float)fVar1);
  fVar1 = gta2::PedStats_EncodedFloatToRegularFloat(pS17);
  fVar2 = gta2::PedStats_EncodedFloatToRegularFloat(&gS17_V3);
  param_3->Matrix3DArray[0].SpriteS1 =
       (SpriteS1 *)
       (float)((float10)(uint)gCameraOrPhysics->ScreenH +
              fVar2 * (float10)(float)fVar1);
  fVar1 = gta2::PedStats_EncodedFloatToRegularFloat(&gS17_V2);
  param_3->Matrix3DArray[0].Car = (Car *)(float)fVar1;
  return;
}


// 0x0046c140: EntityManager::sub_46C140
// IDA: EntityManager::sub_46C140
// Ghidra: ---
S900 * gta2::EntityManager_sub_46C140(struct EntityManager *self, int *arg0, void *a2)
{
  unsigned __int16 *v3; // edx
  int v5; // ecx
  _DWORD *v6; // eax
  SpriteS1 *v7; // eax
  S900 *result; // eax
  _DWORD *v9; // [esp-4h] [ebp-10h]
  _BYTE v10[4]; // [esp+8h] [ebp-4h] BYREF

  v3 = (unsigned __int16 *)a2;
  v5 = *arg0;
  self->dword_5EB854_ = *arg0;
  if ( *v3 )
  {
    gta2::sub_41F990(&arg0, *v3);
    v9 = v6;
    v7 = gta2::Player_sub_401B40((Player *)&self->dword_5EB854_, (S202 *)v10, (int)self);
    result = (S900 *)gta2::sub_401B90(v7, &a2, v9);
    self->field_8 = *(_DWORD *)&result->Index;
  }
  else
  {
    self->dword_5EB854 = v5;
    result = (S900 *)unk_6634B4.FirstElement;
    self->field_8 = (int)unk_6634B4.FirstElement;
  }
  return result;
}


// 0x0046c210: EntityManager::sub_46C210
// IDA: EntityManager::sub_46C210
// Ghidra: FUN_0046c210
void gta2::EntityManager_sub_46C210(int param_1,ushort *param_2,char *param_3,undefined4 param_4)
{
  ushort *puVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined *puVar4;
  undefined4 uVar5;
  int local_4;
  
  puVar1 = param_2;
  local_4 = param_1;
  local_4 = FUN_004bf6b0(*param_2 & 0x3ff);
  if ((short)local_4 != 0) {
    if (*param_3 == '\0') {
      param_2 = (ushort *)(*puVar1 & 0xe000);
      FUN_0046b710(&param_2);
    }
    else {
      param_2 = (ushort *)(*puVar1 & 0xe000);
      FUN_0046b910(&param_2);
    }
    puVar4 = &DAT_006632a0;
    uVar3 = (*puVar1 & 0x1000) >> 5;
    _DAT_006633b8 = uVar3;
    uVar5 = param_4;
    uVar2 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&local_4);
    (*(code *)gbh_DrawTriangle)(gTimeDayAndNight | uVar3,uVar2,puVar4,uVar5);
    *(int *)(param_1 + 0x2f00) = *(int *)(param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046c2c0: EntityManager::sub_46C2C0
// IDA: EntityManager::sub_46C2C0
// Ghidra: FUN_0046c2c0
void gta2::EntityManager_sub_46C2C0(void *param_1,ushort *param_2)
{
  float fVar1;
  ushort *puVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pSVar4;
  Model *pMVar5;
  void *pvVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  float10 fVar12;
  undefined *puVar13;
  int *piVar14;
  SpriteS1 *local_60 [9];
  undefined1 local_3c [16];
  undefined1 local_2c [16];
  undefined1 local_1c [24];
  undefined1 local_4 [4];
  
  if (gSkipLeft != 0) {
    return;
  }
  if (DAT_006633b2 == '\x01') {
    pMVar5 = (Model *)FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,
                                   (PedStats *)&DAT_006636f0,&DAT_006632a0);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632c0);
      _DAT_006632dc = fVar1;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_2c + 4);
      piVar14 = (int *)&DAT_006633b4;
      gta2::S202_sub_41F980((SpriteS1 *)(local_2c + 8),_DAT_006633b4 - (int)_DAT_006633a8);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar14);
      local_60[0] = pSVar3->FirstElement;
      puVar13 = &DAT_006632c0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_2c + 0xc),
                          (S127 *)local_60);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                 (PedStats *)pSVar3,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_1c,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632dc = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_006632c0 < _DAT_006632a0) {
      return;
    }
    puVar13 = &DAT_00663300;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_1c + 4),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar3,puVar13);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_00663300;
      puVar11 = (undefined4 *)&DAT_006632e0;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_006632fc = 63.9999;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_1c + 8);
      piVar14 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_1c + 0xc),(int)pMVar5);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar14);
      local_60[0] = pSVar3->FirstElement;
      puVar13 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_1c + 0x10)
                          ,(S127 *)local_60);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_1c + 0x14)
                          ,(S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar4,
                 (PedStats *)pSVar3,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_4,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632fc = (float)((float10)63.9999 - fVar12);
    }
  }
  else {
    if (DAT_006633b2 != '\x02') {
      FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                   &DAT_006632a0);
      FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632c0);
      if (_DAT_006632c0 < _DAT_006632a0) {
        return;
      }
      puVar13 = &DAT_00663300;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_60 + 1),
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar3,puVar13);
      puVar13 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_60 + 2),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(&gS17_V1,pSVar3,puVar13);
      _DAT_006633b8 = *(uint *)(&DAT_005930d4 + (uint)(*param_2 >> 0xd) * 4);
      goto LAB_0046c780;
    }
    puVar13 = &DAT_00663300;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_60 + 3),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar3,puVar13);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      puVar13 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_60 + 4),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(&gS17_V1,pSVar3,puVar13);
      _DAT_006632fc = fVar1;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_60 + 5);
      piVar14 = (int *)&DAT_006633b4;
      pSVar4 = pSVar3;
      gta2::S202_sub_41F980((SpriteS1 *)(local_60 + 6),_DAT_006633b4 - (int)_DAT_006633a8);
      pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar4,piVar14);
      local_60[0] = pSVar3->FirstElement;
      puVar13 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_60 + 7),
                          (S127 *)local_60);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_60 + 8),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar4,
                 (PedStats *)pSVar3,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_3c,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632fc = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_006632e0 < _DAT_00663300) {
      return;
    }
    FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                 &DAT_006632a0);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_006632a0;
      puVar11 = (undefined4 *)&DAT_006632c0;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_006632dc = 63.9999;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_3c + 4);
      piVar14 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_3c + 8),(int)pMVar5);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar14);
      local_60[0] = pSVar3->FirstElement;
      puVar13 = &DAT_006632c0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_3c + 0xc),
                          (S127 *)local_60);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                 (PedStats *)pSVar3,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_2c,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632dc = (float)((float10)63.9999 - fVar12);
    }
  }
  _DAT_006633b8 = 16389;
  if ((*param_2 & 0x2000) == 0) {
    _DAT_00663318 = 0x427fffe6;
    _DAT_006632b8 = 0;
    _DAT_006632d8 = 0;
    _DAT_006632f8 = 0x427fffe6;
  }
  else {
    _DAT_006632b8 = 0x427fffe6;
    _DAT_006632d8 = 0x427fffe6;
    _DAT_006632f8 = 0;
    _DAT_00663318 = 0;
  }
  _DAT_006632bc = 0x427fffe6;
  _DAT_0066331c = 0x427fffe6;
LAB_0046c780:
  puVar2 = param_2;
  param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
  if ((short)param_2 != 0) {
    if ((*puVar2 & 0x1000) != 0) {
      _DAT_006633b8 = _DAT_006633b8 | 0x80;
    }
    uVar9 = (uint)*(byte *)((int)param_1 + 0xc);
    puVar13 = &DAT_006632a0;
    uVar7 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2);
    (*(code *)gbh_DrawTile)
              (gTimeDayAndNight | _DAT_006633b8,uVar7,puVar13,uVar9);
    *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046c7f0: EntityManager::sub_46C7F0
// IDA: EntityManager::sub_46C7F0
// Ghidra: FUN_0046c7f0
void gta2::EntityManager_sub_46C7F0(void *param_1,ushort *param_2)
{
  float fVar1;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pSVar4;
  Model *pMVar5;
  void *pvVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  float10 fVar12;
  PedStats *pPVar13;
  undefined *puVar14;
  undefined *puVar15;
  int *piVar16;
  SpriteS1 *local_98 [7];
  undefined1 local_7c [56];
  undefined1 local_44 [44];
  undefined1 local_18 [20];
  undefined1 local_4 [4];
  
  if (gSkipRight != 0) {
    return;
  }
  if (DAT_006633b2 == '\x01') {
    puVar14 = &DAT_006632c0;
    pPVar13 = (PedStats *)&DAT_006636f0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 8),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar2,pPVar13,puVar14);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      puVar15 = &DAT_006632a0;
      puVar14 = &DAT_006636f0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 0x10),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar2,puVar14,puVar15);
      _DAT_006632bc = fVar1;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_7c + 0x18);
      piVar16 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)(_DAT_006633b4 - (int)_DAT_006633a8);
      gta2::S202_sub_41F980((SpriteS1 *)(local_7c + 0x20),(int)pMVar5);
      pSVar2 = gta2::S122_sub_401BF0(pMVar5,pSVar2,piVar16);
      local_98[0] = pSVar2->FirstElement;
      puVar14 = &DAT_006632a0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_7c + 0x28)
                          ,(S127 *)local_98);
      pPVar13 = (PedStats *)&DAT_006636f0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 0x30),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar3,pPVar13,(PedStats *)pSVar2,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_44,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632bc = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_006632c0 < _DAT_006632a0) {
      return;
    }
    puVar14 = &DAT_006632e0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_44 + 8),
                        (S127 *)&DAT_00663450);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0x10),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar14);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_006632e0;
      puVar11 = (undefined4 *)&DAT_00663300;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_0066331c = 63.9999;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_44 + 0x18);
      piVar16 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_44 + 0x20),(int)pMVar5);
      pSVar2 = gta2::S122_sub_401BF0(pMVar5,pSVar2,piVar16);
      local_98[0] = pSVar2->FirstElement;
      puVar14 = &DAT_00663300;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_44 + 0x28)
                          ,(S127 *)local_98);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_18 + 4),
                          (S127 *)&DAT_00663450);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 0xc),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar4,(PedStats *)pSVar3,
                 (PedStats *)pSVar2,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_4,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_0066331c = (float)((float10)63.9999 - fVar12);
    }
  }
  else {
    if (DAT_006633b2 != '\x02') {
      puVar14 = &DAT_006632c0;
      pPVar13 = (PedStats *)&DAT_006636f0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0x1c),
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)pSVar2,pPVar13,puVar14);
      puVar15 = &DAT_006632a0;
      puVar14 = &DAT_006636f0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 0x34),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar2,puVar14,puVar15);
      if (_DAT_006632c0 < _DAT_006632a0) {
        return;
      }
      puVar14 = &DAT_006632e0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_98 + 4),
                          (S127 *)&DAT_00663450);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 0x10),
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar14);
      puVar14 = &DAT_00663300;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_98 + 6),
                          (S127 *)&DAT_00663450);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 4),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar3,pSVar2,puVar14);
      _DAT_006633b8 = *(uint *)(&DAT_005930f4 + (uint)(*param_2 >> 0xd) * 4);
      goto LAB_0046cdbf;
    }
    puVar14 = &DAT_006632e0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 4),
                        (S127 *)&DAT_00663450);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0x24),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar14);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      puVar14 = &DAT_00663300;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 0xc),
                          (S127 *)&DAT_00663450);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0xc),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar3,pSVar2,puVar14);
      _DAT_0066331c = fVar1;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_7c + 0x14);
      piVar16 = (int *)&DAT_006633b4;
      pSVar3 = pSVar2;
      gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 8),_DAT_006633b4 - (int)_DAT_006633a8);
      pSVar2 = gta2::S122_sub_401BF0((Model *)pSVar2,pSVar3,piVar16);
      local_98[0] = pSVar2->FirstElement;
      puVar14 = &DAT_00663300;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_7c + 0x1c)
                          ,(S127 *)local_98);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_44 + 0x14)
                          ,(S127 *)&DAT_00663450);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 0x24),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar4,(PedStats *)pSVar3,
                 (PedStats *)pSVar2,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_18,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_0066331c = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_006632e0 < _DAT_00663300) {
      return;
    }
    puVar14 = &DAT_006632c0;
    pPVar13 = (PedStats *)&DAT_006636f0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 0x2c),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar2,pPVar13,puVar14);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_006632c0;
      puVar11 = (undefined4 *)&DAT_006632a0;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_006632bc = 63.9999;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_98 + 1);
      piVar16 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_98 + 2),(int)pMVar5);
      pSVar2 = gta2::S122_sub_401BF0(pMVar5,pSVar2,piVar16);
      local_98[0] = pSVar2->FirstElement;
      puVar14 = &DAT_006632a0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_98 + 3),
                          (S127 *)local_98);
      pPVar13 = (PedStats *)&DAT_006636f0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_98 + 5),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar3,pPVar13,(PedStats *)pSVar2,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_7c,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632bc = (float)((float10)63.9999 - fVar12);
    }
  }
  _DAT_006633b8 = 0x4005;
  if ((*param_2 & 0x2000) == 0) {
    _DAT_00663318 = 0;
    _DAT_006632b8 = 0x427fffe6;
    _DAT_006632d8 = 0x427fffe6;
    _DAT_006632f8 = 0;
  }
  else {
    _DAT_006632b8 = 0;
    _DAT_006632d8 = 0;
    _DAT_006632f8 = 0x427fffe6;
    _DAT_00663318 = 0x427fffe6;
  }
  _DAT_006632dc = 0x427fffe6;
  _DAT_006632fc = 0x427fffe6;
LAB_0046cdbf:
  local_98[0] = (SpriteS1 *)FUN_004bf6b0(*param_2 & 0x3ff);
  if ((ushort)local_98[0] != 0) {
    if ((*param_2 & 0x1000) != 0) {
      _DAT_006633b8 = _DAT_006633b8 | 0x80;
    }
    uVar9 = (uint)*(byte *)((int)param_1 + 0xd);
    puVar14 = &DAT_006632a0;
    uVar7 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_98);
    (*(code *)gbh_DrawTile)
              (gTimeDayAndNight | _DAT_006633b8,uVar7,puVar14,uVar9);
    *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046ce30: EntityManager::sub_46CE30
// IDA: EntityManager::sub_46CE30
// Ghidra: FUN_0046ce30
void gta2::EntityManager_sub_46CE30(void *param_1,ushort *param_2)
{
  float fVar1;
  ushort *puVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pSVar4;
  Model *pMVar5;
  void *pvVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  float10 fVar12;
  PedStats *pPVar13;
  undefined *puVar14;
  undefined *puVar15;
  int *piVar16;
  SpriteS1 *local_60 [8];
  undefined1 local_40 [20];
  undefined1 local_2c [16];
  undefined1 local_1c [24];
  undefined1 local_4 [4];
  
  fVar1 = _DAT_006633a8;
  if (gSkipTop != 0) {
    return;
  }
  if (DAT_006633b2 == '\x03') {
    pMVar5 = (Model *)FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,
                                   (PedStats *)&DAT_006636f0,&DAT_006632a0);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_00663300);
      _DAT_0066331c = fVar1;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_2c + 4);
      piVar16 = (int *)&DAT_006633b4;
      gta2::S202_sub_41F980((SpriteS1 *)(local_2c + 8),_DAT_006633b4 - (int)_DAT_006633a8);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar16);
      local_60[0] = pSVar3->FirstElement;
      puVar14 = &DAT_00663300;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_2c + 0xc),
                          (S127 *)local_60);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                 (PedStats *)pSVar3,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_1c,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_0066331c = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_00663304 < _DAT_006632a4) {
      return;
    }
    puVar14 = &DAT_006632c0;
    pPVar13 = (PedStats *)&DAT_006636f0;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_1c + 4),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,pPVar13,puVar14);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_006632c0;
      puVar11 = (undefined4 *)&DAT_006632e0;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_006632fc = 63.9999;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_1c + 8);
      piVar16 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_1c + 0xc),(int)pMVar5);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar16);
      local_60[0] = pSVar3->FirstElement;
      puVar14 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_1c + 0x10)
                          ,(S127 *)local_60);
      pPVar13 = (PedStats *)&DAT_006636f0;
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_1c + 0x14),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar4,pPVar13,(PedStats *)pSVar3,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_4,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632fc = (float)((float10)63.9999 - fVar12);
    }
  }
  else {
    if (DAT_006633b2 != '\x04') {
      FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                   &DAT_006632a0);
      FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_00663300);
      if (_DAT_00663304 < _DAT_006632a4) {
        return;
      }
      puVar14 = &DAT_006632c0;
      pPVar13 = (PedStats *)&DAT_006636f0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_60 + 1),
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)pSVar3,pPVar13,puVar14);
      puVar15 = &DAT_006632e0;
      puVar14 = &DAT_006636f0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_60 + 2),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar3,puVar14,puVar15);
      _DAT_006633b8 = *(uint *)(&DAT_00593114 + (uint)(*param_2 >> 0xd) * 4);
      goto LAB_0046d2f1;
    }
    if (_DAT_006633a8 == 0.0) {
      puVar15 = &DAT_006632e0;
      puVar14 = &DAT_006636f0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_60 + 3),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar3,puVar14,puVar15);
      _DAT_006632fc = fVar1;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_60 + 4);
      piVar16 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)(_DAT_006633b4 - (int)_DAT_006633a8);
      gta2::S202_sub_41F980((SpriteS1 *)(local_60 + 5),(int)pMVar5);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar16);
      local_60[0] = pSVar3->FirstElement;
      puVar14 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_60 + 6),
                          (S127 *)local_60);
      pPVar13 = (PedStats *)&DAT_006636f0;
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_60 + 7),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar4,pPVar13,(PedStats *)pSVar3,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_40,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632fc = (float)((float10)63.9999 - fVar12);
    }
    puVar14 = &DAT_006632c0;
    pPVar13 = (PedStats *)&DAT_006636f0;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_40 + 4),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,pPVar13,puVar14);
    if (_DAT_006632e4 < _DAT_006632c4) {
      return;
    }
    FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                 &DAT_006632a0);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_006632a0;
      puVar11 = (undefined4 *)&DAT_00663300;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_0066331c = 63.9999;
    }
    else {
      pSVar3 = (SpriteS1 *)(local_40 + 8);
      piVar16 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_40 + 0xc),(int)pMVar5);
      pSVar3 = gta2::S122_sub_401BF0(pMVar5,pSVar3,piVar16);
      local_60[0] = pSVar3->FirstElement;
      puVar14 = &DAT_00663300;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_40 + 0x10)
                          ,(S127 *)local_60);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                 (PedStats *)pSVar3,puVar14);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_2c,(int *)local_60);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_0066331c = (float)((float10)63.9999 - fVar12);
    }
  }
  _DAT_006633b8 = 0x4005;
  if ((*param_2 & 0x2000) == 0) {
    _DAT_00663318 = 0x427fffe6;
    _DAT_006632b8 = 0x427fffe6;
    _DAT_006632d8 = 0;
    _DAT_006632f8 = 0;
  }
  else {
    _DAT_006632b8 = 0;
    _DAT_006632d8 = 0x427fffe6;
    _DAT_006632f8 = 0x427fffe6;
    _DAT_00663318 = 0;
  }
  _DAT_006632bc = 0x427fffe6;
  _DAT_006632dc = 0x427fffe6;
LAB_0046d2f1:
  puVar2 = param_2;
  param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
  if ((short)param_2 != 0) {
    if ((*puVar2 & 0x1000) != 0) {
      _DAT_006633b8 = _DAT_006633b8 | 0x80;
    }
    uVar9 = (uint)*(byte *)((int)param_1 + 0xf);
    puVar14 = &DAT_006632a0;
    uVar7 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2);
    (*(code *)gbh_DrawTile)
              (gTimeDayAndNight | _DAT_006633b8,uVar7,puVar14,uVar9);
    *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046d360: EntityManager::sub_46D360
// IDA: EntityManager::sub_46D360
// Ghidra: FUN_0046d360
void gta2::EntityManager_sub_46D360(void *param_1,ushort *param_2)
{
  bool bVar1;
  SpriteS1 *pSVar2;
  int *piVar3;
  void *pvVar4;
  short *psVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar6;
  undefined4 uVar7;
  Player *self;
  PedStats *pS17;
  undefined *puVar8;
  undefined *puVar9;
  undefined2 local_10 [2];
  short local_c;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_c);
  puVar8 = &DAT_006632a0;
  pS17 = (PedStats *)&DAT_006636f0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_10,
                      (S127 *)&DAT_00663450);
  FUN_0046bdf0(param_1,(PedStats *)pSVar2,pS17,puVar8);
  puVar9 = &DAT_006632c0;
  puVar8 = &DAT_006636f0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_10,
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(pSVar2,puVar8,puVar9);
  piVar3 = (int *)FUN_0046bb20(_DAT_006632c0 - _DAT_006632a0);
  pvVar4 = (void *)FUN_0046bb20(_DAT_006632c4 - _DAT_006632a4);
  psVar5 = gta2::Player_FUN_0040e8d0(self,local_10,pvVar4,piVar3);
  local_c = *psVar5;
  bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&local_c,(short *)&DAT_00663538);
  if ((CONCAT31(extraout_var,bVar1) == 0) &&
     (bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&local_c,(short *)&DAT_00663688),
     CONCAT31(extraout_var_00,bVar1) == 0)) {
    return;
  }
  puVar8 = &DAT_006632e0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(&gS17_V1,pSVar2,puVar8);
  puVar8 = &DAT_00663300;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                      (S127 *)&DAT_00663450);
  FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar2,puVar8);
  _DAT_006633b8 = *(uint *)(&DAT_00593194 + (uint)(*param_2 >> 0xd) * 4);
  param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
  if ((short)param_2 != 0) {
    uVar6 = (uint)*(byte *)((int)param_1 + 0x10);
    puVar8 = &DAT_006632a0;
    uVar7 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2);
    (*(code *)gbh_DrawTile)(gTimeDayAndNight | _DAT_006633b8,uVar7,puVar8,uVar6)
    ;
    *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046d4f0: EntityManager::sub_46D4F0
// IDA: EntityManager::sub_46D4F0
// Ghidra: FUN_0046d4f0
void gta2::EntityManager_sub_46D4F0(void *param_1,ushort *param_2)
{
  bool bVar1;
  int *piVar2;
  void *pvVar3;
  short *psVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  SpriteS1 *pSVar5;
  SpriteS1 *pSVar6;
  uint uVar7;
  undefined4 uVar8;
  Player *self;
  undefined *puVar9;
  undefined2 local_e;
  short local_c;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_c);
  FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632a0);
  FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
               &DAT_006632c0);
  piVar2 = (int *)FUN_0046bb20(_DAT_006632c0 - _DAT_006632a0);
  pvVar3 = (void *)FUN_0046bb20(_DAT_006632c4 - _DAT_006632a4);
  psVar4 = gta2::Player_FUN_0040e8d0(self,&local_e,pvVar3,piVar2);
  local_c = *psVar4;
  bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&local_c,(short *)&DAT_006634b8);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&local_c,(short *)&DAT_006635cc);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      puVar9 = &DAT_006632e0;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                          (S127 *)&DAT_00663450);
      pSVar6 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&stack0xfffffff8,
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)pSVar6,(PedStats *)pSVar5,puVar9);
      puVar9 = &DAT_00663300;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                          (S127 *)&DAT_00663450);
      pSVar6 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&stack0xfffffff8,
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar6,pSVar5,puVar9);
      _DAT_006633b8 = *(uint *)(&DAT_005931b4 + (uint)(*param_2 >> 0xd) * 4);
      param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
      if ((short)param_2 != 0) {
        uVar7 = (uint)*(byte *)((int)param_1 + 0x11);
        puVar9 = &DAT_006632a0;
        uVar8 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar8,puVar9,uVar7);
        *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
      }
    }
  }
  return;
}


// 0x0046d680: EntityManager::sub_46D680
// IDA: EntityManager::sub_46D680
// Ghidra: FUN_0046d680
void gta2::EntityManager_sub_46D680(void *param_1,ushort *param_2)
{
  bool bVar1;
  int *piVar2;
  void *pvVar3;
  short *psVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  SpriteS1 *pSVar5;
  SpriteS1 *pSVar6;
  uint uVar7;
  undefined4 uVar8;
  Player *self;
  undefined *puVar9;
  undefined2 local_e;
  short local_c;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_c);
  FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
               &DAT_006632a0);
  FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632c0);
  piVar2 = (int *)FUN_0046bb20(_DAT_006632c0 - _DAT_006632a0);
  pvVar3 = (void *)FUN_0046bb20(_DAT_006632c4 - _DAT_006632a4);
  psVar4 = gta2::Player_FUN_0040e8d0(self,&local_e,pvVar3,piVar2);
  local_c = *psVar4;
  bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&local_c,(short *)&DAT_006634b8);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&local_c,(short *)&DAT_006635cc);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      puVar9 = &DAT_006632e0;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                          (S127 *)&DAT_00663450);
      pSVar6 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&stack0xfffffff8,
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar6,pSVar5,puVar9);
      puVar9 = &DAT_00663300;
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                          (S127 *)&DAT_00663450);
      pSVar6 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&stack0xfffffff8,
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)pSVar6,(PedStats *)pSVar5,puVar9);
      _DAT_006633b8 = *(uint *)(&DAT_00593194 + (uint)(*param_2 >> 0xd) * 4);
      param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
      if ((short)param_2 != 0) {
        uVar7 = (uint)*(byte *)((int)param_1 + 0x12);
        puVar9 = &DAT_006632a0;
        uVar8 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar8,puVar9,uVar7);
        *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
      }
    }
  }
  return;
}


// 0x0046d810: EntityManager::sub_46D810
// IDA: EntityManager::sub_46D810
// Ghidra: FUN_0046d810
void gta2::EntityManager_sub_46D810(void *param_1,ushort *param_2)
{
  bool bVar1;
  SpriteS1 *pSVar2;
  int *piVar3;
  void *pvVar4;
  short *psVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  uint uVar6;
  undefined4 uVar7;
  Player *self;
  undefined *puVar8;
  PedStats *pS17;
  undefined *puVar9;
  undefined2 local_10 [2];
  short local_c;
  
  gta2::CarSystemManager_SetIndexDefautCarManager((CarSystemManager *)&local_c);
  puVar9 = &DAT_006632a0;
  puVar8 = &DAT_006636f0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_10,
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(pSVar2,puVar8,puVar9);
  puVar8 = &DAT_006632c0;
  pS17 = (PedStats *)&DAT_006636f0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_10,
                      (S127 *)&DAT_00663450);
  FUN_0046bdf0(param_1,(PedStats *)pSVar2,pS17,puVar8);
  piVar3 = (int *)FUN_0046bb20(_DAT_006632c0 - _DAT_006632a0);
  pvVar4 = (void *)FUN_0046bb20(_DAT_006632c4 - _DAT_006632a4);
  psVar5 = gta2::Player_FUN_0040e8d0(self,local_10,pvVar4,piVar3);
  local_c = *psVar5;
  bVar1 = gta2::CarSystemManager_less_than((CarSystemManager *)&local_c,(short *)&DAT_00663538);
  if ((CONCAT31(extraout_var,bVar1) == 0) &&
     (bVar1 = gta2::CarSystemManager_greater_than((CarSystemManager *)&local_c,(short *)&DAT_00663688),
     CONCAT31(extraout_var_00,bVar1) == 0)) {
    return;
  }
  puVar8 = &DAT_006632e0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                      (S127 *)&DAT_00663450);
  FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar2,puVar8);
  puVar8 = &DAT_00663300;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&stack0xfffffffc,
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(&gS17_V1,pSVar2,puVar8);
  _DAT_006633b8 = *(uint *)(&DAT_005931b4 + (uint)(*param_2 >> 0xd) * 4);
  param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
  if ((short)param_2 != 0) {
    uVar6 = (uint)*(byte *)((int)param_1 + 0x13);
    puVar8 = &DAT_006632a0;
    uVar7 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2);
    (*(code *)gbh_DrawTile)(gTimeDayAndNight | _DAT_006633b8,uVar7,puVar8,uVar6)
    ;
    *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046d9a0: EntityManager::sub_46D9A0
// IDA: EntityManager::sub_46D9A0
// Ghidra: FUN_0046d9a0
void gta2::EntityManager_sub_46D9A0(void *param_1,ushort *param_2)
{
  float fVar1;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pSVar4;
  Model *pMVar5;
  void *pvVar6;
  undefined4 uVar7;
  int iVar8;
  uint uVar9;
  undefined4 *puVar10;
  undefined4 *puVar11;
  float10 fVar12;
  undefined *puVar13;
  int *piVar14;
  SpriteS1 *local_98 [7];
  undefined1 local_7c [56];
  undefined1 local_44 [44];
  undefined1 local_18 [20];
  undefined1 local_4 [4];
  
  if (gSkipBottom != 0) {
    return;
  }
  if (DAT_006633b2 == '\x03') {
    puVar13 = &DAT_00663300;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 8),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar2,puVar13);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      puVar13 = &DAT_006632a0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 0x10)
                          ,(S127 *)&DAT_00663450);
      FUN_0046bd40(&gS17_V1,pSVar2,puVar13);
      _DAT_006632bc = fVar1;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_7c + 0x18);
      piVar14 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)(_DAT_006633b4 - (int)_DAT_006633a8);
      gta2::S202_sub_41F980((SpriteS1 *)(local_7c + 0x20),(int)pMVar5);
      pSVar2 = gta2::S122_sub_401BF0(pMVar5,pSVar2,piVar14);
      local_98[0] = pSVar2->FirstElement;
      puVar13 = &DAT_006632a0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_7c + 0x28)
                          ,(S127 *)local_98);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 0x30)
                          ,(S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar3,
                 (PedStats *)pSVar2,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_44,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632bc = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_00663304 < _DAT_006632a4) {
      return;
    }
    puVar13 = &DAT_006632e0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_44 + 8),
                        (S127 *)&DAT_00663450);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0x10),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar13);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_006632e0;
      puVar11 = (undefined4 *)&DAT_006632c0;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_006632dc = 63.9999;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_44 + 0x18);
      piVar14 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_44 + 0x20),(int)pMVar5);
      pSVar2 = gta2::S122_sub_401BF0(pMVar5,pSVar2,piVar14);
      local_98[0] = pSVar2->FirstElement;
      puVar13 = &DAT_006632c0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_44 + 0x28)
                          ,(S127 *)local_98);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_18 + 4),
                          (S127 *)&DAT_00663450);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 0xc),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar4,(PedStats *)pSVar3,
                 (PedStats *)pSVar2,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_4,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632dc = (float)((float10)63.9999 - fVar12);
    }
  }
  else {
    if (DAT_006633b2 != '\x04') {
      puVar13 = &DAT_00663300;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_44 + 0x1c)
                          ,(S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar2,puVar13);
      puVar13 = &DAT_006632a0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 0x34)
                          ,(S127 *)&DAT_00663450);
      FUN_0046bd40(&gS17_V1,pSVar2,puVar13);
      if (_DAT_00663304 < _DAT_006632a4) {
        return;
      }
      puVar13 = &DAT_006632e0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_98 + 4),
                          (S127 *)&DAT_00663450);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 0x10),
                          (S127 *)&DAT_00663450);
      FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar13);
      puVar13 = &DAT_006632c0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_98 + 6),
                          (S127 *)&DAT_00663450);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 4),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar3,pSVar2,puVar13);
      _DAT_006633b8 = *(uint *)(&DAT_00593134 + (uint)(*param_2 >> 0xd) * 4);
      goto LAB_0046df67;
    }
    puVar13 = &DAT_006632e0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 4),
                        (S127 *)&DAT_00663450);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0x24),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar13);
    fVar1 = _DAT_006633a8;
    if (_DAT_006633a8 == 0.0) {
      puVar13 = &DAT_006632c0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 0xc),
                          (S127 *)&DAT_00663450);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_44 + 0xc),
                          (S127 *)&DAT_00663450);
      FUN_0046bd40(pSVar3,pSVar2,puVar13);
      _DAT_006632dc = fVar1;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_7c + 0x14);
      piVar14 = (int *)&DAT_006633b4;
      pSVar3 = pSVar2;
      gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 8),_DAT_006633b4 - (int)_DAT_006633a8);
      pSVar2 = gta2::S122_sub_401BF0((Model *)pSVar2,pSVar3,piVar14);
      local_98[0] = pSVar2->FirstElement;
      puVar13 = &DAT_006632c0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_7c + 0x1c)
                          ,(S127 *)local_98);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_44 + 0x14)
                          ,(S127 *)&DAT_00663450);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_7c + 0x24),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)pSVar4,(PedStats *)pSVar3,
                 (PedStats *)pSVar2,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_18,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632dc = (float)((float10)63.9999 - fVar12);
    }
    if (_DAT_006632e4 < _DAT_006632c4) {
      return;
    }
    puVar13 = &DAT_00663300;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_7c + 0x2c),
                        (S127 *)&DAT_00663450);
    FUN_0046bdf0(param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar2,puVar13);
    if (fVar1 == (float)(_DAT_006633b4 + -1)) {
      puVar10 = (undefined4 *)&DAT_00663300;
      puVar11 = (undefined4 *)&DAT_006632a0;
      for (iVar8 = 8; iVar8 != 0; iVar8 = iVar8 + -1) {
        *puVar11 = *puVar10;
        puVar10 = puVar10 + 1;
        puVar11 = puVar11 + 1;
      }
      _DAT_006632bc = 63.9999;
    }
    else {
      pSVar2 = (SpriteS1 *)(local_98 + 1);
      piVar14 = (int *)&DAT_006633b4;
      pMVar5 = (Model *)((_DAT_006633b4 - (int)fVar1) + -1);
      gta2::S202_sub_41F980((SpriteS1 *)(local_98 + 2),(int)pMVar5);
      pSVar2 = gta2::S122_sub_401BF0(pMVar5,pSVar2,piVar14);
      local_98[0] = pSVar2->FirstElement;
      puVar13 = &DAT_006632a0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)(local_98 + 3),
                          (S127 *)local_98);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_98 + 5),
                          (S127 *)&DAT_00663450);
      MatrixTransform3Advanced
                (param_1,(PedStats *)&gS17_V1,(PedStats *)pSVar3,
                 (PedStats *)pSVar2,puVar13);
      pvVar6 = gta2::WorldCoordinateToScreenCoord
                         (&DAT_00663730,local_7c,(int *)local_98);
      fVar12 = gta2::PedStats_EncodedFloatToRegularFloat(pvVar6);
      _DAT_006632bc = (float)((float10)63.9999 - fVar12);
    }
  }
  _DAT_006633b8 = 0x4005;
  if ((*param_2 & 0x2000) == 0) {
    _DAT_00663318 = 0;
    _DAT_006632b8 = 0;
    _DAT_006632d8 = 0x427fffe6;
    _DAT_006632f8 = 0x427fffe6;
  }
  else {
    _DAT_006632b8 = 0x427fffe6;
    _DAT_006632d8 = 0;
    _DAT_006632f8 = 0;
    _DAT_00663318 = 0x427fffe6;
  }
  _DAT_006632fc = 0x427fffe6;
  _DAT_0066331c = 0x427fffe6;
LAB_0046df67:
  local_98[0] = (SpriteS1 *)FUN_004bf6b0(*param_2 & 0x3ff);
  if ((ushort)local_98[0] != 0) {
    if ((*param_2 & 0x1000) != 0) {
      _DAT_006633b8 = _DAT_006633b8 | 0x80;
    }
    uVar9 = (uint)*(byte *)((int)param_1 + 0xe);
    puVar13 = &DAT_006632a0;
    uVar7 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_98);
    (*(code *)gbh_DrawTile)
              (gTimeDayAndNight | _DAT_006633b8,uVar7,puVar13,uVar9);
    *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
  }
  return;
}


// 0x0046dfe0: EntityManager::sub_46DFE0
// IDA: EntityManager::sub_46DFE0
// Ghidra: FUN_0046dfe0
void gta2::EntityManager_sub_46DFE0(void *self)
{
  uint uVar1;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  int iVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined *puVar9;
  undefined *puVar10;
  SpriteS1 *local_8 [2];
  
  if (gSkipLid != 0) {
    return;
  }
  FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632a0);
  puVar10 = &DAT_006632c0;
  puVar9 = &DAT_006636f0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_8,
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(pSVar2,puVar9,puVar10);
  puVar9 = &DAT_006632e0;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)local_8,
                      (S127 *)&DAT_00663450);
  pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_8 + 1),
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(pSVar3,pSVar2,puVar9);
  puVar9 = &DAT_00663300;
  pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_8 + 1),
                      (S127 *)&DAT_00663450);
  FUN_0046bd40(&gS17_V1,pSVar2,puVar9);
  local_8[0] = (SpriteS1 *)FUN_004bf6b0(_DAT_006633bc & 0x3ff);
  uVar1 = _DAT_006633bc;
  if ((short)local_8[0] == 0) {
    return;
  }
  switch(DAT_005930d0) {
  case 0:
    puVar7 = (undefined4 *)&DAT_006632c0;
    puVar8 = (undefined4 *)&DAT_006632a0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663340;
    puVar8 = (undefined4 *)&DAT_00663320;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_006632e0;
    puVar8 = (undefined4 *)&DAT_006632c0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663360;
    puVar8 = (undefined4 *)&DAT_00663340;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663300;
    puVar8 = (undefined4 *)&DAT_006632e0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663380;
    puVar8 = (undefined4 *)&DAT_00663360;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_006632a0;
    puVar8 = (undefined4 *)&DAT_00663300;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663320;
    puVar8 = (undefined4 *)&DAT_00663380;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    _DAT_006633b8 = *(uint *)(&DAT_005931b4 + ((uVar1 & 0xffff) >> 0xd) * 4);
    break;
  case 1:
    puVar7 = (undefined4 *)&DAT_006632e0;
    puVar8 = (undefined4 *)&DAT_006632c0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663360;
    puVar8 = (undefined4 *)&DAT_00663340;
    goto LAB_0046e23a;
  case 2:
    puVar7 = (undefined4 *)&DAT_006632c0;
    puVar8 = (undefined4 *)&DAT_006632e0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663340;
    puVar8 = (undefined4 *)&DAT_00663360;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_006632a0;
    puVar8 = (undefined4 *)&DAT_006632c0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663320;
    puVar8 = (undefined4 *)&DAT_00663340;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663300;
    puVar8 = (undefined4 *)&DAT_006632a0;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663380;
    puVar8 = (undefined4 *)&DAT_00663320;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    _DAT_006633b8 = *(uint *)(&DAT_00593194 + ((uVar1 & 0xffff) >> 0xd) * 4);
    break;
  case 3:
    puVar7 = (undefined4 *)&DAT_006632a0;
    puVar8 = (undefined4 *)&DAT_00663300;
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    puVar7 = (undefined4 *)&DAT_00663320;
    puVar8 = (undefined4 *)&DAT_00663380;
LAB_0046e23a:
    for (iVar6 = 8; iVar6 != 0; iVar6 = iVar6 + -1) {
      *puVar8 = *puVar7;
      puVar7 = puVar7 + 1;
      puVar8 = puVar8 + 1;
    }
    _DAT_006633b8 = *(uint *)(&DAT_005931d4 + ((uVar1 & 0xffff) >> 0xd) * 4);
    break;
  case 0xff:
    _DAT_006633b8 =
         *(uint *)(&DAT_00593154 + ((_DAT_006633bc & 0xffff) >> 0xd) * 4);
  }
  if ((uVar1 & 0x1000) != 0) {
    _DAT_006633b8 = _DAT_006633b8 | 0x80;
  }
  uVar4 = FUN_0046b5e0(uVar1 >> 10 & 3);
  puVar9 = &DAT_006632a0;
  uVar5 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_8);
  (*(code *)gbh_DrawTile)(gTimeDayAndNight | _DAT_006633b8,uVar5,puVar9,uVar4);
  *(int *)((int)self + 0x2f00) = *(int *)((int)self + 0x2f00) + 1;
  return;
}


// 0x0046e490: EntityManager::sub_46E490
// IDA: EntityManager::sub_46E490
// Ghidra: ---
void gta2::EntityManager_sub_46E490(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int v5; // ecx
  int *v6; // [esp-8h] [ebp-18h]
  char a3; // [esp+7h] [ebp-9h] BYREF
  char v8; // [esp+8h] [ebp-8h] BYREF
  char v9; // [esp+Ch] [ebp-4h] BYREF

  if ( word_6633A4[0] )
  {
    unk_6633B2 = 2;
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
  }
  if ( word_6633B0 )
  {
    unk_6633B2 = 4;
    gta2::EntityManager_sub_46D9A0(self, (int)&word_6633B0);
  }
  if ( word_6633C4[0] )
  {
    v6 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    v2 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v9, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, v2, v6, &a4);
    unk_6632B8 = 1107296256;
    flt_6632BC[0] = 0.0;
    v3 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v9, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, v3, &unk_6632C0);
    unk_6632D8 = 1115684838;
    flt_6632DC = 63.999901;
    v4 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v9, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, v4, &unk_6636F0.field_0, &unk_6632E0);
    flt_6632F8 = 0.0;
    flt_6632FC = 63.999901;
    LOBYTE(v5) = self->field_18;
    a3 = 0;
    gta2::EntityManager_sub_46C210(self, word_6633C4, &a3, v5);
  }
}


// 0x0046e5c0: EntityManager::sub_46E5C0
// IDA: EntityManager::sub_46E5C0
// Ghidra: ---
void gta2::EntityManager_sub_46E5C0(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int v4; // eax
  int *v5; // [esp-8h] [ebp-18h]
  char a3; // [esp+7h] [ebp-9h] BYREF
  char v7; // [esp+8h] [ebp-8h] BYREF
  char v8; // [esp+Ch] [ebp-4h] BYREF

  if ( word_6633C4[0] )
  {
    unk_6633B2 = 2;
    gta2::EntityManager_sub_46C2C0(self);
  }
  if ( word_6633B0 )
  {
    unk_6633B2 = 3;
    gta2::EntityManager_sub_46D9A0(self, (int)&word_6633B0);
  }
  if ( word_6633A4[0] )
  {
    v2 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, v2, &a4);
    unk_6632B8 = 1107296256;
    flt_6632BC[0] = 0.0;
    gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, &unk_6636F0.field_0, &unk_6632C0);
    unk_6632D8 = 1115684838;
    flt_6632DC = 63.999901;
    v5 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    v3 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, v3, v5, &unk_6632E0);
    flt_6632F8 = 0.0;
    flt_6632FC = 63.999901;
    LOBYTE(v4) = self->field_19;
    a3 = 0;
    gta2::EntityManager_sub_46C210(self, word_6633A4, &a3, v4);
  }
}


// 0x0046e6e0: EntityManager::sub_46E6E0
// IDA: EntityManager::sub_46E6E0
// Ghidra: ---
void gta2::EntityManager_sub_46E6E0(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int v4; // eax
  int *v5; // [esp-8h] [ebp-18h]
  char a3; // [esp+7h] [ebp-9h] BYREF
  char v7; // [esp+8h] [ebp-8h] BYREF
  char v8; // [esp+Ch] [ebp-4h] BYREF

  if ( word_6633A4[0] )
  {
    unk_6633B2 = 1;
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
  }
  if ( word_6633C0[0] )
  {
    unk_6633B2 = 4;
    gta2::EntityManager_sub_46CE30(self, (int)word_6633C0);
  }
  if ( word_6633C4[0] )
  {
    v2 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, v2, &unk_6636F0.field_0, &a4);
    unk_6632B8 = 1107296256;
    flt_6632BC[0] = 0.0;
    v5 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    v3 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, v3, v5, &unk_6632C0);
    unk_6632D8 = 1115684838;
    flt_6632DC = 63.999901;
    gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, &unk_6636F0.field_0, &unk_6632E0);
    flt_6632F8 = 0.0;
    flt_6632FC = 63.999901;
    LOBYTE(v4) = self->field_1A;
    a3 = 0;
    gta2::EntityManager_sub_46C210(self, word_6633C4, &a3, v4);
  }
}


// 0x0046e800: EntityManager::sub_46E800
// IDA: EntityManager::sub_46E800
// Ghidra: ---
void gta2::EntityManager_sub_46E800(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int v4; // edx
  char a3; // [esp+7h] [ebp-5h] BYREF
  char v6; // [esp+8h] [ebp-4h] BYREF

  if ( word_6633C4[0] )
  {
    unk_6633B2 = 1;
    gta2::EntityManager_sub_46C2C0(self);
  }
  if ( word_6633C0[0] )
  {
    unk_6633B2 = 3;
    gta2::EntityManager_sub_46CE30(self, (int)word_6633C0);
  }
  if ( word_6633A4[0] )
  {
    gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, &unk_6636F0.field_0, &a4);
    unk_6632B8 = 1107296256;
    flt_6632BC[0] = 0.0;
    v2 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v6, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, v2, &unk_6636F0.field_0, &unk_6632C0);
    unk_6632D8 = 1115684838;
    flt_6632DC = 63.999901;
    v3 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v6, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, v3, &unk_6632E0);
    flt_6632F8 = 0.0;
    flt_6632FC = 63.999901;
    LOBYTE(v4) = self->field_1B;
    a3 = 0;
    gta2::EntityManager_sub_46C210(self, word_6633A4, &a3, v4);
  }
}


// 0x0046e910: EntityManager::sub_46E910
// IDA: EntityManager::sub_46E910
// Ghidra: ---
void gta2::EntityManager_sub_46E910(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int v4; // edx
  char a3; // [esp+7h] [ebp-5h] BYREF
  char v6; // [esp+8h] [ebp-4h] BYREF

  if ( word_6633A4[0] )
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
  if ( word_6633C4[0] )
  {
    v2 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v6, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, v2, &unk_6636F0.field_0, &a4);
    unk_6632B8 = 0;
    flt_6632BC[0] = 0.0;
    gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, &unk_6636F0.field_0, &unk_6632C0);
    unk_6632D8 = 1107296256;
    flt_6632DC = 63.999901;
    v3 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v6, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, v3, &unk_6632E0);
    flt_6632F8 = 63.999901;
    flt_6632FC = 0.0;
    LOBYTE(v4) = self->field_18;
    a3 = 1;
    gta2::EntityManager_sub_46C210(self, word_6633C4, &a3, v4);
  }
  if ( word_6633B0 )
    gta2::EntityManager_sub_46D9A0(self, (int)&word_6633B0);
  if ( word_6633BC )
  {
    byte_5930D0 = 0;
    gta2::EntityManager_sub_46DFE0(self);
    byte_5930D0 = -1;
  }
}


// 0x0046ea30: EntityManager::sub_46EA30
// IDA: EntityManager::sub_46EA30
// Ghidra: ---
void gta2::EntityManager_sub_46EA30(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int v4; // eax
  int *v5; // [esp-8h] [ebp-18h]
  char a3; // [esp+7h] [ebp-9h] BYREF
  char v7; // [esp+8h] [ebp-8h] BYREF
  char v8; // [esp+Ch] [ebp-4h] BYREF

  if ( word_6633C4[0] )
    gta2::EntityManager_sub_46C2C0(self);
  if ( word_6633A4[0] )
  {
    v5 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    v2 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, v2, v5, &a4);
    unk_6632B8 = 0;
    flt_6632BC[0] = 0.0;
    v3 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, v3, &unk_6636F0.field_0, &unk_6632C0);
    unk_6632D8 = 1107296256;
    flt_6632DC = 63.999901;
    gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, &unk_6636F0.field_0, &unk_6632E0);
    flt_6632F8 = 63.999901;
    flt_6632FC = 0.0;
    LOBYTE(v4) = self->field_19;
    a3 = 1;
    gta2::EntityManager_sub_46C210(self, word_6633A4, &a3, v4);
  }
  if ( word_6633B0 )
    gta2::EntityManager_sub_46D9A0(self, (int)&word_6633B0);
  if ( word_6633BC )
  {
    byte_5930D0 = 1;
    gta2::EntityManager_sub_46DFE0(self);
    byte_5930D0 = -1;
  }
}


// 0x0046eb60: EntityManager::sub_46EB60
// IDA: EntityManager::sub_46EB60
// Ghidra: ---
void gta2::EntityManager_sub_46EB60(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int v4; // eax
  int *v5; // [esp-8h] [ebp-18h]
  char a3; // [esp+7h] [ebp-9h] BYREF
  char v7; // [esp+8h] [ebp-8h] BYREF
  char v8; // [esp+Ch] [ebp-4h] BYREF

  if ( word_6633C4[0] )
  {
    gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, &unk_6636F0.field_0, &a4);
    unk_6632B8 = 0;
    flt_6632BC[0] = 0.0;
    v2 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, v2, &unk_6632C0);
    unk_6632D8 = 1107296256;
    flt_6632DC = 63.999901;
    v5 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v7, (PublicTransport *)&dword_663450);
    v3 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, v3, v5, &unk_6632E0);
    flt_6632F8 = 63.999901;
    flt_6632FC = 0.0;
    LOBYTE(v4) = self->field_1A;
    a3 = 1;
    gta2::EntityManager_sub_46C210(self, word_6633C4, &a3, v4);
  }
  if ( word_6633A4[0] )
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
  if ( word_6633C0[0] )
    gta2::EntityManager_sub_46CE30(self, (int)word_6633C0);
  if ( word_6633BC )
  {
    byte_5930D0 = 3;
    gta2::EntityManager_sub_46DFE0(self);
    byte_5930D0 = -1;
  }
}


// 0x0046ec90: EntityManager::sub_46EC90
// IDA: EntityManager::sub_46EC90
// Ghidra: ---
void gta2::EntityManager_sub_46EC90(struct EntityManager *self)
{
  int *v2; // eax
  int *v3; // eax
  int *v4; // eax
  int v5; // ecx
  int *v6; // [esp-8h] [ebp-18h]
  char a3; // [esp+7h] [ebp-9h] BYREF
  char v8; // [esp+8h] [ebp-8h] BYREF
  char v9; // [esp+Ch] [ebp-4h] BYREF

  if ( word_6633C4[0] )
    gta2::EntityManager_sub_46C2C0(self);
  if ( word_6633A4[0] )
  {
    v2 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, v2, &a4);
    unk_6632B8 = 0;
    flt_6632BC[0] = 0.0;
    v6 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v8, (PublicTransport *)&dword_663450);
    v3 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v9, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BDF0(self, v3, v6, &unk_6632C0);
    unk_6632D8 = 1107296256;
    flt_6632DC = 63.999901;
    v4 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v9, (PublicTransport *)&dword_663450);
    gta2::EntityManager_sub_46BD40(self, v4, &unk_6636F0.field_0, &unk_6632E0);
    flt_6632F8 = 63.999901;
    flt_6632FC = 0.0;
    LOBYTE(v5) = self->field_1B;
    a3 = 1;
    gta2::EntityManager_sub_46C210(self, word_6633A4, &a3, v5);
  }
  if ( word_6633C0[0] )
    gta2::EntityManager_sub_46CE30(self, (int)word_6633C0);
  if ( word_6633BC )
  {
    byte_5930D0 = 2;
    gta2::EntityManager_sub_46DFE0(self);
    byte_5930D0 = -1;
  }
}


// 0x0046edd0: EntityManager::sub_46EDD0
// IDA: EntityManager::sub_46EDD0
// Ghidra: FUN_0046edd0
void gta2::EntityManager_sub_46EDD0(void *self)
{
  DAT_006633b2 = 0;
  switch(*(byte *)(_DAT_00663298 + 0xb) & 0xfc) {
  case 0xb4:
    break;
  case 0xb8:
    if (_DAT_006633c4 != 0) {
      FUN_0046c2c0(&DAT_006633c4);
    }
    if (_DAT_006633a4 != 0) {
      FUN_0046d4f0(&DAT_006633a4);
    }
    if (_DAT_006633b0 != 0) {
      FUN_0046d9a0(&DAT_006633b0);
    }
    if (_DAT_006633bc != 0) {
      DAT_005930d0 = 1;
      FUN_0046dfe0(self);
      DAT_005930d0 = 0xff;
    }
    return;
  case 0xbc:
    if (_DAT_006633c4 != 0) {
      FUN_0046d680(&DAT_006633c4);
    }
    if (_DAT_006633a4 != 0) {
      FUN_0046c7f0(&DAT_006633a4);
    }
    if (_DAT_006633c0 != 0) {
      FUN_0046ce30(&DAT_006633c0);
    }
    if (_DAT_006633bc != 0) {
      DAT_005930d0 = 3;
      FUN_0046dfe0(self);
      DAT_005930d0 = 0xff;
    }
    return;
  case 0xc0:
    if (_DAT_006633c4 != 0) {
      FUN_0046c2c0(&DAT_006633c4);
    }
    if (_DAT_006633a4 != 0) {
      FUN_0046d810(&DAT_006633a4);
    }
    if (_DAT_006633c0 != 0) {
      FUN_0046ce30(&DAT_006633c0);
    }
    if (_DAT_006633bc != 0) {
      DAT_005930d0 = 2;
      FUN_0046dfe0(self);
      DAT_005930d0 = 0xff;
    }
    return;
  default:
    return;
  }
  if (_DAT_006633a4 != 0) {
    FUN_0046c7f0(&DAT_006633a4);
  }
  if (_DAT_006633c4 != 0) {
    FUN_0046d360(&DAT_006633c4);
  }
  if (_DAT_006633b0 != 0) {
    FUN_0046d9a0(&DAT_006633b0);
  }
  if (_DAT_006633bc != 0) {
    DAT_005930d0 = 0;
    FUN_0046dfe0(self);
    DAT_005930d0 = 0xff;
  }
  return;
}


// 0x0046ee40: EntityManager::sub_46EE40
// IDA: EntityManager::sub_46EE40
// Ghidra: FUN_0046ee40
void gta2::EntityManager_sub_46EE40(void *self)
{
  byte bVar1;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  undefined *puVar4;
  PedStats *pPVar5;
  undefined *puVar6;
  undefined1 local_5 [5];
  
  _DAT_006633a8 = 0;
  _DAT_006633b4 = 1;
  bVar1 = *(byte *)(_DAT_00663298 + 0xb) & 0xfc;
  if (_DAT_006633bc == 0x3ff) {
    switch(bVar1) {
    case 0xc4:
      if (_DAT_006633a4 != 0) {
        DAT_006633b2 = 2;
        FUN_0046c7f0(&DAT_006633a4);
      }
      if (_DAT_006633b0 != 0) {
        DAT_006633b2 = 4;
        FUN_0046d9a0(&DAT_006633b0);
      }
      if (_DAT_006633c4 != 0) {
        puVar6 = &DAT_006632a0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(pSVar2,pSVar3,puVar6);
        puVar6 = &DAT_006632c0;
        _DAT_006632b8 = 0x42000000;
        _DAT_006632bc = 0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)pSVar3,puVar6);
        puVar6 = &DAT_006632e0;
        pPVar5 = (PedStats *)&DAT_006636f0;
        _DAT_006632d8 = 0x427fffe6;
        _DAT_006632dc = 0x427fffe6;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)pSVar3,pPVar5,puVar6);
        _DAT_006632f8 = 0;
        _DAT_006632fc = 0x427fffe6;
        FUN_0046c210(&DAT_006633c4,&stack0xfffffff7,
                     *(undefined1 *)((int)self + 0x18));
      }
      return;
    case 200:
      if (_DAT_006633c4 != 0) {
        DAT_006633b2 = 2;
        FUN_0046c2c0(&DAT_006633c4);
      }
      if (_DAT_006633b0 != 0) {
        DAT_006633b2 = 3;
        FUN_0046d9a0(&DAT_006633b0);
      }
      if (_DAT_006633a4 != 0) {
        puVar6 = &DAT_006632a0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        FUN_0046bd40(&gS17_V1,pSVar3,puVar6);
        _DAT_006632b8 = 0x42000000;
        _DAT_006632bc = 0;
        FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                     &DAT_006632c0);
        puVar6 = &DAT_006632e0;
        _DAT_006632d8 = 0x427fffe6;
        _DAT_006632dc = 0x427fffe6;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)pSVar2,(PedStats *)pSVar3,puVar6);
        _DAT_006632f8 = 0;
        _DAT_006632fc = 0x427fffe6;
        FUN_0046c210(&DAT_006633a4,&stack0xfffffff7,
                     *(undefined1 *)((int)self + 0x19));
      }
      return;
    case 0xcc:
      if (_DAT_006633a4 != 0) {
        DAT_006633b2 = 1;
        FUN_0046c7f0(&DAT_006633a4);
      }
      if (_DAT_006633c0 != 0) {
        DAT_006633b2 = 4;
        FUN_0046ce30(&DAT_006633c0);
      }
      if (_DAT_006633c4 != 0) {
        puVar4 = &DAT_006632a0;
        puVar6 = &DAT_006636f0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&stack0xfffffff8,
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(pSVar3,puVar6,puVar4);
        puVar6 = &DAT_006632c0;
        _DAT_006632b8 = 0x42000000;
        _DAT_006632bc = 0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)pSVar2,(PedStats *)pSVar3,puVar6);
        _DAT_006632d8 = 0x427fffe6;
        _DAT_006632dc = 0x427fffe6;
        FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                     &DAT_006632e0);
        _DAT_006632f8 = 0;
        _DAT_006632fc = 0x427fffe6;
        FUN_0046c210(&DAT_006633c4,&stack0xfffffff7,
                     *(undefined1 *)((int)self + 0x1a));
      }
      return;
    case 0xd0:
      if (_DAT_006633c4 != 0) {
        DAT_006633b2 = 1;
        FUN_0046c2c0(&DAT_006633c4);
      }
      if (_DAT_006633c0 != 0) {
        DAT_006633b2 = 3;
        FUN_0046ce30(&DAT_006633c0);
      }
      if (_DAT_006633a4 != 0) {
        FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632a0);
        puVar6 = &DAT_006632c0;
        pPVar5 = (PedStats *)&DAT_006636f0;
        _DAT_006632b8 = 0x42000000;
        _DAT_006632bc = 0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)pSVar3,pPVar5,puVar6);
        puVar6 = &DAT_006632e0;
        _DAT_006632d8 = 0x427fffe6;
        _DAT_006632dc = 0x427fffe6;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)pSVar3,puVar6);
        _DAT_006632f8 = 0;
        _DAT_006632fc = 0x427fffe6;
        local_5[0] = 0;
        FUN_0046c210(&DAT_006633a4,local_5,*(undefined1 *)((int)self + 0x1b));
      }
      return;
    }
  }
  else {
    DAT_006633b2 = 0;
    switch(bVar1) {
    case 0xc4:
      if (_DAT_006633a4 != 0) {
        FUN_0046c7f0(&DAT_006633a4);
      }
      if (_DAT_006633c4 != 0) {
        puVar4 = &DAT_006632a0;
        puVar6 = &DAT_006636f0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(pSVar3,puVar6,puVar4);
        _DAT_006632b8 = 0;
        _DAT_006632bc = 0;
        FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                     &DAT_006632c0);
        puVar6 = &DAT_006632e0;
        _DAT_006632d8 = 0x42000000;
        _DAT_006632dc = 0x427fffe6;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(&gS17_V1,pSVar3,puVar6);
        _DAT_006632f8 = 0x427fffe6;
        _DAT_006632fc = 0;
        local_5[0] = 1;
        FUN_0046c210(&DAT_006633c4,local_5,*(undefined1 *)((int)self + 0x18));
      }
      if (_DAT_006633b0 != 0) {
        FUN_0046d9a0(&DAT_006633b0);
      }
      if (_DAT_006633bc != 0) {
        DAT_005930d0 = 0;
        FUN_0046dfe0(self);
        DAT_005930d0 = 0xff;
      }
      return;
    case 200:
      if (_DAT_006633c4 != 0) {
        FUN_0046c2c0(&DAT_006633c4);
      }
      if (_DAT_006633a4 != 0) {
        puVar6 = &DAT_006632a0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(pSVar2,pSVar3,puVar6);
        puVar6 = &DAT_006632c0;
        pPVar5 = (PedStats *)&DAT_006636f0;
        _DAT_006632b8 = 0;
        _DAT_006632bc = 0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)pSVar3,pPVar5,puVar6);
        _DAT_006632d8 = 0x42000000;
        _DAT_006632dc = 0x427fffe6;
        FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632e0);
        _DAT_006632f8 = 0x427fffe6;
        _DAT_006632fc = 0;
        FUN_0046c210(&DAT_006633a4,&stack0xfffffff7,
                     *(undefined1 *)((int)self + 0x19));
      }
      if (_DAT_006633b0 != 0) {
        FUN_0046d9a0(&DAT_006633b0);
      }
      if (_DAT_006633bc != 0) {
        DAT_005930d0 = 1;
        FUN_0046dfe0(self);
        DAT_005930d0 = 0xff;
      }
      return;
    case 0xcc:
      if (_DAT_006633c4 != 0) {
        FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632a0);
        puVar6 = &DAT_006632c0;
        _DAT_006632b8 = 0;
        _DAT_006632bc = 0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)pSVar3,puVar6);
        puVar6 = &DAT_006632e0;
        _DAT_006632d8 = 0x42000000;
        _DAT_006632dc = 0x427fffe6;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(pSVar2,pSVar3,puVar6);
        _DAT_006632f8 = 0x427fffe6;
        _DAT_006632fc = 0;
        FUN_0046c210(&DAT_006633c4,&stack0xfffffff7,
                     *(undefined1 *)((int)self + 0x1a));
      }
      if (_DAT_006633a4 != 0) {
        FUN_0046c7f0(&DAT_006633a4);
      }
      if (_DAT_006633c0 != 0) {
        FUN_0046ce30(&DAT_006633c0);
      }
      if (_DAT_006633bc != 0) {
        DAT_005930d0 = 3;
        FUN_0046dfe0(self);
        DAT_005930d0 = 0xff;
      }
      return;
    case 0xd0:
      if (_DAT_006633c4 != 0) {
        FUN_0046c2c0(&DAT_006633c4);
      }
      if (_DAT_006633a4 != 0) {
        puVar6 = &DAT_006632a0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        FUN_0046bd40(&gS17_V1,pSVar3,puVar6);
        puVar6 = &DAT_006632c0;
        _DAT_006632b8 = 0;
        _DAT_006632bc = 0;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                            (SpriteS1 *)&stack0xfffffff8,(S127 *)&DAT_00663450);
        pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bdf0(self,(PedStats *)pSVar2,(PedStats *)pSVar3,puVar6);
        puVar4 = &DAT_006632e0;
        puVar6 = &DAT_006636f0;
        _DAT_006632d8 = 0x42000000;
        _DAT_006632dc = 0x427fffe6;
        pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_5 + 1),
                            (S127 *)&DAT_00663450);
        FUN_0046bd40(pSVar3,puVar6,puVar4);
        _DAT_006632f8 = 0x427fffe6;
        _DAT_006632fc = 0;
        FUN_0046c210(&DAT_006633a4,&stack0xfffffff7,
                     *(undefined1 *)((int)self + 0x1b));
      }
      if (_DAT_006633c0 != 0) {
        FUN_0046ce30(&DAT_006633c0);
      }
      if (_DAT_006633bc != 0) {
        DAT_005930d0 = 2;
        FUN_0046dfe0(self);
        DAT_005930d0 = 0xff;
      }
      return;
    }
  }
  return;
}


// 0x0046ef10: EntityManager::sub_46EF10
// IDA: EntityManager::sub_46EF10
// Ghidra: ---
void gta2::EntityManager_sub_46EF10(struct EntityManager *self)
{
  int v1; // ebx
  int v2; // edi
  int v4; // ebp
  unsigned __int16 v5; // bx
  int v6; // edi
  int v7; // ebp
  int *v8; // eax
  int *v9; // eax
  S122 *v10; // eax
  PublicTransport *v11; // eax
  int *v12; // eax
  S122 *v13; // eax
  PublicTransport *v14; // eax
  int *v15; // eax
  int *v16; // eax
  int v17; // edi
  S122 *v18; // eax
  PublicTransport *v19; // eax
  int *v20; // eax
  S122 *v21; // eax
  PublicTransport *v22; // eax
  int *v23; // eax
  int v24; // eax
  int v25; // eax
  void *v26; // eax
  int *v27; // [esp-Ch] [ebp-38h]
  int *v28; // [esp-8h] [ebp-34h]
  int *v29; // [esp-8h] [ebp-34h]
  int *v30; // [esp-8h] [ebp-34h]
  int *v31; // [esp-8h] [ebp-34h]
  int v32; // [esp-4h] [ebp-30h]
  _BYTE a2[28]; // [esp+10h] [ebp-1Ch] BYREF

  v1 = *(_DWORD *)word_6633A4;
  v2 = *(_DWORD *)word_6633C4;
  if ( word_6633C4[0] && word_6633A4[0] )
  {
    if ( (word_6633A4[0] & 0x1000) != 0 )
    {
      gta2::Player_sub_40E530((Player *)&gWeapon, (Tango *)&dword_663450);
      *(_DWORD *)a2 = v2 | 0x1000;
      gta2::EntityManager_sub_46C2C0(self);
      gta2::Weapon_UseAmmo((Weapon *)&gWeapon, &dword_663450);
      v1 = *(_DWORD *)word_6633A4;
      LOWORD(v2) = word_6633C4[0];
    }
    if ( (v2 & 0x1000) != 0 )
    {
      gta2::Weapon_UseAmmo((Weapon *)&gWeapon, &dword_663450);
      BYTE1(v1) |= 0x10u;
      *(_DWORD *)a2 = v1;
      gta2::EntityManager_sub_46C7F0(self, (int)a2);
      gta2::Player_sub_40E530((Player *)&gWeapon, (Tango *)&dword_663450);
      LOWORD(v1) = word_6633A4[0];
      LOWORD(v2) = word_6633C4[0];
    }
  }
  if ( word_6633C0[0] )
  {
    v4 = *(_DWORD *)&word_6633B0;
    if ( word_6633B0 )
    {
      if ( (word_6633C0[0] & 0x1000) != 0 )
      {
        gta2::Weapon_UseAmmo((Weapon *)&unk_6636F0, &dword_663450);
        *(_DWORD *)a2 = v4 | 0x1000;
        gta2::EntityManager_sub_46D9A0(self, (int)a2);
        gta2::Player_sub_40E530((Player *)&unk_6636F0, (Tango *)&dword_663450);
        LOWORD(v1) = word_6633A4[0];
        LOWORD(v2) = word_6633C4[0];
      }
    }
  }
  if ( (_WORD)v2 && (!(_WORD)v1 || (v1 & 0x1000) == 0 || (v2 & 0x1000) != 0) )
  {
    gta2::EntityManager_sub_46C2C0(self);
    LOWORD(v1) = word_6633A4[0];
    LOWORD(v2) = word_6633C4[0];
  }
  if ( (_WORD)v1 && (!(_WORD)v2 || (v2 & 0x1000) == 0 || (v1 & 0x1000) != 0) )
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
  if ( word_6633C0[0] && (!word_6633B0 || (word_6633B0 & 0x1000) == 0 || (word_6633C0[0] & 0x1000) != 0) )
    gta2::EntityManager_sub_46CE30(self, (int)word_6633C0);
  v5 = word_6633BC;
  if ( word_6633BC && !skip_lid )
  {
    v6 = dword_6633B4;
    v7 = unk_6633A8;
    if ( unk_6633A8 == dword_6633B4 - 1 )
    {
      v28 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[4], (PublicTransport *)&dword_663450);
      v8 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)a2, (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BDF0(self, v8, v28, &unk_6632E0);
      v9 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[4], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, v9, &unk_663300);
      v6 = dword_6633B4;
    }
    else
    {
      gta2::S202_sub_41F980((S202 *)a2, dword_6633B4 - unk_6633A8 - 1);
      gta2::S122_sub_401BF0(v10, (int)&a2[4], (int)&dword_6633B4);
      v29 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[8], v11);
      v27 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[12], (PublicTransport *)&dword_663450);
      v12 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[16], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, v12, v27, v29, &unk_6632E0);
      gta2::S202_sub_41F980((S202 *)&a2[12], v6 - v7 - 1);
      gta2::S122_sub_401BF0(v13, (int)&a2[16], (int)&dword_6633B4);
      v30 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[20], v14);
      v15 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[24], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, (int *)&gWeapon, v15, v30, &unk_663300);
      v5 = word_6633BC;
    }
    if ( v7 )
    {
      v17 = v6 - v7;
      gta2::S202_sub_41F980((S202 *)&a2[20], v17);
      gta2::S122_sub_401BF0(v18, (int)&a2[24], (int)&dword_6633B4);
      v20 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[16], v19);
      gta2::EntityManager_MatrixTransform3Advanced(self, (int *)&gWeapon, &unk_6636F0.field_0, v20, &a4);
      gta2::S202_sub_41F980((S202 *)&a2[20], v17);
      gta2::S122_sub_401BF0(v21, (int)&a2[24], (int)&dword_6633B4);
      v31 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[12], v22);
      v23 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[8], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, v23, &unk_6636F0.field_0, v31, &unk_6632C0);
      v5 = word_6633BC;
    }
    else
    {
      gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, &unk_6636F0.field_0, &a4);
      v16 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[24], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BD40(self, v16, &unk_6636F0.field_0, &unk_6632C0);
    }
    v24 = dword_593174[v5 >> 13];
    LOBYTE(v24) = v24 | 1;
    dword_6633B8 = v24;
    if ( (v5 & 0x1000) != 0 )
    {
      LOBYTE(v24) = v24 | 0x80;
      dword_6633B8 = v24;
    }
    LOWORD(v25) = gta2::Style_get_tile_by_id(gStyle, v5 & 0x3FF);
    *(_DWORD *)&a2[4] = v25;
    if ( ((*(_DWORD *)&word_6633BC >> 10) & 3) != 0 )
      a2[0] = gta2::EntityManager_sub_46B5E0(self, (*(_DWORD *)&word_6633BC >> 10) & 3);
    else
      a2[0] = self->field_14;
    v32 = *(_DWORD *)a2;
    v26 = gta2::TextureManager_getTexture4M(gTextureManager, (unsigned __int16 *)&a2[4]);
    ((void (__cdecl *)(int, void *, float *, int))gbh_DrawTile)(dword_6633B8 | dword_67358C, v26, &a4, v32);
    ++self->field_2F00;
  }
}


// 0x0046f370: EntityManager::sub_46F370
// IDA: EntityManager::sub_46F370
// Ghidra: ---
void gta2::EntityManager_sub_46F370(struct EntityManager *self)
{
  int v1; // ebx
  int v2; // edi
  int v4; // ebp
  unsigned __int16 v5; // bx
  int v6; // ebp
  int *v7; // eax
  int *v8; // eax
  int v9; // edi
  int v10; // ebx
  S122 *v11; // eax
  PublicTransport *v12; // eax
  int *v13; // eax
  S122 *v14; // eax
  PublicTransport *v15; // eax
  int *v16; // eax
  int *v17; // eax
  int v18; // edi
  S122 *v19; // eax
  PublicTransport *v20; // eax
  int *v21; // eax
  S122 *v22; // eax
  PublicTransport *v23; // eax
  int *v24; // eax
  int v25; // eax
  int v26; // eax
  char v27; // al
  void *v28; // eax
  int *v29; // [esp-Ch] [ebp-38h]
  int *v30; // [esp-8h] [ebp-34h]
  int *v31; // [esp-8h] [ebp-34h]
  int *v32; // [esp-8h] [ebp-34h]
  int *v33; // [esp-8h] [ebp-34h]
  int v34; // [esp-4h] [ebp-30h]
  _BYTE v35[28]; // [esp+10h] [ebp-1Ch] BYREF

  v1 = *(_DWORD *)word_6633A4;
  v2 = *(_DWORD *)word_6633C4;
  if ( word_6633C4[0] && word_6633A4[0] )
  {
    if ( (word_6633A4[0] & 0x1000) != 0 )
    {
      gta2::Player_sub_40E530((Player *)&gWeapon, (Tango *)&dword_663450);
      *(_DWORD *)v35 = v2 | 0x1000;
      gta2::EntityManager_sub_46C2C0(self);
      gta2::Weapon_UseAmmo((Weapon *)&gWeapon, &dword_663450);
      v1 = *(_DWORD *)word_6633A4;
      LOWORD(v2) = word_6633C4[0];
    }
    if ( (v2 & 0x1000) != 0 )
    {
      gta2::Weapon_UseAmmo((Weapon *)&gWeapon, &dword_663450);
      BYTE1(v1) |= 0x10u;
      *(_DWORD *)v35 = v1;
      gta2::EntityManager_sub_46C7F0(self, (int)v35);
      gta2::Player_sub_40E530((Player *)&gWeapon, (Tango *)&dword_663450);
      LOWORD(v1) = word_6633A4[0];
      LOWORD(v2) = word_6633C4[0];
    }
  }
  v4 = *(_DWORD *)word_6633C0;
  if ( word_6633C0[0] && word_6633B0 && (word_6633B0 & 0x1000) != 0 )
  {
    gta2::Player_sub_40E530((Player *)&unk_6636F0, (Tango *)&dword_663450);
    *(_DWORD *)v35 = v4 | 0x1000;
    gta2::EntityManager_sub_46CE30(self, (int)v35);
    gta2::Weapon_UseAmmo((Weapon *)&unk_6636F0, &dword_663450);
    LOWORD(v1) = word_6633A4[0];
    LOWORD(v2) = word_6633C4[0];
  }
  if ( (_WORD)v2 && (!(_WORD)v1 || (v1 & 0x1000) == 0 || (v2 & 0x1000) != 0) )
  {
    gta2::EntityManager_sub_46C2C0(self);
    LOWORD(v1) = word_6633A4[0];
    LOWORD(v2) = word_6633C4[0];
  }
  if ( (_WORD)v1 && (!(_WORD)v2 || (v2 & 0x1000) == 0 || (v1 & 0x1000) != 0) )
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
  if ( word_6633B0 && (!word_6633C0[0] || (word_6633C0[0] & 0x1000) == 0 || (word_6633B0 & 0x1000) != 0) )
    gta2::EntityManager_sub_46D9A0(self, (int)&word_6633B0);
  v5 = word_6633BC;
  if ( word_6633BC && !skip_lid )
  {
    v6 = unk_6633A8;
    if ( unk_6633A8 )
    {
      v9 = dword_6633B4;
      v10 = dword_6633B4 - unk_6633A8;
      gta2::S202_sub_41F980((S202 *)v35, dword_6633B4 - unk_6633A8);
      gta2::S122_sub_401BF0(v11, (int)&v35[4], (int)&dword_6633B4);
      v31 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&v35[8], v12);
      v29 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v35[12], (PublicTransport *)&dword_663450);
      v13 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v35[16], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, v13, v29, v31, &unk_6632E0);
      gta2::S202_sub_41F980((S202 *)&v35[12], v10);
      gta2::S122_sub_401BF0(v14, (int)&v35[16], (int)&dword_6633B4);
      v32 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&v35[20], v15);
      v16 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v35[24], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, (int *)&gWeapon, v16, v32, &unk_663300);
      v5 = word_6633BC;
    }
    else
    {
      v30 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v35[4], (PublicTransport *)&dword_663450);
      v7 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)v35, (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BD40(self, v7, v30, &unk_6632E0);
      v8 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&v35[4], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BD40(self, (int *)&gWeapon, v8, &unk_663300);
      v9 = dword_6633B4;
    }
    if ( v6 == v9 - 1 )
    {
      gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, &unk_6636F0.field_0, &a4);
      v17 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v35[24], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BDF0(self, v17, &unk_6636F0.field_0, &unk_6632C0);
    }
    else
    {
      v18 = v9 - v6 - 1;
      gta2::S202_sub_41F980((S202 *)&v35[20], v18);
      gta2::S122_sub_401BF0(v19, (int)&v35[24], (int)&dword_6633B4);
      v21 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&v35[16], v20);
      gta2::EntityManager_MatrixTransform3Advanced(self, (int *)&gWeapon, &unk_6636F0.field_0, v21, &a4);
      gta2::S202_sub_41F980((S202 *)&v35[20], v18);
      gta2::S122_sub_401BF0(v22, (int)&v35[24], (int)&dword_6633B4);
      v33 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&v35[12], v23);
      v24 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&v35[8], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, v24, &unk_6636F0.field_0, v33, &unk_6632C0);
    }
    v25 = dword_593174[v5 >> 13];
    LOBYTE(v25) = v25 | 2;
    dword_6633B8 = v25;
    if ( (v5 & 0x1000) != 0 )
    {
      LOBYTE(v25) = v25 | 0x80;
      dword_6633B8 = v25;
    }
    LOWORD(v26) = gta2::Style_get_tile_by_id(gStyle, v5 & 0x3FF);
    *(_DWORD *)&v35[4] = v26;
    if ( ((*(_DWORD *)&word_6633BC >> 10) & 3) != 0 )
      v27 = gta2::EntityManager_sub_46B5E0(self, (*(_DWORD *)&word_6633BC >> 10) & 3);
    else
      v27 = self->field_15;
    v35[0] = v27;
    v34 = *(_DWORD *)v35;
    v28 = gta2::TextureManager_getTexture4M(gTextureManager, (unsigned __int16 *)&v35[4]);
    ((void (__cdecl *)(int, void *, float *, int))gbh_DrawTile)(dword_6633B8 | dword_67358C, v28, &a4, v34);
    ++self->field_2F00;
  }
}


// 0x0046fc10: EntityManager::sub_46FC10
// IDA: EntityManager::sub_46FC10
// Ghidra: ---
void gta2::EntityManager_sub_46FC10(struct EntityManager *self)
{
  int v1; // edi
  int v3; // edi
  int v4; // ebx
  unsigned __int16 v5; // bx
  int v6; // edi
  int v7; // ebp
  int *v8; // eax
  S122 *v9; // eax
  PublicTransport *v10; // eax
  int *v11; // eax
  S122 *v12; // eax
  PublicTransport *v13; // eax
  int *v14; // eax
  int *v15; // eax
  int *v16; // eax
  int v17; // edi
  S122 *v18; // eax
  PublicTransport *v19; // eax
  int *v20; // eax
  S122 *v21; // eax
  PublicTransport *v22; // eax
  int *v23; // eax
  int v24; // eax
  int v25; // eax
  void *v26; // eax
  int *v27; // [esp-10h] [ebp-38h]
  int *v28; // [esp-Ch] [ebp-34h]
  int *v29; // [esp-Ch] [ebp-34h]
  int *v30; // [esp-Ch] [ebp-34h]
  int *v31; // [esp-Ch] [ebp-34h]
  int v32; // [esp-4h] [ebp-2Ch]
  _BYTE a2[28]; // [esp+Ch] [ebp-1Ch] BYREF

  v1 = *(_DWORD *)word_6633C4;
  if ( word_6633C4[0] && word_6633A4[0] && (word_6633A4[0] & 0x1000) != 0 )
  {
    gta2::Player_sub_40E530((Player *)&gWeapon, (Tango *)&dword_663450);
    *(_DWORD *)a2 = v1 | 0x1000;
    gta2::EntityManager_sub_46C2C0(self);
    gta2::Weapon_UseAmmo((Weapon *)&gWeapon, &dword_663450);
  }
  v3 = *(_DWORD *)word_6633C0;
  v4 = *(_DWORD *)&word_6633B0;
  if ( word_6633C0[0] && word_6633B0 )
  {
    if ( (word_6633B0 & 0x1000) != 0 )
    {
      gta2::Player_sub_40E530((Player *)&unk_6636F0, (Tango *)&dword_663450);
      *(_DWORD *)a2 = v3 | 0x1000;
      gta2::EntityManager_sub_46CE30(self, (int)a2);
      gta2::Weapon_UseAmmo((Weapon *)&unk_6636F0, &dword_663450);
      v4 = *(_DWORD *)&word_6633B0;
      LOWORD(v3) = word_6633C0[0];
    }
    if ( (v3 & 0x1000) != 0 )
    {
      gta2::Weapon_UseAmmo((Weapon *)&unk_6636F0, &dword_663450);
      BYTE1(v4) |= 0x10u;
      *(_DWORD *)a2 = v4;
      gta2::EntityManager_sub_46D9A0(self, (int)a2);
      gta2::Player_sub_40E530((Player *)&unk_6636F0, (Tango *)&dword_663450);
      LOWORD(v4) = word_6633B0;
      LOWORD(v3) = word_6633C0[0];
    }
  }
  if ( word_6633A4[0] && (!word_6633C4[0] || (word_6633C4[0] & 0x1000) == 0 || (word_6633A4[0] & 0x1000) != 0) )
  {
    gta2::EntityManager_sub_46C7F0(self, (int)word_6633A4);
    LOWORD(v4) = word_6633B0;
    LOWORD(v3) = word_6633C0[0];
  }
  if ( (_WORD)v3 && (!(_WORD)v4 || (v4 & 0x1000) == 0 || (v3 & 0x1000) != 0) )
  {
    gta2::EntityManager_sub_46CE30(self, (int)word_6633C0);
    LOWORD(v4) = word_6633B0;
    LOWORD(v3) = word_6633C0[0];
  }
  if ( (_WORD)v4 && (!(_WORD)v3 || (v3 & 0x1000) == 0 || (v4 & 0x1000) != 0) )
    gta2::EntityManager_sub_46D9A0(self, (int)&word_6633B0);
  v5 = word_6633BC;
  if ( word_6633BC && !skip_lid )
  {
    v6 = dword_6633B4;
    v7 = unk_6633A8;
    if ( unk_6633A8 == dword_6633B4 - 1 )
    {
      gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, &unk_6636F0.field_0, &a4);
      v8 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[4], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BDF0(self, (int *)&gWeapon, v8, &unk_663300);
      v6 = dword_6633B4;
    }
    else
    {
      gta2::S202_sub_41F980((S202 *)a2, dword_6633B4 - unk_6633A8 - 1);
      gta2::S122_sub_401BF0(v9, (int)&a2[4], (int)&dword_6633B4);
      v11 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[8], v10);
      gta2::EntityManager_MatrixTransform3Advanced(self, (int *)&gWeapon, &unk_6636F0.field_0, v11, &a4);
      gta2::S202_sub_41F980((S202 *)&a2[4], v6 - v7 - 1);
      gta2::S122_sub_401BF0(v12, (int)&a2[8], (int)&dword_6633B4);
      v28 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[12], v13);
      v14 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[16], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, (int *)&gWeapon, v14, v28, &unk_663300);
      v5 = word_6633BC;
    }
    if ( v7 )
    {
      v17 = v6 - v7;
      gta2::S202_sub_41F980((S202 *)&a2[12], v17);
      gta2::S122_sub_401BF0(v18, (int)&a2[16], (int)&dword_6633B4);
      v30 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)&a2[8], v19);
      v20 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[4], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, v20, &unk_6636F0.field_0, v30, &unk_6632C0);
      gta2::S202_sub_41F980((S202 *)&a2[12], v17);
      gta2::S122_sub_401BF0(v21, (int)&a2[16], (int)&dword_6633B4);
      v31 = (int *)gta2::S202_sub_401B20(&unk_663738, (SpriteS1 *)a2, v22);
      v27 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[20], (PublicTransport *)&dword_663450);
      v23 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[24], (PublicTransport *)&dword_663450);
      gta2::EntityManager_MatrixTransform3Advanced(self, v23, v27, v31, &unk_6632E0);
    }
    else
    {
      v15 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[16], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BD40(self, v15, &unk_6636F0.field_0, &unk_6632C0);
      v29 = (int *)gta2::S202_sub_401B20(&unk_6636F0, (SpriteS1 *)&a2[16], (PublicTransport *)&dword_663450);
      v16 = (int *)gta2::S202_sub_401B20((S202 *)&gWeapon, (SpriteS1 *)&a2[12], (PublicTransport *)&dword_663450);
      gta2::EntityManager_sub_46BD40(self, v16, v29, &unk_6632E0);
    }
    v24 = dword_593174[v5 >> 13];
    LOBYTE(v24) = v24 | 4;
    dword_6633B8 = v24;
    if ( (v5 & 0x1000) != 0 )
    {
      LOBYTE(v24) = v24 | 0x80;
      dword_6633B8 = v24;
    }
    LOWORD(v25) = gta2::Style_get_tile_by_id(gStyle, v5 & 0x3FF);
    *(_DWORD *)&a2[4] = v25;
    if ( ((*(_DWORD *)&word_6633BC >> 10) & 3) != 0 )
      a2[0] = gta2::EntityManager_sub_46B5E0(self, (*(_DWORD *)&word_6633BC >> 10) & 3);
    else
      a2[0] = self->field_17;
    v32 = *(_DWORD *)a2;
    v26 = gta2::TextureManager_getTexture4M(gTextureManager, (unsigned __int16 *)&a2[4]);
    ((void (__cdecl *)(int, void *, float *, int))gbh_DrawTile)(dword_6633B8 | dword_67358C, v26, &a4, v32);
    ++self->field_2F00;
  }
}


// 0x00470060: EntityManager::sub_470060
// IDA: EntityManager::sub_470060
// Ghidra: FUN_00470060
void gta2::EntityManager_sub_470060(void *self,ushort *param_1,int *param_2,int *param_3,int *param_4)
{
  ushort *puVar1;
  int *pS127;
  int *piVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pSVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  
  piVar2 = param_3;
  if (gSkipLeft == 0) {
    puVar7 = &DAT_006632a0;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_3,
                        (S127 *)param_3);
    pS127 = param_2;
    pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)param_2
                       );
    FUN_0046bdf0(self,(PedStats *)pSVar4,(PedStats *)pSVar3,puVar7);
    puVar7 = &DAT_006632c0;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_3,
                        (S127 *)piVar2);
    pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)pS127);
    FUN_0046bd40(pSVar4,pSVar3,puVar7);
    piVar2 = param_4;
    if (_DAT_006632a0 <= _DAT_006632c0) {
      puVar7 = &DAT_00663300;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_3,
                          (S127 *)param_4);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)pS127
                         );
      FUN_0046bdf0(self,(PedStats *)pSVar4,(PedStats *)pSVar3,puVar7);
      puVar7 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_3,
                          (S127 *)piVar2);
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)pS127
                         );
      FUN_0046bd40(pSVar4,pSVar3,puVar7);
      FUN_0046bea0();
      param_3 = NULL;
      FUN_0046c0c0(&DAT_006634b4);
      param_3 = (int *)0x1;
      FUN_0046c0c0(&DAT_00663450);
      param_3 = (int *)0x2;
      FUN_0046c0c0(&DAT_00663450);
      param_3 = (int *)0x3;
      FUN_0046c0c0(&DAT_006634b4);
      puVar1 = param_1;
      _DAT_006633b8 = 0x4005;
      param_1 = (ushort *)FUN_004bf6b0(*param_1 & 0x3ff);
      if ((short)param_1 != 0) {
        if ((*puVar1 & 0x1000) != 0) {
          _DAT_006633b8 = _DAT_006633b8 | 0x80;
        }
        uVar6 = (uint)*(byte *)((int)self + 0xc);
        puVar7 = &DAT_006632a0;
        uVar5 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_1)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar5,puVar7,uVar6);
        *(int *)((int)self + 0x2f00) = *(int *)((int)self + 0x2f00) + 1;
      }
    }
  }
  return;
}


// 0x00470250: EntityManager::sub_470250
// IDA: EntityManager::sub_470250
// Ghidra: FUN_00470250
void gta2::EntityManager_sub_470250(void *param_1,ushort *param_2,SpriteS1 *param_3,SpriteS1 *param_4, SpriteS1 *param_5)
{
  ushort *puVar1;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pSVar4;
  SpriteS1 *pSVar5;
  undefined4 uVar6;
  uint uVar7;
  undefined *puVar8;
  
  pSVar4 = param_4;
  if (gSkipRight == 0) {
    puVar8 = &DAT_006632c0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                        (S127 *)param_4);
    pSVar5 = param_3;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,(S127 *)param_3
                       );
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar8);
    puVar8 = &DAT_006632a0;
    pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                        (S127 *)pSVar4);
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,(S127 *)pSVar5)
    ;
    FUN_0046bd40(pSVar2,pSVar4,puVar8);
    pSVar4 = param_5;
    if (_DAT_006632a0 <= _DAT_006632c0) {
      puVar8 = &DAT_006632e0;
      pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                          (S127 *)param_5);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,
                          (S127 *)pSVar5);
      FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar8);
      puVar8 = &DAT_00663300;
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                          (S127 *)pSVar4);
      pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,
                          (S127 *)pSVar5);
      FUN_0046bd40(pSVar5,pSVar4,puVar8);
      FUN_0046bea0();
      param_4 = NULL;
      FUN_0046c0c0(&DAT_006634b4);
      param_4 = (SpriteS1 *)0x1;
      FUN_0046c0c0(&DAT_00663450);
      param_4 = (SpriteS1 *)0x2;
      FUN_0046c0c0(&DAT_00663450);
      param_4 = (SpriteS1 *)0x3;
      FUN_0046c0c0(&DAT_006634b4);
      puVar1 = param_2;
      _DAT_006633b8 = 0x4005;
      param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
      if ((short)param_2 != 0) {
        if ((*puVar1 & 0x1000) != 0) {
          _DAT_006633b8 = _DAT_006633b8 | 0x80;
        }
        uVar7 = (uint)*(byte *)((int)param_1 + 0xd);
        puVar8 = &DAT_006632a0;
        uVar6 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar6,puVar8,uVar7);
        *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
      }
    }
  }
  return;
}


// 0x00470440: EntityManager::sub_470440
// IDA: EntityManager::sub_470440
// Ghidra: FUN_00470440
void gta2::EntityManager_sub_470440(void *param_1,ushort *param_2,SpriteS1 *param_3,SpriteS1 *param_4, SpriteS1 *param_5)
{
  ushort *puVar1;
  SpriteS1 *pS127;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pS17_a1;
  SpriteS1 *pSVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  
  pSVar4 = param_5;
  if (gSkipTop == 0) {
    puVar7 = &DAT_006632a0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                        (S127 *)param_5);
    pS127 = param_3;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,(S127 *)param_3
                       );
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar7);
    puVar7 = &DAT_00663300;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                        (S127 *)pSVar4);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,(S127 *)pS127);
    FUN_0046bd40(pSVar3,pSVar2,puVar7);
    if (_DAT_006632a4 <= _DAT_00663304) {
      puVar7 = &DAT_006632c0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                          (S127 *)pSVar4);
      pSVar2 = param_4;
      pS17_a1 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,
                           (S127 *)param_4);
      FUN_0046bdf0(param_1,(PedStats *)pS17_a1,(PedStats *)pSVar3,puVar7);
      puVar7 = &DAT_006632e0;
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                          (S127 *)pSVar4);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,
                          (S127 *)pSVar2);
      FUN_0046bd40(pSVar3,pSVar4,puVar7);
      FUN_0046bea0();
      param_5 = NULL;
      FUN_0046c0c0(pS127);
      param_5 = (SpriteS1 *)0x1;
      FUN_0046c0c0(pSVar2);
      param_5 = (SpriteS1 *)0x2;
      FUN_0046c0c0(pSVar2);
      param_5 = (SpriteS1 *)0x3;
      FUN_0046c0c0(pS127);
      puVar1 = param_2;
      _DAT_006633b8 = 0x4005;
      param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
      if ((short)param_2 != 0) {
        if ((*puVar1 & 0x1000) != 0) {
          _DAT_006633b8 = _DAT_006633b8 | 0x80;
        }
        uVar6 = (uint)*(byte *)((int)param_1 + 0xf);
        puVar7 = &DAT_006632a0;
        uVar5 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar5,puVar7,uVar6);
        *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
      }
    }
  }
  return;
}


// 0x00470620: EntityManager::sub_470620
// IDA: EntityManager::sub_470620
// Ghidra: FUN_00470620
void gta2::EntityManager_sub_470620(void *param_1,ushort *param_2,SpriteS1 *param_3,SpriteS1 *param_4, SpriteS1 *param_5)
{
  ushort *puVar1;
  SpriteS1 *pS127;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  SpriteS1 *pS17_a1;
  SpriteS1 *pSVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  
  pSVar4 = param_5;
  if (gSkipBottom == 0) {
    puVar7 = &DAT_00663300;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                        (S127 *)param_5);
    pS127 = param_3;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,(S127 *)param_3
                       );
    FUN_0046bdf0(param_1,(PedStats *)pSVar3,(PedStats *)pSVar2,puVar7);
    puVar7 = &DAT_006632a0;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                        (S127 *)pSVar4);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,(S127 *)pS127);
    FUN_0046bd40(pSVar3,pSVar2,puVar7);
    if (_DAT_006632a4 <= _DAT_00663304) {
      puVar7 = &DAT_006632e0;
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                          (S127 *)pSVar4);
      pSVar2 = param_4;
      pS17_a1 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,
                           (S127 *)param_4);
      FUN_0046bdf0(param_1,(PedStats *)pS17_a1,(PedStats *)pSVar3,puVar7);
      puVar7 = &DAT_006632c0;
      pSVar4 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_5,
                          (S127 *)pSVar4);
      pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_3,
                          (S127 *)pSVar2);
      FUN_0046bd40(pSVar3,pSVar4,puVar7);
      FUN_0046bea0();
      param_5 = NULL;
      FUN_0046c0c0(pS127);
      param_5 = (SpriteS1 *)0x1;
      FUN_0046c0c0(pSVar2);
      param_5 = (SpriteS1 *)0x2;
      FUN_0046c0c0(pSVar2);
      param_5 = (SpriteS1 *)0x3;
      FUN_0046c0c0(pS127);
      puVar1 = param_2;
      _DAT_006633b8 = 0x4005;
      param_2 = (ushort *)FUN_004bf6b0(*param_2 & 0x3ff);
      if ((short)param_2 != 0) {
        if ((*puVar1 & 0x1000) != 0) {
          _DAT_006633b8 = _DAT_006633b8 | 0x80;
        }
        uVar6 = (uint)*(byte *)((int)param_1 + 0xe);
        puVar7 = &DAT_006632a0;
        uVar5 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_2)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar5,puVar7,uVar6);
        *(int *)((int)param_1 + 0x2f00) = *(int *)((int)param_1 + 0x2f00) + 1;
      }
    }
  }
  return;
}


// 0x00470800: EntityManager::sub_470800
// IDA: EntityManager::sub_470800
// Ghidra: FUN_00470800
void gta2::EntityManager_sub_470800(int param_1,SpriteS1 *param_2,SpriteS1 *param_3,SpriteS1 *param_4, SpriteS1 *param_5)
{
  SpriteS1 *pS127;
  SpriteS1 *pSVar1;
  SpriteS1 *pSVar2;
  SpriteS1 *pSVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  uint uVar6;
  undefined *puVar7;
  
  pSVar3 = param_4;
  if (gSkipLid == 0) {
    puVar7 = &DAT_006632a0;
    pSVar1 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                        (S127 *)param_4);
    pS127 = param_2;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)param_2
                       );
    FUN_0046bd40(pSVar2,pSVar1,puVar7);
    puVar7 = &DAT_006632c0;
    pSVar1 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                        (S127 *)pSVar3);
    pSVar3 = param_3;
    pSVar2 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)param_3
                       );
    FUN_0046bd40(pSVar2,pSVar1,puVar7);
    puVar7 = &DAT_006632e0;
    pSVar1 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                        (S127 *)param_5);
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)pSVar3)
    ;
    FUN_0046bd40(pSVar3,pSVar1,puVar7);
    puVar7 = &DAT_00663300;
    pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)&param_4,
                        (S127 *)param_5);
    pSVar1 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&param_2,(S127 *)pS127);
    FUN_0046bd40(pSVar1,pSVar3,puVar7);
    FUN_0046bea0();
    param_4 = NULL;
    FUN_0046c0c0(pS127);
    param_4 = (SpriteS1 *)0x1;
    FUN_0046c0c0(param_3);
    param_4 = (SpriteS1 *)0x2;
    FUN_0046c0c0(param_3);
    param_3 = (SpriteS1 *)0x3;
    FUN_0046c0c0(pS127);
    param_3 = (SpriteS1 *)FUN_004bf6b0(_DAT_006633bc & 0x3ff);
    if ((short)param_3 != 0) {
      uVar6 = 0x4005;
      _DAT_006633b8 = 0x4005;
      if ((_DAT_006633bc & 0x1000) != 0) {
        uVar6 = 0x4085;
        _DAT_006633b8 = 0x4085;
      }
      uVar4 = FUN_0046b5e0(_DAT_006633bc >> 10 & 3);
      puVar7 = &DAT_006632a0;
      uVar5 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)&param_3);
      (*(code *)gbh_DrawTile)(gTimeDayAndNight | uVar6,uVar5,puVar7,uVar4);
      *(int *)(param_1 + 0x2f00) = *(int *)(param_1 + 0x2f00) + 1;
    }
  }
  return;
}


// 0x00471c30: EntityManager::sub_471C30
// IDA: EntityManager::sub_471C30
// Ghidra: FUN_00471c30
void gta2::EntityManager_sub_471C30(void *self)
{
  ushort uVar1;
  short sVar2;
  short sVar3;
  void *local_4;
  
  _DAT_006633b0 = (uint3)_DAT_006633b0;
  sVar2 = (short)_DAT_006633c4;
  sVar3 = (short)_DAT_006633a4;
  local_4 = self;
  switch(*(byte *)(_DAT_00663298 + 0xb) & 0xfc) {
  case 0xd4:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_006634fc,
                     (int *)&DAT_006634b4,(int *)&DAT_00663450);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006634b4,&DAT_006634b4,&DAT_00663450);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006634b4,&DAT_006634fc,&DAT_00663450);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006634b4,&DAT_006634fc,&DAT_006634b4);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_0046c2c0(&DAT_006633c4);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_006634fc,&DAT_006634b4,&DAT_00663450);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006634b4,&DAT_006634fc,&DAT_006634b4);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006634b4,&DAT_006634fc,&DAT_00663450);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006634b4,&DAT_006634fc,&DAT_006634b4,&DAT_00663450);
    }
    return;
  case 0xd8:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_00663450,
                     (int *)&DAT_006634b4,(int *)&DAT_00663450);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006635b8,&DAT_006634b4,&DAT_00663450);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006635b8,&DAT_00663450,&DAT_00663450);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006635b8,&DAT_00663450,&DAT_006634b4);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006635b8,
                   (int *)&DAT_006634b4,(int *)&DAT_00663450);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_0046c7f0(&DAT_006633a4);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006635b8,&DAT_00663450,&DAT_006634b4);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006635b8,&DAT_00663450,&DAT_00663450);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006635b8,&DAT_00663450,&DAT_006634b4,&DAT_00663450);
    }
    return;
  case 0xdc:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_00663450,
                     (int *)&DAT_006634b4,(int *)&DAT_006634fc);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006634b4,&DAT_006634b4,&DAT_006634fc);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006634b4,&DAT_00663450,&DAT_006634fc);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006634b4,&DAT_00663450,&DAT_006634b4);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006634b4,
                   (int *)&DAT_006634b4,(int *)&DAT_006634fc);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_00663450,&DAT_006634b4,&DAT_006634fc);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_0046ce30(&DAT_006633c0);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006634b4,&DAT_00663450,&DAT_006634fc);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006634b4,&DAT_00663450,&DAT_006634b4,&DAT_006634fc);
    }
    return;
  case 0xe0:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_00663450,
                     (int *)&DAT_006635b8,(int *)&DAT_00663450);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006634b4,&DAT_006635b8,&DAT_00663450);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006634b4,&DAT_00663450,&DAT_00663450);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006634b4,&DAT_00663450,&DAT_006635b8);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006634b4,
                   (int *)&DAT_006635b8,(int *)&DAT_00663450);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_00663450,&DAT_006635b8,&DAT_00663450);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006634b4,&DAT_00663450,&DAT_006635b8);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_0046d9a0(&DAT_006633b0);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006634b4,&DAT_00663450,&DAT_006635b8,&DAT_00663450);
    }
    return;
  case 0xe4:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_006634fc,
                     (int *)&DAT_006634b4,(int *)&DAT_006634fc);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006634b4,&DAT_006634b4,&DAT_006634fc);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006634b4,&DAT_006634fc,&DAT_006634fc);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006634b4,&DAT_006634fc,&DAT_006634b4);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006634b4,
                   (int *)&DAT_006634b4,(int *)&DAT_006634fc);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_006634fc,&DAT_006634b4,&DAT_006634fc);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006634b4,&DAT_006634fc,&DAT_006634b4);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006634b4,&DAT_006634fc,&DAT_006634fc);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006634b4,&DAT_006634fc,&DAT_006634b4,&DAT_006634fc);
    }
    return;
  case 0xe8:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_00663450,
                     (int *)&DAT_006634b4,(int *)&DAT_006634fc);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006635b8,&DAT_006634b4,&DAT_006634fc);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006635b8,&DAT_00663450,&DAT_006634fc);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006635b8,&DAT_00663450,&DAT_006634b4);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006635b8,
                   (int *)&DAT_006634b4,(int *)&DAT_006634fc);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_00663450,&DAT_006634b4,&DAT_006634fc);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006635b8,&DAT_00663450,&DAT_006634b4);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006635b8,&DAT_00663450,&DAT_006634fc);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006635b8,&DAT_00663450,&DAT_006634b4,&DAT_006634fc);
    }
    return;
  case 0xec:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_00663450,
                     (int *)&DAT_006635b8,(int *)&DAT_00663450);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006635b8,&DAT_006635b8,&DAT_00663450);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006635b8,&DAT_00663450,&DAT_00663450);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006635b8,&DAT_00663450,&DAT_006635b8);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006635b8,
                   (int *)&DAT_006635b8,(int *)&DAT_00663450);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_00663450,&DAT_006635b8,&DAT_00663450);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006635b8,&DAT_00663450,&DAT_006635b8);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006635b8,&DAT_00663450,&DAT_00663450);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006635b8,&DAT_00663450,&DAT_006635b8,&DAT_00663450);
    }
    return;
  case 0xf0:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_006634fc,
                     (int *)&DAT_006635b8,(int *)&DAT_00663450);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006634b4,&DAT_006635b8,&DAT_00663450);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006634b4,&DAT_006634fc,&DAT_00663450);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006634b4,&DAT_006634fc,&DAT_006635b8);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006634b4,
                   (int *)&DAT_006635b8,(int *)&DAT_00663450);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_006634fc,&DAT_006635b8,&DAT_00663450);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006634b4,&DAT_006634fc,&DAT_006635b8);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006634b4,&DAT_006634fc,&DAT_00663450);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006634b4,&DAT_006634fc,&DAT_006635b8,&DAT_00663450);
    }
    return;
  case 0xf4:
    if ((sVar2 != 0) && (sVar3 != 0)) {
      if ((_DAT_006633a4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c4 | 0x1000);
        FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_006635b8,
                     (int *)&DAT_006634fc,(int *)&DAT_006635b8);
      }
      if ((_DAT_006633c4 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633a4 | 0x1000);
        FUN_00470250(&local_4,&DAT_006634fc,&DAT_006634fc,&DAT_006635b8);
      }
    }
    if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
      if ((_DAT_006633b0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633c0 | 0x1000);
        FUN_00470440(&local_4,&DAT_006634fc,&DAT_006635b8,&DAT_006635b8);
      }
      if ((_DAT_006633c0 & 0x1000) != 0) {
        local_4 = (void *)(_DAT_006633b0 | 0x1000);
        FUN_00470620(&local_4,&DAT_006634fc,&DAT_006635b8,&DAT_006634fc);
      }
    }
    uVar1 = (ushort)_DAT_006633c4;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
        ((_DAT_006633c4 & 0x1000) != 0)))) {
      FUN_00470060(self,(ushort *)&DAT_006633c4,(int *)&DAT_006634fc,
                   (int *)&DAT_006634fc,(int *)&DAT_006635b8);
      uVar1 = (ushort)_DAT_006633c4;
    }
    if (((short)_DAT_006633a4 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633a4 & 0x1000) != 0)))) {
      FUN_00470250(&DAT_006633a4,&DAT_006635b8,&DAT_006634fc,&DAT_006635b8);
    }
    uVar1 = (ushort)_DAT_006633c0;
    if ((uVar1 != 0) &&
       ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
        ((_DAT_006633c0 & 0x1000) != 0)))) {
      FUN_00470440(&DAT_006633c0,&DAT_006634fc,&DAT_006635b8,&DAT_006634fc);
      uVar1 = (ushort)_DAT_006633c0;
    }
    if (((short)_DAT_006633b0 != 0) &&
       (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
        ((_DAT_006633b0 & 0x1000) != 0)))) {
      FUN_00470620(&DAT_006633b0,&DAT_006634fc,&DAT_006635b8,&DAT_006635b8);
    }
    if (_DAT_006633bc != 0) {
      FUN_00470800(&DAT_006634fc,&DAT_006635b8,&DAT_006634fc,&DAT_006635b8);
    }
    return;
  default:
    return;
  }
}


// 0x00471ce0: EntityManager::sub_471CE0
// IDA: EntityManager::sub_471CE0
// Ghidra: FUN_00471ce0
void gta2::EntityManager_sub_471CE0(void *self)
{
  undefined1 uVar1;
  uint uVar2;
  SpriteS1 *pSVar3;
  Model *pMVar4;
  SpriteS1 *pSVar5;
  Model *pMVar6;
  SpriteS1 *pSVar7;
  uint uVar8;
  undefined4 uVar9;
  int iVar10;
  ushort uVar11;
  short sVar12;
  short sVar13;
  uint uVar14;
  PedStats *pPVar15;
  undefined *puVar16;
  int *piVar17;
  undefined *puVar18;
  SpriteS1 *local_1c;
  SpriteS1 *local_18 [6];
  
  uVar2 = _DAT_006633c4;
  uVar8 = _DAT_006633a4;
  if (gSkipSlopes == '\0') {
    iVar10 = (uint)(*(byte *)(_DAT_00663298 + 0xb) >> 2) * 0xc;
    _DAT_006633b4 = (uint)(byte)(&DAT_00662db1)[iVar10];
    _DAT_006633a8 = (Model *)(uint)(byte)(&DAT_00662db2)[iVar10];
    _DAT_006633b0 = CONCAT12((&DAT_00662db0)[iVar10],_DAT_006633b0);
    sVar13 = (short)_DAT_006633c4;
    sVar12 = (short)_DAT_006633a4;
    switch((&DAT_00662db0)[iVar10]) {
    case 1:
      if ((sVar13 != 0) && (sVar12 != 0)) {
        if ((_DAT_006633a4 & 0x1000) != 0) {
          gta2::Player_sub_40E530((Point2D *)&gS17_V1,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar2 | 0x1000);
          FUN_0046c2c0(&local_1c);
          UseAmmo(&gS17_V1,(int *)&DAT_00663450);
        }
        uVar8 = _DAT_006633a4;
        if ((_DAT_006633c4 & 0x1000) != 0) {
          UseAmmo(&gS17_V1,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar8 | 0x1000);
          FUN_0046c7f0(&local_1c);
          gta2::Player_sub_40E530((Point2D *)&gS17_V1,(int *)&DAT_00663450);
        }
      }
      uVar8 = _DAT_006633b0;
      if ((((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) &&
         ((_DAT_006633c0 & 0x1000) != 0)) {
        UseAmmo(&DAT_006636f0,(int *)&DAT_00663450);
        local_1c = (SpriteS1 *)(uVar8 | 0x1000);
        FUN_0046d9a0(&local_1c);
        gta2::Player_sub_40E530((Point2D *)&DAT_006636f0,(int *)&DAT_00663450);
      }
      uVar11 = (ushort)_DAT_006633a4;
      if (((short)_DAT_006633c4 != 0) &&
         (((uVar11 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
          ((_DAT_006633c4 & 0x1000) != 0)))) {
        FUN_0046c2c0(&DAT_006633c4);
        uVar11 = (ushort)_DAT_006633a4;
      }
      if ((uVar11 != 0) &&
         ((((short)_DAT_006633c4 == 0 || ((_DAT_006633c4 & 0x1000) == 0)) ||
          ((uVar11 & 0x1000) != 0)))) {
        FUN_0046c7f0(&DAT_006633a4);
      }
      if (((short)_DAT_006633c0 != 0) &&
         ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
          ((_DAT_006633c0 & 0x1000) != 0)))) {
        FUN_0046ce30(&DAT_006633c0);
      }
      uVar2 = _DAT_006633bc;
      uVar8 = _DAT_006633b4;
      pMVar6 = _DAT_006633a8;
      if (((short)_DAT_006633bc != 0) && (gSkipLid == 0)) {
        puVar18 = &DAT_006632e0;
        pMVar4 = (Model *)(_DAT_006633b4 - 1);
        if (_DAT_006633a8 == pMVar4) {
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&local_1c,
                              (S127 *)&DAT_00663450);
          FUN_0046bdf0(self,(PedStats *)pSVar5,(PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_00663300;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          pMVar4 = (Model *)FUN_0046bdf0(self,(PedStats *)&gS17_V1,
                                         (PedStats *)pSVar3,puVar18);
          uVar8 = _DAT_006633b4;
        }
        else {
          pSVar3 = (SpriteS1 *)local_18;
          piVar17 = (int *)&DAT_006633b4;
          iVar10 = (_DAT_006633b4 - (int)_DAT_006633a8) + -1;
          gta2::S202_sub_41F980((SpriteS1 *)&local_1c,iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 1),(S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 2),(S127 *)&DAT_00663450);
          pSVar7 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 3),
                              (S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)pSVar7,(PedStats *)pSVar5,
                     (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_00663300;
          pSVar3 = (SpriteS1 *)(local_18 + 3);
          piVar17 = (int *)&DAT_006633b4;
          pSVar5 = pSVar3;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 2),iVar10);
          pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar5,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 4),(S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 5),(S127 *)&DAT_00663450);
          pMVar4 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)&gS17_V1,
                                       (PedStats *)pSVar5,(PedStats *)pSVar3,
                                       puVar18);
          uVar2 = _DAT_006633bc;
        }
        puVar18 = &DAT_006632a0;
        if (pMVar6 == NULL) {
          FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632a0);
          puVar16 = &DAT_006632c0;
          puVar18 = &DAT_006636f0;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 5),
                              (S127 *)&DAT_00663450);
          FUN_0046bd40(pSVar3,puVar18,puVar16);
        }
        else {
          pSVar3 = (SpriteS1 *)(local_18 + 5);
          iVar10 = uVar8 - (int)pMVar6;
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 4),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 3),(S127 *)pSVar3);
          MatrixTransform3Advanced
                    (self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                     (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_006632c0;
          pSVar3 = (SpriteS1 *)(local_18 + 5);
          piVar17 = (int *)&DAT_006633b4;
          pSVar5 = pSVar3;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 4),iVar10);
          pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar5,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 2),(S127 *)pSVar3);
          pPVar15 = (PedStats *)&DAT_006636f0;
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 1),
                              (S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)pSVar5,pPVar15,(PedStats *)pSVar3,puVar18)
          ;
          uVar2 = _DAT_006633bc;
        }
        _DAT_006633b8 =
             *(uint *)(&DAT_00593174 + ((uVar2 & 0xffff) >> 0xd) * 4) | 1;
        if ((uVar2 & 0x1000) != 0) {
          _DAT_006633b8 =
               CONCAT31((int3)(*(uint *)(&DAT_00593174 +
                                        ((uVar2 & 0xffff) >> 0xd) * 4) >> 8),
                        (char)_DAT_006633b8) | 0x80;
        }
        local_18[0] = (SpriteS1 *)FUN_004bf6b0(uVar2 & 0x3ff);
        uVar8 = _DAT_006633bc >> 10 & 3;
        if ((short)uVar8 == 0) {
          local_1c = (SpriteS1 *)
                     CONCAT31(local_1c._1_3_,*(undefined1 *)((int)self + 0x14));
        }
        else {
          uVar1 = FUN_0046b5e0(uVar8);
          local_1c = (SpriteS1 *)CONCAT31(local_1c._1_3_,uVar1);
        }
        puVar18 = &DAT_006632a0;
        pSVar3 = local_1c;
        uVar9 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_18)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar9,puVar18,pSVar3);
        *(int *)((int)self + 0x2f00) = *(int *)((int)self + 0x2f00) + 1;
      }
      return;
    case 2:
      if ((sVar13 != 0) && (sVar12 != 0)) {
        if ((_DAT_006633a4 & 0x1000) != 0) {
          gta2::Player_sub_40E530((Point2D *)&gS17_V1,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar2 | 0x1000);
          FUN_0046c2c0(&local_1c);
          UseAmmo(&gS17_V1,(int *)&DAT_00663450);
        }
        uVar8 = _DAT_006633a4;
        if ((_DAT_006633c4 & 0x1000) != 0) {
          UseAmmo(&gS17_V1,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar8 | 0x1000);
          FUN_0046c7f0(&local_1c);
          gta2::Player_sub_40E530((Point2D *)&gS17_V1,(int *)&DAT_00663450);
        }
      }
      uVar8 = _DAT_006633c0;
      if ((((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) &&
         ((_DAT_006633b0 & 0x1000) != 0)) {
        gta2::Player_sub_40E530((Point2D *)&DAT_006636f0,(int *)&DAT_00663450);
        local_1c = (SpriteS1 *)(uVar8 | 0x1000);
        FUN_0046ce30(&local_1c);
        UseAmmo(&DAT_006636f0,(int *)&DAT_00663450);
      }
      uVar11 = (ushort)_DAT_006633a4;
      if (((short)_DAT_006633c4 != 0) &&
         (((uVar11 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
          ((_DAT_006633c4 & 0x1000) != 0)))) {
        FUN_0046c2c0(&DAT_006633c4);
        uVar11 = (ushort)_DAT_006633a4;
      }
      if ((uVar11 != 0) &&
         ((((short)_DAT_006633c4 == 0 || ((_DAT_006633c4 & 0x1000) == 0)) ||
          ((uVar11 & 0x1000) != 0)))) {
        FUN_0046c7f0(&DAT_006633a4);
      }
      if (((short)_DAT_006633b0 != 0) &&
         ((((short)_DAT_006633c0 == 0 || ((_DAT_006633c0 & 0x1000) == 0)) ||
          ((_DAT_006633b0 & 0x1000) != 0)))) {
        FUN_0046d9a0(&DAT_006633b0);
      }
      uVar2 = _DAT_006633bc;
      uVar8 = _DAT_006633b4;
      pMVar6 = _DAT_006633a8;
      if (((short)_DAT_006633bc != 0) && (gSkipLid == 0)) {
        pSVar3 = (SpriteS1 *)local_18;
        puVar18 = &DAT_006632e0;
        if (_DAT_006633a8 == NULL) {
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,pSVar3,
                              (S127 *)&DAT_00663450);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)&local_1c,
                              (S127 *)&DAT_00663450);
          FUN_0046bd40(pSVar5,pSVar3,puVar18);
          puVar18 = &DAT_00663300;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          FUN_0046bd40(&gS17_V1,pSVar3,puVar18);
          uVar8 = _DAT_006633b4;
        }
        else {
          piVar17 = (int *)&DAT_006633b4;
          iVar10 = _DAT_006633b4 - (int)_DAT_006633a8;
          pSVar5 = pSVar3;
          gta2::S202_sub_41F980((SpriteS1 *)&local_1c,iVar10);
          pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar5,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 1),(S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 2),(S127 *)&DAT_00663450);
          pSVar7 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 3),
                              (S127 *)&DAT_00663450);
          pMVar4 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)pSVar7,
                                       (PedStats *)pSVar5,(PedStats *)pSVar3,
                                       puVar18);
          puVar18 = &DAT_00663300;
          pSVar3 = (SpriteS1 *)(local_18 + 3);
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 2),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 4),(S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 5),(S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)&gS17_V1,(PedStats *)pSVar5,
                     (PedStats *)pSVar3,puVar18);
          uVar2 = _DAT_006633bc;
        }
        puVar18 = &DAT_006632a0;
        if (pMVar6 == (Model *)(uVar8 - 1)) {
          FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                       &DAT_006632a0);
          puVar18 = &DAT_006632c0;
          pPVar15 = (PedStats *)&DAT_006636f0;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 5),
                              (S127 *)&DAT_00663450);
          FUN_0046bdf0(self,(PedStats *)pSVar3,pPVar15,puVar18);
        }
        else {
          pSVar3 = (SpriteS1 *)(local_18 + 5);
          iVar10 = (uVar8 - (int)pMVar6) + -1;
          piVar17 = (int *)&DAT_006633b4;
          pSVar5 = pSVar3;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 4),iVar10);
          pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar5,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 3),(S127 *)pSVar3);
          pMVar6 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)&gS17_V1,
                                       (PedStats *)&DAT_006636f0,
                                       (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_006632c0;
          pSVar3 = (SpriteS1 *)(local_18 + 5);
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 4),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar6,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 2),(S127 *)pSVar3);
          pPVar15 = (PedStats *)&DAT_006636f0;
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 1),
                              (S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)pSVar5,pPVar15,(PedStats *)pSVar3,puVar18)
          ;
        }
        _DAT_006633b8 =
             *(uint *)(&DAT_00593174 + ((uVar2 & 0xffff) >> 0xd) * 4) | 2;
        if ((uVar2 & 0x1000) != 0) {
          _DAT_006633b8 =
               CONCAT31((int3)(*(uint *)(&DAT_00593174 +
                                        ((uVar2 & 0xffff) >> 0xd) * 4) >> 8),
                        (char)_DAT_006633b8) | 0x80;
        }
        local_18[0] = (SpriteS1 *)FUN_004bf6b0(uVar2 & 0x3ff);
        uVar8 = _DAT_006633bc >> 10 & 3;
        if ((short)uVar8 == 0) {
          uVar1 = *(undefined1 *)((int)self + 0x15);
        }
        else {
          uVar1 = FUN_0046b5e0(uVar8);
        }
        local_1c = (SpriteS1 *)CONCAT31(local_1c._1_3_,uVar1);
        puVar18 = &DAT_006632a0;
        pSVar3 = local_1c;
        uVar9 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_18)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar9,puVar18,pSVar3);
        *(int *)((int)self + 0x2f00) = *(int *)((int)self + 0x2f00) + 1;
      }
      return;
    case 3:
      if (((sVar13 != 0) && (sVar12 != 0)) && ((_DAT_006633c4 & 0x1000) != 0)) {
        UseAmmo(&gS17_V1,(int *)&DAT_00663450);
        local_1c = (SpriteS1 *)(uVar8 | 0x1000);
        uVar2 = FUN_0046c7f0(&local_1c);
        gta2::Player_sub_40E530((Point2D *)&gS17_V1,(int *)&DAT_00663450);
      }
      uVar8 = _DAT_006633c0;
      if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
        if ((_DAT_006633b0 & 0x1000) != 0) {
          gta2::Player_sub_40E530((Point2D *)&DAT_006636f0,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar8 | 0x1000);
          uVar2 = FUN_0046ce30(&local_1c);
          UseAmmo(&DAT_006636f0,(int *)&DAT_00663450);
        }
        uVar8 = _DAT_006633b0;
        if ((_DAT_006633c0 & 0x1000) != 0) {
          UseAmmo(&DAT_006636f0,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar8 | 0x1000);
          uVar2 = FUN_0046d9a0(&local_1c);
          gta2::Player_sub_40E530((Point2D *)&DAT_006636f0,(int *)&DAT_00663450);
        }
      }
      if (((short)_DAT_006633c4 != 0) &&
         ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
          (uVar2 = _DAT_006633a4, (_DAT_006633c4 & 0x1000) != 0)))) {
        uVar2 = FUN_0046c2c0(&DAT_006633c4);
      }
      uVar11 = (ushort)_DAT_006633b0;
      if (((short)_DAT_006633c0 != 0) &&
         (((uVar11 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
          ((_DAT_006633c0 & 0x1000) != 0)))) {
        uVar2 = FUN_0046ce30(&DAT_006633c0);
        uVar11 = (ushort)_DAT_006633b0;
      }
      if ((uVar11 != 0) &&
         ((((short)_DAT_006633c0 == 0 || ((_DAT_006633c0 & 0x1000) == 0)) ||
          ((uVar11 & 0x1000) != 0)))) {
        uVar2 = FUN_0046d9a0(&DAT_006633b0);
      }
      uVar14 = _DAT_006633bc;
      uVar8 = _DAT_006633b4;
      pMVar6 = _DAT_006633a8;
      if (((short)_DAT_006633bc != 0) &&
         (pMVar4 = (Model *)CONCAT31((int3)(uVar2 >> 8),gSkipLid), gSkipLid == 0
         )) {
        puVar18 = &DAT_006632a0;
        if (_DAT_006633a8 == NULL) {
          FUN_0046bd40(&gS17_V1,&DAT_006636f0,&DAT_006632a0);
          puVar18 = &DAT_00663300;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          FUN_0046bd40(&gS17_V1,pSVar3,puVar18);
          uVar8 = _DAT_006633b4;
        }
        else {
          pSVar3 = (SpriteS1 *)local_18;
          piVar17 = (int *)&DAT_006633b4;
          iVar10 = _DAT_006633b4 - (int)_DAT_006633a8;
          gta2::S202_sub_41F980((SpriteS1 *)&local_1c,iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 1),(S127 *)pSVar3);
          MatrixTransform3Advanced
                    (self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                     (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_00663300;
          pSVar3 = (SpriteS1 *)(local_18 + 1);
          piVar17 = (int *)&DAT_006633b4;
          pSVar5 = pSVar3;
          gta2::S202_sub_41F980((SpriteS1 *)local_18,iVar10);
          pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar5,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 2),(S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 3),(S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)&gS17_V1,(PedStats *)pSVar5,
                     (PedStats *)pSVar3,puVar18);
          uVar14 = _DAT_006633bc;
        }
        pMVar4 = (Model *)(uVar8 - 1);
        pSVar3 = (SpriteS1 *)(local_18 + 3);
        puVar18 = &DAT_006632c0;
        if (pMVar6 == pMVar4) {
          pPVar15 = (PedStats *)&DAT_006636f0;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,pSVar3,(S127 *)&DAT_00663450);
          FUN_0046bdf0(self,(PedStats *)pSVar3,pPVar15,puVar18);
          puVar18 = &DAT_006632e0;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 3),(S127 *)&DAT_00663450);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 2),
                              (S127 *)&DAT_00663450);
          FUN_0046bdf0(self,(PedStats *)pSVar5,(PedStats *)pSVar3,puVar18);
        }
        else {
          piVar17 = (int *)&DAT_006633b4;
          iVar10 = (uVar8 - (int)pMVar6) + -1;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 2),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 1),(S127 *)pSVar3);
          pPVar15 = (PedStats *)&DAT_006636f0;
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          pMVar6 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)pSVar5,pPVar15,
                                       (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_006632e0;
          pSVar3 = (SpriteS1 *)(local_18 + 3);
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 2),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar6,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)&local_1c,
                              (S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 4),(S127 *)&DAT_00663450);
          pSVar7 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 5),
                              (S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)pSVar7,(PedStats *)pSVar5,
                     (PedStats *)pSVar3,puVar18);
        }
        _DAT_006633b8 =
             *(uint *)(&DAT_00593174 + ((uVar14 & 0xffff) >> 0xd) * 4) | 3;
        if ((uVar14 & 0x1000) != 0) {
          _DAT_006633b8 =
               CONCAT31((int3)(*(uint *)(&DAT_00593174 +
                                        ((uVar14 & 0xffff) >> 0xd) * 4) >> 8),
                        (char)_DAT_006633b8) | 0x80;
        }
        local_18[0] = (SpriteS1 *)FUN_004bf6b0(uVar14 & 0x3ff);
        uVar8 = _DAT_006633bc >> 10 & 3;
        if ((short)uVar8 == 0) {
          uVar1 = *(undefined1 *)((int)self + 0x16);
        }
        else {
          uVar1 = FUN_0046b5e0(uVar8);
        }
        local_1c = (SpriteS1 *)CONCAT31(local_1c._1_3_,uVar1);
        puVar18 = &DAT_006632a0;
        pSVar3 = local_1c;
        uVar9 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_18)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar9,puVar18,pSVar3);
        *(int *)((int)self + 0x2f00) = *(int *)((int)self + 0x2f00) + 1;
      }
      return;
    case 4:
      if (((sVar13 != 0) && (sVar12 != 0)) && ((_DAT_006633a4 & 0x1000) != 0)) {
        gta2::Player_sub_40E530((Point2D *)&gS17_V1,(int *)&DAT_00663450);
        local_1c = (SpriteS1 *)(uVar2 | 0x1000);
        FUN_0046c2c0(&local_1c);
        UseAmmo(&gS17_V1,(int *)&DAT_00663450);
      }
      uVar8 = _DAT_006633c0;
      if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
        if ((_DAT_006633b0 & 0x1000) != 0) {
          gta2::Player_sub_40E530((Point2D *)&DAT_006636f0,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar8 | 0x1000);
          FUN_0046ce30(&local_1c);
          UseAmmo(&DAT_006636f0,(int *)&DAT_00663450);
        }
        uVar8 = _DAT_006633b0;
        if ((_DAT_006633c0 & 0x1000) != 0) {
          UseAmmo(&DAT_006636f0,(int *)&DAT_00663450);
          local_1c = (SpriteS1 *)(uVar8 | 0x1000);
          FUN_0046d9a0(&local_1c);
          gta2::Player_sub_40E530((Point2D *)&DAT_006636f0,(int *)&DAT_00663450);
        }
      }
      if (((short)_DAT_006633a4 != 0) &&
         ((((short)_DAT_006633c4 == 0 || ((_DAT_006633c4 & 0x1000) == 0)) ||
          ((_DAT_006633a4 & 0x1000) != 0)))) {
        FUN_0046c7f0(&DAT_006633a4);
      }
      uVar11 = (ushort)_DAT_006633b0;
      if (((short)_DAT_006633c0 != 0) &&
         (((uVar11 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
          ((_DAT_006633c0 & 0x1000) != 0)))) {
        FUN_0046ce30(&DAT_006633c0);
        uVar11 = (ushort)_DAT_006633b0;
      }
      if ((uVar11 != 0) &&
         ((((short)_DAT_006633c0 == 0 || ((_DAT_006633c0 & 0x1000) == 0)) ||
          ((uVar11 & 0x1000) != 0)))) {
        FUN_0046d9a0(&DAT_006633b0);
      }
      uVar2 = _DAT_006633bc;
      uVar8 = _DAT_006633b4;
      pMVar6 = _DAT_006633a8;
      if (((short)_DAT_006633bc != 0) && (gSkipLid == 0)) {
        puVar18 = &DAT_006632a0;
        if (_DAT_006633a8 == (Model *)(_DAT_006633b4 - 1)) {
          FUN_0046bdf0(self,(PedStats *)&gS17_V1,(PedStats *)&DAT_006636f0,
                       &DAT_006632a0);
          puVar18 = &DAT_00663300;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          pMVar4 = (Model *)FUN_0046bdf0(self,(PedStats *)&gS17_V1,
                                         (PedStats *)pSVar3,puVar18);
          uVar8 = _DAT_006633b4;
        }
        else {
          pSVar3 = (SpriteS1 *)local_18;
          piVar17 = (int *)&DAT_006633b4;
          iVar10 = (_DAT_006633b4 - (int)_DAT_006633a8) + -1;
          pSVar5 = pSVar3;
          gta2::S202_sub_41F980((SpriteS1 *)&local_1c,iVar10);
          pSVar3 = gta2::S122_sub_401BF0((Model *)pSVar3,pSVar5,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 1),(S127 *)pSVar3);
          pMVar4 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)&gS17_V1,
                                       (PedStats *)&DAT_006636f0,
                                       (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_00663300;
          pSVar3 = (SpriteS1 *)(local_18 + 1);
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)local_18,iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 2),(S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 3),(S127 *)&DAT_00663450);
          pMVar4 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)&gS17_V1,
                                       (PedStats *)pSVar5,(PedStats *)pSVar3,
                                       puVar18);
          uVar2 = _DAT_006633bc;
        }
        pSVar3 = (SpriteS1 *)(local_18 + 3);
        puVar18 = &DAT_006632c0;
        if (pMVar6 == NULL) {
          puVar16 = &DAT_006636f0;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,pSVar3,(S127 *)&DAT_00663450);
          FUN_0046bd40(pSVar3,puVar16,puVar18);
          puVar18 = &DAT_006632e0;
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 3),(S127 *)&DAT_00663450);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 2),
                              (S127 *)&DAT_00663450);
          FUN_0046bd40(pSVar5,pSVar3,puVar18);
        }
        else {
          iVar10 = uVar8 - (int)pMVar6;
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 2),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar4,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,
                              (SpriteS1 *)(local_18 + 1),(S127 *)pSVar3);
          pPVar15 = (PedStats *)&DAT_006636f0;
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)local_18,
                              (S127 *)&DAT_00663450);
          pMVar6 = (Model *)MatrixTransform3Advanced
                                      (self,(PedStats *)pSVar5,pPVar15,
                                       (PedStats *)pSVar3,puVar18);
          puVar18 = &DAT_006632e0;
          pSVar3 = (SpriteS1 *)(local_18 + 3);
          piVar17 = (int *)&DAT_006633b4;
          gta2::S202_sub_41F980((SpriteS1 *)(local_18 + 2),iVar10);
          pSVar3 = gta2::S122_sub_401BF0(pMVar6,pSVar3,piVar17);
          pSVar3 = gta2::S202_sub_401B20((Point2D *)&DAT_00663738,(SpriteS1 *)&local_1c,
                              (S127 *)pSVar3);
          pSVar5 = gta2::S202_sub_401B20((Point2D *)&DAT_006636f0,
                              (SpriteS1 *)(local_18 + 4),(S127 *)&DAT_00663450);
          pSVar7 = gta2::S202_sub_401B20((Point2D *)&gS17_V1,(SpriteS1 *)(local_18 + 5),
                              (S127 *)&DAT_00663450);
          MatrixTransform3Advanced
                    (self,(PedStats *)pSVar7,(PedStats *)pSVar5,
                     (PedStats *)pSVar3,puVar18);
        }
        _DAT_006633b8 =
             *(uint *)(&DAT_00593174 + ((uVar2 & 0xffff) >> 0xd) * 4) | 4;
        if ((uVar2 & 0x1000) != 0) {
          _DAT_006633b8 =
               CONCAT31((int3)(*(uint *)(&DAT_00593174 +
                                        ((uVar2 & 0xffff) >> 0xd) * 4) >> 8),
                        (char)_DAT_006633b8) | 0x80;
        }
        local_18[0] = (SpriteS1 *)FUN_004bf6b0(uVar2 & 0x3ff);
        uVar8 = _DAT_006633bc >> 10 & 3;
        if ((short)uVar8 == 0) {
          local_1c = (SpriteS1 *)
                     CONCAT31(local_1c._1_3_,*(undefined1 *)((int)self + 0x17));
        }
        else {
          uVar1 = FUN_0046b5e0(uVar8);
          local_1c = (SpriteS1 *)CONCAT31(local_1c._1_3_,uVar1);
        }
        puVar18 = &DAT_006632a0;
        pSVar3 = local_1c;
        uVar9 = gta2::TextureManager_getTexture4M(gTextureManager,(ushort *)local_18)
        ;
        (*(code *)gbh_DrawTile)
                  (gTimeDayAndNight | _DAT_006633b8,uVar9,puVar18,pSVar3);
        *(int *)((int)self + 0x2f00) = *(int *)((int)self + 0x2f00) + 1;
      }
      return;
    }
  }
  return;
}


// 0x00471d60: EntityManager::sub_471D60
// IDA: EntityManager::sub_471D60
// Ghidra: FUN_00471d60
void gta2::EntityManager_sub_471D60(void *self)
{
  ushort uVar1;
  void *local_4;
  
  _DAT_006633b0 = (uint3)_DAT_006633b0;
  local_4 = self;
  if (((short)_DAT_006633c4 != 0) && ((short)_DAT_006633a4 != 0)) {
    if ((_DAT_006633a4 & 0x1000) != 0) {
      local_4 = (void *)(_DAT_006633c4 | 0x1000);
      FUN_00470060(self,(ushort *)&local_4,(int *)&DAT_00663450,
                   (int *)&DAT_006634b4,(int *)&DAT_00663450);
    }
    if ((_DAT_006633c4 & 0x1000) != 0) {
      local_4 = (void *)(_DAT_006633a4 | 0x1000);
      FUN_00470250(&local_4,&DAT_006634b4,&DAT_006634b4,&DAT_00663450);
    }
  }
  if (((short)_DAT_006633c0 != 0) && ((short)_DAT_006633b0 != 0)) {
    if ((_DAT_006633b0 & 0x1000) != 0) {
      local_4 = (void *)(_DAT_006633c0 | 0x1000);
      FUN_00470440(&local_4,&DAT_006634b4,&DAT_00663450,&DAT_00663450);
    }
    if ((_DAT_006633c0 & 0x1000) != 0) {
      local_4 = (void *)(_DAT_006633b0 | 0x1000);
      FUN_00470620(&local_4,&DAT_006634b4,&DAT_00663450,&DAT_006634b4);
    }
  }
  uVar1 = (ushort)_DAT_006633c4;
  if ((uVar1 != 0) &&
     ((((short)_DAT_006633a4 == 0 || ((_DAT_006633a4 & 0x1000) == 0)) ||
      ((_DAT_006633c4 & 0x1000) != 0)))) {
    FUN_0046c2c0(&DAT_006633c4);
    uVar1 = (ushort)_DAT_006633c4;
  }
  if (((short)_DAT_006633a4 != 0) &&
     (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
      ((_DAT_006633a4 & 0x1000) != 0)))) {
    FUN_0046c7f0(&DAT_006633a4);
  }
  uVar1 = (ushort)_DAT_006633c0;
  if ((uVar1 != 0) &&
     ((((short)_DAT_006633b0 == 0 || ((_DAT_006633b0 & 0x1000) == 0)) ||
      ((_DAT_006633c0 & 0x1000) != 0)))) {
    FUN_0046ce30(&DAT_006633c0);
    uVar1 = (ushort)_DAT_006633c0;
  }
  if (((short)_DAT_006633b0 != 0) &&
     (((uVar1 == 0 || ((uVar1 & 0x1000) == 0)) ||
      ((_DAT_006633b0 & 0x1000) != 0)))) {
    FUN_0046d9a0(&DAT_006633b0);
  }
  if (_DAT_006633bc != 0) {
    FUN_0046dfe0(self);
  }
  return;
}


// 0x00471f20: EntityManager::sub_471F20
// IDA: EntityManager::sub_471F20
// Ghidra: FUN_00471f20
void gta2::EntityManager_sub_471F20(void *self,SpriteS1 *param_1,SpriteS1 *pCar)
{
  ushort uVar1;
  ushort uVar2;
  ushort uVar3;
  ushort uVar4;
  SpriteS1 *pSVar5;
  byte bVar6;
  ushort *puVar7;
  SpriteS1 *pSVar8;
  undefined4 *puVar9;
  GlassInfo *pGVar10;
  S127 *pSVar11;
  CameraOrPhysics *pCameraOrPhysics;
  
  pSVar5 = pCar;
  pSVar8 = param_1;
  puVar7 = (ushort *)
           gta2::MapRelatedStruct_sub_465490(gMapRelatedStruct,(int)param_1->FirstElement,
                      (Turrel *)pCar->FirstElement,_DAT_006633a0);
  pCameraOrPhysics = gCameraOrPhysics;
  _DAT_00663298 = puVar7;
  if (puVar7 != NULL) {
    uVar1 = *puVar7;
    _DAT_006633c4 = CONCAT22(DAT_006633c4_2,uVar1);
    uVar2 = puVar7[1];
    _DAT_006633a4 = CONCAT22(DAT_006633a4_2,uVar2);
    uVar3 = puVar7[2];
    _DAT_006633c0 = CONCAT22(DAT_006633c0_2,uVar3);
    uVar4 = puVar7[3];
    _DAT_006633b0 = CONCAT22(_DAT_006633b2,uVar4);
    _DAT_006633bc = puVar7[4];
    if (gShowHiddenFaces != false) {
      if ((_DAT_006633bc == 0) && ((*(byte *)((int)puVar7 + 0xb) & 3) != 0)) {
        _DAT_006633bc = 0x260;
      }
      if (((uVar1 & 0x400) != 0) && ((uVar1 & 0x3ff) == 0)) {
        _DAT_006633c4 = CONCAT22(DAT_006633c4_2,uVar1) | 0x260;
      }
      if (((uVar2 & 0x400) != 0) && ((uVar2 & 0x3ff) == 0)) {
        _DAT_006633a4 = CONCAT22(DAT_006633a4_2,uVar2) | 0x260;
      }
      if (((uVar3 & 0x400) != 0) && ((uVar3 & 0x3ff) == 0)) {
        _DAT_006633c0 = CONCAT22(DAT_006633c0_2,uVar3) | 0x260;
      }
      if (((uVar4 & 0x400) != 0) && ((uVar4 & 0x3ff) == 0)) {
        _DAT_006633b0 = CONCAT22(_DAT_006633b2,uVar4) | 0x260;
      }
    }
    pSVar8 = pSVar8->FirstElement;
    pGVar10 = (GlassInfo *)&pCar;
    pSVar11 = (S127 *)&gCameraOrPhysics->field_0x98;
    gta2::S202_sub_41F980((SpriteS1 *)&param_1,(int)pSVar8);
    puVar9 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)pSVar8,pGVar10,pSVar11);
    _gS17_V1 = *puVar9;
    pSVar11 = (S127 *)&pCameraOrPhysics->field_0x9c;
    pSVar8 = pSVar5->FirstElement;
    pGVar10 = (GlassInfo *)&pCar;
    gta2::S202_sub_41F980((SpriteS1 *)&param_1,(int)pSVar8);
    puVar9 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)pSVar8,pGVar10,pSVar11);
    _DAT_006636f0 = *puVar9;
    bVar6 = *(byte *)((int)puVar7 + 0xb) & 0xfc;
    if ((0xb3 < bVar6) && (bVar6 < 0xc1)) {
      FUN_0046edd0(self);
      return;
    }
    if ((0xc3 < bVar6) && (bVar6 < 0xd1)) {
      FUN_0046ee40(self);
      return;
    }
    if ((0xd3 < bVar6) && (bVar6 < 0xf5)) {
      FUN_00471c30(self);
      return;
    }
    if ((bVar6 != 0) && (bVar6 < 0xb4)) {
      FUN_00471ce0(self);
      return;
    }
    FUN_00471d60(self);
  }
  return;
}


// 0x004720e0: EntityManager::sub_4720E0
// IDA: EntityManager::sub_4720E0
// Ghidra: ---
void gta2::EntityManager_sub_4720E0(struct EntityManager *self)
{
  int v2; // eax
  char *v3; // esi
  int v4; // ebx

  v2 = self->field_2EFC;
  v3 = &self->field_14 + 8 * v2;
  if ( v2 - 1 >= 0 )
  {
    v4 = self->field_2EFC;
    do
    {
      gta2::EntityManager_sub_471F20(self, (int *)v3, (SpriteS1 *)(v3 + 4));
      v3 -= 8;
      --v4;
    }
    while ( v4 );
  }
}


// 0x00472110: EntityManager::sub_472110
// IDA: EntityManager::sub_472110
// Ghidra: ---
int gta2::EntityManager_sub_472110(struct EntityManager *self, int *a2)
{
  int v3; // ebx
  CameraOrPhysics *pCameraOrPhysics; // esi
  int v5; // ebp
  PublicTransport *v6; // edi
  S202 *v7; // eax
  int v8; // eax
  SpriteS1 *v9; // eax
  PublicTransport *v10; // eax
  SpriteS1 *v11; // eax
  int v12; // ebx
  int v13; // eax
  SpriteS1 *v14; // eax
  PublicTransport *v15; // eax
  SpriteS1 *v16; // eax
  int *v17; // eax
  S202 *v18; // eax
  SpriteS1 *FirstElement; // ecx
  Radar *p_Car; // esi
  SpriteS1 *v21; // eax
  int v22; // ebp
  S202 *v23; // eax
  SpriteS1 *v24; // ecx
  void *S122; // esi
  int v26; // ecx
  int v27; // eax
  int v28; // ebx
  S122 *v29; // ebp
  int v30; // esi
  int v31; // edi
  float v33; // [esp+0h] [ebp-A4h]
  float v34; // [esp+4h] [ebp-A0h]
  float v35; // [esp+8h] [ebp-9Ch]
  PublicTransport *pCameraOrPhysics_1; // [esp+Ch] [ebp-98h]
  float v37; // [esp+Ch] [ebp-98h]
  EntityManager *v38; // [esp+10h] [ebp-94h]
  float v39; // [esp+10h] [ebp-94h]
  int v40; // [esp+14h] [ebp-90h] BYREF
  S122 *a3; // [esp+18h] [ebp-8Ch] BYREF
  int v42; // [esp+1Ch] [ebp-88h]
  int v43; // [esp+20h] [ebp-84h]
  EntityManager *pS17; // [esp+24h] [ebp-80h] BYREF
  S122 v45; // [esp+28h] [ebp-7Ch] BYREF
  char v46; // [esp+68h] [ebp-3Ch] BYREF
  int WindowHeight; // [esp+6Ch] [ebp-38h] BYREF
  S202 pS202; // [esp+70h] [ebp-34h] BYREF
  char v49; // [esp+90h] [ebp-14h] BYREF
  int v50; // [esp+94h] [ebp-10h] BYREF
  char v51[4]; // [esp+98h] [ebp-Ch] BYREF
  char v52; // [esp+9Ch] [ebp-8h] BYREF

  pS17 = self;
  if ( gLighting )
  {
    v39 = gta2::Float10_EncodedFloatToRegularFloat(&self->dword_5EB854);
    gbh_SetAmbient((void *)LODWORD(v39));
    gta2::sub_46C1A0(&self->dword_5EB854);
  }
  v3 = 0;
  v45.field_8 = 0;
  do
  {
    if ( v3 )
      gta2::Display_resetModes(gDisplay, v3);
    if ( !skip_tiles )
    {
      pCameraOrPhysics = gCameraOrPhysics;
      v5 = 8 - v3;
      v6 = (PublicTransport *)&gCameraOrPhysics->cameraPosTarget_[3].field_24;
      pCameraOrPhysics_1 = (PublicTransport *)&gCameraOrPhysics->cameraPosTarget_[3].field_24;
      gta2::S202_sub_41F980((S202 *)&v45.field_28, 8 - v3);
      v45.field_14 = (int)gta2::S202_sub_401B20(v7, (SpriteS1 *)&v45.field_24, pCameraOrPhysics_1)->FirstElement;
      *(_DWORD *)&v45.field0 = *(_DWORD *)gta2::sub_401B90(
                                            &v45.field_14,
                                            &v45.field_2C,
                                            &pCameraOrPhysics->cameraPosTarget_[4].fild);
      v45.S122 = (S122 *)gta2::Radar_AddBlip((Radar *)&v45, (SpriteS1 *)&v45.field_30, (PublicTransport *)&unk_6636C8)->FirstElement;
      v45.field_14 = 2;
      gta2::S122_sub_401BF0(&v45, (int)&v45.field_34, (int)&v45.field_14);
      v9 = gta2::Player_sub_401B40((Player *)&pCameraOrPhysics->cameraPosTarget_[3].Player, (S202 *)&v45.field_38, v8);
      v45.field_4 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v9);
      v45.field_14 = 2;
      gta2::S122_sub_401BF0(&v45, (int)&v45.field_3C, (int)&v45.field_14);
      v11 = gta2::S202_sub_401B20((S202 *)&pCameraOrPhysics->cameraPosTarget_[3].Player, (SpriteS1 *)&v46, v10);
      *(_DWORD *)&v45.field_10 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v11);
      v12 = (*(_DWORD *)&v45.field_10 - v45.field_4 + 1) / 2;
      if ( (*(_DWORD *)&v45.field_10 - v45.field_4) % 2 != 1 )
        ++v12;
      v45.field_14 = 2;
      gta2::S122_sub_401BF0((S122 *)&v45.S122, (int)&WindowHeight, (int)&v45.field_14);
      v14 = gta2::Player_sub_401B40((Player *)&pCameraOrPhysics->cameraPosTarget_[3].field_20, &pS202, v13);
      *(_DWORD *)&v45.field0 = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v14);
      v45.field_14 = 2;
      gta2::S122_sub_401BF0((S122 *)&v45.S122, (int)&pS202.S202, (int)&v45.field_14);
      v16 = gta2::S202_sub_401B20(
              (S202 *)&pCameraOrPhysics->cameraPosTarget_[3].field_20,
              (SpriteS1 *)&pS202.CarSystemManager,
              v15);
      v45.S122 = (S122 *)gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)v16);
      v45.field_14 = (int)(&v45.S122->field_1 - *(_DWORD *)&v45.field0) / 2;
      if ( ((int)v45.S122 - *(_DWORD *)&v45.field0) % 2 != 1 )
        v45.field_14 = (int)(&v45.S122->field_1 - *(_DWORD *)&v45.field0) / 2 + 1;
      unk_6633A0 = v45.field_8;
      gta2::S202_sub_41F980((S202 *)&pS202.field_C, v45.field_8);
      unk_663738.field_0 = *v17;
      gta2::S202_sub_41F980((S202 *)&pS202.pPlayer, v5);
      pS17 = (EntityManager *)gta2::S202_sub_401B20(v18, (SpriteS1 *)&pS202.field_10, v6)->FirstElement;
      if ( gta2::Player_IsCurrentPlayer((Player *)&pS17, (Player *)&unk_6634B4) )
        FirstElement = unk_6634B4.FirstElement;
      else
        FirstElement = *(SpriteS1 **)gta2::sub_401B90(&dword_663450, &pS202.field_18, &pS17);
      p_Car = (Radar *)&pCameraOrPhysics->cameraPosTarget_[2].Car;
      unk_66364C = (int)FirstElement;
      v21 = gta2::Radar_AddBlip(p_Car, (SpriteS1 *)&pS202.field_1C, (PublicTransport *)&unk_66364C);
      v22 = v45.field_8;
      unk_6633CC = (int)v21->FirstElement;
      unk_6633AC = v45.field_8 + 1;
      gta2::S202_sub_41F980((S202 *)&v50, 8 - (v45.field_8 + 1));
      pS17 = (EntityManager *)gta2::S202_sub_401B20(v23, (SpriteS1 *)&v49, v6)->FirstElement;
      if ( gta2::Player_IsCurrentPlayer((Player *)&pS17, (Player *)&unk_6634B4) )
        v24 = unk_6634B4.FirstElement;
      else
        v24 = *(SpriteS1 **)gta2::sub_401B90(&dword_663450, v51, &pS17);
      unk_6635FC = (int)v24;
      unk_663504 = (int)gta2::Radar_AddBlip(p_Car, (SpriteS1 *)&v52, (PublicTransport *)&unk_6635FC)->FirstElement;
      if ( v22 || !gLighting )
      {
        S122 = v45.S122;
      }
      else
      {
        gbh_ResetLights[0]();
        v37 = (float)(int)v45.S122;
        v35 = (float)*(int *)&v45.field_10;
        v34 = (float)*(int *)&v45.field0;
        v33 = (float)v45.field_4;
        gbh_SetCamera(LODWORD(v33), LODWORD(v34), LODWORD(v35), LODWORD(v37));
        S122 = pS17;
        gta2::sub_461400(v42, (int)a3, *(int *)&v45.field0, (int)pS17);
      }
      gta2::EntityManager_sub_45B040(v38);
      v26 = v45.field_4 - 1;
      if ( v45.field_4 - 1 >= 0 )
      {
        v27 = v12 - 1;
        v28 = (int)S122 - v26;
        v29 = (S122 *)((char *)a3 + v26);
        *(_DWORD *)&v45.field_10 = v27;
        pS17 = (EntityManager *)v45.field_4;
        do
        {
          if ( v27 >= 0 )
          {
            v30 = *(_DWORD *)&v45.field0 - v27;
            v45.field_8 = v28;
            v31 = v27 + v42;
            v45.S122 = v29;
            v45.field_4 = v27 + 1;
            do
            {
              a3 = (S122 *)v28;
              v40 = v30;
              gta2::EntityManager_sub_46BB90(v38, &v40, &a3);
              a3 = (S122 *)v31;
              gta2::EntityManager_sub_46BB90(v38, &a3, &v45.field_8);
              a3 = v29;
              v40 = v30;
              gta2::EntityManager_sub_46BB90(v38, &v40, &a3);
              a3 = (S122 *)v31;
              gta2::EntityManager_sub_46BB90(v38, &a3, &v45.S122);
              ++v30;
              --v31;
              --v45.field_4;
            }
            while ( v45.field_4 );
            v27 = *(_DWORD *)&v45.field_10;
          }
          ++v28;
          v29 = (S122 *)((char *)v29 - 1);
          pS17 = (EntityManager *)((char *)pS17 - 1);
        }
        while ( pS17 );
      }
      gta2::EntityManager_sub_4720E0(v38);
      v3 = v43;
    }
    v43 = ++v3;
  }
  while ( v3 < 7 );
  return gta2::Display_resetModes(gDisplay, 7);
}



