#include "gta2_shim.h"

// Module: other, Class: SoundCard
// Functions: 58
// Source: unified (IDA+Ghidra)

// 0x004b5f70: SoundCard::AcquireSampleHandle
// IDA: SoundCard::AcquireSampleHandle
// Ghidra: ---
int gta2::SoundCard_AcquireSampleHandle(struct SoundCard *self)
{
  int result; // eax
  int sample_handle; // eax

  result = self->SampleStatus;
  if ( !result )
  {
    sample_handle = AIL_allocate_sample_handle(self->AudioStream);
    self->SampleStatus = sample_handle;
    AIL_init_sample(sample_handle);
    return AIL_set_sample_type(self->SampleStatus, PCM_FORMAT, 0);
  }
  return result;
}


// 0x004b5fb0: SoundCard::ReleaseSampleHandle
// IDA: SoundCard::ReleaseSampleHandle
// Ghidra: ---
int gta2::SoundCard_ReleaseSampleHandle(struct SoundCard *self)
{
  int result; // eax

  result = self->SampleStatus;
  if ( result )
  {
    result = AIL_release_sample_handle(self->SampleStatus);
    self->SampleStatus = 0;
  }
  return result;
}


// 0x004b5fd0: SoundCard::ReleaseAllSampleHandles
// IDA: SoundCard::ReleaseAllSampleHandles
// Ghidra: ---
byte gta2::SoundCard_ReleaseAllSampleHandles(struct SoundCard *self)
{
  unsigned __int8 v2; // bl
  byte result; // al
  unsigned __int8 v4; // [esp+8h] [ebp-4h]

  v2 = 0;
  v4 = 0;
  result = self->totalSamples;
  if ( result )
  {
    do
    {
      AIL_release_sample_handle(*(_DWORD *)&self->sampleHandles[4 * v4]);
      *(_DWORD *)&self->sampleHandles[4 * v4] = 0;
      result = self->totalSamples;
      v4 = ++v2;
    }
    while ( v2 < result );
  }
  return result;
}


// 0x004b6020: SoundCard::GetHZ
// IDA: SoundCard::GetHZ
// Ghidra: ---
int gta2::SoundCard_GetHZ(struct SoundCard *self, int a2)
{
  int result; // eax

  result = *(_DWORD *)&self->field_B0[24 * a2];
  if ( !result )
    return 1;
  return result;
}


// 0x004b6040: SoundCard::sub_4B6040
// IDA: SoundCard::sub_4B6040
// Ghidra: ---
int gta2::SoundCard_sub_4B6040(struct SoundCard *self, int a2)
{
  return *(_DWORD *)&self->field_B4[24 * a2];
}


// 0x004b6060: SoundCard::sub_4B6060
// IDA: SoundCard::sub_4B6060
// Ghidra: ---
int gta2::SoundCard_sub_4B6060(struct SoundCard *self, int a2)
{
  return *(_DWORD *)&self->field_B8[24 * a2];
}


// 0x004b6080: SoundCard::sub_4B6080
// IDA: SoundCard::sub_4B6080
// Ghidra: ---
int gta2::SoundCard_sub_4B6080(struct SoundCard *self, int a2)
{
  return *(_DWORD *)&self->field_BC[24 * a2];
}


// 0x004b60a0: SoundCard::sub_4B60A0
// IDA: SoundCard::sub_4B60A0
// Ghidra: ---
int gta2::SoundCard_sub_4B60A0(struct SoundCard *self, int a2)
{
  return *(_DWORD *)&self->field_AC[24 * a2];
}


// 0x004b60c0: SoundCard::SetSampleAddress
// IDA: SoundCard::SetSampleAddress
// Ghidra: ---
char gta2::SoundCard_SetSampleAddress(struct SoundCard *self, int a2, int a3)
{
  char result; // al
  int v4; // edx

  result = a2;
  v4 = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( v4 )
  {
    result = self->field_A4;
    if ( result )
      return AIL_set_sample_address(
               v4,
               self->memoryBuffer + *((_DWORD *)&self->field_A8 + 6 * a3),
               *(_DWORD *)&self->field_AC[24 * a3]);
  }
  return result;
}


// 0x004b6110: SoundCard::SetSampleVolume
// IDA: SoundCard::SetSampleVolume
// Ghidra: ---
int gta2::SoundCard_SetSampleVolume(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_set_sample_volume(self, *(_DWORD *)&self->sampleHandles[4 * a2], a3);
  return result;
}


// 0x004b6130: SoundCard::SetSamplePan
// IDA: SoundCard::SetSamplePan
// Ghidra: ---
int gta2::SoundCard_SetSamplePan(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_set_sample_pan(self, *(_DWORD *)&self->sampleHandles[4 * a2], a3);
  return result;
}


// 0x004b6150: SoundCard::SetSamplePlaybackRate
// IDA: SoundCard::SetSamplePlaybackRate
// Ghidra: ---
int gta2::SoundCard_SetSamplePlaybackRate(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_set_sample_playback_rate(self, *(_DWORD *)&self->sampleHandles[4 * a2], a3);
  return result;
}


