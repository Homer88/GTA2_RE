#include "gta2_shim.h"

// Module: other, Class: PlayerStats
// Functions: 22
// Source: unified (IDA+Ghidra)

// 0x004a4f10: PlayerStats::sub_4A4F10
// IDA: PlayerStats::sub_4A4F10
// Ghidra: FUN_004a4f10
void gta2::PlayerStats_sub_4A4F10(void)
{
  gta2::FUN_0041d910();
  return;
}


// 0x004a50b0: PlayerStats::SetMonyeLives
// IDA: PlayerStats::SetMonyeLives
// Ghidra: ---
int gta2::PlayerStats_SetMonyeLives(struct PlayerStats *self, int a2)
{
  int Max; // edx
  int result; // eax

  Max = self->Max;
  result = -Max;
  if ( a2 >= -Max )
  {
    if ( a2 <= Max )
      self->MoneyValue = a2;
    else
      self->MoneyValue = Max;
  }
  else
  {
    self->MoneyValue = result;
  }
  return result;
}


// 0x004b73f0: PlayerStats::Money
// IDA: PlayerStats::Money
// Ghidra: ---
PlayerStats * gta2::PlayerStats_Money(struct PlayerStats *self)
{
  gta2::PlayerStats_Lives(self);
  gta2::PlayerStats_Lives((struct PlayerStats *)&self->PlayerStats1);
  gta2::S165_S165(&self->S165_);
  self->field_74 = 1;
  self->field_75 = 1;
  self->sPlayer = 0;
  self->field_18C = 0;
  self->fly_car = 0;
  self->field_70 = 0;
  self->Cycle1 = 0;
  self->excutin = 0;
  self->gencide = 0;
  self->copkill = 0;
  self->carjaka = 0;
  self->field_80 = 0;
  self->elvis_d = 0;
  self->field_194 = 0;
  self->accurcy = 0;
  self->wrngway = 0;
  self->Cycle = 0;
  self->em_dest = 0;
  memset(self->Arr_int_64, 0, sizeof(self->Arr_int_64));
  return self;
}


// 0x004b7490: PlayerStats::sub_4B7490
// IDA: PlayerStats::sub_4B7490
// Ghidra: ---
int gta2::PlayerStats_sub_4B7490(
        struct PlayerStats *self,
        Player *pPlayer,
        __int16 a3,
        int a4,
        __int16 a5,
        unsigned __int16 a6)
{
  int result; // eax

  self->sPlayer = pPlayer;
  gta2::PlayerStats_sub_44B220(self, a3, a4, a5);
  LOBYTE(result) = gta2::PlayerStats_sub_44B220((struct PlayerStats *)&self->PlayerStats1, a3, a6, a5);
  return result;
}


// 0x004b74d0: PlayerStats::sub_4B74D0
// IDA: PlayerStats::sub_4B74D0
// Ghidra: ---
PlayerStats * gta2::PlayerStats_sub_4B74D0(struct PlayerStats *self)
{
  return self;
}


// 0x004b7500: PlayerStats::sub_4B7500
// IDA: PlayerStats::sub_4B7500
// Ghidra: FUN_004b7500
uint gta2::PlayerStats_sub_4B7500(void *self,byte param_1,char param_2)
{
  int iVar1;
  uint uVar2;
  
  iVar1 = gta2::CarEngines_sub_4327E0(gCarEngines,param_1);
  uVar2 = (uint)*(byte *)(iVar1 + 2);
  if (param_2 != '\0') {
    if (param_2 != '\x01') {
      if (param_2 != '\x02') {
        return 0;
      }
      return uVar2 * 5;
    }
    uVar2 = uVar2 * 2;
  }
  return uVar2;
}


// 0x004b7570: PlayerStats::sub_4B7570
// IDA: PlayerStats::sub_4B7570
// Ghidra: ---
PlayerStats * gta2::PlayerStats_sub_4B7570(struct PlayerStats *self)
{
  return (struct PlayerStats *)&self->PlayerStats1;
}


// 0x004b7580: PlayerStats::sub_4B7580
// IDA: PlayerStats::sub_4B7580
// Ghidra: ---
int gta2::PlayerStats_sub_4B7580(struct PlayerStats *self, int a2)
{
  return gta2::PlayerStats_SetMultiPlayer((struct PlayerStats *)&self->PlayerStats1, a2);
}


// 0x004b75b0: PlayerStats::sub_4B75B0
// IDA: PlayerStats::sub_4B75B0
// Ghidra: ---
char gta2::PlayerStats_sub_4B75B0(struct PlayerStats *self, char a2)
{
  char result; // al
  CarModel v4; // edi
  byte *Arr_int_64; // esi
  struct Style *pStyle_1; // ebp
  byte *v7; // esi
  CarModel v8; // edi
  struct Style *pStyle; // ebp
  BYTE ModelID; // cl
  byte v11; // al

  result = a2;
  if ( (a2 & 1) != 0 )
  {
    v4 = ALFA;
    Arr_int_64 = self->Arr_int_64;
    do
    {
      pStyle_1 = gStyle;
      if ( gta2::Style_CarExist(gStyle, v4) && gta2::Style_isCarRecyclable(pStyle_1, v4) )
        result = *Arr_int_64 & 254;
      else
        result = *Arr_int_64 | 1;
      *Arr_int_64 = result;
      ++v4;
      ++Arr_int_64;
    }
    while ( (unsigned __int16)v4 < 256u );
  }
  if ( (a2 & 2) != 0 )
  {
    v7 = self->Arr_int_64;
    v8 = ALFA;
    while ( 1 )
    {
      pStyle = gStyle;
      if ( !gta2::Style_CarExist(gStyle, v8) || !gta2::Style_isCarRecyclable(pStyle, v8) )
        break;
      ModelID = *(_BYTE *)(gta2::Style_GetCarModelById(gStyle, v8) + 6);
      v11 = *v7;
      if ( ModelID == 99 )
        goto LABEL_15;
      result = v11 & 253;
LABEL_16:
      *v7 = result;
      ++v8;
      ++v7;
      if ( (unsigned __int16)v8 >= 256u )
        return result;
    }
    v11 = *v7;
LABEL_15:
    result = v11 | 2;
    goto LABEL_16;
  }
  return result;
}


