#include "gta2_shim.h"

// Module: other, Class: S31
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x00474e80: S31::sub_474E80
// IDA: S31::sub_474E80
// Ghidra: ---
TrafficManager * gta2::S31_sub_474E80(struct TrafficManager *self)
{
  struct TrafficManager *result; // eax
  int v2; // edx

  result = self;
  v2 = 0;
  while ( result->FirstElement )
  {
    result = (struct TrafficManager *)((char *)result + 12);
    if ( (unsigned __int16)++v2 >= 0x32u )
      return 0;
  }
  return result;
}


// 0x00474ed0: S31::sub_474ED0
// IDA: S31::sub_474ED0
// Ghidra: ---
char gta2::S31_sub_474ED0(struct TrafficManager *self, void *a2)
{
  struct TrafficManager *v2; // eax
  int v3; // ecx
  struct S32 *v4; // edx

  v2 = gta2::TrafficManager_sub_474E80(self);
  if ( v2 )
  {
    v2->FirstElement = (struct S32 *)a2;
    v4 = (struct S32 *)*((_DWORD *)a2 + 5);
    v2->S32_[0].currentData = 2;
    v2->S32_[0].prev_field = v4;
    LOBYTE(v2) = *(_BYTE *)(v3 + 600) + 1;
    *(_BYTE *)(v3 + 600) = (_BYTE)v2;
  }
  return (char)v2;
}


// 0x00476bc0: S31::sub_476BC0
// IDA: S31::sub_476BC0
// Ghidra: ---
int gta2::S31_sub_476BC0(struct TrafficManager *self)
{
  struct TrafficManager *v2; // esi
  struct S169 *S169; // ecx
  struct Car *pCar; // edi
  struct Car *FirstElement; // ecx
  struct S169 *pS169; // ecx
  int v7; // ecx
  struct Car *v8; // edi
  int result; // eax
  int v10; // [esp+10h] [ebp-4h]

  v2 = self;
  S169 = gGame->PlayerMain->MainPed->field_103;
  if ( S169 )
    gta2::S169_ManageGroupPedObjectives(S169);
  if ( unk_6644B0 && unk_6644B0->ID == unk_6644B4 )
  {
    gta2::Player_sub_4A47F0(gGame->PlayerMain, unk_6644B0);
    pCar = unk_6644B0;
    gta2::Car_CarMakeDriveable1(unk_6644B0, SEARCHTYPE_AREA);
    if ( !gta2::Car_GetMask7(pCar) )
      gta2::Car_isMask4(pCar);
    unk_6644B0 = 0;
    unk_6644B4 = 0;
  }
  v10 = 50;
  do
  {
    FirstElement = (struct Car *)v2->FirstElement;
    if ( v2->FirstElement )
    {
      if ( v2->S32_[0].currentData == 1 )
      {
        if ( (struct S32 *)FirstElement->ID == v2->S32_[0].prev_field )
        {
          gta2::Player_sub_4A47F0(gGame->PlayerMain, (struct Car *)v2->FirstElement);
          gta2::Car_CarMakeDriveable1((struct Car *)v2->FirstElement, SEARCHTYPE_AREA);
          v8 = (struct Car *)v2->FirstElement;
          if ( !gta2::Car_GetMask7((struct Car *)v2->FirstElement) )
            gta2::Car_isMask4(v8);
        }
      }
      else if ( v2->S32_[0].currentData == 2 )
      {
        if ( FirstElement->CarDoor_[0].PedInDoor == (struct Ped *)v2->S32_[0].prev_field )
        {
          gta2::S63_sub_483C40((struct EventHandler *)FirstElement);
          gta2::sub_4827C0(&v2->FirstElement->currentData);
        }
      }
      else if ( v2->S32_[0].currentData == 3 && (struct S32 *)FirstElement[2].Mask == v2->S32_[0].prev_field )
      {
        pS169 = *(S169 **)&FirstElement[1].field_A8;
        if ( pS169 )
          gta2::S169_sub_403DA0(pS169);
        gta2::Ped_sub_43EC30((struct Ped *)v2->FirstElement);
        v7 = *(_DWORD *)&v2->FirstElement[45].currentData;
        BYTE1(v7) |= 4u;
        *(_DWORD *)&v2->FirstElement[45].currentData = v7;
      }
      v2->FirstElement = 0;
      v2->S32_[0].prev_field = 0;
      v2->S32_[0].currentData = 0;
      --LOBYTE(self->S32_[49].NextElement);
    }
    v2 = (struct TrafficManager *)((char *)v2 + 12);
    result = --v10;
  }
  while ( v10 );
  gMissionManager->field_C1E70 = 87;
  return result;
}


// 0x00476d20: S31::CreatePed2
// IDA: S31::CreatePed2
// Ghidra: ---
_DWORD * gta2::S31_CreatePed2(struct TrafficManager *self, Ped *pPed)
{
  _DWORD *result; // eax
  _DWORD *v4; // esi

  result = gta2::TrafficManager_sub_474E80(self);
  v4 = result;
  if ( result )
  {
    *result = pPed;
    result = (_DWORD *)gta2::Ped_sub_420B60(pPed);
    v4[2] = result;
    *((_BYTE *)v4 + 4) = 3;
    ++LOBYTE(self->S32_[49].NextElement);
  }
  return result;
}


// 0x00476d50: S31::sub_476D50
// IDA: S31::sub_476D50
// Ghidra: ---
TrafficManager * gta2::S31_sub_476D50(struct TrafficManager *self, S32 *pS32, char a3)
{
  struct TrafficManager *result; // eax

  LOBYTE(result) = a3;
  if ( a3
    || pS32
    && ((int)gta2::S32_sub_40FEF0(pS32) < 64 || (result = (struct TrafficManager *)gta2::S32_sub_40FEF0(pS32), (int)result > 108))
    && ((int)gta2::S32_sub_40FEF0(pS32) < 200 || (result = (struct TrafficManager *)gta2::S32_sub_40FEF0(pS32), (int)result > 244)) )
  {
    result = gta2::TrafficManager_sub_474E80(self);
    if ( result )
    {
      result->FirstElement = pS32;
      result->S32_[0].prev_field = pS32[1].NextElement;
      result->S32_[0].currentData = 2;
      ++LOBYTE(self->S32_[49].NextElement);
    }
  }
  return result;
}



