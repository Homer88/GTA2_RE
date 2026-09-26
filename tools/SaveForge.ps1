<#
    SaveForge.ps1 - synthesize a GTA2 save with chosen values.

    .\SaveForge.ps1 -Slot 5 -Name TEST -Value 90
    .\SaveForge.ps1 -Slot 4 -Unique            # метка 4,5,6... в каждом поле
    .\SaveForge.ps1 -Slot 5 -Value 0 -Risky      # 0 = clear, also poke weapon/wanted
    .\SaveForge.ps1 -Slot 5 -Verify               # just re-read and print

    Layout source of truth: tools\SAVE_LAYOUT.md
#>
param(
    [string]$OutDir = 'C:\work\log\player',
    [string]$BackupDir = 'C:\work\log\exp',
    [string]$TemplateSvg = 'C:\work\log\player\plyslot0.svg',
    [int]$Slot = 5,
    [string]$Name = 'TEST',
    [int]$Value = 90,
    [int]$TopValue = -1,          # 0x64; -1 = same as $Value
    [int]$MarkFrom = 4,          # -Unique: первое значение метки
    [int]$MarkTo = 900,          # -Unique: последнее значение метки
    [switch]$Unique,             # разное число в каждом поле - ищем неизвестные
    [switch]$UniqueAll,          # + затирать mission/object таблицы (риск краша)
    [switch]$SkipRisky,          # не трогать remap/selectWeapon/policeStar/missionCount
    [switch]$SkipUnknown,        # не трогать 72 байта 0xE2..0x129
    [int]$Only = -1,             # записать РОВНО ОДНО поле: смещение, всё остальное из шаблона
    [switch]$Risky,
    [switch]$Verify
)

$ErrorActionPreference = 'Stop'

$svgPath = Join-Path $OutDir "plyslot$Slot.svg"
$datPath = Join-Path $OutDir "plyslot$Slot.dat"

# ---------------------------------------------------------------- helpers
function Show-Svg([string]$p) {
    $b = [IO.File]::ReadAllBytes($p)
    Write-Host ("{0} ({1} B)" -f (Split-Path $p -Leaf), $b.Length)
    Write-Host ("  0x4B city={0}  0x4C level=0x{1:X2}  0x4D gang={2}" -f $b[0x4B], $b[0x4C], $b[0x4D])
    Write-Host ("  money={0}  multiplier={1}  lives={2}  health={3}" -f `
            [BitConverter]::ToUInt32($b, 0x64), [BitConverter]::ToUInt32($b, 0x68), $b[0xD4], [BitConverter]::ToUInt16($b, 0x6C))
    Write-Host ("  wanted={0}  selectWeapon=0x{1:X4}  remap={2}" -f [BitConverter]::ToUInt16($b, 0xE0), [BitConverter]::ToUInt16($b, 0xD6), $b[0xD3])
    Write-Host ('  powerups u16[17]: ' + ((0..16 | ForEach-Object { [BitConverter]::ToUInt16($b, 0x6E + 2 * $_) }) -join ' '))
    Write-Host ('  field644 int[10]: ' + ((0..9 | ForEach-Object { [BitConverter]::ToUInt32($b, 0x90 + 4 * $_) }) -join ' '))
    Write-Host ('  ammo[15]        : ' + ((0..14 | ForEach-Object { $b[0xBA + $_] }) -join ' '))
    Write-Host ('  gangRespect[10] : ' + ((0..9 | ForEach-Object { $b[0xC9 + $_] }) -join ' '))
    Write-Host ("  field678={0}  field67C={1}  tokens={2}" -f `
            [BitConverter]::ToUInt32($b, 0xD8), [BitConverter]::ToUInt32($b, 0xDC), [BitConverter]::ToUInt32($b, 0x744))
}

function Show-Dat([string]$p) {
    $b = [IO.File]::ReadAllBytes($p)
    $n = ([Text.Encoding]::Unicode.GetString($b, 0, 18) -replace "`0", '')
    Write-Host ("{0} ({1} B)  name='{2}'" -f (Split-Path $p -Leaf), $b.Length, $n)
    for ($i = 0; $i -lt 12; $i++) {
        $o = 18 + 9 * $i
        Write-Host ("  rec{0,-2} city={1} sub={2} flag={3} best={4} last={5}" -f `
                $i, [int][Math]::Floor($i / 4), ($i % 4), $b[$o], `
                [BitConverter]::ToUInt32($b, $o + 1), [BitConverter]::ToUInt32($b, $o + 5))
    }
}

