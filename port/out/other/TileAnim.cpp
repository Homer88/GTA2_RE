#include "gta2_shim.h"

// Module: other, Class: TileAnim
// Functions: 5
// Source: unified (IDA+Ghidra)

// 0x004c3430: TileAnim::sub_4C3430
// IDA: TileAnim::sub_4C3430
// Ghidra: FUN_004c3430
void gta2::TileAnim_sub_4C3430(undefined4 param_1,undefined4 param_2,undefined4 param_3, undefined4 param_4,undefined4 param_5)
{
  ScriptCommand *self;
  
  self = (ScriptCommand *)gta2::TileAnim1_sub_4C3380(gScriptVar);
  FUN_004c33f0(param_1,param_2,param_3,param_4,param_5);
  gta2::ScriptCommand_FUN_004c32e0(self);
  return;
}


// 0x004c3470: TileAnim::sub_4C3470
// IDA: TileAnim::sub_4C3470
// Ghidra: TileAnim::FUN_004c3470
void gta2::TileAnim_sub_4C3470(struct TileAnim *self,undefined2 *param_1)
{
  void *this_00;
  ScriptCommand *this_01;
  
  this_00 = (void *)gta2::TileAnim1_sub_4C3380(gScriptVar);
  FUN_004c32a0(this_00,param_1);
  gta2::ScriptCommand_FUN_004c32e0(this_01);
  return;
}


// 0x004c3590: TileAnim::sub_4C3590
// IDA: TileAnim::sub_4C3590
// Ghidra: ---
void gta2::TileAnim_sub_4C3590(struct TileAnim *self)
{
  TileAnim1 *pS70; // ebx
  struct TileAnim2 *NextTileAnim2_1; // esi
  struct TileAnim2 *v3; // edi
  struct TileAnim2 *NextTileAnim2; // ebp
  struct TileAnim2 *NextS71; // eax
  struct TileAnim2 *TileAnim2; // eax

  pS70 = gTileAnim1;
  NextTileAnim2_1 = gTileAnim1->NextS71;
  v3 = 0;
  gTileAnim1->field_4B8 = 0;
  if ( NextTileAnim2_1 )
  {
    do
    {
      ++pS70->field_4B8;
      NextTileAnim2 = NextTileAnim2_1->NextTileAnim2;
      if ( gta2::TileAnim2_sub_4C3300(NextTileAnim2_1) )
      {
        if ( !v3 )
          goto LABEL_6;
        if ( v3->NextTileAnim2 != NextTileAnim2_1 )
        {
          v3 = 0;
LABEL_6:
          NextS71 = pS70->NextS71;
          if ( NextS71 == NextTileAnim2_1 )
          {
            TileAnim2 = pS70->TileAnim2_;
            pS70->NextS71 = NextTileAnim2_1->NextTileAnim2;
            NextTileAnim2_1->NextTileAnim2 = TileAnim2;
            pS70->TileAnim2_ = NextTileAnim2_1;
          }
          else
          {
            v3 = pS70->NextS71;
            if ( NextS71->NextTileAnim2 != NextTileAnim2_1 )
            {
              do
                v3 = v3->NextTileAnim2;
              while ( v3->NextTileAnim2 != NextTileAnim2_1 );
            }
            v3->NextTileAnim2 = NextTileAnim2_1->NextTileAnim2;
            NextTileAnim2_1->NextTileAnim2 = pS70->TileAnim2_;
            pS70->TileAnim2_ = NextTileAnim2_1;
          }
          goto LABEL_13;
        }
        v3->NextTileAnim2 = NextTileAnim2_1->NextTileAnim2;
        NextTileAnim2_1->NextTileAnim2 = pS70->TileAnim2_;
        pS70->TileAnim2_ = NextTileAnim2_1;
      }
      else
      {
        v3 = NextTileAnim2_1;
      }
LABEL_13:
      NextTileAnim2_1 = NextTileAnim2;
    }
    while ( NextTileAnim2 );
  }
}


// 0x004c35a0: TileAnim::TileAnim
// IDA: TileAnim::TileAnim
// Ghidra: ---
TileAnim * gta2::TileAnim_TileAnim(struct TileAnim *self)
{
  TileAnim1 *_pS70; // eax
  TileAnim1 *pS70; // eax

  if ( !gTileAnim1 )
  {
    _pS70 = (TileAnim1 *)gta2::operator_new(1212u);
    if ( _pS70 )
      pS70 = gta2::TileAnim1_TileAnim1(_pS70);
    else
      pS70 = 0;
    gTileAnim1 = pS70;
    if ( !pS70 )
      gta2::debug_log(0x20u, "tileanim.cpp", 220);
  }
  *self = (TileAnim)1;
  return self;
}


// 0x004c3650: TileAnim::TileAnimDes
// IDA: TileAnim::TileAnimDes
// Ghidra: ---
TileAnim1 * gta2::TileAnim_TileAnimDes(struct TileAnim *self)
{
  TileAnim1 *result; // eax

  if ( gTileAnim1 )
  {
    result = gta2::TileAnim1_TileAnim1Des(gTileAnim1, 1);
    gTileAnim1 = 0;
  }
  return result;
}



