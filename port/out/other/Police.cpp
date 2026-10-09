#include "gta2_shim.h"

// Module: other, Class: Police
// Functions: 20
// Source: unified (IDA+Ghidra)

// 0x004a9430: Police::sub_4A9430
// IDA: Police::sub_4A9430
// Ghidra: ---
int gta2::Police_sub_4A9430(struct Police *self)
{
  int v2; // ebp
  int *v3; // edx
  int (*Buffer)[24]; // edi
  int result; // eax
  int pMaxFrameRateChek; // ecx

  v2 = 4;
  self->Field = 1;
  v3 = &self->S113_arr[0].field_C;
  do
  {
    *(v3 - 3) = 0;
    *(_WORD *)v3 = 0;
    *((_BYTE *)v3 + 16) = 0;
    *((_BYTE *)v3 + 100) = 0;
    *((_BYTE *)v3 + 101) = 0;
    *((_BYTE *)v3 + 102) = 0;
    *((_BYTE *)v3 + 103) = 0;
    *((_BYTE *)v3 + 104) = 0;
    *((_WORD *)v3 + 53) = 0;
    *(v3 - 2) = 0;
    *(v3 - 1) = 0;
    v3[1] = dword_66B89C;
    v3[2] = dword_66B89C;
    v3[3] = dword_66B89C;
    *((_BYTE *)v3 + 16) = 0;
    *((_BYTE *)v3 + 2) = 0;
    *((_BYTE *)v3 + 105) = 0;
    *((_BYTE *)v3 + 108) = 0;
    *((_WORD *)v3 + 55) = 0;
    Buffer = (int (*)[24])(v3 + 5);
    result = 0;
    v3 += 31;
    --v2;
    memset(Buffer, 0, 0x18u);
  }
  while ( v2 );
  self->WantedLevel = 0;
  self->Count = 0;
  self->field_659 = 1;
  self->field_65C = 3;
  pMaxFrameRateChek = gNetworkGame;
  self->field_7AC = 100;
  self->NumPolicePedsInRangeScreen = 0;
  self->Ped_ = 0;
  self->field_7B4 = 0;
  self->MaxFrameRateChek = pMaxFrameRateChek != 0 ? 1 : 6;
  unk_66B7A4 = 0;
  return result;
}


// 0x004a9500: Police::sub_4A9500
// IDA: Police::sub_4A9500
// Ghidra: ---
char gta2::Police_sub_4A9500(struct Police *self, Ped *pPed)
{
  unsigned __int8 v2; // dl
  struct S112 *v3; // esi
  struct S110 *S110; // ecx
  char v6; // al
  struct S110 *v7; // ecx
  struct S169 *NPC; // edx
  struct S169 *S169; // ecx
  unsigned __int8 index; // [esp+4h] [ebp-4h]

  v2 = 0;
  index = 0;
  while ( 1 )
  {
    v3 = &self->S112_[index];
    if ( self->S112_[index].field_1C )
      break;
    index = ++v2;
    if ( v2 >= 0x14u )
      return 0;
  }
  S110 = self->S112_[index].S110;
  if ( S110->Ped_ == pPed )
  {
    v6 = gta2::S110_sub_4C5510(S110);
    v7 = v3->S110_;
    NPC = v7->NPC;
    if ( NPC )
      v7->Ped_ = NPC->Ped_;
    if ( v6 )
    {
      return 1;
    }
    else
    {
      v3->S110_->Ped_ = 0;
      return 0;
    }
  }
  else
  {
    S169 = pPed->field_103;
    if ( S169 )
      gta2::S169_sub_404D40(S169, pPed);
    return 0;
  }
}


// 0x004a9590: Police::sub_4A9590
// IDA: Police::sub_4A9590
// Ghidra: ---
bool gta2::Police_sub_4A9590(struct Police *self, Ped *a2)
{
  unsigned __int8 v2; // bl
  char *v4; // eax
  unsigned __int8 v5; // [esp+Ch] [ebp-4h]

  v2 = 0;
  v5 = 0;
  while ( self->S113_arr[v5].Ped != a2 )
  {
    v5 = ++v2;
    if ( v2 >= 4u )
      return 0;
  }
  v4 = &self->Field + 124 * v5;
  return v4[1241] && (*((_DWORD *)v4 + 283) == 3 || *((_WORD *)v4 + 568));
}


// 0x004a9610: Police::sub_4A9610
// IDA: Police::sub_4A9610
// Ghidra: ---
bool gta2::Police_sub_4A9610(struct Police *self, Ped *a2)
{
  unsigned __int8 v2; // bl
  unsigned __int8 v4; // [esp+Ch] [ebp-4h]

  v2 = 0;
  v4 = 0;
  while ( self->S113_arr[v4].Ped != a2 )
  {
    v4 = ++v2;
    if ( v2 >= 4u )
      return 0;
  }
  return self->S113_arr[v4].field_78 != 0;
}


// 0x004a9670: Police::sub_4A9670
// IDA: Police::sub_4A9670
// Ghidra: ---
int gta2::Police_sub_4A9670(struct Police *self, Ped *a2, Ped *a3)
{
  unsigned __int8 v3; // bl
  int result; // eax
  unsigned __int8 v5; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v5 = 0;
  while ( 1 )
  {
    result = v5;
    if ( self->S113_arr[v5].Ped == a2 )
      break;
    v5 = ++v3;
    if ( v3 >= 4u )
      return result;
  }
  result = 31 * v5;
  self->S113_arr[v5].Ped = a2;
  return result;
}


