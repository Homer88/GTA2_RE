#include "gta2_shim.h"

// Module: other, Class: AudioManager
// Functions: 14
// Source: unified (IDA+Ghidra)

// 0x004b1d40: AudioManager::sub_4B1D40
// IDA: AudioManager::sub_4B1D40
// Ghidra: ---
char gta2::AudioManager_sub_4B1D40(struct AudioManager *self)
{
  unsigned int v1; // eax
  int v2; // esi
  int *p_field_5478; // ecx

  LOBYTE(v1) = unk_66BEEC;
  if ( unk_66BEEC )
  {
    v2 = 5;
    v1 = 90000 * self->field_8;
    p_field_5478 = &self->field_5478;
    do
    {
      if ( *p_field_5478 < v1 )
        ++*p_field_5478;
      p_field_5478 += 7;
      --v2;
    }
    while ( v2 );
  }
  return v1;
}


// 0x004b1d80: AudioManager::ResetAudioState
// IDA: AudioManager::ResetAudioState
// Ghidra: ---
void gta2::AudioManager_ResetAudioState(struct AudioManager *self)
{
  int streamIndex; // esi
  int v3; // edi
  AudioBuffer *buffer; // eax
  int v5; // ecx
  unsigned int sampleRate; // eax

  if ( unk_66BEEC )
  {
    unk_66BEEC = 0;
    streamIndex = 0;
    v3 = 2;
    do
    {
      gta2::SoundCard_CloseStreamByIndex(&gSoundCard, streamIndex++);
      --v3;
    }
    while ( v3 );
    buffer = self->AudioBuffer_;
    v5 = 5;
    do
    {
      LOBYTE(buffer[-2].field_C) = 0;
      buffer->isActive = 0;
      buffer->dataSize = 0;
      buffer->sampleRate = 0;
      buffer->endOffset = 0;
      buffer -= 2;
      --v5;
    }
    while ( v5 );
    sampleRate = self->AudioBuffer_[2].sampleRate;
    *(int *)((char *)&self->AudioBuffer_[3].endOffset + 2) = 0;
    if ( sampleRate )
    {
      gta2::AudioManager_sub_416C10(self, sampleRate);
      self->AudioBuffer_[2].sampleRate = 0;
    }
  }
}


// 0x004b1e00: AudioManager::sub_4B1E00
// IDA: AudioManager::sub_4B1E00
// Ghidra: ---
unsigned __int8 gta2::AudioManager_sub_4B1E00(struct AudioManager *self, int a2)
{
  unsigned __int8 result; // al
  unsigned __int8 v3; // [esp+8h] [ebp-4h]

  result = 0;
  v3 = 0;
  while ( *(&self->field_5470 + 7 * v3) != a2 )
  {
    v3 = ++result;
    if ( result >= 5u )
      return 127;
  }
  return result;
}