// 0x004b7660: PlayerStats::sub_4B7660
// IDA: PlayerStats::sub_4B7660
// Ghidra: ---
int gta2::PlayerStats_sub_4B7660(struct PlayerStats *self, int a2)
{
  int result; // eax
  char Id; // al

  gta2::PlayerStats_SetMultiPlayer(self, a2);
  result = gNetworkGame;
  if ( gNetworkGame )
  {
    Id = gta2::Player_GetId(self->sPlayer);
    return (int)gta2::MapGm_sub_45E7C0(&gMapGm, Id, a2);
  }
  return result;
}


// 0x004b7770: PlayerStats::sub_4B7770
// IDA: PlayerStats::sub_4B7770
// Ghidra: ---
unsigned int gta2::PlayerStats_sub_4B7770(struct PlayerStats *self)
{
  struct Ped *Ped; // ebp
  unsigned int v3; // edx
  struct Car *CarPlayers; // edi
  unsigned __int8 CopStars; // al
  struct Player *sPlayer; // ecx
  wchar_t *v7; // eax
  struct Player *Player; // ecx
  wchar_t *v9; // eax
  struct Player *pPlayer5; // ecx
  wchar_t *v11; // eax
  struct Player *pPlayer4; // ecx
  wchar_t *v13; // eax
  struct Player *pPlayer3; // ecx
  wchar_t *v15; // eax
  struct Player *pPlayer6; // ecx
  wchar_t *v17; // eax
  struct Player *pPlayer2; // ecx
  wchar_t *v19; // eax
  struct Car *v20; // eax
  struct Player *v21; // eax
  struct Player *pPlayer1; // ecx
  wchar_t *v23; // eax
  struct Car *PCar1; // edi
  struct Player *v25; // ecx
  struct Car *pCar; // eax
  unsigned int fly_car; // eax
  struct Player *v28; // ecx
  wchar_t *v29; // eax
  char _45E700; // bl
  int v31; // eax
  char v32; // di
  int v33; // ebp
  int PlayerID; // eax
  wchar_t *v35; // eax
  int Cycle; // eax
  unsigned int result; // eax
  int pPlayerID; // [esp+10h] [ebp-4h] BYREF
                                                // ????????? ??????????
                                                // 
  gta2::S165_sub_41DCC0(&self->S165_);
  Ped = gta2::Player_GetPed(self->sPlayer);
  v3 = gta2::Game_sub_45A460(gGame) + self->field_18C;
  self->field_18C = v3;
  if ( v3 >= 1000 )
  {
    self->field_18C = v3 - 1000;
    if ( gta2::Ped_IsInCar(Ped) && gta2::Ped_IsTargetCarDoor(Ped) )
    {
      CarPlayers = gta2::Ped_GetCarPlayers(Ped);
      if ( gta2::Car_has_for_hire_lights(CarPlayers) && !gta2::Passenger_Passenger_des((struct Passenger *)&CarPlayers->Passenger_) )
        gta2::Player_AddMoney(self->sPlayer, 1);
    }
    if ( gta2::Ped_GetPoliceStar(Ped) >= 5000 )
      gta2::Player_AddMoney(self->sPlayer, 1);
    CopStars = gta2::Ped_GetCopStars(Ped);
    gta2::sub_44A010(&self->sPlayer->field_644, CopStars);
  }
  if ( self->excutin >= 20u )
  {
    sPlayer = self->sPlayer;
    self->excutin = 0;
    gta2::Player_AddMoney(sPlayer, 100000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v7 = gta2::Text__Bsearch(gText, "excutin");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v7, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_EXPEDITIOUS_EXECUTION);
    }
  }
  if ( self->elvis_d >= 6u )
  {
    Player = self->sPlayer;
    self->elvis_d = 0;
    gta2::Player_AddMoney(Player, 30000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v9 = gta2::Text__Bsearch(gText, "elvis_d");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v9, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_ELVIS_HAS_LEFT_THE_BUILDING);
    }
  }
  if ( self->em_dest == 7 )
  {
    pPlayer5 = self->sPlayer;
    self->em_dest = 0;
    gta2::Player_AddMoney(pPlayer5, 10000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v11 = gta2::Text__Bsearch(gText, "em_dest");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v11, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_MEDICAL_EMERGENCY);
    }
  }
  if ( self->gencide >= 1000u )
  {
    pPlayer4 = self->sPlayer;
    self->gencide = 0;
    gta2::Player_AddMoney(pPlayer4, 30000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v13 = gta2::Text__Bsearch(gText, "gencide");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v13, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_GENOCIDE);
    }
  }
  if ( self->copkill >= 20u )
  {
    pPlayer3 = self->sPlayer;
    self->copkill = 0;
    gta2::Player_AddMoney(pPlayer3, 5000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v15 = gta2::Text__Bsearch(gText, "copkill");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v15, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_COP_KILLA);
    }
  }
  if ( self->carjaka >= 0x64u )
  {
    pPlayer6 = self->sPlayer;
    self->carjaka = 0;
    gta2::Player_AddMoney(pPlayer6, 10000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v17 = gta2::Text__Bsearch(gText, "carjaka");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v17, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_CAR_JACKA);
    }
  }
  if ( self->accurcy >= 25u )
  {
    pPlayer2 = self->sPlayer;
    self->accurcy = 0;
    gta2::Player_AddMoney(pPlayer2, 5000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v19 = gta2::Text__Bsearch(gText, "accurcy");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v19, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_ACCURACY_BONUS);
    }
  }
  if ( gta2::Ped_GetPoliceStar(Ped) > 3000
    && gta2::Ped_IsInCar(Ped)
    && gta2::Ped_IsTargetCarDoor(Ped)
    && (v20 = gta2::Ped_GetCarPlayers(Ped)) != 0
    && (v21 = v20->Player_) != 0
    && gta2::Player_sub_411810(v21) )
  {
    self->wrngway += gta2::Game_sub_45A460(gGame);
  }
  else
  {
    self->wrngway = 0;
  }
  if ( self->wrngway >= 60000u )
  {
    pPlayer1 = self->sPlayer;
    self->wrngway = 0;
    gta2::Player_AddMoney(pPlayer1, 1000);
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      v23 = gta2::Text__Bsearch(gText, "wrngway");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v23, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_BACK_TO_FRONT_BONUS);
    }
  }
  if ( gta2::Ped_IsInCar(Ped)
    && gta2::Ped_IsTargetCarDoor(Ped)
    && (PCar1 = gta2::Ped_GetCarPlayers(Ped), (v25 = PCar1->Player_) != 0)
    && gta2::Player_sub_49DD80(v25)
    && (pCar = gta2::Car_sub_421EC0(PCar1, &pPlayerID), gta2::Car_sub_403800(pCar, (int)&unk_66F258)) )
  {
    self->fly_car += gta2::Game_sub_45A460(gGame);
  }
  else
  {
    self->fly_car = 0;
  }
  fly_car = self->fly_car;
  if ( fly_car >= 1250 && fly_car < 2250 )
  {
    gta2::Player_AddMoney(self->sPlayer, 1000);
    v28 = self->sPlayer;
    self->fly_car = 2250;
    if ( gta2::Player_GetCurrentPlayer(v28) )
    {
      v29 = gta2::Text__Bsearch(gText, "fly_car");
      gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v29, 1);
      gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_INSANE_STUNT_BONUS);
    }
  }
  if ( gNetworkGame )
  {
    LOBYTE(pPlayerID) = gta2::Player_GetId(self->sPlayer);
    _45E700 = gta2::MapGm_get_45E700(&gMapGm);
    v31 = gta2::MapGm_ShowLimitFrame(&gMapGm);
    v32 = pPlayerID;
    v33 = v31;
    switch ( _45E700 )
    {
      case 1:
        PlayerID = gta2::MapGm_GetPlayerID(&gMapGm, pPlayerID);
        break;
      case 2:
        PlayerID = gta2::MapGm_GetPlayerArena_0(&gMapGm, pPlayerID);
        break;
      case 3:
        goto LABEL_64;
      default:
        PlayerID = pPlayerID;
        break;
    }
    if ( PlayerID >= v33 )
    {
      gta2::MapGm_sub_45E740(&gMapGm, v32);
      if ( !gta2::Game_IsDeadPlayer(gGame) )
      {
        v35 = gta2::Text__Bsearch(gText, "g_over");
        gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v35, 3);
      }
      gta2::Game_SetState(gGame, 2, 5);
    }
  }