// 0x004a9a90: Police::sub_4A9A90
// IDA: Police::sub_4A9A90
// Ghidra: ---
char gta2::Police_sub_4A9A90(struct Police *self)
{
  if ( self->WantedLevel < 3 || LOBYTE(self->PoliceRoadblock) || self->field_7AC )
    return 0;
  self->field_7AC = 40;
  return 1;
}


// 0x004a9ae0: Police::sub_4A9AE0
// IDA: Police::sub_4A9AE0
// Ghidra: ---
S112 * gta2::Police_sub_4A9AE0(struct Police *self)
{
  unsigned __int8 v1; // bl
  struct S112 *v3; // ecx
  unsigned __int8 index; // [esp+8h] [ebp-4h]

  v1 = 0;
  index = 0;
  while ( self->S112_[index].field_1C )
  {
    index = ++v1;
    if ( v1 >= 20u )
      return 0;
  }
  gta2::S112_Defaut(&self->S112_[index]);
  return v3;
}


// 0x004a9b40: Police::sub_4A9B40
// IDA: Police::sub_4A9B40
// Ghidra: FUN_004a9b40
Ped * gta2::Police_sub_4A9B40(undefined4 param_1,undefined4 param_2,undefined4 param_3, short param_4)
{
  struct Ped *self;
  
  if (0x1d < gCharacter->field4_0x5) {
    return NULL;
  }
  if (_DAT_0066b798 == 1) {
    self = gta2::Character_SpawnPedAtPosition(gCharacter,param_1,param_2,param_3,0,param_4);
    gta2::Ped_SetSearchType(self,4);
    gta2::Ped_SetCurrentOccupation(self,0x25);
    gta2::Ped_PedSetObjective(self,0x18,0);
    gta2::Ped_SetRemap(self,'\0');
    self->GraphicType = 2;
    self->SelectedWeapon = NULL;
    gta2::Ped_GiveWeapon(self,0);
  }
  else {
    if (_DAT_0066b798 != 3) {
      return NULL;
    }
    self = gta2::Character_SpawnPedAtPosition(gCharacter,param_1,param_2,param_3,0,param_4);
    gta2::Ped_SetSearchType(self,4);
    gta2::Ped_SetCurrentOccupation(self,0x25);
    gta2::Ped_PedSetObjective(self,0x18,0);
    gta2::Ped_SetRemap(self,'\b');
    self->GraphicType = 1;
    gta2::Ped_SetNPCWeapon(self,9);
  }
  gta2::Ped_SetHealth(self,200);
  self->field129_0x288 = 2;
  self->field130_0x28c = 1;
  return self;
}


// 0x004a9c50: Police::sub_4A9C50
// IDA: Police::sub_4A9C50
// Ghidra: Police::FUN_004a9c50
void gta2::Police_sub_4A9C50(struct Police *self,int param_1)
{
  GlassInfo *pGVar1;
  SpawnPoint *pSVar2;
  int iVar3;
  struct Ped *this_00;
  bool bVar4;
  byte bVar5;
  bool bVar6;
  uint local_4;
  
  bVar5 = 0;
  local_4 = 0;
  do {
    if (self->Array_DecalInfo[local_4].field15_0x1c != 0) {
      pGVar1 = self->Array_DecalInfo[local_4].s110;
      if ((pGVar1 != NULL) && (pGVar1->car == (Car *)param_1)) {
        pSVar2 = (self->Array_DecalInfo[local_4].s110)->SpawnPoint;
        if ((pSVar2 == NULL) ||
           (bVar4 = gta2::S169_sub_404840(pSVar2), bVar4)) {
          iVar3 = *(int *)(self->Array_DecalInfo[local_4].field11_0x14 + 4);
          if (iVar3 == 5) {
            iVar3 = self->Array_DecalInfo[local_4].field16_0x20;
            bVar4 = iVar3 == 1;
            bVar6 = iVar3 == 2;
          }
          else {
            if (iVar3 != 6) {
              return;
            }
            iVar3 = self->Array_DecalInfo[local_4].field16_0x20;
            bVar4 = iVar3 == 2 || iVar3 == 1;
            bVar6 = iVar3 == 3;
          }
          if ((!bVar6) && (!bVar4)) {
            return;
          }
        }
        bVar5 = 0;
        pSVar2 = (self->Array_DecalInfo[local_4].s110)->SpawnPoint;
        if (pSVar2 != NULL) {
          this_00 = pSVar2->Ped_Array[0];
          while (this_00 != NULL) {
            if (this_00->GameObject_ != NULL) {
              gta2::Ped_sub_43E650(this_00);
            }
            bVar5 = bVar5 + 1;
            this_00 = (self->Array_DecalInfo[local_4].s110)->SpawnPoint->
                      Ped_Array[bVar5];
          }
        }
        FUN_004a97c0(self->Array_DecalInfo + local_4);
        gta2::Car_isMask4((self->Array_DecalInfo[local_4].s110)->car);
        (self->Array_DecalInfo[local_4].s110)->field19_0x28 = 5;
        (self->Array_DecalInfo[local_4].s110)->field20_0x2c = 1;
        self->Array_DecalInfo[local_4].select = 6;
        return;
      }
    }
    bVar5 = bVar5 + 1;
    local_4 = (uint)bVar5;
    if (0x13 < bVar5) {
      return;
    }
  } while( true );
}


