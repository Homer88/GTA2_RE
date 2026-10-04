#include "gta2_shim.h"

// Module: other, Class: Random
// Functions: 4
// Source: unified (IDA+Ghidra)

// 0x00472640: Random::Restart
// IDA: Random::Restart
// Ghidra: ---
int gta2::Random_Restart(struct Random *self)
{
  return gta2::Random_Seed(self, 1);
}


// 0x00472e00: Random::Random
// IDA: Random::Random
// Ghidra: ---
unsigned __int16 gta2::Random_Random(struct Random *self, __int16 *a2)
{
  int pCycle; // eax
  int RandomNumberReal_low; // [esp-8h] [ebp-Ch]

  if ( log_random )
  {
    if ( *a2 )
      self->RandomNumberReal = GetRandomNumberReal() % *a2;
    else
      self->RandomNumberReal = 0;
    RandomNumberReal_low = SLOWORD(self->RandomNumberReal);
    pCycle = gta2::General_GetCycle(gGeneral);
    strcpy(gStr, "%d: random (get_int) %d", pCycle, RandomNumberReal_low);
    gta2::CopyBuffer(byte_5EA6B8, gStr);
    return self->RandomNumberReal;
  }
  else if ( *a2 )
  {
    return GetRandomNumberReal() % *a2;
  }
  else
  {
    return 0;
  }
}


// 0x00472e90: Random::PauseGame
// IDA: Random::PauseGame
// Ghidra: ---
char gta2::Random_PauseGame(struct Game *self, S410 *a2)
{
  int Cycle; // eax
  int Status_low; // [esp-8h] [ebp-Ch]

  if ( log_random )
  {
    if ( a2->a )
      self->Status = GetRandomNumberReal() % (unsigned __int8)a2->a;
    else
      self->Status = 0;
    Status_low = LOBYTE(self->Status);
    Cycle = gta2::General_GetCycle(gGeneral);
    strcpy(gStr, "%d: random (get_uint8) %d", Cycle, Status_low);
    gta2::CopyBuffer(byte_5EA6B8, gStr);
    return self->Status;
  }
  else if ( a2->a )
  {
    return GetRandomNumberReal() % (unsigned __int8)a2->a;
  }
  else
  {
    return 0;
  }
}


// 0x004d71ed: Random::Seed
// IDA: Random::Seed
// Ghidra: ---
int gta2::Random_Seed(struct Random *self, int seed)
{
  int result; // eax

  result = seed;
  gSeed = seed;
  return result;
}



