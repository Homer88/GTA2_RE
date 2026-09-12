@echo off
setlocal

set "SCRIPT_DIR=%~dp0"
set "MSBUILD=D:\dev\VisualStudio\vs17\MSBuild\Current\Bin\MSBuild.exe"
set "SLN=%SCRIPT_DIR%dllLoad\dllLoad.sln"

:menu
cls
echo.
echo  ================================================
echo    GTA2 Resurrection - меню сборки
echo  ================================================
echo    0 - Выход
echo    1 - Очистить проект
echo    2 - Собрать DLL (dllLoad)
echo    3 - Собрать основной проект (gta2)
echo    4 - Собрать все
echo  ================================================
echo.
set /p "M=Выберите пункт: "

if "%M%"=="0" goto :eof
if "%M%"=="1" goto clean
if "%M%"=="2" goto build_dll
if "%M%"=="3" goto build_main
if "%M%"=="4" goto build_all
echo  Неверный выбор.
pause
goto menu

:clean
echo.
echo  Очистка основного проекта (build\...)...
if exist "%SCRIPT_DIR%build" rmdir /s /q "%SCRIPT_DIR%build"
echo  Очистка DLL (MSBuild /t:Clean)...
"%MSBUILD%" "%SLN%" /t:Clean /p:Configuration=Debug /p:Platform=Win32 /m /nologo
echo  Готово.
pause
goto menu

:build_dll
echo.
echo  Сборка DLL (Debug|Win32)...
call :do_build_dll
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] DLL не собрана.
) else (
    echo  Готово: c:\games\gta2\gta2-resurection.dll
)
pause
goto menu

:build_main
echo.
echo  CMake: конфигурация основного проекта...
cmake -S "%SCRIPT_DIR%" -B "%SCRIPT_DIR%build" -A Win32 "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Конфигурация CMake не удалась.
    pause
    goto menu
)
echo  CMake: сборка основного проекта...
cmake --build "%SCRIPT_DIR%build" -j
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Сборка основного проекта не удалась.
) else (
    echo  Готово.
)
pause
goto menu

:build_all
echo.
echo  ==== [1/2] Сборка DLL ====
call :do_build_dll
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] DLL не собрана.
    pause
    goto menu
)
echo  Готово: c:\games\gta2\gta2-resurection.dll
echo.
echo  ==== [2/2] Сборка основного проекта ====
cmake -S "%SCRIPT_DIR%" -B "%SCRIPT_DIR%build" -A Win32 "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Конфигурация CMake не удалась.
    pause
    goto menu
)
cmake --build "%SCRIPT_DIR%build" -j
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Сборка основного проекта не удалась.
) else (
    echo  Готово.
)
pause
goto menu

:do_build_dll
"%MSBUILD%" "%SLN%" /t:Build /p:Configuration=Debug /p:Platform=Win32 /m /nologo
exit /b %errorlevel%