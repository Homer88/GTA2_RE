<#
    cmpexp.ps1 - GTA2 save experiment matrix.
    Put a baseline copy named "baseline.svg" plus any number of variants
    (each differing from baseline by ONE change) into a folder, then run:

        .\cmpexp.ps1 -Dir C:\work\log\exp

    Prints a matrix: one row per byte that changed in any variant,
    one column per variant, so you can see exactly which offset each
    editor field controls.
#>
param(
    [Parameter(Mandatory = $true)][string]$Dir,
    [string]$Base = 'baseline.svg',
    [int]$MaxRows = 400
)

$ErrorActionPreference = 'Stop'

$Fields = @(
    @(0x0000, 24, 'mapName'), @(0x0018, 1, 'unk_1'), @(0x0019, 24, 'styleName'),
    @(0x0031, 1, 'unk_2'), @(0x0032, 24, 'scriptName'), @(0x004A, 1, 'unk_3'),
    @(0x004B, 1, 'playerArena'), @(0x004C, 1, 'bonusStage'), @(0x004D, 1, 'gang'),
    @(0x0054, 4, 'posX'), @(0x0058, 4, 'posY'), @(0x005C, 4, 'posZ'), @(0x0060, 2, 'rotation'),
    @(0x0064, 4, 'money'), @(0x0068, 4, 'multiplier'), @(0x006C, 2, 'health'),
    @(0x006E, 34, 'powerupsU16[17]'),
    @(0x0090, 40, 'field644[10]'), @(0x00B8, 2, 'unused'),
    @(0x00BA, 15, 'ammo[15]'), @(0x00C9, 10, 'gangRespect[10]'),
    @(0x00D3, 1, 'remap'), @(0x00D4, 1, 'lives'), @(0x00D5, 1, 'unused'),
    @(0x00D6, 2, 'selectWeapon'), @(0x00D8, 4, 'field678'), @(0x00DC, 4, 'field67C'),
    @(0x00E0, 2, 'wantedLevel'), @(0x00E2, 2, 'unused'), @(0x00E4, 68, 'carSpawn[3]'),
    @(0x0128, 12, 'unknown/ids'), @(0x0134, 1200, 'objectiveIds[300]'),
    @(0x05E4, 300, 'objectState'), @(0x0710, 50, 'S63copy'), @(0x0742, 2, 'unknown'),
    @(0x0744, 4, 'specialToken')
)

function Get-FieldName([int]$off) {
    foreach ($f in $Fields) {
        if ($off -ge $f[0] -and $off -lt ($f[0] + $f[1])) {
            $sub = $off - $f[0]
            if ($f[1] -gt 1) { return ('{0}+{1}' -f $f[2], $sub) }
            return $f[2]
        }
    }
    if ($off -lt 0x748) { return 'pad' }
    return 'block' + (1 + [int](($off - 0x748) / 700))
}

$basePath = Join-Path $Dir $Base
if (-not (Test-Path -LiteralPath $basePath)) { throw "baseline not found: $basePath" }
$baseBytes = [IO.File]::ReadAllBytes($basePath)

$files = Get-ChildItem -LiteralPath $Dir -Filter *.svg |
    Where-Object { $_.Name -ne $Base } | Sort-Object Name

if ($files.Count -eq 0) { Write-Host 'no variants found'; return }

# changed-offset sets per file
$data = @()
$all = New-Object System.Collections.Generic.List[int]
foreach ($f in $files) {
    $b = [IO.File]::ReadAllBytes($f.FullName)
    $set = New-Object System.Collections.Generic.List[int]
    $n = [Math]::Min($baseBytes.Length, $b.Length)
    for ($i = 0; $i -lt $n; $i++) {
        if ($baseBytes[$i] -ne $b[$i]) { $set.Add($i); $all.Add($i) }
    }
    $data += [pscustomobject]@{ Name = $f.Name; Bytes = $b; Set = $set }
}

$rows = $all | Sort-Object -Unique
Write-Host ("baseline: {0} ({1} B)   variants: {2}   changed offsets: {3}" -f $Base, $baseBytes.Length, $files.Count, $rows.Count)
Write-Host ''

$w = 14
$hdr = '  {0,-8} {1,-22}' -f 'offset', 'field'
foreach ($d in $data) { $hdr += ('{0,' + $w + '}') -f $d.Name.Replace('.svg', '') }
Write-Host $hdr
Write-Host ('  ' + ('-' * ($hdr.Length - 2)))

$shown = 0
foreach ($off in $rows) {
    if ($shown -ge $MaxRows) {
        Write-Host ("  ... {0} more offsets not shown (raise -MaxRows)" -f ($rows.Count - $shown))
        break
    }
    $line = '  {0,-8} {1,-22}' -f ('0x{0:X4}' -f $off), (Get-FieldName $off)
    foreach ($d in $data) {
        if ($d.Set.Contains($off)) {
            $line += ('{0,' + $w + '}') -f ('{0:X2}>{1:X2}' -f $baseBytes[$off], $d.Bytes[$off])
        }
        else {
            $line += ('{0,' + $w + '}') -f '.'
        }
    }
    Write-Host $line
    $shown++
}
