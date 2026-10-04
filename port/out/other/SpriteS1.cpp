#include "gta2_shim.h"

// Module: other, Class: SpriteS1
// Functions: 43
// Source: unified (IDA+Ghidra)

// 0x00472c00: SpriteS1::sub_472C00
// IDA: SpriteS1::sub_472C00
// Ghidra: GameObject::FUN_00472c00
byte gta2::SpriteS1_sub_472C00(struct GameObject *self,CarSystemManager *pCarSystemManager)
{
  bool bVar1;
  bool bVar2;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  
  bVar1 = less_or_equal(pCarSystemManager,(short *)&DAT_00663804);
  if (CONCAT31(extraout_var,bVar1) == 0) {
    bVar2 = gta2::CarSystemManager_greater_than(pCarSystemManager,(short *)&DAT_00663948);
    if (CONCAT31(extraout_var_00,bVar2) == 0) {
      bVar2 = gta2::CarSystemManager_less_than(pCarSystemManager,(short *)&DAT_00663854);
      if (CONCAT31(extraout_var_01,bVar2) != 0) {
        return 3;
      }
      bVar2 = gta2::CarSystemManager_less_than(pCarSystemManager,(short *)&DAT_006638c8);
      return (-(CONCAT31(extraout_var_02,bVar2) != 0) & 0xfdU) + 4;
    }
  }
  return 2;
}


// 0x00482a30: SpriteS1::SetS63
// IDA: SpriteS1::SetS63
// Ghidra: ---
EventHandler * gta2::SpriteS1_SetS63(struct SpriteS1 *self, EventHandler *a2)
{
  struct EventHandler *result; // eax

  result = a2;
  self->S3_arr5031[0].GameObject = (struct GameObject *)a2;
  return result;
}


// 0x00488200: SpriteS1::sub_488200
// IDA: SpriteS1::sub_488200
// Ghidra: FUN_00488200
void gta2::SpriteS1_sub_488200(int param_1,undefined1 param_2)
{
  *(undefined1 *)(param_1 + 0x2c) = param_2;
  return;
}


// 0x0048a8d0: SpriteS1::IsNotEmpty
// IDA: SpriteS1::IsNotEmpty
// Ghidra: ---
bool gta2::SpriteS1_IsNotEmpty(struct SpriteS1 *self)
{
  return self->FirstElement != 0;
}


// 0x00492180: SpriteS1::SetGameObject
// IDA: SpriteS1::SetGameObject
// Ghidra: ---
void gta2::SpriteS1_SetGameObject(struct SpriteS1 *self, GameObject *pS51)
{
  self->S3_arr5031[0].GameObject = pS51;
}


// 0x0049ea30: SpriteS1::sub_49EA30
// IDA: SpriteS1::sub_49EA30
// Ghidra: FUN_0049ea30
void * gta2::SpriteS1_sub_49EA30(int param_1,void *param_2,int param_3)
{
  String_ParseLine(param_2,(undefined4 *)
                           (*(int *)(param_1 + 0xc) + 0xc + param_3 * 8),
                   (undefined4 *)(*(int *)(param_1 + 0xc) + 0x10 + param_3 * 8))
  ;
  return param_2;
}


// 0x004b99f0: SpriteS1::sub_4B99F0
// IDA: SpriteS1::sub_4B99F0
// Ghidra: ---
SpriteS3 * gta2::SpriteS1_sub_4B99F0(struct SpriteS1 *self)
{
  struct SpriteS3 *pSpriteS3; // eax
  struct SpriteS1 *SpriteS1; // ecx

  pSpriteS3 = self->S3_arr5031[0].SpriteS3;
  BYTE1(self->S3_arr5031[0].field_34) = -1;
  if ( pSpriteS3 )
    LOBYTE(pSpriteS3->S39_Arr48[3].field_C) = 0;
  SpriteS1 = self->S3_arr5031[0].SpriteS1_;
  if ( SpriteS1 )
    LOBYTE(SpriteS1->S3_arr5031[1].SpriteS3) = 0;
  return pSpriteS3;
}


// 0x004b9aa0: SpriteS1::sub_4B9AA0
// IDA: SpriteS1::sub_4B9AA0
// Ghidra: ---
int gta2::SpriteS1_sub_4B9AA0(struct SpriteS1 *self)
{
  int result; // eax

  result = self->S3_arr5031[0].sprite_type;
  switch ( result )
  {
    case 0:
    case 1:
      self->S3_arr5031[0].field_24 = 0;
      break;
    case 2:
      self->S3_arr5031[0].field_24 = 15;
      break;
    case 3:
      self->S3_arr5031[0].field_24 = 23;
      break;
    case 4:
    case 5:
      self->S3_arr5031[0].field_24 = 2;
      break;
    case 8:
      self->S3_arr5031[0].field_24 = 33;
      break;
    default:
      return result;
  }
  return result;
}


// 0x004b9b00: SpriteS1::SetRemap
// IDA: SpriteS1::SetRemap
// Ghidra: ---
__int16 gta2::SpriteS1_SetRemap(struct SpriteS1 *self, __int16 Remap)
{
  __int16 result; // ax

  switch ( self->S3_arr5031[0].sprite_type )
  {
    case 2:
      result = Remap;
      self->S3_arr5031[0].field_30 = 3;
      self->S3_arr5031[0].Remap = Remap;
      break;
    case 3:
      result = Remap;
      self->S3_arr5031[0].field_30 = 4;
      self->S3_arr5031[0].Remap = Remap;
      break;
    case 4:
    case 8:
      result = Remap;
      self->S3_arr5031[0].field_30 = 5;
      self->S3_arr5031[0].Remap = Remap;
      break;
    case 5:
      result = Remap;
      self->S3_arr5031[0].field_30 = 6;
      self->S3_arr5031[0].Remap = Remap;
      break;
    case 6:
      result = Remap;
      self->S3_arr5031[0].field_30 = 7;
      self->S3_arr5031[0].Remap = Remap;
      break;
    case 7:
      self->S3_arr5031[0].field_30 = 8;
      goto LABEL_8;
    default:
LABEL_8:
      result = Remap;
      self->S3_arr5031[0].Remap = Remap;
      break;
  }
  return result;
}


// 0x004b9ca0: SpriteS1::sub_4B9CA0
// IDA: SpriteS1::sub_4B9CA0
// Ghidra: Sprite::FUN_004b9ca0
void gta2::SpriteS1_sub_4B9CA0(Sprite *self)
{
  int *piVar1;
  
  if ((*(int *)&self->field_0x10 == 0) && (!gSkipAudio)) {
    piVar1 = gta2::DMAudio_sub_410750(&gDMAudio,self,1);
    *(int **)&self->field_0x10 = piVar1;
  }
  return;
}


// 0x004b9cd0: SpriteS1::sub_4B9CD0
// IDA: SpriteS1::sub_4B9CD0
// Ghidra: ---
int gta2::SpriteS1_sub_4B9CD0(struct SpriteS1 *self)
{
  int result; // eax
  __int16 v2; // dx

  result = 0;
  self->S3_arr5031[0].field_28 = 0;
  self->S3_arr5031[0].field_24 = 0;
  self->S3_arr5031[0].GameObject = 0;
  self->S3_arr5031[0].PositionX = (int)unk_670010;
  self->S3_arr5031[0].PositionY = (int)unk_670010;
  self->S3_arr5031[0].PositionZ = (int)unk_670010;
  BYTE1(self->S3_arr5031[0].field_34) = -1;
  v2 = *(_WORD *)unk_66FF7C;
  HIWORD(self->S3_arr5031[0].spriteId) = 0;
  LOWORD(self->FirstElement) = v2;
  self->S3_arr5031[0].Remap = 0;
  self->S3_arr5031[0].field_30 = 2;
  self->S3_arr5031[0].SpriteS3 = 0;
  self->S3_arr5031[0].SpriteS1_ = 0;
  LOBYTE(self->S3_arr5031[0].field_34) = 0;
  self->S3_arr5031[0].NextElement = 0;
  LOWORD(self->S3_arr5031[0].spriteId) = gSpriteEntry->W++;
  if ( !gSpriteEntry->W )
    gSpriteEntry->W = 1;
  return result;
}


// 0x004b9d50: SpriteS1::sub_4B9D50
// IDA: SpriteS1::sub_4B9D50
// Ghidra: ---
void gta2::SpriteS1_sub_4B9D50(struct SpriteS1 *self, int a2, SpriteS1 *pSpriteS1, int a4, __int16 a5)
{
  struct Car *p_Car; // ecx
  struct EventHandler *GameObject; // ecx
  int v8; // [esp-8h] [ebp-10h]
  __int16 v9; // [esp-4h] [ebp-Ch]

  switch ( self->S3_arr5031[0].sprite_type )
  {
    case 1:
    case 4:
    case 5:
      GameObject = (struct EventHandler *)self->S3_arr5031[0].GameObject;
      if ( !GameObject->Car )
        gta2::S63_sub_484880(GameObject);
      v9 = a5;
      v8 = a4;
      p_Car = (struct Car *)self->S3_arr5031[0].GameObject->field_10;
      goto LABEL_7;
    case 2:
      v9 = a5;
      v8 = a4;
      p_Car = (struct Car *)self->S3_arr5031[0].GameObject;
      goto LABEL_7;
    case 3:
      v9 = a5;
      v8 = a4;
      p_Car = (struct Car *)&self->S3_arr5031[0].GameObject->Car;
LABEL_7:
      gta2::Car_sub_4BED90(p_Car, a2, (int)pSpriteS1, v8, v9);
      break;
    default:
      break;
  }
  switch ( *(_DWORD *)(a2 + 48) )
  {
    case 1:
    case 4:
    case 5:
      gta2::S63_sub_483E50(*(EventHandler **)(a2 + 8), self);
      break;
    case 2:
      gta2::Car_sub_422260(*(Car **)(a2 + 8));
      break;
    default:
      return;
  }
}


// 0x004b9f30: SpriteS1::sub_4B9F30
// IDA: SpriteS1::sub_4B9F30
// Ghidra: ---
_DWORD * gta2::SpriteS1_sub_4B9F30(SpriteS1 *a1)
{
  _DWORD *result; // eax

  result = &a1->FirstElement;
  dword_662BF0 = a1;
  return result;
}


// 0x004ba220: SpriteS1::sub_4BA220
// IDA: SpriteS1::sub_4BA220
// Ghidra: Sprite::FUN_004ba220
void gta2::SpriteS1_sub_4BA220(Sprite *self,undefined1 param_1)
{
  self->field_0x39 = param_1;
  return;
}


// 0x004ba230: SpriteS1::get_global_sprite_id
// IDA: SpriteS1::get_global_sprite_id
// Ghidra: ---
__int16 gta2::SpriteS1_get_global_sprite_id(struct SpriteS1 *self)
{
  return gta2::Style_GetGlobalSpriteId(gStyle, self->S3_arr5031[0].sprite_type, HIWORD(self->S3_arr5031[0].spriteId));
}


// 0x004baa70: SpriteS1::GetPed
// IDA: SpriteS1::GetPed
// Ghidra: SpriteS1::FUN_004baa70
Ped * gta2::SpriteS1_GetPed(struct SpriteS1 *self)
{
  struct Car *this_00;
  struct Ped *pPVar1;
  
  this_00 = (struct Car *)gta2::SpriteS1_GetGameObject(self);
  if (this_00 != NULL) {
    pPVar1 = gta2::GameObject_sub_433A20(this_00);
    return pPVar1;
  }
  return (struct Ped *)0;
}


