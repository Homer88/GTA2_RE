#include "gta2_shim.h"

// Module: other, Class: MissionScriptObjectData
// Functions: 86
// Source: unified (IDA+Ghidra)

// 0x004751b0: MissionScriptObjectData::sub_4751B0
// IDA: MissionScriptObjectData::sub_4751B0
// Ghidra: ---
__int16 gta2::MissionScriptObjectData_sub_4751B0(struct MissionScriptObjectData *self)
{
  __int16 v1; // ax
  __int16 result; // ax

  v1 = word_5931F8;
  self->field_118 = 0;
  self->field_11A = v1;
  result = v1 + 1;
  word_5931F8 = result;
  return result;
}


// 0x004751e0: MissionScriptObjectData::sub_4751E0
// IDA: MissionScriptObjectData::sub_4751E0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_4751E0(struct MissionScriptObjectData *self)
{
  self->field_4 = -1;
}


// 0x00475230: MissionScriptObjectData::sub_475230
// IDA: MissionScriptObjectData::sub_475230
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_475230(struct MissionScriptObjectData *self, int a2)
{
  _WORD *v2; // eax
  __int16 v4; // [esp-2Ch] [ebp-2Ch]
  __int16 v5; // [esp-28h] [ebp-28h]
  __int16 v6; // [esp-24h] [ebp-24h]
  __int16 v7; // [esp-20h] [ebp-20h]
  __int16 v8; // [esp-1Ch] [ebp-1Ch]
  __int16 v9; // [esp-18h] [ebp-18h]
  __int16 v10; // [esp-14h] [ebp-14h]
  __int16 v11; // [esp-10h] [ebp-10h]
  __int16 v12; // [esp-Ch] [ebp-Ch]
  __int16 v13; // [esp-8h] [ebp-8h]
  __int16 v14; // [esp-4h] [ebp-4h]

  v14 = *(_WORD *)(a2 + 26);
  v13 = *(_WORD *)(a2 + 24);
  v12 = *(_WORD *)(a2 + 22);
  v11 = *(_WORD *)(a2 + 20);
  v10 = *(_WORD *)(a2 + 18);
  v9 = *(_WORD *)(a2 + 16);
  v8 = *(_WORD *)(a2 + 28);
  v7 = *(_WORD *)(a2 + 14);
  v6 = *(_WORD *)(a2 + 12);
  v5 = *(_WORD *)(a2 + 10);
  v4 = *(_WORD *)(a2 + 8);
  v2 = gta2::MissionManager_sub_474F00(gMissionManager, *(_WORD *)a2);
  return (unsigned __int8)gta2::MapRelatedStruct_sub_465280(
                            gMapRelatedStruct,
                            (__int16)v2[1],
                            v4,
                            v5,
                            v6,
                            v7,
                            v8,
                            v9,
                            v10,
                            v11,
                            v12,
                            v13,
                            v14);
}


// 0x00475290: MissionScriptObjectData::sub_475290
// IDA: MissionScriptObjectData::sub_475290
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_475290(struct MissionScriptObjectData *self, int a2)
{
  char result; // al

  result = a2;
  *(_DWORD *)(a2 + 8) = 0;
  return result;
}


// 0x004752a0: MissionScriptObjectData::sub_4752A0
// IDA: MissionScriptObjectData::sub_4752A0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4752A0(struct MissionScriptObjectData *self, int a2)
{
  int v2; // eax
  int v4; // [esp+8h] [ebp+8h]

  v2 = gta2::S105_sub_44A9C0(gS105, *(SpriteS1 **)(a2 + 12), *(_DWORD *)(a2 + 16));
  *(_DWORD *)(v4 + 8) = v2;
  return v2;
}


// 0x004752d0: MissionScriptObjectData::sub_4752D0
// IDA: MissionScriptObjectData::sub_4752D0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4752D0(struct MissionScriptObjectData *self, int a2)
{
  return gta2::Door_sub_44C760(gDoor, *(_WORD *)(a2 + 8), *(_WORD *)(a2 + 10), *(_BYTE *)(a2 + 12));
}


// 0x004752f0: MissionScriptObjectData::sub_4752F0
// IDA: MissionScriptObjectData::sub_4752F0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4752F0(struct MissionScriptObjectData *self, int a2)
{
  char result; // al
  const char *v4; // eax
  void *v5; // eax
  BaseCar *v6; // eax
  unsigned __int8 v7; // dl
  int *p_SkipTrains; // edi
  int v9; // ebx
  int v10; // ecx
  int v11; // edx
  BaseCar *v12; // [esp+0h] [ebp-4h]
  unsigned __int8 v13; // [esp+8h] [ebp+4h]

  result = skip_trains;
  if ( !skip_trains )
  {
    v4 = (const char *)gta2::MissionManager_sub_474F00(gMissionManager, *(_WORD *)(a2 + 8));
    v5 = (void *)gta2::MapRelatedStruct_sub_464C70(gMapRelatedStruct, v4 + 9);
    v6 = gta2::PublicTransport_sub_4AF660(gPublicTransport, v5);
    v7 = 0;
    v12 = v6;
    v13 = 0;
    p_SkipTrains = &v6->SkipTrains;
    v9 = -36 - (_DWORD)v6;
    do
    {
      if ( v7 >= *(_BYTE *)(a2 + 10) )
      {
        v10 = *(unsigned __int8 *)(a2 + 10);
        v11 = *(unsigned __int8 *)(a2 + 11);
        if ( (int)p_SkipTrains + v9 >= v10 + v11 )
        {
          if ( (int)p_SkipTrains + v9 < v11 + v10 + *(unsigned __int8 *)(a2 + 12) )
            *(_BYTE *)p_SkipTrains = 3;
        }
        else
        {
          *(_BYTE *)p_SkipTrains = 2;
        }
      }
      else
      {
        *(_BYTE *)p_SkipTrains = 1;
      }
      v7 = v13 + 1;
      p_SkipTrains = (int *)((char *)p_SkipTrains + 1);
      ++v13;
    }
    while ( v13 < 0xAu );
    result = *(_BYTE *)(a2 + 10);
    v12->field_2E = result + *(_BYTE *)(a2 + 11) + *(_BYTE *)(a2 + 12);
  }
  return result;
}


// 0x004753b0: MissionScriptObjectData::sub_4753B0
// IDA: MissionScriptObjectData::sub_4753B0
// Ghidra: ---
int gta2::MissionScriptObjectData_sub_4753B0(struct MissionScriptObjectData *self, int a2)
{
  return (int)gta2::DMAudio_sub_410580(&gDMAudio, *(unsigned __int8 *)(a2 + 16), *(_DWORD *)(a2 + 8), *(_DWORD *)(a2 + 12));
}


// 0x004753d0: MissionScriptObjectData::sub_4753D0
// IDA: MissionScriptObjectData::sub_4753D0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4753D0(struct MissionScriptObjectData *self, int a2)
{
  char result; // al
  const char *v3; // eax
  void *v4; // eax
  PublicTransport *pPublicTransport; // eax

  result = skip_trains;
  if ( !skip_trains )
  {
    v3 = (const char *)gta2::MissionManager_sub_474F00(gMissionManager, *(_WORD *)(a2 + 8));
    v4 = (void *)gta2::MapRelatedStruct_sub_464C70(gMapRelatedStruct, v3 + 9);
    pPublicTransport = (PublicTransport *)gta2::PublicTransport_sub_4AF660(gPublicTransport, v4);
    return gta2::PublicTransport_sub_4AF460(pPublicTransport, a2 + 10);
  }
  return result;
}


// 0x004754e0: MissionScriptObjectData::sub_4754E0
// IDA: MissionScriptObjectData::sub_4754E0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4754E0(struct MissionScriptObjectData *self, int a2)
{
  int v2; // eax

  LOWORD(v2) = *(_WORD *)(a2 + 2) - 344;
  switch ( *(_WORD *)(a2 + 2) )
  {
    case 0x158:
      v2 = *(__int16 *)(a2 + 10);
      gMissionManager->field_314 = v2;
      break;
    case 0x159:
      LOBYTE(v2) = (_BYTE)gMissionManager;
      gMissionManager->field_318 = *(__int16 *)(a2 + 10);
      break;
    case 0x182:
      gMissionManager->field_31C = *(__int16 *)(a2 + 10);
      break;
    case 0x183:
      v2 = *(__int16 *)(a2 + 10);
      gMissionManager->field_320 = v2;
      break;
    case 0x184:
      LOBYTE(v2) = (_BYTE)gMissionManager;
      gMissionManager->field_324 = *(__int16 *)(a2 + 10);
      break;
    default:
      return v2;
  }
  return v2;
}


// 0x004755b0: MissionScriptObjectData::sub_4755B0
// IDA: MissionScriptObjectData::sub_4755B0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4755B0(struct MissionScriptObjectData *self, int a2)
{
  char result; // al

  result = a2;
  gMissionManager->Health = *(_DWORD *)(a2 + 8);
  return result;
}


// 0x004755d0: MissionScriptObjectData::sub_4755D0
// IDA: MissionScriptObjectData::sub_4755D0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4755D0(struct MissionScriptObjectData *self, int a2)
{
  char result; // al

  result = a2 + 8;
  gMissionManager->field_340 = a2 + 8;
  return result;
}


// 0x004755f0: MissionScriptObjectData::sub_4755F0
// IDA: MissionScriptObjectData::sub_4755F0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4755F0(struct MissionScriptObjectData *self, int a1)
{
  wchar_t *v2; // eax
  int v4; // [esp-8h] [ebp-8h]

  LOBYTE(v2) = do_text_id_test;
  if ( do_text_id_test )
  {
    strcpy(gStr, "%d", *(unsigned __int16 *)(v4 + 8));
    v2 = gta2::Text__Bsearch(gText, gStr);
    if ( !v2 )
      LOBYTE(v2) = gta2::debug_log(0x47Cu, "miss2.cpp", 2460);
  }
  return (char)v2;
}


// 0x00475650: MissionScriptObjectData::sub_475650
// IDA: MissionScriptObjectData::sub_475650
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_475650(struct MissionScriptObjectData *self, int a2)
{
  __int16 v2; // ax

  v2 = *(_WORD *)(a2 + 2);
  switch ( v2 )
  {
    case 435:
      v2 = *(_WORD *)(a2 + 12);
      gMissionManager->field_356 = v2;
      break;
    case 436:
      LOBYTE(v2) = (_BYTE)gMissionManager;
      gMissionManager->field_358 = *(_WORD *)(a2 + 12);
      break;
    case 437:
      gMissionManager->field_35A = *(_WORD *)(a2 + 12);
      break;
  }
  return v2;
}


// 0x004756b0: MissionScriptObjectData::sub_4756B0
// IDA: MissionScriptObjectData::sub_4756B0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4756B0(struct MissionScriptObjectData *self, int a2)
{
  unsigned __int16 v2; // ax

  v2 = 0;
  while ( *((_WORD *)gMissionManager->arr_12 + v2) )
  {
    if ( ++v2 >= 0x19u )
      return v2;
  }
  *((_WORD *)gMissionManager->arr_12 + v2) = *(_WORD *)a2;
  return v2;
}


// 0x00475b70: MissionScriptObjectData::sub_475B70
// IDA: MissionScriptObjectData::sub_475B70
// Ghidra: ---
int gta2::MissionScriptObjectData_sub_475B70(struct MissionScriptObjectData *self, char a2, __int16 a3)
{
  int result; // eax

  self->field_4 = a3;
  result = 0;
  self->field_6 = a2;
  self->field_E = 0;
  self->field_C = 0;
  self->field_12 = 0;
  self->field_8 = 0;
  self->field_10 = 0;
  return result;
}


// 0x00475ba0: MissionScriptObjectData::MissionScriptObjectData
// IDA: MissionScriptObjectData::MissionScriptObjectData
// Ghidra: ---
void gta2::MissionScriptObjectData_MissionScriptObjectData(struct MissionScriptObjectData *self)
{
  S29 *pS29; // eax
  S29 *ppS29; // eax

  self->NextElement = 0;
  pS29 = (S29 *)gta2::operator_new(8u);
  if ( pS29 )
    ppS29 = gta2::S29_S29(pS29);
  else
    ppS29 = 0;
  self->S29_ = ppS29;
  self->field_4 = 0;
  self->field_6 = 0;
  self->field_8 = 0;
  self->field_C = 0;
  self->field_E = 0;
  self->field_10 = 0;
  self->field_12 = 0;
  self->field_11A = 0;
  memset(self->arr, 0, sizeof(self->arr));
  self->field_110 = 0;
  self->field_112 = 0;
  self->field_118 = 0;
}


// 0x00476e50: MissionScriptObjectData::sub_476E50
// IDA: MissionScriptObjectData::sub_476E50
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_476E50(struct MissionScriptObjectData *self, MissionManager *a2)
{
  if ( LOWORD(a2->arr_96[0]) == 0xFFFF )
  {
    gta2::MissionScriptObjectData_sub_4751E0(self);
  }
  else
  {
    unk_6644C8 = (unsigned __int16)self->field_4;
    self->field_4 = a2->arr_96[0];
    self->field_C = 0;
  }
}


// 0x00476e80: MissionScriptObjectData::sub_476E80
// IDA: MissionScriptObjectData::sub_476E80
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_476E80(struct MissionScriptObjectData *self, __int16 a2)
{
  if ( a2 == -1 )
    gta2::MissionScriptObjectData_sub_4751E0(self);
  else
    self->field_4 = a2;
}


// 0x00476ea0: MissionScriptObjectData::sub_476EA0
// IDA: MissionScriptObjectData::sub_476EA0
// Ghidra: ---
void * gta2::MissionScriptObjectData_sub_476EA0(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  int v2; // esi
  int *v3; // ebx
  unsigned __int16 v4; // di
  int v5; // ecx
  int v6; // ebp
  EventHandler *pS63; // eax
  int v8; // edx
  EventHandler *v9; // esi
  unsigned __int8 v10; // dl
  _BYTE a3[4]; // [esp+10h] [ebp-4h] BYREF
  unsigned __int8 index; // [esp+1Ch] [ebp+8h] OVERLAPPED

  v2 = pCarSystemManager;
  v3 = (int *)(pCarSystemManager + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(pCarSystemManager + 20), (Player *)&unk_664F58) )
    *v3 = *gta2::MapRelatedStruct_FindMaxZForLocation(
             gMapRelatedStruct,
             &pCarSystemManager,
             *(int **)(v2 + 12),
             *(S202 **)(v2 + 16));
  v4 = *(_WORD *)(v2 + 24);
  if ( v4 < 0xC8u || v4 > 0xF4u )
  {
    gta2::sub_41F990(a3, *(_WORD *)(v2 + 26));
    LOWORD(v8) = *gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
    v6 = *(_DWORD *)&index;
    pS63 = gta2::Object_SpawnObject(gObject, v4, *(_DWORD *)(v2 + 12), *(_DWORD *)(v2 + 16), *v3, v8);
  }
  else
  {
    gta2::sub_41F990(a3, *(_WORD *)(v2 + 26));
    LOWORD(v5) = *gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
    v6 = *(_DWORD *)&index;
    pS63 = gta2::Object_sub_485480(gObject, (S900 *)v4, *(_DWORD *)(v2 + 12), *(_DWORD *)(v2 + 16), *v3, v5);
  }
  v9 = pS63;
  *(_DWORD *)(v6 + 8) = pS63;
  if ( pS63 )
  {
    LOBYTE(pS63) = gta2::Car_sub_475AA0(pS63);
    if ( (_BYTE)pS63 )
    {
      gta2::HudArrow_Update(&gHud->HudArrow_, (int)v9);
      v10 = 0;
      index = 0;
      while ( 1 )
      {
        pS63 = *(EventHandler **)&index;
        if ( !*((_WORD *)gMissionManager->arr2_15 + index) )
          break;
        index = ++v10;
        if ( v10 >= 0x1Fu )
          return pS63;
      }
      pS63 = (EventHandler *)index;
      *((_WORD *)gMissionManager->arr2_15 + index) = *(_WORD *)v6;
    }
  }
  return pS63;
}


// 0x00476ff0: MissionScriptObjectData::sub_476FF0
// IDA: MissionScriptObjectData::sub_476FF0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_476FF0(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  int v2; // esi
  int *v3; // ebp
  unsigned __int16 v4; // di
  int v5; // ecx
  EventHandler **v6; // ebx
  EventHandler *v7; // eax
  int v8; // edx
  EventHandler *v9; // ebx
  _BYTE a3[4]; // [esp+10h] [ebp-4h] BYREF
  int pCarSystemManager_4; // [esp+1Ch] [ebp+8h]

  v2 = pCarSystemManager;
  v3 = (int *)(pCarSystemManager + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(pCarSystemManager + 20), (Player *)&unk_664F58) )
    *v3 = *gta2::MapRelatedStruct_FindMaxZForLocation(
             gMapRelatedStruct,
             &pCarSystemManager,
             *(int **)(v2 + 12),
             *(S202 **)(v2 + 16));
  v4 = *(_WORD *)(v2 + 24);
  if ( v4 < 0xC8u || v4 > 0xF4u )
  {
    gta2::sub_41F990(a3, *(_WORD *)(v2 + 26));
    LOWORD(v8) = *gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
    v6 = (EventHandler **)(pCarSystemManager_4 + 8);
    v7 = gta2::Object_SpawnObject(gObject, v4, *(_DWORD *)(v2 + 12), *(_DWORD *)(v2 + 16), *v3, v8);
  }
  else
  {
    gta2::sub_41F990(a3, *(_WORD *)(v2 + 26));
    LOWORD(v5) = *gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
    v6 = (EventHandler **)(pCarSystemManager_4 + 8);
    v7 = gta2::Object_sub_485480(gObject, (S900 *)v4, *(_DWORD *)(v2 + 12), *(_DWORD *)(v2 + 16), *v3, v5);
  }
  *v6 = v7;
  v9 = v7;
  if ( v7 )
  {
    if ( gta2::sub_475A70(v7) )
    {
      gta2::S63_sub_447E90(v9, *(_BYTE *)(v2 + 28));
    }
    else if ( gta2::S63_sub_421060(v9) )
    {
      gta2::S63_sub_45E0A0(v9, *(_BYTE *)(v2 + 28));
    }
    else
    {
      LOBYTE(v7) = gta2::sub_475A60(v9);
      if ( (_BYTE)v7 )
        LOBYTE(v7) = gta2::sub_475A50(v9, *(_BYTE *)(v2 + 28));
    }
  }
  return (char)v7;
}


// 0x00477140: MissionScriptObjectData::sub_477140
// IDA: MissionScriptObjectData::sub_477140
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477140(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  struct Ped *pPed; // eax
  struct Player *pPlayer; // ebx
  bool v4; // al
  int v5; // esi
  SpriteS1 *v6; // eax
  int *v7; // edi
  SpriteS1 *v8; // eax
  int *v9; // eax
  int *v10; // edi
  __int16 v11; // dx
  struct Ped *pPed1; // edi
  int *Sprite; // eax
  char a3; // [esp+4h] [ebp-10h] BYREF
  char v16; // [esp+8h] [ebp-Ch] BYREF
  char v17; // [esp+Ch] [ebp-8h] BYREF
  char v18; // [esp+10h] [ebp-4h] BYREF

  pPed = (Ped *)gta2::Game_GetNextInactivePlayer(gGame);
  pPlayer = (Player *)pPed;
  if ( pPed )
  {
    v4 = gta2::MissionManager_sub_475A20(gMissionManager);
    v5 = pCarSystemManager;
    if ( v4 )
    {
      v6 = gta2::sub_462EA0((SpriteS1 *)&v16, &dword_6645E8);
      v7 = (int *)gta2::S202_sub_401B20((S202 *)v6, (SpriteS1 *)&a3, (PublicTransport *)&unk_664EDC);
      v8 = gta2::sub_462EA0((SpriteS1 *)&v18, &dword_6645E4);
      v9 = (int *)gta2::S202_sub_401B20((S202 *)v8, (SpriteS1 *)&v17, (PublicTransport *)&unk_664E08);
      pPed = gta2::Character_SpawnPedAtPosition(gCharacter, *v9, *v7, *(int *)unk_6645EC, unk_664663, unk_664530);
    }
    else
    {
      v10 = (int *)(pCarSystemManager + 20);
      if ( gta2::Player_IsCurrentPlayer((Player *)(pCarSystemManager + 20), (Player *)&unk_664F58) )
        *v10 = *gta2::MapRelatedStruct_FindMaxZForLocation(
                  gMapRelatedStruct,
                  &pCarSystemManager,
                  *(int **)(v5 + 12),
                  *(S202 **)(v5 + 16));
      gta2::sub_41F990(&a3, *(_WORD *)(v5 + 24));
      v11 = *gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, &a3);
      pPed = gta2::Character_SpawnPedAtPosition(
               gCharacter,
               *(_DWORD *)(v5 + 12),
               *(_DWORD *)(v5 + 16),
               *v10,
               *(_BYTE *)(v5 + 26),
               v11);
    }
    pPed1 = pPed;
    if ( pPed )
    {
      gta2::Ped_SetSearchType(pPed, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY);
      if ( !gta2::MissionManager_sub_475A20(gMissionManager) )
        gta2::Ped_SetHealth(pPed1, 100);
      gta2::Player_sub_4A5B40(pPlayer, pPed1);
      *(_DWORD *)&pPed1->Invulnerability = 1;
      *(_DWORD *)(v5 + 8) = pPed1;
      Sprite = (int *)gta2::Ped_GetSprite(pPed1);
      LOBYTE(pPed) = (unsigned __int8)gta2::sub_4BDAD0(Sprite);
    }
  }
  return (char)pPed;
}


// 0x00477290: MissionScriptObjectData::sub_477290
// IDA: MissionScriptObjectData::sub_477290
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477290(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  int v2; // esi
  int *v3; // ebp
  __int16 v4; // di
  __int16 *v5; // eax
  void *pCar; // edi
  Car *v7; // eax
  __int16 v8; // dx
  __int16 *v9; // eax
  __int16 v10; // bx
  Car *v11; // ebx
  __int16 *v12; // eax
  Car *v13; // eax
  S202 *v14; // eax
  unsigned __int16 v15; // si
  Gang *v16; // eax
  _BYTE a3[4]; // [esp+Ch] [ebp-4h] BYREF
  int pCarSystemManager_4; // [esp+18h] [ebp+8h]

  v2 = pCarSystemManager;
  v3 = (int *)(pCarSystemManager + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(pCarSystemManager + 20), (Player *)&unk_664F58) )
    *v3 = *gta2::MapRelatedStruct_FindMaxZForLocation(
             gMapRelatedStruct,
             &pCarSystemManager,
             *(int **)(v2 + 12),
             *(S202 **)(v2 + 16));
  v4 = *(_WORD *)(v2 + 30);
  if ( v4 == -1 )
  {
    gta2::sub_41F990(a3, *(_WORD *)(v2 + 24));
    v5 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
    pCar = (void *)(pCarSystemManager_4 + 8);
    v7 = gta2::CarSystemManager_SpawnCar(
           gCarSystemManager,
           *(_DWORD *)(v2 + 12),
           *(_DWORD *)(v2 + 16),
           *v3,
           *v5,
           (CarModel *)*(__int16 *)(v2 + 28));
    *(_DWORD *)pCar = v7;
  }
  else if ( v4 == -2 )
  {
    gta2::sub_41F990(a3, *(_WORD *)(v2 + 24));
    v9 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
    v7 = gta2::CarSystemManager_sub_4764A0(
           gCarSystemManager,
           *(_DWORD *)(v2 + 12),
           *(_DWORD *)(v2 + 16),
           *v3,
           *v9,
           (CarModel *)*(__int16 *)(v2 + 28));
    pCar = (void *)(pCarSystemManager_4 + 8);
    *(_DWORD *)(pCarSystemManager_4 + 8) = v7;
    if ( v7 )
    {
      gta2::Car_SetLocksDoor_4(v7);
      gta2::Car_sub_476270(*(Car **)pCar);
      LOBYTE(v7) = gta2::Car_sub_424400(*(Car **)pCar);
    }
  }
  else
  {
    v10 = *(_WORD *)(v2 + 28);
    if ( v10 == 66 )
    {
      v11 = gta2::CarSystemManager_SpawnCar(
              gCarSystemManager,
              unk_6644F4,
              unk_6644F4,
              (int)gAudioSourceParams,
              unk_664530,
              (CarModel *)v4);
      gta2::sub_41F990(a3, *(_WORD *)(v2 + 24));
      v12 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
      v13 = gta2::CarSystemManager_SpawnCar(
              gCarSystemManager,
              *(_DWORD *)(v2 + 12),
              *(_DWORD *)(v2 + 16),
              *v3,
              *v12,
              (CarModel *)*(__int16 *)(v2 + 28));
      pCar = (void *)(pCarSystemManager_4 + 8);
      *(_DWORD *)(pCarSystemManager_4 + 8) = v13;
      gta2::SpriteS1_sub_4B9D50(
        v13->CarSprite,
        (int)v11->CarSprite,
        (SpriteS1 *)gAudioSourceParams,
        (int)gAudioSourceParams,
        unk_664E60.Index);
      LOBYTE(v7) = gta2::Car_sub_424630(v11, 8);
    }
    else
    {
      gta2::sub_41F990(a3, *(_WORD *)(v2 + 24));
      v14 = (S202 *)gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
      LOWORD(v14) = v14->field_0;
      v7 = (Car *)gta2::CarSystemManager_sub_428EC0(
                    gCarSystemManager,
                    *(S202 **)(v2 + 12),
                    *(S202 **)(v2 + 16),
                    v14,
                    (CarModel *)v10,
                    (CarModel *)v4);
      pCar = (void *)(pCarSystemManager_4 + 8);
      if ( v7 )
      {
        v7 = (Car *)v7->PlayerStats_;
        *(_DWORD *)pCar = v7;
      }
      else
      {
        *(_DWORD *)pCar = 0;
      }
    }
  }
  if ( *(_DWORD *)pCar )
  {
    if ( *(_WORD *)(v2 + 26) != 0xFFFF )
    {
      LOBYTE(v8) = *(_BYTE *)(v2 + 26);
      gta2::Car_SetRemap(*(Car **)pCar, v8);
    }
    gta2::Car_CarMakeDriveable1(*(Car **)pCar, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
    gta2::Car_SetLocksDoor2(*(Car **)pCar);
    gta2::Car_sub_424630(*(Car **)pCar, 8);
    LOBYTE(v7) = (unsigned __int8)gta2::sub_4BDAD0(*(int **)(*(_DWORD *)pCar + 80));
    v15 = *(_WORD *)(v2 + 2);
    if ( v15 >= 0x18Au && v15 <= 0x18Du )
    {
      LOBYTE(v7) = gta2::Gangs_FindGangByCarModel(gGangs, *(CarModel *)(*(_DWORD *)pCar + 132));
      LOBYTE(pCarSystemManager_4) = (_BYTE)v7;
      if ( (char)v7 > -1 )
      {
        v16 = gta2::Gangs_SelectGang(gGangs, (GANG)pCarSystemManager_4);
        gta2::Car_sub_41FBD0(*(Car **)pCar, v16->NextGang);
      }
    }
  }
  return (char)v7;
}


// 0x00477530: MissionScriptObjectData::sub_477530
// IDA: MissionScriptObjectData::sub_477530
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477530(struct MissionScriptObjectData *self, int a2)
{
  char result; // al

  gta2::MissionScriptObjectData_sub_477290(self, a2);
  gta2::Car_sub_424660(*(Car **)(a2 + 8), 9);
  gta2::Car_CarMakeDriveable1(*(Car **)(a2 + 8), SEARCHTYPE_AREA_PLAYER_ONLY);
  return result;
}


// 0x00477560: MissionScriptObjectData::sub_477560
// IDA: MissionScriptObjectData::sub_477560
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477560(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  int v2; // esi
  int *v3; // edi
  __int16 *v4; // eax
  struct Ped *v5; // eax
  int v6; // edi
  int *Sprite; // eax
  _BYTE a3[4]; // [esp+8h] [ebp-4h] BYREF
  int pCarSystemManager_4; // [esp+14h] [ebp+8h]

  v2 = pCarSystemManager;
  v3 = (int *)(pCarSystemManager + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(pCarSystemManager + 20), (Player *)&unk_664F58) )
    *v3 = *gta2::MapRelatedStruct_FindMaxZForLocation(
             gMapRelatedStruct,
             &pCarSystemManager,
             *(int **)(v2 + 12),
             *(S202 **)(v2 + 16));
  gta2::sub_41F990(a3, *(_WORD *)(v2 + 24));
  v4 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
  v5 = gta2::Character_SpawnPedAtPosition(
         gCharacter,
         *(_DWORD *)(v2 + 12),
         *(_DWORD *)(v2 + 16),
         *v3,
         *(_BYTE *)(v2 + 26),
         *v4);
  v6 = pCarSystemManager_4;
  *(_DWORD *)(pCarSystemManager_4 + 8) = v5;
  if ( v5 )
  {
    gta2::Ped_SetSearchType(v5, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
    gta2::Ped_SetCurrentOccupation(*(Ped **)(v6 + 8), (ALL_PED)*(__int16 *)(v2 + 28));
    *(_DWORD *)(*(_DWORD *)(v6 + 8) + 620) = 1;
    gta2::Ped_PedSetObjective(*(Ped **)(v6 + 8), 26, 9999);
    gta2::Ped_SetHealth(*(Ped **)(v6 + 8), 100);
    Sprite = (int *)gta2::Ped_GetSprite(*(Ped **)(v6 + 8));
    LOBYTE(v5) = (unsigned __int8)gta2::sub_4BDAD0(Sprite);
  }
  return (char)v5;
}


// 0x00477660: MissionScriptObjectData::sub_477660
// IDA: MissionScriptObjectData::sub_477660
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477660(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  int v2; // esi
  S103 *v3; // eax
  int v4; // edi
  int v5; // ebx
  __int16 v6; // ax
  __int16 v7; // ax
  __int16 *v8; // eax
  int v9; // eax
  MissionManager *started; // eax
  int pCarSystemManager_4; // [esp+14h] [ebp+8h] BYREF

  v2 = pCarSystemManager;
  v3 = gta2::S103_sub_449810(gS103, *(int **)(pCarSystemManager + 16), *(void **)(pCarSystemManager + 20));
  v4 = pCarSystemManager_4;
  v5 = (int)v3;
  *(_DWORD *)(pCarSystemManager_4 + 8) = v3;
  v6 = *(_WORD *)(v2 + 2);
  if ( v6 == 38 )
  {
    v7 = *(_WORD *)(v2 + 26);
    if ( v7 )
    {
      if ( v7 == 1 )
      {
        gta2::sub_41F990(&pCarSystemManager_4, *(_WORD *)(v2 + 36));
        gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, &pCarSystemManager_4);
        sub_4496E0(*(_DWORD *)(v2 + 8), *(int **)(v2 + 28), *(SpriteS1 **)(v2 + 32));
      }
    }
    else
    {
      gta2::sub_41F990(&pCarSystemManager_4, *(_WORD *)(v2 + 36));
      gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, &pCarSystemManager_4);
      sub_4495F0(*(_DWORD *)(v2 + 8), *(int **)(v2 + 28), *(SpriteS1 **)(v2 + 32));
    }
  }
  else if ( v6 == 37 )
  {
    gta2::sub_41F990(&pCarSystemManager_4, *(_WORD *)(v4 + 36));
    gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, &pCarSystemManager_4);
    sub_4495F0(v5, *(int **)(v4 + 28), *(SpriteS1 **)(v4 + 32));
    gta2::sub_41F990(&pCarSystemManager_4, *(_WORD *)(v4 + 38));
    gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, &pCarSystemManager_4);
    sub_4496E0(*(_DWORD *)(v4 + 8), *(int **)(v4 + 40), *(SpriteS1 **)(v4 + 44));
  }
  gta2::sub_41F990(&pCarSystemManager_4, *(_WORD *)(v2 + 24));
  v8 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, &pCarSystemManager_4);
  gta2::sub_4768E0(*(_DWORD **)(v4 + 8), *v8);
  v9 = *(_DWORD *)(v2 + 12);
  if ( v9 )
  {
    started = gta2::MissionManager_StartMission(gMissionManager, *(_DWORD *)(v2 + 12));
    LOBYTE(v9) = gta2::sub_476900(*(_DWORD **)(v4 + 8), started->arr_96[1]);
  }
  return v9;
}


// 0x004777e0: MissionScriptObjectData::sub_4777E0
// IDA: MissionScriptObjectData::sub_4777E0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4777E0(struct MissionScriptObjectData *self, int a2)
{
  int v2; // esi
  int *v3; // edi
  int v4; // ecx
  int *v5; // eax
  char result; // al
  int v7; // [esp+10h] [ebp+8h]

  v2 = a2;
  v3 = (int *)(a2 + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(a2 + 20), (Player *)&unk_664F58) )
    *v3 = *gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, &a2, *(int **)(v2 + 12), *(S202 **)(v2 + 16));
  HIWORD(v4) = unk_664566;
  LOWORD(v4) = unk_664530;
  v5 = gta2::Object_sub_485290(
         gObject,
         (S900 *)0x8B,
         *(_DWORD *)(v2 + 12),
         *(_DWORD *)(v2 + 16),
         *v3,
         v4,
         *(SpriteS1 **)(v2 + 24),
         *(SpriteS3 **)(v2 + 28),
         unk_664564);
  *(_DWORD *)(v7 + 8) = v5;
  gta2::sub_483C00((EventHandler *)v5, *(_BYTE *)(v2 + 32), *(_BYTE *)(v2 + 33));
  return result;
}