// 0x004b6170: SoundCard::SetSampleLoopBlock
// IDA: SoundCard::SetSampleLoopBlock
// Ghidra: ---
int gta2::SoundCard_SetSampleLoopBlock(struct SoundCard *self, int a2, int a3, int a4)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_set_sample_loop_block(self, *(_DWORD *)&self->sampleHandles[4 * a2], a3, a4);
  return result;
}


// 0x004b6190: SoundCard::SetSampleLoopCount
// IDA: SoundCard::SetSampleLoopCount
// Ghidra: ---
int gta2::SoundCard_SetSampleLoopCount(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_set_sample_loop_count(self, *(_DWORD *)&self->sampleHandles[4 * a2], a3);
  return result;
}


// 0x004b61b0: SoundCard::sub_4B61B0
// IDA: SoundCard::sub_4B61B0
// Ghidra: ---
bool gta2::SoundCard_sub_4B61B0(struct SoundCard *self, int a2)
{
  return *(_DWORD *)&self->sampleHandles[4 * a2] && AIL_sample_status(*(_DWORD *)&self->sampleHandles[4 * a2]) == 4;
}


// 0x004b61e0: SoundCard::StartSample
// IDA: SoundCard::StartSample
// Ghidra: ---
int gta2::SoundCard_StartSample(struct SoundCard *self, int a2)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_start_sample(self, *(_DWORD *)&self->sampleHandles[4 * a2]);
  return result;
}


// 0x004b6200: SoundCard::StopSample
// IDA: SoundCard::StopSample
// Ghidra: ---
int gta2::SoundCard_StopSample(struct SoundCard *self, int a2)
{
  int result; // eax

  result = *(_DWORD *)&self->sampleHandles[4 * a2];
  if ( result )
    return AIL_end_sample(self, *(_DWORD *)&self->sampleHandles[4 * a2]);
  return result;
}


// 0x004b6220: SoundCard::Set3DSampleInfo
// IDA: SoundCard::Set3DSampleInfo
// Ghidra: ---
bool gta2::SoundCard_Set3DSampleInfo(struct SoundCard *self, int a2, int a3, int a4)
{
  int v4; // edx
  int memoryBuffer; // esi
  int v6; // edi
  int v7; // eax
  _DWORD v9[9]; // [esp+0h] [ebp-24h] BYREF

  v4 = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( !v4 || !self->field_A4 )
    return 0;
  memoryBuffer = self->memoryBuffer;
  v9[0] = 1;
  v9[5] = 1;
  v6 = *((_DWORD *)&self->field_A8 + 6 * a3);
  v9[2] = *(_DWORD *)&self->field_AC[24 * a3];
  v9[3] = a4;
  v7 = 8 * self->AudioChannels;
  v9[1] = memoryBuffer + v6;
  v9[4] = v7;
  return AIL_set_3D_sample_info(v4, v9) != 0;
}


// 0x004b62b0: SoundCard::Set3DSampleVolume
// IDA: SoundCard::Set3DSampleVolume
// Ghidra: ---
int gta2::SoundCard_Set3DSampleVolume(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_set_3D_sample_volume(self, *(_DWORD *)&self->sample3DHandles[4 * a2], a3);
  return result;
}


// 0x004b62d0: SoundCard::Set3DPosition
// IDA: SoundCard::Set3DPosition
// Ghidra: ---
int gta2::SoundCard_Set3DPosition(struct SoundCard *self, int a2, int a3, int a4, int a5)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_set_3D_position(self, *(_DWORD *)&self->sample3DHandles[4 * a2], a3, a4, a5);
  return result;
}


// 0x004b62f0: SoundCard::Set3DSampleFloatDistances
// IDA: SoundCard::Set3DSampleFloatDistances
// Ghidra: ---
int gta2::SoundCard_Set3DSampleFloatDistances(struct SoundCard *self, int a2, int a3, int a4)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_set_3D_sample_float_distances(result, a3, a4, a3, a4);
  return result;
}


// 0x004b6320: SoundCard::Set3DSamplePlaybackRate
// IDA: SoundCard::Set3DSamplePlaybackRate
// Ghidra: ---
int gta2::SoundCard_Set3DSamplePlaybackRate(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_set_3D_sample_playback_rate(self, *(_DWORD *)&self->sample3DHandles[4 * a2], a3);
  return result;
}


// 0x004b6340: SoundCard::Set3DSampleLoopBlock
// IDA: SoundCard::Set3DSampleLoopBlock
// Ghidra: ---
int gta2::SoundCard_Set3DSampleLoopBlock(struct SoundCard *self, int a2, int a3, int a4)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_set_3D_sample_loop_block(self, *(_DWORD *)&self->sample3DHandles[4 * a2], a3, a4);
  return result;
}


// 0x004b6360: SoundCard::Set3DSampleLoopCount
// IDA: SoundCard::Set3DSampleLoopCount
// Ghidra: ---
int gta2::SoundCard_Set3DSampleLoopCount(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_set_3D_sample_loop_count(self, *(_DWORD *)&self->sample3DHandles[4 * a2], a3);
  return result;
}