// 0x004a9d60: Police::sub_4A9D60
// IDA: Police::sub_4A9D60
// Ghidra: ---
char gta2::Police_sub_4A9D60(struct Police *self, Ped *a2)
{
  struct Ped *Ped; // eax
  unsigned __int8 v5; // cl
  unsigned __int8 v6; // dl
  char *v7; // esi
  _DWORD *v8; // eax
  unsigned __int8 v9; // cl
  char v11[4]; // [esp+8h] [ebp-4h] BYREF
  unsigned __int8 v12; // [esp+10h] [ebp+4h]
  unsigned __int8 v13; // [esp+10h] [ebp+4h]
  unsigned __int8 v14; // [esp+10h] [ebp+4h]

  unk_66B7A4 = 0;
  LOBYTE(Ped) = gta2::Ped_IsPlayerControlled(a2);
  if ( (_BYTE)Ped )
  {
    v5 = 0;
    v12 = 0;
    while ( self->S113_arr[v12].Ped != a2 )
    {
      v12 = ++v5;
      if ( v5 >= 4u )
      {
        v6 = 0;
        v13 = 0;
        while ( self->S113_arr[v13].Ped )
        {
          v13 = ++v6;
          if ( v6 >= 4u )
            goto LABEL_10;
        }
        v7 = &self->Field + 124 * v13;
        *((_DWORD *)v7 + 281) = a2;
        *((_DWORD *)v7 + 283) = 0;
        *((_DWORD *)v7 + 285) = *(_DWORD *)gta2::Ped_GetXCoordinate(a2, (int)v11);
        gta2::Ped_GetYCoordinate(a2, (int *)v11);
        *((_DWORD *)v7 + 286) = *v8;
        *((_DWORD *)v7 + 287) = *(_DWORD *)gta2::Ped_GetPositionZ(a2, (int)v11);
        break;
      }
    }
LABEL_10:
    v9 = 0;
    v14 = 0;
    while ( 1 )
    {
      Ped = self->S113_arr[v14].Ped;
      if ( Ped )
        break;
      v14 = ++v9;
      if ( v9 >= 4u )
        return (char)Ped;
    }
    unk_66B7A4 = 1;
  }
  return (char)Ped;
}


// 0x004a9e80: Police::sub_4A9E80
// IDA: Police::sub_4A9E80
// Ghidra: ---
void gta2::Police_sub_4A9E80(struct Police *self)
{
  struct Ped *Ped; // edi
  __int16 v3; // ax

  Ped = self->S113_arr[0].Ped;
  if ( Ped )
  {
    if ( !gta2::Ped_Get_433B40(self->S113_arr[0].Ped) || gta2::Ped_GetDeadPed(Ped) )
    {
      self->S113_arr[0].field_8 = 4;
    }
    else
    {
      v3 = self->S113_arr[0].field_C;
      if ( v3 )
        LOWORD(self->S113_arr[0].field_C) = v3 - 1;
      if ( self->S113_arr[0].field_8 == 3 && !LOWORD(self->S113_arr[0].field_C) )
        self->S113_arr[0].field_8 = 5;
    }
  }
}


// 0x004a9ef0: Police::sub_4A9EF0
// IDA: Police::sub_4A9EF0
// Ghidra: ---
char gta2::Police_sub_4A9EF0(struct Police *self, int a2)
{
  int v2; // ebp
  struct S112 *pS112; // esi
  struct S110 *pS110; // edi
  __int16 v7; // ax
  struct Car *Car; // edx
  unsigned __int8 v9[4]; // [esp+Ch] [ebp-Ch] BYREF
  unsigned __int8 v10[4]; // [esp+10h] [ebp-8h] BYREF
  int v11; // [esp+14h] [ebp-4h] BYREF

  v2 = a2;
  LOBYTE(a2) = gta2::Weapon_sub_41C1E0((Weapon *)(a2 + 16));
  v9[0] = gta2::Weapon_sub_41C1E0((Weapon *)(v2 + 20));
  v10[0] = gta2::Weapon_sub_41C1E0((Weapon *)(v2 + 24));
  if ( !gta2::S95_sub_49D7A0(gS95, 1, &a2, v9, v10, 0) )
    return 0;
  pS112 = gta2::Police_sub_4A9AE0(self);
  pS112->field_1C = 1;
  pS112->X = a2;
  pS112->Y = v9[0];
  pS112->Z = v10[0];
  pS110 = gta2::S109_sub_4C5430(gS109);
  pS112->S110_ = pS110;
  if ( !pS110 )
  {
    gta2::S112_Defaut(pS112);
    return 0;
  }
  v7 = unk_66B7A8;
  pS112->S113_ = (S113 *)v2;
  pS112->field = v7;
  unk_66B7A8 = v7 + 1;
  pS112->State = *(_DWORD *)&stru_66B76C.field_24;
  pS112->field_20 = unk_66B798;
  pS110->field_1E = 1;
  Car = stru_66B76C.Car;
  pS110->field_24 = 1;
  pS110->field_20 = (int)Car;
  pS110->field_28 = 3;
  pS110->field_18 = (__int16)stru_66B76C.Ped;
  gta2::S202_sub_40CE30((S202 *)&v11, a2);
  pS110->field_C = v11;
  gta2::S202_sub_40CE30((S202 *)&v11, v9[0]);
  pS110->field_10 = v11;
  gta2::S202_sub_40CE30((S202 *)&v11, v10[0]);
  pS110->field_14 = v11;
  gta2::S112_sub_4A9720(pS112);
  return 1;
}


