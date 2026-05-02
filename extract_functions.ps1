# Скрипт для извлечения функций по диапазонам адресов из gta2.exe.c
# Группирует функции по модулям

$inputFile = "re_file\Ghidra\gta2.exe.c"
$outputDir = "gta2_modules"

# Диапазоны адресов для модулей (в hex)
$modules = @{
    "gta2_winmain" = @("00401", "00405")  # 0x401000 - 0x405000
    "gta2_game" = @("00405", "0040A")      # 0x405000 - 0x40A000
    "gta2_player" = @("0040A", "00410")    # 0x40A000 - 0x410000
    "gta2_ped" = @("00410", "00416")       # 0x410000 - 0x416000
    "gta2_car" = @("00416", "0041C")       # 0x416000 - 0x41C000
    "gta2_menu" = @("0041C", "00420")      # 0x41C000 - 0x420000
    "gta2_hud" = @("00420", "00424")       # 0x420000 - 0x424000
    "gta2_map" = @("00424", "0042A")       # 0x424000 - 0x42A000
    "gta2_audio" = @("0042A", "0042F")     # 0x42A000 - 0x42F000
    "gta2_video" = @("0042F", "00435")     # 0x42F000 - 0x435000
    "gta2_weapon" = @("00435", "0043A")    # 0x435000 - 0x43A000
    "gta2_gang" = @("0043A", "0043F")      # 0x43A000 - 0x43F000
    "gta2_collision" = @("0043F", "00445") # 0x43F000 - 0x445000
    "gta2_sprite" = @("00445", "0044A")    # 0x445000 - 0x44A000
    "gta2_mission" = @("0044A", "00450")   # 0x44A000 - 0x450000
    "gta2_replay" = @("00450", "00455")    # 0x450000 - 0x455000
    "gta2_registry" = @("00455", "0045A")  # 0x455000 - 0x45A000
    "gta2_file" = @("0045A", "0045F")      # 0x45A000 - 0x45F000
    "gta2_debug" = @("0045F", "00464")     # 0x45F000 - 0x464000
    "gta2_other" = @("00464", "99999")     # 0x464000 - конец
}

# Читаем файл построчно
$content = Get-Content $inputFile
$currentLine = 0
$totalLines = $content.Count

# Для каждой функции храним начало и конец
$functionBlocks = @{}

Write-Host "Анализ файла... ($totalLines строк)"

# Ищем все функции
for ($i = 0; $i -lt $totalLines; $i++) {
    $line = $content[$i]
    
    # Ищем начало функции: void FUN_004..., int FUN_004..., и т.д.
    if ($line -match "^\s*(void|int|char|byte|undefined|ushort|short|float|double|Player|Car|Ped|Game|Menu|HUD|Registry|FileMgr|AudioManager|Video|SpriteS1|Weapon|Gang|Collide|Replay|MapGm|MissionManager|cNetwork|S\d+)") {
        if ($line -match "FUN_004([0-9a-f]{4})") {
            $addr = $matches[1]
            $startLine = $i
            
            # Находим конец функции (следующая функция или пустая строка после } )
            $endLine = $startLine
            $braceCount = 0
            $inFunction = $false
            
            for ($j = $startLine; $j -lt $totalLines; $j++) {
                $checkLine = $content[$j]
                
                if ($checkLine -match "\{") {
                    $braceCount++
                    $inFunction = $true
                }
                if ($checkLine -match "\}") {
                    $braceCount--
                    if ($inFunction -and $braceCount -eq 0) {
                        $endLine = $j
                        break
                    }
                }
                
                # Если нашли следующую функцию
                if ($j -gt $startLine -and $checkLine -match "FUN_004[0-9a-f]{4}") {
                    $endLine = $j - 1
                    break
                }
            }
            
            # Определяем модуль по адресу
            foreach ($modName in $modules.Keys) {
                $range = $modules[$modName]
                $startAddr = $range[0]
                $endAddr = $range[1]
                
                if ($addr -ge $startAddr -and $addr -lt $endAddr) {
                    if (-not $functionBlocks.ContainsKey($modName)) {
                        $functionBlocks[$modName] = @()
                    }
                    $functionBlocks[$modName] += @{
                        StartLine = $startLine
                        EndLine = $endLine
                        Address = $addr
                        Line = $line
                    }
                    break
                }
            }
        }
    }
    
    $currentLine = $i
    if ($currentLine % 10000 -eq 0) {
        Write-Host "Обработано строк: $currentLine / $totalLines"
    }
}

Write-Host "Функции найдены. Создание файлов..."

# Создаём файлы для каждого модуля
foreach ($modName in $functionBlocks.Keys) {
    $funcs = $functionBlocks[$modName]
    $cFile = "$outputDir\$modName.c"
    $hFile = "$outputDir\$modName.h"
    
    Write-Host "Создаём $modName ($($funcs.Count) функций)"
    
    # Создаём .c файл
    $cContent = @()
    $cContent += "/* $modName.c - Автогенерированный файл из gta2.exe.c */"
    $cContent += "/* Диапазон адресов: 0x4$($modules[$modName][0])000 - 0x4$($modules[$modName][1])000 */"
    $cContent += "#include `"gta2.exe.h`""
    $cContent += ""
    
    foreach ($func in $funcs) {
        $cContent += "// Функция 0x4$($func.Address)000 (строка $($func.StartLine))"
        for ($i = $func.StartLine; $i -le $func.EndLine; $i++) {
            $cContent += $content[$i]
        }
        $cContent += ""
    }
    
    $cContent | Out-File -FilePath $cFile -Encoding UTF8
    
    # Создаём .h файл
    $hContent = @()
    $hContent += "#ifndef __$($modName.ToUpper().Replace("-", "_"))_H_"
    $hContent += "#define __$($modName.ToUpper().Replace("-", "_"))_H_"
    $hContent += ""
    $hContent += "// Объявления функций для $modName"
    $hContent += ""
    $hContent += "#endif // __$($modName.ToUpper().Replace("-", "_"))_H_"
    
    $hContent | Out-File -FilePath $hFile -Encoding UTF8
}

Write-Host "Готово! Файлы созданы в папке $outputDir"