LABEL_64:
  Cycle = gta2::General_GetCycle(gGeneral);
  if ( (unsigned int)(Cycle - self->field_70) > 0xF )
    self->field_74 = 1;
  result = Cycle - self->Cycle1;
  if ( result > 0xF )
    self->field_75 = 1;
  return result;
}


// 0x004b7d50: PlayerStats::sub_4B7D50
// IDA: PlayerStats::sub_4B7D50
// Ghidra: ---
char gta2::PlayerStats_sub_4B7D50(struct PlayerStats *self)
{
  gta2::PlayerStats_sub_44B260(self);
  gta2::PlayerStats_sub_44B260((struct PlayerStats *)&self->PlayerStats1);
  gta2::S165_sub_41D930(&self->S165_, self);
  return gta2::PlayerStats_sub_4B75B0(self, 3);
}


// 0x004b7d80: PlayerStats::sub_4B7D80
// IDA: PlayerStats::sub_4B7D80
// Ghidra: ---
char gta2::PlayerStats_sub_4B7D80(struct PlayerStats *self, char a2)
{
  unsigned __int16 index; // ax
  wchar_t *v4; // eax
  wchar_t *v5; // eax

  LOBYTE(index) = a2;
  if ( (a2 & 1) != 0 )
  {
    index = 0;
    while ( (self->Arr_int_64[index] & 1) != 0 )
    {
      if ( ++index >= 0x100u )
      {
        gta2::Player_AddMoney(self->sPlayer, 30000);
        if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
        {
          v4 = gta2::Text__Bsearch(gText, "stl_all");
          gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v4, 1);
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_GRAND_THEFT_AUTO);
        }
        LOBYTE(index) = gta2::PlayerStats_sub_4B75B0(self, 1);
        return index;
      }
    }
  }
  else if ( (a2 & 2) != 0 )
  {
    index = 0;
    while ( (self->Arr_int_64[index] & 2) != 0 )
    {
      if ( ++index >= 0x100u )
      {
        gta2::Player_AddMoney(self->sPlayer, 50000);
        if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
        {
          v5 = gta2::Text__Bsearch(gText, "dst_all");
          gta2::HudMessage_ShowBigOnScreenLabel(&gHud->HudMessage_, v5, 1);
          gta2::DMAudio_PlayVocal(&gDMAudio, VOCAL_WIPEOUT);
        }
        LOBYTE(index) = gta2::PlayerStats_sub_4B75B0(self, 2);
        return index;
      }
    }
  }
  return index;
}