// 0x00477870: MissionScriptObjectData::sub_477870
// IDA: MissionScriptObjectData::sub_477870
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477870(struct MissionScriptObjectData *self, int pCarSystemManager)
{
  int v2; // esi
  struct Player *pPlayer; // edi
  __int16 *v4; // eax
  S108 *pS108; // eax
  unsigned __int8 v6; // cl
  _BYTE a3[4]; // [esp+8h] [ebp-4h] BYREF
  int pCarSystemManager_4; // [esp+14h] [ebp+8h]

  v2 = pCarSystemManager;
  pPlayer = (Player *)(pCarSystemManager + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(pCarSystemManager + 20), (Player *)&unk_664F58) )
    pPlayer->CurrentPlayer = (Player *)*gta2::MapRelatedStruct_FindMaxZForLocation(
                                          gMapRelatedStruct,
                                          &pCarSystemManager,
                                          *(int **)(v2 + 12),
                                          *(S202 **)(v2 + 16));
  gta2::sub_41F990(a3, *(_WORD *)(v2 + 24));
  v4 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&pCarSystemManager, a3);
  pS108 = gta2::S107_sub_45E330(
            gS107,
            *(_DWORD *)(v2 + 12),
            *(_DWORD *)(v2 + 16),
            pPlayer->CurrentPlayer,
            *v4,
            *(unsigned __int16 *)(v2 + 26),
            *(_WORD *)(v2 + 28),
            *(_WORD *)(v2 + 30));
  *(_DWORD *)(pCarSystemManager_4 + 8) = pS108;
  v6 = *(_BYTE *)(v2 + 32);
  if ( v6 )
    LOBYTE(pS108) = gta2::S108_sub_476920(pS108, v6);
  return (char)pS108;
}


// 0x00477920: MissionScriptObjectData::sub_477920
// IDA: MissionScriptObjectData::sub_477920
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477920(struct MissionScriptObjectData *self, int a2)
{
  int v2; // esi
  int *v3; // edi
  int v4; // ecx
  int *v5; // eax
  int v7; // [esp+10h] [ebp+8h]

  v2 = a2;
  v3 = (int *)(a2 + 20);
  if ( gta2::Player_IsCurrentPlayer((Player *)(a2 + 20), (Player *)&unk_664F58) )
    *v3 = *gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, &a2, *(int **)(v2 + 12), *(S202 **)(v2 + 16));
  HIWORD(v4) = unk_664566;
  LOWORD(v4) = unk_664530;
  v5 = gta2::Object_sub_485290(
         gObject,
         (S900 *)0x8D,
         *(_DWORD *)(v2 + 12),
         *(_DWORD *)(v2 + 16),
         *v3,
         v4,
         *(SpriteS1 **)(v2 + 24),
         *(SpriteS3 **)(v2 + 28),
         unk_664564);
  *(_DWORD *)(v7 + 8) = v5;
  return (char)v5;
}


// 0x004779a0: MissionScriptObjectData::sub_4779A0
// IDA: MissionScriptObjectData::sub_4779A0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4779A0(struct MissionScriptObjectData *self, int a2)
{
  MissionManager *v2; // esi
  int v3; // edx
  MissionManager *started; // ebx
  MissionManager *v5; // eax
  struct Ped *v6; // ecx
  MissionManager *v7; // edi
  int v8; // eax
  int v10; // [esp-8h] [ebp-14h]
  __int16 v11; // [esp-4h] [ebp-10h]
  __int16 *v12; // [esp+14h] [ebp+8h]

  v2 = gMissionManager;
  started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 16));
  v5 = gta2::MissionManager_StartMission(v2, *(_WORD *)(v3 + 18));
  v6 = (Ped *)started->arr_96[1];
  v7 = v5;
  if ( v6 )
  {
    v5 = (MissionManager *)v5->arr_96[1];
    if ( v5 )
    {
      v11 = *v12;
      v10 = v5->arr_96[26];
      v8 = gta2::Ped_sub_420B60(v6);
      gta2::MissionManager_sub_476280(v2, v8, v10, v11);
      gta2::sub_476360((void *)v7->arr_96[1]);
    }
  }
  return (char)v5;
}


// 0x00477ac0: MissionScriptObjectData::sub_477AC0
// IDA: MissionScriptObjectData::sub_477AC0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477AC0(struct MissionScriptObjectData *self, int a2)
{
  int v2; // esi
  MissionManager *started; // eax
  int v5; // [esp-14h] [ebp-24h]
  int v6; // [esp-14h] [ebp-24h]
  int v7; // [esp-10h] [ebp-20h]
  int v8; // [esp-10h] [ebp-20h]
  int v9; // [esp-Ch] [ebp-1Ch]
  int v10; // [esp-Ch] [ebp-1Ch]
  int v11; // [esp-8h] [ebp-18h]
  int v12; // [esp-8h] [ebp-18h]
  int v13; // [esp-4h] [ebp-14h]
  int v14; // [esp-4h] [ebp-14h]
  int v15; // [esp+4h] [ebp-Ch] BYREF
  int v16; // [esp+8h] [ebp-8h] BYREF
  int v17; // [esp+Ch] [ebp-4h] BYREF

  v2 = a2;
  started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 36));
  if ( started->arr_96[1] )
  {
    HIWORD(started) = 0;
    *(_BYTE *)(v2 + 39) = 1;
    LOWORD(started) = *(_WORD *)(v2 + 2);
    if ( (unsigned __int16)started == 214 )
    {
      v14 = *(_DWORD *)(v2 + 32);
      v12 = *(_DWORD *)(v2 + 28);
      v10 = *(_DWORD *)(v2 + 24);
      v8 = *(_DWORD *)(v2 + 20);
      v6 = *(_DWORD *)(v2 + 16);
      v16 = 2;
      v17 = 4;
      LOBYTE(started) = gta2::MissionObjective_sub_4C4F30(gMissionObjective, &v17, &v16, v2, v6, v8, v10, v12, v14);
      goto LABEL_6;
    }
    if ( started == (MissionManager *)434 )
    {
      v13 = *(_DWORD *)(v2 + 32);
      v11 = *(_DWORD *)(v2 + 28);
      v9 = *(_DWORD *)(v2 + 24);
      v7 = *(_DWORD *)(v2 + 20);
      v5 = *(_DWORD *)(v2 + 16);
      a2 = 2;
      v15 = 3;
      LOBYTE(started) = gta2::MissionObjective_sub_4C4F30(gMissionObjective, &v15, &a2, v2, v5, v7, v9, v11, v13);
LABEL_6:
      *(_BYTE *)(v2 + 38) = (_BYTE)started;
    }
  }
  return (char)started;
}


// 0x00477bd0: MissionScriptObjectData::sub_477BD0
// IDA: MissionScriptObjectData::sub_477BD0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477BD0(struct MissionScriptObjectData *self, int a2)
{
  int v2; // esi
  const char *v3; // ebp
  Gang *pGang; // edi
  int *v5; // ebx
  Gang *v6; // eax
  struct HudArrow *pHudArrow; // esi
  int v8; // edi
  void *v9; // ecx

  v2 = a2;
  v3 = (char *)gta2::MissionManager_sub_474F00(gMissionManager, *(_WORD *)(a2 + 8)) + 9;
  pGang = gta2::Gangs_GetGangByName(gGangs, v3);
  gta2::Gang_SetRemap(pGang, *(_BYTE *)(v2 + 10));
  gta2::Gang_SetWeapon1(pGang, (Weapon *)*(unsigned __int8 *)(v2 + 11));
  gta2::Gang_SetWeapon2(pGang, (Weapon *)*(unsigned __int8 *)(v2 + 12));
  gta2::Gang_SetWeapon3(pGang, *(unsigned __int8 *)(v2 + 13));
  gta2::Gang_SetGang(pGang, *(GANG *)(v2 + 14));
  gta2::Gang_SetTypeCar(pGang, *(unsigned __int16 *)(v2 + 28));
  gta2::Gang_SetCar_remap(pGang, *(_BYTE *)(v2 + 30));
  v5 = (int *)(v2 + 24);
  if ( gta2::Player_IsCurrentPlayer((Player *)(v2 + 24), (Player *)&unk_664F58) )
    *v5 = *gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, &a2, *(int **)(v2 + 16), *(S202 **)(v2 + 20));
  gta2::Gang_SetXYZ(pGang, *(_DWORD *)(v2 + 16), *(_DWORD *)(v2 + 20), *v5);
  gta2::Gang_SetKillChar(pGang, *(_BYTE *)(v2 + 15));
  gta2::Gangs_sub_45DF30(gGangs, (int)pGang, gMissionManager->Gang_);
  ++gMissionManager->Gang_;
  v6 = gta2::Gangs_GetGangByName(gGangs, v3);
  if ( *(_BYTE *)(v2 + 15) )
  {
    a2 = (int)v6;
    pHudArrow = gta2::HudArrow_GetHudArrow(&gHud->HudArrow_);
    gta2::HudArrow_SetArrowType(pHudArrow, 4u);
    v8 = a2;
    gta2::sub_4C7030(v9, (Gang *)a2);
    gta2::HudArrow_SetSpriteID(pHudArrow, *(unsigned __int8 *)(v8 + 312));
    gta2::HudArrow_Init(pHudArrow, 0);
    LOBYTE(v6) = gta2::HudArrow_sub_4CA650(pHudArrow);
  }
  return (char)v6;
}


// 0x00477d20: MissionScriptObjectData::sub_477D20
// IDA: MissionScriptObjectData::sub_477D20
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477D20(struct MissionScriptObjectData *self, int a2)
{
  int *v2; // edi
  BOOL IsCurrentPlayer; // eax
  int v4; // eax
  SpriteS1 *v5; // ecx
  void *v6; // eax
  S202 *v7; // edx

  v2 = (int *)(a2 + 32);
  IsCurrentPlayer = gta2::Player_IsCurrentPlayer((Player *)(a2 + 32), (Player *)&gAudioSourceParams);
  if ( *(_WORD *)(a2 + 2) == 375 )
  {
    if ( IsCurrentPlayer && (v4 = gta2::Player_IsCurrentPlayer((Player *)(a2 + 36), (Player *)&gAudioSourceParams)) != 0 )
    {
      LOBYTE(v4) = *(_BYTE *)(a2 + 14);
      LOBYTE(v5) = *(_BYTE *)(a2 + 13);
      v6 = gta2::Door_sub_44DB00(
             gDoor,
             *(_BYTE *)(a2 + 16),
             (SpriteS1 *)*(unsigned __int8 *)(a2 + 12),
             v5,
             v4,
             *(unsigned __int8 *)(a2 + 15),
             *(_BYTE *)(a2 + 40),
             *(_BYTE *)(a2 + 41));
    }
    else
    {
      v6 = gta2::Door_sub_44D670(
             gDoor,
             *(_BYTE *)(a2 + 16),
             *(_BYTE *)(a2 + 12),
             *(_BYTE *)(a2 + 13),
             *(_BYTE *)(a2 + 14),
             *(unsigned __int8 *)(a2 + 15),
             *(_DWORD *)(a2 + 20),
             *(_DWORD *)(a2 + 24),
             *(_DWORD *)(a2 + 28),
             *v2,
             *(_DWORD *)(a2 + 36),
             *(_BYTE *)(a2 + 40),
             *(_BYTE *)(a2 + 41));
    }
  }
  else if ( IsCurrentPlayer && gta2::Player_IsCurrentPlayer((Player *)(a2 + 36), (Player *)&gAudioSourceParams) )
  {
    LOBYTE(v7) = *(_BYTE *)(a2 + 40);
    v6 = gta2::Door_sub_44D430(
           gDoor,
           *(_BYTE *)(a2 + 16),
           *(_BYTE *)(a2 + 12),
           *(_BYTE *)(a2 + 13),
           *(_BYTE *)(a2 + 14),
           *(unsigned __int8 *)(a2 + 15),
           v7);
  }
  else
  {
    v6 = gta2::Door_sub_44D6F0(
           gDoor,
           *(_BYTE *)(a2 + 16),
           *(_BYTE *)(a2 + 12),
           *(_BYTE *)(a2 + 13),
           *(_BYTE *)(a2 + 14),
           *(unsigned __int8 *)(a2 + 15),
           *(_DWORD *)(a2 + 20),
           *(_DWORD *)(a2 + 24),
           *(_DWORD *)(a2 + 28),
           *v2,
           *(_DWORD *)(a2 + 36),
           *(_BYTE *)(a2 + 40),
           *(_BYTE *)(a2 + 41));
  }
  *(_DWORD *)(a2 + 8) = v6;
  switch ( *(_BYTE *)(a2 + 17) )
  {
    case 0:
      gta2::sub_476990(*(void **)(a2 + 8), 1);
      break;
    case 1:
      gta2::sub_476990(*(void **)(a2 + 8), 2);
      break;
    case 2:
      gta2::sub_476990(*(void **)(a2 + 8), 3);
      break;
    case 4:
      gta2::sub_476990(*(void **)(a2 + 8), 5);
      break;
    case 5:
      gta2::sub_476990(*(void **)(a2 + 8), 0);
      break;
    case 6:
      gta2::sub_476990(*(void **)(a2 + 8), 6);
      break;
    default:
      break;
  }
  switch ( *(_BYTE *)(a2 + 18) )
  {
    case 0:
      gta2::sub_476A10(*(void **)(a2 + 8), 3);
      break;
    case 1:
      gta2::sub_476A10(*(void **)(a2 + 8), 1);
      break;
    case 2:
      gta2::sub_476A10(*(void **)(a2 + 8), 2);
      break;
    case 3:
      gta2::sub_476A10(*(void **)(a2 + 8), 4);
      break;
    default:
      return gta2::sub_476A20(*(_WORD **)(a2 + 8), *(unsigned __int8 *)(a2 + 19));
  }
  return gta2::sub_476A20(*(_WORD **)(a2 + 8), *(unsigned __int8 *)(a2 + 19));
}


// 0x00477ee0: MissionScriptObjectData::sub_477EE0
// IDA: MissionScriptObjectData::sub_477EE0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_477EE0(struct MissionScriptObjectData *self, int a2)
{
  int *v2; // edi
  BOOL IsCurrentPlayer; // eax
  int v4; // eax
  SpriteS1 *v5; // ecx
  void *v6; // eax
  S202 *v7; // edx
  MissionManager *started; // edi
  int v9; // eax
  MissionManager *v10; // edi
  int v11; // eax

  v2 = (int *)(a2 + 32);
  IsCurrentPlayer = gta2::Player_IsCurrentPlayer((Player *)(a2 + 32), (Player *)&gAudioSourceParams);
  if ( *(_WORD *)(a2 + 2) == 376 )
  {
    if ( IsCurrentPlayer && (v4 = gta2::Player_IsCurrentPlayer((Player *)(a2 + 36), (Player *)&gAudioSourceParams)) != 0 )
    {
      LOBYTE(v4) = *(_BYTE *)(a2 + 14);
      LOBYTE(v5) = *(_BYTE *)(a2 + 13);
      v6 = gta2::Door_sub_44DB00(
             gDoor,
             *(_BYTE *)(a2 + 16),
             (SpriteS1 *)*(unsigned __int8 *)(a2 + 12),
             v5,
             v4,
             *(unsigned __int8 *)(a2 + 15),
             *(_BYTE *)(a2 + 40),
             *(_BYTE *)(a2 + 41));
    }
    else
    {
      v6 = gta2::Door_sub_44D670(
             gDoor,
             *(_BYTE *)(a2 + 16),
             *(_BYTE *)(a2 + 12),
             *(_BYTE *)(a2 + 13),
             *(_BYTE *)(a2 + 14),
             *(unsigned __int8 *)(a2 + 15),
             *(_DWORD *)(a2 + 20),
             *(_DWORD *)(a2 + 24),
             *(_DWORD *)(a2 + 28),
             *v2,
             *(_DWORD *)(a2 + 36),
             *(_BYTE *)(a2 + 40),
             *(_BYTE *)(a2 + 41));
    }
  }
  else if ( IsCurrentPlayer && gta2::Player_IsCurrentPlayer((Player *)(a2 + 36), (Player *)&gAudioSourceParams) )
  {
    LOBYTE(v7) = *(_BYTE *)(a2 + 40);
    v6 = gta2::Door_sub_44D430(
           gDoor,
           *(_BYTE *)(a2 + 16),
           *(_BYTE *)(a2 + 12),
           *(_BYTE *)(a2 + 13),
           *(_BYTE *)(a2 + 14),
           *(unsigned __int8 *)(a2 + 15),
           v7);
  }
  else
  {
    v6 = gta2::Door_sub_44D6F0(
           gDoor,
           *(_BYTE *)(a2 + 16),
           *(_BYTE *)(a2 + 12),
           *(_BYTE *)(a2 + 13),
           *(_BYTE *)(a2 + 14),
           *(unsigned __int8 *)(a2 + 15),
           *(_DWORD *)(a2 + 20),
           *(_DWORD *)(a2 + 24),
           *(_DWORD *)(a2 + 28),
           *v2,
           *(_DWORD *)(a2 + 36),
           *(_BYTE *)(a2 + 40),
           *(_BYTE *)(a2 + 41));
  }
  *(_DWORD *)(a2 + 8) = v6;
  switch ( *(_BYTE *)(a2 + 17) )
  {
    case 0:
      gta2::sub_476990(*(void **)(a2 + 8), 1);
      break;
    case 1:
      gta2::sub_476990(*(void **)(a2 + 8), 2);
      break;
    case 2:
    case 6:
      started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 42));
      v9 = started->arr_96[1];
      if ( v9 )
      {
        gta2::sub_4769E0(*(void **)(a2 + 8), 3, v9);
        gta2::sub_476A00(*(void **)(a2 + 8), *(_DWORD *)(started->arr_96[1] + 108));
      }
      break;
    case 3:
      gta2::sub_4769A0(*(void **)(a2 + 8), 4, *(unsigned __int16 *)(a2 + 42));
      break;
    case 4:
      v10 = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 42));
      v11 = v10->arr_96[1];
      if ( v11 )
      {
        gta2::sub_4769C0(*(void **)(a2 + 8), 5, v11);
        gta2::sub_476A00(*(void **)(a2 + 8), *(_DWORD *)(v10->arr_96[1] + 512));
      }
      break;
    case 5:
      gta2::sub_476990(*(void **)(a2 + 8), 0);
      break;
    default:
      break;
  }
  switch ( *(_BYTE *)(a2 + 18) )
  {
    case 0:
      gta2::sub_476A10(*(void **)(a2 + 8), 3);
      break;
    case 1:
      gta2::sub_476A10(*(void **)(a2 + 8), 1);
      break;
    case 2:
      gta2::sub_476A10(*(void **)(a2 + 8), 2);
      break;
    case 3:
      gta2::sub_476A10(*(void **)(a2 + 8), 4);
      break;
    default:
      return gta2::sub_476A20(*(_WORD **)(a2 + 8), *(unsigned __int8 *)(a2 + 19));
  }
  return gta2::sub_476A20(*(_WORD **)(a2 + 8), *(unsigned __int8 *)(a2 + 19));
}


// 0x00478120: MissionScriptObjectData::sub_478120
// IDA: MissionScriptObjectData::sub_478120
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_478120(struct MissionScriptObjectData *self, int a2)
{
  char result; // al
  MissionManager *started; // eax
  _DWORD *v4; // ecx
  int v5; // edx
  __int16 v6; // dx
  int v7; // [esp+4h] [ebp+4h]

  started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 10));
  v6 = *(_WORD *)(v5 + 2);
  v7 = (int)&started->arr_96[1];
  if ( v6 == 429 )
  {
    result = (_BYTE)started + 8;
    v4[210] = v7;
  }
  else if ( v6 == 430 )
  {
    result = (_BYTE)started + 8;
    v4[211] = v7;
  }
  else
  {
    result = (_BYTE)started + 8;
    if ( v6 == 431 )
      v4[212] = v7;
    else
      v4[209] = v7;
  }
  return result;
}


// 0x00478170: MissionScriptObjectData::sub_478170
// IDA: MissionScriptObjectData::sub_478170
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_478170(struct MissionScriptObjectData *self, int a2)
{
  MissionManager *started; // eax
  _DWORD *v3; // ecx

  started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 8));
  switch ( *(_WORD *)(a2 + 2) )
  {
    case 0x15A:
      started = (MissionManager *)((char *)started + 8);
      v3[202] = started;
      break;
    case 0x15B:
      started = (MissionManager *)((char *)started + 8);
      v3[203] = started;
      break;
    case 0x15C:
      started = (MissionManager *)((char *)started + 8);
      v3[204] = started;
      break;
    case 0x15D:
      started = (MissionManager *)((char *)started + 8);
      v3[205] = started;
      break;
    case 0x185:
      started = (MissionManager *)((char *)started + 8);
      v3[206] = started;
      break;
    case 0x186:
      started = (MissionManager *)((char *)started + 8);
      v3[207] = started;
      break;
    default:
      return (char)started;
  }
  return (char)started;
}


// 0x00478450: MissionScriptObjectData::sub_478450
// IDA: MissionScriptObjectData::sub_478450
// Ghidra: ---
unsigned __int16 gta2::MissionScriptObjectData_sub_478450(struct MissionScriptObjectData *self, unsigned __int16 a2)
{
  MissionManager *started; // esi
  unsigned __int16 result; // ax

  started = gta2::MissionManager_StartMission(gMissionManager, a2);
  result = started->arr_96[1];
  if ( result != 0xFFFD && result != 0xFFFC )
  {
    result = gta2::sub_41D980(&gGame->PlayerMain->field_47C, result);
    if ( result == 0xFFFD || result == 0xFFFC )
      started->arr_96[1] = (__int16)result;
  }
  return result;
}


// 0x004784a0: MissionScriptObjectData::sub_4784A0
// IDA: MissionScriptObjectData::sub_4784A0
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_4784A0(struct MissionScriptObjectData *self, int a2)
{
  MissionManager *started; // eax
  __int16 v4; // [esp-4h] [ebp-4h]

  v4 = *(_WORD *)a2;
  started = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 8));
  return gta2::sub_476910((_WORD *)started->arr_96[1], v4);
}


// 0x00478610: MissionScriptObjectData::sub_478610
// IDA: MissionScriptObjectData::sub_478610
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_478610(struct MissionScriptObjectData *self)
{
  Viewport *v2; // eax
  Viewport *pS34; // edx

  v2 = gta2::S29_sub_474FD0(self->S29_);
  if ( v2 )
  {
    gta2::MissionScriptObjectData_sub_476E80(self, v2->Data2);
    self->field_8 = pS34->Data1;
    gta2::S34_sub_476E00(pS34);
  }
  else
  {
    gta2::MissionScriptObjectData_sub_4751E0(self);
  }
}


// 0x00479050: MissionScriptObjectData::sub_479050
// IDA: MissionScriptObjectData::sub_479050
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_479050(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  int v2; // edi
  MissionManager *started; // eax
  MissionScriptObjectData *v4; // edx

  v1 = dword_6644CC;
  v2 = SHIWORD(dword_6644CC->arr_96[1]);
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v4->field_8 = *(__int16 *)(started->arr_96[1] + 116) >= 320 * v2;
  gta2::MissionScriptObjectData_sub_476E50(v4, v1);
}


// 0x00479850: MissionScriptObjectData::sub_479850
// IDA: MissionScriptObjectData::sub_479850
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_479850(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  MissionManager *v2; // ebx
  struct Player *v3; // ebp
  MissionManager *started; // esi
  int *MaxZForLocation; // eax
  Car *pCar; // esi
  Weapon *pWeapon; // ebx
  unsigned __int8 v8; // al
  _DWORD *v9; // eax
  struct Player *v10; // eax
  unsigned __int8 v11; // al
  void *v12; // eax
  unsigned __int8 v13; // al
  _DWORD *v14; // eax
  struct Player *v15; // eax
  unsigned __int8 v16; // al
  void *v17; // eax
  Weapon *v18; // eax
  char v19; // bl
  _DWORD *v20; // [esp-4h] [ebp-24h]
  _DWORD *v21; // [esp-4h] [ebp-24h]
  MissionManager *v23; // [esp+14h] [ebp-Ch]
  int v24; // [esp+18h] [ebp-8h] BYREF
  int a2; // [esp+1Ch] [ebp-4h] BYREF

  v1 = dword_6644CC;
  v2 = dword_6644CC;
  v23 = dword_6644CC;
  v3 = (Player *)&dword_6644CC->arr_96[4];
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  if ( gta2::Player_IsCurrentPlayer(v3, (Player *)&unk_664F58) )
  {
    MaxZForLocation = gta2::MapRelatedStruct_FindMaxZForLocation(
                        gMapRelatedStruct,
                        &v24,
                        (int *)v1->arr_96[2],
                        (S202 *)v1->arr_96[3]);
    v1 = dword_6644CC;
    v3->CurrentPlayer = (Player *)*MaxZForLocation;
  }
  pCar = (Car *)started->arr_96[1];
  if ( !pCar )
    goto LABEL_10;
  pWeapon = (Weapon *)&v2->arr_96[2];
  v8 = gta2::Weapon_sub_41C1E0(pWeapon);
  gta2::S202_sub_40CE30((S202 *)&v24, v8);
  v20 = v9;
  gta2::Car_GetX(pCar, &a2);
  if ( !gta2::Player_sub_40CE70(v10, v20) )
    goto LABEL_10;
  v11 = gta2::Weapon_sub_41C1E0(pWeapon);
  gta2::bitShiftLeft1(&a2, v11 + 1);
  gta2::Car_GetX(pCar, &v24);
  if ( !gta2::sub_4037E0(v12) )
    goto LABEL_10;
  v13 = gta2::Weapon_sub_41C1E0((Weapon *)&v23->arr_96[3]);
  gta2::S202_sub_40CE30((S202 *)&a2, v13);
  v21 = v14;
  gta2::Car_GetY(pCar, &v24);
  if ( !gta2::Player_sub_40CE70(v15, v21) )
    goto LABEL_10;
  v16 = gta2::Weapon_sub_41C1E0((Weapon *)&v23->arr_96[3]);
  gta2::bitShiftLeft1(&a2, v16 + 1);
  gta2::Car_GetY(pCar, &v24);
  if ( gta2::sub_4037E0(v17)
    && (gta2::Car_GetZ(pCar, &a2), v19 = gta2::Weapon_sub_41C1E0(v18), v19 == (unsigned __int8)gta2::Weapon_sub_41C1E0((Weapon *)v3)) )
  {
    self->field_8 = 1;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
  else
  {
LABEL_10:
    self->field_8 = 0;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
}


// 0x00479b70: MissionScriptObjectData::sub_479B70
// IDA: MissionScriptObjectData::sub_479B70
// Ghidra: FUN_00479b70
void gta2::MissionScriptObjectData_sub_479B70(void *self)
{
  struct Ped *this_00;
  int iVar1;
  int iVar2;
  byte bVar3;
  void *pvVar4;
  int iVar5;
  MissionManager *this_01;
  int extraout_EDX;
  
  iVar2 = _DAT_006644cc;
  gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  pvVar4 = gta2::MissionManager_StartMission(this_01,*(ushort *)(iVar2 + 10));
  this_00 = *(Ped **)(extraout_EDX + 8);
  if ((this_00 != NULL) && (iVar1 = *(int *)((int)pvVar4 + 8), iVar1 != 0)) {
    bVar3 = gta2::Ped_IsInCar(this_00);
    if (bVar3 != 0) {
      iVar5 = gta2::Ped_GetCarPlayers(this_00);
      if (iVar5 == iVar1) {
        *(undefined4 *)((int)self + 8) = 1;
        gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar2);
        return;
      }
    }
  }
  *(undefined4 *)((int)self + 8) = 0;
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar2);
  return;
}


// 0x00479cc0: MissionScriptObjectData::sub_479CC0
// IDA: MissionScriptObjectData::sub_479CC0
// Ghidra: FUN_00479cc0
void gta2::MissionScriptObjectData_sub_479CC0(void *self)
{
  struct Ped *this_00;
  byte bVar1;
  void *pvVar2;
  int iVar3;
  
  iVar3 = _DAT_006644cc;
  pvVar2 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  this_00 = *(Ped **)((int)pvVar2 + 8);
  if (this_00 != NULL) {
    bVar1 = gta2::Ped_IsPlayerControlled(this_00);
    if (bVar1 != 0) {
      if (*(short *)(iVar3 + 2) == 0x8d) {
        gta2::Player_AddMoney(this_00->isPlayer,*(int *)(iVar3 + 0xc));
        gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,_DAT_006644cc);
        return;
      }
      gta2::Player_DecreaseInMoney(this_00->isPlayer,*(int *)(iVar3 + 0xc));
      iVar3 = _DAT_006644cc;
    }
  }
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar3);
  return;
}


// 0x00479f10: MissionScriptObjectData::sub_479F10
// IDA: MissionScriptObjectData::sub_479F10
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_479F10(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  MissionManager *started; // eax
  struct Ped *v4; // esi
  int *v5; // eax
  SpriteS1 *v6; // eax
  int *v7; // eax
  int v8; // eax
  SpriteS1 *v9; // eax
  int *v10; // eax
  int v11; // eax
  char v12; // bl
  struct Ped *v13; // esi
  struct Player *v14; // eax
  struct Player *v15; // eax
  struct Ped *v16; // esi
  struct Player *v17; // eax
  struct Ped *pPed; // esi
  MissionManager *v19; // [esp+Ch] [ebp-1Ch]
  int a3; // [esp+10h] [ebp-18h] BYREF
  int v21; // [esp+14h] [ebp-14h] BYREF
  int a2; // [esp+18h] [ebp-10h] BYREF
  int v23; // [esp+1Ch] [ebp-Ch] BYREF
  int X; // [esp+20h] [ebp-8h] BYREF
  int v25; // [esp+24h] [ebp-4h] BYREF

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v4 = (Ped *)started->arr_96[1];
  v19 = started;
  if ( v4 )
  {
    v21 = *(_DWORD *)gta2::Ped_GetXCoordinate(v4, (int)&X);
    gta2::Ped_GetYCoordinate(v4, &X);
    v23 = *v5;
    X = *(_DWORD *)gta2::Ped_GetPositionZ(v4, (int)&X);
    a3 = *(_DWORD *)gta2::sub_401B90(&v1->arr_96[5], &a2, &unk_664DC4);
    a2 = *(_DWORD *)gta2::sub_401B90(&v1->arr_96[6], &a2, &unk_664DC4);
    self->field_8 = 0;
    v6 = gta2::Player_sub_401B40((Player *)&v1->arr_96[2], (S202 *)&v25, (int)&a3);
    if ( gta2::Player_sub_40CE70((Player *)&v21, v6) )
    {
      v7 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[2], (SpriteS1 *)&v25, (PublicTransport *)&a3);
      LOBYTE(v8) = gta2::Player_CheckCondition((Player *)&v21, v7);
      if ( v8 )
      {
        v9 = gta2::Player_sub_401B40((Player *)&v1->arr_96[3], (S202 *)&v25, (int)&a2);
        if ( gta2::Player_sub_40CE70((Player *)&v23, v9) )
        {
          v10 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[3], (SpriteS1 *)&v25, (PublicTransport *)&a2);
          LOBYTE(v11) = gta2::Player_CheckCondition((Player *)&v23, v10);
          if ( v11 )
          {
            v12 = gta2::Weapon_sub_41C1E0((Weapon *)&v1->arr_96[4]);
            if ( (unsigned __int8)gta2::Weapon_sub_41C1E0((Weapon *)&X) == v12 )
            {
              switch ( v1->field_2 )
              {
                case 0x91u:
                  goto LABEL_9;
                case 0x92u:
                  if ( !gta2::Ped_GetGameObject((Ped *)v19->arr_96[1]) )
                    break;
                  goto LABEL_9;
                case 0x93u:
                  if ( !gta2::Ped_IsInCar((Ped *)v19->arr_96[1]) )
                    break;
                  goto LABEL_9;
                case 0x94u:
                  v13 = (Ped *)v19->arr_96[1];
                  if ( gta2::Ped_GetGameObject(v13) )
                  {
                    v14 = (Player *)gta2::Ped_sub_433C20(v13, &v25);
                    if ( gta2::Player_IsCurrentPlayer(v14, (Player *)&gAudioSourceParams) )
                      goto LABEL_9;
                  }
                  if ( !gta2::Ped_IsInCar(v13) )
                    break;
                  v15 = gta2::Ped_sub_436160(v13, &X);
LABEL_21:
                  if ( gta2::Player_IsCurrentPlayer(v15, (Player *)&gAudioSourceParams) )
                    self->field_8 = 1;
LABEL_24:
                  v1 = dword_6644CC;
                  break;
                case 0x95u:
                  v16 = (Ped *)v19->arr_96[1];
                  if ( !gta2::Ped_GetGameObject(v16) )
                    break;
                  v17 = (Player *)gta2::Ped_sub_433C20(v16, &v23);
                  if ( !gta2::Player_IsCurrentPlayer(v17, (Player *)&gAudioSourceParams) )
                    break;
LABEL_9:
                  self->field_8 = 1;
                  gta2::MissionScriptObjectData_sub_476E50(self, v1);
                  return;
                case 0x96u:
                  pPed = (Ped *)v19->arr_96[1];
                  if ( !gta2::Ped_IsInCar(pPed) )
                    break;
                  v15 = gta2::Ped_sub_436160(pPed, &a2);
                  goto LABEL_21;
                default:
                  gta2::debug_log(0x3EEu, "miss2.cpp", 4622);
                  goto LABEL_24;
              }
            }
          }
        }
      }
    }
  }
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047a1e0: MissionScriptObjectData::sub_47A1E0
// IDA: MissionScriptObjectData::sub_47A1E0
// Ghidra: FUN_0047a1e0
void gta2::MissionScriptObjectData_sub_47A1E0(void *self)
{
  int iVar1;
  void *pvVar2;
  void *pvVar3;
  
  iVar1 = _DAT_006644cc;
  pvVar2 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  FUN_004751f0(self,iVar1,pvVar2);
  switch(*(undefined2 *)(iVar1 + 10)) {
  case 2:
  case 3:
  case 4:
  case 5:
  case 6:
  case 0x10:
  case 0x13:
  case 0x14:
  case 0x17:
    pvVar3 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(iVar1 + 0xc));
    gta2::Ped_SetDriverPed(*(Ped **)((int)pvVar2 + 8),*(undefined4 *)((int)pvVar3 + 8)
                    );
    break;
  case 0x15:
  case 0x1b:
  case 0x24:
  case 0x37:
  case 0x3b:
    pvVar3 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(iVar1 + 0xc));
    gta2::Ped_SetCurrentCar(*(Ped **)((int)pvVar2 + 8),*(undefined4 *)((int)pvVar3 + 8));
    break;
  case 0x23:
    pvVar3 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(iVar1 + 0xc));
    gta2::Ped_SetCurrentCar(*(Ped **)((int)pvVar2 + 8),*(undefined4 *)((int)pvVar3 + 8));
    if (*(short *)(iVar1 + 0xe) == 1) {
      gta2::Ped_SetTargetCarDoor(*(Ped **)((int)pvVar2 + 8),1);
    }
    else {
      gta2::Ped_SetTargetCarDoor(*(Ped **)((int)pvVar2 + 8),0);
    }
    break;
  case 0x39:
  case 0x3a:
    pvVar3 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(iVar1 + 0xc));
    *(undefined4 *)(*(int *)((int)pvVar2 + 8) + 0x1a0) =
         *(undefined4 *)((int)pvVar3 + 8);
  }
  iVar1 = _DAT_006644cc;
  *(uint *)(*(int *)((int)pvVar2 + 8) + 0x21c) =
       *(uint *)(*(int *)((int)pvVar2 + 8) + 0x21c) & 0xfffffbff;
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
  return;
}