// 0x004baa90: SpriteS1::sub_4BAA90
// IDA: SpriteS1::sub_4BAA90
// Ghidra: ---
bool gta2::SpriteS1_sub_4BAA90(struct SpriteS1 *self)
{
  int *p_PositionZ; // edi
  struct AudioManager *v3; // eax
  struct SpriteS1 *v4; // ecx
  int v5; // eax
  int v6; // eax
  int v8; // [esp-8h] [ebp-14h]
  int v9; // [esp-4h] [ebp-10h]
  _BYTE v10[4]; // [esp+8h] [ebp-4h] BYREF

  p_PositionZ = &self->S3_arr5031[0].PositionZ;
  v3 = gta2::Car_sub_403800((struct Car *)&self->S3_arr5031[0].PositionZ, (int)&unk_670010);
  v4 = (struct SpriteS1 *)p_PositionZ;
  if ( v3 )
    v4 = gta2::Player_sub_401B40((struct Player *)p_PositionZ, (struct S202 *)v10, (int)&unk_66FFAC);
  v9 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)v4);
  v8 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->S3_arr5031[0].PositionY);
  v5 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->S3_arr5031[0].PositionX);
  v6 = gta2::MapRelatedStruct_sub_4653C0(gMapRelatedStruct, v5, v8, v9);
  return v6 && gta2::Style_sub_49E540(gStyle, *(_WORD *)(v6 + 8) & 0x3FF);
}


// 0x004bab10: SpriteS1::sub_4BAB10
// IDA: SpriteS1::sub_4BAB10
// Ghidra: ---
int gta2::SpriteS1_sub_4BAB10(struct SpriteS1 *self, char a2)
{
  unsigned __int16 global_sprite_id; // ax
  int Sprite; // eax
  unsigned __int8 v5; // cl
  unsigned __int8 v6; // al
  int result; // eax
  unsigned __int8 v8; // dl

  global_sprite_id = gta2::SpriteS1_get_global_sprite_id(self);
  Sprite = gta2::Style_GetSprite(gStyle, global_sprite_id);
  v5 = *(_BYTE *)(Sprite + 5);
  v6 = *(_BYTE *)(Sprite + 4);
  if ( (unsigned __int8)(v6 & 0xFE) >= (unsigned __int8)(v5 & 0xFE) )
    result = v5 >> 1;
  else
    result = v6 >> 1;
  v8 = a2 + LOBYTE(self->S3_arr5031[0].field_34);
  LOBYTE(self->S3_arr5031[0].field_34) = v8;
  if ( v8 > result )
    LOBYTE(self->S3_arr5031[0].field_34) = result;
  return result;
}


// 0x004babb0: SpriteS1::sub_4BABB0
// IDA: SpriteS1::sub_4BABB0
// Ghidra: ---
bool gta2::SpriteS1_sub_4BABB0(struct SpriteS1 *self, int a2)
{
  return gta2::SpriteS1_is_object(self) && self->S3_arr5031[0].GameObject->field_18 == a2;
}


// 0x004babe0: SpriteS1::sub_4BABE0
// IDA: SpriteS1::sub_4BABE0
// Ghidra: ---
__int16 gta2::SpriteS1_sub_4BABE0(struct SpriteS1 *self)
{
  int v1; // eax
  __int16 global_sprite_id; // ax

  v1 = self->S3_arr5031[0].field_30;
  if ( v1 != 2 )
    return gta2::Style_get_global_palette_id(gStyle, v1, self->S3_arr5031[0].Remap);
  global_sprite_id = gta2::SpriteS1_get_global_sprite_id(self);
  return gta2::Style_get_global_palette_id(gStyle, 2, global_sprite_id);
}


// 0x004bac10: SpriteS1::sub_4BAC10
// IDA: SpriteS1::sub_4BAC10
// Ghidra: ---
char gta2::SpriteS1_sub_4BAC10(struct SpriteS1 *self)
{
  int v1; // eax
  struct GameObject *GameObject; // ecx
  char result; // al

  switch ( self->S3_arr5031[0].sprite_type )
  {
    case 1:
    case 4:
    case 5:
      result = *(_BYTE *)(self->S3_arr5031[0].GameObject->field_8 + 98);
      break;
    case 2:
      result = 1;
      break;
    case 3:
      GameObject = self->S3_arr5031[0].GameObject;
      result = 0;
      if ( GameObject->field_8 != 9 )
      {
        v1 = GameObject->field_C;
        if ( v1 != 22 && GameObject->field_10 != 15 && v1 != 27 && !gta2::Ped_sub_433DA0(GameObject->Ped_) )
          result = 1;
      }
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004bac60: SpriteS1::sub_4BAC60
// IDA: SpriteS1::sub_4BAC60
// Ghidra: FUN_004bac60
uint gta2::SpriteS1_sub_4BAC60(void)
{
  int iVar1;
  uint uVar2;
  
  iVar1 = FUN_004ba200();
  if (iVar1 == 0) {
    uVar2 = FUN_004b9ba0();
    return uVar2 | 0x80;
  }
  if (iVar1 != 1) {
    if (iVar1 != 2) {
      return 0;
    }
    iVar1 = FUN_004ba210();
    _DAT_0066fe28 = iVar1 << 0x1b | 0xffffff;
    _DAT_0066fe48 = _DAT_0066fe28;
    _DAT_0066fe68 = _DAT_0066fe28;
    _DAT_0066fe88 = _DAT_0066fe28;
    uVar2 = FUN_004b9ba0();
    return uVar2 | 0x2280;
  }
  iVar1 = FUN_004ba210();
  _DAT_0066fe28 = iVar1 << 0x1b | 0xffffff;
  _DAT_0066fe48 = _DAT_0066fe28;
  _DAT_0066fe68 = _DAT_0066fe28;
  _DAT_0066fe88 = _DAT_0066fe28;
  uVar2 = FUN_004b9ba0();
  return uVar2 | 0x2180;
}


// 0x004bb020: SpriteS1::sub_4BB020
// IDA: SpriteS1::sub_4BB020
// Ghidra: FUN_004bb020
uint gta2::SpriteS1_sub_4BB020(void *self,Point2D *param_2)
{
  Point2D *this_00;
  bool bVar1;
  void *pvVar2;
  undefined4 *puVar3;
  struct Player *pPVar4;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  uint uVar5;
  int *piVar6;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  undefined3 extraout_var_08;
  undefined3 extraout_var_09;
  undefined3 extraout_var_10;
  undefined3 extraout_var_11;
  undefined3 extraout_var_12;
  undefined3 extraout_var_13;
  undefined3 extraout_var_14;
  void *pvVar7;
  struct S127 *pSVar8;
  Point2D *this_01;
  struct SpriteS1 *pSVar9;
  struct SpriteS1 *pSVar10;
  struct SpriteS1 *pSVar11;
  undefined3 extraout_var_15;
  undefined3 extraout_var_16;
  undefined3 extraout_var_17;
  undefined3 extraout_var_18;
  struct S127 *pS127;
  int iVar12;
  int iVar13;
  int iVar14;
  int iVar15;
  undefined1 *puVar16;
  undefined1 *puVar17;
  int local_38;
  undefined1 local_34 [4];
  undefined1 local_30 [4];
  int local_2c;
  int local_28;
  Point2D local_24;
  undefined1 local_8 [4];
  undefined4 local_4;
  undefined3 extraout_var_02;
  
  FUN_004ba0a0(*(void **)((int)self + 0xc),&local_2c,&local_28);
  puVar17 = local_30;
  puVar16 = local_34;
  iVar15 = (int)self + 0x18;
  iVar13 = (int)self + 0x14;
  iVar12 = iVar13;
  iVar14 = iVar15;
  pvVar2 = gta2::sub_401C80((struct CarSystemManager *)self,&local_38);
  this_00 = param_2;
  pvVar7 = pvVar2;
  gta2::AudioSourceParams_sub_45ADD0(param_2,(Point2D *)&param_2);
  puVar3 = (undefined4 *)&local_24;
  gta2::AudioSourceParams_sub_45ADB0(this_00,puVar3);
  FUN_0042a720(puVar3,pvVar2,pvVar7,iVar12,iVar14,puVar16,puVar17);
  pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_2c,&param_2);
  bVar1 = gta2::Player_sub_40CE70((struct Player *)local_34,pPVar4);
  if (CONCAT31(extraout_var,bVar1) != 0) {
    bVar1 = gta2::Player_CheckCondition((struct Player *)local_34,&local_2c);
    if (CONCAT31(extraout_var_00,bVar1) != 0) {
      pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_28,&param_2);
      bVar1 = gta2::Player_sub_40CE70((struct Player *)local_30,pPVar4);
      if (CONCAT31(extraout_var_01,bVar1) != 0) {
        bVar1 = gta2::Player_CheckCondition((struct Player *)local_30,&local_28);
        uVar5 = CONCAT31(extraout_var_02,bVar1);
        if (uVar5 != 0) goto LAB_004bb39a;
      }
    }
  }
  puVar17 = local_30;
  puVar16 = local_34;
  iVar12 = iVar13;
  iVar14 = iVar15;
  pvVar2 = gta2::sub_401C80((struct CarSystemManager *)self,&param_2);
  pvVar7 = pvVar2;
  gta2::AudioSourceParams_sub_45ADD0(this_00,&local_24);
  piVar6 = &local_38;
  gta2::AudioSourceParams_sub_45ADA0(this_00,piVar6);
  FUN_0042a720(piVar6,pvVar2,pvVar7,iVar12,iVar14,puVar16,puVar17);
  pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_2c,&param_2);
  bVar1 = gta2::Player_sub_40CE70((struct Player *)local_34,pPVar4);
  if (CONCAT31(extraout_var_03,bVar1) != 0) {
    bVar1 = gta2::Player_CheckCondition((struct Player *)local_34,&local_2c);
    if (CONCAT31(extraout_var_04,bVar1) != 0) {
      pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_28,&param_2);
      bVar1 = gta2::Player_sub_40CE70((struct Player *)local_30,pPVar4);
      if (CONCAT31(extraout_var_05,bVar1) != 0) {
        bVar1 = gta2::Player_CheckCondition((struct Player *)local_30,&local_28);
        uVar5 = CONCAT31(extraout_var_06,bVar1);
        if (uVar5 != 0) goto LAB_004bb39a;
      }
    }
  }
  puVar17 = local_30;
  puVar16 = local_34;
  iVar12 = iVar13;
  iVar14 = iVar15;
  pvVar2 = gta2::sub_401C80((struct CarSystemManager *)self,&param_2);
  pvVar7 = pvVar2;
  gta2::S9_sub_45ADC0(this_00,(undefined4 *)&local_24);
  piVar6 = &local_38;
  gta2::AudioSourceParams_sub_45ADA0(this_00,piVar6);
  FUN_0042a720(piVar6,pvVar2,pvVar7,iVar12,iVar14,puVar16,puVar17);
  pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_2c,&param_2);
  bVar1 = gta2::Player_sub_40CE70((struct Player *)local_34,pPVar4);
  if (CONCAT31(extraout_var_07,bVar1) != 0) {
    bVar1 = gta2::Player_CheckCondition((struct Player *)local_34,&local_2c);
    if (CONCAT31(extraout_var_08,bVar1) != 0) {
      pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_28,&param_2);
      bVar1 = gta2::Player_sub_40CE70((struct Player *)local_30,pPVar4);
      if (CONCAT31(extraout_var_09,bVar1) != 0) {
        bVar1 = gta2::Player_CheckCondition((struct Player *)local_30,&local_28);
        uVar5 = CONCAT31(extraout_var_10,bVar1);
        if (uVar5 != 0) goto LAB_004bb39a;
      }
    }
  }
  puVar17 = local_30;
  puVar16 = local_34;
  iVar12 = iVar13;
  iVar14 = iVar15;
  pvVar2 = gta2::sub_401C80((struct CarSystemManager *)self,&param_2);
  pvVar7 = pvVar2;
  gta2::S9_sub_45ADC0(this_00,(undefined4 *)&local_24);
  piVar6 = &local_38;
  gta2::AudioSourceParams_sub_45ADB0(this_00,piVar6);
  FUN_0042a720(piVar6,pvVar2,pvVar7,iVar12,iVar14,puVar16,puVar17);
  pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_2c,&param_2);
  bVar1 = gta2::Player_sub_40CE70((struct Player *)local_34,pPVar4);
  if (CONCAT31(extraout_var_11,bVar1) != 0) {
    bVar1 = gta2::Player_CheckCondition((struct Player *)local_34,&local_2c);
    if (CONCAT31(extraout_var_12,bVar1) != 0) {
      pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_28,&param_2);
      bVar1 = gta2::Player_sub_40CE70((struct Player *)local_30,pPVar4);
      if (CONCAT31(extraout_var_13,bVar1) != 0) {
        bVar1 = gta2::Player_CheckCondition((struct Player *)local_30,&local_28);
        uVar5 = CONCAT31(extraout_var_14,bVar1);
        if (uVar5 != 0) goto LAB_004bb39a;
      }
    }
  }
  puVar17 = local_30;
  local_38 = 2;
  local_24.Array_24._0_4_ = (struct VehiclePool *)0x2;
  puVar16 = local_34;
  pvVar7 = gta2::sub_401C80((struct CarSystemManager *)self,&param_2);
  piVar6 = &local_38;
  pSVar8 = (struct S127 *)((int)&local_24 + 4);
  pSVar11 = (struct SpriteS1 *)pSVar8;
  gta2::S9_sub_45ADC0(this_00,(undefined4 *)((int)&local_24 + 8));
  pSVar9 = (struct SpriteS1 *)((int)&local_24 + 0xc);
  this_01 = (Point2D *)((int)&local_24 + 0x10);
  gta2::AudioSourceParams_sub_45ADD0(this_00,this_01);
  pSVar9 = gta2::S202_sub_401B20(this_01,pSVar9,pSVar8);
  pSVar10 = gta2::S122_sub_401BF0((struct Model *)pSVar9,pSVar11,piVar6);
  piVar6 = (int *)&local_24;
  pSVar9 = (struct SpriteS1 *)((int)&local_24 + 0x14);
  pSVar8 = (struct S127 *)((int)&local_24 + 0x18);
  gta2::AudioSourceParams_sub_45ADA0(this_00,(undefined4 *)pSVar8);
  pSVar11 = (struct SpriteS1 *)((int)&local_24 + 0x1c);
  pS127 = pSVar8;
  gta2::AudioSourceParams_sub_45ADB0(this_00,&local_4);
  pSVar11 = gta2::S202_sub_401B20((Point2D *)pSVar8,pSVar11,pS127);
  pSVar9 = gta2::S122_sub_401BF0((struct Model *)pSVar11,pSVar9,piVar6);
  FUN_0042a720(pSVar9,pSVar10,pvVar7,iVar13,iVar15,puVar16,puVar17);
  pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_2c,&param_2);
  bVar1 = gta2::Player_sub_40CE70((struct Player *)local_34,pPVar4);
  uVar5 = CONCAT31(extraout_var_15,bVar1);
  if (uVar5 != 0) {
    bVar1 = gta2::Player_CheckCondition((struct Player *)local_34,&local_2c);
    uVar5 = CONCAT31(extraout_var_16,bVar1);
    if (uVar5 != 0) {
      pPVar4 = (struct Player *)gta2::JustCopyByPtrAtoC(&local_28,&param_2);
      bVar1 = gta2::Player_sub_40CE70((struct Player *)local_30,pPVar4);
      uVar5 = CONCAT31(extraout_var_17,bVar1);
      if (uVar5 != 0) {
        bVar1 = gta2::Player_CheckCondition((struct Player *)local_30,&local_28);
        uVar5 = CONCAT31(extraout_var_18,bVar1);
        if (uVar5 != 0) {
LAB_004bb39a:
          return CONCAT31((int3)(uVar5 >> 8),1);
        }
      }
    }
  }
  return uVar5 & 0xffffff00;
}