// 0x004b6380: SoundCard::sub_4B6380
// IDA: SoundCard::sub_4B6380
// Ghidra: ---
bool gta2::SoundCard_sub_4B6380(struct SoundCard *self, int a2)
{
  return *(_DWORD *)&self->sample3DHandles[4 * a2]
      && AIL_3D_sample_status(*(_DWORD *)&self->sample3DHandles[4 * a2]) == 4;
}


// 0x004b63b0: SoundCard::Start3DSample
// IDA: SoundCard::Start3DSample
// Ghidra: ---
int gta2::SoundCard_Start3DSample(struct SoundCard *self, int a2)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
    return AIL_start_3D_sample(self, *(_DWORD *)&self->sample3DHandles[4 * a2]);
  return result;
}


// 0x004b63d0: SoundCard::CheckAndStop3DSample
// IDA: SoundCard::CheckAndStop3DSample
// Ghidra: ---
int gta2::SoundCard_CheckAndStop3DSample(struct SoundCard *self, int a2)
{
  int result; // eax

  result = *(_DWORD *)&self->sample3DHandles[4 * a2];
  if ( result )
  {
    result = AIL_3D_sample_status(*(_DWORD *)&self->sample3DHandles[4 * a2]);
    if ( result == 4 )
      return AIL_end_3D_sample(*(_DWORD *)&self->sample3DHandles[4 * a2]);
  }
  return result;
}


// 0x004b6420: SoundCard::SetEAXEnvironment
// IDA: SoundCard::SetEAXEnvironment
// Ghidra: ---
int gta2::SoundCard_SetEAXEnvironment(struct SoundCard *self, int providerFlags)
{
  int result; // eax

  result = self->current3DProvider;
  if ( result && self->environmentPreset && providerFlags < 26 )
  {
    self->providerFlags = providerFlags;
    return AIL_set_3D_provider_preference(result, "EAX environment selection", &providerFlags);
  }
  return result;
}


// 0x004b6550: SoundCard::Open3DProviderForListener
// IDA: SoundCard::Open3DProviderForListener
// Ghidra: ---
char gta2::SoundCard_Open3DProviderForListener(struct SoundCard *self, int pListenerID)
{
  int ListenerID; // edi
  bool eaxPreset; // zf
  int v6; // [esp-Ch] [ebp-14h]

  ListenerID = pListenerID;
  eaxPreset = pListenerID == -1;
  self->listenerID = pListenerID;
  if ( eaxPreset )
    return 0;
  pListenerID = AIL_open_3D_provider(self->providerList[ListenerID]);
  if ( pListenerID )
  {
    self->listenerID = -1;
    return 0;
  }
  v6 = self->providerList[ListenerID];
  self->current3DProvider = v6;
  AIL_3D_provider_attribute(v6, "EAX environment selection", &pListenerID);
  if ( pListenerID != -1 )
  {
    self->environmentPreset = 1;
    gta2::SoundCard_SetEAXEnvironment(self, 17);
  }
  return 1;
}


// 0x004b65d0: SoundCard::Shutdown3DAudio
// IDA: SoundCard::Shutdown3DAudio
// Ghidra: ---
void gta2::SoundCard_Shutdown3DAudio(struct SoundCard *self)
{
  if ( self->current3DProvider )
  {
    AIL_close_3D_provider(self->current3DProvider);
    self->current3DProvider = 0;
    Sleep(1500u);
  }
}


// 0x004b6600: SoundCard::Enumerate3DAudioProviders
// IDA: SoundCard::Enumerate3DAudioProviders
// Ghidra: ---
void gta2::SoundCard_Enumerate3DAudioProviders(struct SoundCard *self)
{
  char *providerCount; // edi
  int *currentProviderEntry; // esi
  char *v4; // eax
  const char *v5; // ecx
  int providerIndex; // [esp+10h] [ebp-8h] BYREF
  const char *providerName; // [esp+14h] [ebp-4h] BYREF

  providerCount = 0;
  providerIndex = 0;
  currentProviderEntry = &self->currentProviderEntry;
  do
  {
    if ( !AIL_enumerate_3D_providers(&providerIndex, currentProviderEntry - 256, &providerName) )
      break;
    v4 = (char *)new(0x50u);
    v5 = providerName;
    *currentProviderEntry = (int)v4;
    strcpy(v4, v5);
    ++providerCount;
    ++currentProviderEntry;
  }
  while ( (unsigned int)providerCount < 256 );
  self->total3DProviders = providerCount;
}


// 0x004b66a0: SoundCard::StreamStatus
// IDA: SoundCard::StreamStatus
// Ghidra: ---
bool gta2::SoundCard_StreamStatus(struct SoundCard *self)
{
  if ( !self->isStreamActive )
    return 0;
  if ( self->stream_volume[0] )
    return AIL_stream_status(self->stream_volume[0]) == 2;
  return 1;
}