function W8($b, [int]$o, [int]$v) { $b[$o] = [byte]($v -band 0xFF) }
function W16($b, [int]$o, [int]$v) { [Array]::Copy([BitConverter]::GetBytes([uint16]($v -band 0xFFFF)), 0, $b, $o, 2) }
function W32($b, [int]$o, [int]$v) { [Array]::Copy([BitConverter]::GetBytes([uint32]($v -band 0xFFFFFFFFL)), 0, $b, $o, 4) }

# ---------------------------------------------------------------- .dat
if ($Verify) {
    if (Test-Path -LiteralPath $svgPath) { Show-Svg $svgPath }
    if (Test-Path -LiteralPath $datPath) { Show-Dat $datPath }
    return
}
if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir | Out-Null }
if ((Test-Path -LiteralPath $datPath) -and (Test-Path -LiteralPath $BackupDir)) {
    Copy-Item -LiteralPath $datPath -Destination (Join-Path $BackupDir "orig_plyslot$Slot.dat") -Force
    Write-Host "backed up original -> $BackupDir\orig_plyslot$Slot.dat"
}

$dat = New-Object byte[] 126
# В режиме меток best/last=0, чтобы собственные записи игры было видно отчётливо.
$datVal = if ($Unique) { 0 } else { $Value }
$wname = $Name
if ($wname.Length -gt 8) { $wname = $wname.Substring(0, 8) }
$wname = $wname.PadRight(9, [char]0)
[Array]::Copy([Text.Encoding]::Unicode.GetBytes($wname), 0, $dat, 0, 18)
for ($i = 0; $i -lt 12; $i++) {
    $o = 18 + 9 * $i
    W8 $dat $o 1
    W32 $dat ($o + 1) $datVal
    W32 $dat ($o + 5) $datVal
}
[IO.File]::WriteAllBytes($datPath, $dat)
Write-Host "wrote $datPath  (name='$Name', 12/12 levels unlocked, best=last=$datVal)"

# ---------------------------------------------------------------- .svg
if (-not (Test-Path -LiteralPath $TemplateSvg)) { throw "template not found: $TemplateSvg" }
$svg = [IO.File]::ReadAllBytes($TemplateSvg)
# Хвостовые блоки переменной длины (у slot0 3232 B, у slot5 3400 B) - длину
# берём у шаблона, а не хардкодим.
if ($svg.Length -lt 3232) { throw "template is only $($svg.Length) B, too short" }
if (Test-Path -LiteralPath $svgPath) {
    Copy-Item -LiteralPath $svgPath -Destination (Join-Path $BackupDir "orig_plyslot$Slot.svg") -Force
    Write-Host "backed up original -> $BackupDir\orig_plyslot$Slot.svg"
}

$v = $Value
$top = if ($TopValue -ge 0) { $TopValue } else { $Value }
$log = New-Object System.Collections.Generic.List[string]
function SetField([string]$what, [int]$off, [int]$size, $new) {
    $script:log.Add(('  0x{0:X4}  {1,-18} = {2}' -f $off, $what, $new))
}

