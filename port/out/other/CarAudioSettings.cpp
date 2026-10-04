#include "gta2_shim.h"

// Module: other, Class: CarAudioSettings
// Functions: 1
// Source: unified (IDA+Ghidra)

// 0x004b3490: CarAudioSettings::CarAudioSettings
// IDA: CarAudioSettings::CarAudioSettings
// Ghidra: ---
CarAudioSettings * gta2::CarAudioSettings_CarAudioSettings(struct CarAudioSettings *self)
{
  struct AudioSourceParams *pS9; // eax
  void *v3; // ecx

  self->field_9 = 0;
  self->field_A = 0;
  self->sirenActive1 = 0;
  *(_DWORD *)&self->Flag = 0;
  self->Player_ = 0;
  self->int_ = 0;
  pS9 = (struct AudioSourceParams *)gta2::operator_new(24u);
  if ( pS9 )
    self->AudioSourceParams_ = gta2::AudioSourceParams_AudioSourceParams(pS9);
  else
    self->AudioSourceParams_ = 0;
  sub_4B2FF0(v3);
  return self;
}