// 0x004b66d0: SoundCard::SetStreamVolume
// IDA: SoundCard::SetStreamVolume
// Ghidra: ---
void gta2::SoundCard_SetStreamVolume(struct SoundCard *self, unsigned __int8 a2)
{
  int v2; // eax

  if ( self->isStreamActive )
  {
    v2 = self->stream_volume[0];
    if ( v2 )
      AIL_set_stream_volume((SoundCard *)a2, v2, a2);
  }
}


// 0x004b6700: SoundCard::sub_4B6700
// IDA: SoundCard::sub_4B6700
// Ghidra: ---
char gta2::SoundCard_sub_4B6700(struct SoundCard *self, unsigned int a2)
{
  int v3; // eax
  char *v4; // eax
  char v5; // cl
  unsigned int v6; // eax
  char *v7; // edi
  char v10; // [esp+3h] [ebp-51h] BYREF
  _BYTE v11[80]; // [esp+4h] [ebp-50h] BYREF

  LOBYTE(v3) = self->isStreamActive;
  if ( (_BYTE)v3 )
  {
    v3 = self->stream_volume[0];
    if ( !v3 && a2 < 3 )
    {
      v4 = &self->Path[1];
      do
      {
        v5 = *v4;
        v4[v11 - &self->Path[1]] = *v4;
        ++v4;
      }
      while ( v5 );
      v6 = 6 * a2 + strlen((const char *)(6 * a2 + 5722644)) + 1 - 6 * a2;
      v7 = &v10;
      while ( *++v7 )
        ;
      qmemcpy(v7, (const void *)(6 * a2 + 5722644), v6);
      v3 = AIL_open_stream(self->AudioStream, v11, 0);
      self->stream_volume[0] = v3;
      if ( v3 )
      {
        AIL_set_stream_loop_count(v3, 0);
        LOBYTE(v3) = AIL_start_stream(self->stream_volume[0]);
      }
    }
  }
  return v3;
}


// 0x004b67b0: SoundCard::CloseStream
// IDA: SoundCard::CloseStream
// Ghidra: ---
void gta2::SoundCard_CloseStream(struct SoundCard *self)
{
  if ( self->isStreamActive )
  {
    if ( self->stream_volume[0] )
    {
      AIL_close_stream(self->stream_volume[0]);
      self->stream_volume[0] = 0;
    }
  }
}


// 0x004b67e0: SoundCard::FadeOutAndCloseStream
// IDA: SoundCard::FadeOutAndCloseStream
// Ghidra: ---
char gta2::SoundCard_FadeOutAndCloseStream(struct SoundCard *self)
{
  int v2; // eax
  SoundCard *v3; // ecx
  unsigned __int8 v4; // si
  int v5; // ebx
  unsigned __int8 v7; // [esp+4h] [ebp-4h]

  LOBYTE(v2) = self->isStreamActive;
  if ( (_BYTE)v2 )
  {
    v2 = self->stream_volume[0];
    if ( v2 )
    {
      v7 = AIL_stream_volume(self->stream_volume[0]);
      if ( v7 )
      {
        v4 = v7;
        v5 = v7;
        do
        {
          AIL_set_stream_volume(v3, self->stream_volume[0], v4);
          AIL_delay(1);
          --v4;
          --v5;
        }
        while ( v5 );
      }
      LOBYTE(v2) = AIL_close_stream(self->stream_volume[0]);
      self->stream_volume[0] = 0;
    }
  }
  return v2;
}


// 0x004b6850: SoundCard::Get_isStreamActive
// IDA: SoundCard::Get_isStreamActive
// Ghidra: ---
char gta2::SoundCard_Get_isStreamActive(struct SoundCard *self)
{
  return self->isStreamActive;
}


// 0x004b6860: SoundCard::CloseStreamByIndex
// IDA: SoundCard::CloseStreamByIndex
// Ghidra: ---
int gta2::SoundCard_CloseStreamByIndex(struct SoundCard *self, int streamIndex)
{
  int result; // eax

  result = self->stream_volume[streamIndex];
  if ( result )
  {
    result = AIL_close_stream(self->stream_volume[streamIndex]);
    self->stream_volume[streamIndex] = 0;
  }
  return result;
}


// 0x004b6890: SoundCard::SetStreamVolume_0
// IDA: SoundCard::SetStreamVolume_0
// Ghidra: ---
void gta2::SoundCard_SetStreamVolume_0(struct SoundCard *self, int a2, unsigned __int8 Value)
{
  if ( self->stream_volume[a2] )
    AIL_set_stream_volume((SoundCard *)Value, self->stream_volume[a2], Value);
}


// 0x004b68c0: SoundCard::AIL_set_stream_playback_rate
// IDA: SoundCard::AIL_set_stream_playback_rate
// Ghidra: ---
int gta2::SoundCard_AIL_set_stream_playback_rate(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = self->stream_volume[a2];
  if ( result )
    return AIL_set_stream_playback_rate(self->stream_volume[a2], a3);
  return result;
}


