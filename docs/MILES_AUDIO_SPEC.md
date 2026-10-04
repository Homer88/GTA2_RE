# GTA2 retail audio (Miles 5.0r) — reconstructed spec

Source of truth: static decompilation `dump/IDA/gta2.exe.c` (retail `gta2.exe`,
ImageBase `0x3F0000`) + export table of retail `mss32.dll` (`FileVersion 5.0r`,
SHA256 `C448378207983D6FF44198E04A8CDC02AB3915CC69955397E7E61894DE66EE37`).
Runtime probing is secondary: the game needs a real display, so it never
initialises audio in this environment (see "Environment").

Retail `gta2.exe` imports 52 AIL functions from `mss32.dll` — full list in
`mss32/openmiles_v5/exports_vs_retail.txt` context / `gta2_ail_imports.txt`.
No `DMAUDIO.dll`, no `RIB_*` imports, no `.asi` files. RIB is used only
internally by `mss32.dll` itself.

---

## 1. Startup chain (SoundCard)

`SoundCard::InitializeAudioSystem` @ `0x004B7250`:

```
AIL_startup()
if (SoundCard::InitializeAudioStream(1 /*stereo*/, EffectsEnabled, 22050)) {
    SoundCard::Enumerate3DAudioProviders(this)
    this->totalSamples = 16
    SoundCard::ReinitializeAudioSystem(this)
    AIL_set_digital_master_volume(this->AudioStream, 127)
    return 1
}
AIL_shutdown(); return 0
```

### 1.1 `SoundCard::InitializeAudioStream` @ `0x004B6DE0`

```
AudioChannels = enableStereo ? 2 : 1
AIL_set_preference(1,  37)
AIL_set_preference(15, 0)
AIL_set_preference(33, useEffects)     // 1 when 3D/effects requested
AIL_set_preference(31, 1)
if (AIL_waveOutOpen(&this->AudioStream, NULL, -1 /*WAVE_MAPPER*, &fmt)) return 0
this->EffectsEnabled = useEffects
SoundCard::AcquireSampleHandle(this)                 // -> AIL_allocate_sample_handle
buf = AIL_mem_alloc_lock(&gBufferSize)               // NOTE: pointer to global, not size
if (!buf) { ReleaseSampleHandle; AIL_waveOutClose(this->AudioStream); return 0 }
this->allocatedMemory = this->memoryBuffer = buf
```

`fmt` is a plain **`WAVEFORMAT` (14 bytes), not `WAVEFORMATEX`**. Fields as the
game writes them (IDA splits them across `v8[]`, `v11`, `v12`, `pBufferSize`, `v10`):

| offset | field | value |
|---|---|---|
| 0  | `wFormatTag` | 1 (PCM) |
| 2  | `nChannels` | `AudioChannels` |
| 4  | `nSamplesPerSec` | `bufferSize` = 22050 |
| 8  | `nAvgBytesPerSec` | `2 * 22050 * channels` |
| 12 | `nBlockAlign` | `2 * channels` |
| 14 | `wBitsPerSample` | `8 * channels` (16 for stereo, 8 for mono) |

`AIL_set_preference` numeric indices (1, 15, 31, 33) are passed raw; the SDK
headers we have (`mss.h` 6.5c, `mss_6_1a.h`) do not name them — unresolved.

### 1.2 `SoundCard::ReinitializeAudioSystem` @ `0x004B6F70`

```
SoundCard::ReleaseAllSampleHandles(this)
SoundCard::Reset3DAudioSystem(this)
if (!EffectsEnabled || (AIL_waveOutClose(AudioStream),
                        InitializeAudioStream(1, 0, 22050))) {
    for (i = 0; i < this->totalSamples; i++) {
        h = AIL_allocate_sample_handle(this->AudioStream)
        this->sampleHandles[i] = h
        AIL_init_sample(h)
        AIL_set_sample_type(h, 1, 1)
    }
    return 1
}
```

