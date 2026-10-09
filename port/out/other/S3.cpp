#include "gta2_shim.h"

// Module: other, Class: S3
// Functions: 3
// Source: unified (IDA+Ghidra)

// 0x004bbd10: S3::sub_4BBD10
// IDA: S3::sub_4BBD10
// Ghidra: ---
cameraPosTarget * gta2::S3_sub_4BBD10(struct CarTransforms *self)
{
  cameraPosTarget *result; // eax

  result = (cameraPosTarget *)self->PositionX;
  if ( result )
  {
    result = gta2::DMAudio_DMAudio_des(&gDMAudio, (cameraPosTarget *)self->PositionX);
    self->PositionX = 0;
  }
  return result;
}


// 0x004bccc0: S3::sub_4BCCC0
// IDA: S3::sub_4BCCC0
// Ghidra: ---
int gta2::S3_sub_4BCCC0(struct CarTransforms *self)
{
  CarTransforms *NextElement; // eax
  int result; // eax

  NextElement = self->NextElement;
  if ( NextElement )
  {
    gta2::SpriteS2_sub_4BCA10(gSpriteS2, (SpriteS3 *)NextElement);
    self->NextElement = 0;
  }
  result = (int)self->GameObject_;
  if ( result )
  {
    result = (int)gta2::SpriteS2_sub_4BCA10(gSpriteS2, (SpriteS3 *)self->GameObject_);
    self->GameObject_ = 0;
  }
  return result;
}


// 0x004bdc40: S3::sub_4BDC40
// IDA: S3::sub_4BDC40
// Ghidra: ---
cameraPosTarget * gta2::S3_sub_4BDC40(void *self)
{
  gta2::S3_sub_4BCCC0((CarTransforms *)self);
  *((_WORD *)self + 16) = 0;
  return gta2::S3_sub_4BBD10((CarTransforms *)self);
}



