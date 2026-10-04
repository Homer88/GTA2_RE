# clean_header.ps1 - вычищает из dump/unified/gta2_unified.h мусор Ghidra,
# оставляя игровые структуры, #define и типы.

param(
  [string]$InPath  = "dump\unified\gta2_unified.h",
  [string]$OutPath = "port\gta2_clean.h"
)

$junkTokens = @(
  'std::', 'wil::', 'wistd::', 'Microsoft::', '__cppobj', '_Tlg',
  'ComTrace', 'ComTelemetry', 'ActivityBase',
  'CachedEventHandleTraits', 'CachedCallEventTraits',
  'OleClipboard', 'DragDropLogging', 'MbmTelemetry',
  'TypeResolutionTelemetry', 'exception_vtbl', 'nested_exception',
  'TypeInfoVtbl', 'CALLFRAME_CACHE', 'ThreadLocalFailureInfo',
  'ThreadLocalData', 'ThreadFailureCallback', 'IFailureCallback',
  'IFunctor', 'wnf_subscription'
)

# теги, которые windows.h уже определяет - выбрасываем блок целиком (до '};')
$structBlockList = @(
  '_GUID', 'tagRECT', 'tagPOINT', 'tagWNDCLASSA', 'tagWNDCLASSW',
  'HINSTANCE__', 'HICON__', 'HBRUSH__',
  'FuncInfoV1', 'UnwindMapEntry', 'type_info', '_PMD',
  'CDefClient', 'CDDEServer', 'CDdeObject', 'SDK_SchemaEntryLongNames'
)

# выбросить весь блок 'struct X ...;' если X в списке выше.
# токены-атрибуты MSVC из Ghidra, которые нельзя ставить в объявлениях
$attrStrip = @(
  '\b__hex\b', '\b__udec\b', '\b__dec\b', '\b__tabform\([^)]*\)',
  '\b__off\b', '\b__strlit\([^)]*\)', '\b__unaligned\b'
)

$srcLines = Get-Content -LiteralPath $InPath

# --- проход 1: собрать имена типов struct/class/union/enum ---
$typeNames = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
foreach ($sl in $srcLines) {
  $tt = $sl.TrimStart() -replace '\b__(?:udec|dec|bitmask)\b', ''
  if ($tt -match '^(?:struct|class|union|enum)\s+([A-Za-z_][A-Za-z0-9_]*)' -and $Matches[1] -notmatch '^__') {
    [void]$typeNames.Add($Matches[1])
  }
}

# --- проход 2: построчная трансформация для устранения тёзок КАРТЕЖ -> TYPE NAME
# внутри тел структур: префиксуем тип ключевым словом (struct/enum), если он в списке имён.
$dst = [System.Collections.Generic.List[string]]::new()
$inJunkBlock = $false
$inStructBlock = $false
$inBody = $false   # внутри тела какой-либо struct/class/enum (для трансформации тёзок)

function Fix-TypeLine([string]$line) {
  # отрезаем атрибуты MSVC в начале строки поля
  $attrPrefix = ''
  $tmp = $line
  while ($true) {
    if ($tmp -match '^__declspec\([^)]*\)\s*') {
      $attrPrefix += $Matches[0]
      $tmp = $tmp.Substring($Matches[0].Length)
    }
    elseif ($tmp -match '^__unaligned\s+') {
      $attrPrefix += ' '
      $tmp = $tmp -replace '^__unaligned\s+', ''
    }
    elseif ($tmp -match '^const\s+') {
      $attrPrefix += $Matches[0]
      $tmp = $tmp.Substring($Matches[0].Length)
    }
    else { break }
  }
  # теперь '<TYPE> ...;' — type не должен начинаться с '__'
  if ($tmp -match '^(?<name>[A-Za-z_][A-Za-z0-9_]*)\s+(?<rest>[^;]*);\s*$' -and $tmp -notmatch '^__') {
    $n = $Matches['name']
    if ($typeNames.Contains($n) -and $n -notmatch '^__') {
      $kw = 'struct'
      if ($enumNames.Contains($n)) { $kw = 'enum' }
      return "$attrPrefix$kw $($Matches['name']) $($Matches['rest']);"
    }
  }
  return $line
}

$enumNames = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
foreach ($sl in $srcLines) {
  $tt = $sl.TrimStart() -replace '\b__(?:udec|dec|bitmask)\b', ''
  if ($tt -match '^enum\s+([A-Za-z_][A-Za-z0-9_]*)' -and $Matches[1] -notmatch '^__') { [void]$enumNames.Add($Matches[1]) }
}

foreach ($srcLine in $srcLines) {
  $t = $srcLine.TrimStart()

  foreach ($pat in $attrStrip) {
    $t = $t -replace $pat, ''
  }

  if ($t -like 'struct __cppobj*') { $inJunkBlock = $true }
  if ($inJunkBlock) {
    if ($t -eq '};') { $inJunkBlock = $false }
    continue
  }

  if ($inStructBlock) {
    if ($t -eq '};') { $inStructBlock = $false }
    continue
  }

  if ($t -like 'struct*' -or $t -like 'class*' -or $t -like 'enum*') {
    if ($srcLine.Contains('<') -or $srcLine.Contains('>') -or $srcLine.Contains('::')) { continue }
    $tag = ($t -replace '^(struct|class|enum)\s+([A-Za-z_][A-Za-z0-9_]*)', '$2')
    if ($structBlockList -contains $tag) { $inStructBlock = $true; continue }
    $isJunk = $false
    foreach ($tok in $junkTokens) {
      if ($srcLine.IndexOf($tok, [System.StringComparison]::OrdinalIgnoreCase) -ge 0) {
        $isJunk = $true
        break
      }
    }
    if ($isJunk) { continue }
    $inBody = $t -match '\{$'
  }

  if ($t -eq '{') { $inBody = $true }
  elseif ($t -eq '};') { $inBody = $false }

  if ($inBody) { $t = Fix-TypeLine $t }

  [void]$dst.Add($t)
}

Set-Content -LiteralPath $OutPath -Value $dst -Encoding ascii
"cleaned lines: $($dst.Count) (was $($srcLines.Count)) -> $OutPath"