// 0x0047a330: MissionScriptObjectData::sub_47A330
// IDA: MissionScriptObjectData::sub_47A330
// Ghidra: FUN_0047a330
void gta2::MissionScriptObjectData_sub_47A330(void *self)
{
  int iVar1;
  void *pvVar2;
  
  iVar1 = _DAT_006644cc;
  pvVar2 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  FUN_004751f0(self,iVar1,pvVar2);
  if (*(int *)((int)pvVar2 + 8) != 0) {
    *(undefined4 *)(*(int *)((int)pvVar2 + 8) + 0x1dc) =
         *(undefined4 *)(iVar1 + 0xc);
    *(undefined4 *)(*(int *)((int)pvVar2 + 8) + 0x1e0) =
         *(undefined4 *)(iVar1 + 0x10);
    *(undefined4 *)(*(int *)((int)pvVar2 + 8) + 0x1e4) =
         *(undefined4 *)(iVar1 + 0x14);
    *(uint *)(*(int *)((int)pvVar2 + 8) + 0x21c) =
         *(uint *)(*(int *)((int)pvVar2 + 8) + 0x21c) & 0xfffffbff;
  }
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,_DAT_006644cc);
  return;
}


// 0x0047a3b0: MissionScriptObjectData::sub_47A3B0
// IDA: MissionScriptObjectData::sub_47A3B0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47A3B0(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  MissionManager *started; // esi
  MissionManager *v4; // eax
  struct Ped *v5; // edx
  int v6; // esi
  int v7; // eax
  __int16 v8; // [esp+Eh] [ebp-6h] BYREF
  _BYTE a3[4]; // [esp+10h] [ebp-4h] BYREF

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  gta2::MissionScriptObjectData_sub_4751F0(self, v1, started);
  if ( started->arr_96[1] )
  {
    v4 = gta2::MissionManager_StartMission(gMissionManager, v1->arr_96[2]);
    gta2::Ped_SetCurrentCar(v5, (Car *)v4->arr_96[1]);
    gta2::sub_41F990(a3, HIWORD(v1->arr_96[2]));
    *(_WORD *)(started->arr_96[1] + 306) = *gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&v8, a3);
    *(_DWORD *)(started->arr_96[1] + 508) = v1->arr_96[3];
    v6 = started->arr_96[1];
    v7 = *(_DWORD *)(v6 + 540);
    BYTE1(v7) &= ~4u;
    *(_DWORD *)(v6 + 540) = v7;
  }
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047a620: MissionScriptObjectData::sub_47A620
// IDA: MissionScriptObjectData::sub_47A620
// Ghidra: FUN_0047a620
void gta2::MissionScriptObjectData_sub_47A620(void *self)
{
  int iVar1;
  byte bVar2;
  void *pvVar3;
  undefined4 uVar4;
  int iVar5;
  uint uVar6;
  
  iVar5 = _DAT_006644cc;
  pvVar3 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  bVar2 = FUN_00475010(self,(uint)*(ushort *)((int)pvVar3 + 2));
  switch(bVar2) {
  case 1:
    if (*(int *)((int)pvVar3 + 8) == 0) {
      gta2::DebugLog(0x44f,"miss2.cpp",0x1383);
      iVar5 = _DAT_006644cc;
    }
    if (*(short *)(iVar5 + 2) == 0xa0) {
      uVar6 = 1;
      pvVar3 = (void *)gta2::Ped_GetSprite(*(Ped **)((int)pvVar3 + 8));
    }
    else {
      uVar6 = 0;
      pvVar3 = (void *)gta2::Ped_GetSprite(*(Ped **)((int)pvVar3 + 8));
    }
    break;
  case 2:
    if (*(int *)((int)pvVar3 + 8) == 0) {
      gta2::DebugLog(0x44e,"miss2.cpp",0x1376);
      iVar5 = _DAT_006644cc;
    }
    iVar1 = *(int *)((int)pvVar3 + 8);
    if (*(int *)(iVar1 + 0x88) == 6) goto switchD_0047a65a_caseD_4;
    if (*(short *)(iVar5 + 2) == 0xa0) {
      pvVar3 = *(void **)(iVar1 + 0x50);
      uVar6 = 1;
    }
    else {
      pvVar3 = *(void **)(iVar1 + 0x50);
      uVar6 = 0;
    }
    break;
  case 3:
    if (*(int *)((int)pvVar3 + 8) == 0) {
      gta2::DebugLog(0x450,"miss2.cpp",0x138e);
      iVar5 = _DAT_006644cc;
    }
    if (*(short *)(iVar5 + 2) == 0xa0) {
      uVar6 = 1;
      pvVar3 = *(void **)(*(int *)((int)pvVar3 + 8) + 4);
    }
    else {
      uVar6 = 0;
      pvVar3 = *(void **)(*(int *)((int)pvVar3 + 8) + 4);
    }
    break;
  case 4:
    if (*(int *)((int)pvVar3 + 8) == 0) {
      gta2::DebugLog(0x454,"miss2.cpp",0x1399);
      iVar5 = _DAT_006644cc;
    }
    uVar6 = (uint)(*(short *)(iVar5 + 2) == 0xa0);
    pvVar3 = (void *)FUN_00411a00();
    break;
  default:
    goto switchD_0047a65a_caseD_4;
  }
  uVar4 = FUN_0045bb50(gGame,pvVar3,uVar6);
  iVar5 = _DAT_006644cc;
  if ((char)uVar4 != '\0') {
    *(undefined4 *)((int)self + 8) = 1;
    gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar5);
    return;
  }
switchD_0047a65a_caseD_4:
  *(undefined4 *)((int)self + 8) = 0;
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar5);
  return;
}


// 0x0047a860: MissionScriptObjectData::sub_47A860
// IDA: MissionScriptObjectData::sub_47A860
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47A860(struct MissionScriptObjectData *self, unsigned __int16 a2)
{
  MissionManager *started; // eax

  started = gta2::MissionManager_StartMission(gMissionManager, a2);
  switch ( started->field_2 )
  {
    case 0xD3u:
      gta2::MissionScriptObjectData_sub_4779A0(self, (int)started);
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
    case 0xD4u:
      if ( BYTE2(started->arr_96[4]) )
        gta2::S25_sub_4768C0(gMissionObjective, BYTE1(started->arr_96[4]), 1);
      else
        gta2::MissionScriptObjectData_sub_477A00(self, (int)started);
      goto LABEL_10;
    case 0xD5u:
      gta2::MissionScriptObjectData_sub_477B70(self, (int)started);
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
    case 0xD6u:
    case 0x1B2u:
      if ( HIBYTE(started->arr_96[8]) )
      {
        gta2::S25_sub_4768C0(gMissionObjective, BYTE2(started->arr_96[8]), 1);
        gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      }
      else
      {
        gta2::MissionScriptObjectData_sub_477AC0(self, (int)started);
LABEL_10:
        gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      }
      return;
    default:
      goto LABEL_10;
  }
}


// 0x0047acc0: MissionScriptObjectData::sub_47ACC0
// IDA: MissionScriptObjectData::sub_47ACC0
// Ghidra: FUN_0047acc0
void gta2::MissionScriptObjectData_sub_47ACC0(void *self)
{
  short sVar1;
  bool bVar2;
  int iVar3;
  byte bVar4;
  char cVar5;
  void *pvVar6;
  short *psVar7;
  Gang *this_00;
  MissionManager *this_01;
  
  iVar3 = _DAT_006644cc;
  pvVar6 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  psVar7 = gta2::MissionManager_sub_474F00(this_01,*(short *)(iVar3 + 0xc));
  this_00 = gta2::Gangs_GetGangByName(gGangs,(char *)((int)psVar7 + 9));
  sVar1 = *(short *)(iVar3 + 2);
  if (sVar1 == 0xc6) {
    bVar4 = gta2::Player_GetID(*(Player **)(*(int *)((int)pvVar6 + 8) + 0x15c));
    cVar5 = gta2::Gang_GetRespectForPlayer(this_00,bVar4);
    bVar2 = (int)*(short *)(iVar3 + 10) < (int)cVar5 / 0x14;
  }
  else {
    if (sVar1 != 199) {
      if (sVar1 == 0xe7) {
        bVar4 = gta2::Player_GetID(*(Player **)(*(int *)((int)pvVar6 + 8) + 0x15c));
        cVar5 = gta2::Gang_GetRespectForPlayer(this_00,bVar4);
        *(uint *)((int)self + 8) =
             (uint)((int)cVar5 / 0x14 == (int)*(short *)(iVar3 + 10));
        gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,_DAT_006644cc);
        return;
      }
      goto LAB_0047add0;
    }
    bVar4 = gta2::Player_GetID(*(Player **)(*(int *)((int)pvVar6 + 8) + 0x15c));
    cVar5 = gta2::Gang_GetRespectForPlayer(this_00,bVar4);
    bVar2 = (int)cVar5 / 0x14 < (int)*(short *)(iVar3 + 10);
  }
  *(uint *)((int)self + 8) = (uint)bVar2;
LAB_0047add0:
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,_DAT_006644cc);
  return;
}


// 0x0047af50: MissionScriptObjectData::sub_47AF50
// IDA: MissionScriptObjectData::sub_47AF50
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47AF50(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // ebp
  MissionManager *v2; // esi
  MissionManager *started; // eax
  char *v5; // eax
  int *v6; // edx

  v1 = dword_6644CC;
  v2 = gMissionManager;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = gta2::MissionManager_sub_4763E0(v2, *(_DWORD *)(started->arr_96[1] + 20));
  if ( BYTE2(gta2::MissionManager_StartMission(v2, *((_WORD *)v5 + 4))->arr_96[3]) == 1 )
  {
    gta2::MissionManager_sub_4763B0(v2, *v6, v6[1]);
    self->field_8 = 1;
  }
  else
  {
    self->field_8 = 0;
  }
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047b430: MissionScriptObjectData::sub_47B430
// IDA: MissionScriptObjectData::sub_47B430
// Ghidra: FUN_0047b430
void gta2::MissionScriptObjectData_sub_47B430(void *self)
{
  struct Ped *this_00;
  byte bVar1;
  void *pvVar2;
  uint uVar3;
  MissionManager *this_01;
  int extraout_EDX;
  int iVar4;
  
  iVar4 = _DAT_006644cc;
  gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  pvVar2 = gta2::MissionManager_StartMission(this_01,*(ushort *)(iVar4 + 10));
  this_00 = *(Ped **)(extraout_EDX + 8);
  if (this_00 != NULL) {
    bVar1 = gta2::Ped_IsPlayerControlled(this_00);
    if (bVar1 != 0) {
      uVar3 = gta2::Player_GetMoneyPlayer(this_00->isPlayer);
      iVar4 = _DAT_006644cc;
      *(uint *)((int)pvVar2 + 8) = uVar3 & 0xffff;
    }
  }
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar4);
  return;
}