// 0x004b1e40: AudioManager::sub_4B1E40
// IDA: AudioManager::sub_4B1E40
// Ghidra: ---
Car * gta2::AudioManager_sub_4B1E40(struct AudioManager *self)
{
  int v1; // ebx
  int v2; // ebp
  Car *result; // eax
  Car *pCar; // edi
  char dataSize; // al
  int *v7; // eax
  int *v8; // ebx
  int *v9; // eax
  int *v10; // ebp
  int *v11; // eax
  unsigned __int8 isActive; // bl
  char v13; // al
  int v14; // ebp
  unsigned int HZ; // eax
  int v16; // edi
  int v17; // ecx
  int v18; // edx
  int sampleRate; // ecx
  char v20; // bl
  unsigned int v21; // eax
  unsigned int v22; // ecx
  int v23; // eax
  unsigned int v24; // eax
  int v25; // edx
  int CDVol; // ecx
  AudioSourceParams v27; // [esp-14h] [ebp-28h]
  int v28; // [esp+8h] [ebp-Ch] BYREF
  int a2; // [esp+Ch] [ebp-8h] BYREF
  char v30[4]; // [esp+10h] [ebp-4h] BYREF

  result = gta2::Player_GetActivePlayerCar(gGame->PlayerMain);
  pCar = result;
  if ( !result )
    return result;
  if ( !LOBYTE(self->AudioBuffer_[0].field_C) )
    LOBYTE(self->AudioBuffer_[2].dataSize) = 0;
  dataSize = self->AudioBuffer_[2].dataSize;
  v27.field_10 = v1;
  v27.AudioSourceParams2 = v2;
  if ( dataSize )
  {
    LOBYTE(self->AudioBuffer_[1].isActive) = 0;
    LOBYTE(self->AudioBuffer_[2].dataSize) = dataSize - 1;
  }
  else
  {
    gta2::Car_GetZ(pCar, &a2);
    v8 = v7;
    gta2::Car_GetY(pCar, &v28);
    v10 = v9;
    gta2::Car_GetX(pCar, (int *)v30);
    v27.AudioSourceParams1 = *v8;
    v27.AudioSourceParams = *v10;
    v27.field = *v11;
    if ( gta2::MapRelatedStruct_sub_463850(gMapRelatedStruct, v27) )
      LOBYTE(self->AudioBuffer_[1].isActive) -= LOBYTE(self->AudioBuffer_[1].isActive) >> 2;
  }
  isActive = self->AudioBuffer_[1].isActive;
  a2 = isActive * self->CDVol / 127;
  if ( isActive >= 0x73u )
  {
    v13 = 0;
    goto LABEL_19;
  }
  if ( self->IsUserPaused )
  {
    v13 = 0;
  }
  else
  {
    v13 = 127 - isActive;
    LOBYTE(v28) = 127 - isActive;
    if ( (unsigned __int8)(127 - isActive) <= 0x64u )
      goto LABEL_13;
    v13 = 100;
  }
  LOBYTE(v28) = v13;
LABEL_13:
  if ( (unsigned __int8)v28 > byte_66C272[0] + 5 )
  {
    v13 = byte_66C272[0] + 5;
LABEL_19:
    LOBYTE(v28) = v13;
    goto LABEL_20;
  }
  if ( (unsigned __int8)v28 < byte_66C272[0] - 10 )
  {
    v13 = byte_66C272[0] - 10;
    goto LABEL_19;
  }
LABEL_20:
  if ( self->IsUserPaused == 1 )
  {
    v13 = 0;
    LOBYTE(v28) = 0;
    a2 = (unsigned int)a2 >> 1;
  }
  byte_66C272[0] = v13;
  if ( v13 )
  {
    if ( unk_66C270 )
    {
      --unk_66C270;
      v14 = dword_593E68;
    }
    else
    {
      unk_66C270 = *(&self->field_145C + 1) % 0x23u;
      HZ = gta2::SoundCard_GetHZ(&gSoundCard, 137);
      v14 = self->field_145C % (HZ >> 2) + HZ;
    }
    v16 = (unsigned __int8)v28;
    v17 = (unsigned __int8)v28 * self->CDVol;
    dword_593E68 = v14;
    v18 = (unsigned __int64)(2164392969LL * v17) >> 32;
    sampleRate = self->AudioBuffer_[2].sampleRate;
    self->HZ = v14;
    self->field_30 = sampleRate;
    v20 = (unsigned __int8)((v18 < 0) + (v18 >> 6)) >> 2;
    self->field_34 = 0;
    self->SoundCar = 137;
    self->field_48 = 1;
    self->field_54 = v20;
    self->field_64 = 0;
    self->field_68 = -1;
    self->field_4C = 0;
    gta2::bitShiftLeft1(&v28, 0);
    self->field_58 = v28;
    self->Volume = 64;
    self->field_71 = 0;
    self->field_60 = 0;
    self->field_7C = 5;
    self->field_88 = 20;
    self->field_90 = v20;
    self->field_94 = 50;
    gta2::AudioManager_sub_4171A0(self);
    if ( !*(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) )
    {
      v21 = gta2::SoundCard_GetHZ(&gSoundCard, 138);
      v22 = (v21 >> 6) * *(&self->field_5470 + 7 * HIBYTE(self->AudioBuffer_[1].isActive)) + v21;
      v23 = dword_593E64 + 90;
      if ( v22 > dword_593E64 + 90 || (v23 = dword_593E64 - 90, v22 < dword_593E64 - 90) )
        v22 = v23;
      v24 = self->field_1458;
      dword_593E64 = v22;
      self->field_34 = 1;
      self->SoundCar = 138;
      self->field_48 = 1;
      v25 = v22 + v24 % 0x8C;
      CDVol = self->CDVol;
      self->HZ = v25;
      self->field_54 = (unsigned __int8)(self->field_145C % 3u
                                       + ((int)((unsigned __int64)(2164392969LL * v16 * CDVol) >> 32) >> 7 < 0)
                                       + ((int)((unsigned __int64)(2164392969LL * v16 * CDVol) >> 32) >> 7)) >> 2;
      gta2::bitShiftLeft1(&v28, 0);
      self->field_58 = v28;
      self->Volume = 64;
      self->field_88 = 20;
      gta2::AudioManager_sub_4171A0(self);
    }
  }
  gta2::SoundCard_SetStreamVolume_0(&gSoundCard, 0, a2);
  return result;
}