// 0x004b7e90: PlayerStats::sub_4B7E90
// IDA: PlayerStats::sub_4B7E90
// Ghidra: FUN_004b7e90
void gta2::PlayerStats_sub_4B7E90(void *self,byte param_1,int param_2)
{
  byte *pbVar1;
  
  pbVar1 = (byte *)(param_2 + 0x8c + (int)self);
  *pbVar1 = *pbVar1 | param_1;
  gta2::PlayerStats_sub_4B7D80((SaveSlotAnimatedValue *)self,param_1);
  return;
}


// 0x004b7eb0: PlayerStats::sub_4B7EB0
// IDA: PlayerStats::sub_4B7EB0
// Ghidra: ---
bool gta2::PlayerStats_sub_4B7EB0(struct PlayerStats *self, Ped *pPed1, Ped *a3)
{
  struct PlayerStats *MultiPlayer; // eax
  struct Ped *pPed; // ebx
  struct Weapon *v6; // eax
  struct Weapon *XCoordinate; // eax
  unsigned __int8 v8; // al
  char *v9; // edi
  int v10; // eax
  __int16 v11; // si
  struct GameObject *GameObject1; // eax
  struct Car *CarPlayers; // eax
  CarModel CarType; // eax
  ALL_PED CurrentOccupation; // eax
  unsigned int Cycle; // eax
  int pCycle; // edi
  int v18; // esi
  struct Ped **pPed2; // ebx
  struct Ped *v20; // edi
  struct PlayerStats *v21; // ebp
  int v22; // edi
  int *PositionZ; // esi
  int *v24; // eax
  int *v25; // ebp
  int *v26; // eax
  char v27; // al
  bool result; // al
  int v29; // ecx
  int v30; // eax
  struct GameObject *v31; // ecx
  struct GameObject *v32; // eax
  char v33; // cl
  char v34; // al
  unsigned int v35; // edx
  int v36; // eax
  __int16 Remap; // [esp-10h] [ebp-3Ch]
  int field_22C; // [esp-Ch] [ebp-38h]
  CarModel pCarType; // [esp-8h] [ebp-34h]
  unsigned __int8 v40; // [esp-4h] [ebp-30h]
  struct Ped *CurrentPed; // [esp-4h] [ebp-30h]
  struct Ped *v42; // [esp-4h] [ebp-30h]
  struct Ped *v43; // [esp-4h] [ebp-30h]
  struct Ped *v44; // [esp-4h] [ebp-30h]
  char v45; // [esp+13h] [ebp-19h]
  char v46; // [esp+14h] [ebp-18h]
  char v47; // [esp+15h] [ebp-17h]
  char v48; // [esp+16h] [ebp-16h]
  bool v49; // [esp+17h] [ebp-15h]
  struct PlayerStats *v51; // [esp+1Ch] [ebp-10h]
  int X; // [esp+20h] [ebp-Ch] BYREF
  int Y; // [esp+24h] [ebp-8h] BYREF
  int v54; // [esp+28h] [ebp-4h] BYREF

  MultiPlayer = gta2::Player_GetMultiPlayer(self->sPlayer);
  pPed = a3;
  v51 = MultiPlayer;
  gta2::Ped_GetYCoordinate(a3, (int *)&a3);
  v40 = gta2::Weapon_sub_41C1E0(v6);
  XCoordinate = (struct Weapon *)gta2::Ped_GetXCoordinate(pPed, (int)&X);
  v8 = gta2::Weapon_sub_41C1E0(XCoordinate);
  v9 = gta2::MapRelatedStruct_sub_465130(gMapRelatedStruct, v8, v40);
  v10 = *(_DWORD *)&pPed1->field_11B;
  if ( v10 )
  {
    v11 = *(unsigned __int8 *)(v10 + 1);
  }
  else
  {
    GameObject1 = pPed1->GameObject1;
    if ( GameObject1 )
      v11 = BYTE1(GameObject1->NextGameObject1);
    else
      v11 = -1;
  }
  CarPlayers = gta2::Ped_GetCarPlayers(pPed);
  if ( CarPlayers )
    CarType = CarPlayers->CarType;
  else
    CarType = MODEL_NUM_CAR_MODELS;
  pCarType = CarType;
  field_22C = pPed1->field_22C;
  Remap = gta2::Ped_GetRemap(pPed1);
  CurrentOccupation = gta2::Ped_GetCurrentOccupation(pPed1);
  gta2::S165_sub_41DEE0(&self->S165_, 0, 87, CurrentOccupation, v11, Remap, field_22C, pCarType, (int)v9);
  Cycle = gta2::General_GetCycle(gGeneral);
  pCycle = Cycle;
  if ( Cycle - self->Cycle1 <= 0xF )
    ++self->excutin;
  else
    self->excutin = 1;
  ++self->gencide;
  self->Cycle1 = Cycle;
  v18 = 0;
  v49 = *(_DWORD *)&pPed1->GameObject2 != 0;
  v47 = 0;
  if ( gNetworkGame && gta2::Ped_IsSearchType(pPed1, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) && *(_DWORD *)&pPed1->isPlayer )
  {
    switch ( pPed1->field_22C )
    {
      case 1:
        v18 = 1000;
        break;
      case 2:
      case 5:
        v18 = 5000;
        break;
      case 3:
        v18 = 10000;
        break;
      case 4:
      case 9:
      case 0xA:
      case 0xB:
      case 0xC:
      case 0xD:
      case 0xE:
      case 0xF:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
        v18 = 2000;
        break;
      default:
        break;
    }
    LOBYTE(pPed2) = (_BYTE)pPed1;
  }
  else
  {
    v29 = *(_DWORD *)&pPed1->field_11B;
    if ( v29 )
    {
      v30 = *(_DWORD *)&pPed->field_11B;
      if ( !v30 || v30 != v29 )
        v47 = 1;
    }
    v31 = pPed1->GameObject1;
    if ( v31 )
    {
      v32 = *(GameObject **)&pPed->field_11B;
      if ( !v32 || v32 != v31 )
        v47 = 1;
    }
    switch ( gta2::Ped_GetCurrentOccupation(pPed1) )
    {
      case MUGGER:
        v33 = 1;
        v45 = 0;
        LOBYTE(a3) = 0;
        LOBYTE(pPed2) = 0;
        goto LABEL_55;
      case CARTHIEF:
        LOBYTE(pPed2) = 0;
        v34 = 1;
        v46 = 0;
        v45 = 0;
        LOBYTE(a3) = 0;
        v33 = 0;
        goto LABEL_57;
      case ELVIS:
      case ELVIS_LEADER:
        v35 = pCycle - self->field_80;
        LOBYTE(pPed2) = 0;
        v46 = 0;
        v45 = 0;
        LOBYTE(a3) = 0;
        v18 = 100;
        if ( v35 <= 0xF )
          ++self->elvis_d;
        else
          self->elvis_d = 1;
        self->field_80 = pCycle;
        goto LABEL_18;
      case UNKNOWN_OCUPATION_23:
      case POLICE:
      case UNK_REL_TO_POLICE_1:
      case UNK_REL_TO_POLICE_4:
      case FIREMAN:
        LOBYTE(pPed2) = 0;
        v46 = 1;
        v45 = 0;
        LOBYTE(a3) = 0;
        v33 = 0;
        break;
      case SWAT:
      case UNK_REL_TO_POLICE_2:
        LOBYTE(a3) = 1;
        v45 = 0;
        goto LABEL_53;
      case FBI:
        v45 = 1;
        LOBYTE(a3) = 0;
LABEL_53:
        LOBYTE(pPed2) = 0;
        goto LABEL_54;
      case ARMYARMY:
      case UNK_REL_TO_POLICE_3:
      case TANK_DRIVER:
      case ROAD_BLOCK_TANK_MAN:
        LOBYTE(pPed2) = 1;
        v45 = 0;
        LOBYTE(a3) = 0;
LABEL_54:
        v33 = 0;
LABEL_55:
        v46 = 0;
        break;
      default:
        LOBYTE(pPed2) = 0;
        v46 = 0;
        v45 = 0;
        LOBYTE(a3) = 0;
        v33 = 0;
        break;
    }
    v34 = 0;
LABEL_57:
    switch ( pPed1->field_22C )
    {
      case 1:
        if ( v47 )
          goto LABEL_81;
        if ( v46 )
        {
          v18 = 100;
        }
        else if ( (_BYTE)pPed2 )
        {
          v18 = 250;
        }
        else if ( (_BYTE)a3 )
        {
          v18 = 150;
        }
        else if ( v45 )
        {
          v18 = 200;
        }
        else if ( v33 )
        {
          v18 = 20;
        }
        else
        {
          v18 = v34 != 0 ? 20 : 10;
        }
        break;
      case 2:
        if ( v47 )
        {
          v18 = 200;
        }
        else if ( v46 )
        {
          v18 = 500;
        }
        else if ( (_BYTE)pPed2 )
        {
          v18 = 1250;
        }
        else if ( (_BYTE)a3 )
        {
          v18 = 750;
        }
        else if ( v45 )
        {
          v18 = 1000;
        }
        else if ( v33 )
        {
          v18 = 100;
        }
        else
        {
          v18 = v34 != 0 ? 100 : 50;
        }
        break;
      case 3:
        if ( v47 )
        {
          v18 = 200;
        }
        else if ( v46 )
        {
          v18 = 1000;
        }
        else if ( (_BYTE)pPed2 )
        {
          v18 = 2500;
        }
        else if ( (_BYTE)a3 )
        {
          v18 = 1500;
        }
        else if ( v45 )
        {
          v18 = 2000;
        }
        else if ( v33 )
        {
          v18 = 200;
        }
        else
        {
          v18 = v34 != 0 ? 200 : 100;
        }
        break;
      case 4:
LABEL_81:
        v18 = 20;
        break;
      case 5:
        goto LABEL_68;
      case 9:
      case 0xA:
      case 0xB:
      case 0xC:
      case 0xD:
      case 0xE:
      case 0xF:
      case 0x10:
      case 0x11:
      case 0x12:
      case 0x13:
      case 0x14:
        if ( v47 )
        {
LABEL_68:
          v18 = 50;
        }
        else if ( v46 )
        {
          v18 = 200;
        }
        else if ( (_BYTE)pPed2 )
        {
          v18 = 500;
        }
        else if ( (_BYTE)a3 )
        {
          v18 = 300;
        }
        else if ( v45 )
        {
          v18 = 400;
        }
        else if ( v33 )
        {
          v18 = 40;
        }
        else
        {
          v18 = v34 != 0 ? 40 : 20;
        }
        break;
      default:
        break;
    }
  }
LABEL_18:
  v20 = pPed1;
  v48 = 1;
  if ( gAllGxtFile
    && (gta2::Ped_GetCurrentOccupation(pPed1) == POLICE
     || gta2::Ped_GetCurrentOccupation(pPed1) == UNK_REL_TO_POLICE_1
     || gta2::Ped_GetCurrentOccupation(pPed1) == UNK_REL_TO_POLICE_4
     || v45
     || (_BYTE)a3
     || (_BYTE)pPed2) )
  {
    v48 = 0;
  }
  v21 = self;
  if ( v18 )
  {
    v22 = v18 * (unsigned __int8)self->field_75;
    if ( !gExploding_on && v49 )
    {
      if ( !v48 )
      {
LABEL_34:
        v27 = v21->field_75;
        v20 = pPed1;
        if ( (unsigned __int8)v27 < 5u )
          v21->field_75 = v27 + 1;
        goto LABEL_36;
      }
      if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
      {
        PositionZ = (int *)gta2::Ped_GetPositionZ(pPed1, (int)&X);
        gta2::Ped_GetYCoordinate(pPed1, &Y);
        v25 = v24;
        v26 = (int *)gta2::Ped_GetXCoordinate(pPed1, (int)&v54);
        gta2::S123_sub_4B91F0(gS123, *v26, *v25, *PositionZ, (_DWORD)v51 * v22);
      }
    }
    v21 = self;
    if ( v48 )
      gta2::Player_AddMoney(self->sPlayer, v22);
    goto LABEL_34;
  }
LABEL_36:
  result = gta2::S127_sub_44A370(gS127, v20, v21->sPlayer);
  if ( result )
  {
    if ( v47 )
    {
      CurrentPed = gta2::Player_GetCurrentPed(v21->sPlayer);
      return gta2::S127_HandlePedInteraction(gS127, 9u, CurrentPed);
    }
    else if ( v46 || (_BYTE)pPed2 || (_BYTE)a3 || v45 )
    {
      v44 = gta2::Player_GetCurrentPed(v21->sPlayer);
      return gta2::S127_HandlePedInteraction(gS127, 8u, v44);
    }
    else
    {
      v36 = v20->field_22C;
      if ( v36 == 1 || v36 == 3 )
      {
        v43 = gta2::Player_GetCurrentPed(v21->sPlayer);
        return gta2::S127_HandlePedInteraction(gS127, 6u, v43);
      }
      else
      {
        v42 = gta2::Player_GetCurrentPed(v21->sPlayer);
        return gta2::S127_HandlePedInteraction(gS127, 7u, v42);
      }
    }
  }
  return result;
}


