#include "gta2_shim.h"

// Module: other, Class: S28
// Functions: 9
// Source: unified (IDA+Ghidra)

// 0x00475010: S28::sub_475010
// IDA: S28::sub_475010
// Ghidra: FUN_00475010
byte gta2::S28_sub_475010(void *self,uint param_1)
{
  if (param_1 < 0x28) {
    if (0x23 < param_1) {
      return 4;
    }
    switch(param_1) {
    case 5:
    case 6:
    case 7:
    case 8:
switchD_00475032_caseD_5:
      return 1;
    case 9:
    case 10:
    case 0xb:
      goto switchD_00475032_caseD_9;
    default:
      goto switchD_00475032_caseD_c;
    case 0xe:
    case 0xf:
    case 0x10:
    case 0x11:
    case 0x12:
    case 0x13:
    case 0x14:
switchD_00475032_caseD_e:
      return 3;
    case 0x19:
    case 0x1a:
    case 0x1b:
      return 5;
    case 0x1c:
    case 0x1f:
    case 0x20:
      return 7;
    case 0x21:
    case 0x22:
    case 0x23:
      return 6;
    }
  }
  if (param_1 < 0xdb) {
    if (0xd8 < param_1) {
      return 8;
    }
    switch(param_1) {
    case 0x29:
    case 0x2a:
      goto switchD_00475032_caseD_5;
    case 0x2b:
    case 0x2c:
      goto switchD_00475032_caseD_9;
    default:
switchD_00475032_caseD_c:
      return 0;
    case 0x2f:
    case 0x30:
    case 0x31:
    case 0x32:
    case 0x33:
    case 0x34:
      goto switchD_00475032_caseD_e;
    }
  }
  switch(param_1) {
  case 0x11f:
    return 9;
  default:
    goto switchD_00475032_caseD_c;
  case 0x146:
  case 0x147:
  case 0x148:
    return 10;
  case 0x1a9:
  case 0x1aa:
  case 0x1ab:
  case 0x1ac:
switchD_00475032_caseD_9:
    return 2;
  }
}


// 0x004751f0: S28::sub_4751F0
// IDA: S28::sub_4751F0
// Ghidra: FUN_004751f0
void gta2::S28_sub_4751F0(undefined4 param_1,int param_2,int param_3)
{
  gta2::Ped_PedSetObjective(*(Ped **)(param_3 + 8),(int)*(short *)(param_2 + 10),9999);
  *(uint *)(*(int *)(param_3 + 8) + 0x21c) =
       *(uint *)(*(int *)(param_3 + 8) + 0x21c) & 0xfffffbff;
  return;
}


// 0x00475420: S28::sub_475420
// IDA: S28::sub_475420
// Ghidra: ---
char gta2::S28_sub_475420(struct MissionScriptObjectData *self, MissionManager *a2)
{
  char result; // al

  if ( BYTE2(a2->arr_96[1]) )
  {
    result = (char)gPolice;
    gPolice->MaxFrameRateChek = BYTE2(a2->arr_96[1]);
  }
  else
  {
    gSkilPolice = 0;
    result = BYTE2(a2->arr_96[1]);
    gPolice->MaxFrameRateChek = result;
  }
  return result;
}


// 0x00475460: S28::sub_475460
// IDA: S28::sub_475460
// Ghidra: ---
char gta2::S28_sub_475460(struct MissionScriptObjectData *self, int a2)
{
  int *v2; // eax
  int v4; // [esp+8h] [ebp+8h]

  if ( *(_BYTE *)(a2 + 25) )
    v2 = gta2::Object_sub_485320(
           gObject,
           (S900 *)0x117,
           *(_BYTE *)(a2 + 24),
           *(_DWORD *)(a2 + 12),
           *(_DWORD *)(a2 + 16),
           *(_DWORD *)(a2 + 20));
  else
    v2 = gta2::Object_sub_485320(
           gObject,
           (S900 *)0x116,
           *(_BYTE *)(a2 + 24),
           *(_DWORD *)(a2 + 12),
           *(_DWORD *)(a2 + 16),
           *(_DWORD *)(a2 + 20));
  *(_DWORD *)(v4 + 8) = v2;
  return (char)v2;
}


