@echo off
rem Сборка GTA2Launcher.exe (Win32, GUI, статическая libc).
rem Требует заранее собранные build_manual\D3DDLL_gdi.dll и build_manual\mss32\mss32.dll
rem (они встраиваются в exe как RCDATA-ресурсы).
rem Запускать из каталога launcher:  build_launcher.bat

call D:\dev\VisualStudio\vs17\VC\Auxiliary\Build\vcvars32.bat >nul 2>&1

if not exist ..\build_manual\launcher mkdir ..\build_manual\launcher

rem 1) ресурсы: генерируем dlls.rc из актуальных DLL
set D3D=%~dp0..\build_manual\D3DDLL_gdi.dll
set MSS=%~dp0..\build_manual\mss32\mss32.dll
>dlls.rc echo #define IDR_D3DDLL 1001
>>dlls.rc echo #define IDR_MSS32  1002
>>dlls.rc echo IDR_D3DDLL RCDATA "%D3D%"
>>dlls.rc echo IDR_MSS32  RCDATA "%MSS%"

rem 2) компиляция
rc /nologo /fo ..\build_manual\launcher\dlls.res dlls.rc
cl /nologo /O1 /GS- /c main.cpp /Fo..\build_manual\launcher\main.obj
link /nologo /SUBSYSTEM:WINDOWS /OUT:..\build_manual\launcher\GTA2Launcher.exe ^
    ..\build_manual\launcher\main.obj ..\build_manual\launcher\dlls.res ^
    user32.lib gdi32.lib comdlg32.lib shell32.lib

echo.
echo Готово: ..\build_manual\launcher\GTA2Launcher.exe