#include "gta2_shim.h"

// Module: other, Class: PlayerSlotSave
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x004a8700: PlayerSlotSave::sub_4A8700
// IDA: PlayerSlotSave::sub_4A8700
// Ghidra: ---
byte * gta2::PlayerSlotSave_sub_4A8700(struct PlayerSlotSave *self)
{
  int v1; // esi
  byte *result; // eax
  int count; // edx

  *(_DWORD *)self->PlayerName = 0;
  *(_DWORD *)&self->PlayerName[2] = 0;
  v1 = 3;
  *(_DWORD *)&self->PlayerName[4] = 0;
  *(_DWORD *)&self->PlayerName[6] = 0;
  self->field_A0 = 0;
  result = self->ArenaSlots_[0].SubSlot[0].BonusStage[2];
  do
  {
    count = 4;
    do
    {
      *(result - 8) = 0;
      *((_DWORD *)result - 1) = 0;
      *(_DWORD *)result = 0;
      result += 12;
      --count;
    }
    while ( count );
    --v1;
  }
  while ( v1 );
  self->ArenaSlots_[0].SubSlot[0].BonusStage[0][0] = 1;
  return result;
}


// 0x004a8780: PlayerSlotSave::sub_4A8780
// IDA: PlayerSlotSave::sub_4A8780
// Ghidra: ---
int gta2::PlayerSlotSave_sub_4A8780(struct PlayerSlotSave *self)
{
  int result; // eax
  byte *v2; // ecx
  int v3; // esi
  int v4; // edx
  int v5; // edi

  result = 0;
  v2 = self->ArenaSlots_[0].SubSlot[0].BonusStage[1];
  v3 = 3;
  do
  {
    v4 = 4;
    do
    {
      v5 = *(_DWORD *)v2;
      v2 += 12;
      result += v5;
      --v4;
    }
    while ( v4 );
    --v3;
  }
  while ( v3 );
  return result;
}