// 0x004bbd40: SpriteS1::sub_4BBD40
// IDA: SpriteS1::sub_4BBD40
// Ghidra: ---
int gta2::SpriteS1_sub_4BBD40(struct SpriteS1 *self, int a2, int a2_4)
{
  int *v4; // eax
  int *v5; // eax
  int *v6; // eax
  struct SpriteS1 *v7; // eax
  struct SpriteS1 *v8; // eax
  struct SpriteS1 *v9; // eax
  struct SpriteS3 **v10; // eax
  int *v11; // eax
  int *v12; // eax
  _DWORD *v13; // eax
  int *v14; // ebx
  int *v15; // eax
  struct AudioSourceParams *p_sprite_type; // edi
  struct SpriteS1 *v17; // eax
  struct SpriteS1 *v18; // eax
  struct SpriteS1 *v19; // eax
  struct SpriteS3 **v20; // eax
  int *v21; // eax
  int *v22; // eax
  _DWORD *v23; // eax
  int *v24; // ebx
  int *v25; // eax
  struct SpriteS1 *v26; // eax
  struct SpriteS1 *v27; // eax
  struct SpriteS1 *v28; // eax
  struct SpriteS3 **v29; // eax
  int *v30; // eax
  int *v31; // eax
  _DWORD *v32; // eax
  int *v33; // ebx
  int *v34; // eax
  struct SpriteS1 *v35; // eax
  struct SpriteS1 *v36; // eax
  struct SpriteS1 *v37; // eax
  struct SpriteS3 **v38; // eax
  int *v39; // eax
  int *v40; // eax
  _DWORD *v41; // eax
  int *v42; // ebx
  int *v43; // eax
  struct SpriteS1 *v44; // eax
  struct SpriteS1 *v45; // eax
  struct SpriteS1 *v46; // eax
  struct SpriteS3 **v47; // eax
  int *v48; // eax
  int *v49; // eax
  _DWORD *v50; // eax
  int *v51; // eax
  _DWORD *v52; // eax
  int *v53; // eax
  int *v54; // eax
  int *v55; // ebx
  int *v56; // eax
  int result; // eax
  struct SpriteS1 *v58; // [esp-4h] [ebp-54h]
  struct SpriteS1 *v59; // [esp-4h] [ebp-54h]
  struct SpriteS1 *v60; // [esp-4h] [ebp-54h]
  struct SpriteS1 *v61; // [esp-4h] [ebp-54h]
  struct SpriteS1 *v62; // [esp-4h] [ebp-54h]
  int a3; // [esp+Ch] [ebp-44h] BYREF
  int Camer_Z_View; // [esp+10h] [ebp-40h] BYREF
  Weapon v65; // [esp+14h] [ebp-3Ch] BYREF
  _BYTE var8[12]; // [esp+48h] [ebp-8h] BYREF
  Player a2_8; // [esp+60h] [ebp+10h] BYREF

  v65.field_C = 2;
  gta2::S122_sub_401BF0((struct S122 *)self, (int)&v65.field_8, (int)&v65.field_C);
  Camer_Z_View = *v4;
  v65.field_C = 2;
  gta2::S122_sub_401BF0((struct S122 *)self->S3_arr5031, (int)&v65.field_8, (int)&v65.field_C);
  a3 = *v5;
  v65.field_C = 2;
  gta2::S122_sub_401BF0((struct S122 *)&self->S3_arr5031[0].GameObject, (int)&v65.field_8, (int)&v65.field_C);
  v65.field_C = *v6;
  gta2::Weapon_sub_432860((struct Weapon *)&v65.short, &a2, &a2_4);
  if ( gta2::sub_40E690(&a2_8.Player, unk_66FF7C) )
  {
    v58 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.field_8);
    v7 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.Ped, v7, v58);
    v8 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.field_8);
    gta2::Weapon_sub_432860(&v65, &Camer_Z_View, v8);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.field_2C, &Camer_Z_View, &a3);
    v9 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.field_8);
    gta2::Weapon_sub_432860((struct Weapon *)var8, v9, &a3);
    v10 = (SpriteS3 **)gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.TypeWeapon, &v65.Ped);
    self->S3_arr5031[0].SpriteS3 = *v10;
    self->S3_arr5031[0].NextElement = (struct CarTransforms *)v10[1];
    v11 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65);
    self->S3_arr5031[0].PositionX = *v11;
    self->S3_arr5031[0].PositionY = v11[1];
    v12 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65.field_2C);
    self->S3_arr5031[0].PositionZ = *v12;
    self->S3_arr5031[0].spriteId = v12[1];
    v13 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.field_2C, var8);
    *(_DWORD *)&self->S3_arr5031[0].Remap = *v13;
    self->S3_arr5031[0].field_24 = v13[1];
    v14 = (int *)gta2::S202_sub_401B20((struct S202 *)&a2_4, (struct SpriteS1 *)&v65.short, (struct PublicTransport *)&a3);
    v65.field_8 = (int)gta2::Player_sub_401B40((struct Player *)&a2_4, (struct S202 *)&v65.NextWeapon, (int)&a3);
    *(_DWORD *)&v65.Ammo = gta2::S202_sub_401B20((struct S202 *)&a2, (struct SpriteS1 *)&a3, (struct PublicTransport *)&Camer_Z_View);
    v15 = (int *)gta2::Player_sub_401B40((struct Player *)&a2, (struct S202 *)&v65.TypeWeapon, (int)&Camer_Z_View);
    p_sprite_type = (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type;
    gta2::AudioSourceParams_sub_41E350(
      (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type,
      *v15,
      **(_DWORD **)&v65.Ammo,
      *(_DWORD *)v65.field_8,
      *v14);
  }
  else if ( gta2::sub_40E690(&a2_8.Player, word_670254) )
  {
    v17 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.Ped, v17, &Camer_Z_View);
    v59 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.TypeWeapon);
    v18 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.NextWeapon);
    gta2::Weapon_sub_432860(&v65, v18, v59);
    v19 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.field_2C, &a3, v19);
    gta2::Weapon_sub_432860((struct Weapon *)var8, &a3, &Camer_Z_View);
    v20 = (SpriteS3 **)gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.TypeWeapon, &v65.Ped);
    self->S3_arr5031[0].SpriteS3 = *v20;
    self->S3_arr5031[0].NextElement = (struct CarTransforms *)v20[1];
    v21 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65);
    self->S3_arr5031[0].PositionX = *v21;
    self->S3_arr5031[0].PositionY = v21[1];
    v22 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65.field_2C);
    self->S3_arr5031[0].PositionZ = *v22;
    self->S3_arr5031[0].spriteId = v22[1];
    v23 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.field_2C, var8);
    *(_DWORD *)&self->S3_arr5031[0].Remap = *v23;
    self->S3_arr5031[0].field_24 = v23[1];
    v24 = (int *)gta2::S202_sub_401B20((struct S202 *)&a2_4, (struct SpriteS1 *)&v65.TypeWeapon, (struct PublicTransport *)&Camer_Z_View);
    v65.field_8 = (int)gta2::Player_sub_401B40((struct Player *)&a2_4, (struct S202 *)&v65.NextWeapon, (int)&Camer_Z_View);
    *(_DWORD *)&v65.Ammo = gta2::S202_sub_401B20((struct S202 *)&a2, (struct SpriteS1 *)&v65.short, (struct PublicTransport *)&a3);
    v25 = (int *)gta2::Player_sub_401B40((struct Player *)&a2, (struct S202 *)&Camer_Z_View, (int)&a3);
    p_sprite_type = (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type;
    gta2::AudioSourceParams_sub_41E350(
      (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type,
      *v25,
      **(_DWORD **)&v65.Ammo,
      *(_DWORD *)v65.field_8,
      *v24);
  }
  else if ( gta2::sub_40E690(&a2_8.Player, &unk_670130) )
  {
    gta2::Weapon_sub_432860((struct Weapon *)&v65.Ped, &Camer_Z_View, &a3);
    v26 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860(&v65, v26, &a3);
    v60 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.TypeWeapon);
    v27 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.NextWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.field_2C, v27, v60);
    v28 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)var8, &Camer_Z_View, v28);
    v29 = (SpriteS3 **)gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.TypeWeapon, &v65.Ped);
    self->S3_arr5031[0].SpriteS3 = *v29;
    self->S3_arr5031[0].NextElement = (struct CarTransforms *)v29[1];
    v30 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65);
    self->S3_arr5031[0].PositionX = *v30;
    self->S3_arr5031[0].PositionY = v30[1];
    v31 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65.field_2C);
    self->S3_arr5031[0].PositionZ = *v31;
    self->S3_arr5031[0].spriteId = v31[1];
    v32 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.field_2C, var8);
    *(_DWORD *)&self->S3_arr5031[0].Remap = *v32;
    self->S3_arr5031[0].field_24 = v32[1];
    v33 = (int *)gta2::S202_sub_401B20((struct S202 *)&a2_4, (struct SpriteS1 *)&v65.TypeWeapon, (struct PublicTransport *)&a3);
    v65.field_8 = (int)gta2::Player_sub_401B40((struct Player *)&a2_4, (struct S202 *)&v65.NextWeapon, (int)&a3);
    *(_DWORD *)&v65.Ammo = gta2::S202_sub_401B20((struct S202 *)&a2, (struct SpriteS1 *)&v65.short, (struct PublicTransport *)&Camer_Z_View);
    v34 = (int *)gta2::Player_sub_401B40((struct Player *)&a2, (struct S202 *)&a3, (int)&Camer_Z_View);
    p_sprite_type = (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type;
    gta2::AudioSourceParams_sub_41E350(
      (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type,
      *v34,
      **(_DWORD **)&v65.Ammo,
      *(_DWORD *)v65.field_8,
      *v33);
  }
  else if ( gta2::sub_40E690(&a2_8.Player, &unk_670050) )
  {
    v35 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.Ped, &a3, v35);
    gta2::Weapon_sub_432860(&v65, &a3, &Camer_Z_View);
    v36 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.field_2C, v36, &Camer_Z_View);
    v61 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.TypeWeapon);
    v37 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.NextWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)var8, v37, v61);
    v38 = (SpriteS3 **)gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.TypeWeapon, &v65.Ped);
    self->S3_arr5031[0].SpriteS3 = *v38;
    self->S3_arr5031[0].NextElement = (struct CarTransforms *)v38[1];
    v39 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65);
    self->S3_arr5031[0].PositionX = *v39;
    self->S3_arr5031[0].PositionY = v39[1];
    v40 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65.field_2C);
    self->S3_arr5031[0].PositionZ = *v40;
    self->S3_arr5031[0].spriteId = v40[1];
    v41 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.field_2C, var8);
    *(_DWORD *)&self->S3_arr5031[0].Remap = *v41;
    self->S3_arr5031[0].field_24 = v41[1];
    v42 = (int *)gta2::S202_sub_401B20((struct S202 *)&a2_4, (struct SpriteS1 *)&v65.TypeWeapon, (struct PublicTransport *)&Camer_Z_View);
    v65.field_8 = (int)gta2::Player_sub_401B40((struct Player *)&a2_4, (struct S202 *)&v65.NextWeapon, (int)&Camer_Z_View);
    *(_DWORD *)&v65.Ammo = gta2::S202_sub_401B20((struct S202 *)&a2, (struct SpriteS1 *)&v65.short, (struct PublicTransport *)&a3);
    v43 = (int *)gta2::Player_sub_401B40((struct Player *)&a2, (struct S202 *)&Camer_Z_View, (int)&a3);
    p_sprite_type = (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type;
    gta2::AudioSourceParams_sub_41E350(
      (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type,
      *v43,
      **(_DWORD **)&v65.Ammo,
      *(_DWORD *)v65.field_8,
      *v42);
  }
  else
  {
    v62 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.TypeWeapon);
    v44 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.NextWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.Ped, v44, v62);
    v45 = gta2::JustCopyByPtrAtoC(&a3, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860(&v65, &Camer_Z_View, v45);
    gta2::Weapon_sub_432860((struct Weapon *)&v65.field_2C, &Camer_Z_View, &a3);
    v46 = gta2::JustCopyByPtrAtoC(&Camer_Z_View, (struct SpriteS1 *)&v65.TypeWeapon);
    gta2::Weapon_sub_432860((struct Weapon *)var8, v46, &a3);
    gta2::Tango_sub_40F6B0((struct Tango *)&v65.Ped, (struct S900 *)&a2_8.Player);
    gta2::Tango_sub_40F6B0((struct Tango *)&v65, (struct S900 *)&a2_8.Player);
    gta2::Tango_sub_40F6B0((struct Tango *)&v65.field_2C, (struct S900 *)&a2_8.Player);
    gta2::Tango_sub_40F6B0((struct Tango *)var8, (struct S900 *)&a2_8.Player);
    v47 = (SpriteS3 **)gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.TypeWeapon, &v65.Ped);
    self->S3_arr5031[0].SpriteS3 = *v47;
    self->S3_arr5031[0].NextElement = (struct CarTransforms *)v47[1];
    v48 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65);
    self->S3_arr5031[0].PositionX = *v48;
    self->S3_arr5031[0].PositionY = v48[1];
    v49 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.Ped, &v65.field_2C);
    self->S3_arr5031[0].PositionZ = *v49;
    self->S3_arr5031[0].spriteId = v49[1];
    v50 = gta2::S103_sub_40F5C0((struct S103 *)&v65.short, &v65.field_2C, var8);
    p_sprite_type = (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type;
    *(_DWORD *)&self->S3_arr5031[0].Remap = *v50;
    self->S3_arr5031[0].field_24 = v50[1];
    gta2::AudioSourceParams_sub_45ADB0((struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type, (int *)&v65.TypeWeapon);
    v65.field_8 = *v51;
    gta2::AudioSourceParams_sub_45ADA0((struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type, &v65.TypeWeapon);
    *(_DWORD *)&v65.Ammo = *v52;
    gta2::AudioSourceParams_sub_45ADD0(
      (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type,
      (struct AudioSourceParams *)&v65.TypeWeapon);
    a3 = *v53;
    gta2::AudioSourceParams_sub_45ADC0((struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type, &v65.TypeWeapon);
    Camer_Z_View = *v54;
    gta2::sub_4B9E60(
      (struct SpriteS1 *)&v65.field_8,
      (SpriteS1 **)&v65,
      (SpriteS1 **)&self->S3_arr5031[0].SpriteS3,
      (SpriteS1 **)&self->S3_arr5031[0].PositionX,
      (SpriteS1 **)&self->S3_arr5031[0].PositionZ,
      (struct Car *)&self->S3_arr5031[0].Remap);
    gta2::sub_4B9E60(
      (struct SpriteS1 *)&a3,
      (SpriteS1 **)&Camer_Z_View,
      (SpriteS1 **)&self->S3_arr5031[0].NextElement,
      (SpriteS1 **)&self->S3_arr5031[0].PositionY,
      (SpriteS1 **)&self->S3_arr5031[0].spriteId,
      (struct Car *)&self->S3_arr5031[0].field_24);
    gta2::AudioSourceParams_sub_41E350(
      (struct AudioSourceParams *)&self->S3_arr5031[0].sprite_type,
      v65.field_8,
      *(int *)&v65.Ammo,
      a3,
      Camer_Z_View);
  }
  v55 = (int *)gta2::S202_sub_401B20((struct S202 *)&a2_8, (struct SpriteS1 *)&v65.TypeWeapon, (struct PublicTransport *)&v65.field_C);
  v56 = (int *)gta2::Player_sub_401B40(&a2_8, (struct S202 *)&v65.NextWeapon, (int)&v65.field_C);
  gta2::AudioSourceParams_sub_41E370(p_sprite_type, *v56, *v55);
  LOBYTE(self->S3_arr5031[1].SpriteS3) = 1;
  return result;
}


// 0x004bc970: SpriteS1::sub_4BC970
// IDA: SpriteS1::sub_4BC970
// Ghidra: ---
int gta2::SpriteS1_sub_4BC970(struct SpriteS1 *self)
{
  self->FirstElement = 0;
  return gta2::Construct_0(self->S3_arr5031, 60, 5031, S3::S3_Des);
}


// 0x004bca20: SpriteS1::SpriteS1
// IDA: SpriteS1::SpriteS1
// Ghidra: ---
SpriteS1 * gta2::SpriteS1_SpriteS1(struct SpriteS1 *self)
{
  struct CarTransforms *S3_arr5031; // esi
  struct CarTransforms *pS3; // eax
  int Count; // ecx

  S3_arr5031 = self->S3_arr5031;
  gta2::Construct(self->S3_arr5031, 60, 5031, CarTransforms::CarTransforms, S3::S3_Des);
  pS3 = (struct CarTransforms *)&S3_arr5031->NextElement;
  Count = 5030;
  do
  {
    pS3->SpriteS1_ = (struct SpriteS1 *)&pS3->field_30;
    ++pS3;
    --Count;
  }
  while ( Count );
  self->S3_arr5031[5030].NextElement = 0;
  self->FirstElement = (struct SpriteS1 *)S3_arr5031;
  return self;
}


// 0x004bca80: SpriteS1::FUN_004bca80
// IDA: sub_4BCA80
// Ghidra: SpriteS1::FUN_004bca80
byte gta2::SpriteS1_FUN_004bca80(struct SpriteS1 *self)
{
  byte bVar1;
  struct Ped *pPVar2;
  struct Car *this_00;
  
  pPVar2 = (struct Ped *)gta2::SpriteS1_GetPed(self);
  if (pPVar2 == NULL) {
    this_00 = (struct Car *)gta2::SpriteS1_GetCar(self);
    if (this_00 == NULL) {
      return 0;
    }
    pPVar2 = gta2::Car_GetDriver(this_00);
    if (pPVar2 == NULL) {
      return 0;
    }
  }
  if ((pPVar2->isPlayer != NULL) &&
     (bVar1 = gta2::Player_GetCurrentPlayer(pPVar2->isPlayer), bVar1 == 0)) {
    return 1;
  }
  return 0;
}


// 0x004bcb40: SpriteS1::sub_4BCB40
// IDA: SpriteS1::sub_4BCB40
// Ghidra: ---
char gta2::SpriteS1_sub_4BCB40(_DWORD *self)
{
  int v2; // edi
  char result; // al

  v2 = self[3];
  result = *(_BYTE *)(v2 + 72);
  if ( !result )
  {
    gta2::Player_IsActionAllowed((struct Player *)self[3]);
    return gta2::SpriteS1_sub_4BBD40((struct SpriteS1 *)v2, self[5], self[6]);
  }
  return result;
}


// 0x004bcb90: SpriteS1::sub_4BCB90
// IDA: SpriteS1::sub_4BCB90
// Ghidra: ---
int gta2::SpriteS1_sub_4BCB90(struct SpriteS1 *self, SpriteS1 *a2, SpriteS3 *pSpriteS3, EventHandler *a4)
{
  if ( !self->S3_arr5031[0].SpriteS3 )
    self->S3_arr5031[0].SpriteS3 = gta2::SpriteS2_sub_4BC9F0(gSpriteS2);
  return (int)gta2::SpriteS3_sub_482980(self->S3_arr5031[0].SpriteS3, a2, pSpriteS3, a4);
}


// 0x004bcbd0: SpriteS1::sub_4BCBD0
// IDA: SpriteS1::sub_4BCBD0
// Ghidra: ---
_DWORD * gta2::SpriteS1_sub_4BCBD0(struct SpriteS1 *self)
{
  _DWORD *result; // eax
  struct SpriteS1 *SpriteS1; // eax
  int sprite_type; // ecx
  unsigned __int16 GlobalSpriteId; // ax
  int Sprite; // esi
  struct S122 *v7; // ecx
  int *v8; // eax
  int v9; // ebx
  struct S122 *v10; // ecx
  int *v11; // eax
  int WindowWidth; // [esp+4h] [ebp-8h] BYREF
  int WindowHeight; // [esp+8h] [ebp-4h] BYREF

  result = &self->S3_arr5031[0].SpriteS1_->FirstElement;
  if ( !result )
  {
    SpriteS1 = (struct SpriteS1 *)gta2::SpriteS2_sub_4BC9F0(gSpriteS2);
    sprite_type = self->S3_arr5031[0].sprite_type;
    self->S3_arr5031[0].SpriteS1_ = SpriteS1;
    GlobalSpriteId = gta2::Style_GetGlobalSpriteId(gStyle, sprite_type, HIWORD(self->S3_arr5031[0].spriteId));
    Sprite = gta2::Style_GetSprite(gStyle, GlobalSpriteId);
    if ( self->S3_arr5031[0].sprite_type == 8 )
    {
      v7 = (struct S122 *)(4 * *(unsigned __int8 *)(Sprite + 4) + 6699424);
      WindowWidth = 2;
      gta2::S122_sub_401BF0(v7, (int)&WindowHeight, (int)&WindowWidth);
      v9 = *v8;
      v10 = (struct S122 *)(4 * *(unsigned __int8 *)(Sprite + 5) + 6699424);
      WindowWidth = 2;
      gta2::S122_sub_401BF0(v10, (int)&WindowHeight, (int)&WindowWidth);
      return gta2::sub_4BA070((int *)self->S3_arr5031[0].SpriteS1_, v9, *v11);
    }
    else
    {
      return gta2::sub_4BA070(
               (int *)self->S3_arr5031[0].SpriteS1_,
               *(&gSpriteS3_0.S39_Arr48[0].field_0 + *(unsigned __int8 *)(Sprite + 4)),
               *(&gSpriteS3_0.S39_Arr48[0].field_0 + *(unsigned __int8 *)(Sprite + 5)));
    }
  }
  return result;
}


// 0x004bcd00: SpriteS1::sub_4BCD00
// IDA: SpriteS1::sub_4BCD00
// Ghidra: FUN_004bcd00
undefined4 gta2::SpriteS1_sub_4BCD00(Sprite *param_1,undefined4 param_2,SpriteS1 *param_3, SpriteS1 *param_4)
{
  struct SpriteS1 *self;
  struct SpriteS1 *pSVar1;
  bool bVar2;
  undefined4 *puVar3;
  int *piVar4;
  struct Car *pCVar5;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  struct SpriteS1 *pSVar6;
  undefined4 *puVar7;
  struct Player *this_00;
  undefined1 *puVar8;
  struct Car *pCVar9;
  struct SpriteS1 *local_c;
  struct SpriteS1 *local_8;
  struct SpriteS1 *local_4;
  
  gta2::SpriteS1_sub_4BCB40(param_1);
  puVar7 = param_1->field3_0xc;
  puVar3 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(puVar7 + 4),(GlassInfo *)&local_4,
                      (struct S127 *)&param_2);
  local_c = (struct SpriteS1 *)*puVar3;
  puVar3 = (undefined4 *)FUN_004b9c20(&local_4,&local_c);
  local_4 = (struct SpriteS1 *)*puVar3;
  piVar4 = gta2::Player_FUN_00403840((struct Player *)&local_8,(int *)&local_8,(GlassInfo *)&local_c);
  pSVar1 = param_4;
  self = param_3;
  local_8 = (struct SpriteS1 *)*piVar4;
  param_3->FirstElement = (struct SpriteS1 *)puVar7[3];
  param_3->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar7[4];
  ((GameState *)&param_4->FirstElement)->X = 0;
  puVar3 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(puVar7 + 6),(GlassInfo *)&param_3,
                      (struct S127 *)&param_2);
  local_c = (struct SpriteS1 *)*puVar3;
  pCVar9 = (struct Car *)&local_4;
  pCVar5 = (struct Car *)FUN_004b9c20(&param_3,&local_c);
  bVar2 = gta2::Car_IsTrainOrTrainCarriage(pCVar5,pCVar9);
  if (CONCAT31(extraout_var,bVar2) != 0) {
    return 0;
  }
  piVar4 = gta2::Player_FUN_00403840(this_00,(int *)&param_3,(GlassInfo *)&local_c);
  pSVar6 = (struct SpriteS1 *)*piVar4;
  local_c = pSVar6;
  bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_8);
  if (CONCAT31(extraout_var_00,bVar2) == 0) {
    bVar2 = gta2::Player_IsCurrentPlayer((struct Player *)&local_c,(struct Player *)&local_8);
    if (CONCAT31(extraout_var_01,bVar2) != 0) {
      puVar3 = &param_3;
      piVar4 = (int *)&DAT_00670094;
      pSVar6 = gta2::S202_sub_401B20((Point2D *)self,(struct SpriteS1 *)&param_4,
                          (struct S127 *)(puVar7 + 5));
      puVar3 = (undefined4 *)
               gta2::sub_401B90((struct Player *)pSVar6,puVar3,piVar4);
      self->FirstElement = (struct SpriteS1 *)*puVar3;
      ((GameState *)&pSVar1->FirstElement)->X = 5;
    }
  }
  else {
    self->FirstElement = (struct SpriteS1 *)puVar7[5];
    self->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar7[6];
    ((GameState *)&pSVar1->FirstElement)->X = 1;
    local_8 = pSVar6;
  }
  puVar3 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(puVar7 + 8),(GlassInfo *)&param_3,
                      (struct S127 *)&param_2);
  local_c = (struct SpriteS1 *)*puVar3;
  pCVar9 = (struct Car *)&local_4;
  pCVar5 = (struct Car *)FUN_004b9c20(&param_3,&local_c);
  bVar2 = gta2::Car_IsTrainOrTrainCarriage(pCVar5,pCVar9);
  if (CONCAT31(extraout_var_02,bVar2) == 0) {
    piVar4 = gta2::Player_FUN_00403840((struct Player *)&param_3,(int *)&param_3,(GlassInfo *)&local_c
                       );
    pSVar6 = (struct SpriteS1 *)*piVar4;
    local_c = pSVar6;
    bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_8);
    if (CONCAT31(extraout_var_03,bVar2) == 0) {
      bVar2 = gta2::Player_IsCurrentPlayer((struct Player *)&local_c,(struct Player *)&local_8);
      if (CONCAT31(extraout_var_04,bVar2) != 0) {
        puVar3 = &param_3;
        piVar4 = (int *)&DAT_00670094;
        pSVar6 = gta2::S202_sub_401B20((Point2D *)self,(struct SpriteS1 *)&param_4,
                            (struct S127 *)(puVar7 + 7));
        puVar3 = (undefined4 *)
                 gta2::sub_401B90((struct Player *)pSVar6,puVar3,piVar4);
        self->FirstElement = (struct SpriteS1 *)*puVar3;
        ((GameState *)&pSVar1->FirstElement)->X = 5;
      }
    }
    else {
      self->FirstElement = (struct SpriteS1 *)puVar7[7];
      self->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar7[8];
      ((GameState *)&pSVar1->FirstElement)->X = 2;
      local_8 = pSVar6;
    }
    puVar3 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)(puVar7 + 10),(GlassInfo *)&param_3,
                        (struct S127 *)&param_2);
    local_c = (struct SpriteS1 *)*puVar3;
    pCVar9 = (struct Car *)&local_4;
    pCVar5 = (struct Car *)FUN_004b9c20(&param_2,&local_c);
    bVar2 = gta2::Car_IsTrainOrTrainCarriage(pCVar5,pCVar9);
    if (CONCAT31(extraout_var_05,bVar2) == 0) {
      piVar4 = gta2::Player_FUN_00403840((struct Player *)&local_c,&param_2,(GlassInfo *)&local_c);
      local_c = (struct SpriteS1 *)*piVar4;
      bVar2 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_8);
      if (CONCAT31(extraout_var_06,bVar2) != 0) {
        self->FirstElement = (struct SpriteS1 *)puVar7[9];
        self->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar7[10];
        ((GameState *)&pSVar1->FirstElement)->X = 3;
        return 1;
      }
      bVar2 = gta2::Player_IsCurrentPlayer((struct Player *)&local_c,(struct Player *)&local_8);
      if (CONCAT31(extraout_var_07,bVar2) != 0) {
        puVar8 = (undefined1 *)&param_2;
        piVar4 = (int *)&DAT_00670094;
        pSVar6 = gta2::S202_sub_401B20((Point2D *)self,(struct SpriteS1 *)&param_3,
                            (struct S127 *)(puVar7 + 9));
        puVar7 = (undefined4 *)
                 gta2::sub_401B90((struct Player *)pSVar6,puVar8,piVar4);
        self->FirstElement = (struct SpriteS1 *)*puVar7;
        ((GameState *)&pSVar1->FirstElement)->X = 5;
      }
      return 1;
    }
  }
  return 0;
}