// 0x004aa030: Police::sub_4AA030
// IDA: Police::sub_4AA030
// Ghidra: ---
char gta2::Police_sub_4AA030(struct Police *self)
{
  Police *v1; // ebx
  struct Ped *Ped; // eax
  S113 *S113_arr; // esi
  struct Ped *v4; // edi
  char v5; // al
  bool v6; // cf
  char v7; // cl
  void *v8; // eax
  struct Ped *v9; // ebp
  int v10; // edi
  __int16 Max900; // ax
  char Count; // cl
  unsigned __int8 v13; // al
  int v14; // edx
  int v15; // edi
  int v16; // edi
  char v17; // al
  unsigned __int8 v18; // dl
  struct S112 *v19; // eax
  struct S112 **v20; // eax
  char v21; // cl
  struct S112 **S112; // ebx
  struct S112 *v23; // ebp
  struct Ped *v24; // edi
  struct Car *v25; // eax
  int v26; // edi
  struct S112 *v27; // ecx
  int v28; // eax
  char v29; // al
  unsigned __int8 v31; // [esp+Ch] [ebp-1Ch]
  unsigned __int8 v32; // [esp+Ch] [ebp-1Ch]
  unsigned __int8 v33; // [esp+10h] [ebp-18h]
  int v34; // [esp+14h] [ebp-14h]
  char v36[4]; // [esp+1Ch] [ebp-Ch] BYREF
  char v37[4]; // [esp+20h] [ebp-8h] BYREF
  char v38[4]; // [esp+24h] [ebp-4h] BYREF

  v1 = self;
  Ped = self->S113_arr[0].Ped;
  S113_arr = self->S113_arr;
  v33 = 0;
  if ( Ped )
  {
    do
    {
      LOBYTE(Ped) = v33;
      if ( v33 >= 4u )
        break;
      v4 = S113_arr->Ped_;
      S113_arr->field_78 = 0;
      if ( gta2::Ped_sub_420B70(v4) == SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY && (v4->PositionX1 & 0x20) != 0 )
        v4->isPlayer->field_640 = 1;
      switch ( gta2::Ped_GetCopStars(S113_arr->Ped_) )
      {
        case 0u:
          if ( S113_arr->field_8 )
          {
            S113_arr->field_8 = 4;
            v1->field_659 = 2;
            S113_arr->field_4 = 0;
            S113_arr->field_71 = 0;
          }
          break;
        case 1u:
          v5 = S113_arr->field_70;
          S113_arr->field_71 = 1;
          S113_arr->field_4 = (void *)1;
          v1->field_659 = v5 == 0;
          break;
        case 2u:
          if ( S113_arr->field_71 == 1 )
            BYTE2(S113_arr->field_C) = 1;
          v6 = S113_arr->field_70 > 1u;
          S113_arr->field_71 = 2;
          S113_arr->field_4 = (void *)2;
          v1->field_659 = v6 ? 0 : 2;
          break;
        case 3u:
          v6 = S113_arr->field_70 > 1u;
          S113_arr->field_71 = 2;
          S113_arr->field_4 = (void *)3;
          v1->field_659 = v6 ? 0 : 2;
          break;
        case 4u:
          v7 = S113_arr->field_70;
          S113_arr->field_71 = 2;
          S113_arr->field_4 = (void *)4;
          goto LABEL_18;
        case 5u:
          S113_arr->field_4 = (void *)5;
          gPolice->field_65C = 4;
          if ( S113_arr->field_70 || S113_arr->field_72 )
          {
            v1->field_659 = 0;
          }
          else
          {
            v7 = S113_arr->field_73;
LABEL_18:
            v1->field_659 = (unsigned __int8)v7 > 1u ? 0 : 2;
          }
          break;
        case 6u:
          S113_arr->field_71 = 0;
          S113_arr->field_4 = (void *)6;
          gPolice->field_65C = 6;
          break;
        default:
          break;
      }
      v8 = S113_arr->field_4;
      if ( (int)v8 > v1->WantedLevel )
        v1->WantedLevel = (int)v8;
      v9 = S113_arr->Ped_;
      if ( !gta2::Ped_Get_433B40(S113_arr->Ped_) || gta2::Ped_GetDeadPed(v9) )
        S113_arr->field_8 = 4;
      v10 = (int)S113_arr->field_4;
      if ( v10 == 1 )
      {
        if ( gta2::Police_sub_4A9590(v1, v9) )
        {
          S113_arr->Max900 = 0;
        }
        else
        {
          Max900 = S113_arr->Max900;
          if ( (unsigned __int16)Max900 >= 0x384u )
          {
            gta2::Ped_SetPoliceNoStar(S113_arr->Ped_);
            LOBYTE(Ped) = 0;
            S113_arr->Ped_->PoliceStar1 = 0;
            S113_arr->Max900 = 0;
            return (char)Ped;
          }
          S113_arr->Max900 = Max900 + 1;
        }
      }
      switch ( S113_arr->field_8 )
      {
        case 0:
          if ( v10 > 0 )
          {
            if ( S113_arr->field_70 )
              goto LABEL_73;
            if ( !v1->Count )
            {
              LOWORD(stru_66B76C.Ped) = 200;
              stru_66B76C.Car = (Car *)3;
              *(_DWORD *)&stru_66B76C.field_24 = 3;
              unk_66B798 = 1;
              if ( gta2::Police_sub_4A9EF0(gPolice, (int)S113_arr) )
              {
                S113_arr->field_8 = 1;
                v1->field_659 = 0;
              }
            }
          }
          break;
        case 1:
          v1->field_659 = 0;
          if ( LOWORD(S113_arr->field_C) == 250 )
          {
            Count = S113_arr->Count;
            v13 = 0;
            S113_arr->field_8 = 3;
            v31 = 0;
            if ( Count )
            {
              do
              {
                v14 = v31;
                v31 = ++v13;
                S113_arr->S112_[v14]->State = 5;
              }
              while ( v13 < (unsigned int)S113_arr->Count );
            }
          }
          break;
        case 3:
          S113_arr->field_1C = 0;
          switch ( v10 )
          {
            case 3:
              v1->field_659 = 0;
              if ( S113_arr->field_70 < (unsigned int)S113_arr->field_71 )
              {
                stru_66B76C.Car = (Car *)3;
                LOWORD(stru_66B76C.Ped) = 50;
                *(_DWORD *)&stru_66B76C.field_24 = 5;
                unk_66B798 = 1;
                gta2::Police_sub_4A9EF0(gPolice, (int)S113_arr);
              }
              break;
            case 4:
              if ( S113_arr->field_70 < (unsigned int)S113_arr->field_71 )
              {
                stru_66B76C.Car = (Car *)3;
                LOWORD(stru_66B76C.Ped) = 50;
                *(_DWORD *)&stru_66B76C.field_24 = 5;
                unk_66B798 = 1;
                gta2::Police_sub_4A9EF0(gPolice, (int)S113_arr);
              }
              if ( !S113_arr->field_72 )
              {
                LOWORD(stru_66B76C.Ped) = 50;
                stru_66B76C.Car = (Car *)5;
                *(_DWORD *)&stru_66B76C.field_24 = 5;
                unk_66B798 = 2;
                if ( gta2::Police_sub_4A9EF0(gPolice, (int)S113_arr) )
                  S113_arr->field_72 = 1;
              }
              break;
            case 5:
              if ( S113_arr->field_70 )
              {
                if ( S113_arr->Count )
                {
                  v15 = (unsigned __int8)S113_arr->Count;
                  do
                  {
                    S113_arr->S112_[0]->field_34 = 1;
                    gta2::S112_sub_4A97C0(S113_arr->S112_[0]);
                    --v15;
                  }
                  while ( v15 );
                }
                S113_arr->field_70 = 0;
                S113_arr->field_71 = 0;
                S113_arr->field_72 = 0;
                gPolice->field_65C = 4;
              }
              break;
            case 6:
              if ( S113_arr->field_70 || S113_arr->field_72 || S113_arr->field_73 )
              {
                if ( S113_arr->Count )
                {
                  v16 = (unsigned __int8)S113_arr->Count;
                  do
                  {
                    gta2::S112_sub_4A97C0(S113_arr->S112_[0]);
                    --v16;
                  }
                  while ( v16 );
                }
                v17 = unk_66B7A4;
                S113_arr->field_70 = 0;
                S113_arr->field_71 = 0;
                unk_66B7A4 = v17 - 1;
                gPolice->field_65C = 6;
              }
              break;
            default:
              break;
          }
          if ( S113_arr->field_70 > (unsigned int)S113_arr->field_71 )
          {
            v18 = 0;
            v32 = 0;
            if ( S113_arr->Count )
            {
              while ( 1 )
              {
                v19 = S113_arr->S112_[v32];
                if ( v19 )
                {
                  if ( v19->field_1C == 1 && v19->field_20 == 1 && v19->S110_->Car )
                    break;
                }
                v32 = ++v18;
                if ( v18 >= (unsigned int)S113_arr->Count )
                  goto LABEL_96;
              }
              v20 = &S113_arr->S112_[v32];
              (*v20)->field_34 = 1;
              gta2::S112_sub_4A97C0(*v20);
            }
          }
          break;
        case 4:
          if ( S113_arr->Count )
          {
            v26 = (unsigned __int8)S113_arr->Count;
            do
            {
              v27 = S113_arr->S112_[0];
              if ( v27->field_1C )
              {
                gta2::S112_sub_4A97C0(v27);
              }
              else if ( S113_arr->Count )
              {
                v28 = (unsigned __int8)S113_arr->Count;
                S113_arr->S112_[0] = (S112 *)*((_DWORD *)&S113_arr->field_1C + v28);
                *((_DWORD *)&S113_arr->field_1C + v28) = 0;
                --S113_arr->Count;
              }
              else
              {
                S113_arr->S112_[0] = 0;
              }
              --v26;
            }
            while ( v26 );
          }
          v29 = unk_66B7A4;
          S113_arr->Ped_ = 0;
          S113_arr->field_70 = 0;
          S113_arr->field_71 = 0;
          S113_arr->Count = 0;
          S113_arr->field_76 = 0;
          BYTE2(S113_arr->field_C) = 0;
          unk_66B7A4 = v29 - 1;
          gPolice->field_65C = 3;
          break;
        case 5:
          if ( LOWORD(S113_arr->field_C) )
          {
            S113_arr->field_8 = 3;
          }
          else if ( v10 == 5 )
          {
LABEL_73:
            S113_arr->field_8 = 3;
          }
          else if ( !S113_arr->field_1C )
          {
            v21 = 1;
            if ( !S113_arr->Count )
              goto LABEL_104;
            S112 = S113_arr->S112_;
            v34 = (unsigned __int8)S113_arr->Count;
            do
            {
              v23 = *S112;
              if ( *S112 && v23->State == 3 )
              {
                v24 = S113_arr->Ped_;
                if ( S113_arr->Ped_ )
                {
                  gta2::Ped_GetYCoordinate(v24, (int *)v36);
                  gta2::Ped_GetXCoordinate(v24, (int)v37);
                  v25 = gta2::sub_42A6B0(&S113_arr->field_14, v38);
                  if ( gta2::Car_sub_403800(v25, (int)&stru_66B7D0) )
                  {
                    gta2::S112_sub_4A97C0(v23);
                    S113_arr->field_1C = 1;
                  }
                }
                v21 = 0;
              }
              ++S112;
              --v34;
            }
            while ( v34 );
            v1 = self;
            if ( v21 )
            {
LABEL_104:
              if ( !v1->Count )
              {
                LOWORD(stru_66B76C.Ped) = 200;
                stru_66B76C.Car = (Car *)3;
                *(_DWORD *)&stru_66B76C.field_24 = 3;
                unk_66B798 = 1;
                gta2::Police_sub_4A9EF0(gPolice, (int)S113_arr);
              }
            }
          }
          break;
        default:
          break;
      }
LABEL_96:
      LOBYTE(Ped) = ++v33;
      if ( v33 < 4u )
      {
        LOBYTE(Ped) = v33;
        S113_arr = &v1->S113_arr[v33];
      }
    }
    while ( S113_arr->Ped_ );
  }
  return (char)Ped;
}


