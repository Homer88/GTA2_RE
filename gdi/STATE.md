# GDI software back-end for GTA2 under RDP — state

## Goal
Get a picture in `C:\games\GTA2 _old\gta2-resurected.exe` over RDP, where no
physical DirectDraw adapter exists. The route is a replacement `d3ddll.dll`
that rasterises in software and presents via GDI (GDI works over RDP; DirectDraw
does not).

Do NOT touch `C:\work\GTA2_RE\gta2` (incomplete port). Do NOT use
`C:\games\original\...`. Work happens in `gdi` + `dllLoad` hook + `dump`.

## Key finding: the crash is ours, not Miles
The `strlen`-style fault in `ucrtbase.dll` is a SYMPTOM of incomplete stubs in
our GDI DLL, not a Miles bug. Disabling `mss32.dll` only produced
`0xC0000135` (hard dependency) and proved nothing.

Fault captured by VEH in `gdi.dll`:
```
fault EIP = 75FBD9B6  ->  module = ucrtbase.dll  base=75F70000 offset=0004D9B6
operation = READ
fault addr = 7263694D     (ASCII "Micr")
ESI = 7263694D, EDI = 7FFFFFFF
```
Interpretation: the game walks a code path that expects a fully working
driver, gets 0/garbage from our stubs, and ends up passing a text address to a
C runtime string routine. Fixing it via a C-runtime patch is wrong. Fix it by
completing the driver.

## Confirmed working
`gdi` builds and IS loaded by the game in place of DirectDraw:
```
=== gdi back-end attached ===
gbh_InitDLL(00C0AA00)
gbh_GetGlobals -> 5F9AF9D8     <- now a valid pointer (was NULL, was a real bug)
gbh_Init(0)
<crash: our stubs return nothing useful>
```
- `C:\work\GTA2_RE\gdi\gdi.cpp` — GDI back-end, 42 exports, builds clean.
- `C:\work\GTA2_RE\gdi\Exports.def` — export list copied from d3ddll.
- `gbh_GetGlobals` fixed: returns `(u32*)&gGlobals`; `struct Globals` copied
  verbatim from `d3ddll\d3ddll.cpp:69` because the game reads AND writes it.
- VEH crash logger in `gdi.cpp` (`VehHandler`): logs fault EIP, operation,
  fault address, registers, stack, and resolves the containing module via
  `CreateToolhelp32Snapshot(TH32CS_SNAPMODULE)`. Keep this, it is the main
  diagnostic tool.
- `C:\work\GTA2_RE\build_manual\D3DDLL_gdi.dll` — build artifact,
  deployed as `C:\games\GTA2 _old\d3ddll.dll`.

## The asset that makes this cheap
`C:\work\GTA2_RE\d3ddll\d3ddll.cpp` is 3027 lines with 38 working `gbh_*`
functions — a real software 3D rasteriser:
```
gbh_DrawQuad  gbh_DrawTriangle  gbh_DrawTilePart  gbh_DrawQuadClipped
gbh_AddLight  gbh_SetAmbient    gbh_ResetLights   gbh_SetCamera
gbh_ConvertColour  gbh_AssignPalette  gbh_RegisterPalette
gbh_BlitBuffer gbh_BlitImage  gbh_Plot  gbh_DrawFlatRect
```
Also there: `struct Globals` (L69), and a `gProxyOnly` mode with a function
table `gFuncs`.

So the 3D maths does NOT need writing from scratch. Only the OUTPUT must change:
DirectDraw surface -> DIB section + GDI `BitBlt`.

## Next steps, in order
1. Port the structs and rasteriser from `d3ddll\d3ddll.cpp` into `gdi.cpp`:
   `Globals` (L69), `Vert`, `Texture`, `Cache`, `Light`, `Image`.
2. Redirect every pixel write from the DirectDraw surface to `g_bits`
   (already declared: top-down 32bpp DIB created by `CreateBackBuffer`).
3. Keep `gbh_BlitBuffer` -> `BlitToWindow()` -> `StretchBlt` to the window
   client area. GDI this path works over RDP.
4. Fill in every export so no path returns 0/garbage. Current stubs in
   `gdi.cpp` that must become real: `gbh_DrawQuad`, `gbh_DrawTriangle`,
   `gbh_DrawTilePart`, `gbh_DrawFlatRect`, `gbh_Plot`, `gbh_BlitImage`,
   `gbh_LockTexture`, `gbh_UnlockTexture`, `gbh_RegisterTexture`,
   `gbh_SetColourDepth`, `gbh_SetWindow`, `ConvertColourBank`, `DrawLine`,
   `MakeScreenTable`, `SetShadeTableA`, `gbh_InitImageTable`, `gbh_LoadImage`.
5. `gbh_SetMode` currently returns 0 and is never reached. Note the dump's
   caller checks the windowed `Vid_SetMode(...,-2)` result against 1, so
   return values matter. Log and set sane values.
6. Re-run and confirm `gbh_SetMode` is called, then a window appears, then
   geometry shows up.

## Run/verify
```
# build
vcvars32.bat; cl /nologo /LD /D_M_IX86 /D_CRT_SECURE_NO_WARNINGS gdi.cpp ^
  /link /DEF:Exports.def /OUT:..\build_manual\D3DDLL_gdi.dll user32.lib gdi32.lib
# deploy
copy ..\build_manual\D3DDLL_gdi.dll "C:\games\GTA2 _old\d3ddll.dll"
# run, then read the log
C:\games\GTA2 _old\log\gdi.log
```
Never rename `mss32.dll` / `mssds3dh.m3d` — hard dependency, `0xC0000135`.

## Notes / dead ends, do not repeat
- DirectDraw 7 has no software mode. The only real software rasteriser in
  Windows is D3D11 WARP, which GTA2 (1999, DirectDraw 7) cannot use. So a
  "fake video card inside DirectDraw" is not a shortcut; it is the GDI
  back-end we are building.
- A proxy `ddraw.dll` in the game folder made the game report
  "wrong DirectX version" — the game validates the driver. It also never
  reached `DirectDrawCreate`.
- All `dmavideo` / `dmavideo.h` edits are irrelevant to the current path:
  the game never loads `dmavideo.dll` in this run.
- Do not edit `gta2\Engine\Movie\*` or `gta2\Engine\ultil\WinApi.cpp`.
  The earlier Movie work was reverted.
- Audio works and is not the blocker. AIL opens fine (22050 Hz stereo 16-bit).
  Separate cosmetic issue: `cbSize` is read as WAVEFORMATEX though AIL uses
  WAVEFORMAT.

## Verified dump facts (addresses valid in the rebuilt exe, PAGE_EXECUTE_READ)
- `0x004031C0` `InitDirectX` / `InitGraphicsAndInput` — DirectInput, NOT video.
- `0x004CC6D0` `ConfigureVideoSystem` — loads video dll, calls `Vid_Init`,
  `Vid_SetDevice`, `ResetVideoDevice`.
- `0x004CC580` `WindowSize` — only stores window position.
- `0x004CB570` — video setup: `Vid_SetMode(gVideoDevice, gHWND, iVar3)`.
- `0x004CB730` — fullscreen/window transition, `Vid_SetMode(...,-2)`, checks == 1.
- `0x0056E4B8` holds the string "DDRAW.DLL" at runtime.
- `0x006732D8/DC/E0/E4` are empty at attach time.
- `dllLoad\dllLoad\VideoTrace.cpp` hooks these plus `LoadLibraryA`; the fixed
  address transaction commits fine (err=0). The API detours there
  (`VideoTraceInstall`) are called without a Detour transaction and do not
  work — fix or drop them if that hook is reused.