// 0x004b2180: AudioManager::sub_4B2180
// IDA: AudioManager::sub_4B2180
// Ghidra: ---
char gta2::AudioManager_sub_4B2180(struct AudioManager *self, cGameObject *a2)
{
  int v3; // esi
  char *v4; // edi
  __int16 v5; // si
  unsigned __int16 v6; // si
  __int16 v7; // bx
  unsigned __int16 v8; // si
  unsigned __int16 v9; // ax
  int v10; // eax
  int Y; // [esp+Ch] [ebp-8h] BYREF
  int v13; // [esp+1Ch] [ebp+8h]

  v3 = (unsigned __int8)a2;
  v4 = &self->AudioObject + 28 * (unsigned __int8)a2;
  if ( !v4[21608] || !*((_DWORD *)v4 + 5405) )
    return 0;
  gta2::Player_sub_4A6610(gGame->PlayerMain, &Y);
  v5 = gta2::sub_41F9E0(&self->field_546C + 7 * v3);
  v6 = abs16(gta2::Game_ShiftId((Game *)&a2) - v5);
  v7 = gta2::sub_41F9E0(v4 + 21612);
  v8 = abs16(gta2::Game_ShiftId((Game *)&Y) - v7) + v6;
  v9 = v13 ? *((_WORD *)v4 + 10813) : *((_WORD *)v4 + 10812);
  if ( v8 >= v9 )
    return 0;
  v10 = 7 * v9 / 8;
  if ( v8 >= (unsigned __int16)v10 )
    return 127 - (unsigned __int16)(127 * (v8 - v10)) / (v8 >> 3);
  else
    return 127;
}


// 0x004b2350: AudioManager::sub_4B2350
// IDA: AudioManager::sub_4B2350
// Ghidra: ---
char gta2::AudioManager_sub_4B2350(struct AudioManager *self, unsigned __int8 a2, int a3)
{
  __int16 v4; // bx
  unsigned __int8 v5; // bp
  int v6; // esi
  char *v7; // eax
  __int16 v9; // [esp+10h] [ebp-4h]

  v9 = gta2::sub_41F9E0(&a2);
  v4 = gta2::sub_41F9E0(&a3);
  a2 = 5;
  while ( 1 )
  {
    v5 = a2;
    v6 = a2;
    if ( *(&self->field_544C + 28 * a2) == 1
      && (unsigned __int16)gta2::sub_41F9E0(&self->field_5450 + 7 * a2) == v9
      && (unsigned __int16)gta2::sub_41F9E0(&self->relToAudio + 7 * v6) == v4 )
    {
      break;
    }
    LOBYTE(v7) = --a2;
    if ( !a2 )
      return (char)v7;
  }
  v7 = &self->AudioObject + 28 * v5;
  v7[21580] = 0;
  *((_WORD *)v7 + 10798) = 0;
  *((_WORD *)v7 + 10799) = 0;
  *((_DWORD *)v7 + 5400) = 0;
  *((_DWORD *)v7 + 5401) = 0;
  return (char)v7;
}


// 0x004b2420: AudioManager::sub_4B2420
// IDA: AudioManager::sub_4B2420
// Ghidra: ---
char gta2::AudioManager_sub_4B2420(struct AudioManager *self)
{
  unsigned __int8 v2; // bp
  unsigned __int8 v3; // bl
  char v4; // al
  unsigned int v5; // eax
  unsigned int v6; // eax
  unsigned int v7; // et2
  unsigned __int8 v9; // [esp+13h] [ebp-9h]
  cGameObject *a2; // [esp+14h] [ebp-8h]
  unsigned __int8 v11; // [esp+18h] [ebp-4h]

  v9 = 0;
  LOBYTE(a2) = HIBYTE(self->AudioBuffer_[1].isActive);
  v2 = (unsigned __int8)a2;
  while ( 2 )
  {
    if ( LOBYTE(self->AudioBuffer_[2].isActive) == 1 )
    {
      LOBYTE(a2) = (v2 + 1) % 5;
    }
    else if ( (_BYTE)a2 )
    {
      LOBYTE(a2) = (_BYTE)a2 - 1;
    }
    else
    {
      LOBYTE(a2) = 4;
    }
    v2 = (unsigned __int8)a2;
    v3 = 0;
    v11 = 0;
    do
    {
      v4 = gta2::AudioManager_sub_4B2180(self, a2);
      if ( (unsigned __int8)v4 > 0x41u )
      {
        HIBYTE(self->AudioBuffer_[1].isActive) = (_BYTE)a2;
        LOBYTE(self->AudioBuffer_[1].isActive) = v4;
        v6 = self->field_1454;
        *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) = 1 - v11;
        v7 = v6 % 0xF;
        v5 = v6 / 0xF;
        LOBYTE(self->AudioBuffer_[2].isActive) = 0;
        LOBYTE(self->AudioBuffer_[2].dataSize) = v7 + 15;
        return v5;
      }
      v11 = ++v3;
    }
    while ( v3 < 2u );
    LOBYTE(v5) = ++v9;
    if ( v9 < 5u )
      continue;
    break;
  }
  LOBYTE(self->AudioBuffer_[2].isActive) = 0;
  return v5;
}


