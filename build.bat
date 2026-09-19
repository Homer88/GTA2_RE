@echo off
setlocal

set "SCRIPT_DIR=%~dp0"

:menu
cls
echo.
echo  ================================================
echo    GTA2 Resurrection - меню сборки
echo  ================================================
echo    0 - Выход
echo    1 - Очистить проект
echo    2 - Собрать Hook DLL (dllLoad)
echo    3 - Собрать gta2.exe (gta2)
echo    4 - Собрать gta2manager.exe (gta2manager)
echo    5 - Собрать DLL 
echo    6 - Собрать Tools
echo    7 - Собрать Resurce
echo    8 - Другие сборки
echo    9 - Собрать все
echo  ================================================
echo.
set /p "M=Выберите пункт: "

if "%M%"=="0" goto :eof
if "%M%"=="1" goto clean
if "%M%"=="2" goto build_hook_dll
if "%M%"=="3" goto build_gta2
if "%M%"=="4" goto build_manager
if "%M%"=="5" goto menuDLL
if "%M%"=="6" goto menuTools
if "%M%"=="7" goto menuRes
if "%M%"=="8" goto menuConsol
if "%M%"=="9" goto build_all
echo  Неверный выбор.
pause
goto menu

:menuDLL
cls
echo.
echo  ================================================
echo    GTA2 Resurrection - меню сборки DLL 
echo  ================================================
echo    0 - Вернуться 
echo    1 - Собрать DLL 3dfx
echo    2 - Собрать DLL binkw32
echo    3 - Собрать DLL d3ddll
echo    4 - Собрать DLL d3dpoly
echo    5 - Собрать DLL dmaglide
echo    6 - Собрать DLL dmavideo
echo    7 - Собрать DLL mss32
echo    8 - Собрать DLL mssds3dh
echo    9 - Собрать DLL polygon
echo  ================================================
echo.
set /p "M=Выберите пункт: "

if "%M%"=="0" goto menu
if "%M%"=="1" goto build_3dfx
if "%M%"=="2" goto build_binkw32
if "%M%"=="3" goto build_d3ddll
if "%M%"=="4" goto build_d3dpoly
if "%M%"=="5" goto build_dmaglide
if "%M%"=="6" goto build_dmavideo
if "%M%"=="7" goto build_mss32
if "%M%"=="8" goto build_mssds3dh
if "%M%"=="9" goto build_polygon
if "%M%"=="10" goto build_all
echo  Неверный выбор.
pause
goto menuDLL


:menuTools
cls
echo.
echo  ================================================
echo    GTA2 Resurrection - меню сборки инструментов 
echo  ================================================
echo    0 - Вернуться 
echo    1 - Собрать DLL 3dfx
echo    2 - Собрать DLL binkw32
echo    3 - Собрать DLL d3ddll
echo    4 - Собрать DLL d3dpoly
echo    5 - Собрать DLL dmaglide
echo    6 - Собрать DLL dmavideo
echo    7 - Собрать DLL mss32
echo    8 - Собрать DLL mssds3dh
echo    9 - Собрать DLL polygon
echo  ================================================
echo.
set /p "M=Выберите пункт: "

if "%M%"=="0" goto menu
if "%M%"=="1" goto build_3dfx
if "%M%"=="2" goto build_binkw32
if "%M%"=="3" goto build_d3ddll
if "%M%"=="4" goto build_d3dpoly
if "%M%"=="5" goto build_dmaglide
if "%M%"=="6" goto build_dmavideo
if "%M%"=="7" goto build_mss32
if "%M%"=="8" goto build_mssds3dh
if "%M%"=="9" goto build_polygon
if "%M%"=="10" goto build_all


echo  Неверный выбор.
pause
goto menu

:menuRes
cls
echo.
echo  ================================================
echo    GTA2 Resurrection - меню сборки ресурсов
echo  ================================================
echo    0 - Вернуться 
echo    1 - Собрать DLL 3dfx
echo    2 - Собрать DLL binkw32
echo    3 - Собрать DLL d3ddll
echo    4 - Собрать DLL d3dpoly
echo    5 - Собрать DLL dmaglide
echo    6 - Собрать DLL dmavideo
echo    7 - Собрать DLL mss32
echo    8 - Собрать DLL mssds3dh
echo    9 - Собрать DLL polygon
echo  ================================================
echo.
set /p "M=Выберите пункт: "

if "%M%"=="0" goto menu
if "%M%"=="1" goto build_3dfx
if "%M%"=="2" goto build_binkw32
if "%M%"=="3" goto build_d3ddll
if "%M%"=="4" goto build_d3dpoly
if "%M%"=="5" goto build_dmaglide
if "%M%"=="6" goto build_dmavideo
if "%M%"=="7" goto build_mss32
if "%M%"=="8" goto build_mssds3dh
if "%M%"=="9" goto build_polygon
if "%M%"=="10" goto build_all
echo  Неверный выбор.
pause
goto menu
:menuConsol
cls
echo.
echo  ================================================
echo    GTA2 Resurrection - меню сборки консолей
echo  ================================================
echo    0 - Вернуться 
echo    1 - Собрать под PS1(PSone)
echo    2 - Собрать под PS2
echo    3 - Собрать под PS3
echo    4 - Собрать под PS4
echo    5 - Собрать под PS5
echo    6 - Собрать под Nintenod 64(N64)
echo    7 - Собрать под Nintenod GameCube(GC)
echo    8 - Собрать под Nintenod WII
echo    9 - Собрать под Nintendo WII U
echo    10 - Собрать под Nintendo Switch
echo    11 - Собрать под Nintendo Switch 2 (нету SDK)
echo    12 - Собрать под Microsoft Xbox 
echo    13 - Собрать под Microsoft Xbox 360
echo  ================================================
echo.
set /p "M=Выберите пункт: "

if "%M%"=="0" goto menu
if "%M%"=="1" goto build_3dfx
if "%M%"=="2" goto build_binkw32
if "%M%"=="3" goto build_d3ddll
if "%M%"=="4" goto build_d3dpoly
if "%M%"=="5" goto build_dmaglide
if "%M%"=="6" goto build_dmavideo
if "%M%"=="7" goto build_mss32
if "%M%"=="8" goto build_mssds3dh
if "%M%"=="9" goto build_polygon
if "%M%"=="10" goto build_all
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

:build_hook_dll
echo.
echo  Сборка DLL Win32...
cmake -S . -B build  -A Win32 "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Конфигурация CMake не удалась.
    pause
    goto menu
)
cmake --build build --target HookLoad
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] DLL не собрана.
) else (
    echo  Готово: c:\games\gta2\gta2-resurection.dll
)
pause
goto menu

:build_gta2
echo.
echo  CMake: конфигурация основного проекта...
cmake -S . -B build -A Win32 "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Конфигурация CMake не удалась.
    pause
    goto menu
)
echo  CMake: сборка основного проекта...
cmake --build build --target GTA2 
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
rem call :do_build_dll
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] HOOK DLL не собрана.
    pause
    goto menu
)
echo  Готово: c:\games\gta2\gta2-resurection.dll
echo.
echo  ==== [2/2] Сборка основного проекта ====
cmake -S . -B build  -A Win32 "-DCMAKE_POLICY_VERSION_MINIMUM=3.5"
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Конфигурация CMake не удалась.
    pause
    goto menu
)
cmake --build  ./build   -j
if errorlevel 1 (
    echo.
    echo  [ОШИБКА] Сборка основного проекта не удалась.
) else (
    echo  Готово.
)







:build_3dfx

echo  ==== [1/2] Сборка DLL ====
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