// 0x004b68e0: SoundCard::AIL_stream_playback_rate
// IDA: SoundCard::AIL_stream_playback_rate
// Ghidra: ---
int gta2::SoundCard_AIL_stream_playback_rate(struct SoundCard *self, int a2)
{
  if ( self->stream_volume[a2] )
    return AIL_stream_playback_rate(self->stream_volume[a2]);
  else
    return 22050;
}


// 0x004b6910: SoundCard::sub_4B6910
// IDA: SoundCard::sub_4B6910
// Ghidra: ---
int gta2::SoundCard_sub_4B6910(struct SoundCard *self, int a2, int a3)
{
  int result; // eax

  result = self->stream_volume[a2];
  if ( result )
    return AIL_set_stream_ms_position(self, self->stream_volume[a2], a3);
  return result;
}


// 0x004b6930: SoundCard::sub_4B6930
// IDA: SoundCard::sub_4B6930
// Ghidra: ---
int gta2::SoundCard_sub_4B6930(_DWORD *self, int a2)
{
  int v2; // eax

  v2 = self[a2 + 39];
  if ( !v2 )
    return 0;
  AIL_stream_ms_position(v2, 0, &a2);
  return a2;
}


// 0x004b6960: SoundCard::sub_4B6960
// IDA: SoundCard::sub_4B6960
// Ghidra: ---
int gta2::SoundCard_sub_4B6960(struct SoundCard *self, int a2)
{
  int v2; // eax

  v2 = self->stream_volume[a2];
  if ( !v2 )
    return 0;
  AIL_stream_ms_position(v2, &a2, 0);
  return a2;
}


// 0x004b6990: SoundCard::SetSampleVolume_0
// IDA: SoundCard::SetSampleVolume_0
// Ghidra: ---
void gta2::SoundCard_SetSampleVolume_0(struct SoundCard *self, unsigned __int8 a2)
{
  int SampleStatus; // eax

  SampleStatus = self->SampleStatus;
  if ( SampleStatus )
    AIL_set_sample_volume((SoundCard *)a2, SampleStatus, a2);
}


// 0x004b6a40: SoundCard::GetSampleStatus
// IDA: SoundCard::GetSampleStatus
// Ghidra: ---
bool gta2::SoundCard_GetSampleStatus(struct SoundCard *self)
{
  return AIL_sample_status(self->SampleStatus) != 2;
}


// 0x004b6a60: SoundCard::sub_4B6A60
// IDA: SoundCard::sub_4B6A60
// Ghidra: ---
int gta2::SoundCard_sub_4B6A60(struct SoundCard *self)
{
  int result; // eax

  result = self->SampleStatus;
  if ( result )
    return AIL_end_sample(self, self->SampleStatus);
  return result;
}


// 0x004b6a80: SoundCard::sub_4B6A80
// IDA: SoundCard::sub_4B6A80
// Ghidra: ---
void gta2::SoundCard_sub_4B6A80(struct SoundCard *self, unsigned int a2, unsigned int a3)
{
  SoundCard *v4; // ecx
  SoundCard *v5; // ecx

  if ( a2 < a3 && self->SampleStatus && !gta2::SoundCard_GetSampleStatus(self) )
  {
    if ( self->field_A4 )
    {
      AIL_set_sample_address(
        self->SampleStatus,
        self->memoryBuffer + *((_DWORD *)&self->field_A8 + 6 * a2),
        *((_DWORD *)&self->field_A8 + 6 * a3) - *((_DWORD *)&self->field_A8 + 6 * a2));
      AIL_set_sample_playback_rate((SoundCard *)self->SampleStatus, self->SampleStatus, 18050);
      AIL_set_sample_pan(v4, self->SampleStatus, 64);
      AIL_set_sample_loop_count(v5, self->SampleStatus, 1);
      AIL_start_sample((SoundCard *)self->SampleStatus, self->SampleStatus);
    }
  }
}


// 0x004b6b20: SoundCard::EndSample
// IDA: SoundCard::EndSample
// Ghidra: ---
int gta2::SoundCard_EndSample(struct SoundCard *self)
{
  int result; // eax

  result = self->SampleStatus;
  if ( result )
    return AIL_end_sample(self, self->SampleStatus);
  return result;
}


