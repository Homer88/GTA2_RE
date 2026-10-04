# extract_enums.ps1 - извлекает игровые enum-определения IDA-дампа,
# которых нет в gta2_clean.h, в port\gta2_enums.h.
# Источник: dump\IDA\gta2.exe.h, игровой диапазон до Windows-SDK реконструкции.

param(
  [string]$IdaHeader   = "dump\IDA\gta2.exe.h",
  [string]$CleanHeader = "port\gta2_clean.h",
  [string]$OutPath     = "port\gta2_enums.h",
  [int]$MaxLine        = 10710
)

# имена enum, которые уже есть в clean header (чтобы не дублировать)
$existing = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
foreach ($line in (Get-Content -LiteralPath $CleanHeader)) {
  if ($line -match '^\s*enum\s+(?:__[A-Za-z0-9_]+\s+)?([A-Za-z_][A-Za-z0-9_]*)') {
    [void]$existing.Add($Matches[1])
  }
}

# имена SDK-мусора, которые не нужно переносить
$sdkNames = @(
  'EXCEPTION_DISPOSITION', 'tagINVOKEKIND', 'tagFUNCKIND', 'FVTEXTTYPE',
  'WICBitmapAlphaChannelOption', 'ProviderOptions', 'SE_WS_APPX_SIGNATURE_ORIGIN',
  'PS_MITIGATION_OPTION', 'NT_PRODUCT_TYPE', 'ALTERNATIVE_ARCHITECTURE_TYPE',
  'TP_CALLBACK_PRIORITY', 'KSPIN_LOCK_QUEUE_NUMBER', 'POOL_TYPE', 'EX_POOL_PRIORITY',
  'EVENT_TYPE', 'PP_NPAGED_LOOKASIDE_NUMBER', 'EX_GEN_RANDOM_DOMAIN',
  'FILE_INFORMATION_CLASS', 'DIRECTORY_NOTIFY_INFORMATION_CLASS', 'FSINFOCLASS',
  'DEVICE_RELATION_TYPE', 'BUS_QUERY_ID_TYPE', 'DEVICE_TEXT_TYPE',
  'DEVICE_USAGE_NOTIFICATION_TYPE', 'SYSTEM_POWER_STATE', 'POWER_STATE_TYPE',
  'POWER_ACTION', 'IO_PRIORITY_HINT', 'MEMORY_CACHING_TYPE', 'MM_PAGE_ACCESS_TYPE',
  'PF_FILE_ACCESS_TYPE', 'DEVICE_POWER_STATE', 'DEVICE_WAKE_DEPTH',
  'WHEA_ERROR_SOURCE_TYPE', 'WHEA_ERROR_SOURCE_STATE', 'WHEA_EVENT_LOG_ENTRY_TYPE',
  'WHEA_EVENT_LOG_ENTRY_ID', 'WHEA_ERROR_TYPE', 'WHEA_ERROR_SEVERITY',
  'WHEA_ERROR_PACKET_DATA_FORMAT', 'RTLP_CSPARSE_BITMAP_STATE',
  'RTLP_HP_ADDRESS_SPACE_TYPE', 'RTLP_HP_LOCK_TYPE', 'HEAP_FAILURE_TYPE',
  'LDR_DLL_LOAD_REASON', 'HEAP_LFH_LOCKMODE', 'HEAP_SEG_RANGE_TYPE',
  'RTLP_HP_ALLOCATOR', 'IO_RATE_CONTROL_TYPE', 'KINTERRUPT_POLARITY',
  'JOBOBJECTINFOCLASS', 'PROCESS_SECTION_TYPE', 'RTLP_HP_MEMORY_TYPE'
)

$src = Get-Content -LiteralPath $IdaHeader
$out = [System.Collections.Generic.List[string]]::new()
$i = 0
$n = $src.Count

while ($i -lt $n) {
  $line = $src[$i]
  if ($line -match '^(\s*)enum\s+(?:__[A-Za-z0-9_]+\s+)?([A-Za-z_][A-Za-z0-9_]*)') {
    $name = $Matches[2]
    $take = $false
    if ($i -gt 2400 -and $i -lt $MaxLine -and -not $name.StartsWith('_')) {
      if (-not $existing.Contains($name) -and ($sdkNames -notcontains $name)) {
        $take = $true
      }
    }
    if ($take) {
      $block = [System.Collections.Generic.List[string]]::new()
      [void]$block.Add($line)
      $j = $i + 1
      while ($j -lt $n -and $src[$j] -notmatch '^\s*}\s*;') {
        [void]$block.Add($src[$j])
        $j++
      }
      if ($j -lt $n) { [void]$block.Add($src[$j]) }
      foreach ($bl in $block) {
        [void]$out.Add(($bl -replace '\b__(?:udec|dec|bitmask)\b', ''))
      }
      [void]$out.Add('')
      $i = $j
      continue
    }
  }
  $i++
}

Set-Content -LiteralPath $OutPath -Value $out -Encoding ascii
"enums written: $(( $out -join "`n" | Select-String '^enum ' -AllMatches).Matches.Count -join '')"
# проще: посчитать
$cnt = 0
foreach ($l in $out) { if ($l -match '^enum ') { $cnt++ } }
"enums written: $cnt -> $OutPath"