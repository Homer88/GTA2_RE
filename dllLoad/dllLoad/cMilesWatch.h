#ifndef __CMILESPWATCH_H__
#define __CMILESPWATCH_H__

// Live trace of the retail Miles Sound System (mss32.dll v5.0r) calls made by
// gta2.exe (see cMilesWatch.cpp).
//
// The retail exe links mss32.dll DIRECTLY (52 AIL_* imports), so the whole
// audio playback path is visible by detouring those exports. This pins down
// exactly which DMAudio/AudioManager function plays which GTAudio\*.wav
// (music streams, vocals, radio) and with which parameters (loop count,
// volume, playback rate).
//
// Functions are resolved by their exact stdcall-decorated export names
// ("_AIL_open_stream@12"), taken from the retail mss32.dll export table.
//
// Events go to "audio.txt" (same file as cAudioWatch).

#ifdef __cplusplus
extern "C" {
#endif
void InstallMilesWatchHooks(void);
#ifdef __cplusplus
}
#endif

#endif // !__CMILESPWATCH_H__