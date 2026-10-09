#include "gta2_shim.h"

// Module: other, Class: SoundInfo
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00478e10: SoundInfo::sub_478E10
// IDA: SoundInfo::sub_478E10
// Ghidra: ---
void gta2::SoundInfo_sub_478E10(struct MissionScriptObjectData *self)
{
  MissionManager *v1; // edi
  MissionManager *v3; // ebx
  void *started; // esi
  struct HudArrow *HudArrow; // eax

  v1 = dword_6644CC;
  v3 = dword_6644CC;
  started = gta2::MissionManager_StartMission(gMissionManager, dword_6644CC->arr_96[4]);
  if ( !*((_DWORD *)started + 2) )
  {
    HudArrow = gta2::HudArrow_GetHudArrow(&gHud->HudArrow_);
    v1 = dword_6644CC;
    *((_DWORD *)started + 2) = HudArrow;
  }
  gta2::HudArrow_PlayerHandler(*((HudArrow **)started + 2), v3->arr_96[1], v3->arr_96[2], v3->arr_96[3]);
  if ( v1->field_2 == 441 )
  {
    gta2::HudArrow_SetArrowType(*((HudArrow **)started + 2), 5u);
    v1 = dword_6644CC;
  }
  gta2::MissionScriptObjectData_sub_476E50(self, v1);
}


// 0x004797a0: SoundInfo::sub_4797A0
// IDA: SoundInfo::sub_4797A0
// Ghidra: ---
void gta2::SoundInfo_sub_4797A0(struct MissionScriptObjectData *self)
{
  _DWORD *v1; // eax
  MissionManager *v2; // esi
  unsigned __int16 v4; // ax
  _DWORD *v5; // edi

  v2 = dword_6644CC;
  v4 = dword_6644CC->arr_96[1];
  if ( !v4 )
    goto LABEL_7;
  v1 = gta2::MissionManager_StartMission(gMissionManager, v4);
  if ( !v1[2] )
    goto LABEL_7;
  v5 = v1;
  if ( gta2::MissionScriptObjectData_sub_475010(self, *((unsigned __int16 *)v1 + 1)) == 1 )
  {
    if ( v2->field_2 == 138 )
    {
      gta2::Ped_GiveWeapon((Ped *)v5[2], (WeaponType)SHIWORD(v2->arr_96[1]), 100);
LABEL_7:
      gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
      return;
    }
    gta2::Ped_GiveWeapon((Ped *)v5[2], (WeaponType)SHIWORD(v2->arr_96[1]), v2->arr_96[2]);
    gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
  }
  else
  {
    gta2::Turrel_CarAddWeapon(gArsenal, (WeaponType)SHIWORD(v2->arr_96[1]), 0x32u, (Car *)v5[2]);
    gta2::MissionScriptObjectData_sub_476E50(self, dword_6644CC);
  }
}