// 0x004b2510: AudioManager::IsSpecialCarModel
// IDA: AudioManager::IsSpecialCarModel
// Ghidra: ---
bool gta2::AudioManager_IsSpecialCarModel(struct AudioManager *self, Car *pCar)
{
  bool result; // al

  switch ( gta2::Car_GetModelCar(pCar) )
  {
    case APC:
    case COPCAR:
    case FireTruck:
    case GunJeep:
    case JEEP:
    case MEDICAR:
    case SWATVAN:
    case Tank:
    case EDSELFBI:
      result = 1;
      break;
    default:
      result = 0;
      break;
  }
  return result;
}


// 0x004b25a0: AudioManager::IsTransportOrCargo
// IDA: AudioManager::IsTransportOrCargo
// Ghidra: ---
bool gta2::AudioManager_IsTransportOrCargo(struct AudioManager *self, Car *pCar)
{
  bool result; // al
  CarModel ModelCar; // eax

  result = 0;
  if ( pCar )
  {
    ModelCar = gta2::Car_GetModelCar(pCar);
    if ( ModelCar == BOXCAR || ModelCar > TOWTRUCK && ModelCar <= TRAINFB )
      return 1;
  }
  return result;
}


// 0x004b25d0: AudioManager::sub_4B25D0
// IDA: AudioManager::sub_4B25D0
// Ghidra: ---
Car * gta2::AudioManager_sub_4B25D0(struct AudioManager *self, char streamIndex)
{
  char v3; // al
  char v4; // cl
  int v5; // eax
  unsigned int v6; // ebp
  unsigned int v7; // eax
  unsigned __int8 dataSize; // dl
  unsigned int v10; // edi
  int v11; // eax
  char a4; // [esp+10h] [ebp-4h]
  char a4a; // [esp+10h] [ebp-4h]

  v3 = 0;
  v4 = 0;
  if ( LOBYTE(self->AudioBuffer_[0].field_C) == HIBYTE(self->AudioBuffer_[0].field_C) )
  {
    dataSize = self->AudioBuffer_[1].dataSize;
    if ( dataSize != HIBYTE(self->AudioBuffer_[1].isActive) )
    {
      v3 = 1;
      v4 = 1;
    }
    if ( *(int *)((char *)&self->AudioBuffer_[1].endOffset + 2) == *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) )
    {
      if ( !v4 )
        return gta2::AudioManager_sub_4B1E40(self);
    }
    else if ( !v3 )
    {
      if ( gta2::SoundCard_sub_4B6960(&gSoundCard, 0) )
      {
        v10 = gta2::SoundCard_sub_4B6930(&gSoundCard, 0);
        gta2::SoundCard_CloseStreamByIndex(&gSoundCard, 0);
        a4a = *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) == 1;
        if ( HIBYTE(self->AudioBuffer_[1].isActive) == 101 )
          gta2::SoundCard_OpenVocal(&gSoundCard, 0, 101, a4a);
        else
          gta2::SoundCard_OpenVocal(&gSoundCard, 0, *(&self->field_5470 + 7 * HIBYTE(self->AudioBuffer_[1].isActive)), a4a);
        if ( streamIndex )
        {
          v11 = gta2::SoundCard_AIL_stream_playback_rate(&gSoundCard, 0);
          gta2::SoundCard_AIL_set_stream_playback_rate(&gSoundCard, 0, 2 * v11);
        }
        if ( v10 >= gta2::SoundCard_sub_4B6960(&gSoundCard, 0) )
          v10 = 0;
        gta2::SoundCard_sub_4B6910(&gSoundCard, 0, v10);
        return gta2::AudioManager_sub_4B1E40(self);
      }
      return (Car *)gta2::SoundCard_CloseStreamByIndex(&gSoundCard, 0);
    }
    if ( dataSize < 5u )
      *((_DWORD *)&self->gap5480 + 7 * LOBYTE(self->AudioBuffer_[1].dataSize)) = gta2::SoundCard_sub_4B6930(&gSoundCard, 0);
    gta2::SoundCard_CloseStreamByIndex(&gSoundCard, 0);
    a4 = *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) == 1;
  }
  else
  {
    a4 = *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) == 1;
    gta2::SoundCard_CloseStreamByIndex(&gSoundCard, 0);
  }
  if ( HIBYTE(self->AudioBuffer_[1].isActive) == 101 )
    gta2::SoundCard_OpenVocal(&gSoundCard, 0, 101, a4);
  else
    gta2::SoundCard_OpenVocal(&gSoundCard, 0, *(&self->field_5470 + 7 * HIBYTE(self->AudioBuffer_[1].isActive)), a4);
  gta2::SoundCard_SetStreamVolume_0(&gSoundCard, 0, 0);
  if ( streamIndex )
  {
    v5 = gta2::SoundCard_AIL_stream_playback_rate(&gSoundCard, 0);
    gta2::SoundCard_AIL_set_stream_playback_rate(&gSoundCard, 0, 2 * v5);
  }
  v6 = gta2::SoundCard_sub_4B6960(&gSoundCard, 0);
  if ( v6 )
  {
    v7 = *((_DWORD *)&self->gap5480 + 7 * HIBYTE(self->AudioBuffer_[1].isActive))
       + 1000 * *(&self->field_5478 + 7 * HIBYTE(self->AudioBuffer_[1].isActive)) / (unsigned int)self->field_8;
    if ( v7 > v6 )
      v7 %= v6;
    gta2::SoundCard_sub_4B6910(&gSoundCard, 0, v7);
    return gta2::AudioManager_sub_4B1E40(self);
  }
  return (Car *)gta2::SoundCard_CloseStreamByIndex(&gSoundCard, 0);
}


