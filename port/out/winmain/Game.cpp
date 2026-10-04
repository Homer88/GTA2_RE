#include "gta2_shim.h"

// Module: winmain, Class: Game
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x003f113c: Game::GetCurrentPlayerSlot
// IDA: Game::GetCurrentPlayerSlot
// Ghidra: ---
void * gta2::Game_GetCurrentPlayerSlot(Game *self)
{
  unsigned __int8 v1; // al
  _BYTE *v2; // ecx
  char v3; // dl
  int v4; // esi
  unsigned __int8 v6; // [esp-4h] [ebp-4h]

  v1 = gta2::Game_sub_3F135C(self, v6);
  unk_676200 = v1;
  unk_676201 = 0;
  v2[33] = v1;
  if ( !v3 )
    return 0;
  while ( 1 )
  {
    v4 = *(_DWORD *)&v2[4 * v1 + 4];
    if ( v4 )
      break;
LABEL_5:
    if ( ++v1 >= 6u )
      v1 = 0;
    v2[33] = v1;
    if ( unk_676201 >= v2[35] )
      return 0;
  }
  if ( !*(_BYTE *)(v4 + 142) )
  {
    ++unk_676201;
    goto LABEL_5;
  }
  v2[34] = 0;
  return (void *)(*(_DWORD *)&v2[4 * v1 + 4] + 144);
}


// 0x003f11a8: Game::start1
// IDA: Game::start1
// Ghidra: ---
Player * gta2::Game_start1(Game *self)
{
  unsigned __int8 MaxIdx; // dl
  unsigned __int8 pID; // al
  Player *v3; // edx

  MaxIdx = self->MaxIdx;
  pID = unk_676200;
  unk_676203 = 0;
  self->CurrentPlayerCopy = unk_676200;
  if ( !MaxIdx )
    return 0;
  while ( 1 )
  {
    v3 = self->ArrayPlayer[pID];
    if ( v3 )
      break;
LABEL_5:
    if ( ++pID >= 6u )
      pID = 0;
    self->CurrentPlayerCopy = pID;
    if ( unk_676203 >= self->MaxIdx )
      return 0;
  }
  if ( !v3->PlayerNext )
  {
    ++unk_676203;
    goto LABEL_5;
  }
  return self->ArrayPlayer[pID];
}


// 0x003f1208: Game::SwitchToNextPlayer
// IDA: Game::SwitchToNextPlayer
// Ghidra: ---
CameraOrPhysics ** gta2::Game_SwitchToNextPlayer(Game *self)
{
  unsigned __int8 Index; // al
  Player *v3; // edx
  unsigned __int8 v4; // al
  bool v5; // cf

  Index = self->Index;
  if ( !self->ArrayPlayer[Index]->field_2D0 || self->field_22 )
  {
    LOBYTE(v3) = self->MaxIdx;
    while ( 2 )
    {
      ++unk_676201;
      v4 = Index + 1;
      if ( v4 >= 6u )
        v4 = 0;
      v5 = unk_676201 < (unsigned __int8)v3;
      self->Index = v4;
      if ( v5 )
      {
        do
        {
          v3 = self->ArrayPlayer[v4];
          if ( v3 )
          {
            if ( v3->PlayerNext )
            {
              self->field_22 = 0;
              return &self->ArrayPlayer[v4]->CameraOrPhysics1;
            }
            ++unk_676201;
          }
          ++v4;
        }
        while ( v4 < 6u );
        Index = 0;
        self->Index = 0;
        if ( unk_676201 < self->MaxIdx )
          continue;
      }
      break;
    }
    return 0;
  }
  else
  {
    self->field_22 = 1;
    return &self->ArrayPlayer[Index]->CameraOrPhysics2;
  }
}


// 0x003f12a8: Game::CycleToNextPlayer
// IDA: Game::CycleToNextPlayer
// Ghidra: ---
Player * gta2::Game_CycleToNextPlayer(Game *self)
{
  unsigned __int8 CurentPlayer; // al
  unsigned __int8 MaxIdx; // dl
  unsigned __int8 v3; // al
  bool v4; // cf
  Player *v5; // edx

  CurentPlayer = self->CurrentPlayerCopy;
  MaxIdx = self->MaxIdx;
  ++unk_676203;
  v3 = CurentPlayer + 1;
  if ( v3 >= 6u )
    v3 = 0;
  v4 = unk_676203 < MaxIdx;
  self->CurrentPlayerCopy = v3;
  if ( !v4 )
    return 0;
  while ( 1 )
  {
    v5 = self->ArrayPlayer[v3];
    if ( v5 )
      break;
LABEL_7:
    if ( ++v3 >= 6u )
      v3 = 0;
    self->CurrentPlayerCopy = v3;
    if ( unk_676203 >= self->MaxIdx )
      return 0;
  }
  if ( !v5->PlayerNext )
  {
    ++unk_676203;
    goto LABEL_7;
  }
  return self->ArrayPlayer[v3];
}


// 0x003f135c: Game::sub_3F135C
// IDA: Game::sub_3F135C
// Ghidra: ---
char gta2::Game_sub_3F135C(Game *self, unsigned __int8 a2)
{
  unsigned __int8 v2; // dl

  if ( v2 > 1u )
    return gta2::Random_PauseGame(self, (S410 *)sub_3F113B);
  else
    return 0;
}


// 0x00401b00: Game::ShiftId
// IDA: Game::ShiftId
// Ghidra: ---
int gta2::Game_ShiftId(Game *self)
{
  return (int)self->Status >> 14;
}



