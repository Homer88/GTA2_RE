@echo off
REM build_mss32.bat - 32-bit сборка clean-room mss32.dll + import library.
REM Использует vcvars32.bat из Visual Studio 2022.

setlocal
set VCVARS=D:\dev\VisualStudio\vs17\VC\Auxiliary\Build\vcvars32.bat
if not exist "%VCVARS%" (
  echo [ERROR] vcvars32.bat not found: %VCVARS%
  exit /b 1
)

call "%VCVARS%" >nul 2>&1
if errorlevel 1 (
  echo [ERROR] vcvars32 failed
  exit /b 1
)

set SRC_DIR=%~dp0
set OUT_DIR=%SRC_DIR%..\..\build_manual\mss32
if not exist "%OUT_DIR%" mkdir "%OUT_DIR%"

echo [1/4] compiling mss32.obj
cl /nologo /c /O2 /W3 /MT /D_CRT_SECURE_NO_WARNINGS /Fo:"%OUT_DIR%\mss32.obj" "%SRC_DIR%mss32.cpp"
if errorlevel 1 goto :fail

echo [2/4] linking mss32.dll
link /nologo /DLL /OUT:"%OUT_DIR%\mss32.dll" "%OUT_DIR%\mss32.obj" /DEF:"%SRC_DIR%mss32.def" /MAP:"%OUT_DIR%\mss32.map" winmm.lib
if errorlevel 1 goto :fail

echo [3/4] generating mss32.lib import library
lib /nologo /OUT:"%OUT_DIR%\mss32.lib" /DEF:"%SRC_DIR%mss32.def" /MACHINE:X86
if errorlevel 1 goto :fail

echo [4/4] verifying exports
dumpbin /nologo /exports "%OUT_DIR%\mss32.dll" | find /c "_AIL_"

echo.
echo BUILD OK: %OUT_DIR%
endlocal
exit /b 0

:fail
echo.
echo BUILD FAILED
endlocal
exit /b 1