// 0x004b2830: AudioManager::sub_4B2830
// IDA: AudioManager::sub_4B2830
// Ghidra: ---
bool gta2::AudioManager_sub_4B2830(struct AudioManager *self)
{
  Car *ActivePlayerCar; // edi
  bool IsSpecialCarModel; // al
  unsigned __int8 v4; // al
  unsigned __int8 v5; // bl
  unsigned __int8 v6; // cl
  cGameObject *a2; // [esp+8h] [ebp-4h]
  unsigned __int8 a2a; // [esp+8h] [ebp-4h]
  unsigned __int8 a2b; // [esp+8h] [ebp-4h]
  unsigned __int8 a2c; // [esp+8h] [ebp-4h]

  ActivePlayerCar = gta2::Player_GetActivePlayerCar(gGame->PlayerMain);
  IsSpecialCarModel = gta2::AudioManager_IsSpecialCarModel(self, ActivePlayerCar);
  if ( IsSpecialCarModel )
  {
    *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) = 0;
    HIBYTE(self->AudioBuffer_[1].isActive) = 101;
  }
  else if ( ActivePlayerCar->field_B0 )
  {
    IsSpecialCarModel = gta2::AudioManager_sub_4B1E00(self, ActivePlayerCar->field_B0);
    HIBYTE(self->AudioBuffer_[1].isActive) = IsSpecialCarModel;
  }
  else
  {
    *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2) = 1;
    switch ( gta2::Car_GetModelCar(ActivePlayerCar) )
    {
      case BUICK:
        v4 = gta2::AudioManager_sub_4B1E00(self, 11);
        goto LABEL_13;
      case ISETTA:
        v4 = gta2::AudioManager_sub_4B1E00(self, 7);
        goto LABEL_13;
      case MIURA:
        v4 = gta2::AudioManager_sub_4B1E00(self, 6);
        goto LABEL_13;
      case PICKUP:
        v4 = gta2::AudioManager_sub_4B1E00(self, 8);
        goto LABEL_13;
      case STRATOSB:
        v4 = gta2::AudioManager_sub_4B1E00(self, 9);
        goto LABEL_13;
      case VTYPE:
        v4 = gta2::AudioManager_sub_4B1E00(self, 5);
        goto LABEL_13;
      case KRSNABUS:
        v4 = gta2::AudioManager_sub_4B1E00(self, 10);
LABEL_13:
        v5 = v4;
        LOBYTE(a2) = v4;
        if ( v4 == 127 )
          goto LABEL_14;
        goto LABEL_15;
      default:
LABEL_14:
        v5 = 0;
        LOBYTE(a2) = 0;
LABEL_15:
        IsSpecialCarModel = gta2::AudioManager_sub_4B2180(self, a2);
        if ( (unsigned __int8)IsSpecialCarModel >= 0x32u )
        {
          LOBYTE(self->AudioBuffer_[1].isActive) = IsSpecialCarModel;
LABEL_42:
          HIBYTE(self->AudioBuffer_[1].isActive) = v5;
        }
        else
        {
          switch ( self->field_1454 % 5u )
          {
            case 0u:
              v5 = 0;
              a2a = 0;
              do
              {
                *(_DWORD *)&IsSpecialCarModel = *(&self->field_5470 + 7 * a2a);
                if ( *(_DWORD *)&IsSpecialCarModel == 6
                  || *(int *)&IsSpecialCarModel > 8 && *(int *)&IsSpecialCarModel <= 10 )
                {
                  goto LABEL_42;
                }
                if ( v5 == 4 )
                {
                  IsSpecialCarModel = gta2::AudioManager_sub_4B1E00(self, 1);
                  HIBYTE(self->AudioBuffer_[1].isActive) = IsSpecialCarModel;
                }
                a2a = ++v5;
              }
              while ( v5 < 5u );
              break;
            case 1u:
              v5 = 0;
              a2b = 0;
              do
              {
                *(_DWORD *)&IsSpecialCarModel = *(&self->field_5470 + 7 * a2b);
                if ( *(int *)&IsSpecialCarModel >= 7
                  && (*(int *)&IsSpecialCarModel <= 8 || *(_DWORD *)&IsSpecialCarModel == 11) )
                {
                  goto LABEL_42;
                }
                if ( v5 == 4 )
                {
                  IsSpecialCarModel = gta2::AudioManager_sub_4B1E00(self, 1);
                  HIBYTE(self->AudioBuffer_[1].isActive) = IsSpecialCarModel;
                }
                a2b = ++v5;
              }
              while ( v5 < 5u );
              break;
            case 2u:
              IsSpecialCarModel = gta2::AudioManager_sub_4B1E00(self, 5);
              HIBYTE(self->AudioBuffer_[1].isActive) = IsSpecialCarModel;
              if ( IsSpecialCarModel == 127 )
                goto LABEL_34;
              break;
            case 3u:
              v6 = 0;
              a2c = 0;
              while ( 1 )
              {
                *(_DWORD *)&IsSpecialCarModel = (char *)self + 28 * a2c;
                if ( !*(_WORD *)(*(_DWORD *)&IsSpecialCarModel + 21624)
                  && *(_DWORD *)(*(_DWORD *)&IsSpecialCarModel + 21620) != 1 )
                {
                  break;
                }
                a2c = ++v6;
                if ( v6 >= 5u )
                  return IsSpecialCarModel;
              }
              HIBYTE(self->AudioBuffer_[1].isActive) = v6;
              break;
            default:
LABEL_34:
              IsSpecialCarModel = gta2::AudioManager_sub_4B1E00(self, 1);
              HIBYTE(self->AudioBuffer_[1].isActive) = IsSpecialCarModel;
              break;
          }
        }
        break;
    }
  }
  return IsSpecialCarModel;
}


