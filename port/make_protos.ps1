# make_protos.ps1 - сканирует ВСЕ модули, извлекает сигнатуры определений
# и пишет прототипы для кросс-модульных вызовов в port/gta2_protos.h
# (тот же формат имен, что в convert_module.ps1).

param(
  [string]$InRoot = "dump\unified",
  [string]$Out = "port\gta2_protos.h"
)

$sigRe = '(?m)^(?<ret>[A-Za-z_][\w \*<>,\[\]&()]*?)__(?:thiscall|cdecl|stdcall|fastcall)\s+(?:(?<cls>[A-Za-z_]\w*)::)?(?<name>\w+)\s*\((?<params>(?:[^()]|\([^()]*\))*)\)'

# CRT/компиляторный мусор: функции с CRT-типами или внутренними именами исключаются,
# чтобы прото оставались чисто игровыми (кросс-модульные вызовы GTA2).
$badTypeNames = @(
  '_s_HandlerType','_s_CatchableType','_s_ThrowInfo','_s_FuncInfo','_func_int',
  '_PtFuncCompare','_CoreCrtNonSecureSearchSortCompareFunction','INTRNCVT_STATUS',
  '_LDBL12','_LDOUBLE','_CRT_DOUBLE','longlong','_onexit_t','_onexit',
  '__return_ptr','CP_ACP','CP_ACP1','CP_THREAD_ACP','CP_UTF8','CP_OEMCP'
)
$badFuncNames = @(
  'memmove','memcpy','memset','memcmp','strlen','strcpy','strncpy','strcat',
  'strncat','strcmp','strncmp','sprintf','vsprintf','sscanf','fopen','fclose',
  'fread','fwrite','fseek','ftell','malloc','calloc','realloc','free','_exit',
  'exit','abort','qsort','bsearch','_validateExecute','TypeMatch','WinMain'
)
$badPatterns = @('^(?:__|FID_conflict|__ld|__ls)', '^_CxxFrameHelper|^_CxxThrow|^__CxxFrame', '^_corerrmsg')

function Is-CRTBadLine([string]$sig) {
  if ($sig -match '^(?:struct|class|enum)\b.*;\s*$') { return $true }
  foreach ($bt in $badTypeNames) {
    if ($sig -match ("\b" + [regex]::Escape($bt) + "\b")) { return $true }
  }
  foreach ($bf in $badFuncNames) {
    if ($sig -match ("\b" + [regex]::Escape($bf) + "\s*\(")) { return $true }
  }
  return $false
}

# known-типы из clean/enums (для определения недостающих в прото)
$knownTypes = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
foreach ($kt in @('char','short','int','long','float','double','void','bool','unsigned','signed','const','_BYTE','_WORD','_DWORD','_QWORD','byte','word','dword','qword','uchar','uint','ulong','ushort','undefined','undefined1','undefined2','undefined4','undefined8','GLuint','GLenum','GLint','float10','wchar_t','intptr_t','uintptr_t','size_t','SIZE_T','LSTATUS','HKEY','HLOCAL','LRESULT','WPARAM','LPARAM','WCHAR','LPCSTR','LPSTR','LPCWSTR','LPWSTR','LPVOID','PVOID','HANDLE','HWND','HINSTANCE','HMODULE','HDC','HMENU','HICON','HBRUSH','HBITMAP','HFONT','HRESULT','DWORD','WORD','BYTE','BOOL','UINT','LONG','INT','SHORT','CHAR','FLOAT','DOUBLE','LONGLONG','ULONG','DWORD_PTR','ULONG_PTR','INT_PTR','LPDWORD','LPBYTE','PDWORD','PBYTE','FILE','tm','OVERLAPPED','_FILETIME','FILETIME','LPFILETIME','__int8','__int16','__int32','__int64','_BOOL2','_BOOL4','_BY','_SBYTE','_UBYTE')) { [void]$knownTypes.Add($kt) }
foreach ($kf in @('port\gta2_clean.h','port\gta2_enums.h')) {
  if (Test-Path -LiteralPath $kf) {
    $kt = Get-Content -LiteralPath $kf -Raw
    [regex]::Matches($kt, '\b(?:struct|class|union|enum)\s+([A-Za-z_]\w*)') | ForEach-Object { [void]$knownTypes.Add($_.Groups[1].Value) }
    [regex]::Matches($kt, '\btypedef\s+[^;]{1,200}?\b([A-Za-z_]\w*)\s*;') | ForEach-Object { [void]$knownTypes.Add($_.Groups[1].Value) }
  }
}
# enum-теги (чтобы не делать 'struct X' для enum-типов)
$enumTags = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
foreach ($kf in @('port\gta2_enums.h')) {
  if (Test-Path -LiteralPath $kf) {
    $kt = Get-Content -LiteralPath $kf -Raw
    [regex]::Matches($kt, '\benum\s+([A-Za-z_]\w*)') | ForEach-Object { [void]$enumTags.Add($_.Groups[1].Value) }
  }
}
# системные типы, которым НЕЛЬЗЯ делать 'struct X;' (это typedef-теги Windows)
$noForward = @('HKEY','HLOCAL','LRESULT','SIZE_T','LSTATUS','WCHAR','_FILETIME','LPFILETIME','FILE','tm','OVERLAPPED','HANDLE','HWND','HINSTANCE','HMODULE','HDC','HRESULT','DWORD','WORD','BYTE','BOOL','UINT','LONG','INT','SHORT','FLOAT','DOUBLE','CHAR','LONGLONG','ULONG','INT_PTR','LPCSTR','LPSTR','LPCWSTR','LPWSTR','LPVOID','PVOID','BYTE','PDWORD','LPBYTE','wchar_t','intptr_t','__int8','__int16','__int32','__int64','FARPROC','PHKEY','UINT_PTR','USHORT','LPCWCH','time_t','_EXCEPTION_POINTERS','LPDIRECTINPUTDEVICE8','LPCRITICAL_SECTION','_IMAGELISTDRAWPARAMS')

