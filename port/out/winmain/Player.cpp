#include "gta2_shim.h"

// Module: winmain, Class: Player
// Functions: 2
// Source: unified (IDA+Ghidra)

// 0x00401b40: Player::sub_401B40
// IDA: Player::sub_401B40
// Ghidra: ---
SpriteS1 * gta2::Player_sub_401B40(Player *self, void *pS202, void *Camer_Z_View)
{
  gta2::S202_SetToNewVal((S202 *)pS202, (SpriteS1 *)((char *)self->CurrentPlayer - *(_DWORD *)Camer_Z_View));
  return (SpriteS1 *)pS202;
}


// 0x00403840: Player::FUN_00403840
// IDA: sub_403840
// Ghidra: Player::FUN_00403840
int * gta2::Player_FUN_00403840(Player *self,int *param_1,GlassInfo *pS110)
{
  if (0 < (int)pS110->car) {
    *param_1 = (int)pS110->car;
    return param_1;
  }
  gta2::JustCopyByPtrAtoC(pS110,param_1);
  return param_1;
}