# Размер поля по подтверждённой карте (см. gta2.exe.c: Player::sub_4A6B20 /
# sub_4A6C80, MissionManager::SaveFile / sub_47F0B0). Неизвестное смещение -
# ошибка, а не молчаливая запись одним байтом.
function Get-FieldSize([int]$off) {
    if (@(0x54, 0x58, 0x5C, 0x60, 0x64, 0x68, 0xD8, 0xDC) -contains $off) { return 4 }
    if (@(0x90, 0x94, 0x98, 0x9C, 0xA0, 0xA4, 0xA8, 0xAC, 0xB0, 0xB4) -contains $off) { return 4 }
    if ($off -eq 0x6C -or $off -eq 0xD6 -or $off -eq 0xE0 -or $off -eq 0x12A) { return 2 }
    if ($off -ge 0x6E -and $off -le 0x8E -and (($off - 0x6E) % 2) -eq 0) { return 2 }
    if ($off -ge 0xBA -and $off -le 0xC8) { return 1 }
    if ($off -ge 0xC9 -and $off -le 0xD4) { return 1 }
    if ($off -ge 0xE2 -and $off -le 0x129) { return 1 }
    throw ("0x{0:X4}: размер поля неизвестен - уточни карту, чтобы не записать" -f $off) +
          " неверную ширину. Известны: 0x54/58/5C/60/64/68/90..B4/D8/DC (4 байта)," +
          " 0x6C/6E..8E/D6/E0/12A (2 байта), 0xBA..0xD4 (1 байт), 0xE2..0x129 (1 байт)."
}