// 0x00477a00: S28::sub_477A00
// IDA: S28::sub_477A00
// Ghidra: ---
char gta2::S28_sub_477A00(struct MissionScriptObjectData *self, int a2)
{
  unsigned __int8 *v2; // esi
  _DWORD *v3; // eax
  unsigned __int8 v4; // dl
  S202 *v5; // eax
  int *v6; // edi
  S202 *v7; // eax
  SpriteS1 *v8; // eax
  unsigned __int8 v9; // dl
  int *v10; // ebx
  int v11; // ecx
  S202 v13; // [esp-Ch] [ebp-2Ch] BYREF
  int v14; // [esp+14h] [ebp-Ch] BYREF
  char v15; // [esp+18h] [ebp-8h] BYREF
  int v16; // [esp+1Ch] [ebp-4h] BYREF

  v2 = (unsigned __int8 *)a2;
  v3 = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 16));
  if ( v3[2] )
  {
    v4 = v2[19];
    a2 = 2;
    v13.field_18 = 4;
    gta2::S202_sub_40CE30((S202 *)&v14, v4);
    v6 = (int *)gta2::S202_sub_401B20(v5, (SpriteS1 *)&v13.field_1C, (PublicTransport *)&unk_664E08);
    gta2::S202_sub_40CE30((S202 *)&v16, v2[18]);
    v8 = gta2::S202_sub_401B20(v7, (SpriteS1 *)&v15, (PublicTransport *)&unk_664E08);
    v9 = v2[20];
    v10 = (int *)v8;
    v13.CarSystemManager = (CarSystemManager *)unk_664E08.field_0;
    v13.S202 = (S202 *)unk_664E08.field_0;
    v13.field_0 = v11;
    gta2::S202_sub_40CE30(&v13, v9);
    LOBYTE(v3) = gta2::MissionObjective_sub_4C4F30(
                   gMissionObjective,
                   &v13.field_18,
                   &a2,
                   (int)v2,
                   *v10,
                   *v6,
                   v13.field_0,
                   (int)v13.S202,
                   (int)v13.CarSystemManager);
    v2[21] = (unsigned __int8)v3;
    v2[22] = 1;
  }
  return (char)v3;
}


// 0x00477b70: S28::sub_477B70
// IDA: S28::sub_477B70
// Ghidra: ---
char gta2::S28_sub_477B70(struct MissionScriptObjectData *self, int a2)
{
  int v2; // edx
  void *v3; // esi
  MissionManager *v4; // ecx
  void *v5; // edi
  int v6; // eax
  EventHandler *v7; // ecx
  int v8; // eax
  int v10; // [esp-8h] [ebp-10h]
  __int16 v11; // [esp-4h] [ebp-Ch]
  __int16 *v12; // [esp+10h] [ebp+8h]

  v3 = gta2::MissionManager_StartMission(gMissionManager, *(_WORD *)(a2 + 16));
  v5 = gta2::MissionManager_StartMission(v4, *(_WORD *)(v2 + 18));
  v6 = *((_DWORD *)v3 + 2);
  if ( v6 )
  {
    v7 = (EventHandler *)*((_DWORD *)v5 + 2);
    if ( v7 )
    {
      gta2::S63_sub_483C50(v7);
      v11 = *v12;
      v10 = *(_DWORD *)(*((_DWORD *)v5 + 2) + 20);
      v8 = gta2::Ped_sub_420B60(*((Ped **)v3 + 2));
      LOBYTE(v6) = (unsigned __int8)gta2::MissionManager_sub_476370(gMissionManager, v8, v10, v11);
    }
  }
  return v6;
}