// 0x004bcfa0: SpriteS1::sub_4BCFA0
// IDA: SpriteS1::sub_4BCFA0
// Ghidra: FUN_004bcfa0
undefined4 gta2::SpriteS1_sub_4BCFA0(Sprite *param_1,undefined4 param_2,SpriteS1 *param_3, SpriteS1 *param_4)
{
  struct SpriteS1 *pSVar1;
  struct SpriteS1 *pSVar2;
  bool bVar3;
  undefined4 *puVar4;
  int *piVar5;
  struct Car *pCVar6;
  undefined3 extraout_var;
  undefined3 extraout_var_00;
  undefined3 extraout_var_01;
  undefined3 extraout_var_02;
  undefined3 extraout_var_03;
  undefined3 extraout_var_04;
  undefined3 extraout_var_05;
  undefined3 extraout_var_06;
  undefined3 extraout_var_07;
  struct SpriteS1 *pSVar7;
  undefined4 *puVar8;
  struct Player *self;
  struct Player *this_00;
  struct Player *this_01;
  undefined1 *puVar9;
  struct Car *pCVar10;
  struct SpriteS1 *local_c;
  struct SpriteS1 *local_8;
  struct SpriteS1 *local_4;
  
  puVar8 = param_1->field3_0xc;
  gta2::SpriteS1_sub_4BCB40(param_1);
  puVar4 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(puVar8 + 3),(GlassInfo *)&local_4,
                      (struct S127 *)&param_2);
  local_c = (struct SpriteS1 *)*puVar4;
  puVar4 = (undefined4 *)FUN_004b9c20(&local_4,&local_c);
  local_4 = (struct SpriteS1 *)*puVar4;
  piVar5 = gta2::Player_FUN_00403840((struct Player *)&local_8,(int *)&local_8,(GlassInfo *)&local_c);
  pSVar2 = param_4;
  pSVar1 = param_3;
  local_8 = (struct SpriteS1 *)*piVar5;
  param_3->FirstElement = *(SpriteS1 **)(puVar8 + 3);
  param_3->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar8[4];
  ((GameState *)&param_4->FirstElement)->X = 0;
  puVar4 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)(puVar8 + 5),(GlassInfo *)&param_3,
                      (struct S127 *)&param_2);
  local_c = (struct SpriteS1 *)*puVar4;
  pCVar10 = (struct Car *)&local_4;
  pCVar6 = (struct Car *)FUN_004b9c20(&param_3,&local_c);
  bVar3 = gta2::Car_IsTrainOrTrainCarriage(pCVar6,pCVar10);
  if (CONCAT31(extraout_var,bVar3) == 0) {
    piVar5 = gta2::Player_FUN_00403840(self,(int *)&param_3,(GlassInfo *)&local_c);
    local_c = (struct SpriteS1 *)*piVar5;
    bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_8);
    if (CONCAT31(extraout_var_00,bVar3) == 0) {
      bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)&local_c,(struct Player *)&local_8);
      if (CONCAT31(extraout_var_01,bVar3) != 0) {
        puVar4 = &param_3;
        piVar5 = (int *)&DAT_00670094;
        pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar1->Matrix3DArray,
                            (struct SpriteS1 *)&param_4,(struct S127 *)(puVar8 + 6));
        puVar4 = (undefined4 *)
                 gta2::sub_401B90((struct Player *)pSVar7,puVar4,piVar5);
        pSVar1->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)*puVar4;
        ((GameState *)&pSVar2->FirstElement)->X = 5;
      }
    }
    else {
      pSVar1->FirstElement = *(SpriteS1 **)(puVar8 + 5);
      pSVar1->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar8[6];
      local_8 = local_c;
      ((GameState *)&pSVar2->FirstElement)->X = 1;
    }
    puVar4 = (undefined4 *)
             gta2::Player_sub_401B40((SpawnPoint *)(puVar8 + 7),(GlassInfo *)&param_3,
                        (struct S127 *)&param_2);
    local_c = (struct SpriteS1 *)*puVar4;
    pCVar10 = (struct Car *)&local_4;
    pCVar6 = (struct Car *)FUN_004b9c20(&param_3,&local_c);
    bVar3 = gta2::Car_IsTrainOrTrainCarriage(pCVar6,pCVar10);
    if (CONCAT31(extraout_var_02,bVar3) == 0) {
      piVar5 = gta2::Player_FUN_00403840(this_00,(int *)&param_3,(GlassInfo *)&local_c);
      local_c = (struct SpriteS1 *)*piVar5;
      bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_8);
      if (CONCAT31(extraout_var_03,bVar3) == 0) {
        bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)&local_c,(struct Player *)&local_8);
        if (CONCAT31(extraout_var_04,bVar3) != 0) {
          puVar4 = &param_3;
          piVar5 = (int *)&DAT_00670094;
          pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar1->Matrix3DArray,
                              (struct SpriteS1 *)&param_4,(struct S127 *)(puVar8 + 8));
          puVar4 = (undefined4 *)
                   gta2::sub_401B90((struct Player *)pSVar7,puVar4,piVar5);
          pSVar1->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)*puVar4;
          ((GameState *)&pSVar2->FirstElement)->X = 5;
        }
      }
      else {
        pSVar1->FirstElement = *(SpriteS1 **)(puVar8 + 7);
        pSVar1->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar8[8];
        local_8 = local_c;
        ((GameState *)&pSVar2->FirstElement)->X = 2;
      }
      puVar4 = (undefined4 *)
               gta2::Player_sub_401B40((SpawnPoint *)(puVar8 + 9),(GlassInfo *)&param_3,
                          (struct S127 *)&param_2);
      local_c = (struct SpriteS1 *)*puVar4;
      pCVar10 = (struct Car *)&local_4;
      pCVar6 = (struct Car *)FUN_004b9c20(&param_2,&local_c);
      bVar3 = gta2::Car_IsTrainOrTrainCarriage(pCVar6,pCVar10);
      if (CONCAT31(extraout_var_05,bVar3) == 0) {
        piVar5 = gta2::Player_FUN_00403840(this_01,&param_2,(GlassInfo *)&local_c);
        local_c = (struct SpriteS1 *)*piVar5;
        bVar3 = gta2::Point2D_FUN_004037e0((Point2D *)&local_c,(struct SpriteS1 *)&local_8);
        if (CONCAT31(extraout_var_06,bVar3) != 0) {
          pSVar1->FirstElement = *(SpriteS1 **)(puVar8 + 9);
          pSVar1->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)puVar8[10];
          ((GameState *)&pSVar2->FirstElement)->X = 3;
          return 1;
        }
        bVar3 = gta2::Player_IsCurrentPlayer((struct Player *)&local_c,(struct Player *)&local_8);
        if (CONCAT31(extraout_var_07,bVar3) != 0) {
          puVar9 = (undefined1 *)&param_2;
          piVar5 = (int *)&DAT_00670094;
          pSVar7 = gta2::S202_sub_401B20((Point2D *)pSVar1->Matrix3DArray,
                              (struct SpriteS1 *)&param_3,(struct S127 *)(puVar8 + 10));
          puVar8 = (undefined4 *)
                   gta2::sub_401B90((struct Player *)pSVar7,puVar9,piVar5);
          pSVar1->Matrix3DArray[0].SpriteS1 = (struct SpriteS1 *)*puVar8;
          ((GameState *)&pSVar2->FirstElement)->X = 5;
        }
        return 1;
      }
    }
  }
  return 0;
}