if ($Only -ge 0) {
    $sz = Get-FieldSize $Only
    switch ($sz) {
        1 { W8 $svg $Only $Value }
        2 { W16 $svg $Only $Value }
        4 { W32 $svg $Only $Value }
    }
    SetField "ONLY (${sz} B)" $Only $sz $Value
}
elseif ($Unique) {
    # --- Метки: в каждое поле своё число, по возрастанию смещения.
    # Смотришь в игре, какое число где горит, и читаешь таблицу.
    $fields = New-Object System.Collections.Generic.List[object]
    function Fld([int]$off, [int]$size, [string]$name) {
        $script:fields.Add([pscustomobject]@{ Off = $off; Size = $size; Name = $name })
    }
    function FldRun([int]$off, [int]$size, [int]$count, [string]$fmt) {
        for ($k = 0; $k -lt $count; $k++) { Fld ($off + $size * $k) $size ($fmt -f $k) }
    }

    Fld 0x64 4 'money/счёт миссии'
    Fld 0x68 4 'multiplier'
    Fld 0x6C 2 'health'
    FldRun 0x6E 2 17 'powerup[{0}]'
    FldRun 0x90 4 10 'field644[{0}]'
    FldRun 0xB8 1 2 'unkB8[{0}]'
    FldRun 0xBA 1 15 'ammo[{0}]'
    FldRun 0xC9 1 10 'gangRespect[{0}]'
    Fld 0xD3 1 'remap'
    Fld 0xD4 1 'lives'
    Fld 0xD5 1 'unkD5'
    Fld 0xD6 2 'selectWeapon'
    Fld 0xD8 4 'field678'
    Fld 0xDC 4 'field67C'
    Fld 0xE0 2 'policeStar'
    FldRun 0xE2 1 72 'unkE2[{0}]'
    Fld 0x12A 2 'missionCount'
    # 0x710..0x744 НЕ размечаем НИКОГДА.
    #   0x710..0x741 -> загрузчик делает qmemcpy в ЖИВУЮ gObject->S63[0].S63_1
    #                   (48 B) + field_30; там указатели, мусор -> краш при
    #                   первом обращении (проверено:Turrel::sub_4CD770 -> Weapon::SetPed).
    #   0x744 -> MapGm::sub_476B10(токены), реальное поле движка.
    if ($UniqueAll) {
        FldRun 0x5E4 1 300 'objectState[{0}]'
        FldRun 0x134 2 300 'missionCity[{0}]'
        FldRun 0x136 2 300 'missionId[{0}]'
    }

    # 0x12C/0x130 НЕ размечаем НИКОГДА: это битовые маски "запустить миссию при
    # загрузке", а ID mission берутся из RAM-массивов arr_15[32]/arr_12[25],
    # которых в файле нет. Несуществующий бит -> StartMission вернёт мусор ->
    # разыменование -> краш при загрузке (проверено, игра упала).
    $skip = New-Object System.Collections.Generic.List[int]
    if ($SkipRisky) {
        $skip.AddRange([int[]]@(0xD3, 0xD6, 0xE0, 0x12A))   # remap/selectWeapon/policeStar/missionCount
    }
    if ($SkipUnknown) {
        0xE2..0x129 | ForEach-Object { $skip.Add($_) }
    }
    $fields = $fields | Where-Object { $skip -notcontains $_.Off }

    $ordered = $fields | Sort-Object Off
    $n = $MarkFrom
    $map = New-Object System.Collections.Generic.List[string]
    $skipped = 0
    foreach ($f in $ordered) {
        if ($n -gt $MarkTo) { $skipped++; continue }
        switch ($f.Size) {
            1 { W8 $svg $f.Off $n }
            2 { W16 $svg $f.Off $n }
            4 { W32 $svg $f.Off $n }
        }
        $map.Add(('  {0,4}  0x{1:X4}  {2}' -f $n, $f.Off, $f.Name))
        $n++
    }
    $mapFile = Join-Path $BackupDir "slot$Slot`_map.txt"
    $hdr = @(
        "Значение  Смещение  Поле",
        "Слот $Slot, шаблон $TemplateSvg",
        "Диапазон меток $MarkFrom..$($n - 1), полей помечено $($map.Count), не влезло $skipped",
        ""
    ) + $map
    Set-Content -LiteralPath $mapFile -Value $hdr -Encoding utf8
    Write-Host ''
    Write-Host "МЕТКИ: $($map.Count) полей, значения $MarkFrom..$($n - 1) (не влезло $skipped)"
    Write-Host "таблица соответствия -> $mapFile"
    if ($skipped -gt 0) { Write-Host "ВНИМАНИЕ: $skipped полей не получили метку (лимит $MarkTo)" -ForegroundColor Yellow }
}
else {
W32 $svg 0x64 $top; SetField 'money(счёт)' 0x64 4 $top
W32 $svg 0x68 $v; SetField 'multiplier' 0x68 4 $v
W16 $svg 0x6C $v; SetField 'health' 0x6C 2 $v
0..16 | ForEach-Object { W16 $svg (0x6E + 2 * $_) $v }
SetField 'powerups[17] u16' 0x6E 34 "$v x17"
0..9 | ForEach-Object { W32 $svg (0x90 + 4 * $_) $v }
SetField 'field644[10] i32' 0x90 40 "$v x10"
0..14 | ForEach-Object { W8 $svg (0xBA + $_) $v }
SetField 'ammo[15]' 0xBA 15 "$v x15"
0..9 | ForEach-Object { W8 $svg (0xC9 + $_) $v }
SetField 'gangRespect[10]' 0xC9 10 "$v x10"
W8 $svg 0xD4 $v; SetField 'lives' 0xD4 1 $v
W32 $svg 0xD8 $v; SetField 'field678' 0xD8 4 $v
W32 $svg 0xDC $v; SetField 'field67C' 0xDC 4 $v
W32 $svg 0x744 $v; SetField 'specialToken' 0x744 4 $v

if ($Risky) {
    W16 $svg 0xD6 $v; SetField 'selectWeapon' 0xD6 2 "$v  (RISKY)"
    W16 $svg 0xE0 $v; SetField 'wantedLevel' 0xE0 2 "$v  (RISKY, in-game max is 6)"
    W8 $svg 0xD3 $v; SetField 'remap' 0xD3 1 "$v  (RISKY)"
}
}

Write-Host ''
if ($Only -ge 0) { Write-Host "patched into ${svgPath} (ровно одно поле):" }
elseif ($Unique) { Write-Host "patched into ${svgPath}:" }
else { Write-Host "patched into ${svgPath} (from ${TemplateSvg}):" }
$log | ForEach-Object { Write-Host $_ }
[IO.File]::WriteAllBytes($svgPath, $svg)
Write-Host ''
if ($Unique) {
    Write-Host "left untouched: map/style/script names, posX/Y/Z, rotation, carSpawn[3],"
    Write-Host "                missionCity/missionId[300], objectState[300]"
    Write-Host ''
    Write-Host "первые метки:"
    $map | Select-Object -First 12 | ForEach-Object { Write-Host $_ }
    Write-Host '  ...'
    $map | Select-Object -Last 6 | ForEach-Object { Write-Host $_ }
}
else {
    Write-Host "left untouched: map/style/script names, posX/Y/Z, rotation, remap, carSpawn[3],"
    Write-Host "                objectiveIds[300], objectState, S63copy"
}
Write-Host ''
Show-Svg $svgPath
Write-Host ''
Show-Dat $datPath