// 0x004b2ad0: AudioManager::sub_4B2AD0
// IDA: AudioManager::sub_4B2AD0
// Ghidra: ---
void gta2::AudioManager_sub_4B2AD0(AudioManager *a1)
{
  AudioManager *v1; // esi
  char *v2; // eax
  char v3; // al
  cGameObject *v4; // edx
  cGameObject *v5; // eax
  cGameObject *v6; // edx

  v1 = a1;
  LOBYTE(a1) = HIBYTE(a1->AudioBuffer_[1].isActive);
  if ( (_BYTE)a1 == 101 )
  {
    LOBYTE(v1->AudioBuffer_[1].isActive) = 115;
    return;
  }
  v2 = &v1->AudioObject + 28 * (unsigned __int8)a1;
  if ( *((_DWORD *)v2 + 5405) && v2[21608] == 1 )
  {
    if ( !*(int *)((char *)&v1->AudioBuffer_[1].sampleRate + 2) )
    {
      v3 = gta2::AudioManager_sub_4B2180(v1, (cGameObject *)a1);
      if ( (unsigned __int8)v3 <= 0x6Eu )
      {
        LOBYTE(v4) = HIBYTE(v1->AudioBuffer_[1].isActive);
        LOBYTE(v1->AudioBuffer_[1].isActive) = gta2::AudioManager_sub_4B2180(v1, v4);
        return;
      }
      *(int *)((char *)&v1->AudioBuffer_[1].sampleRate + 2) = 1;
      goto LABEL_11;
    }
    if ( (unsigned __int8)gta2::AudioManager_sub_4B2180(v1, (cGameObject *)a1) < 0x5Au )
    {
      LOBYTE(v5) = HIBYTE(v1->AudioBuffer_[1].isActive);
      v3 = gta2::AudioManager_sub_4B2180(v1, v5);
      *(int *)((char *)&v1->AudioBuffer_[1].sampleRate + 2) = 0;
LABEL_11:
      LOBYTE(v1->AudioBuffer_[1].isActive) = v3;
      LOBYTE(v1->AudioBuffer_[2].dataSize) = v1->field_1454 % 0xAu + 16;
      return;
    }
    LOBYTE(v6) = HIBYTE(v1->AudioBuffer_[1].isActive);
    LOBYTE(v1->AudioBuffer_[1].isActive) = gta2::AudioManager_sub_4B2180(v1, v6);
    *(int *)((char *)&v1->AudioBuffer_[1].sampleRate + 2) = 1;
  }
  else
  {
    LOBYTE(v1->AudioBuffer_[1].isActive) = 0;
  }
}