// 0x004bd290: SpriteS1::sub_4BD290
// IDA: SpriteS1::sub_4BD290
// Ghidra: ---
char gta2::SpriteS1_sub_4BD290(struct SpriteS1 *self)
{
  struct SpriteS1 *SpriteS1; // ecx

  gta2::SpriteS1_sub_4BCBD0(self);
  SpriteS1 = self->S3_arr5031[0].SpriteS1_;
  if ( !LOBYTE(SpriteS1->S3_arr5031[1].SpriteS3) )
    gta2::SpriteS1_sub_4BBD40(SpriteS1, self->S3_arr5031[0].PositionX, self->S3_arr5031[0].PositionY);
  gta2::SpriteS3_sub_4BC580((struct SpriteS3 *)self->S3_arr5031[0].SpriteS1_);
  sub_4B9F80();
  return gta2::MapRelatedStruct_sub_466620(gMapRelatedStruct, (void *)self->S3_arr5031[0].PositionZ);
}


// 0x004bd2e0: SpriteS1::sub_4BD2E0
// IDA: SpriteS1::sub_4BD2E0
// Ghidra: Sprite::FUN_004bd2e0
undefined1 gta2::SpriteS1_sub_4BD2E0(Sprite *self)
{
  bool bVar1;
  char cVar2;
  void *pvVar3;
  int iVar4;
  struct Car *local_4;
  
  if (self->field_0x39 == -1) {
    local_4 = (struct Car *)self;
    if (self->field27_0x30 == 2) {
      bVar1 = gta2::Car_IsTrainOrTrainCarriage((struct Car *)self->s61);
      if (bVar1) {
        pvVar3 = gta2::Player_sub_401B40((SpawnPoint *)&self->Point2D,(GlassInfo *)&local_4,
                            (struct S127 *)&DAT_0066ffac);
        iVar4 = FUN_00491ee0(pvVar3);
        self->field_0x39 = (char)iVar4;
        return (char)iVar4;
      }
    }
    pvVar3 = gta2::Player_sub_401B40((SpawnPoint *)&self->Point2D,(GlassInfo *)&local_4,
                        (struct S127 *)&DAT_0066ffac);
    iVar4 = FUN_00491ee0(pvVar3);
    cVar2 = (char)iVar4;
    gta2::SpriteS1_sub_4BD290(self);
    self->field_0x39 = (char)iVar4 + cVar2;
  }
  return self->field_0x39;
}