// 0x004b85b0: PlayerStats::sub_4B85B0
// IDA: PlayerStats::sub_4B85B0
// Ghidra: ---
char gta2::PlayerStats_sub_4B85B0(struct PlayerStats *self, Car *pCar, Ped *pPed)
{
  struct PlayerStats *MultiPlayer; // eax
  struct Ped *pPed1; // esi
  struct Weapon *v6; // eax
  struct Weapon *XCoordinate; // eax
  unsigned __int8 v8; // al
  char *v9; // ebx
  struct Car *CarPlayers; // eax
  char GangByCarModel; // al
  __int16 v13; // bp
  __int16 remap; // ax
  int Cycle; // ebx
  char v16; // al
  int v17; // ebp
  int *v18; // eax
  int *v19; // ebx
  int *v20; // eax
  int *v21; // eax
  char v22; // al
  struct Ped *PedStatus; // eax
  DamageType DamageType; // [esp-Ch] [ebp-30h]
  struct Ped *v26; // [esp-8h] [ebp-2Ch]
  unsigned __int8 v27; // [esp-4h] [ebp-28h]
  struct PlayerStats *v28; // [esp+10h] [ebp-14h]
  int X; // [esp+14h] [ebp-10h] BYREF
  int a2; // [esp+18h] [ebp-Ch] BYREF
  int v31; // [esp+1Ch] [ebp-8h] BYREF
  int v32; // [esp+20h] [ebp-4h] BYREF
  int *pCara; // [esp+28h] [ebp+4h]

  MultiPlayer = gta2::Player_GetMultiPlayer(self->sPlayer);
  pPed1 = pPed;
  v28 = MultiPlayer;
  gta2::Ped_GetYCoordinate(pPed, (int *)&pPed);
  v27 = gta2::Weapon_sub_41C1E0(v6);
  XCoordinate = (struct Weapon *)gta2::Ped_GetXCoordinate(pPed1, (int)&X);
  v8 = gta2::Weapon_sub_41C1E0(XCoordinate);
  v9 = gta2::MapRelatedStruct_sub_465130(gMapRelatedStruct, v8, v27);
  CarPlayers = gta2::Ped_GetCarPlayers(pPed1);
  if ( CarPlayers )
    pPed = (struct Ped *)CarPlayers->CarType;
  else
    pPed = (struct Ped *)87;
  GangByCarModel = gta2::Gangs_FindGangByCarModel(gGangs, pCar->CarType);
  v26 = pPed;
  DamageType = pCar->DamageType;
  v13 = GangByCarModel;
  remap = gta2::SpriteS1_get_remap(pCar->CarSprite);
  gta2::S165_sub_41DEE0(&self->S165_, 1, pCar->CarType, NO_OCCUPATION, v13, remap, DamageType, (CarModel)v26, (int)v9);
  LOBYTE(pPed) = 1;
  if ( gAllGxtFile )
    LOBYTE(pPed) = !gta2::Car_IsCopCar(pCar);
  Cycle = gta2::General_GetCycle(gGeneral);
  X = Cycle;
  if ( gta2::Car_isFileTruck(pCar)
    || gta2::Car_isCopCar(pCar)
    || gta2::Car_isMedicCar(pCar)
    || gta2::Car_isSWATVAN(pCar)
    || gta2::Car_isEDSELFBI(pCar) )
  {
    if ( (unsigned int)(Cycle - self->Cycle) > 0x96 )
      self->em_dest = 0;
    if ( gta2::Car_isMedicCar(pCar) )
    {
      v16 = self->em_dest | 1;
    }
    else if ( gta2::Car_isCopCar(pCar) || gta2::Car_isSWATVAN(pCar) || gta2::Car_isEDSELFBI(pCar) )
    {
      v16 = self->em_dest | 2;
    }
    else
    {
      if ( !gta2::Car_isFileTruck(pCar) )
      {
LABEL_22:
        self->Cycle = Cycle;
        goto LABEL_23;
      }
      v16 = self->em_dest | 4;
    }
    self->em_dest = v16;
    goto LABEL_22;
  }
LABEL_23:
  if ( pCar->CarType == COPCAR && (_BYTE)pPed )
    ++self->copkill;
  v17 = gta2::PlayerStats_sub_4B7500(self, pCar->CarType, 2) * (unsigned __int8)self->field_74;
  if ( !gExploding_on )
  {
    if ( !(_BYTE)pPed )
      goto LABEL_32;
    if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
    {
      gta2::Car_GetZ(pCar, &a2);
      v19 = v18;
      gta2::Car_GetY(pCar, &v31);
      pCara = v20;
      gta2::Car_GetX(pCar, &v32);
      gta2::S123_sub_4B91F0(gS123, *v21, *pCara, *v19, (_DWORD)v28 * v17);
      Cycle = X;
    }
  }
  if ( (_BYTE)pPed )
    gta2::Player_AddMoney(self->sPlayer, v17);
LABEL_32:
  v22 = self->field_74;
  self->field_70 = Cycle;
  if ( (unsigned __int8)v22 < 5u )
    self->field_74 = v22 + 1;
  if ( gta2::S127_sub_44A2C0(gS127, pCar, self->sPlayer) )
  {
    PedStatus = gta2::Player_GetCurrentPed(self->sPlayer);
    gta2::S127_HandlePedInteraction(gS127, 3u, PedStatus);
  }
  gta2::sub_44A000(&self->sPlayer->field_644, (_DWORD)v28 * v17);
  return gta2::PlayerStats_sub_4B7E90(self, 2, pCar->CarType);
}