// 0x004b2bc0: AudioManager::sub_4B2BC0
// IDA: AudioManager::sub_4B2BC0
// Ghidra: ---
__int16 gta2::AudioManager_sub_4B2BC0(struct AudioManager *self, int a2, int a3, int a4)
{
  unsigned __int8 v5; // cl
  char *v6; // eax
  char *v7; // edi
  unsigned __int16 v8; // ax
  unsigned __int16 v9; // ax
  int v10; // eax
  unsigned __int8 v12; // [esp+8h] [ebp-4h]

  v5 = 0;
  v12 = 0;
  while ( 1 )
  {
    v6 = &self->AudioObject + 28 * v12;
    if ( !v6[21608] && !*((_WORD *)v6 + 10812) && !*((_WORD *)v6 + 10813) )
      break;
    v12 = ++v5;
    if ( v5 >= 5u )
      return (__int16)v6;
  }
  v7 = &self->AudioObject + 28 * v12;
  *((_DWORD *)v7 + 5405) = a2;
  v7[21608] = 1;
  v8 = gta2::sub_41F9E0(&a3);
  gta2::sub_41F990(&a3, v8);
  *((_DWORD *)v7 + 5403) = a3;
  v9 = gta2::sub_41F9E0(&a4);
  gta2::sub_41F990(&a3, v9);
  *(&self->field_546C + 7 * v12) = a3;
  v10 = *(&self->field_1454 + v12 % 5) * *(&self->field_1454 + (v12 + 1) % 5);
  *((_DWORD *)v7 + 5408) = v10;
  *((_DWORD *)v7 + 5407) = v10;
  LOWORD(v6) = sub_4B22B0((int)(v7 + 21608), a2);
  return (__int16)v6;
}


