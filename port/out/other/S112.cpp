#include "gta2_shim.h"

// Module: other, Class: S112
// Functions: 18
// Source: unified (IDA+Ghidra)

// 0x004a96d0: S112::Defaut
// IDA: S112::Defaut
// Ghidra: ---
int gta2::S112_Defaut(struct S112 *self)
{
  int result; // eax

  result = 0;
  self->X = 0;
  self->Y = 0;
  self->Z = 0;
  self->field_18 = 0;
  self->field_1C = 0;
  self->field_1A = 0;
  self->S110_ = 0;
  self->State = 0;
  self->field_28 = 0;
  self->field_8 = dword_66B89C;
  self->field_C = dword_66B89C;
  self->S113_ = 0;
  self->field_1A = 0;
  self->field_29 = 0;
  self->field_2A = 0;
  self->field_2C = 0;
  self->field_30 = 0;
  self->field_34 = 0;
  return result;
}


// 0x004a9720: S112::sub_4A9720
// IDA: S112::sub_4A9720
// Ghidra: ---
char gta2::S112_sub_4A9720(struct S112 *self)
{
  struct S113 *S113; // esi
  int v2; // eax
  unsigned __int8 v3; // dl
  unsigned __int8 v5; // [esp+4h] [ebp-4h]

  S113 = self->S113_;
  LOBYTE(v2) = S113->Count;
  if ( (unsigned __int8)v2 < 6u )
  {
    v3 = 0;
    v5 = 0;
    while ( S113->S112_[v5] != self )
    {
      v5 = ++v3;
      if ( v3 >= 6u )
      {
        S113->S112_[(unsigned __int8)S113->Count] = self;
        ++self->S113_->Count;
        v2 = self->S110_->field_20 - 3;
        switch ( self->S110_->field_20 )
        {
          case 3:
            ++self->S113_->field_70;
            break;
          case 4:
            ++self->S113_->field_73;
            break;
          case 5:
            ++self->S113_->field_72;
            break;
          case 6:
            ++self->S113_->field_74;
            break;
          default:
            return v2;
        }
        return v2;
      }
    }
  }
  return v2;
}


// 0x004a97c0: S112::sub_4A97C0
// IDA: S112::sub_4A97C0
// Ghidra: FUN_004a97c0
void gta2::S112_sub_4A97C0(void *self)
{
  char *pcVar1;
  int iVar2;
  int iVar3;
  byte bVar4;
  byte bVar5;
  uint local_4;
  
  if ((*(int *)((int)self + 0x1c) == 0) ||
     (((iVar2 = *(int *)((int)self + 0x24), iVar2 != 0 && (iVar2 != 1)) &&
      (iVar2 != 6)))) {
    iVar3 = *(int *)((int)self + 0x14);
    bVar5 = *(char *)(iVar3 + 0x75) - 1;
    local_4 = (uint)bVar5;
    iVar2 = local_4 * 4 + 0x20;
    if (*(void **)(iVar2 + iVar3) == self) {
      *(undefined4 *)(iVar2 + iVar3) = 0;
    }
    else {
      local_4 = 0;
      if (bVar5 != 0) {
        do {
          if (*(void **)(iVar3 + 0x20 + local_4 * 4) == self) {
            *(void **)(iVar3 + 0x20 + local_4 * 4) = *(void **)(iVar2 + iVar3);
            *(undefined4 *)(iVar2 + *(int *)((int)self + 0x14)) = 0;
            break;
          }
          bVar4 = (char)local_4 + 1;
          local_4 = (uint)bVar4;
        } while (bVar4 < bVar5);
      }
    }
    if (*(int *)((int)self + 0x1c) != 0) {
      switch(*(undefined4 *)((int)self + 0x20)) {
      case 1:
        *(char *)(*(int *)((int)self + 0x14) + 0x70) =
             *(char *)(*(int *)((int)self + 0x14) + 0x70) + -1;
        *(char *)(*(int *)((int)self + 0x14) + 0x75) =
             *(char *)(*(int *)((int)self + 0x14) + 0x75) + -1;
        *(undefined4 *)((int)self + 0x24) = 6;
        return;
      case 2:
        *(char *)(*(int *)((int)self + 0x14) + 0x72) =
             *(char *)(*(int *)((int)self + 0x14) + 0x72) + -1;
        *(char *)(*(int *)((int)self + 0x14) + 0x75) =
             *(char *)(*(int *)((int)self + 0x14) + 0x75) + -1;
        *(undefined4 *)((int)self + 0x24) = 6;
        return;
      case 3:
        *(char *)(*(int *)((int)self + 0x14) + 0x73) =
             *(char *)(*(int *)((int)self + 0x14) + 0x73) + -1;
        *(char *)(*(int *)((int)self + 0x14) + 0x75) =
             *(char *)(*(int *)((int)self + 0x14) + 0x75) + -1;
        *(undefined4 *)((int)self + 0x24) = 6;
        return;
      case 4:
        pcVar1 = (char *)(*(int *)((int)self + 0x14) + 0x74);
        *pcVar1 = *pcVar1 + -1;
      }
    }
    *(char *)(*(int *)((int)self + 0x14) + 0x75) =
         *(char *)(*(int *)((int)self + 0x14) + 0x75) + -1;
    *(undefined4 *)((int)self + 0x24) = 6;
  }
  return;
}


// 0x004a9930: S112::sub_4A9930
// IDA: S112::sub_4A9930
// Ghidra: ---
int gta2::S112_sub_4A9930(struct S112 *self)
{
  int result; // eax
  int v3; // ecx
  unsigned __int8 i; // [esp+8h] [ebp-4h]

  result = (int)self->S113_;
  if ( result )
  {
    for ( i = 0; i < *(_BYTE *)(result + 117); ++i )
    {
      if ( self == *(S112 **)(result + 4 * i + 32) )
      {
        v3 = *(unsigned __int8 *)(result + 117);
        if ( i == v3 - 1 )
        {
          *(_DWORD *)(result + 4 * i + 32) = 0;
        }
        else
        {
          *(_DWORD *)(result + 4 * i + 32) = *(_DWORD *)(result + 4 * v3 + 28);
          *(_DWORD *)(result + 4 * *(unsigned __int8 *)(result + 117) + 28) = 0;
        }
        --*(_BYTE *)(result + 117);
        switch ( self->S110_->field_20 )
        {
          case 3:
            --self->S113_->field_70;
            break;
          case 4:
            --self->S113_->field_73;
            break;
          case 5:
            --self->S113_->field_72;
            break;
          case 6:
            --self->S113_->field_74;
            break;
          default:
            continue;
        }
      }
    }
  }
  return result;
}


