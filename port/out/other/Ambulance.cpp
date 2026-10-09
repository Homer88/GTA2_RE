#include "gta2_shim.h"

// Module: other, Class: Ambulance
// Functions: 7
// Source: unified (IDA+Ghidra)

// 0x00472f20: Ambulance::AddPedToAmbulance
// IDA: Ambulance::AddPedToAmbulance
// Ghidra: ---
char gta2::Ambulance_AddPedToAmbulance(struct Ambulance *self, Ped *a2)
{
  if ( gta2::Ped_IsSearchType(a2, SEARCHTYPE_LINE_OF_SIGHT_PLAYER_ONLY) || self->field_1 >= 0x19u )
    return 0;
  gta2::Passenger_sub_445F10(&self->Passenger_, a2);
  ++self->field_1;
  return 1;
}


// 0x00472f60: Ambulance::sub_472F60
// IDA: Ambulance::sub_472F60
// Ghidra: FUN_00472f60
int gta2::Ambulance_sub_472F60(void *self)
{
  byte bVar1;
  undefined4 local_4;
  
  bVar1 = 0;
  local_4 = 0;
  do {
    if (*(int *)(local_4 * 0x20 + 0xe8 + (int)self) == 0) {
      return local_4 * 0x20 + 0xd0 + (int)self;
    }
    bVar1 = bVar1 + 1;
    local_4 = (uint)bVar1;
  } while (bVar1 < 2);
  return 0;
}


// 0x00472fe0: Ambulance::sub_472FE0
// IDA: Ambulance::sub_472FE0
// Ghidra: ---
char * gta2::Ambulance_sub_472FE0(struct Ambulance *self)
{
  char *result; // eax
  int v3; // ecx

  self->field_0 = 1;
  self->field_1 = 0;
  gta2::Passenger_Passenger(&self->Passenger_);
  result = (char *)&self->Ped1;
  v3 = 25;
  do
  {
    *((_DWORD *)result - 1) = 0;
    *(_DWORD *)result = 0;
    result += 8;
    --v3;
  }
  while ( v3 );
  return result;
}


// 0x00473010: Ambulance::sub_473010
// IDA: Ambulance::sub_473010
// Ghidra: ---
char gta2::Ambulance_sub_473010(struct Ambulance *self, Ped *pPed)
{
  unsigned __int8 v3; // cl
  int v4; // eax
  Medical *v5; // esi
  struct S110 *S110; // eax
  S169 *v7; // eax
  char v9; // bl
  struct S110 *v10; // eax
  S169 *NPC; // ecx
  struct Ped *Ped; // edi
  struct Ped *v13; // edi
  struct Ped *v14; // ecx
  struct Ped *v15; // esi
  unsigned __int8 v16; // [esp+Ch] [ebp-4h]

  v3 = 0;
  v16 = 0;
  while ( 1 )
  {
    v4 = v16;
    v5 = &self->Medical_[v4];
    if ( self->Medical_[v4].field_14 )
    {
      S110 = self->Medical_[v4].S110;
      if ( S110->Ped_ == pPed )
      {
        v9 = gta2::S110_sub_4C5510(v5->S110_);
        v10 = v5->S110_;
        NPC = v10->NPC;
        if ( NPC )
          v10->Ped_ = NPC->Ped_;
        Ped = v5->Ped_;
        if ( Ped && gta2::Ped_GetPedState(v5->Ped_) == 9 )
        {
          gta2::Ambulance_AddPedToAmbulance(self, Ped);
          v5->Ped_ = 0;
        }
        v13 = (Ped *)v5->field_C;
        if ( v13 && gta2::Ped_GetPedState((Ped *)v5->field_C) == 9 )
        {
          gta2::Ambulance_AddPedToAmbulance(self, v13);
          v5->field_C = 0;
        }
        if ( v9 )
          return 1;
        v14 = pPed;
        if ( pPed->GameObject2 )
          goto LABEL_27;
        return 0;
      }
      v7 = S110->NPC;
      if ( v7 )
      {
        if ( v7->Ped_Arr9[0] == pPed )
          break;
      }
    }
    v16 = ++v3;
    if ( v3 >= 2u )
      return 0;
  }
  if ( pPed->field_10B )
    gta2::S110_sub_4C54C0(v5->S110_, pPed);
  v15 = (Ped *)v5->field_C;
  if ( v15 )
  {
    if ( gta2::Ped_GetPedState(v15) == 9 )
      gta2::Ambulance_AddPedToAmbulance(self, v15);
  }
  if ( pPed->GameObject2 )
  {
    v14 = pPed;
LABEL_27:
    gta2::Ped_PedSetObjective(v14, 28, 9999);
  }
  return 0;
}


