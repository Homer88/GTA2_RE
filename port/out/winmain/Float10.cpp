#include "gta2_shim.h"

// Module: winmain, Class: Float10
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x00401b10: Float10::EncodedFloatToRegularFloat
// IDA: Float10::EncodedFloatToRegularFloat
// Ghidra: ---
double gta2::Float10_EncodedFloatToRegularFloat(int *self)
{
  return (double)*self * 0.000061035156;
}



