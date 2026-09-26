<#
    SaveEdit.ps1 - GTA2 save editor (.svg block0 + .dat records)

    Layout is taken from retail code in dump\IDA\gta2.exe.c, not guessed:
      MissionManager::SaveFile        0x47EF40  - .svg assembly + write order
      MissionManager::sub_47EE70      0x47EE70  - mission table (map-derived!)
      MissionManager::sub_47EF10      0x47EF10  - mission table load
      Player::sub_4A6B20             - player block writer
      Player::sub_4A6C80             - player block loader
      PlayerData::WriteFileNamePlayer 0x4A89E0  - .dat layout (a3 = 126)

    USAGE
      .\SaveEdit.ps1 -Slot 4 -Show
      .\SaveEdit.ps1 -Slot 4 -Set money=9000,lives=5
      .\SaveEdit.ps1 -Slot 4 -Set gangRespect.0=200
      .\SaveEdit.ps1 -Slot 4 -Unknown
      .\SaveEdit.ps1 -Slot 4 -Dat 0 -Last 8750000
      .\SaveEdit.ps1 -Slot 4 -Force -Set missionCount=10

    Reads/writes the LIVE save dir C:\work\log\player (that is the dir the
    game uses - confirmed by the hiscores.hsc the game rewrites there).
#>

[CmdletBinding()]
param(
    [int]$Slot = 0,
    [switch]$Show,
    [switch]$Unknown,
    [string]$Set,          # "field=value,field=value"
    [int]$Dat = -1,        # .dat record index 0..11
    [long]$Last = -1,      # .dat record "last" (money at last save)
    [long]$Best = -1,      # .dat record "best" (best money ever)
    [switch]$Force,        # allow writing fields marked dangerous
    [string]$PlayerDir = 'C:\work\log\player',
    [string]$BackupDir = 'C:\work\log\exp'
)

$ErrorActionPreference = 'Stop'

$svgPath = Join-Path $PlayerDir "plyslot$Slot.svg"
$datPath = Join-Path $PlayerDir "plyslot$Slot.dat"

# ---------------------------------------------------------------------------
# .svg block0 field manifest.
#   off  - byte offset inside the 1864-byte block0
#   size - 1,2 or 4
#   kind - 'money','count','level','enum','bytes','tokens','mask'
#   danger - true => refuse without -Force (proven to crash the game)
# ---------------------------------------------------------------------------
$script:Fields = [ordered]@{
    'city'           = @{ off=0x4B; size=1; kind='enum';   max=2;  note='current city 0..2' }
    'level'          = @{ off=0x4C; size=1; kind='level';  note='city<<4 | sublevel, 0xFF = none' }
    'gang'           = @{ off=0x4D; size=1; kind='enum';   max=9;  note='current gang 0..9' }
    'money'          = @{ off=0x64; size=4; kind='money';  note='CONFIRMED: written by Player::sub_4A6B20 via GetMoneyPlayer' }
    'multiplier'     = @{ off=0x68; size=4; kind='count';  note='GetMultiPlayer / SetMultiPlayer' }
    'health'         = @{ off=0x6C; size=2; kind='count';  note='Ped::GetHealth' }
    'powerup'        = @{ off=0x6E; size=2; kind='bytes';  count=17; note='bonus types; 11=invisibility 6/9=special fx (see sub_4A5A50)' }
    'field644'       = @{ off=0x90; size=4; kind='count';  count=10; note='unknown, verbatim copy' }
    'unkB8'          = @{ off=0xB8; size=1; kind='bytes';  count=2; note='unknown' }
    'ammo'           = @{ off=0xBA; size=1; kind='bytes';  count=15; note='per-weapon ammo' }
    'gangRespect'    = @{ off=0xC9; size=1; kind='bytes';  count=10; note='respect per gang 0..9' }
    'remap'          = @{ off=0xD3; size=1; kind='enum';   danger=$true; note='weapon remap - table index' }
    'lives'          = @{ off=0xD4; size=1; kind='count';  note='SetMonyeLives' }
    'unkD5'          = @{ off=0xD5; size=1; kind='bytes';  note='unknown' }
    'selectWeapon'   = @{ off=0xD6; size=2; kind='enum';   danger=$true; note='-1 = none; index into arsenal' }
    'field678'       = @{ off=0xD8; size=4; kind='count';  note='unknown, verbatim copy' }
    'field67C'       = @{ off=0xDC; size=4; kind='count';  note='unknown, verbatim copy' }
    'policeStar'     = @{ off=0xE0; size=2; kind='count';  note='wanted level, in-game max 6' }
    'unkE2'          = @{ off=0xE2; size=1; kind='bytes';  count=70; note='NOT written by any known writer' }
    'missionCount'   = @{ off=0x12A; size=2; kind='count'; danger=$true; note='MAP-DERIVED, rebuilt every save' }
    'mask32'         = @{ off=0x12C; size=4; kind='mask';  danger=$true; note='bits -> arr2_15 (32 ids, NOT saved)' }
    'mask25'         = @{ off=0x130; size=4; kind='mask';  danger=$true; note='bits -> arr_12  (25 ids, NOT saved)' }
    'unk742'         = @{ off=0x742; size=1; kind='bytes'; note='unknown' }
    'unk743'         = @{ off=0x743; size=1; kind='bytes'; note='unknown' }
    'tokens'         = @{ off=0x744; size=4; kind='tokens'; note='MapGm::GetSpecialTokens' }
}

