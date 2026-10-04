@echo off
rem Builds and runs the S200 write-watch core test.
rem
rem The test links the real dllLoad/dllLoad/cS200Watch.cpp with stubs for
rem DumpPrintf and GetLogPath, so it exercises production code rather than a
rem copy. It needs the 32-bit toolchain, because the project is _M_IX86 and
rem the debug registers are handled through 32-bit CONTEXT.
rem
rem Usage: dllLoad\tests\build_and_run_test.bat
rem Requires a Visual Studio 2022 install; override VSDEV if yours differs.

setlocal

set "VSDEV=D:\dev\VisualStudio\vs17"
if not defined VSDEV set "VSDEV=%ProgramFiles%\Microsoft Visual Studio\2022"
if not defined VSDEV set "VSDEV=%ProgramFiles(x86)%\Microsoft Visual Studio\2022"

set "HERE=%~dp0"
set "SRC=%HERE%..\dllLoad"
set "OUT=%TEMP%\s200watch_test"

if not exist "%OUT%" mkdir "%OUT%"

call "%VSDEV%\VC\Auxiliary\Build\vcvarsall.bat" x86 >nul 2>&1
if errorlevel 1 (
    echo Could not initialise the x86 toolchain from "%VSDEV%".
    echo Set VSDEV to your Visual Studio installation path and retry.
    exit /b 2
)

cd /d "%OUT%"
cl /nologo /W3 /O2 /MT /D_M_IX86 /D_CRT_SECURE_NO_WARNINGS ^
   /I"%SRC%" ^
   "%HERE%test_s200watch.cpp" "%SRC%\cS200Watch.cpp" ^
   /Fe:s200watch_test.exe
if errorlevel 1 exit /b 1

del /q "%OUT%\S200Write.log" >nul 2>&1
s200watch_test.exe
exit /b %errorlevel%