// 0x004aadd0: S112::sub_4AADD0
// IDA: S112::sub_4AADD0
// Ghidra: ---
int gta2::S112_sub_4AADD0(struct S112 *self)
{
  struct S169 *v2; // ebx
  struct Ped *Ped; // esi
  int WantedLevel; // eax
  struct Ped *v5; // edi
  int result; // eax
  struct Ped *v7; // [esp+10h] [ebp-8h] BYREF
  int v8; // [esp+14h] [ebp-4h] BYREF

  v2 = gta2::Medical_sub_404C40((struct Medical *)self);
  Ped = gta2::Character_CreatePed(gCharacter);
  gta2::Ped_SetSearchType(Ped, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(Ped, POLICE);
  gta2::Ped_PutPedInCarRelated(Ped, self->S110_->Car);
  gta2::Ped_PedSetObjective(Ped, 14, 0);
  gta2::S202_sub_40CE30((struct S202 *)&v7, self->X);
  Ped->Weapon2 = (int)v7;
  gta2::S202_sub_40CE30((struct S202 *)&v7, self->Y);
  Ped->Gang_ = v7;
  gta2::S202_sub_40CE30((struct S202 *)&v7, self->Z);
  Ped->DriverPed = (int)v7;
  gta2::Ped_SetRemap(Ped, 0);
  Ped->Invulnerability = GRAPHIC_GANG;
  WantedLevel = gPolice->WantedLevel;
  if ( WantedLevel >= 0 )
  {
    if ( WantedLevel <= 1 )
    {
      Ped->WeaponSelect = 0;
      gta2::Ped_sub_43AD10(Ped, Pistolet);
      gta2::Ped_SetHealth(Ped, 50);
      Ped->field_18C = (int)gta2::Radar_AddBlip((struct Tango *)&unk_66B8C4, (struct SpriteS1 *)&v8, (struct PublicTransport *)&unk_66B93C)->FirstElement;
      goto LABEL_7;
    }
    if ( WantedLevel == 2 )
    {
      gta2::Ped_sub_43AD10(Ped, Pistolet);
      gta2::Ped_SetHealth(Ped, 100);
      Ped->field_18C = (int)gta2::Radar_AddBlip((struct Tango *)&unk_66B8C4, (struct SpriteS1 *)&v7, (struct PublicTransport *)&unk_66B93C)->FirstElement;
      goto LABEL_7;
    }
  }
  gta2::Ped_sub_43AD10(Ped, Pistolet);
  gta2::Ped_SetHealth(Ped, 100);
LABEL_7:
  Ped->field_224 = 1;
  Ped->field_228 = 1;
  v5 = gta2::Character_CreatePed(gCharacter);
  gta2::Ped_sub_433320(v5, self->S110_->Car);
  gta2::Ped_SetSearchType(v5, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(v5, POLICE);
  gta2::Ped_PedSetObjective(v5, 0, 9999);
  gta2::Ped_SetRemap(v5, 0);
  if ( self->S113_->field_4 == (void *)1 )
  {
    v5->WeaponSelect = 0;
    gta2::Ped_sub_43AD10(v5, Pistolet);
    gta2::Ped_SetHealth(v5, 50);
    v5->field_18C = (int)gta2::Radar_AddBlip((struct Tango *)&unk_66B8C4, (struct SpriteS1 *)&v7, (struct PublicTransport *)&unk_66B93C)->FirstElement;
  }
  else if ( self->S113_->field_4 == (void *)2 )
  {
    gta2::Ped_sub_43AD10(v5, Pistolet);
    gta2::Ped_SetHealth(v5, 100);
    v5->field_18C = (int)gta2::Radar_AddBlip((struct Tango *)&unk_66B8C4, (struct SpriteS1 *)&v8, (struct PublicTransport *)&unk_66B93C)->FirstElement;
  }
  else
  {
    gta2::Ped_sub_43AD10(v5, Pistolet);
    gta2::Ped_SetHealth(v5, 100);
  }
  v5->field_224 = 1;
  v5->field_228 = 1;
  v5->Invulnerability = GRAPHIC_GANG;
  gta2::S169_sub_404400(v2, Ped);
  gta2::S169_SetListSize(v2, 1);
  gta2::S169_AddPedtoList(v2, v5, 0);
  LOBYTE(v2->Ped1[0]) = 0;
  self->S110_->Ped_ = Ped;
  self->S110_->field_28 = 6;
  gta2::Car_CarMakeDriveable1(self->S110_->Car, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
  gta2::Car_CarMakeDummy(self->S110_->Car);
  gta2::Car_sub_4222D0(self->S110_->Car);
  gta2::Car_sub_422D20(self->S110_->Car);
  self->S110_->NPC = v2;
  return result;
}


// 0x004ab060: S112::sub_4AB060
// IDA: S112::sub_4AB060
// Ghidra: ---
int gta2::S112_sub_4AB060(struct S112 *self)
{
  struct S169 *v2; // ebx
  struct Ped *Ped; // edi
  struct Ped *v4; // esi
  int result; // eax
  unsigned __int8 v6; // [esp-4h] [ebp-18h]
  unsigned __int8 Id[4]; // [esp+10h] [ebp-4h] BYREF

  v2 = gta2::Medical_sub_404C40((struct Medical *)self);
  Ped = gta2::Character_CreatePed(gCharacter);
  gta2::Ped_SetSearchType(Ped, SEARCHTYPE_AREA_PLAYER_ONLY);
  gta2::Ped_SetCurrentOccupation(Ped, SWAT);
  gta2::Ped_PutPedInCarRelated(Ped, self->S110_->Car);
  gta2::Ped_PedSetObjective(Ped, 14, 0);
  gta2::S202_sub_40CE30((struct S202 *)Id, self->X);
  Ped->Weapon2 = *(_DWORD *)Id;
  gta2::S202_sub_40CE30((struct S202 *)Id, self->Y);
  Ped->Gang_ = *(Ped **)Id;
  gta2::S202_sub_40CE30((struct S202 *)Id, self->Z);
  Ped->DriverPed = *(_DWORD *)Id;
  gta2::Ped_SetRemap(Ped, -1);
  gta2::Ped_SetNPCWeapon(Ped, Pistolet);
  gta2::Ped_SetHealth(Ped, 400);
  Ped->field_224 = 1;
  Ped->field_228 = 1;
  Ped->Invulnerability = GRAPHIC_GANG;
  gta2::S169_sub_404400(v2, Ped);
  gta2::S169_SetListSize(v2, 3);
  Id[0] = 0;
  do
  {
    v4 = gta2::Character_CreatePed(gCharacter);
    gta2::Ped_sub_433320(v4, self->S110_->Car);
    gta2::Ped_SetSearchType(v4, SEARCHTYPE_AREA_PLAYER_ONLY);
    gta2::Ped_SetCurrentOccupation(v4, SWAT);
    gta2::Ped_PedSetObjective(v4, 0, 9999);
    gta2::Ped_SetRemap(v4, -1);
    gta2::Ped_SetNPCWeapon(v4, Pistolet);
    gta2::Ped_SetHealth(v4, 400);
    v6 = Id[0];
    v4->field_224 = 1;
    v4->field_228 = 1;
    v4->Invulnerability = GRAPHIC_GANG;
    gta2::S169_AddPedtoList(v2, v4, v6);
    ++Id[0];
  }
  while ( Id[0] < 3u );
  LOBYTE(v2->Ped1[0]) = 0;
  self->S110_->Ped_ = Ped;
  self->S110_->field_28 = 6;
  gta2::Car_CarMakeDriveable1(self->S110_->Car, SEARCHTYPE_AREA_PLAYER_ONLY|SEARCHTYPE_LINE_OF_SIGHT);
  gta2::Car_CarMakeDummy(self->S110_->Car);
  gta2::Car_sub_4222D0(self->S110_->Car);
  gta2::Car_sub_422D20(self->S110_->Car);
  self->S110_->NPC = v2;
  return result;
}


// 0x004ab400: S112::sub_4AB400
// IDA: S112::sub_4AB400
// Ghidra: ---
void gta2::S112_sub_4AB400(struct S112 *self)
{
  struct S110 *S110; // esi
  struct Car *Car; // ebx
  struct S169 *v4; // ebp
  struct Ped *j; // esi
  struct S169 *v6; // eax
  int v7; // edx
  struct Ped *v8; // esi
  struct S169 *NPC; // ecx
  struct Ped *i; // esi
  struct S169 *v11; // eax
  int v12; // edx
  struct Ped *Ped; // ebx
  unsigned __int8 v14; // [esp+10h] [ebp-4h]
  unsigned __int8 v15; // [esp+10h] [ebp-4h]

  S110 = self->S110_;
  Car = S110->Car;
  if ( !S110->Car )
  {
    NPC = S110->NPC;
    if ( NPC )
    {
      if ( gta2::S169_sub_403C40(NPC) )
      {
        v15 = 0;
        for ( i = self->S110_->Ped_; i; i = v11->Ped_Arr9[v12] )
        {
          gta2::Ped_SetDefault(i);
          gta2::Ped_sub_43E650(i);
          v11 = self->S110_->NPC;
          if ( !v11 )
            break;
          v12 = v15++;
        }
        gta2::S169_sub_403BE0(self->S110_->NPC);
        self->S110_->field_28 = 5;
        self->S110_->field_2C = 1;
      }
      return;
    }
    Ped = S110->Ped_;
    if ( !Ped )
    {
      S110->field_28 = 5;
      self->S110_->field_2C = 1;
      return;
    }
    if ( gta2::Ped_GetSub_4039F0(S110->Ped_) >= 0x1Eu )
    {
      gta2::Ped_sub_43E650(Ped);
      self->S110_->field_28 = 5;
      self->S110_->field_2C = 1;
      return;
    }
    if ( !Ped->field_10B )
    {
      if ( Ped->field_228 != 1 )
      {
        S110->field_28 = 5;
        self->S110_->field_2C = 1;
      }
      return;
    }
    gta2::Ped_sub_43E650(Ped);
LABEL_26:
    self->S110_->field_28 = 5;
    self->S110_->field_2C = 1;
    return;
  }
  v4 = S110->NPC;
  if ( !v4 )
  {
    v8 = S110->Ped_;
    if ( !v8 )
    {
      if ( gta2::Car_sub_4A9AD0(Car) > 200 )
      {
        gta2::Car_isMask4(Car);
        self->S110_->field_28 = 5;
        self->S110_->field_2C = 1;
      }
      return;
    }
    if ( v8->? <= 0x1Eu || gta2::Car_sub_4A9AD0(Car) <= 200 )
      return;
    gta2::Ped_sub_43E650(v8);
    gta2::Car_isMask4(self->S110_->Car);
    goto LABEL_26;
  }
  if ( gta2::Car_sub_4A9AD0(S110->Car) > 200 && gta2::S169_sub_403C40(v4) )
  {
    v14 = 0;
    for ( j = self->S110_->Ped_; j; j = v6->Ped_Arr9[v7] )
    {
      gta2::Ped_SetDefault(j);
      gta2::Ped_sub_43E650(j);
      v6 = self->S110_->NPC;
      if ( !v6 )
        break;
      v7 = v14++;
    }
    gta2::S169_sub_403BE0(self->S110_->NPC);
    gta2::Car_isMask4(self->S110_->Car);
    goto LABEL_26;
  }
}


// 0x004ab610: S112::sub_4AB610
// IDA: S112::sub_4AB610
// Ghidra: ---
void gta2::S112_sub_4AB610(struct S112 *self)
{
  struct Car *CurrentCar; // eax
  struct S110 *S110; // eax
  struct S169 *NPC; // edi
  struct Ped *i; // edi
  struct S169 *v6; // eax
  int v7; // edx
  struct S110 *v8; // ebp
  char v9; // bl
  struct S169 *v10; // edi
  struct Ped *v11; // ecx
  unsigned __int8 v12; // bl
  struct Ped *j; // edi
  struct Car *Car; // edi
  struct S110 *v15; // edi
  struct S169 *v16; // ecx
  struct S110 *v17; // edi
  struct Car *v18; // ebx
  struct Ped *Ped; // edi
  struct S169 *v20; // eax
  struct S110 *v21; // eax
  struct Car *v22; // ebx
  char v23; // [esp+13h] [ebp-5h]
  unsigned __int8 v24; // [esp+14h] [ebp-4h]
  unsigned __int8 k; // [esp+14h] [ebp-4h]

  CurrentCar = unk_66B794->field_10B;
  if ( CurrentCar && unk_66B794 == CurrentCar->Driver )
  {
    S110 = self->S110_;
    NPC = S110->NPC;
    if ( NPC )
    {
      if ( gta2::Car_sub_4A9AD0(S110->Car) <= 200 )
        return;
      if ( gta2::S169_sub_404840(NPC) )
      {
        v24 = 0;
        for ( i = self->S110_->Ped_; i; i = v6->Ped_Arr9[v7] )
        {
          gta2::Ped_SetSearchType(i, SEARCHTYPE_AREA);
          gta2::Ped_SetDefault(i);
          v6 = self->S110_->NPC;
          if ( !v6 )
            break;
          v7 = v24++;
        }
        gta2::S169_sub_403BE0(self->S110_->NPC);
        gta2::Car_isMask4(self->S110_->Car);
LABEL_39:
        self->S110_->field_28 = 5;
        self->S110_->field_2C = 1;
        return;
      }
      v23 = 1;
      gta2::Car_sub_4222F0(self->S110_->Car);
      v8 = self->S110_;
      v9 = 0;
      v10 = v8->NPC;
      v11 = v10->Ped_Arr9[0];
      if ( !v11 )
        goto LABEL_16;
      do
      {
        if ( v11->GameObject2 && gta2::Ped_GetSub_4039F0(v11) < 0xAu )
          v23 = 0;
        v11 = v10->Ped_Arr9[(unsigned __int8)++v9];
      }
      while ( v11 );
      if ( v23 )
      {
LABEL_16:
        gta2::Ped_SetDefault(v8->Ped_);
        gta2::Car_isMask4(self->S110_->Car);
        v12 = 0;
        for ( j = self->S110_->NPC->Ped_Arr9[0]; j; j = self->S110_->NPC->Ped_Arr9[v12] )
        {
          if ( j->GameObject2 )
          {
            gta2::Ped_SetDefault(j);
            gta2::Ped_sub_43E650(j);
          }
          ++v12;
        }
        gta2::S169_sub_403BE0(self->S110_->NPC);
LABEL_21:
        self->S110_->field_28 = 5;
        self->S110_->field_2C = 1;
      }
    }
    else
    {
      Car = S110->Car;
      if ( gta2::Car_sub_4A9AD0(S110->Car) > 80 )
      {
        gta2::Car_isMask4(Car);
        self->S110_->field_28 = 5;
        self->S110_->field_2C = 1;
      }
    }
  }
  else
  {
    v15 = self->S110_;
    v16 = v15->NPC;
    if ( v16 )
    {
      if ( gta2::S169_sub_403C40(v16) )
      {
        v17 = self->S110_;
        v18 = v17->Car;
        if ( gta2::Car_sub_4A9AD0(v17->Car) > 200 || v18->SearchType == SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY )
        {
          Ped = v17->Ped_;
          for ( k = 0; Ped; Ped = v20->Ped_Arr9[k++] )
          {
            gta2::Ped_SetDefault(Ped);
            gta2::Ped_sub_43E650(Ped);
            v20 = self->S110_->NPC;
            if ( !v20 )
              break;
          }
          gta2::S169_sub_403BE0(self->S110_->NPC);
          v21 = self->S110_;
          if ( v21->Car->SearchType != SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY )
            gta2::Car_isMask4(v21->Car);
          goto LABEL_21;
        }
      }
    }
    else
    {
      v22 = v15->Car;
      if ( (gta2::Car_sub_4A9AD0(v15->Car) > 200 || v22->SearchType == SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY)
        && v15->Ped_->? > 0x1Eu )
      {
        if ( v22->SearchType != SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY )
          gta2::Car_isMask4(v22);
        gta2::Ped_sub_43E650(self->S110_->Ped_);
        goto LABEL_39;
      }
    }
  }
}


// 0x004ab8c0: S112::sub_4AB8C0
// IDA: S112::sub_4AB8C0
// Ghidra: ---
void gta2::S112_sub_4AB8C0(struct S112 *self)
{
  struct S110 *S110; // eax
  struct S169 *NPC; // ecx
  struct Ped *i; // esi
  struct S169 *v5; // eax
  int v6; // edx
  struct Ped *Ped; // esi
  char Count; // al
  int v10; // eax
  unsigned __int8 v11; // [esp+0h] [ebp-4h]

  if ( self->S110_->field_24 == 2 )
  {
    if ( self->field_29 )
    {
      Count = gPolice->Count;
      if ( Count )
        gPolice->Count = Count - 1;
      self->field_29 = 0;
    }
    if ( self->State != 6 )
    {
      gta2::S112_sub_4A9930(self);
      self->State = 6;
      return;
    }
  }
  else if ( self->State != 6 )
  {
    return;
  }
  v10 = self->S110_->field_24;
  if ( v10 )
  {
    if ( v10 == 2 )
      gta2::S112_sub_4AB400(self);
    else
      gta2::S112_sub_4AB610(self);
  }
  else
  {
    S110 = self->S110_;
    self->State = 2;
    NPC = S110->NPC;
    if ( NPC )
    {
      if ( gta2::S169_sub_403C40(NPC) )
      {
        v11 = 0;
        for ( i = self->S110_->Ped_; i; i = v5->Ped_Arr9[v6] )
        {
          gta2::Ped_SetDefault(i);
          gta2::Ped_sub_43E650(i);
          v5 = self->S110_->NPC;
          if ( !v5 )
            break;
          v6 = v11++;
        }
        gta2::S169_sub_403BE0(self->S110_->NPC);
        self->S110_->field_28 = 5;
        self->S110_->field_2C = 1;
      }
    }
    else
    {
      Ped = S110->Ped_;
      if ( Ped )
      {
        if ( gta2::Ped_GetSub_4039F0(S110->Ped_) >= 0x1Eu )
        {
          gta2::Ped_sub_43E650(Ped);
          self->S110_->field_28 = 5;
          self->S110_->field_2C = 1;
        }
      }
      else
      {
        S110->field_28 = 5;
        self->S110_->field_2C = 1;
      }
    }
  }
}


// 0x004ab930: S112::sub_4AB930
// IDA: S112::sub_4AB930
// Ghidra: ---
bool gta2::S112_sub_4AB930(struct S112 *self)
{
  struct S113 *S113; // esi
  struct Ped *v2; // esi
  void *v3; // ecx
  int Y; // [esp+4h] [ebp-14h] BYREF
  char v6[4]; // [esp+8h] [ebp-10h] BYREF
  char v7[4]; // [esp+Ch] [ebp-Ch] BYREF
  char v8[4]; // [esp+10h] [ebp-8h] BYREF
  char v9[4]; // [esp+14h] [ebp-4h] BYREF

  S113 = self->S113_;
  if ( !S113->Ped_ || self->field_34 || !LOWORD(S113->field_C) )
    return 0;
  if ( self->S110_->field_24 )
    return 1;
  gta2::Ped_GetYCoordinate(S113->Ped_, &Y);
  gta2::Ped_GetXCoordinate(S113->Ped_, (int)v6);
  v2 = unk_66B794;
  gta2::Ped_GetYCoordinate(unk_66B794, (int *)v7);
  gta2::Ped_GetXCoordinate(v2, (int)v8);
  Y = (int)gta2::sub_42A6B0(v3, v9)->Car;
  return gta2::sub_4037E0(&Y);
}


// 0x004ab9d0: S112::sub_4AB9D0
// IDA: S112::sub_4AB9D0
// Ghidra: ---
void gta2::S112_sub_4AB9D0(struct S112 *self)
{
  struct S110 *S110; // edi
  struct Ped *v2; // esi
  char _450CB0; // al
  struct Ped *v4; // ecx

  S110 = self->S110_;
  if ( S110->field_24 )
  {
    v2 = unk_66B794;
    _450CB0 = gta2::Ped_Get_450CB0(unk_66B794);
    v4 = v2;
    if ( !_450CB0 )
    {
      if ( gta2::Ped_Get_450CB0(v2) != 2 )
      {
        gta2::Car_sub_421540(S110->Car);
        return;
      }
      v4 = v2;
    }
  }
  else
  {
    v4 = unk_66B794;
  }
  gta2::Ped_SetAnimationState(v4, 0, 9999);
  gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
}


// 0x004aba30: S112::sub_4ABA30
// IDA: S112::sub_4ABA30
// Ghidra: ---
void gta2::S112_sub_4ABA30(struct S112 *self)
{
  struct Ped *v1; // esi
  char _450CB0; // al
  struct Ped *v3; // ecx

  if ( self->S110_->field_24 )
  {
    v1 = unk_66B794;
    _450CB0 = gta2::Ped_Get_450CB0(unk_66B794);
    v3 = v1;
    if ( !_450CB0 )
    {
      if ( gta2::Ped_Get_450CB0(v1) != 2 )
        return;
      v3 = v1;
    }
  }
  else
  {
    v3 = unk_66B794;
  }
  gta2::Ped_SetAnimationState(v3, 0, 9999);
  gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
}


// 0x004aba90: S112::sub_4ABA90
// IDA: S112::sub_4ABA90
// Ghidra: DecalInfo::FUN_004aba90
void gta2::S112_sub_4ABA90(DecalInfo *self)
{
  char cVar1;
  
  cVar1 = gta2::Ped_Get_450CB0(gPed);
  if (cVar1 != '\0') {
    self->s110->field19_0x28 = 6;
    gta2::Ped_SetAnimationState(gPed,0,9999);
    gta2::Ped_PedSetObjective(gPed,0,9999);
  }
  DAT_0066b79c = 1;
  return;
}


// 0x004ac080: S112::sub_4AC080
// IDA: S112::sub_4AC080
// Ghidra: ---
void gta2::S112_sub_4AC080(struct S112 *self)
{
  char v2; // bl
  struct S110 *S110; // eax
  int v4; // ecx
  int v5; // eax
  struct Car *Car; // eax
  struct Ped *pPed; // edi
  unsigned __int8 v8; // al
  unsigned __int8 v9; // al
  unsigned __int8 v10; // al
  struct S113 *S113; // edi
  struct Ped *v12; // ebx
  int v13; // eax
  int v14; // eax
  struct S113 *v15; // edx
  struct Ped *v16; // edi
  struct S169 *NPC; // eax
  unsigned __int8 v18; // [esp+8h] [ebp-28h]
  unsigned __int8 a2[4]; // [esp+Ch] [ebp-24h] BYREF
  unsigned __int8 v20[4]; // [esp+10h] [ebp-20h] BYREF
  unsigned __int8 v21[4]; // [esp+14h] [ebp-1Ch] BYREF
  int v22; // [esp+18h] [ebp-18h] BYREF
  struct Ped *v23; // [esp+1Ch] [ebp-14h] BYREF
  int v24; // [esp+20h] [ebp-10h] BYREF
  int v25; // [esp+24h] [ebp-Ch] BYREF
  struct Ped *v26; // [esp+28h] [ebp-8h] BYREF
  int v27; // [esp+2Ch] [ebp-4h] BYREF

  v2 = 1;
  unk_66B79C = 1;
  v18 = 0;
  S110 = self->S110_;
  v4 = S110->field_28;
  if ( v4 == 3 )
  {
    if ( S110->field_2C )
    {
      if ( gCharacter->field_5 < 0x1Au )
      {
        v5 = S110->field_20 - 3;
        if ( v5 )
        {
          if ( v5 == 2 )
          {
            gta2::S112_sub_4AB060(self);
            unk_66B794 = self->S110_->Ped_;
            self->field_1A = 0;
            goto LABEL_15;
          }
        }
        else
        {
          gta2::S112_sub_4AADD0(self);
        }
        unk_66B794 = self->S110_->Ped_;
        self->field_1A = 0;
        goto LABEL_15;
      }
      Car = S110->Car;
      if ( !Car )
        goto LABEL_15;
      gta2::Car_isMask4(Car);
      self->S110_->Car = 0;
    }
    else
    {
      v2 = 0;
      if ( S110->field_18 != -80 )
        goto LABEL_15;
    }
    self->State = 6;
    gta2::S112_sub_4A9930(self);
    goto LABEL_15;
  }
  if ( v4 == 6 )
    gta2::S112_sub_4AB8C0(self);
LABEL_15:
  if ( self->State != 6 && v2 )
  {
    pPed = self->S110_->Ped_;
    unk_66B794 = pPed;
    if ( LOWORD(self->S113_->field_C) == 250 )
    {
      self->State = 5;
    }
    else
    {
      for ( ; pPed; ++v18 )
      {
        if ( pPed->field_214 != PEDSTATE_DEAD && pPed->field_228 == 1 )
        {
          switch ( gta2::Ped_GetState(pPed) )
          {
            case 0:
              if ( gta2::Ped_sub_472FD0(pPed) )
              {
                if ( !pPed->field_10B )
                  goto LABEL_32;
                gta2::Ped_SetAnimationState(pPed, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 36, 9999);
                gta2::Ped_SetCurrentCar(unk_66B794, self->S110_->Car);
              }
              break;
            case 12:
              self->field_28 = 0;
              v16 = unk_66B794;
              if ( gta2::Ped_Get_450CB0(unk_66B794) == 1 )
              {
                gta2::Ped_SetAnimationState(v16, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 51, 200);
              }
              break;
            case 14:
              gta2::S112_sub_4ABA90(self);
              S113 = self->S113_;
              v12 = unk_66B794;
              LOWORD(v13) = gta2::Car_sub_403820((struct Car *)&unk_66B794->Weapon2, &S113->field_10);
              if ( v13 || (LOWORD(v14) = gta2::Car_sub_403820((struct Car *)&v12->Gang_, &S113->field_14), v14) )
              {
                a2[0] = gta2::Weapon_sub_41C1E0((struct Weapon *)&S113->field_10);
                v20[0] = gta2::Weapon_sub_41C1E0((struct Weapon *)&S113->field_14);
                v21[0] = gta2::Weapon_sub_41C1E0((struct Weapon *)&S113->field_18);
                if ( gta2::S95_sub_49D7A0(gS95, 1, a2, v20, v21, 0) )
                {
                  gta2::S202_sub_40CE30((struct S202 *)&v25, a2[0]);
                  unk_66B794->Weapon2 = v25;
                  *(_DWORD *)&self->S113_->field_10 = unk_66B794->Weapon2;
                  gta2::S202_sub_40CE30((struct S202 *)&v26, v20[0]);
                  unk_66B794->Gang_ = v26;
                  *(_DWORD *)&self->S113_->field_14 = unk_66B794->Gang_;
                  gta2::S202_sub_40CE30((struct S202 *)&v27, v21[0]);
                  unk_66B794->DriverPed = v27;
                  *(_DWORD *)&self->S113_->field_18 = unk_66B794->DriverPed;
                }
              }
              self->field_28 = 1;
              break;
            case 20:
LABEL_32:
              gta2::Ped_SetAnimationState(pPed, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 12, 9999);
              unk_66B794->Weapon2 = *(_DWORD *)&self->S113_->field_10;
              unk_66B794->Gang_ = *(Ped **)&self->S113_->field_14;
              unk_66B794->DriverPed = *(_DWORD *)&self->S113_->field_18;
              break;
            case 28:
              if ( gta2::Ped_Get_450CB0(pPed) )
                goto LABEL_40;
              break;
            case 32:
LABEL_40:
              gta2::Ped_SetAnimationState(pPed, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
              break;
            case 35:
              gta2::S112_sub_4AB9D0(self);
              break;
            case 36:
              gta2::S112_sub_4ABA30(self);
              break;
            case 51:
              if ( gta2::Ped_Get_450CB0(pPed) == 2 )
              {
                v15 = self->S113_;
                self->State = 6;
                v15->field_1C = 1;
              }
              break;
            case 52:
              gta2::Ped_PedSetObjective(pPed, 14, 9999);
              v8 = gta2::Weapon_sub_41C1E0((struct Weapon *)&self->S113_->field_10);
              gta2::S202_sub_40CE30((struct S202 *)&v22, v8);
              unk_66B794->Weapon2 = v22;
              v9 = gta2::Weapon_sub_41C1E0((struct Weapon *)&self->S113_->field_14);
              gta2::S202_sub_40CE30((struct S202 *)&v23, v9);
              unk_66B794->Gang_ = v23;
              v10 = gta2::Weapon_sub_41C1E0((struct Weapon *)&self->S113_->field_18);
              gta2::S202_sub_40CE30((struct S202 *)&v24, v10);
              unk_66B794->DriverPed = v24;
              break;
            default:
              break;
          }
        }
        NPC = self->S110_->NPC;
        if ( NPC )
          pPed = NPC->Ped_Arr9[v18];
        else
          pPed = 0;
        unk_66B794 = pPed;
      }
    }
  }
}


// 0x004ac580: S112::sub_4AC580
// IDA: S112::sub_4AC580
// Ghidra: ---
void gta2::S112_sub_4AC580(struct S112 *self)
{
  char v2; // bl
  struct S110 *S110; // eax
  int v4; // ecx
  int v5; // eax
  struct Car *Car; // eax
  struct Ped *Ped; // edi
  struct S113 *S113; // edi
  struct S113 *v9; // edi
  _DWORD *v10; // eax
  struct S113 *v11; // edi
  struct S113 *v12; // ebp
  struct S113 *v13; // edi
  _DWORD *v14; // eax
  struct S113 *v15; // edi
  struct S110 *v16; // eax
  struct S169 *v17; // eax
  struct S110 *v18; // eax
  struct S169 *v19; // eax
  struct Ped *v20; // ecx
  struct S110 *v21; // eax
  struct S169 *NPC; // eax
  struct Ped *LinkedPed; // ebp
  struct Ped *Passenger; // eax
  struct S113 *v25; // ecx
  struct S113 *v26; // ebp
  void *v27; // ecx
  int *v28; // edi
  struct Car *CurrentCar; // ecx
  struct SpriteS1 *v30; // eax
  char v31; // al
  struct Ped *v32; // edi
  struct Ped *pPed; // edi
  struct S169 *v34; // ecx
  struct SpriteS1 *v35; // eax
  int v36; // eax
  struct S169 *v37; // eax
  char v38; // [esp+Bh] [ebp-25h]
  unsigned __int8 v39; // [esp+Ch] [ebp-24h]
  char v40[4]; // [esp+10h] [ebp-20h] BYREF
  char v41[4]; // [esp+14h] [ebp-1Ch] BYREF
  char v42[4]; // [esp+18h] [ebp-18h] BYREF
  char v43[4]; // [esp+1Ch] [ebp-14h] BYREF
  char v44[4]; // [esp+20h] [ebp-10h] BYREF
  int v45; // [esp+24h] [ebp-Ch] BYREF
  char v46[4]; // [esp+28h] [ebp-8h] BYREF
  char v47[4]; // [esp+2Ch] [ebp-4h] BYREF

  v2 = 1;
  v38 = 0;
  v39 = 0;
  if ( !self->S113_->Ped_ )
  {
    self->State = 6;
    gta2::S112_sub_4A9930(self);
    return;
  }
  S110 = self->S110_;
  v4 = S110->field_28;
  if ( v4 == 3 )
  {
    if ( S110->field_2C )
    {
      if ( gCharacter->field_5 < 0x1Au )
      {
        v5 = S110->field_20 - 3;
        if ( v5 )
        {
          if ( v5 == 2 )
            gta2::S112_sub_4AB060(self);
        }
        else
        {
          gta2::S112_sub_4AADD0(self);
        }
        unk_66B794 = self->S110_->Ped_;
        self->field_1A = 0;
        goto LABEL_19;
      }
      Car = S110->Car;
      if ( !Car )
        goto LABEL_19;
      gta2::Car_isMask4(Car);
      self->S110_->Car = 0;
    }
    else
    {
      v2 = 0;
      if ( S110->field_18 != -80 )
        goto LABEL_19;
    }
    self->State = 6;
    gta2::S112_sub_4A9930(self);
    goto LABEL_19;
  }
  if ( v4 == 6 )
  {
    gta2::S112_sub_4AB8C0(self);
    if ( self->S110_->field_28 == 5 || self->State == 6 )
    {
      self->State = 6;
      gta2::S112_sub_4A9930(self);
      return;
    }
    goto LABEL_20;
  }
LABEL_19:
  if ( self->State == 6 )
    return;
LABEL_20:
  if ( !v2 )
    return;
  Ped = self->S110_->Ped_;
  unk_66B794 = Ped;
  if ( gta2::S112_sub_4AB930(self) )
  {
    S113 = self->S113_;
    *(_DWORD *)&S113->field_10 = *(_DWORD *)gta2::Ped_GetXCoordinate(S113->Ped_, (int)v40);
    v9 = self->S113_;
    gta2::Ped_GetYCoordinate(v9->Ped_, (int *)v40);
    *(_DWORD *)&v9->field_14 = *v10;
    v11 = self->S113_;
    *(_DWORD *)&v11->field_18 = *(_DWORD *)gta2::Ped_GetPositionZ(v11->Ped_, (int)v40);
    goto LABEL_27;
  }
  v12 = self->S113_;
  if ( !LOWORD(v12->field_C) )
  {
    if ( self->S110_->field_24 )
    {
      self->State = 3;
      return;
    }
LABEL_108:
    self->State = 6;
    gta2::S112_sub_4A9930(self);
    return;
  }
  if ( !self->S110_->field_24 )
    goto LABEL_108;
  if ( !v12->Ped_->field_10B )
    goto LABEL_28;
  *(_DWORD *)&v12->field_10 = *(_DWORD *)gta2::Ped_GetXCoordinate(v12->Ped_, (int)v40);
  v13 = self->S113_;
  gta2::Ped_GetYCoordinate(v13->Ped_, (int *)v40);
  *(_DWORD *)&v13->field_14 = *v14;
  v15 = self->S113_;
  *(_DWORD *)&v15->field_18 = *(_DWORD *)gta2::Ped_GetPositionZ(v15->Ped_, (int)v40);
LABEL_27:
  Ped = unk_66B794;
LABEL_28:
  if ( !LOWORD(self->S113_->field_C) )
  {
    gta2::Ped_SetAnimationState(Ped, 0, 9999);
    gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
    goto LABEL_108;
  }
  for ( ; Ped; ++v39 )
  {
    if ( Ped->field_214 != PEDSTATE_DEAD && Ped->field_228 == 1 )
    {
      switch ( gta2::Ped_GetState(Ped) )
      {
        case 0:
          v21 = self->S110_;
          if ( Ped == v21->Ped_ )
          {
            if ( Ped->field_10B )
            {
              if ( self->S113_->Ped_->field_10B )
              {
                NPC = v21->NPC;
                if ( !NPC )
                  goto LABEL_52;
                if ( gta2::S169_sub_4048A0(NPC) )
                {
                  Ped = unk_66B794;
LABEL_52:
                  gta2::Ped_SetAnimationState(Ped, 0, 9999);
                  goto LABEL_98;
                }
              }
              else
              {
                gta2::Ped_SetAnimationState(Ped, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 36, 9999);
                gta2::Ped_SetCurrentCar(unk_66B794, self->S110_->Car);
                self->field_28 = 0;
              }
            }
            else if ( self->field_28 && v21->field_24 == 1 )
            {
              if ( (Ped->PositionX1 & 0x8000000) == 0 )
              {
                gta2::Ped_SetAnimationState(Ped, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 35, 9999);
                gta2::Ped_SetCurrentCar(unk_66B794, self->S110_->Car);
                gta2::Ped_sub_403960(unk_66B794);
              }
            }
            else if ( (Ped->PositionX1 & 0x8000000) == 0 )
            {
              gta2::Ped_SetAnimationState(Ped, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 20, 9999);
              gta2::Ped_SetDriverPed(unk_66B794, self->S113_->Ped_);
              gta2::Ped_sub_403960(unk_66B794);
              self->field_28 = 0;
              self->field_35 = 0;
            }
          }
          else if ( gta2::Ped_GetLinkedPed(Ped) == (struct Ped *)self->field_30 && gta2::Ped_GetLinkedPed(Ped) )
          {
            gta2::Ped_SetPed2(Ped, self->S113_->Ped_);
          }
          break;
        case 2:
          unk_66B79C = 0;
          gta2::S112_sub_4A97C0(self);
          break;
        case 12:
        case 51:
          goto LABEL_71;
        case 14:
          v16 = self->S110_;
          if ( Ped != v16->Ped_ )
            goto LABEL_40;
          v17 = v16->NPC;
          if ( v17 )
          {
            if ( !gta2::S169_sub_404840(v17) )
            {
              gta2::Ped_SetAnimationState(unk_66B794, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
              self->field_28 = 1;
              break;
            }
            gta2::Ped_SetAnimationState(unk_66B794, 0, 9999);
            gta2::Ped_PedSetObjective(unk_66B794, 52, 9999);
            gta2::Ped_SetDriverPed(unk_66B794, self->S113_->Ped_);
          }
          else
          {
            gta2::Ped_SetAnimationState(Ped, 0, 9999);
            gta2::Ped_PedSetObjective(unk_66B794, 52, 9999);
            gta2::Ped_SetDriverPed(unk_66B794, self->S113_->Ped_);
          }
          self->field_28 = 1;
LABEL_40:
          self->field_28 = 1;
          break;
        case 20:
        case 32:
          LinkedPed = gta2::Ped_GetLinkedPed(Ped);
          if ( gta2::Ped_GetDriver(Ped) == LinkedPed )
          {
            Passenger = gta2::Ped_GetDriver(Ped);
            v25 = self->S113_;
            self->field_30 = (int)Passenger;
            gta2::Ped_SetPed2(unk_66B794, v25->Ped_);
            Ped = unk_66B794;
          }
          gta2::Ped_SetDriverPed(Ped, self->S113_->Ped_);
          Ped = unk_66B794;
          if ( gta2::Ped_Get_450CB0(unk_66B794) == 1 )
          {
            unk_66B79C = 0;
            break;
          }
          if ( gta2::Ped_Get_450CB0(Ped) == 2 )
          {
LABEL_71:
            v20 = Ped;
            goto LABEL_72;
          }
          v26 = self->S113_;
          if ( v26->Ped_ )
          {
            gta2::Ped_GetYCoordinate(v26->Ped_, (int *)v40);
            gta2::Ped_GetXCoordinate(v26->Ped_, (int)v41);
            gta2::Ped_GetYCoordinate(Ped, (int *)v42);
            gta2::Ped_GetXCoordinate(Ped, (int)v43);
            v28 = &self->field_8;
            self->field_8 = (int)gta2::sub_42A6B0(v27, v44)->Car;
          }
          else
          {
            v28 = &self->field_8;
            self->field_8 = (int)gta2::Radar_AddBlip((struct Tango *)&unk_66BB2C, (struct SpriteS1 *)&v45, &unk_66BAB0)->FirstElement;
          }
          if ( self->S110_->field_24 != 1 )
            goto LABEL_87;
          if ( gta2::Car_sub_403800((struct Car *)v28, (int)&unk_66BB2C) )
            goto LABEL_81;
          CurrentCar = v26->Ped_->field_10B;
          if ( !CurrentCar )
            goto LABEL_87;
          v30 = gta2::Car_sub_421D90(CurrentCar, (struct SpriteS1 *)v46);
          if ( gta2::Car_sub_403800((struct Car *)v30, (int)&unk_66B7BC) )
          {
            v31 = self->field_35 + 1;
            self->field_35 = v31;
            if ( (unsigned __int8)v31 > 0x1Eu )
              goto LABEL_81;
          }
          else
          {
            if ( gta2::Car_sub_403800((struct Car *)v28, (int)&unk_66B840) )
            {
LABEL_81:
              v32 = unk_66B794;
              if ( (gta2::Ped_GetState(unk_66B794) != 32 || gta2::Ped_GetPedState(v32) == 1)
                && (v32->PositionX1 & 0x8000000) == 0 )
              {
                gta2::Ped_SetAnimationState(v32, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 35, 9999);
                gta2::Ped_SetCurrentCar(unk_66B794, self->S110_->Car);
                gta2::Ped_sub_403960(unk_66B794);
                self->field_28 = 1;
              }
              break;
            }
            v38 = 1;
          }
LABEL_87:
          pPed = unk_66B794;
          if ( gta2::Ped_GetState(unk_66B794) == 32 )
          {
            if ( self->S113_->Ped_->GameObject2 && (pPed->PositionX1 & 0x8000000) != 0 )
            {
              gta2::Ped_SetAnimationState(pPed, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 20, 9999);
              gta2::Ped_SetDriverPed(unk_66B794, self->S113_->Ped_);
              gta2::Ped_sub_403960(unk_66B794);
              self->field_28 = 0;
            }
          }
          else if ( v38 )
          {
            gta2::Ped_PedSetObjective(pPed, 32, 9999);
            gta2::Ped_SetDriverPed(unk_66B794, self->S113_->Ped_);
            gta2::Ped_sub_403960(unk_66B794);
          }
          break;
        case 27:
          v35 = gta2::Car_sub_421D90(self->S110_->Car, (struct SpriteS1 *)v47);
          LOBYTE(v36) = gta2::Player_CheckCondition((struct Player *)v35, &unk_66BA64);
          if ( v36 )
          {
            gta2::Ped_PedSetObjective(unk_66B794, 36, 9999);
            gta2::Ped_SetCurrentCar(unk_66B794, unk_66B794->field_10B);
          }
          break;
        case 28:
          if ( gta2::Ped_Get_450CB0(Ped) )
            goto LABEL_71;
          break;
        case 35:
          gta2::S112_sub_4AB9D0(self);
          self->field_28 = 1;
          break;
        case 36:
          gta2::S112_sub_4ABA30(self);
          self->field_28 = 0;
          break;
        case 43:
          gta2::Ped_SetAnimationState(Ped, 0, 9999);
          v34 = self->S110_->NPC;
          if ( v34 && !gta2::S169_sub_404840(v34) )
          {
            gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
          }
          else
          {
LABEL_98:
            gta2::Ped_PedSetObjective(unk_66B794, 52, 9999);
            gta2::Ped_SetDriverPed(unk_66B794, self->S113_->Ped_);
            self->field_28 = 1;
          }
          break;
        case 52:
          v18 = self->S110_;
          self->field_28 = 1;
          if ( v18->Car && ((v19 = v18->NPC) == 0 || gta2::S169_sub_4048A0(v19)) )
          {
            gta2::sub_4ABAE0((int)self);
            self->field_28 = 1;
          }
          else
          {
            v20 = unk_66B794;
LABEL_72:
            gta2::Ped_SetAnimationState(v20, 0, 9999);
            gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
          }
          break;
        default:
          break;
      }
    }
    v37 = self->S110_->NPC;
    if ( v37 )
      Ped = v37->Ped_Arr9[v39];
    else
      Ped = 0;
    unk_66B794 = Ped;
  }
}


// 0x004ace80: S112::sub_4ACE80
// IDA: S112::sub_4ACE80
// Ghidra: ---
void gta2::S112_sub_4ACE80(struct S112 *self)
{
  struct Ped *pPed; // ebx
  struct S110 *S110; // ecx
  struct Model *Model; // eax
  struct S110 *v5; // eax
  int v6; // ecx
  struct S110 *v7; // ebp
  struct EngineStruct *EngineStruct; // eax
  char JuncIdx; // al
  char Count; // al
  struct Ped *Ped; // ecx
  struct S113 *S113; // esi
  void *v13; // esi
  struct S113 *v14; // esi
  struct S113 *v15; // esi
  _DWORD *v16; // eax
  struct S113 *v17; // esi
  struct Ped *pPed_1; // esi
  struct S110 *v19; // eax
  struct S169 *NPC; // eax
  struct S169 *v21; // eax
  struct Car *Car; // eax
  struct EngineStruct *v23; // eax
  char v24; // al
  char v25; // al
  struct S112 *v26; // ecx
  int X; // [esp+10h] [ebp-4h] BYREF

  unk_66B79C = 1;
  LOBYTE(X) = 0;
  pPed = self->S110_->Ped_;
  unk_66B794 = pPed;
  S110 = self->S110_;
  if ( S110->Car )
  {
    Model = S110->Car->Model_;
    if ( Model )
    {
      gta2::S121_ReleaseModel(gS121, Model);
      self->S110_->Car->Model_ = 0;
    }
    if ( gta2::Car_IsEmergencyOrFbiCar(self->S110_->Car) )
      gta2::Car_sub_422D80(self->S110_->Car);
    pPed = unk_66B794;
  }
  v5 = self->S110_;
  v6 = v5->field_28;
  if ( v6 != 3 )
  {
    if ( v6 == 6 )
    {
      gta2::S112_sub_4AB8C0(self);
      pPed = unk_66B794;
    }
    v7 = self->S110_;
    if ( v7->field_28 == 5 )
    {
      if ( v7->Car )
      {
        EngineStruct = v7->Car->EngineStruct_;
        if ( EngineStruct )
        {
          JuncIdx = EngineStruct->JuncIdx;
          if ( JuncIdx > 0 )
          {
            gta2::JuncIds_ClearJunctionId(gJuncIds, JuncIdx);
            self->S110_->Car->EngineStruct_->JuncIdx = -1;
          }
        }
      }
      gta2::S112_sub_4A9930(self);
      if ( self->field_29 )
      {
        Count = gPolice->Count;
        if ( Count )
          gPolice->Count = Count - 1;
        self->field_29 = 0;
      }
      Ped = self->S110_->Ped_;
      if ( Ped )
        gta2::Ped_sub_43EC30(Ped);
      self->S110_->field_28 = 0;
      gta2::S110_sub_4C5480_2(self->S110_);
      gta2::S112_Defaut(self);
      return;
    }
    S113 = self->S113_;
    if ( S113 )
    {
      if ( v7->field_24 == 2 )
        return;
      if ( S113->Ped_ )
      {
        if ( gta2::S112_sub_4AB930(self) )
        {
          if ( v7->field_20 == 6 || (v13 = S113->field_4, v13 != (void *)6) && v13 )
          {
            if ( gta2::Ped_GetState(pPed) == 35 && (pPed->PositionX1 & 0x8000000) == 0 )
            {
              gta2::Ped_SetAnimationState(pPed, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
            }
            v14 = self->S113_;
            *(_DWORD *)&v14->field_10 = *(_DWORD *)gta2::Ped_GetXCoordinate(v14->Ped_, (int)&X);
            v15 = self->S113_;
            gta2::Ped_GetYCoordinate(v15->Ped_, &X);
            *(_DWORD *)&v15->field_14 = *v16;
            v17 = self->S113_;
            *(_DWORD *)&v17->field_18 = *(_DWORD *)gta2::Ped_GetPositionZ(v17->Ped_, (int)&X);
            gta2::Police(gPolice, self, (int)self->S113_);
            return;
          }
        }
      }
    }
    if ( v7->field_24 == 2 )
      return;
    if ( !pPed )
      return;
    gta2::Ped_sub_403A40(pPed);
    pPed_1 = unk_66B794;
    if ( !unk_66B794 )
      return;
    while ( 1 )
    {
      if ( pPed_1->field_214 != PEDSTATE_DEAD && pPed_1->field_228 == 1 )
      {
        switch ( gta2::Ped_GetState(pPed_1) )
        {
          case 0:
            v19 = self->S110_;
            if ( pPed_1 != v19->Ped_ )
              break;
            if ( !pPed_1->field_10B )
            {
              if ( v19->field_24 == 1 && (pPed_1->PositionX1 & 0x8000000) == 0 )
              {
                gta2::Ped_SetAnimationState(pPed_1, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 35, 9999);
                gta2::Ped_SetCurrentCar(unk_66B794, self->S110_->Car);
                gta2::Ped_sub_403960(unk_66B794);
              }
              break;
            }
            NPC = v19->NPC;
            if ( !NPC )
              goto LABEL_45;
            if ( gta2::S169_sub_404840(NPC) )
            {
              pPed_1 = unk_66B794;
LABEL_45:
              gta2::Ped_SetAnimationState(pPed_1, 0, 9999);
              gta2::Ped_PedSetObjective(unk_66B794, 43, 9999);
              gta2::Car_CarMakeDummy(unk_66B794->field_10B);
              gta2::Car_sub_4222D0(unk_66B794->field_10B);
              unk_66B79C = 0;
            }
            break;
          case 8:
          case 27:
          case 34:
          case 43:
          case 50:
            break;
          case 14:
          case 52:
            gta2::Ped_SetAnimationState(pPed_1, 0, 9999);
            gta2::Ped_PedSetObjective(unk_66B794, 43, 9999);
            unk_66B79C = 0;
            break;
          case 28:
            if ( gta2::Ped_Get_450CB0(pPed_1) )
              goto LABEL_52;
            break;
          case 35:
            gta2::S112_sub_4AB9D0(self);
            break;
          case 36:
            gta2::S112_sub_4ABA30(self);
            break;
          default:
LABEL_52:
            gta2::Ped_SetAnimationState(pPed_1, 0, 9999);
            gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
            break;
        }
      }
      v21 = self->S110_->NPC;
      if ( v21 )
        pPed_1 = v21->Ped_Arr9[(unsigned __int8)X];
      else
        pPed_1 = 0;
      unk_66B794 = pPed_1;
      LOBYTE(X) = X + 1;
      if ( !pPed_1 )
        return;
    }
  }
  Car = v5->Car;
  if ( Car )
  {
    v23 = Car->EngineStruct_;
    if ( v23 )
    {
      v24 = v23->JuncIdx;
      if ( v24 > 0 )
      {
        gta2::JuncIds_ClearJunctionId(gJuncIds, v24);
        self->S110_->Car->EngineStruct_->JuncIdx = -1;
      }
    }
  }
  self->S110_->field_28 = 0;
  gta2::S110_sub_4C5480_2(self->S110_);
  if ( self->field_29 )
  {
    v25 = gPolice->Count;
    if ( v25 )
      gPolice->Count = v25 - 1;
  }
  gta2::S112_Defaut(self);
  gta2::S112_sub_4A9930(v26);
}


// 0x004ad310: S112::sub_4AD310
// IDA: S112::sub_4AD310
// Ghidra: ---
char gta2::S112_sub_4AD310(struct S112 *self)
{
  struct S110 *S110; // ecx
  struct S169 *NPC; // eax
  struct Car *Car; // ecx
  struct S110 *v5; // ebp
  struct EngineStruct *EngineStruct; // eax
  char JuncIdx; // al
  char Count; // al
  struct S113 *S113; // esi
  struct S113 *v10; // esi
  _DWORD *v11; // eax
  struct S113 *v12; // esi
  struct Ped *pPed2; // esi
  struct S110 *v14; // edx
  int X; // [esp+10h] [ebp-4h] BYREF

  unk_66B79C = 1;
  LOBYTE(X) = 0;
  S110 = self->S110_;
  NPC = (struct S169 *)S110->field_24;
  if ( NPC == (struct S169 *)2 || !NPC || (Car = S110->Car, Car->field_76 > 80) )
  {
    self->State = 6;
  }
  else
  {
    gta2::Car_sub_421550(Car);
    if ( self->S110_->field_28 == 6 )
      gta2::S112_sub_4AB8C0(self);
    v5 = self->S110_;
    if ( v5->field_28 == 5 )
    {
      if ( v5->Car )
      {
        EngineStruct = v5->Car->EngineStruct_;
        if ( EngineStruct )
        {
          JuncIdx = EngineStruct->JuncIdx;
          if ( JuncIdx > 0 )
          {
            gta2::JuncIds_ClearJunctionId(gJuncIds, JuncIdx);
            self->S110_->Car->EngineStruct_->JuncIdx = -1;
          }
        }
      }
      gta2::S112_sub_4A9930(self);
      if ( self->field_29 )
      {
        Count = gPolice->Count;
        if ( Count )
          gPolice->Count = Count - 1;
      }
      self->S110_->field_28 = 0;
      gta2::S110_sub_4C5480_2(self->S110_);
      LOBYTE(NPC) = gta2::S112_Defaut(self);
    }
    else
    {
      S113 = self->S113_;
      if ( S113 && S113->Ped_ && gta2::S112_sub_4AB930(self) && (v5->field_20 == 6 || S113->field_4 != (void *)6) )
      {
        *(_DWORD *)&S113->field_10 = *(_DWORD *)gta2::Ped_GetXCoordinate(S113->Ped_, (int)&X);
        v10 = self->S113_;
        gta2::Ped_GetYCoordinate(v10->Ped_, &X);
        *(_DWORD *)&v10->field_14 = *v11;
        v12 = self->S113_;
        *(_DWORD *)&v12->field_18 = *(_DWORD *)gta2::Ped_GetPositionZ(v12->Ped_, (int)&X);
        LOBYTE(NPC) = gta2::Police(gPolice, self, (int)self->S113_);
      }
      else
      {
        unk_66B794 = v5->Ped_;
        gta2::Ped_sub_403A40(unk_66B794);
        for ( pPed2 = unk_66B794; pPed2; LOBYTE(X) = X + 1 )
        {
          switch ( gta2::Ped_GetState(pPed2) )
          {
            case 0:
              if ( pPed2 == self->S110_->Ped_ )
              {
                if ( pPed2->field_10B )
                {
                  unk_66B79C = 0;
                }
                else if ( (pPed2->PositionX1 & 0x8000000) == 0 )
                {
                  gta2::Ped_SetAnimationState(pPed2, 0, 9999);
                  gta2::Ped_PedSetObjective(unk_66B794, 35, 9999);
                  gta2::Ped_SetCurrentCar(unk_66B794, self->S110_->Car);
                  gta2::Ped_sub_403960(unk_66B794);
                }
              }
              break;
            case 2:
            case 12:
            case 20:
              goto LABEL_33;
            case 14:
            case 52:
              unk_66B79C = 0;
              v14 = self->S110_;
              if ( v14->Car->Model_ )
              {
                gta2::S121_ReleaseModel(gS121, v14->Car->Model_);
                self->S110_->Car->Model_ = 0;
              }
              break;
            case 28:
              if ( gta2::Ped_Get_450CB0(pPed2) )
              {
LABEL_33:
                gta2::Ped_SetAnimationState(pPed2, 0, 9999);
                gta2::Ped_PedSetObjective(unk_66B794, 0, 9999);
              }
              break;
            case 35:
              gta2::S112_sub_4AB9D0(self);
              break;
            case 36:
              gta2::S112_sub_4ABA30(self);
              break;
            default:
              break;
          }
          NPC = self->S110_->NPC;
          if ( NPC )
            pPed2 = NPC->Ped_Arr9[(unsigned __int8)X];
          else
            pPed2 = 0;
          unk_66B794 = pPed2;
        }
      }
    }
  }
  return (char)NPC;
}


// 0x004ad600: S112::sub_4AD600
// IDA: S112::sub_4AD600
// Ghidra: ---
void gta2::S112_sub_4AD600(struct S112 *self)
{
  struct S110 *S110; // eax
  struct Ped *Ped; // esi
  struct S169 *pS169; // ecx
  struct Ped *v5; // esi

  S110 = self->S110_;
  if ( S110 )
  {
    Ped = S110->Ped_;
    if ( Ped )
    {
      if ( !Ped->? && gta2::Ped_GetPedState(S110->Ped_) != 9 && gta2::Ped_Get_433B40(Ped) )
        gPolice->field_7B4 = 1;
    }
    else
    {
      pS169 = S110->NPC;
      if ( pS169 )
      {
        v5 = pS169->Ped_Arr9[0];
        if ( v5 )
        {
          gta2::S169_sub_404D40(pS169, pS169->Ped_Arr9[0]);
          gta2::S169_sub_404400(self->S110_->NPC, v5);
          self->S110_->Ped_ = v5;
        }
      }
    }
  }
  switch ( self->State )
  {
    case 1:
      gta2::S112_sub_4AD310(self);
      break;
    case 2:
      unk_66B79C = 1;
      self->State = 6;
      break;
    case 3:
      gta2::S112_sub_4AC080(self);
      break;
    case 5:
      gta2::S112_sub_4AC580(self);
      break;
    case 6:
      gta2::S112_sub_4ACE80(self);
      break;
    default:
      return;
  }
}