// 0x004b6b40: SoundCard::LoadSounds
// IDA: SoundCard::LoadSounds
// Ghidra: ---
char gta2::SoundCard_LoadSounds(struct SoundCard *self, const char *buffer)
{
  unsigned int v2; // eax
  char *v3; // edi
  unsigned int v4; // ecx
  FILE *v5; // eax
  FILE *v6; // esi
  size_t v7; // edi
  SoundCard *v9; // ebx
  FILE *v10; // edi
  int v11; // [esp+0h] [ebp-B4h] BYREF
  SoundCard *v12; // [esp+10h] [ebp-A4h]
  CHAR FileName[8]; // [esp+14h] [ebp-A0h] BYREF
  _BYTE v14[7]; // [esp+1Ch] [ebp-98h] BYREF
  const unsigned __int16 *v15; // [esp+23h] [ebp-91h]
  CHAR v16[11]; // [esp+64h] [ebp-50h] BYREF
  int v17; // [esp+6Fh] [ebp-45h]
  char *v18; // [esp+73h] [ebp-41h]

  self->field_A4 = 0;
  *(_DWORD *)v14 = &unk_5C6F69;
  v12 = self;
  qmemcpy(FileName, "data\\aud", sizeof(FileName));
  v2 = strlen(buffer) + 1;
  qmemcpy(&v14[3], buffer, v2);
  v3 = &v14[v2 + 2];
  strcpy(v3, ".RAW");
  v4 = v3 - (char *)&v11 - 20;
  qmemcpy(v16, FileName, v4);
  strcpy(&v16[v4], ".SDT");
  v5 = gta2::FileMgr_WriteReadFile(FileName, "rb");
  if ( !v5 )
  {
    *(_DWORD *)&v14[3] = 776751426;
    v15 = L"p";
    v5 = gta2::FileMgr_WriteReadFile(FileName, "rb");
    if ( !v5 )
      return 0;
  }
  v6 = v5;
  gta2::_fseek(v5, 0, 2);
  v7 = gta2::_ftell(v6);
  if ( v7 > (unsigned int)&gBufferSize )
  {
    fclose(v6);
    return 0;
  }
  gta2::sub_4D8245(v6);
  v9 = v12;
  gta2::_fread((const void *)v12->allocatedMemory, 1u, v7, v6);
  fclose(v6);
  v10 = gta2::FileMgr_WriteReadFile(v16, "rb");
  if ( !v10 )
  {
    v17 = 776751426;
    v18 = (char *)sub_544450 + 3;
    v10 = gta2::FileMgr_WriteReadFile(v16, "rb");
    if ( !v10 )
      fclose(v6);
  }
  gta2::_fread(&v9->field_A8, 0x18u, 0x140u, v10);
  fclose(v10);
  v9->field_A4 = 1;
  return 1;
}


// 0x004b6ce0: SoundCard::sub_4B6CE0
// IDA: SoundCard::sub_4B6CE0
// Ghidra: ---
char * gta2::SoundCard_sub_4B6CE0(struct SoundCard *self)
{
  char *v2; // eax
  int v3; // ecx

  self->allocatedMemory = 0;
  self->memoryBuffer = 0;
  memset(self->sampleHandles, 0, sizeof(self->sampleHandles));
  self->stream_volume[0] = 0;
  self->field_A0 = 0;
  memset(self->sample3DHandles, 0, sizeof(self->sample3DHandles));
  self->field_A4 = 0;
  v2 = self->field_AC;
  v3 = 320;
  do
  {
    *((_DWORD *)v2 - 1) = 0;
    *(_DWORD *)v2 = 0;
    *((_DWORD *)v2 + 1) = 11025;
    *((_DWORD *)v2 + 2) = 0;
    *((_DWORD *)v2 + 3) = 0;
    *((_DWORD *)v2 + 4) = -1;
    v2 += 24;
    --v3;
  }
  while ( v3 );
  self->AudioStream = 0;
  self->totalSamples = 16;
  self->AudioChannels = 2;
  self->active3DSamples = 0;
  self->listenerID = -1;
  self->environmentPreset = 0;
  self->current3DProvider = 0;
  self->positionX = -1.0;
  self->positionY = -1.0;
  self->positionZ = -1.0;
  self->providerFlags = 0;
  self->total3DProviders = 0;
  self->EffectsEnabled = 0;
  sub_4B5ED0();
  self->Path[0] = 0;
  self->isStreamActive = 0;
  self->isStreamActive = 1;
  strcpy(self->Path, "cdata\\gtaudio\\");
  return (char *)self;
}


// 0x004b6de0: SoundCard::InitializeAudioStream
// IDA: SoundCard::InitializeAudioStream
// Ghidra: ---
char gta2::SoundCard_InitializeAudioStream(struct SoundCard *self, bool enableStereo, bool useEffects, int bufferSize)
{
  byte pAudioChannels; // al
  int v6; // eax
  _WORD v8[2]; // [esp+Ch] [ebp-10h] BYREF
  int pBufferSize; // [esp+10h] [ebp-Ch]
  int v10; // [esp+14h] [ebp-8h]
  __int16 v11; // [esp+18h] [ebp-4h]
  __int16 v12; // [esp+1Ah] [ebp-2h]

  if ( enableStereo )
    self->AudioChannels = 2;
  else
    self->AudioChannels = 1;
  v8[1] = 2;
  pAudioChannels = self->AudioChannels;
  pBufferSize = bufferSize;
  v10 = 2 * bufferSize * pAudioChannels;
  v8[0] = 1;
  v11 = (unsigned __int8)(2 * pAudioChannels);
  v12 = (unsigned __int8)(8 * pAudioChannels);
  AIL_set_preference(1, 37);
  AIL_set_preference(15, 0);
  AIL_set_preference(33, useEffects);
  AIL_set_preference(31, 1);
  if ( AIL_waveOutOpen(self, 0, -1, v8) )
    return 0;
  self->EffectsEnabled = useEffects;
  gta2::SoundCard_AcquireSampleHandle(self);
  v6 = AIL_mem_alloc_lock(&gBufferSize);
  self->allocatedMemory = v6;
  if ( !v6 )
  {
    gta2::SoundCard_ReleaseSampleHandle(self);
    AIL_waveOutClose(self->AudioStream);
    return 0;
  }
  self->memoryBuffer = v6;
  return 1;
}


