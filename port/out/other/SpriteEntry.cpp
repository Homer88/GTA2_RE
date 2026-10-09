#include "gta2_shim.h"

// Module: other, Class: SpriteEntry
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004b9e50: SpriteEntry::sub_4B9E50
// IDA: SpriteEntry::sub_4B9E50
// Ghidra: ---
void gta2::SpriteEntry_sub_4B9E50(SpriteEntry *self)
{
  self->ptr = 0;
}


// 0x004bdc60: SpriteEntry::sub_4BDC60
// IDA: SpriteEntry::sub_4BDC60
// Ghidra: ---
int gta2::SpriteEntry_sub_4BDC60(SpriteEntry *self)
{
  unk_66FF18 = gta2::SpriteS1_sub_421000(gSpriteS1);
  return gta2::SpriteS1_sub_4BCB90(unk_66FF18, unk_670010, (SpriteS3 *)unk_670010, (EventHandler *)unk_670010);
}


// 0x004be5b0: SpriteEntry::SpriteEntry
// IDA: SpriteEntry::SpriteEntry
// Ghidra: ---
SpriteEntry * gta2::SpriteEntry_SpriteEntry(SpriteEntry *self)
{
  SpriteS1 *pSpriteS1_1; // eax
  SpriteS1 *pSpriteS1; // eax
  SpriteS2 *v4; // eax
  SpriteS2 *pSpriteS2; // eax
  SpriteS3 *v6; // eax
  SpriteS3 *pSpriteS3; // eax
  SpriteS4 *v8; // eax
  SpriteS4 *v9; // eax

  pSpriteS1_1 = (SpriteS1 *)gta2::operator_new(0x49B28u);
  if ( pSpriteS1_1 )
    pSpriteS1 = gta2::SpriteS1_SpriteS1(pSpriteS1_1);
  else
    pSpriteS1 = 0;
  gSpriteS1 = pSpriteS1;
  if ( !pSpriteS1 )
    gta2::debug_log(0x20u, "sprite.cpp", 3239);
  v4 = (SpriteS2 *)gta2::operator_new(0x5D598u);
  if ( v4 )
    pSpriteS2 = gta2::SpriteS2_SpriteS2(v4);
  else
    pSpriteS2 = 0;
  gSpriteS2 = pSpriteS2;
  if ( !pSpriteS2 )
    gta2::debug_log(0x20u, "sprite.cpp", 3241);
  v6 = (SpriteS3 *)gta2::operator_new(0x3CCu);
  if ( v6 )
    pSpriteS3 = gta2::SpriteS3_SpriteS3(v6);
  else
    pSpriteS3 = 0;
  gSpriteS3 = pSpriteS3;
  if ( !pSpriteS3 )
    gta2::debug_log(0x20u, "sprite.cpp", 3243);
  v8 = (SpriteS4 *)gta2::operator_new(0x1C24u);
  if ( v8 )
    v9 = gta2::SpriteS4_SpriteS4(v8);
  else
    v9 = 0;
  gSpriteS4 = v9;
  if ( !v9 )
    gta2::debug_log(0x20u, "sprite.cpp", 3246);
  self->ptr = 0;
  self->W = 1;
  return self;
}