// 0x0047f550: S28::sub_47F550
// IDA: S28::sub_47F550
// Ghidra: ---
char gta2::S28_sub_47F550(struct MissionScriptObjectData *self)
{
  struct Player *MissionPtrMaybe; // eax
  struct Player *Player; // edi
  int v4; // eax
  __int16 v5; // si
  unsigned __int8 v6; // al
  _DWORD *v7; // edx
  unsigned __int16 v8; // ax
  _DWORD *v9; // edx
  _DWORD *int_A; // edx
  wchar_t *v11; // eax
  char v13; // [esp+7h] [ebp-1h] BYREF

  LOBYTE(MissionPtrMaybe) = (_BYTE)gMissionManager;
  if ( gMissionManager->field_355 )
  {
    MissionPtrMaybe = (Player *)gMissionManager->MissionPtrMaybe;
    if ( MissionPtrMaybe )
    {
      if ( MissionPtrMaybe->CurrentPlayer == (Player *)1 )
      {
        Player = gGame->PlayerMain;
        if ( gta2::Player_sub_476700(Player)
          || (LOBYTE(MissionPtrMaybe) = gta2::Player_sub_476730(Player), (_BYTE)MissionPtrMaybe) )
        {
          gta2::S29_sub_474FF0(self->S29_, 2u);
          gta2::MissionScriptObjectData_sub_478610(self);
          v4 = -gta2::Player_sub_476700(gGame->PlayerMain);
          LOBYTE(v4) = v4 & 0xFB;
          v5 = v4 + 5;
          v13 = 5;
          v6 = gta2::Random_PauseGame((Game *)&gRandom, (S410 *)&v13);
          v7 = (_DWORD *)gMissionManager->field_348;
          if ( v7 && *v7 == 1 )
          {
            v8 = v5 + gMissionManager->field_356 + v6;
          }
          else
          {
            v9 = (_DWORD *)gMissionManager->field_34C;
            if ( v9 && *v9 == 1 )
            {
              v8 = v5 + gMissionManager->field_358 + v6;
            }
            else
            {
              int_A = (_DWORD *)gMissionManager->int_A;
              if ( int_A && *int_A == 1 )
                v8 = v5 + gMissionManager->field_35A + v6;
              else
                v8 = 8001;
            }
          }
          strcpy(gStr, "%d", v8);
          gta2::HudBrief_Clear(&gHud->HudBrief_, (void *)1);
          gta2::HudBrief_Clear(&gHud->HudBrief_, (void *)3);
          gta2::HudBrief_ShowMessageToPlayer(&gHud->HudBrief_, 1, gStr);
          v11 = gta2::Text__Bsearch(gText, "mfail");
          gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v11, 3);
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_JOB_FAILED);
          *(_DWORD *)gMissionManager->MissionPtrMaybe = 0;
          gMissionManager->field_C1E2E = 1;
          MissionPtrMaybe = gGame->PlayerMain;
          MissionPtrMaybe->MainPed->Invulnerability = GRAPHIC_EMERG;
        }
      }
    }
  }
  return (char)MissionPtrMaybe;
}


// 0x0047f710: S28::sub_47F710
// IDA: S28::sub_47F710
// Ghidra: ---
int gta2::S28_sub_47F710(struct MissionScriptObjectData *self, int a2)
{
  int result; // eax
  char v3; // cl
  int v4; // [esp+Ch] [ebp+8h]

  result = gta2::S115_sub_469010(
             gS115,
             *(_DWORD *)(a2 + 12),
             *(_DWORD *)(a2 + 16),
             *(_DWORD *)(a2 + 20),
             *(_DWORD *)(a2 + 24),
             *(_DWORD *)(a2 + 28),
             *(_BYTE *)(a2 + 32));
  *(_DWORD *)(v4 + 8) = result;
  v3 = *(_BYTE *)(a2 + 33);
  if ( v3 )
    return gta2::S115_sub_469070(gS115, result, v3, *(_BYTE *)(a2 + 34), *(_BYTE *)(a2 + 35));
  return result;
}


// 0x0047f9c0: S28::S28_Des
// IDA: S28::S28_Des
// Ghidra: ---
S29 * gta2::S28_S28_Des(struct MissionScriptObjectData *self)
{
  struct S29 *S29; // ecx
  struct S29 *result; // eax

  S29 = self->S29_;
  if ( S29 )
  {
    result = gta2::S29_S29_Des(S29, 1);
    self->S29_ = 0;
  }
  self->NextElement = 0;
  return result;
}