// 0x004b8870: PlayerStats::sub_4B8870
// IDA: PlayerStats::sub_4B8870
// Ghidra: ---
char gta2::PlayerStats_sub_4B8870(struct PlayerStats *self, Car *pCar, int *a3)
{
  struct PlayerStats *MultiPlayer; // eax
  struct Car *pCar_1; // ebp
  char result; // al
  int v7; // esi
  int *v8; // eax
  int *v9; // ebx
  int *v10; // eax
  int *v11; // eax
  struct Ped *CurrentPed; // eax
  bool v13; // [esp+Bh] [ebp-Dh]
  struct PlayerStats *v14; // [esp+Ch] [ebp-Ch]
  int v15; // [esp+10h] [ebp-8h] BYREF
  int v16; // [esp+14h] [ebp-4h] BYREF

  MultiPlayer = gta2::Player_GetMultiPlayer(self->sPlayer);
  pCar_1 = pCar;
  v14 = MultiPlayer;
  v13 = 1;
  if ( gAllGxtFile )
    v13 = !gta2::Car_IsCopCar(pCar);
  result = (char)a3;
  if ( (_WORD)a3 )
  {
    if ( (unsigned int)(__int16)a3 >= 0x12C )
      v7 = (unsigned int)(__int16)a3 < 0x190 ? 10 : 100;
    else
      v7 = 1;
    if ( !gExploding_on )
    {
      if ( !v13 )
      {
LABEL_13:
        gta2::sub_44A000(&self->sPlayer->field_644, (_DWORD)v14 * v7);
        result = gta2::S127_sub_44A2C0(gS127, pCar_1, self->sPlayer);
        if ( result )
        {
          CurrentPed = gta2::Player_GetCurrentPed(self->sPlayer);
          return gta2::S127_HandlePedInteraction(gS127, 1u, CurrentPed);
        }
        return result;
      }
      if ( gta2::Player_GetCurrentPlayer(self->sPlayer) )
      {
        gta2::Car_GetZ(pCar_1, (int *)&pCar);
        v9 = v8;
        gta2::Car_GetY(pCar_1, &v15);
        a3 = v10;
        gta2::Car_GetX(pCar_1, &v16);
        gta2::S123_sub_4B91F0(gS123, *v11, *a3, *v9, (_DWORD)v14 * v7);
      }
    }
    if ( v13 )
      gta2::Player_AddMoney(self->sPlayer, v7);
    goto LABEL_13;
  }
  return result;
}


