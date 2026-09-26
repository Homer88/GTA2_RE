<#
    datdump.ps1 - decode GTA2 plyslotN.dat
    .\datdump.ps1 -Dir C:\work\log\player
#>
param([string]$Dir = 'C:\work\log\player')

$ErrorActionPreference = 'Stop'

foreach ($f in Get-ChildItem -LiteralPath $Dir -Filter 'plyslot*.dat' | Sort-Object Name) {
    $b = [IO.File]::ReadAllBytes($f.FullName)
    $name = ([Text.Encoding]::Unicode.GetString($b, 0, 18) -replace "`0", '')
    Write-Host ("{0}  name='{1}'" -f $f.Name, $name)
    Write-Host ('  {0,-5} {1,-4} {2,-12} {3,-12} {4}' -f 'rec', 'city', 'sub', 'best', 'last')
    $cities = @(); $levels = @()
    for ($n = 0; $n -lt 12; $n++) {
        $o = 18 + 9 * $n
        $flag = $b[$o]
        $best = [BitConverter]::ToUInt32($b, $o + 1)
        $last = [BitConverter]::ToUInt32($b, $o + 5)
        $city = [int][Math]::Floor($n / 4); $sub = $n % 4
        $mark = if ($flag -ne 0) { '*' } else { ' ' }
        Write-Host ('  {0}{1,-4} {2,-4} {3,-4} {4,-12} {5,-12}' -f $mark, $n, $city, $sub, $best, $last)
        if ($flag -ne 0) {
            if ($sub -eq 0) { $cities += $city } else { $levels += "c$city.s$sub" }
        }
    }
    $sumBest = 0; $sumLast = 0
    for ($n = 0; $n -lt 12; $n++) { $sumBest += [BitConverter]::ToUInt32($b, 19 + 9 * $n); $sumLast += [BitConverter]::ToUInt32($b, 23 + 9 * $n) }
    Write-Host ("  => cities unlocked (SubSlot[0]): {0}   extra levels done: {1}" -f (($cities | Sort-Object) -join ','), ($levels -join ','))
    Write-Host ("  => total best = {0}   total last = {1}" -f $sumBest, $sumLast)
    Write-Host ''
}