// 0x004aa710: Police::sub_4AA710
// IDA: Police::sub_4AA710
// Ghidra: ---
SpriteS1 * gta2::Police_sub_4AA710(struct Police *self, Ped *pPed, Ped *a1, int a2, int a3, __int16 a6)
{
  Remap Remap; // al

  if ( self->field_65C == 6 )
  {
    gta2::Ped_SetCurrentOccupation(pPed, UNK_REL_TO_POLICE_3);
    gta2::Ped_SetSearchType(pPed, SEARCHTYPE_AREA);
    gta2::Ped_SetRemap(pPed, 4);
  }
  else
  {
    gta2::Ped_SetCurrentOccupation(pPed, UNK_REL_TO_POLICE_1);
    gta2::Ped_SetSearchType(pPed, SEARCHTYPE_AREA);
    gta2::Ped_SetRemap(pPed, 0);
  }
  pPed->Invulnerability = GRAPHIC_GANG;
  pPed->field_224 = 1;
  pPed->field_228 = 1;
  gta2::Ped_SetPedPosition(pPed, (int)a1, a2, a3);
  Remap = gta2::Ped_GetRemap(pPed);
  gta2::Ped_SetRemap_0(pPed, Remap);
  gta2::Ped_SetRotation(pPed, a6);
  return gta2::Ped_sub_433DF0(pPed);
}


