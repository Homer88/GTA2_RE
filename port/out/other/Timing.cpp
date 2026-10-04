#include "gta2_shim.h"

// Module: other, Class: Timing
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004c36c0: Timing::sub_4C36C0
// IDA: Timing::sub_4C36C0
// Ghidra: ---
int gta2::Timing_sub_4C36C0(struct Timing *self)
{
  ShowTextDisplay(&TextWcharT, (char *)off_5755B4, self->field_8, self->Sec_100);
  return gta2::S86_7_PrintText(&gHud->S86_7_, &TextWcharT, 0, 0, unk_672F18, 1);
}


// 0x004c3700: Timing::Timing
// IDA: Timing::Timing
// Ghidra: ---
Timing * gta2::Timing_Timing(struct Timing *self)
{
  gta2::S36_S36(self->S36);
  gta2::S36_S36(&self->S36[1]);
  gta2::S36_S36(&self->S36[2]);
  gta2::S36_S36(&self->S36[3]);
  gta2::S36_S36(&self->S36[4]);
  self->field_8 = 0;
  self->Sec_100 = 0;
  self->field = 0;
  self->field_C = 0;
  self->timeGetTime = timeGetTime();
  self->timeGetTime_1 = timeGetTime();
  return self;
}


// 0x004c3760: Timing::sub_4C3760
// IDA: Timing::sub_4C3760
// Ghidra: ---
char gta2::Timing_sub_4C3760(struct Timing *self, char a2, char a3)
{
  DWORD Time; // eax
  DWORD v5; // ecx

  LOBYTE(Time) = a3;
  if ( a3 )
  {
    Time = self->field + 1;
    self->field = Time;
    if ( Time == 100 )
    {
      v5 = timeGetTime() - self->timeGetTime;
      self->field_8 = 0x186A0 / v5;
      self->S36[0].field_0 = 100 * self->S36[0].DeltaTime / v5;
      self->S36[1].field_0 = 100 * self->S36[1].DeltaTime / v5;
      self->S36[2].field_0 = 100 * self->S36[2].DeltaTime / v5;
      self->S36[3].field_0 = 100 * self->S36[3].DeltaTime / v5;
      self->S36[4].field_0 = 100 * self->S36[4].DeltaTime / v5;
      Time = timeGetTime();
      self->timeGetTime = Time;
      self->field = 0;
      self->S36[0].DeltaTime = 0;
      self->S36[1].DeltaTime = 0;
      self->S36[2].DeltaTime = 0;
      self->S36[3].DeltaTime = 0;
      self->S36[4].DeltaTime = 0;
    }
  }
  if ( a2 )
  {
    Time = self->field_C + 1;
    self->field_C = Time;
    if ( Time == 100 )
    {
      self->Sec_100 = 100000 / (timeGetTime() - self->timeGetTime_1);
      Time = timeGetTime();
      self->timeGetTime_1 = Time;
      self->field_C = 0;
    }
  }
  return Time;
}