// 0x0047b5e0: MissionScriptObjectData::sub_47B5E0
// IDA: MissionScriptObjectData::sub_47B5E0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47B5E0(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  struct Ped *v2; // esi
  struct Player *XCoordinate; // eax
  struct Player *v4; // eax
  int v5; // eax
  struct Player *v6; // eax
  struct Player *v7; // eax
  int v8; // eax
  Weapon *PositionZ; // eax
  char v10; // bl
  SpriteS1 *v11; // [esp-4h] [ebp-20h]
  int *v12; // [esp-4h] [ebp-20h]
  SpriteS1 *v13; // [esp-4h] [ebp-20h]
  int *v14; // [esp-4h] [ebp-20h]
  int Y; // [esp+14h] [ebp-8h] BYREF
  int X; // [esp+18h] [ebp-4h] BYREF

  v1 = dword_6644CC;
  v2 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
  if ( !(unsigned __int8)gta2::Ped_sub_433CA0(v2) )
    goto LABEL_8;
  v11 = gta2::Player_sub_401B40((Player *)&v1->arr_96[2], (S202 *)&Y, (int)&v1->arr_96[5]);
  XCoordinate = (Player *)gta2::Ped_GetXCoordinate(v2, (int)&X);
  if ( !gta2::Player_sub_40CE70(XCoordinate, v11) )
    goto LABEL_8;
  v12 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[2], (SpriteS1 *)&X, (PublicTransport *)&v1->arr_96[5]);
  v4 = (Player *)gta2::Ped_GetXCoordinate(v2, (int)&Y);
  LOBYTE(v5) = gta2::Player_CheckCondition(v4, v12);
  if ( !v5 )
    goto LABEL_8;
  v13 = gta2::Player_sub_401B40((Player *)&v1->arr_96[3], (S202 *)&X, (int)&v1->arr_96[6]);
  gta2::Ped_GetYCoordinate(v2, &Y);
  if ( gta2::Player_sub_40CE70(v6, v13)
    && (v14 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[3], (SpriteS1 *)&X, (PublicTransport *)&v1->arr_96[6]),
        gta2::Ped_GetYCoordinate(v2, &Y),
        LOBYTE(v8) = gta2::Player_CheckCondition(v7, v14),
        v8)
    && (PositionZ = (Weapon *)gta2::Ped_GetPositionZ(v2, (int)&X),
        v10 = gta2::Weapon_sub_41C1E0(PositionZ),
        v10 == (unsigned __int8)gta2::Weapon_sub_41C1E0((Weapon *)&v1->arr_96[4])) )
  {
    self->field_8 = 1;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
  else
  {
LABEL_8:
    self->field_8 = 0;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
}


// 0x0047b810: MissionScriptObjectData::sub_47B810
// IDA: MissionScriptObjectData::sub_47B810
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47B810(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  Car *pCar; // esi
  struct Player *v3; // eax
  struct Player *v4; // eax
  int v5; // eax
  struct Player *v6; // eax
  struct Player *v7; // eax
  int v8; // eax
  Weapon *v9; // eax
  char v10; // bl
  SpriteS1 *v11; // [esp-4h] [ebp-20h]
  int *v12; // [esp-4h] [ebp-20h]
  SpriteS1 *v13; // [esp-4h] [ebp-20h]
  int *v14; // [esp-4h] [ebp-20h]
  int v16; // [esp+14h] [ebp-8h] BYREF
  int a2; // [esp+18h] [ebp-4h] BYREF

  v1 = dword_6644CC;
  pCar = (Car *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
  if ( pCar->Damage < 32000 && pCar->Mask != 5 )
    goto LABEL_9;
  v11 = gta2::Player_sub_401B40((Player *)&v1->arr_96[2], (S202 *)&v16, (int)&v1->arr_96[5]);
  gta2::Car_GetX(pCar, &a2);
  if ( !gta2::Player_sub_40CE70(v3, v11) )
    goto LABEL_9;
  v12 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[2], (SpriteS1 *)&a2, (PublicTransport *)&v1->arr_96[5]);
  gta2::Car_GetX(pCar, &v16);
  LOBYTE(v5) = gta2::Player_CheckCondition(v4, v12);
  if ( !v5 )
    goto LABEL_9;
  v13 = gta2::Player_sub_401B40((Player *)&v1->arr_96[3], (S202 *)&a2, (int)&v1->arr_96[6]);
  gta2::Car_GetY(pCar, &v16);
  if ( gta2::Player_sub_40CE70(v6, v13)
    && (v14 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[3], (SpriteS1 *)&a2, (PublicTransport *)&v1->arr_96[6]),
        gta2::Car_GetY(pCar, &v16),
        LOBYTE(v8) = gta2::Player_CheckCondition(v7, v14),
        v8)
    && (gta2::Car_GetZ(pCar, &a2),
        v10 = gta2::Weapon_sub_41C1E0(v9),
        v10 == (unsigned __int8)gta2::Weapon_sub_41C1E0((Weapon *)&v1->arr_96[4])) )
  {
    self->field_8 = 1;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
  else
  {
LABEL_9:
    self->field_8 = 0;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
}


// 0x0047bac0: MissionScriptObjectData::sub_47BAC0
// IDA: MissionScriptObjectData::sub_47BAC0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47BAC0(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // ebp
  MissionManager *v3; // ecx
  MissionManager *started; // eax
  int v5; // edx
  struct Ped *v6; // esi
  MissionManager *v7; // edi
  S169 *pS169; // ecx

  v1 = dword_6644CC;
  gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  started = gta2::MissionManager_StartMission(v3, HIWORD(v1->arr_96[1]));
  v6 = *(Ped **)(v5 + 8);
  v7 = started;
  pS169 = gta2::sub_475AF0(v6);
  switch ( v1->field_2 )
  {
    case 0xEBu:
      gta2::S169_AddPedToEndOfList(pS169, (Ped *)v7->arr_96[1]);
      break;
    case 0xECu:
      gta2::S169_sub_404D40(pS169, (Ped *)v7->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
    case 0x103u:
      gta2::Ped_PedGroupChangeLeader((Ped *)v7->arr_96[1], v6);
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
  }
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047bcd0: MissionScriptObjectData::sub_47BCD0
// IDA: MissionScriptObjectData::sub_47BCD0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47BCD0(struct MissionScriptObjectData *self)
{
  int v2; // edx
  MissionManager *started; // edi
  MissionManager *v4; // ecx
  const char *v5; // eax
  int v6; // esi
  void *v7; // esi
  int v8; // ebx
  char *v9; // eax
  Weapon *v10; // eax
  Weapon *XCoordinate; // eax
  unsigned __int8 v12; // al
  char *v13; // eax
  struct Ped *v14; // esi
  Weapon *v15; // eax
  Weapon *v16; // eax
  unsigned __int8 v17; // al
  char *v18; // esi
  unsigned __int8 v19; // [esp-8h] [ebp-2Ch]
  unsigned __int8 v20; // [esp-8h] [ebp-2Ch]
  const char *v21; // [esp+10h] [ebp-14h]
  int Y; // [esp+14h] [ebp-10h] BYREF
  int X; // [esp+18h] [ebp-Ch] BYREF
  int v24; // [esp+1Ch] [ebp-8h] BYREF
  int v25; // [esp+20h] [ebp-4h] BYREF

  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = (const char *)gta2::MissionManager_sub_474F00(v4, *(_WORD *)(v2 + 10));
  v6 = started->arr_96[1];
  v21 = v5;
  if ( gta2::Ped_IsPlayerControlled((Ped *)v6) )
  {
    v7 = *(void **)(v6 + 348);
    v8 = gta2::sub_4766E0(v7);
    v9 = (char *)gta2::sub_4766F0(v7);
  }
  else
  {
    gta2::Ped_GetYCoordinate((Ped *)v6, &Y);
    v19 = gta2::Weapon_sub_41C1E0(v10);
    XCoordinate = (Weapon *)gta2::Ped_GetXCoordinate((Ped *)v6, (int)&X);
    v12 = gta2::Weapon_sub_41C1E0(XCoordinate);
    v13 = gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, v12, v19, 15);
    v14 = (Ped *)started->arr_96[1];
    v8 = (int)v13;
    gta2::Ped_GetYCoordinate(v14, &v24);
    v20 = gta2::Weapon_sub_41C1E0(v15);
    v16 = (Weapon *)gta2::Ped_GetXCoordinate(v14, (int)&v25);
    v17 = gta2::Weapon_sub_41C1E0(v16);
    v9 = gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, v17, v20, 1);
  }
  v18 = v9;
  self->field_8 = v8 && !gta2::_strnicmp((const char *)(v8 + 6), v21 + 9, *(unsigned __int8 *)(v8 + 5))
               || v18 && !gta2::_strnicmp(v18 + 6, v21 + 9, (unsigned __int8)v18[5]);
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047be00: MissionScriptObjectData::sub_47BE00
// IDA: MissionScriptObjectData::sub_47BE00
// Ghidra: FUN_0047be00
void gta2::MissionScriptObjectData_sub_47BE00(void *self)
{
  Car *this_00;
  int iVar1;
  bool bVar2;
  byte bVar3;
  void *pvVar4;
  MissionManager *this_01;
  void *extraout_EDX;
  
  iVar1 = _DAT_006644cc;
  gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  pvVar4 = gta2::MissionManager_StartMission(this_01,*(ushort *)(iVar1 + 10));
  if (pvVar4 != extraout_EDX) {
    bVar3 = FUN_00475e60(*(void **)((int)extraout_EDX + 8),
                         *(int *)((int)pvVar4 + 8));
    *(uint *)((int)self + 8) = (uint)(bVar3 != 0);
    gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
    return;
  }
  this_00 = *(Car **)((int)extraout_EDX + 8);
  bVar2 = gta2::Car_sub_421720(this_00);
  if (!bVar2) {
    bVar3 = gta2::Car_sub_41E460(this_00);
    if (bVar3 == 0) {
      *(undefined4 *)((int)self + 8) = 0;
      gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
      return;
    }
  }
  *(undefined4 *)((int)self + 8) = 1;
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
  return;
}


// 0x0047c000: MissionScriptObjectData::sub_47C000
// IDA: MissionScriptObjectData::sub_47C000
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47C000(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // ebp
  MissionManager *v2; // esi
  MissionManager *started; // edi
  MissionManager *v5; // eax
  int v6; // edx

  v1 = gMissionManager;
  v2 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  gta2::sub_475B10((void *)started->arr_96[1]);
  v5 = gta2::MissionManager_StartMission(v1, HIWORD(v2->arr_96[1]));
  v5->arr_96[1] = v6;
  gta2::sub_475B40((void *)started->arr_96[1]);
  gta2::MissionScriptObjectData_sub_476E50(self, v2);
}


// 0x0047c1e0: MissionScriptObjectData::sub_47C1E0
// IDA: MissionScriptObjectData::sub_47C1E0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47C1E0(struct MissionScriptObjectData *self)
{
  MissionManager *started; // esi
  int v3; // edx
  unsigned __int16 v4; // ax
  int v5; // edi
  struct Ped *v6; // esi
  int *PositionZ; // ebx
  int *v8; // eax
  int *v9; // ebp
  int *XCoordinate; // eax
  int v11; // edx
  EventHandler *pS63; // esi
  int *v13; // eax
  int *v14; // ebx
  int *v15; // eax
  int *v16; // ebp
  int v17; // ecx
  int *v18; // eax
  int *MaxZForLocation; // eax
  int v20; // ecx
  int Z; // [esp+14h] [ebp-1Ch] BYREF
  int Y; // [esp+18h] [ebp-18h] BYREF
  int X; // [esp+1Ch] [ebp-14h] BYREF
  int a2; // [esp+20h] [ebp-10h] BYREF
  int v26; // [esp+24h] [ebp-Ch] BYREF
  int v27; // [esp+28h] [ebp-8h] BYREF
  char v28[4]; // [esp+2Ch] [ebp-4h] BYREF

  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  *(_DWORD *)&v4 = *(unsigned __int16 *)(v3 + 2);
  if ( v4 > 0x193u )
  {
    v5 = 32;
    if ( *(_DWORD *)&v4 == 405 )
      goto LABEL_10;
  }
  else
  {
    if ( v4 == 403 )
    {
      v5 = 18;
      goto LABEL_10;
    }
    if ( *(_DWORD *)&v4 == 144 )
    {
      v5 = 19;
      goto LABEL_10;
    }
    if ( *(_DWORD *)&v4 == 398 )
    {
      v5 = 20;
      goto LABEL_10;
    }
  }
  v5 = (int)self;
LABEL_10:
  switch ( gta2::MissionScriptObjectData_sub_475010(self, started->field_2) )
  {
    case 1:
      v6 = (Ped *)started->arr_96[1];
      PositionZ = (int *)gta2::Ped_GetPositionZ(v6, (int)&Z);
      gta2::Ped_GetYCoordinate(v6, &Y);
      v9 = v8;
      XCoordinate = (int *)gta2::Ped_GetXCoordinate(v6, (int)&X);
      LOWORD(v11) = unk_664530;
      gta2::Object_sub_485540(gObject, *XCoordinate, *v9, *PositionZ, v11, v5, 0);
      break;
    case 2:
      gta2::Car_ExplodeCar((Car *)started->arr_96[1], 19);
      break;
    case 3:
      pS63 = (EventHandler *)started->arr_96[1];
      gta2::S63_sub_4340F0(pS63, &a2);
      v14 = v13;
      gta2::S63_sub_4340E0(pS63, &v26);
      v16 = v15;
      gta2::S63_sub_4340D0(pS63, &v27);
      LOWORD(v17) = unk_664530;
      gta2::Object_sub_485540(gObject, *v18, *v16, *v14, v17, v5, 0);
      break;
    case 4:
      MaxZForLocation = gta2::MapRelatedStruct_FindMaxZForLocation(
                          gMapRelatedStruct,
                          (int *)v28,
                          (int *)started->arr_96[3],
                          (S202 *)started->arr_96[4]);
      LOWORD(v20) = unk_664530;
      gta2::Object_sub_485540(gObject, started->arr_96[3], started->arr_96[4], *MaxZForLocation, v20, v5, 0);
      break;
    default:
      break;
  }
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047c6a0: MissionScriptObjectData::sub_47C6A0
// IDA: MissionScriptObjectData::sub_47C6A0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47C6A0(struct MissionScriptObjectData *self)
{
  S16_02 *v2; // [esp+4h] [ebp-Ch] BYREF

  gta2::S16_02_sub_44C840((S16_02 *)&v2);
  gta2::MapRelatedStruct_sub_464060(
    gMapRelatedStruct,
    LOBYTE(dword_6644CC->arr_96[1]),
    BYTE1(dword_6644CC->arr_96[1]),
    BYTE2(dword_6644CC->arr_96[1]),
    &v2);
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047c8d0: MissionScriptObjectData::sub_47C8D0
// IDA: MissionScriptObjectData::sub_47C8D0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47C8D0(struct MissionScriptObjectData *self, int a2, __int16 a3)
{
  Viewport *v4; // eax

  v4 = (Viewport *)gta2::S29_sub_476DF0(self->S29_);
  v4->Data1 = self->field_8;
  v4->Data2 = *(_WORD *)(a2 + 4);
  gta2::S29_sub_474FB0(self->S29_, v4);
  gta2::MissionScriptObjectData_sub_476E80(self, a3);
}


// 0x0047cc50: MissionScriptObjectData::sub_47CC50
// IDA: MissionScriptObjectData::sub_47CC50
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47CC50(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *v3; // ecx
  int v4; // edx
  MissionManager *started; // edi

  v1 = dword_6644CC;
  gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  started = gta2::MissionManager_StartMission(v3, HIWORD(v1->arr_96[1]));
  if ( v1->field_2 == 193 )
    started->arr_96[1] = (int)gta2::Player_getMoney(*(Player **)(*(_DWORD *)(v4 + 8) + 348));
  else
    started->arr_96[1] = (int)gta2::Player_GetMultiPlayer(*(Player **)(*(_DWORD *)(v4 + 8) + 348));
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047ccc0: MissionScriptObjectData::sub_47CCC0
// IDA: MissionScriptObjectData::sub_47CCC0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47CCC0(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  Player *a2[2]; // [esp+8h] [ebp-8h] BYREF

  v1 = dword_6644CC;
  gta2::S103_sub_401D20((S103 *)a2, &dword_6644CC->arr_96[1], &dword_6644CC->arr_96[2]);
  gta2::CarSystemManager_sub_476610(gCarSystemManager, a2);
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047ce00: MissionScriptObjectData::sub_47CE00
// IDA: MissionScriptObjectData::sub_47CE00
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47CE00(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  int v2; // edi
  __int16 GangPositionByName; // bp
  int v4; // ebx
  MissionManager *v5; // ecx
  char v6; // al
  char *v7; // eax
  __int16 v8; // ax
  signed __int16 v9; // ax
  MissionManager *v10; // edx
  int v11; // [esp+10h] [ebp-14h]
  __int16 v12; // [esp+14h] [ebp-10h]
  MissionManager *started; // [esp+1Ch] [ebp-8h]

  v1 = dword_6644CC;
  v2 = 87;
  GangPositionByName = -1;
  v11 = 87;
  v4 = 51;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[5]);
  v6 = BYTE2(v1->arr_96[1]);
  if ( !v6 || (v12 = 0, v6 == 2) )
    v12 = 1;
  switch ( BYTE2(v1->arr_96[1]) )
  {
    case 0:
      if ( HIWORD(v1->arr_96[2]) != 0xFFFF )
      {
        v2 = HIWORD(v1->arr_96[2]);
        if ( gAllGxtFile && (v2 == 12 || v2 == 3 || v2 == 22 || v2 == 30 || v2 == 52 || v2 == 84) )
          v2 = 87;
      }
      break;
    case 1:
      v4 = HIWORD(v1->arr_96[2]);
      if ( gAllGxtFile && (v4 == 46 || v4 == 24) )
        v4 = 51;
      break;
    case 2:
    case 3:
      v7 = (char *)gta2::MissionManager_sub_474F00(v5, HIWORD(v1->arr_96[2]));
      GangPositionByName = (char)gta2::Gangs_GetGangPositionByName(gGangs, v7 + 9);
      break;
    default:
      break;
  }
  v8 = HIWORD(v1->arr_96[3]);
  if ( v8 >= 0 )
    v11 = v8;
  v9 = gta2::sub_41DE40(
         &gGame->PlayerMain->field_47C,
         v12,
         v2,
         v4,
         GangPositionByName,
         SHIBYTE(v1->arr_96[1]),
         BYTE2(v1->arr_96[5]),
         v11,
         LOWORD(v1->arr_96[3]),
         (BYTE1(v1->arr_96[2]) != 1) + 1,
         v1->arr_96[2],
         v1->arr_96[4],
         0);
  v10 = dword_6644CC;
  started->arr_96[1] = v9;
  gta2::MissionScriptObjectData_sub_476E50(self, v10);
}


// 0x0047d070: MissionScriptObjectData::sub_47D070
// IDA: MissionScriptObjectData::sub_47D070
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47D070(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *v3; // ecx
  int v4; // edx
  MissionManager *started; // edi
  SpriteS1 *v6; // eax
  int v7; // eax
  struct Ped *v8; // ebx
  struct Player *Player; // ecx
  S900 *v10; // eax
  struct Player *v11; // ecx
  S900 *v12; // eax
  MissionManager *v13; // [esp-4h] [ebp-20h]
  char v14; // [esp+10h] [ebp-Ch] BYREF
  _BYTE v15[4]; // [esp+14h] [ebp-8h] BYREF
  _BYTE v16[4]; // [esp+18h] [ebp-4h] BYREF

  v1 = dword_6644CC;
  gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  started = gta2::MissionManager_StartMission(v3, HIWORD(v1->arr_96[1]));
  if ( v1->field_2 == 206 )
  {
    v11 = *(Player **)(*(_DWORD *)(v4 + 8) + 88);
    if ( v11 )
    {
      v12 = gta2::Player_sub_4211C0(v11, v16);
      started->arr_96[1] = sub_4754D0(v12);
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      return;
    }
    goto LABEL_10;
  }
  if ( v1->field_2 != 207 )
  {
    if ( v1->field_2 == 209 )
    {
      v6 = gta2::sub_421C00(*(void **)(v4 + 8), (SpriteS1 *)&v14);
      v7 = sub_4754D0(v6);
      v13 = dword_6644CC;
      started->arr_96[1] = v7;
      gta2::MissionScriptObjectData_sub_476E50(self, v13);
      return;
    }
    goto LABEL_11;
  }
  v8 = *(Ped **)(v4 + 8);
  if ( gta2::Ped_IsInCar(v8) )
  {
    Player = gta2::Ped_GetCarPlayers(v8)->Player_;
    if ( Player )
    {
      v10 = gta2::Player_sub_4211C0(Player, v15);
      started->arr_96[1] = sub_4754D0(v10);
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      return;
    }
LABEL_10:
    started->arr_96[1] = gta2::AudioSourceParams_sub_41F9D0((AudioSourceParams *)&gAudioSourceParams);
  }
LABEL_11:
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047d260: MissionScriptObjectData::sub_47D260
// IDA: MissionScriptObjectData::sub_47D260
// Ghidra: FUN_0047d260
void gta2::MissionScriptObjectData_sub_47D260(void *self)
{
  int iVar1;
  byte bVar2;
  void *pvVar3;
  void *pvVar4;
  MissionManager *this_00;
  MissionManager *this_01;
  int extraout_EDX;
  
  iVar1 = _DAT_006644cc;
  pvVar3 = gta2::MissionManager_StartMission(gMissionManager,*(ushort *)(_DAT_006644cc + 8));
  gta2::MissionManager_StartMission(this_00,*(ushort *)(iVar1 + 10));
  pvVar4 = gta2::MissionManager_StartMission(this_01,*(ushort *)(iVar1 + 0xc));
  bVar2 = gta2::sub_475700((MissionManager *)self,(uint)*(ushort *)(iVar1 + 2));
  switch(bVar2) {
  case 0:
    *(int *)((int)pvVar3 + 8) =
         *(int *)((int)pvVar4 + 8) + *(int *)(extraout_EDX + 8);
    gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
    return;
  case 1:
    *(int *)((int)pvVar3 + 8) =
         *(int *)(extraout_EDX + 8) - *(int *)((int)pvVar4 + 8);
    gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
    return;
  case 7:
    *(int *)((int)pvVar3 + 8) =
         *(int *)(extraout_EDX + 8) / *(int *)((int)pvVar4 + 8);
    gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
    return;
  case 8:
    *(int *)((int)pvVar3 + 8) =
         *(int *)((int)pvVar4 + 8) * *(int *)(extraout_EDX + 8);
    gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
    return;
  case 9:
    *(int *)((int)pvVar3 + 8) =
         *(int *)(extraout_EDX + 8) % *(int *)((int)pvVar4 + 8);
  }
  gta2::MissionScriptObjectData_sub_476E50((MissionManager *)self,iVar1);
  return;
}


// 0x0047d360: MissionScriptObjectData::sub_47D360
// IDA: MissionScriptObjectData::sub_47D360
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47D360(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *started; // edi
  MissionManager *v4; // ecx
  int v5; // edx

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  gta2::MissionManager_StartMission(v4, HIWORD(v1->arr_96[1]));
  switch ( gta2::sub_475700(v1->field_2) )
  {
    case 0:
      started->arr_96[1] = *(_DWORD *)(v5 + 8) + SLOWORD(v1->arr_96[2]);
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      break;
    case 1:
      started->arr_96[1] = *(_DWORD *)(v5 + 8) - SLOWORD(v1->arr_96[2]);
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      break;
    case 7:
      started->arr_96[1] = *(_DWORD *)(v5 + 8) / SLOWORD(v1->arr_96[2]);
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      break;
    case 8:
      started->arr_96[1] = *(_DWORD *)(v5 + 8) * SLOWORD(v1->arr_96[2]);
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      break;
    case 9:
      started->arr_96[1] = *(_DWORD *)(v5 + 8) % SLOWORD(v1->arr_96[2]);
      goto LABEL_7;
    default:
LABEL_7:
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      break;
  }
}


// 0x0047d7a0: MissionScriptObjectData::sub_47D7A0
// IDA: MissionScriptObjectData::sub_47D7A0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47D7A0(struct MissionScriptObjectData *self)
{
  MissionManager *pMissionManager; // ebp
  MissionManager *v2; // esi
  MissionManager *started; // eax
  MissionManager *v5; // edi
  int v6; // eax
  int v7; // eax
  int v8; // eax
  char v9; // [esp-8h] [ebp-18h]
  char v10; // [esp-8h] [ebp-18h]

  pMissionManager = gMissionManager;
  v2 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = started;
  if ( HIWORD(v2->arr_96[1]) )
  {
    v10 = v2->arr_96[2];
    v7 = gta2::Ped_sub_420B60((Ped *)started->arr_96[1]);
    if ( gta2::MissionManager_sub_4765A0(pMissionManager, v7, v10, 1) )
    {
      self->field_8 = 1;
      v8 = gta2::Ped_sub_420B60((Ped *)v5->arr_96[1]);
      gta2::MissionManager_sub_4764D0(gMissionManager, v8, 1);
      HIWORD(v2->arr_96[1]) = 0;
    }
    else
    {
      self->field_8 = 0;
    }
    gta2::MissionScriptObjectData_sub_476E50(self, v2);
  }
  else
  {
    v9 = v2->arr_96[2];
    v6 = gta2::Ped_sub_420B60((Ped *)started->arr_96[1]);
    gta2::MissionManager_sub_476400(pMissionManager, v6, v9, 1);
    self->field_8 = 0;
    HIWORD(v2->arr_96[1]) = 1;
    gta2::MissionScriptObjectData_sub_476E50(self, v2);
  }
}


// 0x0047d860: MissionScriptObjectData::sub_47D860
// IDA: MissionScriptObjectData::sub_47D860
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47D860(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *started; // eax
  MissionManager *v4; // ecx
  MissionManager *v5; // edi
  int v6; // eax
  char v7; // al

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = started;
  if ( HIWORD(v1->arr_96[1]) )
  {
    if ( gta2::MissionManager_sub_4765A0(v4, *(_DWORD *)(started->arr_96[1] + 108), v1->arr_96[2], 0) )
    {
LABEL_7:
      self->field_8 = 1;
      HIWORD(v1->arr_96[1]) = 0;
      gta2::MissionScriptObjectData_sub_476E50(self, v1);
      return;
    }
    self->field_8 = 0;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
  else
  {
    v6 = started->arr_96[1];
    if ( v1->field_2 == 358 )
      v7 = gta2::MissionManager_sub_476400(v4, *(_DWORD *)(v6 + 108), v1->arr_96[2], 0);
    else
      v7 = gta2::MissionManager_sub_476400(v4, *(_DWORD *)(v6 + 108), 23, 0);
    if ( v7 && gta2::MissionManager_sub_4765A0(gMissionManager, *(_DWORD *)(v5->arr_96[1] + 108), v1->arr_96[2], 0) )
      goto LABEL_7;
    self->field_8 = 0;
    HIWORD(v1->arr_96[1]) = 1;
    gta2::MissionScriptObjectData_sub_476E50(self, v1);
  }
}


// 0x0047d9d0: MissionScriptObjectData::sub_47D9D0
// IDA: MissionScriptObjectData::sub_47D9D0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47D9D0(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *v3; // ecx
  MissionManager *started; // eax
  int v5; // ecx
  unsigned __int8 *v6; // ecx
  int v7; // edx
  int v8; // edx
  MissionManager *v9; // edi
  unsigned __int16 v10; // si
  void *v11; // ecx

  v1 = dword_6644CC;
  gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  started = gta2::MissionManager_StartMission(v3, HIWORD(v1->arr_96[1]));
  v6 = *(unsigned __int8 **)(v5 + 832);
  v8 = *(_DWORD *)(v7 + 8);
  v9 = started;
  v10 = 0;
  while ( !v8 || *(_DWORD *)(v8 + 132) != *v6 )
  {
    ++v6;
    if ( ++v10 >= 0x13u )
      goto LABEL_9;
  }
  gta2::sub_476950((_DWORD *)started->arr_96[1], (unsigned __int8)byte_5931FC[v10]);
  v11 = (void *)v9->arr_96[1];
  if ( (unsigned __int8)byte_5931FC[v10] >= 0x5Bu )
    gta2::sub_476930(v11, 1);
  else
    gta2::sub_476930(v11, 3);
LABEL_9:
  if ( v10 == 19 )
  {
    gta2::sub_476930((void *)v9->arr_96[1], 3);
    gta2::sub_476950((_DWORD *)v9->arr_96[1], 65);
  }
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047dad0: MissionScriptObjectData::sub_47DAD0
// IDA: MissionScriptObjectData::sub_47DAD0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47DAD0(struct MissionScriptObjectData *self)
{
  _DWORD *v1; // ebp
  GameObject *v2; // ecx
  MissionManager *v3; // esi
  MissionManager *started; // edi
  int v5; // ebx
  Car *CarPlayers; // ebp
  int v7; // ecx
  int v8; // edx
  struct Ped *v9; // eax
  __int16 *v10; // eax
  int v11; // [esp-4h] [ebp-20h]
  __int16 v12; // [esp+12h] [ebp-Ah] BYREF
  _BYTE a3[4]; // [esp+14h] [ebp-8h] BYREF
  MissionScriptObjectData *v14; // [esp+18h] [ebp-4h]

  v3 = dword_6644CC;
  v14 = self;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = started->arr_96[1];
  CarPlayers = gta2::Ped_GetCarPlayers((Ped *)v5);
  if ( v5 )
  {
    v7 = v3->arr_96[4];
    v8 = v3->arr_96[3];
    v9 = (Ped *)v3->arr_96[2];
    v11 = v7;
    if ( CarPlayers )
    {
      gta2::Ped_sub_43AD50((Ped *)v5, v9, v8, v7);
      gta2::sub_401AE0(a3, HIWORD(v3->arr_96[1]));
      v10 = gta2::sub_401CB0(&unk_664E00, (CarSystemManager *)&v12, a3);
      gta2::Ped_SetRotation((Ped *)started->arr_96[1], *v10);
      gta2::Car_sub_4235D0(CarPlayers);
      CarPlayers->Driver = 0;
      gta2::Player_sub_4A6900(*(Player **)(v5 + 348));
      gta2::CameraOrPhysics_sub_41F410((CameraOrPhysics *)(*(_DWORD *)(v5 + 348) + 144), (S131 *)started->arr_96[1]);
      gta2::CameraOrPhysics_sub_41E410((CameraOrPhysics *)(*(_DWORD *)(v5 + 348) + 144));
      gta2::CameraOrPhysics_sub_41E010((CameraOrPhysics *)(*(_DWORD *)(v5 + 348) + 144));
      gta2::CameraOrPhysics_ResetAccuracy((CameraOrPhysics *)(*(_DWORD *)(v5 + 348) + 144));
      v3 = dword_6644CC;
    }
    else
    {
      v1 = *(_DWORD **)(v5 + 348);
      v1[70] = v9;
      v1[71] = v8;
      v1[72] = v7;
      v1[74] = v9;
      v1[75] = v8;
      v1[76] = v7;
      v1[117] = v9;
      v1[118] = v8;
      v1[119] = v7;
      v1[121] = v9;
      v1[122] = v8;
      v1[123] = v7;
      v2 = *(GameObject **)(v5 + 360);
      v2->Rotation = 4 * HIWORD(v3->arr_96[1]);
      gta2::GameObject_sub_491E00(v2, (int)v9, v8, v11);
    }
  }
  gta2::MissionScriptObjectData_sub_476E50(v14, v3);
}


// 0x0047de70: MissionScriptObjectData::sub_47DE70
// IDA: MissionScriptObjectData::sub_47DE70
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47DE70(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *started; // ebx
  MissionManager *v4; // ecx
  struct Ped *v5; // edi
  int *v6; // eax
  CarSystemManager **v7; // eax
  struct Ped *v8; // edi
  Weapon **v9; // eax
  SpriteS1 *v10; // eax
  int *v11; // eax
  int v12; // eax
  SpriteS1 *v13; // eax
  int *v14; // eax
  int v15; // eax
  char v16; // bl
  bool ExitAnimState; // al
  unsigned __int16 v18; // [esp-4h] [ebp-3Ch]
  int a3; // [esp+10h] [ebp-28h] BYREF
  S202 a2; // [esp+14h] [ebp-24h] BYREF
  char v21; // [esp+34h] [ebp-4h] BYREF

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v18 = HIWORD(v1->arr_96[1]);
  a2.pPlayer = (Player *)started;
  v5 = (Ped *)gta2::MissionManager_StartMission(v4, v18)->arr_96[1];
  a2.field_0 = *(_DWORD *)gta2::Ped_GetXCoordinate(v5, (int)&a2.field_1C);
  gta2::Ped_GetYCoordinate(v5, (int *)&a2.field_1C);
  a2.field_C = *v6;
  *(_DWORD *)&a2.field_1C = *(_DWORD *)gta2::Ped_GetPositionZ(v5, (int)&a2.field_1C);
  a3 = *(_DWORD *)gta2::sub_401B90(&v1->arr_96[2], &a2.field_18, &unk_664DC4);
  v7 = (CarSystemManager **)gta2::sub_401B90(&v1->arr_96[3], &a2.field_18, &unk_664DC4);
  v8 = (Ped *)started->arr_96[1];
  a2.CarSystemManager = *v7;
  a2.S202 = *(S202 **)gta2::Ped_GetXCoordinate(v8, (int)&a2.field_18);
  gta2::Ped_GetYCoordinate(v8, &a2.field_18);
  a2.field_10 = *v9;
  a2.field_18 = *(_DWORD *)gta2::Ped_GetPositionZ(v8, (int)&a2.field_18);
  self->field_8 = 0;
  v10 = gta2::Player_sub_401B40((Player *)&a2, (S202 *)&v21, (int)&a3);
  if ( !gta2::Player_sub_40CE70((Player *)&a2.S202, v10) )
    goto LABEL_14;
  v11 = (int *)gta2::S202_sub_401B20(&a2, (SpriteS1 *)&v21, (PublicTransport *)&a3);
  LOBYTE(v12) = gta2::Player_CheckCondition((Player *)&a2.S202, v11);
  if ( !v12 )
    goto LABEL_14;
  v13 = gta2::Player_sub_401B40((Player *)&a2.field_C, (S202 *)&v21, (int)&a2.CarSystemManager);
  if ( !gta2::Player_sub_40CE70((Player *)&a2.field_10, v13) )
    goto LABEL_14;
  v14 = (int *)gta2::S202_sub_401B20((S202 *)&a2.field_C, (SpriteS1 *)&v21, (PublicTransport *)&a2.CarSystemManager);
  LOBYTE(v15) = gta2::Player_CheckCondition((Player *)&a2.field_10, v14);
  if ( !v15 )
    goto LABEL_14;
  v16 = gta2::Weapon_sub_41C1E0((Weapon *)&a2.field_18);
  if ( v16 != (unsigned __int8)gta2::Weapon_sub_41C1E0((Weapon *)&a2.field_1C) )
    goto LABEL_14;
  switch ( v1->field_2 )
  {
    case 0x16Fu:
      ExitAnimState = gta2::Ped_GetGameObject(*(Ped **)&a2.pPlayer->Rotate);
      break;
    case 0x17Du:
      ExitAnimState = gta2::Ped_IsInCar(*(Ped **)&a2.pPlayer->Rotate);
      break;
    case 0x17Eu:
      goto LABEL_13;
    default:
      goto LABEL_14;
  }
  if ( ExitAnimState )
LABEL_13:
    self->field_8 = 1;
LABEL_14:
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047e210: MissionScriptObjectData::sub_47E210
// IDA: MissionScriptObjectData::sub_47E210
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47E210(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *v2; // edi
  MissionManager *started; // eax
  int v5; // ecx
  MissionManager *v6; // eax
  int v7; // edx

  v1 = dword_6644CC;
  v2 = gMissionManager;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  v5 = started->arr_96[1];
  if ( v5 != -3 && v5 != -4 )
  {
    gta2::sub_476660(&gGame->PlayerMain->field_47C, started->arr_96[1]);
    v6 = gta2::MissionManager_StartMission(v2, HIWORD(v1->arr_96[1]));
    v6->arr_96[1] = v7;
  }
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047e360: MissionScriptObjectData::sub_47E360
// IDA: MissionScriptObjectData::sub_47E360
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47E360(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  MissionScriptObjectData *pS28; // ebx
  int *v3; // eax
  MissionManager *started; // eax
  S169 *v5; // ebp
  struct Ped *v6; // esi
  unsigned __int8 Index; // al
  struct Player *XCoordinate; // eax
  struct Player *v9; // eax
  int v10; // eax
  struct Player *v11; // eax
  struct Player *v12; // eax
  int v13; // eax
  unsigned __int16 v14; // cx
  struct Ped *Ped; // ebp
  struct Player *v16; // eax
  struct Player *v17; // eax
  int v18; // eax
  struct Player *v19; // eax
  struct Player *v20; // eax
  int v21; // eax
  unsigned __int16 v22; // [esp-4h] [ebp-48h]
  SpriteS1 *v23; // [esp-4h] [ebp-48h]
  int *v24; // [esp-4h] [ebp-48h]
  SpriteS1 *v25; // [esp-4h] [ebp-48h]
  int *v26; // [esp-4h] [ebp-48h]
  SpriteS1 *v27; // [esp-4h] [ebp-48h]
  int *v28; // [esp-4h] [ebp-48h]
  SpriteS1 *v29; // [esp-4h] [ebp-48h]
  int *v30; // [esp-4h] [ebp-48h]
  int a3; // [esp+10h] [ebp-34h] BYREF
  int Camer_Z_View; // [esp+14h] [ebp-30h] BYREF
  MissionScriptObjectData *v33; // [esp+18h] [ebp-2Ch]
  struct Ped **Ped_Arr9; // [esp+1Ch] [ebp-28h]
  int a2; // [esp+20h] [ebp-24h] BYREF
  S202 pS202; // [esp+24h] [ebp-20h] BYREF

  v1 = dword_6644CC;
  pS28 = self;
  v33 = self;
  a3 = *(_DWORD *)gta2::sub_401B90(&dword_6644CC->arr_96[5], &a2, &unk_664DC4);
  v3 = (int *)gta2::sub_401B90(&v1->arr_96[6], &a2, &unk_664DC4);
  v22 = v1->arr_96[1];
  Camer_Z_View = *v3;
  started = gta2::MissionManager_StartMission(gMissionManager, v22);
  v5 = gta2::sub_475AF0((void *)started->arr_96[1]);
  v6 = v5->Ped_Arr9[0];
  Ped_Arr9 = v5->Ped_Arr9;
  if ( v6 )
  {
    Index = v5->Index;
    a2 = 0;
    if ( Index )
    {
      do
      {
        v23 = gta2::Player_sub_401B40((Player *)&v1->arr_96[2], &pS202, (int)&a3);
        XCoordinate = (Player *)gta2::Ped_GetXCoordinate(v6, (int)&pS202.S202);
        if ( !gta2::Player_sub_40CE70(XCoordinate, v23) )
          goto LABEL_8;
        v24 = (int *)gta2::S202_sub_401B20(
                       (S202 *)&v1->arr_96[2],
                       (SpriteS1 *)&pS202.CarSystemManager,
                       (PublicTransport *)&a3);
        v9 = (Player *)gta2::Ped_GetXCoordinate(v6, (int)&pS202.field_C);
        LOBYTE(v10) = gta2::Player_CheckCondition(v9, v24);
        if ( !v10 )
          goto LABEL_8;
        v25 = gta2::Player_sub_401B40((Player *)&v1->arr_96[3], (S202 *)&pS202.field_10, (int)&Camer_Z_View);
        gta2::Ped_GetYCoordinate(v6, (int *)&pS202.pPlayer);
        if ( gta2::Player_sub_40CE70(v11, v25)
          && (v26 = (int *)gta2::S202_sub_401B20(
                             (S202 *)&v1->arr_96[3],
                             (SpriteS1 *)&pS202.field_18,
                             (PublicTransport *)&Camer_Z_View),
              gta2::Ped_GetYCoordinate(v6, (int *)&pS202.field_1C),
              LOBYTE(v13) = gta2::Player_CheckCondition(v12, v26),
              v13) )
        {
          v33->field_8 = 1;
        }
        else
        {
LABEL_8:
          v33->field_8 = 0;
        }
        v14 = v5->Index;
        v6 = Ped_Arr9[1];
        ++Ped_Arr9;
        ++a2;
      }
      while ( (unsigned __int16)a2 < v14 );
      pS28 = v33;
    }
  }
  Ped = v5->Ped_;
  v27 = gta2::Player_sub_401B40((Player *)&v1->arr_96[2], (S202 *)&pS202.field_1C, (int)&a3);
  v16 = (Player *)gta2::Ped_GetXCoordinate(Ped, (int)&pS202.field_18);
  if ( !gta2::Player_sub_40CE70(v16, v27) )
    goto LABEL_16;
  v28 = (int *)gta2::S202_sub_401B20((S202 *)&v1->arr_96[2], (SpriteS1 *)&pS202.field_1C, (PublicTransport *)&a3);
  v17 = (Player *)gta2::Ped_GetXCoordinate(Ped, (int)&pS202.field_18);
  LOBYTE(v18) = gta2::Player_CheckCondition(v17, v28);
  if ( !v18 )
    goto LABEL_16;
  v29 = gta2::Player_sub_401B40((Player *)&v1->arr_96[3], (S202 *)&pS202.field_1C, (int)&Camer_Z_View);
  gta2::Ped_GetYCoordinate(Ped, &pS202.field_18);
  if ( gta2::Player_sub_40CE70(v19, v29)
    && (v30 = (int *)gta2::S202_sub_401B20(
                       (S202 *)&v1->arr_96[3],
                       (SpriteS1 *)&pS202.field_1C,
                       (PublicTransport *)&Camer_Z_View),
        gta2::Ped_GetYCoordinate(Ped, &pS202.field_18),
        LOBYTE(v21) = gta2::Player_CheckCondition(v20, v30),
        v21) )
  {
    pS28->field_8 = 1;
    gta2::MissionScriptObjectData_sub_476E50(pS28, v1);
  }
  else
  {
LABEL_16:
    pS28->field_8 = 0;
    gta2::MissionScriptObjectData_sub_476E50(pS28, v1);
  }
}


// 0x0047ecb0: MissionScriptObjectData::sub_47ECB0
// IDA: MissionScriptObjectData::sub_47ECB0
// Ghidra: FUN_0047ecb0
undefined4 gta2::MissionScriptObjectData_sub_47ECB0(void *self,undefined2 param_1)
{
  MissionManager *this_00;
  undefined4 extraout_ECX;
  
  this_00 = (MissionManager *)gta2::MissionScriptObjects_RemoveFirstElement(gAnimation);
  gta2::MissionScriptObjectData_sub_475B70(this_00,*(undefined1 *)((int)self + 6),param_1);
  return extraout_ECX;
}


// 0x0047ece0: MissionScriptObjectData::sub_47ECE0
// IDA: MissionScriptObjectData::sub_47ECE0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47ECE0(struct MissionScriptObjectData *self, int a2, int a3)
{
  gta2::MissionManager_sub_475E90(gMissionManager, (FileMgr *)a3);
  strcpy((char *)self->arr, (const char *)a3);
  gta2::MissionScriptObjectData_sub_47C8D0(self, a2, a3);
}


// 0x0047f760: MissionScriptObjectData::sub_47F760
// IDA: MissionScriptObjectData::sub_47F760
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47F760(struct MissionScriptObjectData *self, unsigned __int16 a2)
{
  MissionManager *pMissionManager; // esi
  MissionManager *started; // eax
  MissionScriptObjectData *v4; // edx
  MissionManager *v5; // ecx
  MissionManager *v6; // edi
  int v7; // eax
  MissionManager *v8; // esi
  struct Ped *v9; // ecx
  MissionManager *v10; // esi
  S65 *v11; // eax
  MissionManager *v12; // eax
  MissionManager *v13; // esi
  EventHandler *pS63; // ecx

  pMissionManager = gMissionManager;
  started = gta2::MissionManager_StartMission(gMissionManager, a2);
  switch ( gta2::MissionScriptObjectData_sub_475010(v4, started->field_2) )
  {
    case 1:
      v8 = gta2::MissionManager_StartMission(pMissionManager, a2);
      v9 = (Ped *)v8->arr_96[1];
      if ( v9 )
      {
        gta2::Ped_sub_43E650(v9);
        v8->arr_96[1] = 0;
      }
      break;
    case 2:
      v6 = gta2::MissionManager_StartMission(pMissionManager, a2);
      v7 = v6->arr_96[1];
      if ( v7 )
      {
        gta2::MissionManager_sub_4764D0(v5, *(_DWORD *)(v7 + 108), 0);
        gta2::Car_isMask4((Car *)v6->arr_96[1]);
        v6->arr_96[1] = 0;
      }
      break;
    case 3:
    case 10:
      v13 = gta2::MissionManager_StartMission(pMissionManager, a2);
      pS63 = (EventHandler *)v13->arr_96[1];
      if ( pS63 )
      {
        gta2::S63_sub_483C40(pS63);
        v13->arr_96[1] = 0;
      }
      break;
    case 8:
      v10 = gta2::MissionManager_StartMission(pMissionManager, a2);
      v11 = (S65 *)v10->arr_96[1];
      if ( v11 )
      {
        gta2::S115_sub_47F4F0(gS115, v11);
        v10->arr_96[1] = 0;
      }
      break;
    case 9:
      v12 = gta2::MissionManager_StartMission(pMissionManager, a2);
      gta2::DMAudio_sub_410590(&gDMAudio, v12->arr_96[1], v12->arr_96[2]);
      break;
    default:
      return;
  }
}


// 0x0047f890: MissionScriptObjectData::sub_47F890
// IDA: MissionScriptObjectData::sub_47F890
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47F890(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  MissionManager *started; // ebx
  MissionScriptObjectData *pMissionScriptObjectData; // eax

  v1 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
  pMissionScriptObjectData = (MissionScriptObjectData *)gta2::MissionScriptObjectData_sub_47ECB0(self, v1->arr_96[1]);
  started->arr_96[1] = (int)pMissionScriptObjectData;
  LOWORD(started->arr_96[2]) = pMissionScriptObjectData->field_11A;
  gta2::MissionScriptObjectData_sub_475B70(pMissionScriptObjectData, self->field_6, v1->arr_96[1]);
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x0047f920: MissionScriptObjectData::sub_47F920
// IDA: MissionScriptObjectData::sub_47F920
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47F920(struct MissionScriptObjectData *self)
{
  int *v1; // esi
  MissionManager *started; // edi
  __int16 v4; // si
  int *arr2_15; // eax
  char v6; // cl

  v1 = &dword_6644CC->arr_96[1];
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
  gta2::S63_sub_483C60((EventHandler *)started->arr_96[1], 174);
  gta2::MissionManager_sub_47F420(gMissionManager, *(_DWORD *)(started->arr_96[1] + 20));
  v4 = *(_WORD *)v1;
  arr2_15 = gMissionManager->arr2_15;
  v6 = 0;
  while ( *(_WORD *)arr2_15 != v4 )
  {
    arr2_15 = (int *)((char *)arr2_15 + 2);
    if ( (unsigned __int8)++v6 >= 0x1Fu )
    {
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
    }
  }
  unk_6646BC |= 1 << v6;
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047fac0: MissionScriptObjectData::sub_47FAC0
// IDA: MissionScriptObjectData::sub_47FAC0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_47FAC0(struct MissionScriptObjectData *self)
{
  MissionManager *v2; // esi
  MissionManager *started; // ebx
  int v4; // edx
  MissionManager *v5; // ecx
  int v6; // edx
  MissionManager *v7; // ecx
  int v8; // edx
  MissionManager *v9; // ecx
  int v10; // edx
  MissionManager *v11; // ecx
  int v12; // edx
  MissionManager *v13; // ecx
  int v14; // edx
  MissionManager *v15; // ecx
  const char *v16; // eax
  Gang *pGang; // ebp
  int v18; // eax
  char Id; // al
  _WORD *v20; // eax
  int v21; // ecx
  int v22; // eax
  int v23; // edx
  int v24; // ecx
  char v25; // al
  _WORD *v26; // eax
  char v27; // al
  char v28; // al
  MissionManager *v29; // [esp+10h] [ebp-14h]
  MissionManager *v30; // [esp+14h] [ebp-10h]
  MissionManager *v31; // [esp+18h] [ebp-Ch]
  MissionManager *v32; // [esp+1Ch] [ebp-8h]
  MissionManager *v33; // [esp+20h] [ebp-4h]

  v2 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
  v33 = gta2::MissionManager_StartMission(v5, *(_WORD *)(v4 + 16));
  v32 = gta2::MissionManager_StartMission(v7, *(_WORD *)(v6 + 12));
  v29 = gta2::MissionManager_StartMission(v9, *(_WORD *)(v8 + 18));
  v30 = gta2::MissionManager_StartMission(v11, *(_WORD *)(v10 + 20));
  v31 = gta2::MissionManager_StartMission(v13, *(_WORD *)(v12 + 22));
  v16 = (const char *)gta2::MissionManager_sub_474F00(v15, *(_WORD *)(v14 + 24));
  pGang = gta2::Gangs_GetGangByName(gGangs, v16 + 9);
  v18 = started->arr_96[1];
  if ( v18 >= 1 && !v32->arr_96[1] && !v29->arr_96[1] && !v30->arr_96[1] && !v31->arr_96[1]
    || (v21 = v33->arr_96[1], v21 >= 1) && !v32->arr_96[1] && !v29->arr_96[1] && !v30->arr_96[1] && !v31->arr_96[1] )
  {
    Id = gta2::Player_GetId(gGame->PlayerMain);
    if ( gta2::Gang_GetRespectForPlayer(pGang, Id) / 20 >= HIWORD(v2->arr_96[5]) )
    {
      gMissionManager->field_C1E2E = 0;
      v20 = gta2::MissionManager_sub_474F00(gMissionManager, HIWORD(v2->arr_96[2]));
      gta2::MissionScriptObjectData_sub_47ECE0(self, (int)dword_6644CC, (int)v20 + 9);
      return;
    }
    goto LABEL_31;
  }
  if ( v29->arr_96[1] >= 1 )
  {
    v22 = LOWORD(v2->arr_96[1]) - 5;
LABEL_19:
    strcpy(gStr, "%d", v22);
    gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
    gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
    return;
  }
  if ( v30->arr_96[1] == 1 )
  {
    v22 = LOWORD(v2->arr_96[1]) - 2;
    goto LABEL_19;
  }
  if ( v31->arr_96[1] == 1 )
  {
    v22 = LOWORD(v2->arr_96[1]) - 1;
    goto LABEL_19;
  }
  if ( v18 == 1 )
  {
    v23 = LOWORD(v2->arr_96[1]);
LABEL_30:
    strcpy(gStr, "%d", v23);
    gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
    gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
    return;
  }
  if ( v21 != 1 )
  {
    v25 = gta2::Player_GetId(gGame->PlayerMain);
    if ( gta2::Gang_GetRespectForPlayer(pGang, v25) / 20 >= HIWORD(v2->arr_96[5]) )
    {
      gMissionManager->field_C1E2E = 0;
      v26 = gta2::MissionManager_sub_474F00(gMissionManager, v2->arr_96[6]);
      gta2::MissionScriptObjectData_sub_47ECE0(self, (int)dword_6644CC, (int)v26 + 9);
      return;
    }
    v27 = gta2::Player_GetId(gGame->PlayerMain);
    if ( !(gta2::Gang_GetRespectForPlayer(pGang, v27) / 20) )
    {
      v24 = LOWORD(v2->arr_96[1]) - 6;
      goto LABEL_32;
    }
    v28 = gta2::Player_GetId(gGame->PlayerMain);
    if ( gta2::Gang_GetRespectForPlayer(pGang, v28) / 20 < 0 )
    {
      v23 = LOWORD(v2->arr_96[1]) - 4;
      goto LABEL_30;
    }
LABEL_31:
    v24 = LOWORD(v2->arr_96[1]) - 7;
    goto LABEL_32;
  }
  v24 = LOWORD(v2->arr_96[1]) + 1;
LABEL_32:
  strcpy(gStr, "%d", v24);
  gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x0047fe80: MissionScriptObjectData::SaveToGames
// IDA: MissionScriptObjectData::SaveToGames
// Ghidra: ---
void gta2::MissionScriptObjectData_SaveToGames(struct MissionScriptObjectData *self)
{
  MissionManager *MissionPtrMaybe; // eax
  char *SaveFile; // eax
  MissionManager *v4; // esi
  PublicTransport *v5; // ebx
  struct Ped *MainPed; // edi
  S202 *v7; // ebp
  void *XCoordinate; // eax
  Car *v9; // eax
  void *v10; // eax
  Car *v11; // eax
  SpriteS1 *v12; // [esp-10h] [ebp-20h]
  SpriteS1 *v13; // [esp-10h] [ebp-20h]
  int Y; // [esp+8h] [ebp-8h] BYREF
  int X; // [esp+Ch] [ebp-4h] BYREF

  if ( self->field_C )
  {
    v4 = dword_6644CC;
    v5 = (PublicTransport *)&dword_6644CC->arr_96[5];
    MainPed = gGame->PlayerMain->MainPed;
    v7 = (S202 *)&dword_6644CC->arr_96[2];
    gta2::Player_sub_401B40((Player *)&dword_6644CC->arr_96[2], (S202 *)&Y, (int)&dword_6644CC->arr_96[5]);
    XCoordinate = (void *)gta2::Ped_GetXCoordinate(MainPed, (int)&X);
    if ( gta2::sub_4037E0(XCoordinate)
      || (v12 = gta2::S202_sub_401B20(v7, (SpriteS1 *)&X, v5),
          v9 = (Car *)gta2::Ped_GetXCoordinate(MainPed, (int)&Y),
          gta2::Car_sub_403800(v9, (int)v12))
      && (gta2::Player_sub_401B40((Player *)&v4->arr_96[3], (S202 *)&X, (int)&v4->arr_96[6]),
          gta2::Ped_GetYCoordinate(MainPed, &Y),
          gta2::sub_4037E0(v10))
      || (v13 = gta2::S202_sub_401B20((S202 *)&v4->arr_96[3], (SpriteS1 *)&X, (PublicTransport *)&v4->arr_96[6]),
          gta2::Ped_GetYCoordinate(MainPed, &Y),
          gta2::Car_sub_403800(v11, (int)v13)) )
    {
      gta2::MissionScriptObjectData_sub_47A860(self, v4->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
    }
  }
  else
  {
    gta2::sub_478240(dword_6644CC->arr_96[1]);
    if ( gta2::General_GetCycle(gGeneral) )
    {
      MissionPtrMaybe = gMissionManager->MissionPtrMaybe;
      if ( !MissionPtrMaybe || *(_DWORD *)&MissionPtrMaybe->field_0 )
      {
        strcpy(gStr, "svmiss");
      }
      else if ( gta2::Player_GetMoneyPlayer(gGame->PlayerMain) < 50000 )
      {
        gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_DAMNATION__NO_DONATION__NO_SALVATION);
        strcpy(gStr, "svscore");
      }
      else
      {
        gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_HALLELUJAH__ANOTHER_SOUL_SAVED);
        gta2::Player_DecreaseInMoney(gGame->PlayerMain, -50000);
        SaveFile = gta2::MapGm_GetSaveFile(&gMapGm);
        gta2::MissionManager_SaveFile(gMissionManager, SaveFile);
        strcpy(gStr, "svdone");
      }
      gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
    }
    self->field_C = 1;
  }
}


// 0x00480080: MissionScriptObjectData::sub_480080
// IDA: MissionScriptObjectData::sub_480080
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_480080(struct MissionScriptObjectData *self)
{
  MissionManager *v2; // esi
  int v3; // edx
  MissionManager *v4; // ecx
  int v5; // edx
  MissionManager *v6; // ecx
  MissionManager *v7; // ebx
  int v8; // edx
  MissionManager *v9; // ecx
  int v10; // edx
  MissionManager *v11; // ecx
  int v12; // edx
  MissionManager *v13; // ecx
  const char *v14; // eax
  Gang *v15; // ebp
  int v16; // eax
  char Id; // al
  _WORD *v18; // eax
  char v19; // al
  int v20; // ecx
  char v21; // al
  MissionManager *v22; // [esp+10h] [ebp-10h]
  MissionManager *v23; // [esp+14h] [ebp-Ch]
  MissionManager *started; // [esp+18h] [ebp-8h]
  MissionManager *v25; // [esp+1Ch] [ebp-4h]

  v2 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
  v25 = gta2::MissionManager_StartMission(v4, *(_WORD *)(v3 + 16));
  v7 = gta2::MissionManager_StartMission(v6, *(_WORD *)(v5 + 18));
  v22 = gta2::MissionManager_StartMission(v9, *(_WORD *)(v8 + 20));
  v23 = gta2::MissionManager_StartMission(v11, *(_WORD *)(v10 + 22));
  v14 = (const char *)gta2::MissionManager_sub_474F00(v13, *(_WORD *)(v12 + 24));
  v15 = gta2::Gangs_GetGangByName(gGangs, v14 + 9);
  if ( v7->arr_96[1] == 1 )
  {
    v16 = LOWORD(v2->arr_96[1]) - 5;
LABEL_11:
    strcpy(gStr, "%d", v16);
    gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
    gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
    return;
  }
  if ( v22->arr_96[1] == 1 )
  {
    v16 = LOWORD(v2->arr_96[1]) - 2;
    goto LABEL_11;
  }
  if ( v23->arr_96[1] == 1 )
  {
    v16 = LOWORD(v2->arr_96[1]) - 1;
    goto LABEL_11;
  }
  if ( started->arr_96[1] == 1 )
  {
    v16 = LOWORD(v2->arr_96[1]);
    goto LABEL_11;
  }
  if ( v25->arr_96[1] == 1 )
  {
    v16 = LOWORD(v2->arr_96[1]) + 1;
    goto LABEL_11;
  }
  Id = gta2::Player_GetId(gGame->PlayerMain);
  if ( gta2::Gang_GetRespectForPlayer(v15, Id) / 20 >= HIWORD(v2->arr_96[5]) )
  {
    v18 = gta2::MissionManager_sub_474F00(gMissionManager, v2->arr_96[6]);
    gta2::MissionScriptObjectData_sub_47ECE0(self, (int)dword_6644CC, (int)v18 + 9);
    return;
  }
  v19 = gta2::Player_GetId(gGame->PlayerMain);
  if ( gta2::Gang_GetRespectForPlayer(v15, v19) / 20 )
  {
    v21 = gta2::Player_GetId(gGame->PlayerMain);
    if ( gta2::Gang_GetRespectForPlayer(v15, v21) / 20 < 0 )
    {
      strcpy(gStr, "%d", LOWORD(v2->arr_96[1]) - 4);
      gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
    }
    v20 = LOWORD(v2->arr_96[1]) - 7;
  }
  else
  {
    v20 = LOWORD(v2->arr_96[1]) - 6;
  }
  strcpy(gStr, "%d", v20);
  gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
  gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
}


// 0x00480430: MissionScriptObjectData::sub_480430
// IDA: MissionScriptObjectData::sub_480430
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_480430(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // esi
  MissionManager *pMissionManager; // edi
  wchar_t *v4; // eax
  unsigned __int16 v5; // di
  MissionManager *started; // eax
  MissionManager *v7; // eax
  unsigned __int8 v8; // cl
  int v9; // esi
  Car *CarPlayers; // eax
  int *arr_12; // eax
  __int16 v12; // cx
  WeaponType v13; // [esp-4h] [ebp-10h]

  v1 = dword_6644CC;
  pMissionManager = gMissionManager;
  if ( gta2::MissionManager_sub_475A30(gMissionManager) )
  {
    gta2::MissionScriptObjectData_sub_47A860(self, v1->arr_96[1]);
    gta2::MissionScriptObjectData_sub_478610(self);
  }
  else
  {
    gta2::MissionManager_sub_475A40(pMissionManager, 1);
    gta2::sub_478240(v1->arr_96[1]);
    v4 = gta2::Text__Bsearch(gText, "kfstart");
    gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v4, 3);
    gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_KILL_FRENZY);
    v5 = v1->arr_96[2];
    started = gta2::MissionManager_StartMission(gMissionManager, v5);
    if ( gta2::MissionScriptObjectData_sub_475010(self, started->field_2) == 3 )
      gta2::MissionScriptObjectData_sub_47F760(self, v5);
    strcpy(gStr, "%d", HIWORD(v1->arr_96[1]));
    gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
    v7 = gta2::MissionManager_StartMission(gMissionManager, HIWORD(v1->arr_96[2]));
    v8 = v1->arr_96[3];
    if ( v8 < 0xFu || v8 > 0x1Bu )
    {
      if ( v8 != 28 )
        gta2::sub_4A52B0(*(void **)(v7->arr_96[1] + 348), LOBYTE(v1->arr_96[3]));
    }
    else
    {
      v9 = v7->arr_96[1];
      v13 = v8;
      CarPlayers = gta2::Ped_GetCarPlayers((Ped *)v9);
      gta2::Player_sub_4A5220(*(Player **)(v9 + 348), CarPlayers, v13);
    }
    arr_12 = gMissionManager->arr_12;
    v12 = 0;
    while ( *(_WORD *)arr_12 != dword_6644CC->field_0 )
    {
      arr_12 = (int *)((char *)arr_12 + 2);
      if ( (unsigned __int16)++v12 >= 0x19u )
      {
        gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
        return;
      }
    }
    unk_6646C0 |= 1 << v12;
    gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
  }
}


// 0x004805b0: MissionScriptObjectData::sub_4805B0
// IDA: MissionScriptObjectData::sub_4805B0
// Ghidra: ---
void gta2::MissionScriptObjectData_sub_4805B0(struct MissionScriptObjectData *self)
{
  unsigned __int16 v1; // ax
  MissionManager *v2; // ecx
  MissionManager *v3; // eax
  char v4; // cl
  __int16 v5; // cx
  MissionManager *v6; // ecx
  MissionManager *v7; // eax
  unsigned int v8; // ecx
  MissionScriptObjectData *v9; // esi
  MissionManager *v10; // ebx
  MissionScriptObjectData *v11; // edi
  MissionManager *v12; // eax
  MissionScriptObjectData *v13; // ecx
  __int16 v14; // dx
  char v15; // al
  MissionScriptObjectData *pS28_2; // esi
  Viewport *v17; // eax
  MissionManager *v18; // edi
  MissionManager *v19; // esi
  MissionManager *v20; // edi
  MissionScriptObjectData *pS28_1; // edx
  MissionManager *v22; // ebx
  MissionManager *v23; // esi
  MissionManager *v24; // ecx
  MissionManager *v25; // edi
  char v26; // al
  MissionScriptObjectData *pS28_4; // edx
  MissionManager *v28; // edi
  __int16 v29; // ax
  __int16 v30; // ax
  MissionManager *v31; // esi
  MissionManager *v32; // eax
  int v33; // ecx
  MissionScriptObjectData *pS28_5; // edx
  MissionManager *v35; // esi
  MissionManager *v36; // eax
  int v37; // ecx
  MissionScriptObjectData *pS28_6; // edx
  MissionManager *v39; // esi
  MissionScriptObjectData *v40; // edi
  int *v41; // ebx
  MissionManager *v42; // ebp
  int *MaxZForLocation; // eax
  MissionManager *v44; // ebx
  MissionScriptObjectData *pS28_7; // ebx
  MissionManager *v46; // eax
  MissionManager *v47; // esi
  Car *v48; // edi
  MissionManager *pMissionManager46; // esi
  MissionScriptObjectData *pS28_8; // edi
  _WORD *v51; // eax
  unsigned __int16 v52; // cx
  MissionManager *v53; // ebp
  MissionScriptObjectData *pS28_9; // ebx
  MissionManager *v55; // ecx
  MissionManager *v56; // edi
  MissionManager *v57; // esi
  struct HudArrow *HudArrow; // eax
  int pPed_1; // esi
  char Id; // bl
  EventHandler *v61; // eax
  int v62; // ecx
  int v63; // edx
  MissionManager *v64; // ebx
  MissionScriptObjectData *pS28_10; // edi
  MissionManager *v66; // eax
  MissionManager *v67; // esi
  MissionManager *v68; // edi
  void *v69; // ecx
  struct Ped *v70; // ecx
  MissionManager *v71; // esi
  MissionManager *v72; // ecx
  MissionManager *v73; // eax
  int v74; // edx
  struct Ped *v75; // esi
  void *v76; // edi
  Car *v77; // eax
  Car *v78; // ecx
  int v79; // ecx
  Car *pCar3_1; // esi
  Car *pCar_2; // esi
  Car *v82; // ecx
  int v83; // edx
  int v84; // edx
  MissionManager *v85; // esi
  char v86; // al
  MissionScriptObjectData *v87; // edi
  __int16 v88; // ax
  wchar_t *v89; // eax
  MissionScriptObjectData *v90; // esi
  int v91; // edx
  MissionManager *v92; // edi
  __int16 v93; // ax
  MissionScriptObjectData *pMissionManager37; // esi
  MissionManager *v95; // edi
  int v96; // edx
  MissionManager *v97; // esi
  MissionScriptObjectData *v98; // edi
  MissionManager *v99; // eax
  MissionScriptObjectData *v100; // esi
  MissionManager *v101; // eax
  void *v102; // edx
  struct Ped *v103; // ecx
  int _450CB0; // eax
  int v105; // eax
  struct Ped *v106; // ecx
  struct Ped *v107; // ecx
  MissionManager *v108; // ebx
  MissionScriptObjectData *v109; // edi
  MissionManager *v110; // eax
  struct Ped *v111; // esi
  Car *CarPlayers; // eax
  MissionManager *v113; // eax
  struct Ped *v114; // esi
  MissionManager *pMissionManager11; // ebx
  MissionManager *v116; // edi
  MissionScriptObjectData *pMissionManager13; // ebp
  MissionManager *v118; // eax
  int v119; // esi
  MissionManager *v120; // eax
  MissionManager *v121; // edi
  MissionScriptObjectData *v122; // esi
  struct Ped *v123; // ecx
  struct Player *v124; // eax
  MissionScriptObjectData *v125; // esi
  MissionManager *v126; // ecx
  int v127; // eax
  MissionManager *v128; // eax
  MissionScriptObjectData *v129; // esi
  int v130; // ecx
  unsigned __int16 v131; // dx
  MissionManager *v132; // eax
  MissionManager *v133; // eax
  struct Ped *v134; // ecx
  MissionManager *v135; // esi
  int v136; // eax
  MissionScriptObjectData *v137; // edx
  int v138; // eax
  MissionManager *v139; // esi
  MissionScriptObjectData *v140; // edi
  int v141; // eax
  MissionManager *v142; // eax
  __int16 v143; // dx
  __int16 v144; // dx
  MissionManager *v145; // eax
  __int16 v146; // dx
  __int16 v147; // dx
  MissionScriptObjectData *v148; // esi
  MissionScriptObjectData *v149; // esi
  MissionManager *v150; // ebx
  MissionScriptObjectData *v151; // ebp
  const char *v152; // eax
  const char *v153; // esi
  Gang *pGang1; // edi
  const char *v155; // esi
  Gang *v156; // esi
  MissionManager *v157; // esi
  MissionScriptObjectData *v158; // ebp
  const char *v159; // eax
  Gangs *pGang; // edi
  MissionManager *v161; // eax
  MissionManager *v162; // ecx
  char v163; // al
  __int16 v164; // ax
  char v165; // al
  char v166; // al
  char v167; // al
  MissionScriptObjectData *v168; // ebp
  MissionManager *v169; // edi
  MissionManager *v170; // eax
  MissionManager *v171; // edx
  MissionManager *v172; // ebx
  struct Ped *v173; // esi
  char v174; // al
  MissionScriptObjectData *v175; // esi
  MissionManager *v176; // esi
  MissionScriptObjectData *v177; // ebx
  MissionManager *v178; // edi
  MissionManager *v179; // eax
  MissionManager *v180; // ecx
  MissionManager *v181; // eax
  int v182; // edx
  MissionManager *v183; // ebp
  EventHandler *pS63; // ecx
  int v185; // eax
  __int16 v186; // di
  MissionScriptObjectData *v187; // esi
  MissionManager *pMissionManager; // edi
  MissionManager *v189; // ebx
  MissionManager *v190; // ecx
  char *v191; // eax
  int v192; // edx
  __int16 v193; // bp
  MissionManager *v194; // eax
  MissionManager *pMissionManager1; // esi
  MissionManager *v196; // eax
  MissionManager *v197; // ecx
  MissionManager *v198; // edi
  int v199; // eax
  int *v200; // eax
  int v201; // esi
  char v202; // al
  MissionScriptObjectData *v203; // esi
  MissionManager *v204; // eax
  MissionScriptObjectData *v205; // esi
  MissionManager *v206; // edi
  int v207; // edx
  MissionManager *v208; // ecx
  MissionManager *v209; // eax
  MissionManager *v210; // edx
  void *v211; // ecx
  MissionManager *v212; // ebx
  Car *v213; // eax
  MissionScriptObjectData *v214; // ebx
  MissionManager *v215; // esi
  int v216; // edx
  MissionManager *v217; // ecx
  MissionManager *v218; // eax
  MissionManager *v219; // edx
  struct Ped *v220; // ecx
  MissionManager *v221; // edi
  MissionManager *v222; // esi
  struct Ped *v223; // ecx
  MissionManager *v224; // eax
  MissionManager *v225; // esi
  Car *v226; // edi
  MissionScriptObjectData *v227; // esi
  MissionScriptObjectData *v228; // edi
  MissionManager *v229; // esi
  MissionManager *v230; // eax
  int v231; // esi
  int MoneyPlayer; // eax
  int v233; // edx
  MissionManager *v234; // ebx
  MissionScriptObjectData *v235; // edi
  int v236; // edx
  MissionManager *v237; // esi
  MissionManager *v238; // ecx
  const char *v239; // eax
  Gang *v240; // eax
  int pPed; // esi
  Gang *v242; // ebx
  Weapon *pWeapon; // eax
  Weapon *XCoordinate; // eax
  unsigned __int8 v245; // al
  char *v246; // eax
  Car *pCar_3; // ecx
  unsigned __int16 v248; // ax
  MissionScriptObjectData *v249; // esi
  MissionManager *v250; // edi
  MissionManager *v251; // eax
  MissionManager *v252; // edx
  int v253; // eax
  MissionManager *v254; // edi
  MissionScriptObjectData *v255; // esi
  MissionManager *v256; // eax
  MissionManager *v257; // eax
  int v258; // edx
  MissionManager *v259; // esi
  byte *v260; // edi
  MissionManager *v261; // esi
  MissionScriptObjectData *v262; // edi
  MissionManager *v263; // eax
  MissionScriptObjectData *pS28_11; // esi
  MissionManager *v265; // eax
  MissionManager *v266; // edx
  int v267; // ecx
  int v268; // eax
  MissionManager *v269; // eax
  S169 *v270; // eax
  MissionManager *v271; // esi
  MissionScriptObjectData *v272; // edi
  MissionManager *v273; // eax
  S169 *v274; // eax
  MissionScriptObjectData *pMissionManager10; // esi
  int v276; // edi
  MissionManager *v277; // edx
  MissionScriptObjectData *v278; // esi
  MissionManager *v279; // eax
  int v280; // edx
  struct Ped *pPed1; // esi
  Car *pCar; // eax
  MissionManager *v283; // ebx
  MissionScriptObjectData *v284; // edi
  struct Ped *pPed2; // esi
  Car *pCar1; // eax
  MissionManager *v287; // ecx
  MissionManager *v288; // ecx
  MissionScriptObjectData *pMissionManager27; // esi
  int v290; // edx
  MissionManager *v291; // edi
  MissionManager *v292; // ecx
  MissionManager *v293; // eax
  SpriteS1 *pSpriteS1; // eax
  MissionManager *v295; // eax
  unsigned __int16 v296; // cx
  MissionManager *v297; // edi
  MissionScriptObjectData *v298; // esi
  MissionManager *v299; // eax
  MissionManager *v300; // edi
  MissionScriptObjectData *v301; // esi
  MissionManager *v302; // eax
  struct Ped *pPed_2; // esi
  MissionManager *v304; // esi
  MissionScriptObjectData *v305; // esi
  MissionManager *v306; // eax
  bool v307; // al
  MissionManager *v308; // edi
  MissionScriptObjectData *v309; // esi
  MissionManager *v310; // eax
  MissionScriptObjectData *v311; // esi
  int v312; // edx
  MissionManager *v313; // edi
  MissionManager *v314; // ecx
  const char *v315; // eax
  Gang *v316; // eax
  MissionScriptObjectData *pMissionManager14; // esi
  int v318; // edx
  MissionManager *v319; // ecx
  MissionManager *v320; // eax
  MissionManager *pMissionManager2; // ebx
  MissionManager *v322; // edi
  MissionScriptObjectData *v323; // esi
  MissionManager *v324; // eax
  MissionManager *v325; // eax
  int v326; // edx
  MissionManager *v327; // ebx
  MissionManager *pMissionManager3; // ebp
  unsigned __int16 v329; // ax
  MissionManager *v330; // esi
  void *v331; // edi
  int v332; // eax
  int v333; // eax
  MissionManager *v334; // ebp
  MissionManager *v335; // ebp
  MissionManager *v336; // ebp
  MissionScriptObjectData *pMissionManager26; // esi
  MissionManager *v338; // eax
  int v339; // edx
  int pPed3; // esi
  MissionScriptObjectData *v341; // esi
  MissionScriptObjectData *v342; // esi
  MissionScriptObjectData *v343; // esi
  unsigned __int8 v344; // dl
  unsigned __int8 v345; // al
  MissionScriptObjectData *pS28_12; // edi
  int v347; // edx
  MissionManager *v348; // esi
  _BYTE *v349; // esi
  MissionManager *v350; // edi
  MissionScriptObjectData *pMissionManager15; // ebp
  int *v352; // ebx
  MissionManager *v353; // esi
  __int16 v354; // bx
  MissionScriptObjectData *v355; // esi
  MissionManager *v356; // eax
  int v357; // edx
  bool v358; // al
  MissionScriptObjectData *v359; // esi
  MissionScriptObjectData *v360; // edi
  int v361; // edx
  MissionManager *v362; // esi
  MissionManager *pMissionManager4; // ecx
  MissionManager *v364; // ebx
  MissionManager *v365; // eax
  MissionManager *v366; // esi
  MissionScriptObjectData *v367; // edi
  MissionManager *v368; // eax
  MissionManager *v369; // esi
  MissionScriptObjectData *v370; // edi
  MissionManager *v371; // eax
  MissionManager *v372; // esi
  MissionScriptObjectData *v373; // edi
  MissionManager *v374; // eax
  MissionManager *v375; // esi
  MissionScriptObjectData *v376; // ebp
  MissionManager *v377; // eax
  unsigned int v378; // ecx
  int v379; // edi
  int v380; // edi
  PlayerStats *Money; // eax
  int v382; // edi
  int v383; // edi
  MissionScriptObjectData *v384; // esi
  struct Ped *v385; // esi
  struct Ped *v386; // esi
  unsigned __int16 v387; // ax
  bool v388; // zf
  MissionManager *v389; // edi
  MissionScriptObjectData *v390; // esi
  MissionScriptObjectData *v391; // esi
  int v392; // eax
  S900 *v393; // eax
  MissionScriptObjectData *v394; // esi
  unsigned __int16 v395; // dx
  MissionManager *v396; // eax
  MissionManager *v397; // esi
  int v398; // ecx
  MissionScriptObjectData *pMissionManager16; // edx
  MissionScriptObjectData *v400; // esi
  MissionManager *v401; // eax
  int v402; // edx
  MissionManager *v403; // eax
  int v404; // ecx
  int v405; // eax
  MissionManager *v406; // edi
  MissionScriptObjectData *v407; // esi
  MissionManager *v408; // eax
  MissionManager *v409; // eax
  Car *pCar_1; // ecx
  Car *v411; // ecx
  Car *pCar2; // ecx
  int v413; // edx
  MissionManager *v414; // edi
  MissionManager *pMissionManager5; // ecx
  MissionManager *v416; // eax
  SpriteS1 *v417; // esi
  bool v418; // al
  int v419; // ecx
  SpriteS1 *pSpriteS1_2; // ecx
  MissionScriptObjectData *v421; // esi
  MissionManager *v422; // edi
  MissionScriptObjectData *v423; // esi
  MissionManager *v424; // eax
  unsigned __int8 CopStars; // al
  MissionScriptObjectData *v426; // esi
  _DWORD *v427; // eax
  MissionManager *v428; // edi
  MissionScriptObjectData *v429; // esi
  MissionManager *v430; // eax
  MissionScriptObjectData *pMissionManager7; // esi
  MissionScriptObjectData *pS28_22; // esi
  int v433; // edx
  MissionManager *v434; // eax
  S169 *v435; // eax
  struct Ped *pPed4; // ecx
  S32 *pS32; // ecx
  MissionManager *v438; // eax
  int v439; // ecx
  MissionManager *v440; // edi
  MissionScriptObjectData *pMissionManager18; // ebp
  MissionManager *v442; // eax
  MissionManager *v443; // edx
  int v444; // eax
  int v445; // ecx
  int v446; // ecx
  struct Ped *pPed5; // esi
  Car *pCar6; // eax
  MissionManager *v449; // eax
  struct Ped *v450; // edi
  Car *v451; // eax
  struct Ped *pPed6; // ecx
  MissionScriptObjectData *pMissionManager21; // esi
  Car *pCar_4; // ecx
  MissionScriptObjectData *pMissionManager45; // esi
  void *v456; // ecx
  void *v457; // ecx
  void *v458; // ecx
  struct Player *v459; // ecx
  MissionManager *v460; // eax
  int v461; // eax
  MissionScriptObjectData *pMissionManager23; // edi
  MissionManager *v463; // eax
  int v464; // edx
  int pWeaponType1; // ecx
  struct Ped *pPed7; // esi
  Car *pCar7; // eax
  MissionScriptObjectData *pMissionManager24; // esi
  MissionManager *v469; // eax
  MissionScriptObjectData *pMissionManager25; // esi
  int v471; // edx
  MissionManager *v472; // edi
  MissionManager *v473; // ecx
  MissionManager *v474; // eax
  MissionManager *v475; // eax
  int v476; // edx
  unsigned __int16 v477; // ax
  S166 *p_S166; // ecx
  MissionManager *v479; // edi
  MissionScriptObjectData *pMissionManager28; // esi
  S169 *pPed8; // ecx
  MissionManager *pMissionManager42; // edi
  MissionManager *v483; // eax
  int v484; // eax
  MissionManager *pMissionManager40; // esi
  MissionScriptObjectData *pMissionManager29; // edi
  MissionManager *v487; // eax
  MissionManager *pMissionManager31; // ecx
  MissionManager *v489; // ebx
  MissionManager *v490; // ebx
  MissionManager *v491; // ebx
  MissionManager *pMissionManager33; // ecx
  MissionManager *v493; // eax
  unsigned __int16 *v494; // ebp
  unsigned __int16 v495; // cx
  MissionManager *pMissionManager30; // ebp
  MissionManager *v497; // edi
  MissionManager *v498; // eax
  int v499; // edx
  struct Ped *pPed_3; // esi
  MissionManager *pMissionManager41; // ecx
  wchar_t *v502; // eax
  __int16 v503; // ax
  wchar_t *v504; // eax
  MissionScriptObjectData *pMissionManager34; // esi
  MissionScriptObjectData *pMissionManager35; // esi
  unsigned __int16 v507; // cx
  MissionManager *v508; // eax
  MissionManager *v509; // edx
  __int16 v510; // ax
  MissionManager *v511; // esi
  char v512; // al
  Gang *pGang_1; // eax
  MissionScriptObjectData *v514; // esi
  MissionManager *v515; // eax
  int v516; // edx
  unsigned __int16 v517; // cx
  int v518; // ecx
  int v519; // ecx
  bool IsPlayerDriving; // al
  Car *v521; // eax
  int Mask; // ecx
  bool v523; // zf
  int v524; // ecx
  int v525; // ecx
  MissionManager *v526; // edi
  MissionScriptObjectData *v527; // esi
  _WORD *v528; // eax
  MissionScriptObjectData *v529; // esi
  char *SaveFile; // eax
  MissionScriptObjectData *pS28_20; // esi
  int v532; // edx
  MissionScriptObjectData *pMissionManager9; // ebp
  MissionManager *v534; // ebx
  int v535; // edx
  MissionManager *v536; // esi
  MissionManager *pMissionManager8; // ecx
  MissionManager *v538; // edi
  struct Ped *Ped; // eax
  Car *pCar3; // ecx
  MissionManager *v541; // edi
  Car *v542; // esi
  Car *carLights; // ecx
  MissionScriptObjectData *v544; // ebx
  int v545; // ebp
  MissionScriptObjectData *v546; // edi MAPDST
  int v547; // esi
  MissionManager *started; // eax
  MissionScriptObjectData *pMissionScriptObjectData; // edx
  MissionScriptObjectData *pS28_3; // ecx
  MissionScriptObjectData *v551; // esi
  MissionScriptObjectData *v552; // ecx
  MissionScriptObjectData *v553; // ecx
  MissionScriptObjectData *v554; // ecx
  MissionScriptObjectData *v555; // ecx
  MissionScriptObjectData *v556; // esi
  MissionScriptObjectData *v557; // ecx
  MissionScriptObjectData *v558; // esi
  MissionScriptObjectData *MissionManager36; // ecx
  MissionScriptObjectData *MissionManager39; // esi
  int v561; // [esp-2Ch] [ebp-34h]
  unsigned __int8 v562; // [esp-2Ch] [ebp-34h]
  int v563; // [esp-2Ch] [ebp-34h]
  unsigned __int16 v564; // [esp-28h] [ebp-30h]
  char v565; // [esp-28h] [ebp-30h]
  unsigned __int16 v566; // [esp-28h] [ebp-30h]
  __int16 v567; // [esp-28h] [ebp-30h]
  int v568; // [esp-28h] [ebp-30h]
  SpriteS1 *pS9; // [esp-28h] [ebp-30h]
  char v570; // [esp-24h] [ebp-2Ch]
  unsigned __int8 v571; // [esp-24h] [ebp-2Ch]
  AudioSourceParams *v572; // [esp-24h] [ebp-2Ch]
  MissionManager *v573; // [esp-20h] [ebp-28h]
  MissionManager *v574; // [esp-20h] [ebp-28h]
  char v575; // [esp-20h] [ebp-28h]
  char v576; // [esp-20h] [ebp-28h]
  unsigned __int8 v577; // [esp-20h] [ebp-28h]
  char v578; // [esp-20h] [ebp-28h]
  unsigned __int8 v579; // [esp-20h] [ebp-28h]
  unsigned __int16 Index; // [esp-20h] [ebp-28h]
  MissionManager *v581; // [esp-1Ch] [ebp-24h]
  ALL_PED v582; // [esp-1Ch] [ebp-24h]
  int v583; // [esp-1Ch] [ebp-24h]
  int v584; // [esp-1Ch] [ebp-24h]
  MissionManager *v585; // [esp-1Ch] [ebp-24h]
  char v586; // [esp-1Ch] [ebp-24h]
  MissionManager *v588; // [esp-1Ch] [ebp-24h]
  MissionManager *v589; // [esp-1Ch] [ebp-24h]
  void *v590; // [esp-1Ch] [ebp-24h]
  unsigned __int8 v591; // [esp-1Ch] [ebp-24h]
  int v592; // [esp-1Ch] [ebp-24h]
  int v593; // [esp-1Ch] [ebp-24h]
  MissionManager *v594; // [esp-1Ch] [ebp-24h]
  WeaponType pWeaponType; // [esp-1Ch] [ebp-24h]
  MissionManager *v596; // [esp-1Ch] [ebp-24h]
  int Index_1; // [esp-18h] [ebp-20h] BYREF
  MissionScriptObjectData *pS28Arr[5]; // [esp-14h] [ebp-1Ch] BYREF
  MissionManager *v599; // [esp+Ch] [ebp+4h]

  if ( self->field_10 == 1 )
    return;
  started = gta2::MissionManager_StartMission(gMissionManager, self->field_4);
  dword_6644CC = started;
  switch ( started->field_2 )
  {
    case 0x29u:
    case 0x2Au:
      Index_1 = (int)v546;
      pMissionManager37 = pMissionScriptObjectData;
      v95 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_477560(pMissionManager37, v96);
      if ( !pMissionManager37->field_118 )
        gta2::S31_CreatePed2(gTrafficManager, (Ped *)v95->arr_96[1]);
      goto LABEL_789;
    case 0x2Bu:
    case 0x2Cu:
    case 0x2Du:
    case 0x2Eu:
    case 0x18Au:
    case 0x18Bu:
    case 0x18Cu:
    case 0x18Du:
      pS28Arr[0] = pMissionScriptObjectData;
      v39 = dword_6644CC;
      v40 = pMissionScriptObjectData;
      v41 = &dword_6644CC->arr_96[4];
      v42 = dword_6644CC;
      if ( gta2::Player_IsCurrentPlayer((Player *)&dword_6644CC->arr_96[4], (Player *)&unk_664F58) )
      {
        MaxZForLocation = gta2::MapRelatedStruct_FindMaxZForLocation(
                            gMapRelatedStruct,
                            (int *)pS28Arr,
                            (int *)v39->arr_96[2],
                            (S202 *)v39->arr_96[3]);
        v39 = dword_6644CC;
        *v41 = *MaxZForLocation;
      }
      v44 = gta2::MissionManager_StartMission(gMissionManager, v42->arr_96[1]);
      gta2::MissionScriptObjectData_sub_477290(v40, (int)v39);
      if ( !v40->field_118 )
        gta2::TrafficManager_sub_474EA0(gTrafficManager, v44->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v40, dword_6644CC);
      return;
    case 0x2Fu:
    case 0x30u:
    case 0x31u:
    case 0x32u:
    case 0x33u:
    case 0x34u:
      gta2::MissionScriptObjectDatar_sub_478A80(pMissionScriptObjectData);
      return;
    case 0x3Bu:
      v9 = pMissionScriptObjectData;
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_AND_REMEMBER__RESPECT_IS_EVERYTHING);
      Index_1 = (int)dword_6644CC;
      v9->field_118 = 1;
      gta2::MissionScriptObjectData_sub_476E50(v9, (MissionManager *)Index_1);
      return;
    case 0x3Cu:
      pMissionScriptObjectData->field_118 = 0;
      gta2::MissionScriptObjectData_sub_4751E0(pMissionScriptObjectData);
      return;
    case 0x3Du:
      gta2::MissionScriptObjectData_sub_47F890(pMissionScriptObjectData);
      return;
    case 0x3Eu:
      pS28Arr[0] = pMissionScriptObjectData;
      v10 = dword_6644CC;
      v11 = pMissionScriptObjectData;
      v12 = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
      if ( v12->field_2 == 24 )
      {
        v13 = (MissionScriptObjectData *)v12->arr_96[1];
        v14 = v12->arr_96[2];
        LOWORD(v12->arr_96[2]) = 0;
        v12->arr_96[1] = 0;
      }
      else if ( v12->field_2 <= 0xD2u || v12->field_2 > 0xD6u )
      {
        v13 = pS28Arr[0];
        v14 = (__int16)pS28Arr[0];
      }
      else
      {
        v13 = (MissionScriptObjectData *)v12->arr_96[1];
        v14 = v12->arr_96[2];
        v12->arr_96[1] = 0;
        LOWORD(v12->arr_96[2]) = 0;
      }
      if ( v13->field_11A == v14 )
        gta2::sub_4751D0(v13);
      goto LABEL_167;
    case 0x3Fu:
      pS28_3 = pMissionScriptObjectData;
      v29 = pMissionScriptObjectData->field_12;
      if ( v29 <= 0 )
        pMissionScriptObjectData->field_12 = v29 + 1;
      goto LABEL_206;
    case 0x40u:
      pS28_3 = pMissionScriptObjectData;
      v30 = pMissionScriptObjectData->field_12;
      if ( v30 >= 0 )
        pMissionScriptObjectData->field_12 = v30 - 1;
      goto LABEL_206;
    case 0x44u:
    case 0x111u:
      gta2::MissionScriptObjectData_sub_478610(pMissionScriptObjectData);
      return;
    case 0x47u:
      v388 = pMissionScriptObjectData->field_8 == 0;
      pS28Arr[0] = (MissionScriptObjectData *)dword_6644CC;
      pMissionScriptObjectData->field_8 = v388;
      gta2::MissionScriptObjectData_sub_476E50(pMissionScriptObjectData, (MissionManager *)pS28Arr[0]);
      return;
    case 0x4Eu:
      pS28_2 = pMissionScriptObjectData;
      Index_1 = (int)v546;
      v17 = (Viewport *)gta2::S29_sub_476DF0(pMissionScriptObjectData->S29_);
      v18 = dword_6644CC;
      v17->Data1 = pS28_2->field_8;
      v17->Data2 = v18->arr_96[0];
      gta2::S29_sub_474FB0(pS28_2->S29_, v17);
      gta2::MissionScriptObjectData_sub_476E80(pS28_2, v18->arr_96[1]);
      return;
    case 0x4Fu:
    case 0x52u:
    case 0x56u:
    case 0x58u:
    case 0x5Au:
    case 0x5Cu:
    case 0x5Eu:
      v19 = dword_6644CC;
      Index_1 = (int)v546;
      v20 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      switch ( gta2::sub_475700(v19->field_2) )
      {
        case 0:
          pS28_1->field_8 = v20->arr_96[1] + SHIWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 1:
          pS28_1->field_8 = v20->arr_96[1] - SHIWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 2:
          pS28_1->field_8 = v20->arr_96[1] > SHIWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 3:
          pS28_1->field_8 = v20->arr_96[1] >= SHIWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 4:
          pS28_1->field_8 = v20->arr_96[1] < SHIWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 5:
          pS28_1->field_8 = v20->arr_96[1] <= SHIWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 6:
          pS28_1->field_8 = v20->arr_96[1] == SHIWORD(v19->arr_96[1]);
          goto LABEL_183;
        default:
          goto LABEL_183;
      }
      return;
    case 0x50u:
    case 0x53u:
      v19 = dword_6644CC;
      Index_1 = (int)v546;
      v28 = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
      switch ( gta2::sub_475700(v19->field_2) )
      {
        case 0:
          pS28_1->field_8 = v28->arr_96[1] + SLOWORD(v19->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 1:
          pS28_1->field_8 = SLOWORD(v19->arr_96[1]) - v28->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 2:
          pS28_1->field_8 = SLOWORD(v19->arr_96[1]) > v28->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 3:
          pS28_1->field_8 = SLOWORD(v19->arr_96[1]) >= v28->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 4:
          pS28_1->field_8 = SLOWORD(v19->arr_96[1]) < v28->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 5:
          pS28_1->field_8 = SLOWORD(v19->arr_96[1]) <= v28->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
        case 6:
          pS28_1->field_8 = SLOWORD(v19->arr_96[1]) == v28->arr_96[1];
          goto LABEL_183;
        default:
LABEL_183:
          gta2::MissionScriptObjectData_sub_476E50(pS28_1, v19);
          break;
      }
      return;
    case 0x51u:
    case 0x54u:
    case 0x57u:
    case 0x59u:
    case 0x5Bu:
    case 0x5Du:
    case 0x5Fu:
      v22 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v23 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v25 = gta2::MissionManager_StartMission(v24, HIWORD(v22->arr_96[1]));
      v26 = gta2::sub_475700(v22->field_2);
      switch ( v26 )
      {
        case 0:
          pS28_4->field_8 = v23->arr_96[1] + v25->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
        case 1:
          pS28_4->field_8 = v23->arr_96[1] - v25->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
        case 2:
          pS28_4->field_8 = v23->arr_96[1] > v25->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
        case 3:
          pS28_4->field_8 = v23->arr_96[1] >= v25->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
        case 4:
          pS28_4->field_8 = v23->arr_96[1] < v25->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
        case 5:
          pS28_4->field_8 = v23->arr_96[1] <= v25->arr_96[1];
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
        case 6:
          pS28_4->field_8 = v23->arr_96[1] == v25->arr_96[1];
          goto LABEL_192;
        default:
LABEL_192:
          gta2::MissionScriptObjectData_sub_476E50(pS28_4, v22);
          break;
      }
      return;
    case 0x60u:
      v31 = dword_6644CC;
      v32 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v33 = v32->arr_96[1];
      Index_1 = (int)v31;
      v32->arr_96[1] = v33 + 1;
      gta2::MissionScriptObjectData_sub_476E50(pS28_5, (MissionManager *)Index_1);
      return;
    case 0x61u:
      v35 = dword_6644CC;
      v36 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v37 = v36->arr_96[1];
      Index_1 = (int)v35;
      v36->arr_96[1] = v37 - 1;
      gta2::MissionScriptObjectData_sub_476E50(pS28_6, (MissionManager *)Index_1);
      return;
    case 0x62u:
      pS28_3 = pMissionScriptObjectData;
      v15 = dword_6644CC->arr_96[1];
      if ( (v15 != 1 || !pMissionScriptObjectData->field_8) && (v15 || pMissionScriptObjectData->field_8) )
LABEL_206:
        gta2::MissionScriptObjectData_sub_476E50(pS28_3, dword_6644CC);
      else
        gta2::MissionScriptObjectData_sub_476E80(pMissionScriptObjectData, HIWORD(dword_6644CC->arr_96[1]));
      return;
    case 0x64u:
      pS28_7 = pMissionScriptObjectData;
      Index_1 = (int)pS28Arr[0];
      v46 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v47 = v46;
      v48 = (Car *)v46->arr_96[1];
      if ( v48 )
      {
        if ( !gta2::Car_GetDriver((Car *)v46->arr_96[1]) )
          gta2::Car_CarPutDummyDriverIn(v48);
        gta2::Car_CarMakeDummy((Car *)v47->arr_96[1]);
        gta2::Car_CarMakeDriveable1((Car *)v47->arr_96[1], SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
      }
      goto LABEL_828;
    case 0x67u:
    case 0x68u:
    case 0x69u:
    case 0x6Au:
    case 0x6Bu:
    case 0x6Cu:
    case 0x6Du:
    case 0x6Eu:
    case 0x6Fu:
    case 0x70u:
    case 0x174u:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      v51 = gta2::MissionManager_sub_474F00(gMissionManager, dword_6644CC->arr_96[1]);
      *(_DWORD *)&v52 = pMissionManager46->field_2;
      if ( v52 > 0x174u )
        goto LABEL_729;
      if ( v52 == 372 )
      {
        gta2::MapRelatedStruct_sub_462D60(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
        pMissionManager46 = dword_6644CC;
        goto LABEL_729;
      }
      switch ( pMissionManager46->field_2 )
      {
        case 'g':
          gta2::MapRelatedStruct_sub_462CE0(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'h':
          gta2::MapRelatedStruct_sub_462D00(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'i':
          gta2::MapRelatedStruct_sub_462D20(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'j':
          gta2::MapRelatedStruct_sub_462D40(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'k':
          gta2::MapRelatedStruct_sub_462D80(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'l':
          gta2::MapRelatedStruct_sub_462DA0(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'm':
          gta2::MapRelatedStruct_sub_462DC0(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'n':
          gta2::MapRelatedStruct_sub_462DE0(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'o':
          gta2::MapRelatedStruct_sub_462E00(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        case 'p':
          gta2::MapRelatedStruct_sub_462E20(gMapRelatedStruct, v51[1], pMissionManager46->arr_96[2]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, dword_6644CC);
          break;
        default:
          goto LABEL_729;
      }
      return;
    case 0x71u:
    case 0x1B8u:
      pS28Arr[0] = pMissionScriptObjectData;
      v53 = dword_6644CC;
      pS28_9 = pMissionScriptObjectData;
      v564 = dword_6644CC->arr_96[2];
      pS28Arr[0] = pMissionScriptObjectData;
      v56 = gta2::MissionManager_StartMission(gMissionManager, v564);
      v57 = gta2::MissionManager_StartMission(v55, v53->arr_96[1]);
      if ( !v56->arr_96[1] )
      {
        HudArrow = gta2::HudArrow_GetHudArrow(&gHud->HudArrow_);
        v53 = dword_6644CC;
        v56->arr_96[1] = (int)HudArrow;
      }
      switch ( gta2::MissionScriptObjectData_sub_475010(pS28_9, v57->field_2) )
      {
        case 1:
          pPed_1 = v57->arr_96[1];
          if ( !gta2::Ped_IsPlayerControlled((Ped *)pPed_1)
            || (Id = gta2::Player_GetId(*(Player **)(pPed_1 + 348)), Id != gta2::Game_sub_476790(gGame)) )
          {
            gta2::HudArrow_SetParam((HudArrow *)v56->arr_96[1], pPed_1);
          }
          break;
        case 2:
          gta2::HudArrow_GetParam((HudArrow *)v56->arr_96[1], v57->arr_96[1]);
          break;
        case 3:
          gta2::HudArrow_ResetParam((HudArrow *)v56->arr_96[1], v57->arr_96[1]);
          break;
        case 4:
          v61 = unk_664564;
          v62 = v57->arr_96[4];
          v63 = v57->arr_96[3];
          goto LABEL_244;
        case 5:
          v61 = (EventHandler *)v57->arr_96[4];
          v62 = v57->arr_96[3];
          v63 = v57->arr_96[2];
LABEL_244:
          gta2::HudArrow_PlayerHandler((HudArrow *)v56->arr_96[1], v63, v62, (int)v61);
          break;
        default:
          break;
      }
      if ( v53->field_2 == 440 )
      {
        gta2::HudArrow_SetArrowType((HudArrow *)v56->arr_96[1], 5u);
        v53 = dword_6644CC;
      }
      gta2::MissionScriptObjectData_sub_476E50(pS28Arr[0], v53);
      return;
    case 0x72u:
    case 0x1B9u:
      gta2::SoundInfo_sub_478E10(pMissionScriptObjectData);
      return;
    case 0x73u:
      Index_1 = (int)pS28Arr[0];
      v64 = dword_6644CC;
      pS28_10 = pMissionScriptObjectData;
      v66 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v67 = v66;
      if ( !v66->arr_96[1] )
        v66->arr_96[1] = (int)gta2::HudArrow_GetHudArrow(&gHud->HudArrow_);
      gta2::HudArrow_SetArrowType((HudArrow *)v67->arr_96[1], HIWORD(v64->arr_96[1]));
      gta2::MissionScriptObjectData_sub_476E50(pS28_10, dword_6644CC);
      return;
    case 0x74u:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v69 = (void *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( v69 )
        gta2::sub_476880(v69);
      goto LABEL_684;
    case 0x75u:
    case 0x76u:
    case 0x117u:
    case 0x141u:
      v85 = dword_6644CC;
      Index_1 = (int)v546;
      v86 = BYTE2(dword_6644CC->arr_96[1]);
      v87 = pMissionScriptObjectData;
      if ( v86 == 1 )
      {
        gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_JOB_COMPLETE);
      }
      else if ( v86 == 2 )
      {
        gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_JOB_FAILED);
      }
      v88 = v85->arr_96[1];
      switch ( v88 )
      {
        case 5501:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_RACE_OVER);
          break;
        case 5502:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_SECOND_LAP);
          break;
        case 5503:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_FINAL_LAP);
          break;
        case 5504:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_RACE_ON);
          break;
        case 5505:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_HEY__30_PEOPLE_DOWN__MULTIPLIER_X2);
          break;
        case 5506:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_OOH__60_PEOPLE_DOWN__MULTIPLIER_X3);
          break;
        case 5507:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_NICE__90_PEOPLE_DOWN__MULTIPLIER_X4);
          break;
        case 5508:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_GREAT__120_PEOPLE_DOWN__MULTIPLIER_X5);
          break;
        case 5509:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_OUTSTANDING__150_PEOPLE_DOWN__MULTIPLIER_X6);
          break;
        case 5510:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_TIME_OUT);
          break;
        case 5000:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_YOUR_TIME_IS_EXTENDED);
          break;
        case 5015:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_TIME_S_UP__PAL___duplicate);
          break;
        case 5031:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_Oh__sorry_about_that____Did_that_hurt);
          break;
        case 5032:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_Nice_work);
          break;
        case 5050:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_CHOCTASTIC);
          break;
        case 5051:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_RASPBERRY_RIPPLE);
          break;
        case 5052:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_YOU_SHOT_YOUR_LOAD);
          break;
        case 5053:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_OOH____DID_THAT_HURT);
          break;
        case 5054:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_DEATH_TO_ICE_CREAM_VANS);
          break;
        case 5055:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_CRISPY_CRITTER);
          break;
        case 5056:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_YOU_RE_TOAST__BUDDY);
          break;
        case 5057:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_EAT_LEADEN_DEATH__PUNK);
          break;
        case 5058:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_THAT_S_GOTTA_HURT);
          break;
        case 5059:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_SORRY_ABOUT_THAT);
          break;
        case 5060:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_XIN_LOI__MY_MAN);
          break;
        case 5061:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_DAMN_SUNDAY_DRIVERS);
          break;
        case 5062:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_SUCK_IT_AND_SEE);
          break;
        case 5063:
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_TASTE_MY_WRATH__ICE_CREAM_BOY);
          break;
      }
      strcpy(gStr, "%d", LOWORD(v85->arr_96[1]));
      switch ( v85->field_2 )
      {
        case 0x75u:
          v89 = gta2::Text__Bsearch(gText, gStr);
          gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v89, 3);
          gta2::MissionScriptObjectData_sub_476E50(v87, dword_6644CC);
          break;
        case 0x76u:
          gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
          goto LABEL_576;
        case 0x117u:
          gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 3, gStr);
          goto LABEL_576;
        case 0x141u:
          gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 2, gStr);
          goto LABEL_576;
        default:
          goto LABEL_576;
      }
      return;
    case 0x77u:
      Index_1 = (int)v546;
      v90 = pMissionScriptObjectData;
      v92 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v93 = gta2::S166_sub_4C9310(&gHud->S166_, *(__int16 *)(v91 + 10));
      v581 = dword_6644CC;
      LOWORD(v92->arr_96[1]) = v93;
      gta2::MissionScriptObjectData_sub_476E50(v90, v581);
      return;
    case 0x78u:
      Index_1 = (int)v546;
      v228 = pMissionScriptObjectData;
      v229 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      if ( LOWORD(v229->arr_96[1]) != 0xFFFF )
        gta2::S166_sub_4C93B0(&gHud->S166_, LOWORD(v229->arr_96[1]));
      v585 = dword_6644CC;
      LOWORD(v229->arr_96[1]) = 0;
      gta2::MissionScriptObjectData_sub_476E50(v228, v585);
      return;
    case 0x79u:
      gta2::MissionScriptObjectData_sub_479B70(pMissionScriptObjectData);
      return;
    case 0x7Au:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      v110 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v111 = (Ped *)v110->arr_96[1];
      if ( v111 )
      {
        if ( gta2::Ped_IsInCar((Ped *)v110->arr_96[1]) )
        {
          CarPlayers = gta2::Ped_GetCarPlayers(v111);
          if ( gta2::Car_GetModelCar(CarPlayers) == SHIWORD(v108->arr_96[1]) )
            goto LABEL_624;
        }
      }
      goto LABEL_552;
    case 0x7Bu:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      v113 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v114 = (Ped *)v113->arr_96[1];
      if ( !v114 || !gta2::Ped_IsInCar((Ped *)v113->arr_96[1]) || !gta2::Ped_IsInCar(v114) )
        goto LABEL_552;
      goto LABEL_624;
    case 0x7Cu:
      v551 = pS28Arr[0];
      pS28Arr[0] = pMissionScriptObjectData;
      Index_1 = (int)v551;
      v121 = dword_6644CC;
      v122 = pMissionScriptObjectData;
      v123 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( v123 )
      {
        v124 = (Player *)gta2::Ped_sub_433C20(v123, pS28Arr);
        if ( gta2::Player_IsCurrentPlayer(v124, (Player *)&gAudioSourceParams) )
          goto LABEL_375;
      }
      goto LABEL_640;
    case 0x7Du:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      pPed_2 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_Get_433B60(pPed_2) != 22 && gta2::Ped_GetHealth(pPed_2) > 25 )
        goto LABEL_552;
      goto LABEL_624;
    case 0x7Eu:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v70 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( !v70 || gta2::Ped_GetHealth(v70) < SHIWORD(v68->arr_96[1]) )
        goto LABEL_353;
      goto LABEL_694;
    case 0x7Fu:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v107 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( v107 && gta2::Ped_GetPedState(v107) == 9 )
        goto LABEL_694;
      goto LABEL_353;
    case 0x80u:
      Index_1 = (int)pS28Arr[0];
      v71 = dword_6644CC;
      pS28_7 = pMissionScriptObjectData;
      gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v73 = gta2::MissionManager_StartMission(v72, HIWORD(v71->arr_96[1]));
      v75 = *(Ped **)(v74 + 8);
      v76 = v73;
      if ( !v75 || !gta2::Ped_IsInCar(*(Ped **)(v74 + 8)) )
        goto LABEL_828;
      v77 = gta2::Ped_GetCarPlayers(v75);
      v78 = unk_6644B0;
      *((_DWORD *)v76 + 2) = v77;
      if ( !v78 )
      {
        v84 = v77->ID;
        unk_6644B0 = v77;
        unk_6644B4 = v84;
        gta2::Car_sub_424680(v77, 8);
        goto LABEL_828;
      }
      if ( v78 == v77 )
        goto LABEL_828;
      v79 = v78->ID;
      if ( v79 == v77->ID )
        goto LABEL_828;
      if ( v79 != unk_6644B4 )
        goto LABEL_270;
      if ( gta2::CarSystemManager_sub_420CE0(gCarSystemManager, 1) )
      {
        gta2::Car_sub_424680(unk_6644B0, 1);
        gta2::Player_sub_4A47F0(gGame->PlayerMain, unk_6644B0);
        pCar3_1 = unk_6644B0;
        gta2::Car_CarMakeDriveable1(unk_6644B0, SEARCHTYPE_AREA);
        if ( gta2::Car_GetMask7(pCar3_1) )
          goto LABEL_270;
        goto LABEL_265;
      }
      if ( gta2::CarSystemManager_sub_420C40(gCarSystemManager, 8) )
      {
        gta2::Player_sub_4A47F0(gGame->PlayerMain, unk_6644B0);
        pCar3_1 = unk_6644B0;
        gta2::Car_CarMakeDriveable1(unk_6644B0, SEARCHTYPE_AREA);
        if ( !gta2::Car_GetMask7(pCar3_1) )
LABEL_265:
          gta2::Car_isMask4(pCar3_1);
      }
      else
      {
        gta2::Player_sub_4A47F0(gGame->PlayerMain, unk_6644B0);
        pCar_2 = unk_6644B0;
        gta2::Car_CarMakeDriveable1(unk_6644B0, SEARCHTYPE_AREA);
        gta2::Car_isMask3(pCar_2);
      }