// 0x004b89b0: PlayerStats::sub_4B89B0
// IDA: PlayerStats::sub_4B89B0
// Ghidra: ---
char gta2::PlayerStats_sub_4B89B0(struct PlayerStats *self, Car *pCar, __int16 pPed)
{
  char result; // al
  struct PlayerStats *MultiPlayer; // ebx
  int pMoney; // esi
  struct Ped *CurrentPed; // eax

  result = gta2::Car_GetFullDamage(pCar);
  if ( !result )
  {
    MultiPlayer = gta2::Player_GetMultiPlayer(self->sPlayer);
    result = pPed;
    if ( pPed )
    {
      if ( (unsigned int)pPed >= 0x12C )
        pMoney = (unsigned int)pPed < 400 ? 10 : 100;
      else
        pMoney = 1;
      if ( !gAllGxtFile || !gta2::Car_IsCopCar(pCar) )
        gta2::Player_AddMoney(self->sPlayer, pMoney);
      gta2::sub_44A000(&self->sPlayer->field_644, (_DWORD)MultiPlayer * pMoney);
      CurrentPed = gta2::Player_GetCurrentPed(self->sPlayer);
      return gta2::S127_HandlePedInteraction(gS127, 1u, CurrentPed);
    }
  }
  return result;
}


// 0x004b8a60: PlayerStats::sub_4B8A60
// IDA: PlayerStats::sub_4B8A60
// Ghidra: ---
int gta2::PlayerStats_sub_4B8A60(struct PlayerStats *self)
{
  return gta2::Player_AddMoney(self->sPlayer, 20);
}