// 0x00473e00: Ambulance::sub_473E00
// IDA: Ambulance::sub_473E00
// Ghidra: ---
void gta2::Ambulance_sub_473E00(struct Ambulance *self)
{
  Passenger *p_Passenger; // esi
  char v3; // cl
  struct Ped *v4; // ebx
  Weapon *XCoordinate; // eax
  Weapon *v6; // eax
  Weapon *PositionZ; // eax
  int Index; // eax
  Medical *ppMedical_1; // esi
  Medical *ppMedical; // eax
  Medical *pMedical; // edi
  struct S110 *pS110; // esi
  struct S110 *S110; // eax
  unsigned __int8 v14; // dl
  unsigned __int8 v15; // cl
  unsigned __int8 a2[4]; // [esp+8h] [ebp-28h] BYREF
  unsigned __int8 v17[4]; // [esp+Ch] [ebp-24h] BYREF
  unsigned __int8 v18[4]; // [esp+10h] [ebp-20h] BYREF
  unsigned __int8 i; // [esp+14h] [ebp-1Ch]
  int v20; // [esp+18h] [ebp-18h] BYREF
  int v21; // [esp+1Ch] [ebp-14h] BYREF
  int X; // [esp+20h] [ebp-10h] BYREF
  int Y; // [esp+24h] [ebp-Ch] BYREF
  int v24; // [esp+28h] [ebp-8h] BYREF
  _BYTE v25[4]; // [esp+2Ch] [ebp-4h] BYREF

  p_Passenger = &self->Passenger_;
  v3 = self->field_1 - gta2::S195_sub_446060(&self->Passenger_);
  self->field_1 = v3;
  if ( v3 )
  {
    v4 = (Ped *)sub_446100(p_Passenger);
    if ( sub_435430(v4) )
    {
      --self->field_1;
      gta2::Ambulance_AddPedToAmbulance(gAmbulance, v4);
    }
    else
    {
      XCoordinate = (Weapon *)gta2::Ped_GetXCoordinate(v4, (int)&X);
      a2[0] = gta2::Weapon_sub_41C1E0(XCoordinate);
      gta2::Ped_GetYCoordinate(v4, &X);
      v17[0] = gta2::Weapon_sub_41C1E0(v6);
      PositionZ = (Weapon *)gta2::Ped_GetPositionZ(v4, (int)&X);
      v18[0] = gta2::Weapon_sub_41C1E0(PositionZ);
      if ( gta2::S95_sub_49D7A0(gS95, 1, a2, v17, v18, 0) )
      {
        for ( i = 0; i < 2u; ++i )
        {
          Index = i;
          ppMedical_1 = &self->Medical_[Index];
          if ( self->Medical_[Index].field_14 == 1 && gta2::S110_sub_4C54F0(self->Medical_[Index].S110) )
          {
            gta2::S202_sub_40CE30((S202 *)&v20, ppMedical_1->field_1);
            gta2::S202_sub_40CE30((S202 *)&v21, ppMedical_1->field);

            gta2::Ped_GetYCoordinate(v4, &Y);
            gta2::Ped_GetXCoordinate(v4, (int)&v24);

            X = (int)gta2::sub_42A6B0(v25, v25)->Car;
            if ( gta2::sub_4037E0(&X) )
            {
              if ( LOBYTE(ppMedical_1->Passenger_.PassengerPrev) < 0xAu )
              {
                gta2::Medical_sub_472FB0(ppMedical_1, v4);
                --self->field_1;
                S110 = ppMedical_1->S110_;
                if ( S110->field_28 == 5 )
                {
                  v14 = v17[0];
                  ppMedical_1->field = a2[0];
                  v15 = v18[0];
                  ppMedical_1->field_1 = v14;
                  ppMedical_1->field_2 = v15;
                  S110->field_28 = 6;
                }
                return;
              }
            }
          }
        }
        ppMedical = gta2::Ambulance_sub_472F60(self);
        pMedical = ppMedical;
        if ( ppMedical )
        {
          ppMedical->field_14 = 1;
          ppMedical->field = a2[0];
          ppMedical->field_1 = v17[0];
          ppMedical->field_2 = v18[0];
          pS110 = gta2::S109_sub_4C5430(gS109);
          pMedical->S110_ = pS110;
          if ( !pS110 )
          {
            --self->field_1;
            gta2::Ped_PedSetObjective(v4, 50, 9999);
            gta2::Medical_sub_473140(pMedical);
            return;
          }
          pS110->field_1E = 1;
          pS110->field_20 = 1;
          pS110->field_24 = 1;
          pS110->field_28 = 3;
          pS110->field_18 = 300;
          pS110->field_1C = 0;
          gta2::S202_sub_40CE30((S202 *)&X, a2[0]);
          pS110->field_C = X;

          gta2::S202_sub_40CE30((S202 *)&X, v17[0]);
          pS110->field_10 = X;

          gta2::S202_sub_40CE30((S202 *)&X, v18[0]);
          pS110->field_14 = X;

          gta2::Medical_sub_472FB0(pMedical, v4);
        }
        --self->field_1;
      }
      else
      {
        --self->field_1;
        gta2::Ped_PedSetObjective(v4, 50, 9999);
      }
    }
  }
}


// 0x004740b0: Ambulance::sub_4740B0
// IDA: Ambulance::sub_4740B0
// Ghidra: ---
void gta2::Ambulance_sub_4740B0(struct Ambulance *self)
{
  Medical *pMedical; // esi
  int v3; // edi

  if ( self->field_1 )
    gta2::Ambulance_sub_473E00(self);
  pMedical = self->Medical_;
  v3 = 2;
  do
  {
    if ( pMedical->field_14 == 1 )
      gta2::Medical_sub_473CE0(pMedical);
    ++pMedical;
    --v3;
  }
  while ( v3 );
}


// 0x004fa800: Ambulance::sub_4FA800
// IDA: Ambulance::sub_4FA800
// Ghidra: ---
int gta2::Ambulance_sub_4FA800(struct Ambulance *self, Ped *a2)
{
  SpriteS1 *v2; // eax
  SpriteS1 *v3; // eax
  int v5; // [esp+0h] [ebp-10h] BYREF
  int a2a; // [esp+4h] [ebp-Ch] BYREF
  char v7; // [esp+8h] [ebp-8h] BYREF
  char v8; // [esp+Ch] [ebp-4h] BYREF

  v5 = 30;
  gta2::bitShiftLeft1(&a2a, 0);
  v2 = gta2::JustCopyByPtrAtoC(&unk_5E3310, (SpriteS1 *)&v8);
  v3 = gta2::sub_401BD0(v2, (SpriteS1 *)&v7, &v5);
  gta2::S103_sub_401D20((S103 *)&unk_5E34C8, &a2a, v3);
  return gta2::atexit(nullsub_76);
}