// 0x004b6ee0: SoundCard::Reset3DAudioSystem
// IDA: SoundCard::Reset3DAudioSystem
// Ghidra: ---
void gta2::SoundCard_Reset3DAudioSystem(struct SoundCard *self)
{
  unsigned int v2; // ebp
  int *pSample3DHandles; // edi

  v2 = 0;
  if ( self->active3DSamples )
  {
    pSample3DHandles = (int *)self->sample3DHandles;
    do
    {
      if ( *pSample3DHandles )
      {
        AIL_release_3D_sample_handle(*pSample3DHandles);
        *pSample3DHandles = 0;
      }
      ++v2;
      ++pSample3DHandles;
    }
    while ( v2 < self->active3DSamples );
  }
  gta2::SoundCard_Shutdown3DAudio(self);
  self->totalSamples = 16;
  self->active3DSamples = 0;
  self->listenerID = -1;
  self->environmentPreset = 0;
  self->current3DProvider = 0;
  self->positionX = -1.0;
  self->positionY = -1.0;
  self->positionZ = -1.0;
  self->providerFlags = 0;
}


// 0x004b6f70: SoundCard::ReinitializeAudioSystem
// IDA: SoundCard::ReinitializeAudioSystem
// Ghidra: ---
char gta2::SoundCard_ReinitializeAudioSystem(struct SoundCard *self)
{
  char result; // al
  unsigned int v3; // ebx
  char *sampleHandles; // edi
  int sample_handle; // eax

  gta2::SoundCard_ReleaseAllSampleHandles(self);
  gta2::SoundCard_Reset3DAudioSystem(self);
  if ( !self->EffectsEnabled
    || (AIL_waveOutClose(self->AudioStream), (result = gta2::SoundCard_InitializeAudioStream(self, 1, 0, 22050)) != 0) )
  {
    v3 = 0;
    if ( self->totalSamples )
    {
      sampleHandles = self->sampleHandles;
      do
      {
        sample_handle = AIL_allocate_sample_handle(self->AudioStream);
        *(_DWORD *)sampleHandles = sample_handle;
        AIL_init_sample(sample_handle);
        AIL_set_sample_type(*(_DWORD *)sampleHandles, 1, 1);
        ++v3;
        sampleHandles += 4;
      }
      while ( v3 < self->totalSamples );
    }
    return 1;
  }
  return result;
}


// 0x004b7000: SoundCard::CloseAudioSystem
// IDA: SoundCard::CloseAudioSystem
// Ghidra: ---
int gta2::SoundCard_CloseAudioSystem(struct SoundCard *self)
{
  unsigned int i; // ebx
  SoundCard *v3; // ecx
  unsigned __int8 v4; // si
  int v5; // ebp
  int AudioStream; // edx
  unsigned __int8 v8; // [esp+10h] [ebp-4h]

  for ( i = 0; i < 2; ++i )
  {
    if ( !i )
    {
      if ( self->isStreamActive )
      {
        if ( self->stream_volume[0] )
        {
          v8 = AIL_stream_volume(self->stream_volume[0]);
          if ( v8 )
          {
            v4 = v8;
            v5 = v8;
            do
            {
              AIL_set_stream_volume(v3, self->stream_volume[0], v4);
              AIL_delay(1);
              --v4;
              --v5;
            }
            while ( v5 );
          }
        }
      }
    }
    if ( self->stream_volume[i] )
    {
      AIL_close_stream(self->stream_volume[i]);
      self->stream_volume[i] = 0;
    }
  }
  gta2::SoundCard_ReleaseSampleHandle(self);
  gta2::SoundCard_Reset3DAudioSystem(self);
  gta2::SoundCard_ReleaseAllSampleHandles(self);
  AIL_mem_free_lock(self->allocatedMemory);
  AudioStream = self->AudioStream;
  self->allocatedMemory = 0;
  self->memoryBuffer = 0;
  AIL_waveOutClose(AudioStream);
  return AIL_shutdown();
}


