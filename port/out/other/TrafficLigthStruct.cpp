#include "gta2_shim.h"

// Module: other, Class: TrafficLigthStruct
// Functions: 6
// Source: unified (IDA+Ghidra)

// 0x00482d10: TrafficLigthStruct::sub_482D10
// IDA: TrafficLigthStruct::sub_482D10
// Ghidra: ---
bool gta2::TrafficLigthStruct_sub_482D10(_BYTE *self)
{
  return self[402] == 1;
}


// 0x00482d20: TrafficLigthStruct::sub_482D20
// IDA: TrafficLigthStruct::sub_482D20
// Ghidra: ---
bool gta2::TrafficLigthStruct_sub_482D20(struct TrafficLigthStruct *self)
{
  return self->Phase == TRAFFIC_PHASE_HORIZONTAL_GREEN;
}


// 0x004c3980: TrafficLigthStruct::TrafficLigthStruct
// IDA: TrafficLigthStruct::TrafficLigthStruct
// Ghidra: ---
TrafficLigthStruct * gta2::TrafficLigthStruct_TrafficLigthStruct(struct TrafficLigthStruct *self)
{
  self->index = 0;
  memset(self, 0, 400u);
  self->Phase = TRAFFIC_PHASE_VERTICAL_GREEN;
  self->Timer = gTimer;
  return self;
}


// 0x004c4a30: TrafficLigthStruct::sub_4C4A30
// IDA: TrafficLigthStruct::sub_4C4A30
// Ghidra: ---
GameObject * gta2::TrafficLigthStruct_sub_4C4A30(
        struct TrafficLigthStruct *self,
        unsigned __int8 a2,
        int *a3,
        int a4,
        SpriteS1 *a5)
{
  struct S202 *pS202; // eax

  pS202 = (struct S202 *)gta2::operator_new(0x20u);
  *(&self->S202_[0].field_0 + self->index++) = (int)pS202;
  return gta2::S202_sub_4C3C70(pS202, a2, a3, a4, a5);
}


// 0x004c4a60: TrafficLigthStruct::sub_4C4A60
// IDA: TrafficLigthStruct::sub_4C4A60
// Ghidra: ---
char gta2::TrafficLigthStruct_sub_4C4A60(struct TrafficLigthStruct *self)
{
  char v2; // al
  TRAFFIC_PHASE v3; // al
  unsigned int v4; // edi
  bool v5; // zf
  char result; // al

  v2 = self->Timer - 1;
  self->Timer = v2;
  if ( !v2 )
  {
    if ( self->Phase == TRAFFIC_PHASE_HORIZONTAL_YELLOW )
      gta2::CarSystemManager_sub_4C39F0(gCarSystemManager);
    v3 = self->Phase + 1;
    self->Phase = v3;
    if ( (unsigned __int8)v3 > 8u )
      self->Phase = TRAFFIC_PHASE_VERTICAL_GREEN;
    v4 = 0;
    v5 = self->index == 0;
    self->Timer = byte_594FF8[(unsigned __int8)self->Phase];
    if ( !v5 )
    {
      do
        gta2::sub_4C3A10(*((void **)&self->S202_[0].field_0 + v4++), self->Phase);
      while ( v4 < self->index );
    }
  }
  result = do_show_traffic_lights_info;
  if ( do_show_traffic_lights_info )
  {
    ShowTextDisplay(&TextWcharT, (char *)L"timer: %d", (unsigned __int8)self->Timer);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, -1, 0, unk_672F18, 1);
    ShowTextDisplay(&TextWcharT, (char *)L"phase: %d", (unsigned __int8)self->Phase);
    gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, -1, 16, unk_672F18, 1);
    result = gta2::TrafficLigthStruct_IsPedCrossingPhase(self);
    if ( result )
      return gta2::S86_7_PrintText(&gHud->S86_7_, &off_5755F4, -1, 32, unk_672F18, 1);
  }
  return result;
}


// 0x004c4b00: TrafficLigthStruct::sub_4C4B00
// IDA: TrafficLigthStruct::sub_4C4B00
// Ghidra: ---
int gta2::TrafficLigthStruct_sub_4C4B00(struct TrafficLigthStruct *self)
{
  int result; // eax
  int v3; // edx
  int *v4; // ecx
  struct SpriteS1 *v5; // [esp-4h] [ebp-8h]

  for ( result = (int)gta2::MapRelatedStruct_sub_464E70(gMapRelatedStruct, 2);
        result;
        result = (int)gta2::MapRelatedStruct_sub_4651C0(gMapRelatedStruct) )
  {
    LOBYTE(v4) = *(_BYTE *)(result + 4);
    LOBYTE(v3) = *(_BYTE *)(result + 3);
    v5 = (struct SpriteS1 *)v4;
    LOBYTE(v4) = *(_BYTE *)(result + 2);
    gta2::TrafficLigthStruct_sub_4C4A30(self, *(_BYTE *)(result + 1), v4, v3, v5);
  }
  return result;
}



