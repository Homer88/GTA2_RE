#ifndef __CAUDIOWATCH_H__
#define __CAUDIOWATCH_H__

// Live audio-trace probe (dllLoad). Purpose: answer "who plays GTAudio\*.wav /
// which sound bank the frontend loads" in the retail gta2.exe at runtime.
//
// Hooked (retail __thiscall -> __fastcall wrappers, see cAudioWatch.cpp):
//   DMAudio::AddAudioObject (0x00410530)   - sets base sample rate (11025 Hz)
//   DMAudio::LoadSTY       (0x00410550)   - loads a style bank (data\audio\*.RAW/.SDT)
//   DMAudio::sub_410560    (0x00410560)   - music/Vocal poll entry
//   DMAudio::PlayVocal     (0x004105B0)   - voice line player
//   DMAudio::sub_410590    (0x00410590)   - PlayMusic (track index, loop) -> AudioManager
//   DMAudio::Init3DSound   (0x00410670)   - frontend 3D-sound setup (runs right after LoadSTY)
//   SoundCard::LoadSounds  (0x004B6B40)   - low-level bank loader (basename arg)
//   AudioManager::sub_4B2350 (0x004B2350) - StopMusic (channel clear by index/loop)
//   CreateFileA / CreateFileW              - logs any open of *GTAudio* or *.wav,
//                                            caller resolved to module!+offset
//
// All events go to "audio.txt" via GetLogPath(); TraceCall logs the caller.
//
// Shared with the other probes (cMilesWatch):
//   ProbeLog       - write "<tag>, <info>" into audio.txt
//   ProbeLogCaller - resolve <callerAddr> to "module!+rva" and log it
void ProbeLog(const char* tag, const char* info);
void ProbeLogCaller(const char* tag, unsigned long callerAddr);

#ifdef __cplusplus
extern "C" {
#endif
void InstallAudioWatchHooks(void);
#ifdef __cplusplus
}
#endif

#endif // !__CAUDIOWATCH_H__