# имена функций (без префикса класса) — конфликтуют с типами в namespace gta2,
# тип-токен такого имени нужно обернуть в 'struct X'
$funcNamesAll = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
Get-ChildItem -LiteralPath $InRoot -Directory | ForEach-Object {
  Get-ChildItem -LiteralPath $_.FullName -Filter *.cpp | ForEach-Object {
    $txt = Get-Content -LiteralPath $_.FullName -Raw
    foreach ($m in [regex]::Matches($txt, $sigRe)) {
      $n = $m.Groups['name'].Value
      if ($n -notmatch '^(?:__|FID_conflict|_validateExecute|TypeMatch|_Cxx|_Throw|_IsException)') { [void]$funcNamesAll.Add($n) }
    }
  }
}
# типы, имена которых совпадают с именами функций (нужно 'struct X' вместо голого X)
$conflictTypeNames = New-Object System.Collections.Generic.List[string]

# заменяет конфликтные типы ТОЛЬКО в позиции имени типа параметра (не имя параметра):
# первый id-токен сегмента (после необязательных const/struct/enum)
function Convert-ConflictTypes([string]$src, [System.Collections.Generic.List[string]]$conf) {
  if (-not $src -or $src.Length -eq 0 -or $conf.Count -eq 0) { return $src }
  $segments = New-Object System.Collections.Generic.List[string]
  $depth = 0; $cur = ''
  foreach ($ch in $src.ToCharArray()) {
    if ($ch -eq '(' -or $ch -eq '[') { $depth++ }
    if ($ch -eq ')' -or $ch -eq ']') { $depth-- }
    if ($ch -eq ',' -and $depth -eq 0) { $segments.Add($cur.Trim()); $cur = ''; continue }
    $cur += $ch
  }
  if ($cur) { $segments.Add($cur.Trim()) }
  $res = New-Object System.Collections.Generic.List[string]
  foreach ($seg in $segments) {
    $s = $seg
    # уже тег 'struct/enum/class/union' — не обёртываем повторно
    if ($s -match '^\s*(?:struct|enum|class|union)\b') { $res.Add($s); continue }
    foreach ($ct in $conf) {
      # тип = первый id-токен сегмента (после необязательных const/ctor prepend)
      $pat = '^\s*(?:const\s+)?(' + [regex]::Escape($ct) + ')(?=\s|\*|$)'
      if ($s -cmatch $pat) {
        if ($enumTags.Contains($ct)) { $s = [regex]::Replace($s, $pat, 'enum $1', 1) }
        else { $s = [regex]::Replace($s, $pat, 'struct $1', 1) }
      }
    }
    $res.Add($s)
  }
  return ($res -join ', ')
}

function Scan-Signatures([bool]$doConflict) {
  $out = @{}
  $conf = $conflictTypeNames
  Get-ChildItem -LiteralPath $InRoot -Directory | ForEach-Object {
    Get-ChildItem -LiteralPath $_.FullName -Filter *.cpp | ForEach-Object {
      $txt = Get-Content -LiteralPath $_.FullName -Raw
      foreach ($m in [regex]::Matches($txt, $sigRe)) {
        $ret = $m.Groups['ret'].Value.Trim()
        if (-not $ret) { continue }
        $cls = $m.Groups['cls'].Value
        $name = $m.Groups['name'].Value
        $params = $m.Groups['params'].Value
        $params = [regex]::Replace($params, '(?<cls2>[A-Za-z_]\w*)\s*\*\s*this\b', '$1 *self')
        $params = [regex]::Replace($params, '\bthis\b', 'self')
        # константа enum CarModel::Taxi конфликтует с struct Taxi (игровая сигнатура Taxi_*),
        # в прото используем теговое имя 'struct Taxi'
        $params = [regex]::Replace($params, '\bTaxi\b', 'struct Taxi')
        $ret = [regex]::Replace($ret, '\bTaxi\b', 'struct Taxi')
        # конфликтные типы (имя типа == имя функции): оборачиваем только тип
        if ($doConflict -and $conf.Count -gt 0) {
          $params = Convert-ConflictTypes $params $conf
          $ca = Convert-ConflictTypes $ret $conf
          if ($ca -and $ca -notmatch '^\s*(void|bool|char|short|int|long|float|double)\s*$') { $ret = $ca }
        }
        $line = "$ret $name($params)"
        if ($name -match '^(?:__|FID_conflict|_validateExecute|TypeMatch|_Cxx|_Throw|_IsException)') { continue }
        if ($name -match '^(if|for|while|switch|return|else|do|new|delete|int|char|void|struct|class|enum|union|template|typename|sizeof|this|true|false|namespace|using|static|const|inline|public|private|protected)$') { continue }
        if (Is-CRTBadLine $line) { continue }
        $q = if ($cls) { "$cls" + "_" } else { "" }
        $out["gta2::$q$name"] = "$ret $q$name($params);"
      }
    }
  }
  return $out
}