`totalSamples` = 16, `AudioChannels` = 2, sample descriptor template in the
constructor holds rate `11025`.

### 1.3 3D init — `SoundCard::Initialize3DAudioWithDirectSound` @ `0x004B72B0`

Hard requirement discovered here: the game scans the provider list and only
accepts a provider whose name matches, byte for byte:

```
for (i = 0; i < 256; i++)
    if (!providerName[i] ||
        _strncmp(providerName[i], "Microsoft DirectSound3D hardware support", 30) != 0 ||
        !SoundCard::Open3DProviderForListener(this, i))
        continue;
    break;
if (i >= 256 || !this->current3DProvider) return 0;

this->active3DSamples = 0;
AIL_3D_provider_attribute(this->current3DProvider,
                          "Maximum supported samples", &this->active3DSamples);
if ((BYTE)this->active3DSamples <= 0x10) {
    if ((BYTE)this->active3DSamples < 8) goto fail;      // need 8..16
} else {
    this->active3DSamples = 16;                          // cap at 16
}
for (j = 0; j < this->active3DSamples; j++) {
    h = AIL_allocate_3D_sample_handle(this->current3DProvider);
    if (!h) goto fail;
    this->sample3DHandles[j] = h;
}
this->active3DSamples = n; return 1;
```

Consequences for any replacement 3D provider:

* provider **name string must be exactly** `"Microsoft DirectSound3D hardware support"`,
  otherwise GTA2 silently disables all 3D audio;
* `AIL_3D_provider_attribute("Maximum supported samples")` must return a value in `8..16`;
* `AIL_allocate_3D_sample_handle` must return non-NULL.

`SoundCard::Enumerate3DAudioProviders` @ `0x004B6600`:

```
while (AIL_enumerate_3D_providers(&index, &this->providerList[n], &name)) {
    this->currentProviderEntry[n] = strdup(name);   // new(0x50) + strcpy
    n++;
    if (n >= 256) break;
}
this->total3DProviders = n;
```

`SoundCard::Open3DProviderForListener` @ `0x004B6550`:

```
this->listenerID = idx;
if (idx == -1) return 0;
if (AIL_open_3D_provider(this->providerList[idx])) return 0;   // 0 == M3D_NOERR
this->current3DProvider = this->providerList[idx];
AIL_3D_provider_attribute(provider, "EAX environment selection", &v);
if (v != -1) { this->environmentPreset = 1; SoundCard::SetEAXEnvironment(this, 17); }
```

So `AIL_open_3D_provider` is called with a **provider string** (the name copied
from `AIL_enumerate_3D_providers`), and success is `0`.

EAX surface used by the game (`AIL_set_3D_provider_preference`):

| preference name | value type | range checked |
|---|---|---|
| `"EAX environment selection"` | int preset | `< 26` (`0x4B63C0`, default 17) |
| `"EAX effect volume"` | float | `[0.0 .. 1.0]` (`0x4B6460`) |
| `"EAX decay time"` | float | `[0.1 .. 20.0]` |
| `"EAX damping"` | float | `[0.0 .. 2.0]` |

`SoundCard::Shutdown3DAudio` @ `0x004B65D0`: `AIL_close_3D_provider(h); Sleep(1500);`

---

## 2. Music / vocal / radio streams

All three use `AIL_open_stream(AudioStream, path, 0)` + `AIL_set_stream_loop_count` +
`AIL_start_stream`. No `AIL_set_stream_volume` at open time — volume is applied
separately by `SoundCard::SetStreamVolume`.

### 2.1 Music — `SoundCard::sub_4B6700` @ `0x004B6700`, `index < 3`

```
if (!isStreamActive || stream_volume[0]) return;
path = this->Path + table[6 * index]
h = AIL_open_stream(this->AudioStream, path, 0);
this->stream_volume[0] = h;
if (h) { AIL_set_stream_loop_count(h, 0); AIL_start_stream(h); }
```