LABEL_270:
      v82 = (Car *)*((_DWORD *)v76 + 2);
      v83 = v82->ID;
      unk_6644B0 = v82;
      unk_6644B4 = v83;
      gta2::Car_sub_424680(v82, 8);
      if ( gta2::PublicTransport_IsThisBus(gPublicTransport, *((Car **)v76 + 2)) )
        goto LABEL_828;
      gta2::Car_SetLocksDoor2(*((Car **)v76 + 2));
      gta2::MissionScriptObjectData_sub_476E50(pS28_7, dword_6644CC);
      return;
    case 0x81u:
      gta2::MissionScriptObjectData_sub_479050(pMissionScriptObjectData);
      return;
    case 0x82u:
    case 0x9Au:
    case 0xBEu:
    case 0xBFu:
    case 0x10Bu:
    case 0x131u:
    case 0x1A1u:
      pMissionManager26 = pMissionScriptObjectData;
      v515 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      *(&v517 + 1) = 0;
      pMissionManager26->field_8 = 0;
      v517 = *(_WORD *)(v516 + 2);
      if ( v517 > 0xBFu )
      {
        v524 = *(_DWORD *)&v517 - 267;
        if ( v524 )
        {
          v525 = v524 - 38;
          if ( v525 )
          {
            if ( v525 != 112 )
              goto LABEL_815;
            IsPlayerDriving = gta2::Car_sub_414F80((Car *)v515->arr_96[1]);
          }
          else
          {
            IsPlayerDriving = gta2::sub_4119B0((void *)v515->arr_96[1]);
          }
        }
        else
        {
          IsPlayerDriving = gta2::Car_sub_41FA60((Car *)v515->arr_96[1]);
        }
      }
      else if ( v517 == 191 )
      {
        IsPlayerDriving = gta2::Car_IsPlayerDriving((Car *)v515->arr_96[1]);
      }
      else
      {
        v518 = *(_DWORD *)&v517 - 130;
        if ( !v518 )
        {
          v523 = gta2::Car_GetDriver((Car *)v515->arr_96[1]) == 0;
          goto LABEL_813;
        }
        v519 = v518 - 24;
        if ( v519 )
        {
          if ( v519 != 36 )
            goto LABEL_815;
          IsPlayerDriving = gta2::Car_sub_421D80((Car *)v515->arr_96[1]);
        }
        else
        {
          v521 = (Car *)v515->arr_96[1];
          Mask = v521->Mask;
          if ( Mask == 6 || Mask == 5 || v521->Damage >= 32000 )
            goto LABEL_814;
          IsPlayerDriving = gta2::Car_sub_421D80(v521);
        }
      }
      v523 = !IsPlayerDriving;
