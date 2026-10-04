# Clean-room mss32.dll (Miles Sound System 5.0r ABI) для GTA2

Цель: своя реализация `mss32.dll`, экспортирующая v5-имена с декораторами `@N`,
которую GTA2 (`gta2-resurected.exe`) грузит вместо retail Miles 5.0r.

Рабочий каталог: `C:\work\GTA2_RE\mss32\ours`

## 1. Контракт ABI (52 импорта, проверено по таблице импортов exe)

Все 52 декорированных имени присутствуют в retail 5.0r с теми же `@N`
(экспортная таблица retail распарсена напрямую), значит `@N` = реальный
размер стековых аргументов в v5.0r.

Соглашение вызова: `AILCALL` = `__stdcall` (`mss.h:329`).
Хендлы 32-битные. `FAR` — пустой макрос на Win32.

### Расхождения v5 vs v6.5c (обязательно учесть в реализации)

| Функция | v6.5c (`mss.h`) | v5 (нужно реализовать) |
|---|---|---|
| `AIL_set_digital_master_volume@8` | `..._level(HDIGDRIVER, F32)` | `(HDIGDRIVER, S32)`, шкала 0..127 |
| `AIL_set_sample_volume@8` | `AIL_set_sample_volume_levels(HSAMPLE, F32 left, F32 right)` @12 | `(HSAMPLE, S32)`, 0..127 |
| `AIL_set_sample_pan@8` | `AIL_set_sample_volume_pan(HSAMPLE, F32, F32)` @12 | `(HSAMPLE, S32)`, 0=LEFT .. 127=RIGHT |
| `AIL_set_stream_volume@8` | `..._volume_pan(HSTREAM, F32, F32)` @12 | `(HSTREAM, S32)`, 0..127 |
| `AIL_stream_volume@4` | `..._volume_pan(HSTREAM, F32*, F32*)` @12 | `(HSTREAM) -> S32` |
| `AIL_set_3D_sample_float_distances@20` | `AIL_set_3D_sample_distances(H3DSAMPLE, F32, F32)` @12 | `(H3DSAMPLE, F32 front_min, F32 front_max, F32 back_min, F32 back_max)` |

Остальные 46 прототипов совпадают с `mss.h` байт-в-байт.

Ошибка в `mss_v5compat.h:53`: первый аргумент `AIL_set_3D_sample_float_distances`
объявлен как `HSAMPLE`; GTA2 передаёт `H3DSAMPLE` (`dump/IDA/gta2.exe.c:150203`).

Ловушка: `mss.h:3087` под MSVC переопределяет `AIL_startup` макросом
`AIL_startup()`, а `mss.h:2996` под Watcom — в `AIL_startup_stack`.
В своей реализации не включать этот макрос.

## 2. Константы, которых нет в SDK (задать вручную)

### Статус сэмпла (`SMP_*`) — из `mss_6_1a.h`, подтверждено GTA2
```
SMP_FREE    = 1
SMP_DONE    = 2
SMP_PLAYING = 4
SMP_STOPPED = 8
```
GTA2: пул SFX проверяет `AIL_sample_status == 4`; одиночный вокал — `!= 2`.

### Громкость / панорама
```
volume 0..127   (127 = макс; DEFAULT_MDV = 127, mss.h:791)
pan    0..127   (0 = L, 64 = центр, 127 = R)  GTA2 gta2.exe.c:150669
```

### `M3DRESULT` (`mss.h:1403-1412`)
```
M3D_NOERR = 0  (GTA2 трактует как УСПЕХ — обратная логика)
M3D_NOT_ENABLED=1 M3D_ALREADY_STARTED=2 M3D_INVALID_PARAM=3
M3D_INTERNAL_ERR=4 M3D_OUT_OF_MEM=5 M3D_ERR_NOT_IMPLEMENTED=6
M3D_NOT_FOUND=7 M3D_NOT_INIT=8 M3D_CLOSE_ERR=9
```

### `HPROVIDER` = `U32`, `HPROENUM` = `U32` (`mss.h:1019,1045`)
`H3DSAMPLE` = `H3DPOBJECT` = `struct h3DPOBJECT*` (`mss.h:1395`)
`HTIMER` = `S32` (не указатель!) (`mss.h:1730`)

### `AILSOUNDINFO` (`mss.h:984-994`) = 36 байт, 9 полей
```c
S32 format; void const* data_ptr; U32 data_len; U32 rate; S32 bits;
S32 channels; U32 samples; U32 block_size; void const* initial_ptr;
```

### Шкала форматов
`AIL_set_sample_type(S, 1, 1)` — GTA2: format=1 (WAVE_FORMAT_PCM), flags=1.

## 3. Как GTA2 реально использует Miles

### A. Своего микшера в EXE нет
Все 52 импорта вызываются только из модуля `SoundCard`.
В EXE нет `timeSetEvent`, `CreateThread`, `mmio*`, raw `waveOut*`.
WINMM импортирует только `timeGetTime`.
**Следовательно: смешивание, ресемплинг и 3D полностью на нас.**

Дополнительно: `gta2.exe.c:108534` (`LoadBinkPlay @ 0x481F20`) вызывает
`BinkSetSoundSystem(BinkOpenMiles, gSoundCard.AudioStream)` — наш драйвер
должен корректно работать и как чужой бэкенд для `binkw32.dll`.

### B. Колбэки
GTA2 **не импортирует** `AIL_register_SOB/EOB/EOS_callback` — в retail 5.0r
их нет среди импортов. Колбэки работают внутри DLL. Игра их не регистрирует.
`AIL_sample_status` — единственный способ узнать, что семпл доиграл.

