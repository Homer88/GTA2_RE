# GTA2_RE Progress

## Rules
- Insert dump code verbatim, adapting only field/method naming. Do NOT fix logic or compilation errors.
- Keep function signatures as declared in `.h` (even if they mismatch dump signatures).
- Do NOT add comments to code unless asked.
- C++98, CMake build.

## What's Filled (Menu.cpp)
- All 48 functions have bodies (no TODOs remain).
- `FindBackground`, `PrintCentr`, `clearArrayTail` ported from `gta2/old/Menu.cpp`.
- Bink wrapper class at `gta2/Engine/bink/Bink.h/.cpp` with global `gBink`.
- `Version.lib` linked for `GetFileVersionInfo` in ULTIL.

## Compilation
- Build succeeds. Only pre-existing errors in `Text.h` (`Font` is not a class/namespace) — not related to Menu/Bink.

## Fields added to Menu.h
- `CountPages`, `FontStyle`, `Key`, `Index`, `CurentArrayIndex`, `MenuItems[9]`, `TimeToWaitDemoStart`, `TimeToWaitBeforeDemoStart`, `FrameCounter`

## Enums updated in Menu.cpp
- `MenuPicture`: fixed `TGA_2 = 4`, added all file indices (`OptionsFile`..`Credits_tga`)
- `MenuBackground`: added `MenuPic_3`, `MenuPic_4`, `MenuPic_5`

## Source dump
- `dump/IDA/Menu_Functions_Extracted.txt` (primary)
- `dump/IDA/gta2.exe.c` (fallback)
- `gta2/old/` (user's manual RE code)