LABEL_813:
      if ( v523 )
        goto LABEL_815;
LABEL_814:
      pMissionManager26->field_8 = 1;
      goto LABEL_815;
    case 0x83u:
      v100 = pMissionScriptObjectData;
      v101 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_4751F0(v100, v102, v101);
      gta2::MissionScriptObjectData_sub_476E50(v100, dword_6644CC);
      return;
    case 0x84u:
      gta2::MissionScriptObjectData_sub_47A1E0(pMissionScriptObjectData);
      return;
    case 0x85u:
      gta2::MissionScriptObjectData_sub_47A330(pMissionScriptObjectData);
      return;
    case 0x86u:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v103 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( !v103 )
        goto LABEL_684;
      _450CB0 = (unsigned __int8)gta2::Ped_Get_450CB0(v103);
      if ( !_450CB0 )
        goto LABEL_348;
      v105 = _450CB0 - 1;
      if ( !v105 )
        goto LABEL_694;
      if ( v105 == 1 )
LABEL_348:
        pMissionManager14->field_8 = 0;
      goto LABEL_684;
    case 0x87u:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v106 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( !v106 )
        goto LABEL_684;
      if ( gta2::Ped_Get_450CB0(v106) != 2 )
        goto LABEL_353;
      pMissionManager14->field_8 = 1;
      goto LABEL_684;
    case 0x8Au:
    case 0x10Au:
      gta2::SoundInfo_sub_4797A0(pMissionScriptObjectData);
      return;
    case 0x8Bu:
      gta2::MissionScriptObjectData_sub_479850(pMissionScriptObjectData);
      return;
    case 0x8Cu:
      v514 = pMissionScriptObjectData;
      gta2::MissionScriptObjectData_sub_47F760(pMissionScriptObjectData, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v514, dword_6644CC);
      return;
    case 0x8Du:
    case 0x188u:
      gta2::MissionScriptObjectData_sub_479CC0(pMissionScriptObjectData);
      return;
    case 0x8Eu:
    case 0x18Fu:
    case 0x194u:
    case 0x196u:
      v125 = pMissionScriptObjectData;
      v126 = dword_6644CC;
      v127 = dword_6644CC->field_2;
      if ( (unsigned __int16)v127 > 0x194u )
      {
        if ( v127 != 406 )
          goto LABEL_388;
        Index_1 = 0;
        v583 = 32;
      }
      else if ( (unsigned __int16)v127 == 404 )
      {
        Index_1 = 0;
        v583 = 18;
      }
      else
      {
        if ( v127 != 142 )
        {
          if ( v127 != 399 )
            goto LABEL_388;
          gta2::Object_sub_485540(
            gObject,
            dword_6644CC->arr_96[1],
            dword_6644CC->arr_96[2],
            dword_6644CC->arr_96[3],
            (unsigned __int16)unk_664530,
            20,
            0);
LABEL_387:
          v126 = dword_6644CC;
LABEL_388:
          gta2::MissionScriptObjectData_sub_476E50(v125, v126);
          return;
        }
        Index_1 = 0;
        v583 = 19;
      }
      LOWORD(pMissionScriptObjectData) = unk_664530;
      gta2::Object_sub_485540(
        gObject,
        dword_6644CC->arr_96[1],
        dword_6644CC->arr_96[2],
        dword_6644CC->arr_96[3],
        (int)pMissionScriptObjectData,
        v583,
        Index_1);
      goto LABEL_387;
    case 0x8Fu:
      v128 = dword_6644CC;
      v129 = pMissionScriptObjectData;
      v130 = LOBYTE(dword_6644CC->arr_96[4]) - 1;
      switch ( LOBYTE(dword_6644CC->arr_96[4]) )
      {
        case 1:
          Index_1 = 0;
          v584 = 23;
          goto LABEL_394;
        case 2:
          Index_1 = 0;
          v584 = 22;
          goto LABEL_394;
        case 3:
          Index_1 = 0;
          v584 = 24;
          goto LABEL_394;
        case 4:
          Index_1 = 0;
          v584 = 25;
LABEL_394:
          LOWORD(v130) = unk_664530;
          gta2::Object_sub_485540(
            gObject,
            dword_6644CC->arr_96[1],
            dword_6644CC->arr_96[2],
            dword_6644CC->arr_96[3],
            v130,
            v584,
            Index_1);
          v128 = dword_6644CC;
          break;
        default:
          goto LABEL_395;
      }
      goto LABEL_395;
    case 0x90u:
    case 0x18Eu:
    case 0x193u:
    case 0x195u:
      gta2::MissionScriptObjectData_sub_47C1E0(pMissionScriptObjectData);
      return;
    case 0x91u:
    case 0x92u:
    case 0x93u:
    case 0x94u:
    case 0x95u:
    case 0x96u:
      gta2::MissionScriptObjectData_sub_479F10(pMissionScriptObjectData);
      return;
    case 0x97u:
    case 0x98u:
    case 0x99u:
    case 0xEEu:
    case 0xEFu:
      pS28_11 = pMissionScriptObjectData;
      v265 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      switch ( v266->field_2 )
      {
        case 0x97u:
          *(_DWORD *)(v265->arr_96[1] + 648) = SHIWORD(v266->arr_96[1]);
          goto LABEL_740;
        case 0x98u:
          v267 = SHIWORD(v266->arr_96[1]);
          v268 = v265->arr_96[1];
          Index_1 = (int)v266;
          *(_DWORD *)(v268 + 652) = v267;
          gta2::MissionScriptObjectData_sub_476E50(pS28_11, (MissionManager *)Index_1);
          break;
        case 0x99u:
          gta2::Ped_PedGroupCreate((Ped *)v265->arr_96[1], BYTE2(v266->arr_96[1]));
          gta2::MissionScriptObjectData_sub_476E50(pS28_11, dword_6644CC);
          break;
        default:
          goto LABEL_740;
      }
      return;
    case 0x9Bu:
      v552 = pMissionScriptObjectData;
      v128 = dword_6644CC;
      v129 = pMissionScriptObjectData;
      if ( HIWORD(dword_6644CC->arr_96[1]) != 255 )
      {
        LOBYTE(v552) = BYTE2(dword_6644CC->arr_96[1]);
        v131 = dword_6644CC->arr_96[1];
        Index_1 = (int)v552;
        v132 = gta2::MissionManager_StartMission(gMissionManager, v131);
        gta2::Car_SetRemap((Car *)v132->arr_96[1], Index_1);
        v128 = dword_6644CC;
      }