// 0x004aa7b0: Police::sub_4AA7B0
// IDA: Police::sub_4AA7B0
// Ghidra: ---
char gta2::Police_sub_4AA7B0(struct Police *self, int a2)
{
  struct S112 *pS112; // ebx
  struct S110 *pS110; // ebp
  __int16 v5; // ax
  Police *pMedical; // ecx
  int v7; // edx
  struct Ped *Ped; // esi
  struct Ped *v9; // edi
  int WantedLevel; // eax
  struct Car *Car; // ecx
  int v13; // [esp+4h] [ebp-10h] BYREF
  int v14; // [esp+8h] [ebp-Ch] BYREF
  int v15; // [esp+Ch] [ebp-8h] BYREF
  int v16; // [esp+10h] [ebp-4h] BYREF
  struct S169 *v17; // [esp+18h] [ebp+4h]

  if ( gCharacter->field_5 >= 0x1Eu || self->Count > 2u )
    return 0;
  pS112 = gta2::Police_sub_4A9AE0(self);
  pS112->field_1C = 1;
  pS110 = gta2::S109_sub_4C5430(gS109);
  pS112->S110_ = pS110;
  if ( !pS110 )
  {
    gta2::S112_Defaut(pS112);
    return 0;
  }
  v5 = unk_66B7A8;
  pS112->State = 1;
  pS112->field = v5;
  pS112->field_29 = 1;
  pS110->field_1E = 1;
  pMedical = gPolice;
  v7 = gPolice->field_65C;
  unk_66B7A8 = v5 + 1;
  pS110->field_20 = v7;
  pS110->field_24 = 1;
  pS110->Car = (Car *)a2;
  v17 = gta2::Medical_sub_404C40((Medical *)pMedical);
  Ped = gta2::Character_CreatePed(gCharacter);
  gta2::Ped_SetSearchType(Ped, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(Ped, POLICE);
  gta2::Ped_PutPedInCarRelated(Ped, pS110->Car);
  gta2::Ped_PedSetObjective(Ped, 43, 9999);
  Ped->field_224 = 1;
  Ped->field_228 = 1;
  v9 = gta2::Character_CreatePed(gCharacter);
  gta2::Ped_PedSetObjective(v9, 0, 9999);
  gta2::Ped_sub_433320(v9, pS110->Car);
  gta2::Ped_SetSearchType(v9, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(v9, POLICE);
  v9->field_224 = 1;
  v9->field_228 = 1;
  if ( gPolice->field_65C != 3 )
  {
    if ( gPolice->field_65C == 4 )
    {
      gta2::Ped_SetHealth(Ped, 250);
      gta2::Ped_SetNPCWeapon(Ped, DR);
      gta2::Ped_sub_43AD10(Ped, SMG_G);
      gta2::Ped_SetRemap(Ped, 8);
      gta2::Ped_SetCurrentOccupation(Ped, FBI);
      Ped->Invulnerability = GRAPHIC_EMERG;
      gta2::Ped_SetHealth(v9, 250);
      gta2::Ped_SetRemap(v9, 8);
      gta2::Ped_SetNPCWeapon(v9, SMG_G);
      v9->Invulnerability = GRAPHIC_EMERG;
      gta2::Ped_SetCurrentOccupation(v9, FBI);
      pS112->field_20 = 3;
    }
    else
    {
      gta2::Ped_SetHealth(Ped, 250);
      gta2::Ped_SetNPCWeapon(Ped, SMG);
      gta2::Ped_SetRemap(Ped, 4);
      gta2::Ped_SetCurrentOccupation(Ped, ARMYARMY);
      Ped->Invulnerability = GRAPHIC_GANG;
      gta2::Ped_SetHealth(v9, 250);
      gta2::Ped_SetNPCWeapon(v9, SMG);
      gta2::Ped_SetRemap(v9, 4);
      gta2::Ped_SetCurrentOccupation(v9, ARMYARMY);
      v9->Invulnerability = GRAPHIC_GANG;
      pS112->field_20 = 4;
    }
    goto LABEL_17;
  }
  WantedLevel = self->WantedLevel;
  if ( WantedLevel < 0 )
    goto LABEL_15;
  if ( WantedLevel <= 1 )
  {
    Ped->WeaponSelect = 0;
    gta2::Ped_sub_43AD10(Ped, Pistolet);
    gta2::Ped_SetHealth(Ped, 50);
    Ped->field_18C = (int)gta2::Radar_AddBlip((Tango *)&unk_66B8C4, (SpriteS1 *)&v15, (PublicTransport *)&unk_66B93C)->FirstElement;
    v9->WeaponSelect = 0;
    gta2::Ped_sub_43AD10(v9, Pistolet);
    gta2::Ped_SetHealth(v9, 50);
    v9->field_18C = (int)gta2::Radar_AddBlip((Tango *)&unk_66B8C4, (SpriteS1 *)&v16, (PublicTransport *)&unk_66B93C)->FirstElement;
    goto LABEL_16;
  }
  if ( WantedLevel != 2 )
  {
LABEL_15:
    gta2::Ped_sub_43AD10(Ped, Pistolet);
    gta2::Ped_SetHealth(Ped, 100);
    gta2::Ped_sub_43AD10(v9, Pistolet);
    gta2::Ped_SetHealth(v9, 100);
    goto LABEL_16;
  }
  gta2::Ped_sub_43AD10(Ped, Pistolet);
  gta2::Ped_SetHealth(Ped, 100);
  Ped->field_18C = (int)gta2::Radar_AddBlip((Tango *)&unk_66B8C4, (SpriteS1 *)&v13, (PublicTransport *)&unk_66B93C)->FirstElement;
  gta2::Ped_sub_43AD10(v9, Pistolet);
  gta2::Ped_SetHealth(v9, 100);
  v9->field_18C = (int)gta2::Radar_AddBlip((Tango *)&unk_66B8C4, (SpriteS1 *)&v14, (PublicTransport *)&unk_66B93C)->FirstElement;
LABEL_16:
  gta2::Ped_SetCurrentOccupation(Ped, POLICE);
  gta2::Ped_SetRemap(Ped, 0);
  Ped->Invulnerability = GRAPHIC_GANG;
  gta2::Ped_SetRemap(v9, 0);
  v9->Invulnerability = GRAPHIC_GANG;
  pS112->field_20 = 1;
LABEL_17:
  gta2::S169_sub_404400(v17, Ped);
  gta2::S169_SetListSize(v17, 1);
  gta2::S169_AddPedtoList(v17, v9, 0);
  LOBYTE(v17->Ped1[0]) = 0;
  Car = pS110->Car;
  pS110->Ped_ = Ped;
  pS110->field_18 = 0;
  pS110->field_28 = 6;
  gta2::Car_CarMakeDriveable1(Car, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
  gta2::Car_CarMakeDummy(pS110->Car);
  gta2::Car_sub_4222D0(pS110->Car);
  ++self->Count;
  return 1;
}


// 0x004aabb0: Police::CriminalTakesPoliceCar
// IDA: Police::CriminalTakesPoliceCar
// Ghidra: ---
bool gta2::Police_CriminalTakesPoliceCar(struct Police *self, Car *pCar, Ped *a3)
{
  bool result; // al
  unsigned __int8 v6; // dl
  S113 *v7; // ecx
  unsigned __int8 v8; // dl
  struct S110 *S110; // esi
  unsigned __int8 v10; // [esp+10h] [ebp+8h]
  unsigned __int8 index; // [esp+10h] [ebp+8h]

  result = gta2::Ped_IsPlayerControlled(a3);
  if ( result )
  {
    v6 = 0;
    v10 = 0;
    while ( self->S113_arr[v10].Ped != a3 )
    {
      v10 = ++v6;
      if ( v6 >= 4u )
        return 0;
    }
    v7 = &self->S113_arr[v10];
    if ( (Police *)((char *)self + 124 * v10) == (Police *)-1124 )
      return 0;
    v8 = 0;
    index = 0;
    while ( !self->S112_[index].field_1C || self->S112_[index].S110->Car != pCar )
    {
      index = ++v8;
      if ( v8 >= 0x14u )
        return 0;
    }
    if ( self->S112_[index].S110->field_20 != 6 && v7->field_4 == (void *)6 )
    {
      return 0;
    }
    else
    {
      v7->field_8 = 3;
      self->S112_[index].S113 = v7;
      self->S112_[index].State = 5;
      gta2::S112_sub_4A9720(&self->S112_[index]);
      S110 = self->S112_[index].S110;
      if ( S110->field_20 != 6 )
        gta2::Car_sub_422D20(S110->Car);
      return 1;
    }
  }
  return result;
}


// 0x004aaca0: Police::sub_4AACA0
// IDA: Police::sub_4AACA0
// Ghidra: Police::FUN_004aaca0
void gta2::Police_sub_4AACA0(struct Police *self,Ped *pPed)
{
  struct Ped *pPVar1;
  undefined4 *puVar2;
  byte bVar3;
  uint local_4;
  
  pPVar1 = pPed;
  bVar3 = 0;
  local_4 = 0;
  do {
    if (self->Array_StainInfo[local_4].Ped == pPed) {
      puVar2 = (undefined4 *)gta2::Ped_GetXCoordinate(pPed,(int)&pPed);
      self->Array_StainInfo[local_4].S110 = (GlassInfo *)*puVar2;
      puVar2 = (undefined4 *)gta2::Ped_GetYCoordinate(pPVar1, &pPed);
      self->Array_StainInfo[local_4].ped2 = (Ped *)*puVar2;
      puVar2 = (undefined4 *)gta2::Ped_GetPositionZ(pPVar1,(int)&pPed);
      pPVar1 = (Ped *)*puVar2;
      self->Array_StainInfo[local_4].field3_0xc = 0xfa;
      self->Array_StainInfo[local_4].ped1 = pPVar1;
      return;
    }
    bVar3 = bVar3 + 1;
    local_4 = (uint)bVar3;
  } while (bVar3 < 4);
  return;
}


// 0x004aad40: Police::sub_4AAD40
// IDA: Police::sub_4AAD40
// Ghidra: ---
int gta2::Police_sub_4AAD40(struct Police *self, Ped *pPed)
{
  unsigned __int8 count; // cl
  struct Ped *v4; // edi
  int result; // eax
  char *v6; // esi
  _DWORD *v7; // eax
  unsigned __int8 index; // [esp+Ch] [ebp-4h]

  count = 0;
  v4 = pPed;
  index = 0;
  while ( 1 )
  {
    result = index;
    if ( self->S113_arr[index].Ped == pPed )
      break;
    index = ++count;
    if ( count >= 4u )
      return result;
  }
  v6 = &self->Field + 124 * index;
  *((_DWORD *)v6 + 285) = *(_DWORD *)gta2::Ped_GetXCoordinate(pPed, (int)&pPed);
  gta2::Ped_GetYCoordinate(v4, (int *)&pPed);
  *((_DWORD *)v6 + 286) = *v7;
  result = *(_DWORD *)gta2::Ped_GetPositionZ(v4, (int)&pPed);
  *((_DWORD *)v6 + 287) = result;
  return result;
}


// 0x004aee70: Police::sub_4AEE70
// IDA: Police::sub_4AEE70
// Ghidra: ---
char gta2::Police_sub_4AEE70(struct Police *self, unsigned __int8 a2, unsigned __int8 a3, int a4)
{
  char v5; // bl
  int *v6; // ecx
  int *MaxZForLocation; // eax
  char v8; // al
  PoliceRoadblock **p_PoliceRoadblock; // ecx
  char PoliceRoadblock; // al
  char result; // al
  int *v12; // [esp-8h] [ebp-18h] BYREF
  int v13; // [esp-4h] [ebp-14h] BYREF

  v5 = 0;
  switch ( self->WantedLevel )
  {
    case 3:
    case 4:
      unk_66B798 = 1;
      break;
    case 5:
      unk_66B798 = 3;
      break;
    case 6:
      unk_66B798 = 4;
      break;
    default:
      break;
  }
  if ( a4 > 0 && a4 <= 2 )
    v5 = 1;
  v13 = 1;
  gta2::S202_sub_40CE30((S202 *)&v13, a3);
  v12 = v6;
  gta2::S202_sub_40CE30((S202 *)&v12, a2);
  MaxZForLocation = gta2::MapRelatedStruct_FindMaxZForLocation(gMapRelatedStruct, &a4, v12, (S202 *)v13);
  v8 = gta2::Weapon_sub_41C1E0((Weapon *)MaxZForLocation);
  p_PoliceRoadblock = &self->PoliceRoadblock;
  LOBYTE(a4) = v8;
  PoliceRoadblock = (char)self->PoliceRoadblock;
  if ( !v5 )
  {
    if ( !PoliceRoadblock )
      return gta2::PoliceRoadblock_sub_4ADB70((PoliceRoadblock *)p_PoliceRoadblock, a2, a3, a4, 2);
LABEL_13:
    result = (char)self->PoliceRoadblock1;
    p_PoliceRoadblock = &self->PoliceRoadblock1;
    if ( result )
      return result;
    return gta2::PoliceRoadblock_sub_4ADB70((PoliceRoadblock *)p_PoliceRoadblock, a2, a3, a4, 3);
  }
  if ( PoliceRoadblock )
    goto LABEL_13;
  return gta2::PoliceRoadblock_sub_4ADB70((PoliceRoadblock *)p_PoliceRoadblock, a2, a3, a4, 3);
}


// 0x004aef70: Police::sub_4AEF70
// IDA: Police::sub_4AEF70
// Ghidra: ---
char gta2::Police_sub_4AEF70(struct Police *self)
{
  bool v2; // zf
  struct S112 *S112; // edi
  int v4; // ebp
  int PedState; // eax
  struct Ped *Ped; // edi

  v2 = unk_66B7A4 == 1;
  self->field_7B4 = 0;
  self->WantedLevel = 0;
  if ( v2 )
    gta2::Police_sub_4AA030(self);
  S112 = self->S112_;
  v4 = 20;
  do
  {
    if ( S112->field_1C == 1 )
      gta2::S112_sub_4AD600(S112);
    ++S112;
    --v4;
  }
  while ( v4 );
  if ( unk_66B7A4 == 1 )
    gta2::Police_sub_4A9E80(self);
  gta2::PoliceRoadblock_sub_4AD6C0((PoliceRoadblock *)&self->PoliceRoadblock);
  gta2::PoliceRoadblock_sub_4AD6C0((PoliceRoadblock *)&self->PoliceRoadblock1);
  LOBYTE(PedState) = self->field_7AC;
  if ( (_BYTE)PedState )
  {
    LOBYTE(PedState) = PedState - 1;
    self->field_7AC = PedState;
  }
  Ped = self->Ped_;
  if ( Ped )
  {
    PedState = gta2::Ped_GetPedState(self->Ped_);
    if ( PedState == 9
      || (LOBYTE(PedState) = gta2::Ped_Get_433B40(Ped), !(_BYTE)PedState)
      || (PedState = Ped->PositionX1, (PedState & 0x800) == 0) )
    {
      self->Ped_ = 0;
    }
  }
  return PedState;
}