Table at VA `0x575914`, 6-byte stride, 3 entries (read from the exe):

| index | file | role |
|---|---|---|
| 0 | `d.wav` | menu |
| 1 | `m.wav` | in-game music |
| 2 | `a.wav` | final credits |

**`m.wav` is referenced by the game but is not shipped** in this install
(`data\GTAudio` has `D.wav` and `A.wav` only).

### 2.2 Vocals / radio — `SoundCard::OpenVocal` @ `0x004B7000`

```
if (streamIndex || this->isStreamActive) {
    if (this->stream_volume[streamIndex]) SoundCard::CloseStreamByIndex(this, streamIndex);
    if (streamIndex != 0) {
        path = "data\\audio\\vocals\\" + vocalTable[30 * a3]
    } else {
        path = this->Path + itoa(a3)
        if (!a4) path += 'A'          // *(_WORD*)v11 = 65
        path += ".WAV"
    }
    h = AIL_open_stream(this->AudioStream, path, 0);
    this->stream_volume[streamIndex] = h;
    if (h) { AIL_set_stream_loop_count(h, streamIndex != 0); AIL_start_stream(h); }
}
```

* vocal table VA `0x574698`, 30-byte stride: `accuracyb.wav`, `back2front.wav`,
  `busted.wav`, ... (dir `data\audio\vocals\`, present in the install).
* radio files are `Path` + number + optional `A` + `.WAV`; install has
  `1.wav`..`12.wav` plus `5a/6a/7a/9a/10a/11a/101a.wav`.
* `set_stream_loop_count` is `0` for music, `1` for vocals (vocals loop).
* `SoundCard::SetStreamVolume` does `AIL_set_stream_volume(h, v, v)`.

### 2.3 Path bug in this install

The constructor (`SoundCard::sub_4B6CE0` @ `0x004B6CE0`) sets

```
this->Path = "cdata\\gtaudio\\";
```

and nothing in `gta2.exe` rewrites `cdata` (single occurrence in the whole
decompile). The install has **`data\GTAudio\`** and **no `cdata\`** folder, so
all stream opens resolve to a missing path. A working replacement layer should
use `data\GTAudio\`.

---

## 3. SFX bank loading — `SoundCard::LoadSounds` @ `0x004B6B40`

```
FileName = "data\\aud" + <bank> + ".RAW"
if (!f = fopen(FileName, "rb")) { FileName = "data\\audp"; f = fopen(...); if (!f) return 0; }
size = filesize; if (size > gBufferSize) { fclose; return 0; }
fread(this->allocatedMemory, 1, size, f); fclose(f);

SdtName = "data\\aud" + <bank> + ".SDT"
f = fopen(SdtName, "rb"); if (!f) fallback; 
fread(&this->field_A8, 0x18, 0x140, f); fclose(f);   // 320 entries x 24 bytes
this->field_A4 = 1;
```

Descriptor table: 320 entries × `0x18` bytes, template `{ 0, 0, 11025, 0, 0, -1 }`.
Neither `data\audfstyle.RAW` nor `data\audfstyle.SDT` exist in this install
(`data\` has `fstyle.sty`, `bil.sty`, `*.gxt`, `*.gmp`, `*.scr`).

Sample-level API used by the game (`SoundCard` @ `0x004B60xx`):

| wrapper | AIL call |
|---|---|
| `SetSampleAddress` `0x4B6110` | `AIL_set_sample_address` |
| `SetSampleVolume` `0x4B6130` | `AIL_set_sample_volume` |
| `SetSamplePan` `0x4B6150` | `AIL_set_sample_pan` |
| `SetSamplePlaybackRate` `0x4B6160` | `AIL_set_sample_playback_rate` |
| `SetSampleLoopCount` `0x4B61B0` | `AIL_set_sample_loop_count` |
| `SetSampleLoopBlock` `0x4B6170` | `AIL_set_sample_loop_block` |
| `StartSample` / `StopSample` | `AIL_start_sample` / `AIL_end_sample` |
| `Set3DSampleInfo` `0x4B6220` | `AIL_set_3D_sample_info` |
| `Set3DSampleVolume` `0x4B6240` | `AIL_set_3D_sample_volume` |
| `Set3DPosition` `0x4B6250` | `AIL_set_3D_position` |
| `Set3DSampleFloatDistances` `0x4B6280` | `AIL_set_3D_sample_float_distances` (5 floats, `@20`) |
| `Set3DSamplePlaybackRate` `0x4B62A0` | `AIL_set_3D_sample_playback_rate` |
| `Set3DSampleLoopCount` / `...LoopBlock` | `AIL_set_3D_sample_loop_count` / `..._loop_block` |
| `Start3DSample` / `CheckAndStop3DSample` | `AIL_start_3D_sample` / `AIL_end_3D_sample` |
| `Reset3DAudioSystem` | `AIL_release_3D_sample_handle` |

---

## 4. openmiles reference build

`muzea/openmiles` (fork of `maci0/openmiles`, branch `test/windows`, GPL-3.0),
built with `zig 0.16.0`:

```
zig build -Dtarget=x86-windows -Doptimize=ReleaseSmall -Dmss-version=5
```

Artifacts: `mss32/openmiles_v5/mss32.dll`, retail reference copy
`mss32/openmiles_v5/mss32_retail_5.0r.dll`.

Verified against retail export tables:

* **all 52 GTA2 AIL imports present**;
* 27 exports that retail has and openmiles lacks (filter API, DLS reverb,
  input, `RIB_find_provider`, `AIL_primary_digital_driver`,
  `AIL_get_timer_highest_delay`, ...) — **none of them imported by GTA2**;
* one spurious extra: `_DllMainCRTStartup@12`;
* **required local patch**: `AIL_3D_sample_float_distances` and
  `AIL_set_3D_sample_float_distances` were listed in `src/api/digital.zig`
  `never_export` and were therefore suppressed. Retail 5.0r *does* export both
  (`_AIL_set_3D_sample_float_distances@20`, `_AIL_3D_sample_float_distances@20`)
  and `gta2.exe` imports the first — without the patch GTA2 cannot start.
  Removing those two names from `never_export` restores 52/52.

openmiles exposes its built-in 3D provider under its own name, so per §1.3
GTA2 would reject it and disable 3D audio. A replacement provider must report
the retail name string.

Behavioural reference points in openmiles source (`src/api/`): `stream.zig`,
`digital.zig`, `3d.zig`, `rib.zig`. `AIL_set_3D_sample_float_distances_v5`
(`3d.zig:104`) forwards only `max_dist`/`min_dist` and ignores the 3rd/4th
float args.

---

## 5. Environment

* Session is RDP without graphics. `ddraw.dll`, `dsound.dll`, `d3d9.dll` exist
  in `System32`, `d3d8.dll` does not.
* Retail `gta2.exe` runs (20 s alive, responding) once our own renderer sits next
  to it: `d3ddll.dll` (+ `d3dpoly.dll`, `dmavideo.dll`) from `bin/`.
* `gta2-resurected.exe` is the exe carrying the hook; it also has all 52 AIL
  imports.
* `ProbeLog` writes to **`CWD\log\<yyyy-mm-dd_HH-mm-ss>\`**, not to `C:\work\log`.
* In this environment the game never reaches audio init: `audio.txt` contains
  only `Install ok`, `MilesInstall ok` and two `Init3DSound
  pSound3DConfigure=0` entries from `WndProc`. Synthetic `SendKeys` input does
  not advance it (stuck on intro/FMV). Hence no runtime AIL trace is available
  here — the spec above is derived statically instead.