$script:Block0Size  = 1864
$script:S63Lo       = 0x710   # memcpy'd into LIVE gObject->S63 (has pointers)
$script:S63Hi       = 0x741
$script:MissionLo   = 0x134
$script:MissionHi   = 0x5E3
$script:ObjLo       = 0x5E4
$script:ObjHi       = 0x70F

# ---------------------------------------------------------------------------
function Read-Bytes([string]$p) {
    if (-not (Test-Path -LiteralPath $p)) { throw "not found: $p" }
    , [IO.File]::ReadAllBytes($p)
}

function Get-FieldValue([byte[]]$b, [hashtable]$f) {
    $o = $f.off
    switch ($f.size) {
        1 { [int]$b[$o] }
        2 { [int][BitConverter]::ToUInt16($b, $o) }
        4 { [int][BitConverter]::ToUInt32($b, $o) }
    }
}

function Set-FieldValue([byte[]]$b, [hashtable]$f, [int]$v) {
    $o = $f.off
    switch ($f.size) {
        1 { $b[$o] = [byte]($v -band 0xFF) }
        2 { [Array]::Copy([BitConverter]::GetBytes([uint16]$v), 0, $b, $o, 2) }
        4 { [Array]::Copy([BitConverter]::GetBytes([uint32]$v), 0, $b, $o, 4) }
    }
}

# Resolve "gangRespect.3" -> {base field, index 3}
function Resolve-Field([string]$spec) {
    $name = $spec; $idx = $null
    if ($spec -match '^(.+)\.(\d+)$') { $name = $Matches[1]; $idx = [int]$Matches[2] }
    if (-not $script:Fields.Contains($name)) {
        throw "unknown field '$name'. known: $($script:Fields.Keys -join ', ')"
    }
    $f = $script:Fields[$name]
    if ($null -ne $idx) {
        if (-not $f.ContainsKey('count')) { throw "field '$name' is not an array" }
        if ($idx -lt 0 -or $idx -ge $f.count) { throw "index $idx out of range 0..$($f.count - 1)" }
        $copy = @{} + $f
        $copy.off = $f.off + $idx * $f.size
        $copy.count = $null; $copy.remove('count')
        return @{ name = "$name.$idx"; f = $copy }
    }
    if ($f.ContainsKey('count') -and $f.count -gt 1) {
        throw "'$name' is an array of $($f.count); use '$name.<0..$($f.count-1)>'"
    }
    return @{ name = $name; f = $f }
}

# ---------------------------------------------------------------------------
# .dat : 18-byte header + 12 records of 9 bytes {u8 flag; u32 best; u32 last}
# Proven by PlayerData::WriteFileNamePlayer (a3 = 126) and by the real slot 0
# where best=0x008953dc / last=0x008583b0 == money 0x64 = 8750000.
# Record index encodes location: arena = idx / 4, sub = idx % 4.
# ---------------------------------------------------------------------------
$script:DatHeader = 18
$script:DatRecSz  = 9
$script:DatRecs   = 12

