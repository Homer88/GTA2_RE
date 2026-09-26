<#
    svgdiff.ps1 - compare two GTA2 .svg saves byte-by-byte and label every
    difference with the field it belongs to (see tools/SAVE_LAYOUT.md).

    .\svgdiff.ps1 -A old.svg -B new.svg          # diff
    .\svgdiff.ps1 -A save.svg -Show              # annotated dump
    .\svgdiff.ps1 -A save.svg -Region 0x0090,40  # raw hex of one region
#>
param(
    [Parameter(Mandatory = $true)][string]$A,
    [string]$B,
    [switch]$Show,
    [string]$Region,
    [int]$From = 0,
    [int]$To = -1
)

$ErrorActionPreference = 'Stop'

# field start, size, name
$Fields = @(
    @(0x0000, 24, 'mapName'), @(0x0018, 1, 'unk_1(10)'), @(0x0019, 24, 'styleName'),
    @(0x0031, 1, 'unk_2(10)'), @(0x0032, 24, 'scriptName'), @(0x004A, 1, 'unk_3(10)'),
    @(0x004B, 1, 'playerArena'), @(0x004C, 1, 'bonusStage'), @(0x004D, 1, 'gang'),
    @(0x0054, 4, 'posX'), @(0x0058, 4, 'posY'), @(0x005C, 4, 'posZ'), @(0x0060, 2, 'rotation'),
    @(0x0064, 4, 'money'), @(0x0068, 4, 'multiplier'), @(0x006C, 2, 'health'),
    @(0x006E, 34, 'powerupsU16[17]'),
    @(0x0090, 40, 'field644[10]'), @(0x00B8, 2, 'unused'),
    @(0x00BA, 15, 'ammo[15]'), @(0x00C9, 10, 'gangRespect[10]'),
    @(0x00D3, 1, 'remap'), @(0x00D4, 1, 'lives'), @(0x00D5, 1, 'unused'),
    @(0x00D6, 2, 'selectWeapon'), @(0x00D8, 4, 'field678'), @(0x00DC, 4, 'field67C'),
    @(0x00E0, 2, 'wantedLevel'), @(0x00E2, 2, 'unused'), @(0x00E4, 68, 'carSpawn[3]'),
    @(0x0128, 12, 'unknown'), @(0x0134, 1200, 'objectives[300]'),
    @(0x05E4, 300, 'objectState'), @(0x0710, 50, 'S63copy'), @(0x0742, 2, 'unknown'),
    @(0x0744, 4, 'specialToken')
)

function Get-FieldName([int]$off) {
    foreach ($f in $Fields) {
        if ($off -ge $f[0] -and $off -lt ($f[0] + $f[1])) {
            $sub = $off - $f[0]
            if ($f[1] -gt 1 -and $f[2] -match '\[') { return ('{0}+{1}' -f $f[2], $sub) }
            return $f[2]
        }
    }
    $blk = if ($off -ge 0x748) { 'block' + (1 + [int](($off - 0x748) / 700)) } else { 'pad' }
    return $blk
}

function Get-Runs($a, $b) {
    $n = [Math]::Min($a.Length, $b.Length)
    $runs = New-Object System.Collections.Generic.List[object]
    $start = -1
    for ($i = 0; $i -lt $n; $i++) {
        if ($a[$i] -ne $b[$i]) {
            if ($start -lt 0) { $start = $i }
        }
        elseif ($start -ge 0) {
            $runs.Add([pscustomobject]@{ Off = $start; Len = $i - $start })
            $start = -1
        }
    }
    if ($start -ge 0) { $runs.Add([pscustomobject]@{ Off = $start; Len = $n - $start }) }
    return $runs
}

$fa = [IO.File]::ReadAllBytes($A)
Write-Host ("{0}  ({1} bytes)" -f $A, $fa.Length)

if ($Region) {
    $p = $Region.Split(',')
    $s = [Convert]::ToInt32($p[0].Trim().Substring(2), 16)
    $l = [int]$p[1]
    for ($r = 0; $r -lt $l; $r += 16) {
        $line = '  {0:X4}: ' -f ($s + $r)
        for ($i = 0; $i -lt 16 -and ($r + $i) -lt $l; $i++) { $line += '{0:X2} ' -f $fa[$s + $r + $i] }
        Write-Host $line
    }
    return
}

if ($Show) {
    foreach ($f in $Fields) {
        $o = $f[0]; $n = $f[1]
        if ($o -ge $fa.Length) { continue }
        $n = [Math]::Min($n, $fa.Length - $o)
        if ($n -le 0) { continue }
        $bytes = $fa[$o..($o + $n - 1)]
        if (($bytes | Where-Object { $_ -ne 0 }).Count -eq 0) { continue }
        $cap = [Math]::Min($n, 48)
        $txt = ($bytes[0..($cap - 1)] | ForEach-Object { if ($_ -ge 32 -and $_ -lt 127) { [char]$_ } else { '.' } }) -join ''
        $hex = ($bytes[0..($cap - 1)] | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
        if ($n -gt $cap) { $hex += ' ...'; $txt += ' ...' }
        Write-Host ('  {0:X4} {1,-18} {2,-120} "{3}"' -f $o, $f[2], $hex, $txt)
    }
    return
}

if (-not $B) { Write-Host 'need -B (second file) or -Show'; return }

$fb = [IO.File]::ReadAllBytes($B)
Write-Host ("{0}  ({1} bytes)" -f $B, $fb.Length)
if ($fa.Length -ne $fb.Length) { Write-Host "!! size mismatch" }

$runs = Get-Runs $fa $fb
$total = ($runs | Measure-Object -Property Len -Sum).Sum
Write-Host ("-- {0} runs, {1} bytes differ" -f $runs.Count, $total)
Write-Host ""
foreach ($r in $runs) {
    $end = [Math]::Min($r.Off + $r.Len, [Math]::Min($fa.Length, $fb.Length)) - 1
    $name = Get-FieldName $r.Off
    $cnt = [Math]::Min(8, $r.Len)
    $o1 = ($fa[$r.Off..($r.Off + $cnt - 1)] | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
    $o2 = ($fb[$r.Off..($r.Off + $cnt - 1)] | ForEach-Object { '{0:X2}' -f $_ }) -join ' '
    if ($r.Len -gt 8) { $o1 += ' ...'; $o2 += ' ...' }
    Write-Host ('  {0:X4}..{1:X4} ({2,4} B)  {3,-22} A={4}' -f $r.Off, $end, $r.Len, $name, $o1)
    Write-Host ('  {0}      {1,22}   B={2}' -f (' ' * 15), '', $o2)
}
