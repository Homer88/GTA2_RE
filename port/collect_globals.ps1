# collect_globals.ps1 - сканирует ВСЕ модули, собирает токены глобалей данных
# (unk_*/DAT_*) и пишет объявления extern в port/gta2_globals.h

param(
  [string]$InRoot = "dump\unified",
  [string]$Out = "port\gta2_globals.h"
)

# IDA-префикс -> тип
$prefType = @{
  'C'        = 'char'
  'byte'     = 'unsigned char'
  'word'     = 'unsigned short'
  'dword'    = 'unsigned int'
  'qword'    = 'unsigned __int64'
  'unk'      = 'unsigned char'
  'DAT'      = 'unsigned char'
  'float'    = 'float'
  'flt'      = 'float'
  'dbl'      = 'double'
  'off'      = 'void *'
  'PTR'      = 'void *'
  'arr'      = 'unsigned char'
  'sbyte'    = 'signed char'
  'rbyte'    = 'unsigned char'
  'rword'    = 'unsigned short'
  'a'        = 'char *'
}

$tokens = @{}
Get-ChildItem -LiteralPath $InRoot -Directory | ForEach-Object {
  $mod = $_.Name
  Get-ChildItem -LiteralPath $_.FullName -Filter *.cpp | ForEach-Object {
    $txt = Get-Content -LiteralPath $_.FullName -Raw
    foreach ($m in [regex]::Matches($txt, '(?<![A-Za-z0-9_])_?(?<pref>[A-Za-z][A-Za-z]*)_[0-9A-Fa-f]{4,8}(?![A-Za-z0-9])')) {
      $tokens[$m.Value] = $m.Groups['pref'].Value
    }
  }
}

$sb = New-Object System.Text.StringBuilder
[void]$sb.AppendLine('// ���ᣥ���஢���: collect_globals.ps1')
[void]$sb.AppendLine('#pragma once')
[void]$sb.AppendLine('// ������� ������ �� ���������권, �� ������ IDA (��-�������� - unsigned char):')
foreach ($t in ($tokens.Keys | Sort-Object)) {
  $pref = $tokens[$t]
  $type = $prefType[$pref]
  if (-not $type) { continue }
  [void]$sb.AppendLine("extern $type $t;")
}

# ручные дополнения: именованные глобалы (из IDA.c / usage)
if (Test-Path -LiteralPath 'port\globals_supplement.h') {
  foreach ($line in Get-Content -LiteralPath 'port\globals_supplement.h') {
    if ($line -match '^\s*//') { continue }
    $ln = $line.Trim()
    if ($ln) { [void]$sb.AppendLine($ln) }
  }
}

# курируемый список глобалов-массивов (используются с индексацией, но собираются скалярами)
$arrayGlobals = @('flt_595EDC','flt_595EE4','flt_595EE8','flt_595EEC','dword_595EE0','dword_595EE8','dword_595EF0','dword_595EF8','dword_5CC2C8','flt_595EF4','flt_595EFC','flt_599EF0','flt_599EF4','flt_599EF8','flt_599EFC','flt_599F00','flt_599F04','flt_599F08','flt_599F0C','flt_599F10','flt_599F14','flt_599F18','flt_599F1C')

Set-Content -LiteralPath $Out -Value $sb.ToString() -Encoding ascii
foreach ($ag in $arrayGlobals) {
  $cur = "$Out".ToString()
  $l = ((Select-String -LiteralPath $Out -Pattern ('extern\s+\S[^;]*\s+' + [regex]::Escape($ag) + ';') | Select-Object -First 1).Line)
  if ($l) { $l2 = $l -replace ';$', '[0x4000];'; (Get-Content -LiteralPath $Out) -replace [regex]::Escape($l), $l2 | Set-Content -LiteralPath $Out -Encoding ascii }
}
"globals: $($sb.ToString().Split([string]::new([char]10).TrimEnd(),[stringsplitoptions]::RemoveEmptyEntries).Length) -> $Out"