function Show-Dat([byte[]]$b) {
    if ($b.Length -ne ($script:DatHeader + $script:DatRecs * $script:DatRecSz)) {
        Write-Warning "unexpected .dat length $($b.Length) (expected $($script:DatHeader + $script:DatRecs * $script:DatRecSz))"
    }
    $name = [Text.Encoding]::Unicode.GetString($b, 0, 12) -replace "`0", ''
    Write-Host ""
    Write-Host "=== $datName ($($b.Length) B)  player='$name' ==="
    Write-Host ("  {0,-4} {1,-5} {2,-5} {3,-6} {4,-12} {5,-12}" -f 'rec','city','sub','flag','best','last')
    for ($i = 0; $i -lt $script:DatRecs; $i++) {
        $o = $script:DatHeader + $i * $script:DatRecSz
        if ($o + 9 -gt $b.Length) { break }
        $flag = $b[$o]
        $best = [BitConverter]::ToUInt32($b, $o + 1)
        $last = [BitConverter]::ToUInt32($b, $o + 5)
        Write-Host ("  {0,-4} {1,-5} {2,-5} {3,-6} {4,-12} {5,-12}" -f $i, [int]($i / 4), ($i % 4), $flag, $best, $last)
    }
}

# ---------------------------------------------------------------------------
$datName = "plyslot$Slot.dat"
$svgName = "plyslot$Slot.svg"

if (-not (Test-Path -LiteralPath $svgPath)) {
    throw "no save for slot $Slot ($svgPath missing)"
}

$svg = Read-Bytes $svgPath
if ($svg.Length -lt $script:Block0Size) { throw "block0 truncated: $($svg.Length) B" }

# --- show ------------------------------------------------------------------
if ($Show) {
    $city = $svg[0x4B]; $lvl = $svg[0x4C]; $gang = $svg[0x4D]
    $levelTxt = if ($lvl -eq 0xFF) { 'none' }
                else { "city $($lvl -shr 4), sub $($lvl -band 0x0F)" }
    Write-Host "=== $svgName ($($svg.Length) B)  slot $Slot ==="
    Write-Host ("  city={0}  level=0x{1:X2} ({2})  gang={3}" -f $city, $lvl, $levelTxt, $gang)
    Write-Host ""
    Write-Host ("  {0,-18} {1,-6} {2}" -f 'field','value','note')
    foreach ($k in $script:Fields.Keys) {
        $f = $script:Fields[$k]
        if ($f.ContainsKey('count') -and $f.count -gt 1) {
            $vals = @()
            for ($i = 0; $i -lt $f.count; $i++) {
                $c = @{} + $f; $c.off = $f.off + $i * $f.size; $c.remove('count')
                $vals += (Get-FieldValue $svg $c)
            }
            $warn = if ($f.danger) { '  <-- DANGEROUS, needs -Force' } else { '' }
            Write-Host ("  {0,-18} [{1}]{2}" -f $k, ($vals -join ','), $warn)
        } else {
            $warn = if ($f.danger) { '  <-- DANGEROUS, needs -Force' } else { '' }
            Write-Host ("  {0,-18} {1,-10}{2}  {3}" -f $k, (Get-FieldValue $svg $f), $warn, $f.note)
        }
    }
    # mission table
    $cnt = [BitConverter]::ToUInt16($svg, 0x12A)
    $ne = 0
    for ($i = 0; $i -lt 300; $i++) { if ([BitConverter]::ToUInt16($svg, 0x134 + $i*4) -ne 0) { $ne++ } }
    Write-Host ""
    Write-Host "  mission table @0x134: 300 x {u16 id, u16 extra}, count=$cnt, non-empty=$ne"
    Write-Host "    -> MAP-DERIVED: sub_47EE70 rebuilds it from the live script every save."
    Write-Host "    -> identical in every slot, so it is NOT per-player state."
    $t1 = [BitConverter]::ToUInt32($svg, 0x748)
    Write-Host ("  trailing blocks: {0} / {1} / {2} B (identical in all slots - map constants)" -f $t1, `
        [BitConverter]::ToUInt32($svg, 0x748 + 4 + $t1), `
        [BitConverter]::ToUInt32($svg, 0x748 + 4 + $t1 + 4 + [BitConverter]::ToUInt32($svg, 0x748 + 4 + $t1)))
    if (Test-Path -LiteralPath $datPath) { Show-Dat (Read-Bytes $datPath) }
}