// 0x004b8a70: PlayerStats::sub_4B8A70
// IDA: PlayerStats::sub_4B8A70
// Ghidra: ---
char gta2::PlayerStats_sub_4B8A70(struct PlayerStats *self, Car *a2)
{
  struct Player *sPlayer; // edi
  struct Weapon *v4; // eax
  struct Weapon *XCoordinate; // eax
  unsigned __int8 v6; // al
  char *v8; // ebx
  __int16 GangByCarModel; // bp
  __int16 remap; // ax
  int v11; // ebx
  int *v12; // eax
  int *v13; // ebp
  int *v14; // eax
  int *v15; // eax
  struct Ped *CurrentPed; // eax
  unsigned __int8 v18; // [esp-4h] [ebp-24h]
  struct PlayerStats *MultiPlayer; // [esp+10h] [ebp-10h]
  int Y; // [esp+14h] [ebp-Ch] BYREF
  int X; // [esp+18h] [ebp-8h] BYREF
  int v22; // [esp+1Ch] [ebp-4h] BYREF
  int *a2a; // [esp+24h] [ebp+4h]

  sPlayer = self->sPlayer;
  MultiPlayer = gta2::Player_GetMultiPlayer(sPlayer);
  gta2::Ped_GetYCoordinate(sPlayer->MainPed, &Y);
  v18 = gta2::Weapon_sub_41C1E0(v4);
  XCoordinate = (struct Weapon *)gta2::Ped_GetXCoordinate(sPlayer->MainPed, (int)&X);
  v6 = gta2::Weapon_sub_41C1E0(XCoordinate);
  v8 = gta2::MapRelatedStruct_sub_465130(gMapRelatedStruct, v6, v18);
  GangByCarModel = gta2::Gangs_FindGangByCarModel(gGangs, a2->CarType);
  remap = gta2::SpriteS1_get_remap(a2->CarSprite);
  gta2::S165_sub_41DEE0(&self->S165_, 2, a2->CarType, NO_OCCUPATION, GangByCarModel, remap, 23, MODEL_NUM_CAR_MODELS, (int)v8);
  ++self->carjaka;
  v11 = gta2::PlayerStats_sub_4B7500(self, a2->CarType, 0);
  if ( !gExploding_on && gta2::Player_GetCurrentPlayer(self->sPlayer) )
  {
    gta2::Car_GetZ(a2, &X);
    v13 = v12;
    gta2::Car_GetY(a2, &Y);
    a2a = v14;
    gta2::Car_GetX(a2, &v22);
    gta2::S123_sub_4B91F0(gS123, *v15, *a2a, *v13, (_DWORD)MultiPlayer * v11);
  }
  gta2::Player_AddMoney(self->sPlayer, v11);
  CurrentPed = gta2::Player_GetCurrentPed(self->sPlayer);
  gta2::S127_HandlePedInteraction(gS127, 5u, CurrentPed);
  return gta2::PlayerStats_sub_4B7E90(self, 1, a2->CarType);
}


// 0x004b8bd0: PlayerStats::sub_4B8BD0
// IDA: PlayerStats::sub_4B8BD0
// Ghidra: ---
bool gta2::PlayerStats_sub_4B8BD0(struct PlayerStats *self, Car *pCar)
{
  struct PlayerStats *v2; // esi
  struct Player *sPlayer; // ebp
  struct Car *pCar1; // esi
  int *v5; // eax
  int *v6; // edi
  int *v7; // eax
  int *v8; // ebx
  int *v9; // eax
  int *v10; // esi
  struct PlayerStats *MultiPlayer; // eax
  struct Ped *CurrentPed; // eax
  int v15; // [esp+8h] [ebp-8h] BYREF
  int v16; // [esp+Ch] [ebp-4h] BYREF

  v2 = self;
  if ( !gExploding_on )
  {
    sPlayer = self->sPlayer;
    if ( gta2::Player_GetCurrentPlayer(sPlayer) )
    {
      pCar1 = pCar;
      gta2::Car_GetZ(pCar, (int *)&pCar);
      v6 = v5;
      gta2::Car_GetY(pCar1, &v15);
      v8 = v7;
      gta2::Car_GetX(pCar1, &v16);
      v10 = v9;
      MultiPlayer = gta2::Player_GetMultiPlayer(sPlayer);
      gta2::S123_sub_4B91F0(gS123, *v10, *v8, *v6, 10 * (_DWORD)MultiPlayer);
      v2 = self;
    }
  }
  gta2::Player_AddMoney(v2->sPlayer, 10);
  CurrentPed = gta2::Player_GetCurrentPed(v2->sPlayer);
  return gta2::S127_HandlePedInteraction(gS127, 4u, CurrentPed);
}


// 0x004b8c80: PlayerStats::sub_4B8C80
// IDA: PlayerStats::sub_4B8C80
// Ghidra: ---
char gta2::PlayerStats_sub_4B8C80(struct PlayerStats *self, Car *pCar)
{
  struct Player *sPlayer; // ebp
  struct PlayerStats *MultiPlayer; // esi
  int *v6; // eax
  int *v7; // ebp
  int *v8; // eax
  int *v9; // eax
  char result; // al
  struct Ped *CurrentPed; // eax
  int a2; // [esp+10h] [ebp-Ch] BYREF
  int v13; // [esp+14h] [ebp-8h] BYREF
  int v14; // [esp+18h] [ebp-4h] BYREF
  int *pCara; // [esp+20h] [ebp+4h]

  sPlayer = self->sPlayer;
  MultiPlayer = gta2::Player_GetMultiPlayer(sPlayer);
  if ( !gExploding_on && gta2::Player_GetCurrentPlayer(sPlayer) )
  {
    gta2::Car_GetZ(pCar, &a2);
    v7 = v6;
    gta2::Car_GetY(pCar, &v13);
    pCara = v8;
    gta2::Car_GetX(pCar, &v14);
    gta2::S123_sub_4B91F0(gS123, *v9, *pCara, *v7, 100 * (_DWORD)MultiPlayer);
  }
  gta2::Player_AddMoney(self->sPlayer, 100);
  gta2::sub_44A000(&self->sPlayer->field_644, 100 * (_DWORD)MultiPlayer);
  result = gta2::S127_sub_44A2C0(gS127, pCar, self->sPlayer);
  if ( result )
  {
    CurrentPed = gta2::Player_GetCurrentPed(self->sPlayer);
    return gta2::S127_HandlePedInteraction(gS127, 3u, CurrentPed);
  }
  return result;
}