LABEL_395:
      gta2::MissionScriptObjectData_sub_476E50(v129, v128);
      return;
    case 0x9Cu:
      pS28_11 = pMissionScriptObjectData;
      v133 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v134 = (Ped *)v133->arr_96[1];
      if ( v134 )
      {
        gta2::Ped_SetRemap_0(v134, BYTE2(v266->arr_96[1]));
        v266 = dword_6644CC;
      }
      goto LABEL_740;
    case 0x9Du:
      v135 = dword_6644CC;
      v136 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( v136 && *(char *)(v136 + 132) == HIWORD(v135->arr_96[1]) )
      {
        Index_1 = (int)v135;
        v137->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(v137, (MissionManager *)Index_1);
      }
      else
      {
        Index_1 = (int)v135;
        v137->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(v137, (MissionManager *)Index_1);
      }
      return;
    case 0x9Eu:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v138 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( !v138
        || *(_DWORD *)(v138 + 136) == 6
        || (unsigned __int16)gta2::SpriteS1_get_remap(*(SpriteS1 **)(v138 + 80)) != SHIWORD(v68->arr_96[1]) )
      {
        goto LABEL_353;
      }
      goto LABEL_694;
    case 0x9Fu:
      v139 = dword_6644CC;
      Index_1 = (int)v546;
      v140 = pMissionScriptObjectData;
      v141 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( v141
        && *(_DWORD *)(v141 + 136) != 6
        && *(char *)(v141 + 132) == HIWORD(v139->arr_96[1])
        && (unsigned __int16)gta2::SpriteS1_get_remap(*(SpriteS1 **)(v141 + 80)) == SLOWORD(v139->arr_96[2]) )
      {
        v140->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(v140, v139);
      }
      else
      {
        v140->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(v140, v139);
      }
      return;
    case 0xA0u:
    case 0x164u:
      gta2::MissionScriptObjectData_sub_47A620(pMissionScriptObjectData);
      return;
    case 0xA1u:
      v553 = pMissionScriptObjectData;
      v142 = dword_6644CC;
      v143 = dword_6644CC->arr_96[1];
      if ( v143 == -1 )
      {
        LOWORD(dword_6644CC->arr_96[1]) = HIWORD(dword_6644CC->arr_96[1]);
      }
      else
      {
        v144 = v143 - 1;
        LOWORD(dword_6644CC->arr_96[1]) = v144;
        if ( !v144 )
        {
          pS28Arr[0] = (MissionScriptObjectData *)v142;
          LOWORD(v142->arr_96[1]) = -1;
          gta2::MissionScriptObjectData_sub_476E50(v553, (MissionManager *)pS28Arr[0]);
        }
      }
      return;
    case 0xA2u:
      v554 = pMissionScriptObjectData;
      v145 = dword_6644CC;
      v146 = dword_6644CC->arr_96[1];
      if ( v146 == -1 )
      {
        LOWORD(dword_6644CC->arr_96[1]) = HIWORD(dword_6644CC->arr_96[1]);
      }
      else
      {
        v147 = v146 - 1;
        LOWORD(dword_6644CC->arr_96[1]) = v147;
        if ( !v147 )
        {
          LOWORD(v145->arr_96[1]) = -1;
          pS28Arr[0] = (MissionScriptObjectData *)v145;
          v554->field_8 = 0;
          gta2::MissionScriptObjectData_sub_476E50(v554, (MissionManager *)pS28Arr[0]);
          return;
        }
      }
      pS28Arr[0] = (MissionScriptObjectData *)v145;
      v554->field_8 = 1;
      gta2::MissionScriptObjectData_sub_476E50(v554, (MissionManager *)pS28Arr[0]);
      return;
    case 0xA3u:
      Index_1 = (int)v546;
      v254 = dword_6644CC;
      v255 = pMissionScriptObjectData;
      v256 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::Ped_SetPoliceNoStar((Ped *)v256->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v255, v254);
      return;
    case 0xA4u:
    case 0x1A5u:
      Index_1 = (int)pS28Arr[0];
      pS28_7 = pMissionScriptObjectData;
      v257 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v259 = v257;
      if ( *(_WORD *)(v258 + 2) == 421 )
      {
        v260 = (byte *)(v258 + 10);
        if ( !gta2::Ped_IsCopStarsExceeding((Ped *)v257->arr_96[1], *(_BYTE *)(v258 + 10)) )
          gta2::Ped_HandleWantedEvent((Ped *)v259->arr_96[1], *v260);
      }
      else
      {
        gta2::Ped_HandleWantedEvent((Ped *)v257->arr_96[1], *(_BYTE *)(v258 + 10));
      }
      goto LABEL_828;
    case 0xA5u:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      v201 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      v202 = gta2::Ped_sub_433CA0((Ped *)v201);
      if ( !v202 || gta2::Ped_GetSub_4039F0((Ped *)v201) || !*(_DWORD *)(v201 + 368) )
        goto LABEL_552;
      goto LABEL_624;
    case 0xA6u:
      Index_1 = (int)v546;
      v87 = pMissionScriptObjectData;
      v222 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v223 = (Ped *)v222->arr_96[1];
      if ( v223 )
      {
        gta2::Ped_SetAnimationState(v223, 0, 9999);
        gta2::Ped_PedSetObjective((Ped *)v222->arr_96[1], 36, 9999);
        gta2::Ped_SetCurrentCar((Ped *)v222->arr_96[1], *(Car **)(v222->arr_96[1] + 364));
      }
      goto LABEL_576;
    case 0xA7u:
    case 0xABu:
      Index_1 = (int)pS28Arr[0];
      v214 = pMissionScriptObjectData;
      v215 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v218 = gta2::MissionManager_StartMission(v217, *(_WORD *)(v216 + 10));
      v220 = (Ped *)v215->arr_96[1];
      v221 = v218;
      if ( !v220 )
        goto LABEL_480;
      if ( v219->field_2 == 171 )
      {
        gta2::Ped_EnterCarAsPassenger(v220, (Car *)v218->arr_96[1]);
        v219 = dword_6644CC;
LABEL_480:
        gta2::MissionScriptObjectData_sub_476E50(v214, v219);
      }
      else
      {
        gta2::Ped_SetAnimationState(v220, 0, 9999);
        gta2::Ped_PedSetObjective((Ped *)v215->arr_96[1], 35, 9999);
        gta2::Ped_SetCurrentCar((Ped *)v215->arr_96[1], (Car *)v221->arr_96[1]);
        gta2::Ped_SetTargetCarDoor((Ped *)v215->arr_96[1], 0);
        gta2::MissionScriptObjectData_sub_476E50(v214, dword_6644CC);
      }
      return;
    case 0xA8u:
      pS28Arr[0] = pMissionScriptObjectData;
      v176 = dword_6644CC;
      v177 = pMissionScriptObjectData;
      v178 = dword_6644CC;
      v179 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[2]);
      v566 = v176->arr_96[1];
      pS28Arr[0] = (MissionScriptObjectData *)v179;
      v181 = gta2::MissionManager_StartMission(v180, v566);
      v183 = v181;
      pS63 = (EventHandler *)v181->arr_96[1];
      if ( !pS63 || !*(_DWORD *)(v182 + 8) )
        goto LABEL_453;
      gta2::S63_sub_483C50(pS63);
      v176 = dword_6644CC;
      v567 = dword_6644CC->field_0;
      v561 = *(_DWORD *)(v183->arr_96[1] + 20);
      v185 = gta2::Ped_sub_420B60((Ped *)pS28Arr[0]->field_8);
      gta2::MissionManager_sub_476370(gMissionManager, v185, v561, v567);
      v177->field_8 = 0;
      BYTE2(v178->arr_96[3]) = 0;
      v186 = v178->arr_96[3];
      if ( v186 <= 0 )
      {
        v177->field_E = -1;
LABEL_453:
        gta2::MissionScriptObjectData_sub_476E50(v177, v176);
      }
      else
      {
        v177->field_E = v186;
        gta2::MissionScriptObjectData_sub_476E50(v177, v176);
      }
      return;
    case 0xA9u:
      v261 = dword_6644CC;
      Index_1 = (int)v546;
      v262 = pMissionScriptObjectData;
      v579 = gta2::Weapon_sub_41C1E0((Weapon *)&dword_6644CC->arr_96[4]);
      v571 = gta2::Weapon_sub_41C1E0((Weapon *)&v261->arr_96[3]);
      v568 = gta2::Weapon_sub_41C1E0((Weapon *)&v261->arr_96[2]);
      v263 = gta2::MissionManager_StartMission(gMissionManager, v261->arr_96[1]);
      gta2::Car_sub_4237F0((Car *)v263->arr_96[1], v568, v571, v579, 1);
      gta2::MissionScriptObjectData_sub_476E50(v262, dword_6644CC);
      return;
    case 0xAAu:
      pS28_7 = pMissionScriptObjectData;
      Index_1 = (int)pS28Arr[0];
      v224 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v225 = v224;
      v226 = (Car *)v224->arr_96[1];
      if ( v226 )
      {
        if ( !gta2::Car_GetDriver((Car *)v224->arr_96[1]) )
          gta2::Car_CarPutDummyDriverIn(v226);
        gta2::Car_CarMakeDummy((Car *)v225->arr_96[1]);
        gta2::Car_sub_421540((Car *)v225->arr_96[1]);
        gta2::Car_CarMakeDriveable1((Car *)v225->arr_96[1], SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
      }
      goto LABEL_828;
    case 0xADu:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      pCar_3 = (Car *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( !pCar_3 )
        goto LABEL_729;
      v248 = pMissionManager46->field_2;
      if ( v248 == 173 )
      {
        gta2::Car_sub_44A3E0(pCar_3);
        gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
        return;
      }
      if ( v248 == 174 )
        gta2::Car_sub_476230(pCar_3);
      goto LABEL_729;
    case 0xAFu:
      v203 = pMissionScriptObjectData;
      v204 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::Car_CarMakeDummy((Car *)v204->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v203, dword_6644CC);
      return;
    case 0xB0u:
      gta2::MissionScriptObjectData_sub_47B5E0(pMissionScriptObjectData);
      return;
    case 0xB1u:
    case 0xB2u:
    case 0xB3u:
    case 0xB4u:
      pMissionManager26 = pMissionScriptObjectData;
      v338 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      switch ( *(_WORD *)(v339 + 2) )
      {
        case 0xB1:
          gta2::sub_476A60((void *)v338->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pMissionManager26, dword_6644CC);
          break;
        case 0xB2:
          gta2::sub_476A30((void *)v338->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pMissionManager26, dword_6644CC);
          break;
        case 0xB3:
          gta2::sub_476AA0((_BYTE *)v338->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pMissionManager26, dword_6644CC);
          break;
        case 0xB4:
          gta2::sub_476AB0((_BYTE *)v338->arr_96[1]);
          goto LABEL_815;
        default:
          goto LABEL_815;
      }
      return;
    case 0xB5u:
      v555 = pMissionScriptObjectData;
      pMissionManager26 = pMissionScriptObjectData;
      v344 = BYTE1(dword_6644CC->arr_96[1]);
      v388 = HIBYTE(dword_6644CC->arr_96[1]) == 0;
      LOBYTE(v555) = BYTE2(dword_6644CC->arr_96[1]);
      v345 = dword_6644CC->arr_96[1];
      Index_1 = (int)v555;
      if ( v388 )
        gta2::JuncIds_sub_40E1B0(gJuncIds, v345, v344, Index_1);
      else
        gta2::JuncIds_sub_40E2F0(gJuncIds, v345, v344, Index_1);
      goto LABEL_815;
    case 0xB6u:
      gta2::MissionScriptObjectData_sub_47C6A0(pMissionScriptObjectData);
      return;
    case 0xB7u:
      v341 = pMissionScriptObjectData;
      gta2::MapRelatedStruct_sub_464110(
        gMapRelatedStruct,
        LOBYTE(dword_6644CC->arr_96[1]),
        BYTE1(dword_6644CC->arr_96[1]),
        BYTE2(dword_6644CC->arr_96[1]),
        HIBYTE(dword_6644CC->arr_96[1]));
      gta2::MissionScriptObjectData_sub_476E50(v341, dword_6644CC);
      return;
    case 0xB8u:
      v342 = pMissionScriptObjectData;
      gta2::MapRelatedStruct_sub_464210(
        gMapRelatedStruct,
        LOBYTE(dword_6644CC->arr_96[1]),
        BYTE2(dword_6644CC->arr_96[1]),
        BYTE1(dword_6644CC->arr_96[1]),
        HIBYTE(dword_6644CC->arr_96[1]));
      gta2::MissionScriptObjectData_sub_476E50(v342, dword_6644CC);
      return;
    case 0xB9u:
    case 0xBAu:
    case 0xBBu:
      v343 = pMissionScriptObjectData;
      gta2::MapRelatedStruct_sub_463F60(
        gMapRelatedStruct,
        LOBYTE(dword_6644CC->arr_96[1]),
        BYTE1(dword_6644CC->arr_96[1]),
        BYTE2(dword_6644CC->arr_96[1]),
        HIBYTE(dword_6644CC->arr_96[1]),
        dword_6644CC->arr_96[2]);
      gta2::MissionScriptObjectData_sub_476E50(v343, dword_6644CC);
      return;
    case 0xBCu:
      Index_1 = (int)pS28Arr[0];
      v205 = pMissionScriptObjectData;
      v206 = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
      v209 = gta2::MissionManager_StartMission(v208, *(_WORD *)(v207 + 8));
      v211 = (void *)v206->arr_96[1];
      v212 = v209;
      if ( v211 )
      {
        v213 = gta2::sub_4497D0(v211);
        v210 = dword_6644CC;
        v212->arr_96[1] = (int)v213;
        v205->field_8 = v213 != 0;
      }
      else
      {
        v205->field_8 = 0;
      }
      gta2::MissionScriptObjectData_sub_476E50(v205, v210);
      return;
    case 0xBDu:
      gta2::MissionScriptObjectData_sub_47B810(pMissionScriptObjectData);
      return;
    case 0xC0u:
    case 0xC4u:
    case 0x119u:
    case 0x11Au:
      Index_1 = (int)pS28Arr[0];
      v375 = dword_6644CC;
      v376 = pMissionScriptObjectData;
      v377 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v378 = v375->field_2 - 192;
      if ( v378 <= 0x5A )
      {
        switch ( byte_47CBE8[v378] )
        {
          case 0:
            v380 = v377->arr_96[1];
            if ( !gta2::Ped_IsPlayerControlled((Ped *)v380) )
              break;
            Money = gta2::Player_getMoney(*(Player **)(v380 + 348));
            goto LABEL_616;
          case 1:
            v383 = v377->arr_96[1];
            if ( !gta2::Ped_IsPlayerControlled((Ped *)v383) )
              break;
            Money = gta2::Player_GetMultiPlayer(*(Player **)(v383 + 348));
LABEL_616:
            v376->field_8 = (int)Money > SHIWORD(v375->arr_96[1]);
            break;
          case 2:
            v379 = v377->arr_96[1];
            if ( !gta2::Ped_IsPlayerControlled((Ped *)v379) )
              break;
            gta2::Player_AddLives(*(Player **)(v379 + 348), SHIWORD(v375->arr_96[1]));
            gta2::MissionScriptObjectData_sub_476E50(v376, dword_6644CC);
            return;
          case 3:
            v382 = v377->arr_96[1];
            if ( !gta2::Ped_IsPlayerControlled((Ped *)v382) )
              break;
            gta2::Player_SetMultiPlayer(*(Player **)(v382 + 348), SHIWORD(v375->arr_96[1]));
            gta2::MissionScriptObjectData_sub_476E50(v376, dword_6644CC);
            return;
          case 4:
            break;
        }
      }
      gta2::MissionScriptObjectData_sub_476E50(v376, v375);
      return;
    case 0xC1u:
    case 0xC5u:
      gta2::MissionScriptObjectData_sub_47CC50(pMissionScriptObjectData);
      return;
    case 0xC2u:
      v10 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v11 = pMissionScriptObjectData;
      v230 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v231 = v230->arr_96[1];
      if ( !v231 )
        goto LABEL_167;
      if ( gta2::Ped_IsPlayerControlled((Ped *)v230->arr_96[1]) )
      {
        MoneyPlayer = gta2::Player_GetMoneyPlayer(*(Player **)(v231 + 348));
        v233 = v10->arr_96[2];
        v234 = dword_6644CC;
        v11->field_8 = MoneyPlayer > v233;
        gta2::MissionScriptObjectData_sub_476E50(v11, v234);
        return;
      }
      v11->field_8 = 0;
      goto LABEL_167;
    case 0xC3u:
      gta2::MissionScriptObjectData_sub_47B430(pMissionScriptObjectData);
      return;
    case 0xC6u:
    case 0xC7u:
    case 0xE7u:
      gta2::MissionScriptObjectData_sub_47ACC0(pMissionScriptObjectData);
      return;
    case 0xC8u:
      v355 = pMissionScriptObjectData;
      v356 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v358 = gta2::Car_sub_4230D0((Car *)v356->arr_96[1], *(__int16 *)(v357 + 10));
      Index_1 = (int)dword_6644CC;
      v355->field_8 = v358;
      gta2::MissionScriptObjectData_sub_476E50(v355, (MissionManager *)Index_1);
      return;
    case 0xC9u:
      Index_1 = (int)v546;
      v249 = pMissionScriptObjectData;
      v250 = dword_6644CC;
      v251 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v253 = v251->arr_96[1];
      if ( v253 )
      {
        v249->field_8 = (unsigned __int16)sub_445BB0((void *)(v253 + 4)) >= SHIWORD(v250->arr_96[1]);
        gta2::MissionScriptObjectData_sub_476E50(v249, dword_6644CC);
      }
      else
      {
        v249->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(v249, v252);
      }
      return;
    case 0xCAu:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      v385 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_Get_433B60(v385) != 19 || gta2::Ped_GetPedState(v385) != 8 )
        goto LABEL_552;
      goto LABEL_624;
    case 0xCBu:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      v386 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_Get_433B60(v386) == 20 && gta2::Ped_GetPedState(v386) == 8 )
        goto LABEL_624;
      goto LABEL_552;
    case 0xCDu:
      v168 = pMissionScriptObjectData;
      v169 = dword_6644CC;
      v170 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v172 = v170;
      v173 = (Ped *)v170->arr_96[1];
      if ( v173 )
      {
        if ( gta2::Ped_GetState((Ped *)v170->arr_96[1]) != 42 )
          gta2::Ped_PedSetObjective(v173, 42, 9999);
        v570 = gta2::Weapon_sub_41C1E0((Weapon *)&v169->arr_96[4]);
        v565 = gta2::Weapon_sub_41C1E0((Weapon *)&v169->arr_96[3]);
        v174 = gta2::Weapon_sub_41C1E0((Weapon *)&v169->arr_96[2]);
        gta2::sub_435460((_DWORD *)v172->arr_96[1], v174, v565, v570);
        v171 = dword_6644CC;
      }
      gta2::MissionScriptObjectData_sub_476E50(v168, v171);
      return;
    case 0xCEu:
    case 0xCFu:
    case 0xD1u:
      gta2::MissionScriptObjectData_sub_47D070(pMissionScriptObjectData);
      return;
    case 0xD0u:
      v556 = pS28Arr[0];
      pS28Arr[0] = pMissionScriptObjectData;
      Index_1 = (int)v556;
      v121 = dword_6644CC;
      v122 = pMissionScriptObjectData;
      v392 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( *(_DWORD *)(v392 + 88)
        && (v393 = gta2::Player_sub_4211C0(*(Player **)(v392 + 88), pS28Arr), sub_4754D0(v393) > v121->arr_96[2]) )
      {
LABEL_375:
        v122->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(v122, v121);
      }
      else
      {
LABEL_640:
        v122->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(v122, v121);
      }
      return;
    case 0xD7u:
      v149 = pMissionScriptObjectData;
      gta2::MissionScriptObjectData_sub_47A860(pMissionScriptObjectData, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v149, dword_6644CC);
      return;
    case 0xD8u:
      v148 = pMissionScriptObjectData;
      gta2::sub_478240(dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v148, dword_6644CC);
      return;
    case 0xDBu:
    case 0x12Du:
      pS28_20 = pMissionScriptObjectData;
      gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_47F710(pS28_20, v532);
      gta2::MissionScriptObjectData_sub_476E50(pS28_20, dword_6644CC);
      return;
    case 0xDCu:
      v366 = dword_6644CC;
      Index_1 = (int)v546;
      v367 = pMissionScriptObjectData;
      v591 = BYTE2(dword_6644CC->arr_96[1]);
      v368 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_476AE0((S116 *)v368->arr_96[1], v591);
      gta2::MissionScriptObjectData_sub_476E50(v367, v366);
      return;
    case 0xDDu:
      v369 = dword_6644CC;
      Index_1 = (int)v546;
      v370 = pMissionScriptObjectData;
      v592 = dword_6644CC->arr_96[2];
      v371 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_476B00((_DWORD *)v371->arr_96[1], v592);
      gta2::MissionScriptObjectData_sub_476E50(v370, v369);
      return;
    case 0xDEu:
      v372 = dword_6644CC;
      Index_1 = (int)v546;
      v373 = pMissionScriptObjectData;
      v593 = dword_6644CC->arr_96[2];
      v374 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_463F10((int *)v374->arr_96[1], v593);
      gta2::MissionScriptObjectData_sub_476E50(v373, v372);
      return;
    case 0xDFu:
      v227 = pMissionScriptObjectData;
      gta2::MissionScriptObjectData_sub_477BD0(pMissionScriptObjectData, (int)dword_6644CC);
      gta2::MissionScriptObjectData_sub_476E50(v227, dword_6644CC);
      return;
    case 0xE0u:
      pS28Arr[0] = v544;
      v150 = dword_6644CC;
      Index_1 = v545;
      v151 = pMissionScriptObjectData;
      v152 = (const char *)gta2::MissionManager_sub_474F00(gMissionManager, dword_6644CC->arr_96[1]);
      v153 = v152;
      if ( !v152 )
        gta2::debug_log(0x474u, "miss2.cpp", 5217);
      pGang1 = gta2::Gangs_GetGangByName(gGangs, v153 + 9);
      v155 = (const char *)gta2::MissionManager_sub_474F00(gMissionManager, v150->arr_96[2]);
      if ( !v155 )
      {
        Index_1 = (unsigned __int16)dword_6644CC->field_0;
        gta2::debug_log(0x475u, "miss2.cpp", 5223);
      }
      v156 = gta2::Gangs_GetGangByName(gGangs, v155 + 9);
      gta2::Gang_SetWarMaskGang(pGang1, v156->CurrentGang, BYTE2(v150->arr_96[1]));
      gta2::Gang_Set_475900(pGang1, 1);
      gta2::Gang_Set_475900(v156, 1);
      gta2::MissionScriptObjectData_sub_476E50(v151, dword_6644CC);
      return;
    case 0xE1u:
    case 0x106u:
    case 0x189u:
      Index_1 = (int)pS28Arr[0];
      v157 = dword_6644CC;
      v158 = pMissionScriptObjectData;
      if ( dword_6644CC->field_2 != 262 )
        goto LABEL_151;
      v1 = HIWORD(dword_6644CC->arr_96[1]);
      if ( v1 < 0x65u )
        goto LABEL_151;
      if ( v1 <= 0x68u )
        goto LABEL_139;
      if ( v1 < 0x6Fu )
        goto LABEL_151;
      if ( v1 <= 0x72u )
      {
LABEL_139:
        v573 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
        v3 = gta2::MissionManager_StartMission(v2, v157->arr_96[2]);
        switch ( HIWORD(v157->arr_96[1]) )
        {
          case 'e':
            v4 = *(_BYTE *)v573->arr_96[1];
            v3->arr_96[1] = 0;
            LOBYTE(v3->arr_96[1]) = v4;
            goto LABEL_441;
          case 'f':
            v5 = *(_WORD *)v573->arr_96[1];
            v3->arr_96[1] = 0;
            LOWORD(v3->arr_96[1]) = v5;
            goto LABEL_441;
          case 'h':
            v3->arr_96[1] = *(_DWORD *)v573->arr_96[1];
            goto LABEL_441;
          case 'o':
            *(_BYTE *)v573->arr_96[1] = v3->arr_96[1];
            goto LABEL_441;
          case 'p':
            *(_WORD *)v573->arr_96[1] = v3->arr_96[1];
            goto LABEL_441;
          case 'r':
            *(_DWORD *)v573->arr_96[1] = v3->arr_96[1];
            goto LABEL_441;
        }
        goto LABEL_151;
      }
      if ( v1 != 120 && v1 != 121 )
      {
LABEL_151:
        v159 = (const char *)gta2::MissionManager_sub_474F00(gMissionManager, v157->arr_96[1]);
        pGang = (Gangs *)gta2::Gangs_GetGangByName(gGangs, v159 + 9);
        v161 = gta2::MissionManager_StartMission(gMissionManager, v157->arr_96[2]);
        v162 = v161;
        switch ( dword_6644CC->field_2 )
        {
          case 0xE1u:
            v578 = 20 * BYTE2(v157->arr_96[1]);
            v167 = gta2::Player_GetId(*(Player **)(v161->arr_96[1] + 348));
            gta2::Gang_SetRespectForPlayer(pGang->Gang_, v167, v578);
            gta2::Gang_Set_475900(pGang->Gang_, 1);
            break;
          case 0x106u:
            v164 = HIWORD(v157->arr_96[1]);
            if ( v164 <= 0 )
            {
              v577 = 20 * abs16(v164);
              v166 = gta2::Player_GetId(*(Player **)(v162->arr_96[1] + 348));
              gta2::Gang_decreaseRespect(pGang->Gang_, v166, v577);
            }
            else
            {
              v576 = 20 * v164;
              v165 = gta2::Player_GetId(*(Player **)(v162->arr_96[1] + 348));
              gta2::Gangs_IncreaseRespectForPlayer(pGang, v165, v576);
            }
            break;
          case 0x189u:
            v575 = 20 * BYTE2(v157->arr_96[1]);
            v163 = gta2::Player_GetId(*(Player **)(v161->arr_96[1] + 348));
            gta2::Gang_sub_45DEA0(pGang->Gang_, v163, v575);
            break;
        }
        goto LABEL_441;
      }
      v574 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v7 = gta2::MissionManager_StartMission(v6, v157->arr_96[2]);
      v8 = v574->arr_96[1];
      if ( HIWORD(v157->arr_96[1]) == 120 )
      {
        v8 += 1080;
        if ( v8 >= 0x5A0 )
          v8 -= 1440;
      }
      v7->arr_96[1] = dword_3F1C28[v8];
LABEL_441:
      gta2::MissionScriptObjectData_sub_476E50(v158, dword_6644CC);
      return;
    case 0xE2u:
      v175 = pMissionScriptObjectData;
      gta2::EntityManager_sub_46C140(gEntityManager, &dword_6644CC->arr_96[1], &dword_6644CC->arr_96[2]);
      gta2::MissionScriptObjectData_sub_476E50(v175, dword_6644CC);
      return;
    case 0xE3u:
      gta2::MissionScriptObjectData_sub_47AF50(pMissionScriptObjectData);
      return;
    case 0xE4u:
      v187 = pMissionScriptObjectData;
      pMissionManager = gMissionManager;
      v189 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v191 = gta2::MissionManager_sub_4763E0(v190, *(_DWORD *)(v189->arr_96[1] + 20));
      v192 = 0;
      if ( !v191 )
        goto LABEL_460;
      v193 = v187->field_E;
      if ( v193 == -1 )
        goto LABEL_461;
      if ( v193
        || (v194 = gta2::MissionManager_StartMission(pMissionManager, *((_WORD *)v191 + 4)),
            BYTE2(v194->arr_96[3]) != (_BYTE)v192) )
      {
        v187->field_E = v193 - 1;
LABEL_460:
        v187->field_8 = v192;
LABEL_461:
        gta2::MissionScriptObjectData_sub_476E50(v187, dword_6644CC);
      }
      else
      {
        v187->field_8 = 1;
        gta2::S63_sub_483C50((EventHandler *)v189->arr_96[1]);
        gta2::MissionScriptObjectData_sub_476E50(v187, dword_6644CC);
      }
      return;
    case 0xE5u:
      pS28_7 = pMissionScriptObjectData;
      Index_1 = (int)pS28Arr[0];
      pMissionManager1 = gMissionManager;
      v196 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v198 = v196;
      v199 = v196->arr_96[1];
      if ( v199 )
      {
        v200 = (int *)gta2::MissionManager_sub_4763E0(v197, *(_DWORD *)(v199 + 20));
        if ( v200 )
          gta2::MissionManager_sub_4763B0(pMissionManager1, *v200, v200[1]);
        gta2::S63_sub_483C60((EventHandler *)v198->arr_96[1], 163);
      }
      goto LABEL_828;
    case 0xE8u:
      v235 = pMissionScriptObjectData;
      v237 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v239 = (const char *)gta2::MissionManager_sub_474F00(v238, *(_WORD *)(v236 + 10));
      v240 = gta2::Gangs_GetGangByName(gGangs, v239 + 9);
      pPed = v237->arr_96[1];
      v242 = v240;
      if ( gta2::Ped_IsPlayerControlled((Ped *)pPed) )
      {
        v235->field_8 = gta2::Player_GetRespect(*(Player **)(pPed + 348)) == v242;
      }
      else
      {
        gta2::Ped_GetYCoordinate((Ped *)pPed, &Index_1);
        v562 = gta2::Weapon_sub_41C1E0(pWeapon);
        XCoordinate = (Weapon *)gta2::Ped_GetXCoordinate((Ped *)pPed, (int)pS28Arr);
        v245 = gta2::Weapon_sub_41C1E0(XCoordinate);
        v246 = gta2::MapRelatedStruct_sub_464FE0(gMapRelatedStruct, v245, v562, 14);
        if ( v246 )
          v235->field_8 = gta2::_strnicmp(v246 + 6, v242->NameGang, (unsigned __int8)v246[5]) == 0;
        else
          v235->field_8 = 0;
      }
      gta2::MissionScriptObjectData_sub_476E50(v235, dword_6644CC);
      return;
    case 0xEAu:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      v269 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v270 = gta2::sub_475AF0((void *)v269->arr_96[1]);
      if ( v270 && v270->Index >= SHIWORD(v68->arr_96[1]) )
        goto LABEL_694;
      goto LABEL_353;
    case 0xEBu:
    case 0xECu:
    case 0x103u:
      gta2::MissionScriptObjectData_sub_47BAC0(pMissionScriptObjectData);
      return;
    case 0xEDu:
      v271 = dword_6644CC;
      Index_1 = (int)v546;
      v272 = pMissionScriptObjectData;
      v586 = BYTE2(dword_6644CC->arr_96[1]);
      v273 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v274 = gta2::sub_475AF0((void *)v273->arr_96[1]);
      gta2::sub_475AE0(v274, v586);
      gta2::MissionScriptObjectData_sub_476E50(v272, v271);
      return;
    case 0xF1u:
      v278 = pMissionScriptObjectData;
      v279 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v278->field_8 = gta2::Turrel_FindWeaponInPool(gArsenal, (Car *)v279->arr_96[1], (WeaponType)*(__int16 *)(v280 + 10)) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v278, dword_6644CC);
      return;
    case 0xF2u:
      gta2::MissionScriptObjectData_sub_47BCD0(pMissionScriptObjectData);
      return;
    case 0xF3u:
      v108 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v109 = pMissionScriptObjectData;
      pPed1 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_IsInCar(pPed1) && (pCar = gta2::Ped_GetCarPlayers(pPed1), gta2::Car_sub_411970(pCar)) )
      {
LABEL_624:
        v109->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(v109, v108);
      }
      else
      {
LABEL_552:
        v109->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(v109, v108);
      }
      return;
    case 0xF4u:
      v283 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v284 = pMissionScriptObjectData;
      pPed2 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_IsInCar(pPed2)
        && (pCar1 = gta2::Ped_GetCarPlayers(pPed2),
            (unsigned __int8)gta2::Car_sub_41FBB0(pCar1, (int)v546) >= SHIWORD(v283->arr_96[1])) )
      {
        v287 = dword_6644CC;
        v284->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(v284, v287);
      }
      else
      {
        v288 = dword_6644CC;
        v284->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(v284, v288);
      }
      return;
    case 0xF5u:
      gta2::MissionScriptObjectData_sub_47F920(pMissionScriptObjectData);
      return;
    case 0xF6u:
      gta2::MissionScriptObjectData_sub_47BE00(pMissionScriptObjectData);
      return;
    case 0xF7u:
      Index_1 = (int)v546;
      pMissionManager27 = pMissionScriptObjectData;
      v291 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v293 = gta2::MissionManager_StartMission(v292, *(_WORD *)(v290 + 10));
      pSpriteS1 = (SpriteS1 *)gta2::sub_4BEA90((void *)v293->arr_96[1], 2);
      if ( pSpriteS1 && gta2::SpriteS1_GetCar(pSpriteS1) == (Car *)v291->arr_96[1] )
        goto LABEL_541;
      goto LABEL_756;
    case 0xF8u:
    case 0xF9u:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      v295 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v296 = pMissionManager46->field_2;
      if ( v296 == 248 )
      {
        gta2::sub_447F60((_DWORD *)v295->arr_96[1], 0);
        gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
        return;
      }
      if ( v296 == 249 )
        gta2::sub_447F60((_DWORD *)v295->arr_96[1], 1);
      goto LABEL_729;
    case 0xFAu:
      Index_1 = (int)v546;
      v297 = dword_6644CC;
      v298 = pMissionScriptObjectData;
      v299 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v298->field_8 = gta2::Car_GetDriver((Car *)v299->arr_96[1]) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v298, v297);
      return;
    case 0xFBu:
      Index_1 = (int)v546;
      v300 = dword_6644CC;
      v301 = pMissionScriptObjectData;
      v302 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v301->field_8 = (unsigned __int8)gta2::sub_475B00((_DWORD *)v302->arr_96[1]) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v301, v300);
      return;
    case 0xFCu:
      gta2::MissionScriptObjectData_sub_47C000(pMissionScriptObjectData);
      return;
    case 0xFDu:
      Index_1 = (int)v546;
      v87 = pMissionScriptObjectData;
      v304 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_446120((void *)(v304->arr_96[1] + 4));
      if ( gta2::PublicTransport_IsThisBus(gPublicTransport, (Car *)v304->arr_96[1]) )
        gta2::PublicTransport_sub_4AF5F0(gPublicTransport);
      goto LABEL_576;
    case 0xFEu:
      v305 = pMissionScriptObjectData;
      v306 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v307 = gta2::sub_475B20((_DWORD *)v306->arr_96[1]);
      Index_1 = (int)dword_6644CC;
      v305->field_8 = v307;
      gta2::MissionScriptObjectData_sub_476E50(v305, (MissionManager *)Index_1);
      return;
    case 0xFFu:
      Index_1 = (int)v546;
      v308 = dword_6644CC;
      v309 = pMissionScriptObjectData;
      v310 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v309->field_8 = gta2::sub_475B10((void *)v310->arr_96[1]) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v309, v308);
      return;
    case 0x100u:
      Index_1 = (int)v546;
      v87 = pMissionScriptObjectData;
      pPed3 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_IsPlayerControlled((Ped *)pPed3) )
        gta2::Player_sub_4A5690(*(Player **)(pPed3 + 348));
      else
        gta2::Ped_sub_436830((Ped *)pPed3);