# --- unknown dump ----------------------------------------------------------
if ($Unknown) {
    Write-Host ""
    Write-Host "=== unaccounted regions of block0 (candidate homes for the 5 mission lists) ==="
    $known = New-Object 'System.Collections.Generic.HashSet[int]'
    foreach ($k in $script:Fields.Keys) {
        $f = $script:Fields[$k]
        $n = if ($f.ContainsKey('count')) { $f.count } else { 1 }
        for ($i = 0; $i -lt $n; $i++) {
            for ($j = 0; $j -lt $f.size; $j++) { [void]$known.Add($f.off + $i * $f.size + $j) }
        }
    }
    for ($i = 0; $i -lt $script:Block0Size; $i++) {
        if ($known.Contains($i)) { continue }
        if ($i -ge $script:MissionLo -and $i -le $script:MissionHi) { continue }
        if ($i -ge $script:ObjLo     -and $i -le $script:ObjHi)     { continue }
        if ($i -ge $script:S63Lo     -and $i -le $script:S63Hi)     { continue }
        $lo = $i; while ($i -lt $script:Block0Size -and -not $known.Contains($i) -and
               -not ($i -ge $script:MissionLo -and $i -le $script:MissionHi) -and
               -not ($i -ge $script:ObjLo     -and $i -le $script:ObjHi) -and
               -not ($i -ge $script:S63Lo     -and $i -le $script:S63Hi)) { $i++ }
        $hi = $i - 1
        $len = $hi - $lo + 1
        $hex = ''
        for ($j = $lo; $j -le [Math]::Min($hi, $lo + 23); $j++) { $hex += '{0:x2} ' -f $svg[$j] }
        Write-Host ("  0x{0:X4}..0x{1:X4}  {2,4} B  {3}" -f $lo, $hi, $len, $hex)
    }
}

# --- write -----------------------------------------------------------------
$dirty = $false
$changes = @()

if ($Set) {
    foreach ($pair in $Set -split ',') {
        if ($pair -notmatch '^([^=]+)=(.+)$') { throw "bad -Set item '$pair', expected field=value" }
        $r = Resolve-Field $Matches[1]
        $val = [int]$Matches[2]
        if ($r.f.danger -and -not $Force) {
            throw "'$($r.name)' is marked DANGEROUS (proven crasher). re-run with -Force if you really mean it."
        }
        $old = Get-FieldValue $svg $r.f
        Set-FieldValue $svg $r.f $val
        $changes += ("{0}: {1} -> {2}" -f $r.name, $old, $val)
        $dirty = $true
    }
}

if ($Dat -ge 0) {
    if (-not (Test-Path -LiteralPath $datPath)) { throw "no .dat for slot $Slot" }
    $dat = Read-Bytes $datPath
    $o = $script:DatHeader + $Dat * $script:DatRecSz
    if ($o + 9 -gt $dat.Length) { throw "record $Dat out of range" }
    if ($Best -ge 0) { [Array]::Copy([BitConverter]::GetBytes([uint32]$Best), 0, $dat, $o + 1, 4) }
    if ($Last -ge 0) { [Array]::Copy([BitConverter]::GetBytes([uint32]$Last), 0, $dat, $o + 5, 4) }
    if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
    Copy-Item -LiteralPath $datPath -Destination (Join-Path $BackupDir "orig_plyslot$Slot.dat") -Force
    [IO.File]::WriteAllBytes($datPath, $dat)
    $changes += (".dat rec$Dat : best=$Best last=$Last  (city $($Dat/4) sub $($Dat%4))")
    $dirty = $true
}

if ($dirty) {
    if (-not (Test-Path -LiteralPath $BackupDir)) { New-Item -ItemType Directory -Path $BackupDir -Force | Out-Null }
    Copy-Item -LiteralPath $svgPath -Destination (Join-Path $BackupDir "orig_plyslot$Slot.svg") -Force
    [IO.File]::WriteAllBytes($svgPath, $svg)
    Write-Host ""
    Write-Host "WROTE $svgPath"
    $changes | ForEach-Object { Write-Host "  $_" }
    Write-Host "backup -> $(Join-Path $BackupDir "orig_plyslot$Slot.svg")"
    Write-Host ""
    Write-Host "REMINDER: money in .dat best/last and block0 0x64 both survive a save cycle,"
    Write-Host "  but the game rewrites 0xE2..0x129 and 0x710..0x744 itself - don't expect"
    Write-Host "  those to keep your values, and never write 0x710..0x741 (live S63 pointers)."
}
elseif (-not $Show -and -not $Unknown) {
    Write-Host "nothing to do. use -Show / -Set field=value / -Unknown"
}