// 0x004bd350: SpriteS1::sub_4BD350
// IDA: SpriteS1::sub_4BD350
// Ghidra: FUN_004bd350
byte gta2::SpriteS1_sub_4BD350(Sprite *param_1,int *param_2)
{
  undefined4 *puVar1;
  undefined4 uVar2;
  bool bVar3;
  char cVar4;
  struct Model *self;
  struct SpriteS1 *pSVar5;
  undefined4 *puVar6;
  undefined3 extraout_var;
  struct SpriteS1 **ppSVar7;
  bool local_d;
  SpriteS1 *local_c [2];
  undefined1 local_4 [4];
  
  gta2::SpriteS1_sub_4BCB40(param_1);
  puVar1 = param_1->field3_0xc;
  ppSVar7 = local_c;
  pSVar5 = (struct SpriteS1 *)(local_c + 1);
  local_c[0] = (struct SpriteS1 *)0x2;
  self = (struct Model *)FUN_00492170(local_4);
  pSVar5 = gta2::S122_sub_401BF0(self,pSVar5,(int *)ppSVar7);
  local_c[0] = pSVar5->FirstElement;
  puVar6 = (undefined4 *)
           gta2::Player_sub_401B40((SpawnPoint *)&param_1->Point2D,(GlassInfo *)local_4,
                      (struct S127 *)local_c);
  uVar2 = *puVar6;
  pSVar5 = gta2::S202_sub_401B20((Point2D *)&param_1->Point2D,(struct SpriteS1 *)local_4,
                      (struct S127 *)local_c);
  pSVar5 = pSVar5->FirstElement;
  local_c[0] = pSVar5;
  bVar3 = gta2::Car_sub_403800((struct Car *)local_c,(int *)&DAT_0067003c);
  if (CONCAT31(extraout_var,bVar3) != 0) {
    pSVar5 = _DAT_0067003c;
  }
  cVar4 = FUN_00469c20(puVar1[3],puVar1[4],uVar2,pSVar5);
  if (cVar4 == '\0') {
    *param_2 = 0;
  }
  else {
    *param_2 = 1;
  }
  local_d = cVar4 != '\0';
  cVar4 = FUN_00469c20(puVar1[5],puVar1[6],uVar2,pSVar5);
  if (cVar4 != '\0') {
    local_d = (bool)(local_d | 2);
    *param_2 = *param_2 + 1;
  }
  cVar4 = FUN_00469c20(puVar1[7],puVar1[8],uVar2,pSVar5);
  if (cVar4 != '\0') {
    local_d = (bool)(local_d | 4);
    *param_2 = *param_2 + 1;
  }
  cVar4 = FUN_00469c20(puVar1[9],puVar1[10],uVar2,pSVar5);
  if (cVar4 != '\0') {
    local_d = (bool)(local_d | 8);
    *param_2 = *param_2 + 1;
  }
  return local_d;
}


