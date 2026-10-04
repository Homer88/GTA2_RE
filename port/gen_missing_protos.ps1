# gen_missing_protos.ps1 - генерирует port/missing_protos.h из компиляторного лога.
#
# Зачем: часть функций вызывается в декомпиляции, но не имеет тела в dump
# (Miles Sound System AIL_*, gbh_*, внешние SDK и декомпилятор-артефакты).
# MSVC на них даёт C3861 ("missing return type") и C2039 (нет члена "gta2").
# Здесь такие имена собираются из лога и объявляются как extern int f(...).

param(
  [Parameter(Mandatory = $true)][string]$Log,
  [string]$Out = "port\missing_protos.h"
)

if (-not (Test-Path -LiteralPath $Log)) { throw "log not found: $Log" }

$raw = Get-Content -LiteralPath $Log -Raw
# логи MSVC читаются как Default (cp866); если уже UTF-8 - читаем как есть
if ($raw -match '\uFFFD') { $raw = [System.IO.File]::ReadAllText($Log, [System.Text.Encoding]::GetEncoding(1251)) }

$names = New-Object 'System.Collections.Generic.HashSet[string]'
foreach ($line in ($raw -split "`r?`n")) {
  if ($line -notmatch 'error C(3861|2039)') { continue }
  $m = [regex]::Match($line, 'C3861:\s*[`"'']?(?<n>[A-Za-z_]\w*)')
  if (-not $m.Success) { $m = [regex]::Match($line, 'C2039:\s*"(?<n>[A-Za-z_]\w*)"') }
  if ($m.Success) { [void]$names.Add($m.Groups['n'].Value) }
}

# уже объявленные / определённые - не дублируем
$known = New-Object 'System.Collections.Generic.HashSet[string]'
foreach ($h in @('port\gta2_protos.h','port\protos_supplement.h')) {
  if (-not (Test-Path -LiteralPath $h)) { continue }
  foreach ($ln in Get-Content -LiteralPath $h) {
    $m = [regex]::Match($ln, '([A-Za-z_]\w*)\s*\(')
    if ($m.Success) { [void]$known.Add($m.Groups[1].Value) }
  }
}

# имена, которые MSVC ошибочно выдаёт за функции, но которые являются типами/полями
# (C3861 срабатывает на "неизвестный идентификатор" в декомпиляции, а не только на вызов)
$typeNames = @(
  'FILE','GLuint','GLenum','GLint','HANDLE','HWND','HDC','HINSTANCE','BOOL','BYTE','WORD',
  'DWORD','UINT','INT','LONG','ULONG','FLOAT','DOUBLE','CHAR','WCHAR','LPSTR','LPCSTR',
  'LPVOID','LPBYTE','LPWORD','LPDWORD','SIZE_T','HRESULT','LRESULT','WPARAM','LPARAM',
  'Car10','Sprite','EventHandler','AIState','S7','GameObject','ped3','SpriteS3','Matrix3DArray',
  'arg0','dest','this_00','this_01','code','int3','MEMORY','Len','uint32_t','uint3','ulonglong',
  'retaddr','ReturnedString','local_20','local_44','nullsub_76','a5','p1S371','param_3',
  'self','skilPolice','v1','v51','partOfLoadScrip','gGraeme','SNG','FontEnglish','FontJapan',
  'ExceptionList','DestructorS801','FileName','PCM_FORMAT','PedModel','PlayerSlotSave_des',
  'S101_des','S125_Dec','S151_des','S152','S200_des','S371','S372','S40_Des','S41_Dec',
  'S46_Des','S58_Des','S63_dec','S65_dec','S67_Des','S71_Dec','S82_Des','S83_des','S94_Des',
  'Weapon_dec','stru_669B70','stru_66AC54','stru_66AD3C','stru_66ADE0','stru_66B76C',
  'log_random','log_routefinder','do_kill_phones_on_answer','do_show_imaginary',
  'do_show_traffic_lights_info','do_text_id_test','show_brief_number','skip_audio',
  'skip_buses','skip_dummies','skip_trains','skip_user','do_free','findFilePis'
)

$sb = New-Object System.Text.StringBuilder
[void]$sb.AppendLine('// missing_protos.h - авто-генерация: gen_missing_protos.ps1 <log>')
[void]$sb.AppendLine('// Функции, вызываемые в декомпиляции, но без тел в dump (Miles SDK,')
[void]$sb.AppendLine('// gbh_*, внешние библиотеки). Объявляются как int f(...) - точный')
[void]$sb.AppendLine('// возвращаемый тип из лога не восстановить, этого достаточно для сборки.')
[void]$sb.AppendLine('#pragma once')
[void]$sb.AppendLine('namespace gta2 {')
$emitted = 0
$typeClash = @()
# имена, совпадающие с объявленными структурами: "int Ped();" конфликтует со
# "struct Ped" и ломает парсинг всех последующих объявлений -> пропускаем.
$structNames = New-Object 'System.Collections.Generic.HashSet[string]'
if (Test-Path -LiteralPath 'port\gta2_clean.h') {
  foreach ($ln in Get-Content -LiteralPath 'port\gta2_clean.h') {
    $m = [regex]::Match($ln, '^struct\s+(?<n>[A-Za-z_]\w*)\b')
    if ($m.Success) { [void]$structNames.Add($m.Groups['n'].Value) }
  }
}
foreach ($n in ($names | Sort-Object)) {
  if ($known.Contains($n)) { continue }
  if ($typeNames -contains $n) { continue }
  if ($structNames.Contains($n)) { $typeClash += $n; continue }
  [void]$sb.AppendLine("int $n();")
  $emitted++
}
[void]$sb.AppendLine('}')

Set-Content -LiteralPath $Out -Value $sb.ToString() -Encoding ascii
"missing_protos: $($names.Count) candidates, $emitted emitted, skipped type-clash: $($typeClash -join ',') -> $Out"