LABEL_576:
      gta2::MissionScriptObjectData_sub_476E50(v87, dword_6644CC);
      return;
    case 0x102u:
      Index_1 = (int)v546;
      v311 = pMissionScriptObjectData;
      v313 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v315 = (const char *)gta2::MissionManager_sub_474F00(v314, *(_WORD *)(v312 + 10));
      v316 = gta2::Gangs_GetGangByName(gGangs, v315 + 9);
      v589 = dword_6644CC;
      *(_DWORD *)(v313->arr_96[1] + 380) = v316;
      gta2::MissionScriptObjectData_sub_476E50(v311, v589);
      return;
    case 0x104u:
    case 0x118u:
      Index_1 = (int)v546;
      pMissionManager14 = pMissionScriptObjectData;
      v590 = (void *)gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]))->arr_96[1];
      v320 = gta2::MissionManager_StartMission(v319, *(_WORD *)(v318 + 8));
      gta2::S119_sub_489BC0(gS119, (_DWORD ***)v320->arr_96[1], v590);
      v68 = dword_6644CC;
      if ( dword_6644CC->field_2 == 280 )
        gta2::S119_sub_476AD0(gS119);
      goto LABEL_684;
    case 0x105u:
      v359 = pMissionScriptObjectData;
      pMissionScriptObjectData->field_8 = gta2::S119_sub_476AC0(gS119);
      gta2::MissionScriptObjectData_sub_476E50(v359, dword_6644CC);
      return;
    case 0x107u:
      gta2::MissionScriptObjectData_sub_47FAC0(pMissionScriptObjectData);
      return;
    case 0x108u:
      pMissionManager2 = gMissionManager;
      Index_1 = (int)pS28Arr[0];
      v322 = dword_6644CC;
      v323 = pMissionScriptObjectData;
      v324 = gta2::MissionManager_StartMission(gMissionManager, HIWORD(dword_6644CC->arr_96[1]));
      gta2::sub_475B10((void *)v324->arr_96[1]);
      v325 = gta2::MissionManager_StartMission(pMissionManager2, v322->arr_96[1]);
      v323->field_8 = v326 == v325->arr_96[1];
      gta2::MissionScriptObjectData_sub_476E50(v323, v322);
      return;
    case 0x109u:
      pS28Arr[0] = pMissionScriptObjectData;
      v327 = dword_6644CC;
      pMissionManager3 = gMissionManager;
      v329 = dword_6644CC->arr_96[1];
      pS28Arr[0] = pMissionScriptObjectData;
      v330 = gta2::MissionManager_StartMission(gMissionManager, v329);
      v331 = (void *)v330->arr_96[1];
      v332 = gta2::sub_476A90((_DWORD *)v330->arr_96[1]) - 3;
      if ( v332 )
      {
        v333 = v332 - 2;
        if ( v333 )
        {
          if ( v333 == 1 )
          {
            v334 = gta2::MissionManager_StartMission(pMissionManager3, HIWORD(v327->arr_96[1]));
            gta2::sub_4769E0(v331, 6, v334->arr_96[1]);
            gta2::sub_476A00((void *)v330->arr_96[1], *(_DWORD *)(v334->arr_96[1] + 108));
          }
        }
        else
        {
          v335 = gta2::MissionManager_StartMission(pMissionManager3, HIWORD(v327->arr_96[1]));
          gta2::sub_4769C0(v331, 5, v335->arr_96[1]);
          gta2::sub_476A00((void *)v330->arr_96[1], *(_DWORD *)(v335->arr_96[1] + 512));
        }
      }
      else
      {
        v336 = gta2::MissionManager_StartMission(pMissionManager3, HIWORD(v327->arr_96[1]));
        gta2::sub_4769E0(v331, 3, v336->arr_96[1]);
        gta2::sub_476A00((void *)v330->arr_96[1], *(_DWORD *)(v336->arr_96[1] + 108));
      }
      gta2::MissionScriptObjectData_sub_476E50(pS28Arr[0], v327);
      return;
    case 0x10Cu:
    case 0x10Du:
      Index_1 = (int)v546;
      pS28_12 = pMissionScriptObjectData;
      v348 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_476930((void *)v348->arr_96[1], *(_WORD *)(v347 + 10));
      v349 = (_BYTE *)v348->arr_96[1];
      if ( (gta2::sub_476960(v349) < 200 || gta2::sub_476960(v349) > 244) && (gta2::sub_476960(v349) < 64 || gta2::sub_476960(v349) > 108) )
      {
        gta2::sub_476980(v349);
        gta2::MissionScriptObjectData_sub_476E50(pS28_12, dword_6644CC);
      }
      else
      {
        gta2::sub_476970(v349);
        gta2::MissionScriptObjectData_sub_476E50(pS28_12, dword_6644CC);
      }
      return;
    case 0x10Eu:
      gta2::MissionManager_sub_4799D0(v599);
      return;
    case 0x10Fu:
      Index_1 = (int)pS28Arr[0];
      v360 = pMissionScriptObjectData;
      v362 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v364 = gta2::MissionManager_StartMission(pMissionManager4, *(_WORD *)(v361 + 10));
      gta2::Player_sub_4A6900(*(Player **)(v362->arr_96[1] + 348));
      gta2::Player_sub_4A6310(*(Player **)(v362->arr_96[1] + 348));
      gta2::Player_sub_4A6350(*(Player **)(v362->arr_96[1] + 348), (Car *)v364->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v360, dword_6644CC);
      return;
    case 0x112u:
      Index_1 = (int)v546;
      v526 = dword_6644CC;
      v527 = pMissionScriptObjectData;
      v528 = gta2::MissionManager_sub_474F00(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_47ECE0(v527, (int)v526, (int)v528 + 9);
      return;
    case 0x115u:
      v529 = pMissionScriptObjectData;
      SaveFile = gta2::MapGm_GetSaveFile(&gMapGm);
      gta2::MissionManager_SaveFile(gMissionManager, SaveFile);
      gta2::MissionScriptObjectData_sub_476E50(v529, dword_6644CC);
      return;
    case 0x116u:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      v365 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      switch ( HIWORD(pMissionManager46->arr_96[1]) )
      {
        case 1:
          gta2::Car_SetLocksDoor((Car *)v365->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
          break;
        case 2:
          gta2::Car_SetLocksDoor2((Car *)v365->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
          break;
        case 3:
          gta2::Car_sub_475C80((Car *)v365->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
          break;
        case 4:
          gta2::Car_SetLocksDoor_4((Car *)v365->arr_96[1]);
          gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
          break;
        case 5:
          gta2::sub_475C60((_DWORD *)v365->arr_96[1]);
          goto LABEL_729;
        default:
          goto LABEL_729;
      }
      return;
    case 0x11Bu:
      gta2::MissionScriptObjectData_sub_47CCC0(pMissionScriptObjectData);
      return;
    case 0x11Cu:
      v384 = pMissionScriptObjectData;
      pMissionScriptObjectData->field_8 = gta2::Game_sub_45BC10(
                                            gGame,
                                            (Player *)dword_6644CC->arr_96[1],
                                            (Player *)dword_6644CC->arr_96[2]) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v384, dword_6644CC);
      return;
    case 0x120u:
    case 0x121u:
    case 0x122u:
    case 0x123u:
      gta2::MissionScriptObjectData_sub_47CE00(pMissionScriptObjectData);
      return;
    case 0x124u:
    case 0x125u:
    case 0x126u:
      pS28_11 = pMissionScriptObjectData;
      v387 = gta2::MissionScriptObjectData_sub_478450(pMissionScriptObjectData, dword_6644CC->arr_96[1]);
      v266 = dword_6644CC;
      pS28_11->field_8 = 0;
      if ( v266->field_2 == 292 )
      {
        v388 = v387 == 0xFFFD;
LABEL_633:
        if ( v388 )
          pS28_11->field_8 = 1;
        goto LABEL_740;
      }
      if ( v266->field_2 == 293 )
      {
        v388 = v387 == 0xFFFC;
        goto LABEL_633;
      }
      if ( v266->field_2 == 294 && v387 != 0xFFFE )
      {
        Index_1 = (int)v266;
        pS28_11->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(pS28_11, (MissionManager *)Index_1);
        return;
      }
LABEL_740:
      gta2::MissionScriptObjectData_sub_476E50(pS28_11, v266);
      return;
    case 0x12Bu:
      Index_1 = (int)v546;
      v389 = dword_6644CC;
      v390 = pMissionScriptObjectData;
      gta2::CarSystemManager_sub_476630(gCarSystemManager, LOWORD(dword_6644CC->arr_96[1]));
      gta2::MissionScriptObjectData_sub_476E50(v390, v389);
      return;
    case 0x12Cu:
      v391 = pMissionScriptObjectData;
      pMissionScriptObjectData->field_8 = gta2::CarSystemManager_sub_476640(gCarSystemManager) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v391, dword_6644CC);
      return;
    case 0x12Fu:
      v557 = pMissionScriptObjectData;
      v394 = pMissionScriptObjectData;
      LOBYTE(v557) = dword_6644CC->arr_96[2];
      v395 = dword_6644CC->arr_96[1];
      Index_1 = (int)v557;
      v396 = gta2::MissionManager_StartMission(gMissionManager, v395);
      gta2::Car_sub_422E00((Car *)v396->arr_96[1], Index_1);
      gta2::MissionScriptObjectData_sub_476E50(v394, dword_6644CC);
      return;
    case 0x132u:
      Index_1 = (int)v546;
      v400 = pMissionScriptObjectData;
      v401 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      *(_DWORD *)(v401->arr_96[1] + 540) ^= ((unsigned __int8)*(_DWORD *)(v401->arr_96[1] + 540) ^ (unsigned __int8)(8 * *(_BYTE *)(v402 + 10))) & 8;
      gta2::MissionScriptObjectData_sub_476E50(v400, (MissionManager *)v402);
      return;
    case 0x133u:
    case 0x17Fu:
      pS28_11 = pMissionScriptObjectData;
      v403 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v404 = v403->arr_96[1];
      v405 = v266->arr_96[2];
      if ( v266->field_2 == 383 )
        *(_DWORD *)(v404 + 496) = v405;
      else
        *(_DWORD *)(v404 + 504) = v405;
      goto LABEL_740;
    case 0x134u:
    case 0x135u:
    case 0x151u:
    case 0x152u:
    case 0x153u:
      gta2::MissionScriptObjectData_sub_47D260(pMissionScriptObjectData);
      return;
    case 0x136u:
      Index_1 = (int)v546;
      v406 = dword_6644CC;
      v407 = pMissionScriptObjectData;
      v408 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_4762C0((Car *)v408->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v407, v406);
      return;
    case 0x137u:
    case 0x138u:
    case 0x139u:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      v409 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      switch ( pMissionManager46->field_2 )
      {
        case 0x137u:
          pCar2 = (Car *)v409->arr_96[1];
          if ( BYTE2(pMissionManager46->arr_96[1]) == 1 )
          {
            gta2::Car_sub_4218C0(pCar2);
            gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
            return;
          }
          gta2::Car_sub_4762F0(pCar2);
          break;
        case 0x138u:
          v411 = (Car *)v409->arr_96[1];
          if ( BYTE2(pMissionManager46->arr_96[1]) == 1 )
            gta2::Car_sub_4762D0(v411);
          else
            gta2::Car_sub_476300(v411);
          break;
        case 0x139u:
          pCar_1 = (Car *)v409->arr_96[1];
          if ( BYTE2(pMissionManager46->arr_96[1]) == 1 )
            gta2::Car_sub_4218D0(pCar_1);
          else
            gta2::Car_sub_476310(pCar_1);
          break;
      }
      goto LABEL_729;
    case 0x13Bu:
      gta2::MissionScriptObjectData_sub_47A3B0(pMissionScriptObjectData);
      return;
    case 0x13Cu:
      Index_1 = (int)pS28Arr[0];
      pS28_7 = pMissionScriptObjectData;
      v414 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v416 = gta2::MissionManager_StartMission(pMissionManager5, *(_WORD *)(v413 + 10));
      v417 = (SpriteS1 *)v416->arr_96[1];
      if ( v417 )
      {
        if ( v417->S3_arr5031[2].NextElement != (CarTransforms *)6 )
        {
          v418 = gta2::Car_sub_41E460((Car *)v416->arr_96[1]);
          v419 = v414->arr_96[1];
          if ( v419 )
          {
            Index = unk_664E60.Index;
            v572 = gAudioSourceParams;
            pS9 = (SpriteS1 *)gAudioSourceParams;
            v563 = *(_DWORD *)(v419 + 80);
            if ( v418 )
              pSpriteS1_2 = (SpriteS1 *)gta2::Turrel_sub_41FC70((Arsenal *)v417);
            else
              pSpriteS1_2 = (SpriteS1 *)v417->S3_arr5031[1].PositionX;
            gta2::SpriteS1_sub_4B9D50(pSpriteS1_2, v563, pS9, (int)v572, Index);
          }
        }
      }
      goto LABEL_828;
    case 0x13Du:
      v421 = pMissionScriptObjectData;
      gta2::HudBrief_Clear(&gHud->HudBrief_, (void *)1);
      gta2::HudBrief_Clear(&gHud->HudBrief_, (void *)3);
      gta2::MissionScriptObjectData_sub_476E50(v421, dword_6644CC);
      return;
    case 0x13Eu:
      Index_1 = (int)v546;
      v422 = dword_6644CC;
      v423 = pMissionScriptObjectData;
      v424 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      CopStars = gta2::Ped_GetCopStars((Ped *)v424->arr_96[1]);
      v594 = dword_6644CC;
      v423->field_8 = CopStars > SHIWORD(v422->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(v423, v594);
      return;
    case 0x13Fu:
      v558 = pS28Arr[0];
      pS28Arr[0] = pMissionScriptObjectData;
      Index_1 = (int)v558;
      v426 = pMissionScriptObjectData;
      switch ( HIWORD(dword_6644CC->arr_96[1]) )
      {
        case 0:
          LOBYTE(pS28Arr[0]) = 0;
          break;
        case 1:
          LOBYTE(pS28Arr[0]) = 1;
          break;
        case 2:
          LOBYTE(pS28Arr[0]) = 2;
          break;
        case 3:
          LOBYTE(pS28Arr[0]) = 3;
          break;
        default:
          break;
      }
      v427 = (_DWORD *)gMissionManager->field_328;
      if ( v427 && gMissionManager->field_314 == *v427 )
      {
        LOBYTE(pS28Arr[0]) = 2;
      }
      else if ( !LOBYTE(pS28Arr[0]) )
      {
        gta2::Game_SetState(gGame, 0, 4);
        gta2::MissionScriptObjectData_sub_476E50(v426, dword_6644CC);
        return;
      }
      gta2::Game_sub_45A480(gGame, 0, 4, (char)pS28Arr[0]);
      gta2::MissionScriptObjectData_sub_476E50(v426, dword_6644CC);
      return;
    case 0x140u:
      gta2::MissionScriptObjectData_sub_47D7A0(pMissionScriptObjectData);
      return;
    case 0x144u:
      Index_1 = (int)v546;
      v428 = dword_6644CC;
      v429 = pMissionScriptObjectData;
      v430 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v429->field_8 = (unsigned __int8)gta2::sub_475B50((_BYTE *)v430->arr_96[1]) != 0;
      gta2::MissionScriptObjectData_sub_476E50(v429, v428);
      return;
    case 0x145u:
      pMissionManager7 = pMissionScriptObjectData;
      pMissionScriptObjectData->field_8 = gta2::HudBrief_IsMessageVisible(&gHud->HudBrief_);
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager7, dword_6644CC);
      return;
    case 0x148u:
      pS28_22 = pMissionScriptObjectData;
      gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::MissionScriptObjectData_sub_475460(pS28_22, v433);
      gta2::MissionScriptObjectData_sub_476E50(pS28_22, dword_6644CC);
      return;
    case 0x149u:
      gta2::MissionScriptObjectData_sub_480080(pMissionScriptObjectData);
      return;
    case 0x14Au:
      pMissionManager9 = pMissionScriptObjectData;
      v534 = dword_6644CC;
      v536 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v538 = gta2::MissionManager_StartMission(pMissionManager8, *(_WORD *)(v535 + 16));
      Ped = gta2::Character_CreatePed(gCharacter);
      v536->arr_96[1] = (int)Ped;
      if ( Ped )
      {
        gta2::Ped_SetSearchType(Ped, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
        gta2::Ped_PutPedInCarRelated((Ped *)v536->arr_96[1], (Car *)v538->arr_96[1]);
        gta2::Ped_SetRemap((Ped *)v536->arr_96[1], v534->arr_96[2]);
        gta2::Ped_SetCurrentOccupation((Ped *)v536->arr_96[1], (ALL_PED)SHIWORD(v534->arr_96[2]));
        if ( !pMissionManager9->field_118 )
          gta2::S31_CreatePed2(gTrafficManager, (Ped *)v536->arr_96[1]);
      }
      pCar3 = (Car *)v538->arr_96[1];
      if ( pCar3 )
      {
        gta2::Car_CarMakeDriveable1(pCar3, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
        gta2::Car_CarMakeDriveable2((Car *)v538->arr_96[1]);
        gta2::EngineStruct_MakeDriveable3(*(EngineStruct **)(v538->arr_96[1] + 92), (Car *)v538->arr_96[1]);
        gta2::Car_CarMakeDriveable4((Car *)v538->arr_96[1]);
      }
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager9, dword_6644CC);
      return;
    case 0x14Cu:
    case 0x14Du:
    case 0x14Eu:
    case 0x14Fu:
    case 0x150u:
      gta2::MissionScriptObjectData_sub_47D360(pMissionScriptObjectData);
      return;
    case 0x154u:
      Index_1 = (int)v546;
      pMissionManager10 = pMissionScriptObjectData;
      v276 = SHIWORD(dword_6644CC->arr_96[1]);
      gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1] = v276;
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager10, v277);
      return;
    case 0x156u:
      pMissionManager11 = gMissionManager;
      v116 = dword_6644CC;
      pMissionManager13 = pMissionScriptObjectData;
      v118 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v119 = v118->arr_96[1];
      if ( v119 && gta2::Ped_IsPlayerControlled((Ped *)v118->arr_96[1]) )
      {
        v120 = gta2::MissionManager_StartMission(pMissionManager11, v116->arr_96[2]);
        gta2::Player_AddMoney(*(Player **)(v119 + 348), v120->arr_96[1]);
        v116 = dword_6644CC;
      }
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager13, v116);
      return;
    case 0x15Eu:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      if ( LOWORD(dword_6644CC->arr_96[1]) == 0xFFFF )
        gta2::CarSystemManager_sub_476650(gCarSystemManager, 87);
      else
        gta2::CarSystemManager_sub_476650(gCarSystemManager, LOWORD(dword_6644CC->arr_96[1]));
LABEL_684:
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager14, v68);
      return;
    case 0x15Fu:
    case 0x160u:
      v350 = dword_6644CC;
      pMissionManager15 = pMissionScriptObjectData;
      v352 = &dword_6644CC->arr_96[2];
      v353 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::sub_476950((_DWORD *)v353->arr_96[1], *(__int16 *)v352);
      gta2::sub_476930((void *)v353->arr_96[1], HIWORD(v350->arr_96[1]));
      v354 = *(_WORD *)v352;
      if ( (v354 < 200 || v354 > 244) && (v354 < 64 || v354 > 108) )
      {
        gta2::sub_476980((_BYTE *)v353->arr_96[1]);
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager15, dword_6644CC);
      }
      else
      {
        gta2::sub_476970((_BYTE *)v353->arr_96[1]);
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager15, dword_6644CC);
      }
      return;
    case 0x162u:
      gta2::MissionScriptObjectData_sub_47D9D0(pMissionScriptObjectData);
      return;
    case 0x163u:
      v397 = dword_6644CC;
      v398 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      Index_1 = (int)v397;
      pMissionManager16->field_8 = (*(unsigned __int8 *)(v398 + 540) >> 5) & 1;
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager16, (MissionManager *)Index_1);
      return;
    case 0x165u:
      gta2::MissionScriptObjectData_sub_47DAD0(pMissionScriptObjectData);
      return;
    case 0x166u:
    case 0x16Eu:
      gta2::MissionScriptObjectData_sub_47D860(pMissionScriptObjectData);
      return;
    case 0x167u:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      v434 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v435 = gta2::sub_475AF0((void *)v434->arr_96[1]);
      if ( v435 )
        v435->field_38 = pMissionManager46->arr_96[2];
      goto LABEL_729;
    case 0x168u:
      pMissionManager26 = pMissionScriptObjectData;
      pPed4 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( pPed4 )
        gta2::Ped_sub_43EC30(pPed4);
      goto LABEL_815;
    case 0x169u:
      Index_1 = (int)pS28Arr[0];
      v541 = dword_6644CC;
      pS28_7 = pMissionScriptObjectData;
      v542 = (Car *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      if ( !gta2::Car_IsEmergencyOrFbiCar((Car *)v542->PlayerStats_) )
        goto LABEL_828;
      carLights = (Car *)v542->PlayerStats_;
      if ( BYTE2(v541->arr_96[1]) == 1 )
      {
        gta2::Car_sub_422D20(carLights);
        gta2::MissionScriptObjectData_sub_476E50(pS28_7, dword_6644CC);
      }
      else
      {
        gta2::Car_sub_422D80(carLights);
LABEL_828:
        gta2::MissionScriptObjectData_sub_476E50(pS28_7, dword_6644CC);
      }
      return;
    case 0x16Au:
      Index_1 = (int)v546;
      v68 = dword_6644CC;
      pMissionManager14 = pMissionScriptObjectData;
      pS32 = (S32 *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( pS32 && gta2::S32_sub_40FEF0(pS32) == (S32 *)v68->arr_96[2] )
      {
LABEL_694:
        pMissionManager14->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager14, v68);
      }
      else
      {
LABEL_353:
        pMissionManager14->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager14, v68);
      }
      return;
    case 0x16Bu:
    case 0x180u:
    case 0x181u:
    case 0x1B0u:
      Index_1 = (int)v546;
      v440 = gMissionManager;
      pMissionManager18 = pMissionScriptObjectData;
      v442 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v444 = v442->arr_96[1];
      if ( v444 )
      {
        switch ( v443->field_2 )
        {
          case 0x16Bu:
            *(_WORD *)(v444 + 520) = BYTE2(v443->arr_96[1]) != 1 ? 0 : 9999;
            gta2::MissionScriptObjectData_sub_476E50(pMissionManager18, v443);
            break;
          case 0x180u:
            v445 = *(_DWORD *)(v444 + 540);
            if ( BYTE2(v443->arr_96[1]) == 1 )
              *(_DWORD *)(v444 + 540) = v445 | 0x10;
            else
              *(_DWORD *)(v444 + 540) = v445 & 0xFFFFFFEF;
            goto LABEL_704;
          case 0x181u:
            v446 = *(_DWORD *)(v444 + 540);
            if ( BYTE2(v443->arr_96[1]) == 1 )
              LOBYTE(v446) = v446 | 0x80;
            else
              LOBYTE(v446) = v446 & 0x7F;
            *(_DWORD *)(v444 + 540) = v446;
            gta2::MissionScriptObjectData_sub_476E50(pMissionManager18, v443);
            break;
          case 0x1B0u:
            v440->field_355 = BYTE2(v443->arr_96[1]);
            goto LABEL_704;
          default:
            goto LABEL_704;
        }
      }
      else
      {
LABEL_704:
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager18, v443);
      }
      return;
    case 0x16Cu:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      v438 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v439 = v438->arr_96[1];
      if ( v439 )
      {
        *(_DWORD *)(v439 + 620) = LOWORD(pMissionManager46->arr_96[2]);
        gta2::Ped_SetRemap((Ped *)v438->arr_96[1], BYTE2(pMissionManager46->arr_96[1]));
      }
      goto LABEL_729;
    case 0x16Du:
      Index_1 = (int)dword_6644CC;
      gCharacter->Bunt = BYTE2(dword_6644CC->arr_96[1]) == 1;
      gta2::MissionScriptObjectData_sub_476E50(pMissionScriptObjectData, (MissionManager *)Index_1);
      return;
    case 0x16Fu:
    case 0x17Du:
    case 0x17Eu:
      gta2::MissionScriptObjectData_sub_47DE70(pMissionScriptObjectData);
      return;
    case 0x170u:
      v10 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v11 = pMissionScriptObjectData;
      pPed5 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( gta2::Ped_IsInCar(pPed5) )
      {
        pCar6 = gta2::Ped_GetCarPlayers(pPed5);
        gta2::Car_sub_421540(pCar6);
      }
      goto LABEL_167;
    case 0x171u:
      pMissionManager37 = pMissionScriptObjectData;
      Index_1 = (int)v546;
      v449 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      pMissionManager37->field_8 = 0;
      v450 = (Ped *)v449->arr_96[1];
      if ( v450 )
      {
        if ( gta2::Ped_IsInCar((Ped *)v449->arr_96[1]) )
        {
          v451 = gta2::Ped_GetCarPlayers(v450);
          if ( gta2::PublicTransport_IsThisBus(gPublicTransport, v451)
            && gta2::PublicTransport_HasReachedBusSkipLimit(gPublicTransport) )
          {
            pMissionManager37->field_8 = 1;
          }
        }
      }
      goto LABEL_789;
    case 0x172u:
      Index_1 = (int)dword_6644CC;
      gPublicTransport->field_1818 = BYTE2(dword_6644CC->arr_96[1]) == 1;
      gta2::MissionScriptObjectData_sub_476E50(pMissionScriptObjectData, (MissionManager *)Index_1);
      return;
    case 0x173u:
      pMissionManager26 = pMissionScriptObjectData;
      pPed6 = (Ped *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( pPed6 )
        gta2::Ped_sub_4411B0(pPed6);
      goto LABEL_815;
    case 0x175u:
      pMissionManager21 = pMissionScriptObjectData;
      gta2::EntityManager_Defaut(gEntityManager, BYTE2(dword_6644CC->arr_96[1]));
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager21, dword_6644CC);
      return;
    case 0x176u:
      pMissionManager46 = dword_6644CC;
      Index_1 = (int)v546;
      pS28_8 = pMissionScriptObjectData;
      pCar_4 = (Car *)gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1];
      if ( !pCar_4 )
        goto LABEL_729;
      if ( BYTE2(pMissionManager46->arr_96[1]) == 1 )
      {
        gta2::Car_jam_accelerator(pCar_4);
        gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
      }
      else
      {
        gta2::Car_unjam_accelerator(pCar_4);
LABEL_729:
        gta2::MissionScriptObjectData_sub_476E50(pS28_8, pMissionManager46);
      }
      return;
    case 0x187u:
      pMissionManager45 = pMissionScriptObjectData;
      gta2::S31_sub_476BC0(gTrafficManager);
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager45, dword_6644CC);
      return;
    case 0x190u:
    case 0x197u:
      pMissionManager26 = pMissionScriptObjectData;
      if ( BYTE2(dword_6644CC->arr_96[1]) == 1 )
      {
        if ( dword_6644CC->field_2 == 400 )
        {
          gta2::MissionScriptObjectData_sub_3F10B0(pMissionScriptObjectData);
          gta2::sub_4A4E90(v456);
        }
        else
        {
          gta2::MissionScriptObjectData_sub_3F10B0(pMissionScriptObjectData);
          gta2::sub_4A4E50(v457);
        }
      }
      else if ( dword_6644CC->field_2 == 400 )
      {
        gta2::MissionScriptObjectData_sub_3F10B0(pMissionScriptObjectData);
        gta2::sub_4A4E80(v458);
      }
      else
      {
        gta2::MissionScriptObjectData_sub_3F10B0(pMissionScriptObjectData);
        gta2::Player_sub_4A69A0(v459);
      }
      goto LABEL_815;
    case 0x192u:
      gta2::MissionScriptObjectData_sub_47E210(pMissionScriptObjectData);
      return;
    case 0x198u:
      pS28_11 = pMissionScriptObjectData;
      v460 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v461 = v460->arr_96[1];
      if ( v461 )
        *(_DWORD *)(v461 + 628) = v266->arr_96[2];
      goto LABEL_740;
    case 0x199u:
      gta2::MissionScriptObjectData_sub_47E360(pMissionScriptObjectData);
      return;
    case 0x19Au:
      v97 = dword_6644CC;
      Index_1 = (int)v546;
      v98 = pMissionScriptObjectData;
      v582 = dword_6644CC->arr_96[2];
      v99 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::Ped_SetCurrentOccupation((Ped *)v99->arr_96[1], v582);
      gta2::MissionScriptObjectData_sub_476E50(v98, v97);
      return;
    case 0x19Bu:
      pS28Arr[0] = v546;
      pMissionManager23 = pMissionScriptObjectData;
      v463 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      pWeaponType1 = *(_DWORD *)(v464 + 12);
      if ( pWeaponType1 < 15 || pWeaponType1 > 27 )
      {
        gta2::sub_4A52B0(*(void **)(v463->arr_96[1] + 348), *(_DWORD *)(v464 + 12));
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager23, dword_6644CC);
      }
      else
      {
        Index_1 = v547;
        pPed7 = (Ped *)v463->arr_96[1];
        pWeaponType = pWeaponType1;
        pCar7 = gta2::Ped_GetCarPlayers(pPed7);
        gta2::Player_sub_4A5220(*(Player **)&pPed7->isPlayer, pCar7, pWeaponType);
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager23, dword_6644CC);
      }
      return;
    case 0x19Cu:
      pMissionManager24 = pMissionScriptObjectData;
      v469 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      gta2::Player_ProcessWeaponChange(*(Player **)(v469->arr_96[1] + 348));
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager24, dword_6644CC);
      return;
    case 0x19Eu:
      Index_1 = (int)v546;
      pMissionManager25 = pMissionScriptObjectData;
      v472 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v474 = gta2::MissionManager_StartMission(v473, *(_WORD *)(v471 + 10));
      LOWORD(v472->arr_96[1]) = gta2::S166_sub_4C9360(&gHud->S166_, (int)&v474->arr_96[1]);
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager25, dword_6644CC);
      return;
    case 0x19Fu:
    case 0x1A0u:
      pMissionManager26 = pMissionScriptObjectData;
      v475 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v477 = v475->arr_96[1];
      if ( v477 == 0xFFFF )
        goto LABEL_815;
      p_S166 = &gHud->S166_;
      v388 = *(_WORD *)(v476 + 2) == 415;
      Index_1 = v477;
      if ( v388 )
      {
        gta2::S166_sub_4C9410(p_S166, Index_1);
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager26, dword_6644CC);
      }
      else
      {
        gta2::S166_sub_4C93D0(p_S166, Index_1);
LABEL_815:
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager26, dword_6644CC);
      }
      return;
    case 0x1A2u:
      Index_1 = (int)v546;
      v479 = dword_6644CC;
      pMissionManager28 = pMissionScriptObjectData;
      gta2::MissionScriptObjectData_sub_475420(pMissionScriptObjectData, dword_6644CC);
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager28, v479);
      return;
    case 0x1A3u:
      pMissionManager26 = pMissionScriptObjectData;
      pPed8 = *(S169 **)(gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1])->arr_96[1] + 356);
      if ( pPed8 )
        gta2::S169_ManageGroupPedObjectives(pPed8);
      goto LABEL_815;
    case 0x1A4u:
      Index_1 = (int)v546;
      pMissionManager42 = dword_6644CC;
      pMissionManager27 = pMissionScriptObjectData;
      v483 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v484 = sub_4A4870(*(void **)(v483->arr_96[1] + 348));
      if ( v484 && *(_DWORD *)(v484 + 28) == pMissionManager42->arr_96[2] )
      {
LABEL_541:
        v588 = dword_6644CC;
        pMissionManager27->field_8 = 1;
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager27, v588);
      }
      else
      {
LABEL_756:
        v596 = dword_6644CC;
        pMissionManager27->field_8 = 0;
        gta2::MissionScriptObjectData_sub_476E50(pMissionManager27, v596);
      }
      return;
    case 0x1A6u:
      gta2::MissionScriptObjectData_sub_480430(pMissionScriptObjectData);
      return;
    case 0x1A7u:
      pS28Arr[0] = pMissionScriptObjectData;
      pMissionManager40 = dword_6644CC;
      pMissionManager29 = pMissionScriptObjectData;
      v487 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[5]);
      v489 = v487;
      if ( pMissionManager29->field_C )
      {
        v494 = (unsigned __int16 *)&pMissionManager40->arr_96[1];
        if ( gta2::MissionScriptObjectData_sub_478450(pMissionManager29, pMissionManager40->arr_96[1]) == 0xFFFE )
        {
          v495 = *v494;
          pMissionManager30 = gMissionManager;
          v497 = gta2::MissionManager_StartMission(gMissionManager, v495);
          gta2::sub_476660(&gGame->PlayerMain->field_47C, v497->arr_96[1]);
          v498 = gta2::MissionManager_StartMission(pMissionManager30, HIWORD(pMissionManager40->arr_96[3]));
          v498->arr_96[1] = v499;
          pPed_3 = (Ped *)v489->arr_96[1];
          if ( gta2::Ped_GetPedState(pPed_3) == 9 || (pPed_3->PositionX1 & 0x20) != 0 )
          {
            gta2::sub_476680(&gGame->PlayerMain->field_47C, v497->arr_96[1]);
            gta2::Player_ProcessWeaponChange(*(Player **)(v489->arr_96[1] + 348));
          }
        }
        else
        {
          pMissionManager41 = gta2::MissionManager_StartMission(gMissionManager, HIWORD(pMissionManager40->arr_96[1]));
          pS28Arr[0] = (MissionScriptObjectData *)pMissionManager41;
          if ( LOWORD(pMissionManager41->arr_96[1]) != 0xFFFF )
          {
            gta2::S166_sub_4C93B0(&gHud->S166_, LOWORD(pMissionManager41->arr_96[1]));
            pMissionManager41 = (MissionManager *)pS28Arr[0];
          }
          LOWORD(pMissionManager41->arr_96[1]) = 0;
          gta2::Player_ProcessWeaponChange(*(Player **)(v489->arr_96[1] + 348));
          gta2::MissionManager_sub_475A40(gMissionManager, 0);
          if ( gta2::MissionScriptObjectData_sub_478450(pMissionManager29, *v494) == 0xFFFD )
          {
            v502 = gta2::Text__Bsearch(gText, "kfpass");
            gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v502, 3);
            gta2::Ped_SetPoliceNoStar((Ped *)v489->arr_96[1]);
            ++*(_DWORD *)gMissionManager->field_338;
            v503 = HIWORD(pMissionManager40->arr_96[5]);
            if ( v503 == 1 )
            {
              gta2::Player_AddMoney(*(Player **)(v489->arr_96[1] + 348), pMissionManager40->arr_96[6]);
              gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_FRENZY_PASSED);
            }
            else if ( v503 == 2 )
            {
              gta2::Player_SetMultiPlayer(*(Player **)(v489->arr_96[1] + 348), pMissionManager40->arr_96[6]);
              gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_FRENZY_PASSED);
            }
            else
            {
              if ( v503 == 3 )
                gta2::Player_AddLives(*(Player **)(v489->arr_96[1] + 348), pMissionManager40->arr_96[6]);
              gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_FRENZY_PASSED);
            }
          }
          else
          {
            v504 = gta2::Text__Bsearch(gText, "kffail");
            gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v504, 3);
            ++*(_DWORD *)gMissionManager->field_33C;
            gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_FRENZY_FAILED);
          }
          gta2::MissionScriptObjectData_sub_476E50(pMissionManager29, dword_6644CC);
        }
      }
      else
      {
        v490 = gta2::MissionManager_StartMission(pMissionManager31, HIWORD(pMissionManager40->arr_96[1]));
        LOWORD(v490->arr_96[1]) = gta2::S166_sub_4C9310(&gHud->S166_, pMissionManager40->arr_96[2]);
        v491 = gta2::MissionManager_StartMission(gMissionManager, pMissionManager40->arr_96[3]);
        v493 = gta2::MissionManager_StartMission(pMissionManager33, HIWORD(pMissionManager40->arr_96[3]));
        LOWORD(v491->arr_96[1]) = gta2::S166_sub_4C9360(&gHud->S166_, (int)&v493->arr_96[1]);
        ++pMissionManager29->field_C;
      }
      return;
    case 0x1A8u:
      pMissionManager34 = pMissionScriptObjectData;
      gta2::MapGm_sub_45E5F0(&gMapGm, HIWORD(dword_6644CC->arr_96[1]));
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager34, dword_6644CC);
      return;
    case 0x1B1u:
      pMissionManager35 = pMissionScriptObjectData;
      v507 = dword_6644CC->arr_96[1];
      Index_1 = 30 * dword_6644CC->arr_96[2];
      v508 = gta2::MissionManager_StartMission(gMissionManager, v507);
      gta2::S166_sub_4C93F0(&gHud->S166_, LOWORD(v508->arr_96[1]), Index_1);
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager35, dword_6644CC);
      return;
    case 0x1B6u:
      gta2::MissionScriptObjectData_SaveToGames(pMissionScriptObjectData);
      return;
    case 0x1BAu:
      MissionManager36 = pMissionScriptObjectData;
      v509 = dword_6644CC;
      v510 = HIWORD(dword_6644CC->arr_96[1]);
      if ( v510 == -1 )
      {
        pS28Arr[0] = (MissionScriptObjectData *)dword_6644CC;
        gMissionManager->field_C1E70 = 87;
        gta2::MissionScriptObjectData_sub_476E50(MissionManager36, (MissionManager *)pS28Arr[0]);
      }
      else
      {
        gMissionManager->field_C1E70 = v510;
        gta2::MissionScriptObjectData_sub_476E50(MissionManager36, v509);
      }
      return;
    case 0x1BBu:
      pMissionScriptObjectData->field_8 = gMissionManager->field_C1E2E != 0;
      gta2::MissionScriptObjectData_sub_476E50(pMissionScriptObjectData, dword_6644CC);
      return;
    case 0x1BCu:
      v10 = dword_6644CC;
      Index_1 = (int)pS28Arr[0];
      v11 = pMissionScriptObjectData;
      v511 = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[1]);
      v512 = gta2::MissionScriptObjectData_sub_475010(v11, v511->field_2);
      if ( v512 == 3 )
      {
        gta2::TrafficManager_sub_476D50(gTrafficManager, (S32 *)v511->arr_96[1], 1);
        gta2::MissionScriptObjectData_sub_476E50(v11, v10);
      }
      else
      {
        if ( v512 == 10 )
          gta2::S31_sub_474ED0(gTrafficManager, (void *)v511->arr_96[1]);
LABEL_167:
        gta2::MissionScriptObjectData_sub_476E50(v11, v10);
      }
      return;
    case 0x1BDu:
    case 0x1BEu:
      MissionManager39 = pS28Arr[0];
      pS28Arr[0] = pMissionScriptObjectData;
      Index_1 = (int)MissionManager39;
      pMissionManager37 = pMissionScriptObjectData;
      LOBYTE(pS28Arr[0]) = 0;
      pGang_1 = gta2::Gangs_GetFirstUsedGang(gGangs);
      if ( dword_6644CC->field_2 == 445 )
      {
        for ( ; pGang_1; pGang_1 = gta2::Gangs_GetNextUsedGang(gGangs) )
        {
          *((_BYTE *)&gMissionManager->field_C1E2F + LOBYTE(pS28Arr[0])) = gta2::Gang_GetRespectForPlayer(pGang_1, 0);
          ++LOBYTE(pS28Arr[0]);
        }
      }
      else
      {
        for ( ; pGang_1; pGang_1 = gta2::Gangs_GetNextUsedGang(gGangs) )
        {
          gta2::Gang_SetRespectForPlayer(pGang_1, 0, *((_BYTE *)&gMissionManager->field_C1E2F + LOBYTE(pS28Arr[0])));
          ++LOBYTE(pS28Arr[0]);
        }
      }
LABEL_789:
      gta2::MissionScriptObjectData_sub_476E50(pMissionManager37, dword_6644CC);
      return;
    default:
      gta2::MissionScriptObjectData_sub_476E50(pMissionScriptObjectData, started);
      return;
  }
}


// 0x00481120: MissionScriptObjectData::sub_481120
// IDA: MissionScriptObjectData::sub_481120
// Ghidra: ---
bool gta2::MissionScriptObjectData_sub_481120(struct MissionScriptObjectData *self)
{
  unsigned __int16 v3; // dx
  MissionManager *started; // edi
  bool v5; // zf
  MissionManager *v6; // edi

  if ( self->field_10 == 1 )
    return 1;
  started = gta2::MissionManager_StartMission(gMissionManager, self->field_4);
  if ( !started )
    strcpy(gStr, "Miss2: accessing nonexistant mission line. Current uid: %d", v3);
  gta2::MissionScriptObjectData_sub_47F550(self);
  if ( started->field_2 == 63 )
  {
    do
      gta2::MissionScriptObjectData_sub_4805B0(self);
    while ( self->field_12 > 0 );
    v5 = self->field_4 == -1;
    self->field_12 = 0;
    return v5;
  }
  else
  {
    if ( HIWORD(started->arr_96[0]) == 1 )
    {
      while ( 1 )
      {
        v6 = gta2::MissionManager_StartMission(gMissionManager, self->field_4);
        gta2::MissionScriptObjectData_sub_4805B0(self);
        if ( HIWORD(v6->arr_96[0]) != 1 || self->field_4 == -1 )
          break;
        if ( self->field_12 )
        {
          v5 = self->field_4 == -1;
          self->field_12 = 0;
          return v5;
        }
      }
    }
    else
    {
      gta2::MissionScriptObjectData_sub_4805B0(self);
    }
    v5 = self->field_4 == -1;
    self->field_12 = 0;
    return v5;
  }
}


// 0x00481270: MissionScriptObjectData::sub_481270
// IDA: MissionScriptObjectData::sub_481270
// Ghidra: ---
char gta2::MissionScriptObjectData_sub_481270(struct MissionScriptObjectData *self)
{
  char v2; // bp
  int v3; // edi
  MissionManager *started; // esi
  char result; // al
  int v6; // [esp+10h] [ebp-4h]

  v2 = 0;
  v3 = 794228;
  v6 = 25;
  do
  {
    if ( ((1 << v2) & unk_6646C0) != 0 )
    {
      started = gta2::MissionManager_StartMission(gMissionManager, *(__int16 *)((char *)&gMissionManager->field_0 + v3));
      gta2::sub_478240(started->arr_96[1]);
      gta2::MissionScriptObjectData_sub_47F760(self, started->arr_96[2]);
    }
    ++v2;
    v3 += 2;
    result = --v6;
  }
  while ( v6 );
  return result;
}