// 0x004bd670: SpriteS1::sub_4BD670
// IDA: SpriteS1::sub_4BD670
// Ghidra: ---
char gta2::SpriteS1_sub_4BD670(struct SpriteS1 *self)
{
  struct AudioSourceParams *p_PositionZ; // ebp
  int *p_PositionX; // edi
  int *p_PositionY; // esi
  struct SpriteS1 *v5; // eax
  int *v6; // edi
  int *v7; // eax
  int *v9; // esi
  struct SpriteS1 *v10; // eax
  int *v11; // edi
  int *v12; // eax
  struct SpriteS1 *v13; // eax
  int *v14; // esi
  int *v15; // eax
  struct SpriteS1 *v16; // eax
  struct SpriteS1 *v17; // eax
  int *v18; // esi
  int *v19; // eax
  struct GameObject *v20; // eax
  __int16 v21; // ax
  struct CarSystemManager *v22; // eax
  char v23; // bl
  struct CarSystemManager *v24; // [esp-10h] [ebp-2Ch]
  int v25; // [esp-Ch] [ebp-28h]
  int *v26; // [esp-4h] [ebp-20h]
  __int16 v27; // [esp-4h] [ebp-20h]
  char v28; // [esp+10h] [ebp-Ch] BYREF
  char v29; // [esp+14h] [ebp-8h] BYREF
  char v30; // [esp+18h] [ebp-4h] BYREF

  p_PositionZ = (struct AudioSourceParams *)&self->S3_arr5031[0].PositionZ;
  if ( gta2::Player_sub_40CE70((struct Player *)&self->S3_arr5031[0].PositionZ, &unk_66FF68) )
  {
    p_PositionX = &self->S3_arr5031[0].PositionX;
    if ( gta2::sub_4037E0(&self->S3_arr5031[0].PositionX) )
    {
      p_PositionY = &self->S3_arr5031[0].PositionY;
      v5 = gta2::sub_462EA0((struct SpriteS1 *)&v29, p_PositionY);
      v6 = (int *)gta2::S202_sub_401B20((struct S202 *)v5, (struct SpriteS1 *)&v28, &unk_66FFAC);
      v7 = (int *)gta2::sub_462EA0((struct SpriteS1 *)&v30, p_PositionY);
      gta2::sub_4BA280(&dword_5E6874, *v7, *v6, unk_66FFAC.BaseCar[0].field);
      gta2::sub_4BA2B0(&dword_5E6874, p_PositionZ->field);
      return 1;
    }
    if ( gta2::Car_sub_403800((struct Car *)&self->S3_arr5031[0].PositionX, (int)&unk_670224) )
    {
      v9 = &self->S3_arr5031[0].PositionY;
      v10 = gta2::sub_462EA0((struct SpriteS1 *)&v29, v9);
      v11 = (int *)gta2::S202_sub_401B20((struct S202 *)v10, (struct SpriteS1 *)&v30, &unk_66FFAC);
      v12 = (int *)gta2::sub_462EA0((struct SpriteS1 *)&v28, v9);
      gta2::sub_4BA280(&dword_5E6874, *v12, *v11, unk_670224);
LABEL_10:
      gta2::sub_4BA2B0(&dword_5E6874, p_PositionZ->field);
      return 1;
    }
    if ( gta2::sub_4037E0(&self->S3_arr5031[0].PositionY) )
    {
      v13 = gta2::sub_462EA0((struct SpriteS1 *)&v29, &self->S3_arr5031[0].PositionX);
      v14 = (int *)gta2::S202_sub_401B20((struct S202 *)v13, (struct SpriteS1 *)&v30, &unk_66FFAC);
      v15 = (int *)gta2::sub_462EA0((struct SpriteS1 *)&v28, p_PositionX);
      gta2::sub_4BA250(&dword_5E6874, *v15, *v14, unk_66FFAC.BaseCar[0].field);
      gta2::sub_4BA2B0(&dword_5E6874, p_PositionZ->field);
      return 1;
    }
    if ( gta2::Car_sub_403800((struct Car *)&self->S3_arr5031[0].PositionY, (int)&unk_670224) )
    {
      v16 = gta2::sub_462EA0((struct SpriteS1 *)&v29, &self->S3_arr5031[0].PositionX);
      v17 = gta2::S202_sub_401B20((struct S202 *)v16, (struct SpriteS1 *)&v30, &unk_66FFAC);
      v26 = &self->S3_arr5031[0].PositionX;
      v18 = (int *)v17;
      v19 = (int *)gta2::sub_462EA0((struct SpriteS1 *)&v28, v26);
      gta2::sub_4BA250(&dword_5E6874, *v19, *v18, unk_670224);
      goto LABEL_10;
    }
  }
  gta2::SpriteS1_sub_4BCB40(self);
  gta2::SpriteS3_sub_4BC580(self->S3_arr5031[0].SpriteS3);
  v20 = gta2::SpriteS1_sub_40FEC0(self);
  if ( v20 )
    v21 = gta2::sub_4824C0(v20);
  else
    v21 = 1024;
  v27 = v21;
  v25 = gta2::AudioSourceParams_sub_41F9D0(p_PositionZ);
  v24 = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->S3_arr5031[0].PositionY);
  v22 = (struct CarSystemManager *)gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->S3_arr5031[0].PositionX);
  v23 = gta2::MapRelatedStruct_sub_46B440(gMapRelatedStruct, v22, v24, v25, self, v27);
  if ( v23 )
    gta2::sub_4BA2B0(&dword_5E6874, p_PositionZ->field);
  return v23;
}


// 0x004bd8a0: SpriteS1::sub_4BD8A0
// IDA: SpriteS1::sub_4BD8A0
// Ghidra: FUN_004bd8a0
void gta2::SpriteS1_sub_4BD8A0(SpriteS1 *param_1,undefined4 *param_2,SpriteS1 *param_3, int *param_4,short param_5,undefined1 *param_6,undefined1 *param_7, char *param_8)
{
  undefined2 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  char cVar4;
  undefined4 *puVar5;
  struct SpriteS1 *pSVar6;
  void *self;
  uint *puVar7;
  struct SpriteS1 **ppSVar8;
  uint local_2c [2];
  uint local_24 [2];
  undefined4 local_1c;
  struct SpriteS1 *local_18;
  struct SpriteS1 *local_14;
  SpriteS1 *local_10 [3];
  
  gta2::SpriteS1_sub_4207B0(param_1,&local_18);
  uVar1 = *(undefined2 *)&param_1->FirstElement;
  *param_6 = 5;
  *param_7 = 5;
  local_1c = CONCAT22(local_1c._2_2_,uVar1);
  gta2::SpriteS1_sub_420600((Sprite *)param_1,*param_4,param_4[1],
                      param_1->Matrix3DArray[0].PositionZ);
  gta2::SpriteS1_SetRotation((Sprite *)param_1,param_5);
  gta2::SpriteS1_sub_4BCB40((Sprite *)param_1);
  cVar4 = FUN_004bb3c0(param_1,local_2c,local_24);
  *param_8 = cVar4;
  if (cVar4 == '\0') {
    cVar4 = FUN_004bb3c0(param_3,local_2c,local_24);
    *param_8 = cVar4;
    gta2::SpriteS1_sub_420600((Sprite *)param_1,(int)local_18,(int)local_14,
                        param_1->Matrix3DArray[0].PositionZ);
    gta2::SpriteS1_SetRotation((Sprite *)param_1,(short)local_1c);
    if (*param_8 == '\0') {
      puVar5 = &local_1c;
      ppSVar8 = local_10;
      pSVar6 = (struct SpriteS1 *)&local_18;
      puVar7 = local_24;
      local_1c = 2;
      self = (void *)gta2::SpriteS1_sub_4207B0(param_3,local_2c);
    }
    else {
      if (*param_8 == '\x01') {
        puVar5 = (undefined4 *)FUN_0049ea30(local_10,local_2c[0] & 0xff);
        uVar2 = *puVar5;
        uVar3 = puVar5[1];
        *param_7 = (char)local_2c[0];
        *param_2 = uVar2;
        param_2[1] = uVar3;
        return;
      }
      puVar5 = &local_1c;
      ppSVar8 = local_10;
      local_1c = 2;
      pSVar6 = (struct SpriteS1 *)FUN_0049ea30(&local_18,local_24[0] & 0xff);
      puVar7 = local_24;
      self = (void *)FUN_0049ea30(local_2c,local_2c[0] & 0xff);
    }
  }
  else {
    gta2::SpriteS1_sub_420600((Sprite *)param_1,(int)local_18,(int)local_14,
                        param_1->Matrix3DArray[0].PositionZ);
    gta2::SpriteS1_SetRotation((Sprite *)param_1,(short)local_1c);
    gta2::SpriteS1_sub_4BCB40((Sprite *)param_1);
    if (*param_8 == '\x01') {
      puVar5 = (undefined4 *)FUN_0049ea30(&local_18,local_2c[0] & 0xff);
      uVar2 = *puVar5;
      uVar3 = puVar5[1];
      *param_6 = (char)local_2c[0];
      *param_2 = uVar2;
      param_2[1] = uVar3;
      return;
    }
    puVar5 = &local_1c;
    ppSVar8 = &local_18;
    local_1c = 2;
    pSVar6 = (struct SpriteS1 *)FUN_0049ea30(local_24,local_24[0] & 0xff);
    puVar7 = local_2c;
    self = (void *)FUN_0049ea30(local_10,local_2c[0] & 0xff);
  }
  FUN_0040f5c0(self,puVar7,pSVar6);
  puVar5 = (undefined4 *)gta2::FUN_0049e360(ppSVar8,puVar5);
  uVar2 = puVar5[1];
  *param_2 = *puVar5;
  param_2[1] = uVar2;
  return;
}


// 0x004bdc90: SpriteS1::SpriteS1_des
// IDA: SpriteS1::SpriteS1_des
// Ghidra: ---
SpriteS1 * gta2::SpriteS1_SpriteS1_des(struct SpriteS1 *self, char a2)
{
  gta2::SpriteS1_sub_4BC970(self);
  if ( (a2 & 1) != 0 )
    free(self);
  return self;
}


// 0x004bddb0: SpriteS1::sub_4BDDB0
// IDA: SpriteS1::sub_4BDDB0
// Ghidra: ---
_DWORD * gta2::SpriteS1_sub_4BDDB0(struct SpriteS1 *self)
{
  _DWORD *result; // eax

  result = gta2::SpriteS1_sub_4BCBD0(self);
  qmemcpy(self->S3_arr5031[0].SpriteS1_, self->S3_arr5031[0].SpriteS3, 0x4Cu);
  return result;
}


// 0x004bdef0: SpriteS1::sub_4BDEF0
// IDA: SpriteS1::sub_4BDEF0
// Ghidra: ---
int gta2::SpriteS1_sub_4BDEF0(struct SpriteS1 *self, int a2, int a3)
{
  int result; // eax

  gta2::SpriteS1_sub_4BCBD0(self);
  LOBYTE(result) = gta2::sub_4BA1A0(self->S3_arr5031[0].SpriteS1_, a2);
  if ( a3 == 1 )
    LOBYTE(result) = gta2::sub_4BA1A0(self->S3_arr5031[0].SpriteS3, a2);
  return result;
}


// 0x004bdfe0: SpriteS1::sub_4BDFE0
// IDA: SpriteS1::sub_4BDFE0
// Ghidra: ---
SpriteS1 * gta2::SpriteS1_sub_4BDFE0(struct SpriteS1 *self, int a2)
{
  struct MapRelatedStruct *pMapRelatedStruct; // edi
  int v4; // eax
  struct SpriteS1 *v6; // eax
  struct SpriteS1 *v7; // esi

  gta2::SpriteS1_sub_4BCB40(self);
  gta2::SpriteS3_sub_4BC580(self->S3_arr5031[0].SpriteS3);
  pMapRelatedStruct = gMapRelatedStruct;
  gta2::SpriteS1_sub_4B9F30(self);
  v4 = gta2::AudioSourceParams_sub_41F9D0((struct AudioSourceParams *)&self->S3_arr5031[0].PositionZ);
  if ( gta2::MapRelatedStruct_sub_466170(pMapRelatedStruct, v4) )
    return unk_5E6894;
  v6 = gta2::S56_sub_447740(gCheckpoint1, self, a2);
  v7 = v6;
  if ( v6 )
    gta2::sub_40FEE0(&dword_5E6874, (int)v6);
  return v7;
}


