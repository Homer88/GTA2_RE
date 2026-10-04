#include "gta2_shim.h"

// Module: other, Class: S86_5
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004c73a0: S86_5::sub_4C73A0
// IDA: S86_5::sub_4C73A0
// Ghidra: ---
char gta2::S86_5_sub_4C73A0(int *self)
{
  struct Ped *CurrentPed; // eax
  struct Ped *v3; // esi
  int *PositionZ; // ebx
  int *v5; // eax
  int *v6; // ebp
  int *XCoordinate; // eax
  struct CarSystemManager *Rotation; // eax
  int *v9; // ebx
  int *v10; // eax
  int *v11; // ebp
  int *v12; // eax
  struct CameraOrPhysics *MultiPlayerMode; // eax
  int v15; // [esp-14h] [ebp-30h]
  int v16; // [esp-10h] [ebp-2Ch]
  AudioSourceParams v17; // [esp-Ch] [ebp-28h]
  int v18; // [esp-Ch] [ebp-28h]
  int Y; // [esp+10h] [ebp-Ch] BYREF
  int Z; // [esp+14h] [ebp-8h] BYREF
  int X; // [esp+18h] [ebp-4h] BYREF

  CurrentPed = gta2::Player_GetCurrentPed(gGame->PlayerMain);
  v3 = CurrentPed;
  if ( !CurrentPed || (LOBYTE(CurrentPed) = gta2::sub_4354F0(CurrentPed), (_BYTE)CurrentPed) )
  {
    *((_BYTE *)self + 10) = 0;
  }
  else
  {
    PositionZ = (int *)gta2::Ped_GetPositionZ(v3, (int)&Z);
    gta2::Ped_GetYCoordinate(v3, &Y);
    v6 = v5;
    XCoordinate = (int *)gta2::Ped_GetXCoordinate(v3, (int)&X);
    v17.AudioSourceParams1 = *PositionZ;
    v17.AudioSourceParams = *v6;
    v17.field = *XCoordinate;
    LOBYTE(CurrentPed) = gta2::MapRelatedStruct_sub_463850(gMapRelatedStruct, v17);
    *((_BYTE *)self + 10) = (_BYTE)CurrentPed;
    if ( (_BYTE)CurrentPed )
    {
      Rotation = (struct CarSystemManager *)gta2::Ped_GetRotation(v3, (__int16 *)&Z);
      *((_WORD *)self + 4) = *(_WORD *)gta2::sub_40E5A0(Rotation, (struct CarSystemManager *)&Y, &unk_67314C);
      v9 = (int *)gta2::Ped_GetPositionZ(v3, (int)&X);
      gta2::Ped_GetYCoordinate(v3, &Z);
      v11 = v10;
      v12 = (int *)gta2::Ped_GetXCoordinate(v3, (int)&Y);
      v18 = *v9;
      v16 = *v11;
      v15 = *v12;
      MultiPlayerMode = gta2::Player_GetMultiPlayerMode(gGame->PlayerMain);
      LOBYTE(CurrentPed) = (unsigned __int8)gta2::CameraOrPhysics_WorldToScreen2D(
                                              MultiPlayerMode,
                                              v15,
                                              v16,
                                              v18,
                                              self,
                                              self + 1);
    }
  }
  return (char)CurrentPed;
}


// 0x004c74a0: S86_5::sub_4C74A0
// IDA: S86_5::sub_4C74A0
// Ghidra: ---
char gta2::S86_5_sub_4C74A0(void *self)
{
  char result; // al

  result = *((_BYTE *)self + 10);
  if ( result )
  {
    gta2::Player_GetMultiPlayerMode(gGame->PlayerMain);
    return gta2::sub_4CBA50(*((void **)self + 1), 6, 0, *(_DWORD *)self, *((void **)self + 1));
  }
  return result;
}