// 0x004b70c0: SoundCard::OpenVocal
// IDA: SoundCard::OpenVocal
// Ghidra: ---
char gta2::SoundCard_OpenVocal(struct SoundCard *self, int streamIndex, int a3, char a4)
{
  int v5; // eax
  char *v6; // eax
  char v7; // cl
  unsigned int v8; // eax
  char *v9; // edi
  char *v11; // edi
  char *v13; // edi
  unsigned int v15; // eax
  char *v16; // edi
  char v19[11]; // [esp+8h] [ebp-5Ch] BYREF
  char v20; // [esp+13h] [ebp-51h] BYREF
  char v21[80]; // [esp+14h] [ebp-50h] BYREF

  if ( streamIndex || (LOBYTE(v5) = self->isStreamActive, (_BYTE)v5) )
  {
    if ( self->stream_volume[streamIndex] )
      gta2::SoundCard_CloseStreamByIndex(self, streamIndex);
    if ( streamIndex )
    {
      strcpy(v21, "data\\audio\\vocals\\");
      v15 = 30 * a3 + strlen((const char *)(30 * a3 + 5719704)) + 1 - 30 * a3;
      v16 = &v20;
      while ( *++v16 )
        ;
      qmemcpy(v16, (const void *)(30 * a3 + 5719704), v15);
    }
    else
    {
      v6 = &self->Path[1];
      do
      {
        v7 = *v6;
        v6[v21 - &self->Path[1]] = *v6;
        ++v6;
      }
      while ( v7 );
      strcpy(v19, "%d", a3);
      v8 = strlen(v19) + 1;
      v9 = &v20;
      while ( *++v9 )
        ;
      qmemcpy(v9, v19, v8);
      if ( !a4 )
      {
        v11 = &v20;
        while ( *++v11 )
          ;
        *(_WORD *)v11 = 65;
      }
      v13 = &v20;
      while ( *++v13 )
        ;
      strcpy(v13, ".WAV");
    }
    v5 = AIL_open_stream(self->AudioStream, v21, 0);
    self->stream_volume[streamIndex] = v5;
    if ( v5 )
    {
      AIL_set_stream_loop_count(v5, streamIndex != 0);
      LOBYTE(v5) = AIL_start_stream(self->stream_volume[streamIndex]);
    }
  }
  return v5;
}


// 0x004b7250: SoundCard::InitializeAudioSystem
// IDA: SoundCard::InitializeAudioSystem
// Ghidra: ---
char gta2::SoundCard_InitializeAudioSystem(struct SoundCard *self)
{
  int AudioStream; // esi

  AIL_startup();
  if ( gta2::SoundCard_InitializeAudioStream(self, 1, self->EffectsEnabled, 22050) )
  {
    gta2::SoundCard_Enumerate3DAudioProviders(self);
    self->totalSamples = 16;
    gta2::SoundCard_ReinitializeAudioSystem(self);
    AudioStream = self->AudioStream;
    if ( AudioStream )
      AIL_set_digital_master_volume(AudioStream, 127);
    return 1;
  }
  else
  {
    AIL_shutdown();
    return 0;
  }
}


// 0x004b72b0: SoundCard::Initialize3DAudioWithDirectSound
// IDA: SoundCard::Initialize3DAudioWithDirectSound
// Ghidra: ---
char gta2::SoundCard_Initialize3DAudioWithDirectSound(struct SoundCard *self, bool *active3DSamples)
{
  unsigned int v4; // edi
  int *i; // ebx
  unsigned int v6; // ebp
  char *sample3DHandles; // ebx
  int _3D_sample_handle; // eax
  int current3DProvider; // [esp-14h] [ebp-1Ch]

  gta2::SoundCard_ReleaseAllSampleHandles(self);
  gta2::SoundCard_Reset3DAudioSystem(self);
  if ( !self->EffectsEnabled
    || (AIL_waveOutClose(self->AudioStream), gta2::SoundCard_InitializeAudioStream(self, 1, 0, 22050)) )
  {
    v4 = 0;
    for ( i = &self->currentProviderEntry;
          !*i
       || gta2::_strncmp((_BYTE *)*i, "Microsoft DirectSound3D hardware support", 30)
       || !gta2::SoundCard_Open3DProviderForListener(self, v4);
          ++i )
    {
      if ( ++v4 >= 0x100 )
        return 0;
    }
    if ( v4 >= 0x100 || !self->current3DProvider )
      return 0;
    *active3DSamples = 0;
    current3DProvider = self->current3DProvider;
    self->active3DSamples = 0;
    AIL_3D_provider_attribute(current3DProvider, "Maximum supported samples", active3DSamples);
    if ( (unsigned __int8)*active3DSamples <= 0x10u )
    {
      if ( (unsigned __int8)*active3DSamples < 8u )
      {
LABEL_22:
        *active3DSamples = 0;
        gta2::SoundCard_Shutdown3DAudio(self);
        return 0;
      }
    }
    else
    {
      *active3DSamples = 16;
    }
    v6 = 0;
    if ( !*active3DSamples )
    {
LABEL_21:
      self->active3DSamples = *active3DSamples;
      return 1;
    }
    sample3DHandles = self->sample3DHandles;
    while ( 1 )
    {
      _3D_sample_handle = AIL_allocate_3D_sample_handle(self->current3DProvider);
      *(_DWORD *)sample3DHandles = _3D_sample_handle;
      if ( !_3D_sample_handle )
        goto LABEL_22;
      ++v6;
      sample3DHandles += 4;
      if ( v6 >= *active3DSamples )
        goto LABEL_21;
    }
  }
  if ( gta2::SoundCard_InitializeAudioStream(self, 1, 0, 22050) )
    gta2::SoundCard_ReinitializeAudioSystem(self);
  return 0;
}