// 0x004be060: SpriteS1::sub_4BE060
// IDA: SpriteS1::sub_4BE060
// Ghidra: ---
char gta2::SpriteS1_sub_4BE060(SpriteS1 *pSpriteS1, Car *a2)
{
  struct Car *v2; // ebp
  struct Style *pS15; // esi
  int Sprite; // esi
  unsigned __int16 global_sprite_id; // ax
  int v7; // edi
  char v8; // cl
  char result; // al
  struct Car *v10; // eax
  int v11; // edx
  GLuint *v12; // eax
  int v13; // eax
  int v14; // eax
  __int16 Remap; // dx
  __int16 spriteId; // cx
  struct SpriteS1 *SpriteS1; // ecx
  int PositionZ; // edx
  int PositionY; // eax
  int v20; // ecx
  struct SpriteS1 *pSprite1_; // edi
  double v22; // st7
  struct SpriteS1 *FirstElement; // ebp
  struct Car *pCar; // ebp
  int v25; // eax
  unsigned __int16 v26; // si
  int v27; // eax
  int v28; // edx
  struct GameObject *GameObject; // eax
  struct Ped *v30; // eax
  struct Player *v31; // ecx
  int *v32; // eax
  double v33; // st7
  int v34; // eax
  CAR_LIGHTS_AND_DOORS_BITSTATE *p_carLights; // ebp
  int v36; // eax
  unsigned __int16 v37; // si
  unsigned __int16 v38; // ax
  int v39; // edx
  GLuint *v40; // esi
  S202 v41; // [esp-20h] [ebp-ECh]
  S202 v42; // [esp-20h] [ebp-ECh]
  int v43; // [esp-4h] [ebp-D0h]
  int v44; // [esp+0h] [ebp-CCh] BYREF
  char v45; // [esp+Bh] [ebp-C1h] BYREF
  int v46; // [esp+Ch] [ebp-C0h] BYREF
  int v47; // [esp+14h] [ebp-B8h]
  struct Car *v48; // [esp+18h] [ebp-B4h]
  void *v49; // [esp+1Ch] [ebp-B0h] BYREF
  int v50; // [esp+20h] [ebp-ACh] BYREF
  int v51; // [esp+28h] [ebp-A4h] BYREF
  int v52; // [esp+2Ch] [ebp-A0h] BYREF
  int v53; // [esp+30h] [ebp-9Ch] BYREF
  int v54; // [esp+34h] [ebp-98h]
  GLuint *v55; // [esp+38h] [ebp-94h]
  int v56; // [esp+3Ch] [ebp-90h] BYREF
  _DWORD v57[2]; // [esp+40h] [ebp-8Ch] BYREF
  float v58; // [esp+48h] [ebp-84h] BYREF
  float v59[8]; // [esp+4Ch] [ebp-80h] BYREF
  float v60[8]; // [esp+6Ch] [ebp-60h] BYREF
  float v61[8]; // [esp+8Ch] [ebp-40h] BYREF
  float v62[8]; // [esp+ACh] [ebp-20h] BYREF

  gta2::SpriteS1_sub_4BCBD0(pSpriteS1);
  if ( LOBYTE(pSpriteS1->S3_arr5031[0].field_34) )
  {
    pS15 = gStyle;
    v56 = gta2::Style_sub_4B9F20(gStyle, v49);
    Sprite = gta2::Style_GetSprite(pS15, v56);
    v54 = Sprite;
    global_sprite_id = gta2::SpriteS1_get_global_sprite_id(pSpriteS1);
    v7 = gta2::Style_GetSprite(gStyle, global_sprite_id);
    v8 = *(_BYTE *)(v7 + 4) - 2 * LOBYTE(pSpriteS1->S3_arr5031[0].field_34);
    *(_BYTE *)(Sprite + 4) = v8;
    result = *(_BYTE *)(v7 + 5) - 2 * LOBYTE(pSpriteS1->S3_arr5031[0].field_34);
    *(_BYTE *)(Sprite + 5) = result;
    if ( !v8 || !result )
      return result;
    *(_DWORD *)Sprite = *(_DWORD *)v7 + 257 * LOBYTE(pSpriteS1->S3_arr5031[0].field_34);
    LOWORD(v10) = gta2::SpriteS1_sub_4BABE0(pSpriteS1);
    v11 = *(_DWORD *)Sprite;
    v48 = v10;
    LOWORD(v10) = *(unsigned __int8 *)(Sprite + 5);
    v12 = gta2::TextureManager_sub_4C2CE0(
            gTextureManager,
            *(unsigned __int8 *)(Sprite + 4),
            (GLuint)v10,
            v11,
            (unsigned __int16)v48);
  }
  else
  {
    LOWORD(v13) = gta2::SpriteS1_get_global_sprite_id(pSpriteS1);
    v56 = v13;
    v14 = gta2::Style_GetSprite(gStyle, v13);
    Remap = pSpriteS1->S3_arr5031[0].Remap;
    spriteId = HIWORD(pSpriteS1->S3_arr5031[0].spriteId);
    v54 = v14;
    v12 = (GLuint *)gta2::TextureManager_sub_4C2AC0(
                      gTextureManager,
                      pSpriteS1->S3_arr5031[0].sprite_type,
                      spriteId,
                      pSpriteS1->S3_arr5031[0].field_30,
                      Remap);
    Sprite = v54;
  }
  SpriteS1 = pSpriteS1->S3_arr5031[0].SpriteS1_;
  v55 = v12;
  if ( !LOBYTE(SpriteS1->S3_arr5031[1].SpriteS3) )
  {
    LOWORD(v12) = pSpriteS1->FirstElement;
    PositionZ = pSpriteS1->S3_arr5031[0].PositionZ;
    v48 = (struct Car *)v12;
    PositionY = pSpriteS1->S3_arr5031[0].PositionY;
    v47 = PositionZ;
    gta2::SpriteS1_sub_4BBD40(SpriteS1, pSpriteS1->S3_arr5031[0].PositionX, PositionY);
  }
  v20 = *(unsigned __int8 *)(Sprite + 5);
  v53 = *(unsigned __int8 *)(Sprite + 4);
  pSprite1_ = pSpriteS1->S3_arr5031[0].SpriteS1_;
  v22 = (double)v53;
  v53 = v20;
  v48 = v2;
  pSprite1_ = (struct SpriteS1 *)((char *)pSprite1_ + 12);
  v58 = v22 - 0.30000001;
  *(float *)&v57[1] = (double)v20 - 0.30000001;
  FirstElement = sub_4B9C70((struct SpriteS1 *)&v52, &pSpriteS1->S3_arr5031[0].PositionZ)->FirstElement;
  gta2::sub_4BA4D0((int *)pSprite1_, &flt_66FE18, *(float *)&FirstElement);
  gta2::sub_4BA4D0((int *)&pSprite1_->S3_arr5031[0].GameObject, &flt_66FE38, *(float *)&FirstElement);
  gta2::sub_4BA4D0((int *)&pSprite1_->S3_arr5031[0].NextElement, flt_66FE58, *(float *)&FirstElement);
  gta2::sub_4BA4D0(&pSprite1_->S3_arr5031[0].PositionY, &flt_66FE78, *(float *)&FirstElement);
  gta2::sub_4B9BC0(&v58);
  pCar = gta2::SpriteS1_GetCar(pSpriteS1);
  if ( pCar )
  {
    if ( LOBYTE(pSpriteS1->S3_arr5031[0].field_34) )
      gta2::SpriteS3_sub_44AFB0(gSpriteS3, (unsigned __int16 *)&v56);
    v53 = gta2::sub_4A5190(&pCar->PlayerStats_);
    if ( gLighting )
    {
      if ( gta2::Car_sub_421680(pCar, v48) )
      {
        gta2::sub_4BA360(&pCar->PlayerStats_);
      }
      else if ( gta2::Car_isEDSELFBI(pCar) )
      {
        gta2::sub_4BA370();
      }
      else
      {
        gta2::sub_4BA350();
      }
      gta2::sub_4BA340(&pCar->PlayerStats_);
    }
    v57[0] = 0;
    LOWORD(v25) = gta2::SpriteS1_sub_4BABE0(pSpriteS1);
    v52 = v25;
    v26 = gta2::sub_44B0C0(&pCar->PlayerStats_, (unsigned __int16 *)&v56, (_BYTE *)&v51 + 3, (__int16 *)&v52, v57);
    if ( v26 != 0xFFFF )
    {
      if ( HIBYTE(v51) )
      {
        LOWORD(v27) = gta2::SpriteS1_sub_4BABE0(pSpriteS1);
        v47 = v27;
        LOWORD(v28) = *(unsigned __int8 *)(v54 + 5);
        gta2::TextureManager_sub_4C2C80(gTextureManager, v26, *(unsigned __int8 *)(v54 + 4), v28, v27);
      }
      v55 = gta2::TextureManager_sub_4C2BA0(gTextureManager, v26);
    }
    gta2::sub_4A51A0(&pCar->PlayerStats_, &v53);
  }
  else
  {
    GameObject = gta2::SpriteS1_GetGameObject(pSpriteS1);
    if ( GameObject )
    {
      v30 = gta2::GameObject_sub_433A20(GameObject);
      if ( v30 )
      {
        v31 = *(Player **)&v30->isPlayer;
        if ( v31 )
        {
          if ( (v30->PositionX1 & 0x2000000) != 0 )
          {
            result = gta2::Player_GetCurrentPlayer(v31);
            if ( !result )
              return result;
          }
        }
      }
    }
  }
  if ( gta2::SpriteS1_sub_4BAC10(pSpriteS1) )
  {
    qmemcpy(v59, &flt_66FE18, sizeof(v59));
    qmemcpy(v60, &flt_66FE38, sizeof(v60));
    qmemcpy(v61, flt_66FE58, sizeof(v61));
    qmemcpy(v62, &flt_66FE78, sizeof(v62));
    v52 = 5;
    v32 = (int *)gta2::sub_401BD0(&gCameraOrPhysics->cameraPosTarget_[4].field_4, (struct SpriteS1 *)v57, &v52);
    v33 = gta2::Float10_EncodedFloatToRegularFloat(v32);
    v59[0] = flt_66FE18 + v33;
    v59[4] = -1.0842022e-19;
    v60[4] = -1.0842022e-19;
    v61[4] = -1.0842022e-19;
    v62[4] = -1.0842022e-19;
    v60[0] = flt_66FE38 + v33;
    v61[0] = flt_66FE58[0] + v33;
    v62[0] = flt_66FE78 + v33;
    v59[1] = v59[1] + v33;
    v60[1] = v60[1] + v33;
    v61[1] = v61[1] + v33;
    v62[1] = v62[1] + v33;
    gbh_DrawQuad(8576, v55, v59, 255);
  }
  v43 = v51;
  LOBYTE(v34) = gta2::SpriteS1_sub_4BAC60(pSpriteS1);
  gbh_DrawQuad(v34, v43, &flt_66FE18, 255);
  if ( pCar && gLighting )
  {
    p_carLights = &pCar->PlayerStats_;
    gta2::sub_4BA330(p_carLights);
    v46 = 1;
    LOWORD(v36) = gta2::SpriteS1_sub_4BABE0(pSpriteS1);
    v50 = v36;
    v37 = gta2::sub_44B0C0(p_carLights, (unsigned __int16 *)&v49, &v45, (__int16 *)&v50, &v46);
    if ( v37 != 0xFFFF )
    {
      if ( v45 )
      {
        v38 = gta2::SpriteS1_sub_4BABE0(pSpriteS1);
        LOWORD(v39) = *(unsigned __int8 *)(v47 + 5);
        gta2::TextureManager_sub_4C2C80(gTextureManager, v37, *(unsigned __int8 *)(v47 + 4), v39, v38);
      }
      v40 = gta2::TextureManager_sub_4C2BA0(gTextureManager, v37);
      gta2::sub_4B9BC0(&v51);
      gbh_DrawQuad(128, v40, &flt_66FE18, 255);
    }
    gta2::sub_4A51A0(p_carLights, &v44);
  }
  ++gSpriteEntry->ptr;
  if ( do_show_collision_box )
  {
    if ( pSpriteS1->S3_arr5031[0].SpriteS3 )
      sub_4BC590(pSpriteS1->S3_arr5031[0].PositionZ);
  }
  v41.S202 = (struct S202 *)&unk_66FE3C;
  v41.field_0 = (int)&flt_66FE38;
  sub_4BACF0(pSpriteS1, v41);
  v42.S202 = (struct S202 *)&unk_66FE7C;
  v42.field_0 = (int)&flt_66FE78;
  gta2::sub_4BAEF0(pSpriteS1, v42);
  return result;
}


// 0x004be570: SpriteS1::sub_4BE570
// IDA: SpriteS1::sub_4BE570
// Ghidra: FUN_004be570
void * gta2::SpriteS1_sub_4BE570(void *self,Sprite *pSprite)
{
  char cVar1;
  char cVar2;
  undefined3 extraout_var;
  void *pvVar3;
  
  cVar2 = gta2::SpriteS1_sub_4BD2E0(pSprite);
  gta2::SpriteS1_sub_4BD2E0((Sprite *)self);
  cVar1 = *(char *)((int)self + 0x39);
  pvVar3 = (void *)CONCAT31(extraout_var,cVar1);
  if (cVar2 < cVar1) {
    gta2::SpriteS1_sub_4BA220(pSprite,cVar1);
    return pvVar3;
  }
  *(char *)((int)self + 0x39) = cVar2;
  return pvVar3;
}