### C. `AIL_mem_alloc_lock` — передаётся АДРЕС глобала
`gta2.exe.c:150861` передаёт `&0x005C6F69`. Значение по этому адресу
(6 063 209) используется как размер буфера. Игра работает случайно —
VA оказался похож на размер. Реализация: читать `*(U32*)arg` как size.

### D. Инициализация (`InitializeAudioStream @ 0x4B6DE0`)
```
AIL_set_preference(1,  37)            // DIG_MIXER_CHANNELS (default 64)
AIL_set_preference(15,  0)            // DIG_USE_WAVEOUT=0 -> DirectSound
AIL_set_preference(31,  1)            // DIG_ENABLE_RESAMPLE_FILTER=YES
AIL_set_preference(33,  useEffects)   // НЕ ОПРЕДЕЛЁН в SDK, эмпирический
AIL_waveOutOpen(&dig, NULL, -1, fmt)  // WAVE_MAPPER, fmt = WAVEFORMATEX 16 байт
AIL_mem_alloc_lock(&0x5C6F69)
AIL_set_digital_master_volume(dig, 127)
```
Формат (16 байт, как WAVEFORMATEX):
`wFormatTag=1 (PCM)`, `nChannels=2` (жёстко стерео), `nSamplesPerSec=22050`,
`nAvgBytesPerSec=2*rate*ch`, `nBlockAlign=2*ch`, `wBitsPerSample=8*ch`.
2-й аргумент `lphWaveOut = NULL`.

### E. Форматы игровых данных (подтверждено бинарно)
- `data/audio/<bank>.raw` — **8-битный unsigned PCM, mono**, per-sample rate
- `data/audio/<bank>.sdt` — 320 записей x 24 байта:
  `+0 offset, +4 len, +8 rate, +C variants, +10 min_dist, +14 max_dist`
  `sum(len)` == размер `.raw`
- `data/GTAudio/*.wav` — **WAVE_FORMAT_IMA_ADPCM (tag 17)**, 22050 Hz,
  4-bit, stereo, blockAlign 1024, есть `fact`-chunk
- `data/audio/Vocals/*.wav` — tag 17, 22050 Hz, 4-bit, **mono**, blockAlign 512
- Гистограмма rate в SDT: 4500, 5000, 5012, 5500, 6000, 7000, 8000, 11025,
  12000, 12500, 12600, 13000, 14000, 15000, 15500, 16000, 16600, 16800,
  18050, 19000, 20000, 22050 -> нужен ресемплинг
- XMIDI не используется, MIDI-импортов нет

### F. Пути
- Музыка: `cdata\gtaudio\` -> `data\GTAudio\` (`1..12.wav`, `A.wav`, `D.wav`,
  `5a..11a`, `101a.wav`)
- Вокалы: `data\audio\Vocals\` (таблица `0x574698`, 98 записей x 30 байт)
- Банки: `data\audio\bil/ste/wil/fstyle`, fallback `data\audio\BIL.p`

### G. 3D активно используется
`DMAudio::Init3DSound @ 0x410670`; `Initialize3DAudioWithDirectSound @ 0x4B72B0`:
- перебирает до 256 провайдеров и требует строку
  **`"Microsoft DirectSound3D hardware support"`** — не нашлось -> `AIL_shutdown_3D`
- `AIL_3D_provider_attribute(prov, "Maximum supported samples", &n)`,
  n clamp в 8..16
- `AIL_allocate_3D_sample_handle(prov)` x n
- `AIL_set_3D_provider_preference(prov, "EAX environment selection", &preset)`,
  preset < 26, третий аргумент — указатель
- `Set3DSampleInfo @ 0x4B6220`: `si.format=1`, `si.data_ptr=memBase+entry.off`,
  `si.data_len=entry.len`, `si.playback_rate=arg`, `si.bits=8*AudioChannels`,
  `si.channels=1`; поля `si[6..8]` (vol, loop) НЕ инициализируются
- `Set3DSampleFloatDistances @ 0x4B62F0`:
  `AIL_set_3D_sample_float_distances(S, a3, a4, a3, a4)`, значения из SDT `(0, -1)`
- `AIL_set_3D_position(obj, F32 X, F32 Y, F32 Z)` — GTA2 передаёт `H3DSAMPLE`

### H. Завершение (`0x4B7000`)
```
fade-out обоих HSTREAM (AIL_stream_volume -> AIL_set_stream_volume -> AIL_delay(1) в цикле)
-> release sample handles -> reset 3D -> AIL_mem_free_lock
-> AIL_waveOutClose -> AIL_shutdown
```
`AIL_delay(1)` = 1 мс ожидания. Значит наш fade-out должен реально
занимать время, иначе цикл пролетит мгновенно.

## 4. Архитектура реализации

```
mss32.dll (наш, 32-bit, stdcall)
  |- waveOut backend: 22050 Hz, stereo, 16-bit
  |- Mixer thread
  |    ├─ пул голосов: 2D-семплы (16 шт) + 3D-семплы (8..16 шт) + потоки (2)
  |    ├─ ресемплинг 8-bit unsigned mono @ любая rate -> 16-bit stereo @22050
  |    ├─ IMA ADPCM декодер для WAV-потоков
  |    ├─ микшер: наложение голосов с учётом volume(0..127) / pan(0..127)
  |    └─ 3D: позиция -> volume + pan (приблизительная HRTF не нужна)
  |- провайдер "Microsoft DirectSound3D hardware support"
  └─ экспорт 52 функций через .def с v5-именами
```

Приоритет: сначала 2D-семплы + потоки (слышно), затем 3D.