# проход 1: без обёртки, чтобы понять недостающие типы (forward-структуры)
$protos = Scan-Signatures $false

# --- сбор недостающих типов: типы из ret-позиции и параметров (не имена функций) ---
$missing = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
foreach ($p in $protos.Values) {
  # разделяем "ret name(params);" => ret = всё до последнего идентификатора перед '('
  $m2 = [regex]::Match($p, '^(?<ret>.+?)\s+[A-Za-z_]\w*\s*\((?<params>.*)\);?\s*$')
  if (-not $m2.Success) { continue }
  $ret = $m2.Groups['ret'].Value
  $params = $m2.Groups['params'].Value
  # ret: последний токен
  $toks = [regex]::Matches($ret, '[A-Za-z_][A-Za-z0-9_]*')
  foreach ($t in $toks) {
    if ($t.Value -match '^(__|struct|class|enum|const)') { continue }
    if (-not $knownTypes.Contains($t.Value)) { [void]$missing.Add($t.Value); break }
  }
  # params: тип перед именем параметра
  foreach ($pm in [regex]::Matches($params, '(?<t>[A-Za-z_][A-Za-z0-9_]*)\s+(?:\*\s*)?(?:[A-Za-z_]\w*|struct\s+\w+)\s*(?:,|\[|\)|$)')) {
    $tt = $pm.Groups['t'].Value
    if ($tt -match '^(__|struct|class|enum|const)') { continue }
    if (-not $knownTypes.Contains($tt)) { [void]$missing.Add($tt) }
  }
}

# конфликтные типы из knownTypes + реальные forward-структуры
foreach ($tn in $knownTypes) { if ($funcNamesAll.Contains($tn)) { $conflictTypeNames.Add($tn) } }
foreach ($mt in $missing) {
  if ($noForward -contains $mt) { continue }
  if ($mt -match '^S\d+$') { continue }
  if ($funcNamesAll.Contains($mt)) { $conflictTypeNames.Add($mt) }
}

# проход 2: финальный, с обёрткой конфликтных типов
$protos = Scan-Signatures $true

$sb = New-Object System.Text.StringBuilder
[void]$sb.AppendLine('// Автосгенерировано: make_protos.ps1')
[void]$sb.AppendLine('#pragma once')
foreach ($mt in ($missing | Sort-Object)) {
  if ($noForward -contains $mt) { continue }
  if ($mt -match '^(S\d+)$') { continue }   # S97 и т.п. — возможные enum-константы
  [void]$sb.AppendLine("struct $mt;")
}
if ($missing.Count -gt 0) { [void]$sb.AppendLine('') }
[void]$sb.AppendLine('namespace gta2 {')
foreach ($p in ($protos.Values | Sort-Object)) {
  [void]$sb.AppendLine('  ' + $p)
}
# ручные дополнения (функции вне unified-зоны)
if (Test-Path -LiteralPath 'port\protos_supplement.h') {
  foreach ($line in Get-Content -LiteralPath 'port\protos_supplement.h') {
    if ($line -match '^\s*//') { continue }
    $ln = $line.Trim()
    if (-not $ln) { continue }
    $name = $null
    foreach ($mm in [regex]::Matches($ln, '([A-Za-z_]\w*)\s*\(')) { $name = $mm.Groups[1].Value }
    if ($name -and -not $protos.ContainsKey("gta2::$name")) { [void]$sb.AppendLine('  ' + $ln) }
  }
}
[void]$sb.AppendLine('}')
Set-Content -LiteralPath $Out -Value $sb.ToString() -Encoding ascii
"protos: $($protos.Count) -> $Out (missing forward: $($missing.Count), skipped: $((@($missing | Where-Object { $noForward -contains $_ })).Count + (@($missing | Where-Object { $_ -match '^S\d+$' })).Count), conflictTypes: $($conflictTypeNames.Count))"