// 0x004b2d50: AudioManager::sub_4B2D50
// IDA: AudioManager::sub_4B2D50
// Ghidra: ---
char gta2::AudioManager_sub_4B2D50(struct AudioManager *self)
{
  unsigned __int8 dataSize; // al
  int v2; // ecx
  unsigned int v3; // edx
  Game *result; // eax
  char v6; // al
  int v7; // edx
  Car *ActivePlayerCar; // eax
  Car *pCar; // edi
  bool IsTransportOrCargo; // bl
  bool FullDamage; // al
  char v12; // al
  char v13; // al
  char v14; // al

  if ( unk_66BEED )
    --unk_66BEED;
  LOBYTE(result) = (_BYTE)gGame;
  if ( gGame && gGame->PlayerMain )
  {
    if ( self->IsUserPaused )
      gta2::SoundCard_sub_4B6A60(&gSoundCard);
    else
      gta2::AudioManager_sub_41C600(self);
    LOBYTE(result) = gta2::SoundCard_Get_isStreamActive(&gSoundCard);
    if ( (_BYTE)result )
    {
      v6 = HIBYTE(self->AudioBuffer_[0].field_C);
      v7 = *(int *)((char *)&self->AudioBuffer_[1].sampleRate + 2);
      LOBYTE(self->AudioBuffer_[1].dataSize) = HIBYTE(self->AudioBuffer_[1].isActive);
      LOBYTE(self->AudioBuffer_[0].field_C) = v6;
      *(int *)((char *)&self->AudioBuffer_[1].endOffset + 2) = v7;
      gta2::AudioManager_sub_4B1D40(self);
      ActivePlayerCar = gta2::Player_GetActivePlayerCar(gGame->PlayerMain);
      pCar = ActivePlayerCar;
      if ( !ActivePlayerCar
        || (IsTransportOrCargo = gta2::AudioManager_IsTransportOrCargo(self, ActivePlayerCar),
            FullDamage = gta2::Car_GetFullDamage(pCar),
            IsTransportOrCargo)
        || FullDamage )
      {
        v14 = self->AudioBuffer_[0].field_C;
        HIBYTE(self->AudioBuffer_[0].field_C) = 0;
        if ( v14 == 1 )
        {
          if ( unk_66C274 )
            *(_DWORD *)(unk_66C274 + 176) = *(&self->field_5470 + 7 * HIBYTE(self->AudioBuffer_[1].isActive));
          if ( LOBYTE(self->AudioBuffer_[1].dataSize) < 5u )
            *(&self->field_5478 + 7 * LOBYTE(self->AudioBuffer_[1].dataSize)) = 0;
        }
        HIBYTE(self->AudioBuffer_[1].isActive) = 102;
        if ( HIBYTE(self->AudioBuffer_[1].isActive) != 102 || (dataSize = self->AudioBuffer_[1].dataSize, dataSize == 102) )
        {
          v2 = *(int *)((char *)&self->AudioBuffer_[3].endOffset + 2);
          if ( v2 )
          {
            v3 = 60 * (60 - v2) / 0x3Cu;
            if ( self->IsUserPaused )
            {
              if ( v3 > 0x1E )
                v3 = 30;
            }
            else
            {
              *(int *)((char *)&self->AudioBuffer_[3].endOffset + 2) = v2 - 1;
            }
            gta2::SoundCard_SetStreamVolume_0(&gSoundCard, 0, v3 * self->SFXVol / 0x7F);
          }
          else if ( self->IsUserPaused )
          {
            gta2::SoundCard_SetStreamVolume_0(&gSoundCard, 0, 30 * self->SFXVol / 127);
          }
          else
          {
            gta2::SoundCard_SetStreamVolume_0(&gSoundCard, 0, (char)(60 * self->SFXVol) / 127);
          }
        }
        else
        {
          if ( dataSize < 5u )
            *((_DWORD *)&self->gap5480 + 7 * LOBYTE(self->AudioBuffer_[1].dataSize)) = gta2::SoundCard_sub_4B6930(
                                                                                        &gSoundCard,
                                                                                        0);
          gta2::SoundCard_CloseStreamByIndex(&gSoundCard, 0);
          gta2::SoundCard_OpenVocal(&gSoundCard, 0, 12, 1);
          gta2::SoundCard_SetStreamVolume_0(&gSoundCard, 0, 0);
          result = (Game *)gta2::SoundCard_sub_4B6960(&gSoundCard, 0);
          if ( result )
            LOBYTE(result) = gta2::SoundCard_sub_4B6910(&gSoundCard, 0, self->field_145C % (unsigned int)result);
          *(int *)((char *)&self->AudioBuffer_[3].endOffset + 2) = 60;
        }
      }
      else
      {
        v12 = self->AudioBuffer_[0].field_C;
        HIBYTE(self->AudioBuffer_[0].field_C) = 1;
        if ( v12 )
        {
          if ( LOBYTE(self->AudioBuffer_[2].isActive) )
          {
            if ( HIBYTE(self->AudioBuffer_[1].isActive) < 5u )
              *(&self->field_5478 + 7 * HIBYTE(self->AudioBuffer_[1].isActive)) = 0;
            gta2::AudioManager_sub_4B2420(self);
          }
          else
          {
            gta2::AudioManager_sub_4B2AD0(self);
          }
        }
        else
        {
          gta2::AudioManager_sub_4B2830(self);
          gta2::AudioManager_sub_4B2AD0(self);
          LOBYTE(self->AudioBuffer_[2].dataSize) = 0;
        }
        if ( !LOBYTE(self->AudioBuffer_[1].isActive) )
        {
          LOBYTE(self->AudioBuffer_[2].isActive) = 1;
          gta2::AudioManager_sub_4B2420(self);
          LOBYTE(self->AudioBuffer_[2].dataSize) = 0;
        }
        v13 = gta2::Car_sub_403820((Car *)&pCar->field_68, &dword_66BF7C);
        LOBYTE(result) = (unsigned __int8)gta2::AudioManager_sub_4B25D0(self, v13);
        unk_66C274 = pCar;
      }
    }
  }
  return (char)result;
}



