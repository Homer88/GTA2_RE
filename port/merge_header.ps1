# merge_header.ps1 - собирает портируемый заголовок gta2_clean.h:
#   1) берёт ИГРОВУЮ ЗОНУ из dump/unified/gta2_unified.h (строки 1..EndLine);
#   2) применяет построчную очистку (junk tokens, блоклисты, Fix-TypeLine);
#   3) добавляет ПРОПАВШИЕ типы из dump/IDA/gta2.exe.h, которых нет в unified
#      (struct __fixed ... + ArrowTrace + enum MenuActions + DirectInput typedef);
#   4) ТОПОЛОГИЧЕСКАЯ СОРТИРОВКА struct-блоков по зависимостям "по значению".

param(
  [string]$UnifiedPath = "C:\work\GTA2_RE\dump\unified\gta2_unified.h",
  [string]$IDAPath     = "C:\work\GTA2_RE\dump\IDA\gta2.exe.h",
  [string]$OutPath     = "C:\work\GTA2_RE\port\gta2_clean.h",
  [int]$EndLine        = 7850,
  [int]$IdaZoneEnd     = 10600
)

# ---------------------------------------------------------------- (0) конфигурация
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

$structBlockList = @(
  # SDK-хэндлы / базовые типы windows.h
  '_GUID', 'tagRECT', 'tagPOINT', 'tagWNDCLASSA', 'tagWNDCLASSW',
  'HINSTANCE__', 'HICON__', 'HBRUSH__', 'HWND__', 'HDC__', 'HMENU__',
  'HPEN__', 'HBITMAP__', 'HFONT__', 'HMONITOR__', 'HKEY__',
  'FuncInfoV1', 'UnwindMapEntry', 'type_info', '_PMD',
  'CDefClient', 'CDDEServer', 'CDdeObject', 'SDK_SchemaEntryLongNames',
  'LIST_ENTRY64', 'LIST_ENTRY32', 'RTL_HP_ENV_HANDLE',
  'BATTERY_REPORTING_SCALE', 'SYSTEM_POWER_CAPABILITIES',
  # COM/OLE
  'IDispatch', 'IDispatchVtbl', 'tagVARIANT', 'tagEXCEPINFO',
  'tagSAFEARRAY', 'tagSAFEARRAYBOUND', 'tagTYPEDESC', 'tagTYPEATTR',
  'tagPARAMDESC', 'tagFUNCDESC', 'tagVARDESC', 'tagARRAYDESC',
  'tagSTATSTG', 'tagSIZE', 'IUnknown', 'IUnknownVtbl', 'ITypeInfo',
  'ITypeInfoVtbl', 'ITypeLib', 'ITypeLibVtbl', 'ITypeComp',
  'ITypeCompVtbl', 'IRecordInfo', 'IRecordInfoVtbl', 'IMoniker',
  'IMonikerVtbl', 'IStream', 'IStreamVtbl', 'IBindCtx', 'IBindCtxVtbl',
  'IEnumMoniker', 'IEnumMonikerVtbl', 'IRunningObjectTable',
  'IRunningObjectTableVtbl', 'IEnumString', 'IEnumStringVtbl',
  'tagBIND_OPTS',
  # DirectDraw / Direct3D
  'IDirectDrawPalette', 'IDirectDrawPaletteVtbl', 'IDirectDraw',
  'IDirectDrawVtbl', 'IDirectDrawSurface', 'IDirectDrawSurfaceVtbl',
  'IDirectDrawClipper', 'IDirectDrawClipperVtbl', 'IDirectDraw2',
  'IDirectDraw2Vtbl', 'IDirectDraw4', 'IDirectDraw4Vtbl', 'IDirectDraw7',
  'IDirectDraw7Vtbl', 'IDirectDrawSurface2', 'IDirectDrawSurface2Vtbl',
  'IDirectDrawSurface3', 'IDirectDrawSurface3Vtbl',
  'IDirectDrawSurface4', 'IDirectDrawSurface4Vtbl',
  'IDirectDrawSurface7', 'IDirectDrawSurface7Vtbl',
  'IDirect3D9', 'IDirect3DDevice9', 'IDirect3DDevice9Vtbl',
  'IDirect3DSurface9', 'IDirect3DSurface9Vtbl', 'IDirect3DTexture9',
  'IDirect3DTexture9Vtbl', 'IDirect3DVolumeTexture9',
  'IDirect3DVolumeTexture9Vtbl', 'IDirect3DCubeTexture9',
  'IDirect3DCubeTexture9Vtbl', 'IDirect3DVolume9', 'IDirect3DVolume9Vtbl',
  'IDirect3DVertexBuffer9', 'IDirect3DVertexBuffer9Vtbl',
  'IDirect3DIndexBuffer9', 'IDirect3DIndexBuffer9Vtbl',
  'IDirect3DBaseTexture9', 'IDirect3DBaseTexture9Vtbl',
  'IDirect3DStateBlock9', 'IDirect3DStateBlock9Vtbl',
  'IDirect3DVertexDeclaration9', 'IDirect3DVertexDeclaration9Vtbl',
  'IDirect3DVertexShader9', 'IDirect3DVertexShader9Vtbl',
  'IDirect3DPixelShader9', 'IDirect3DPixelShader9Vtbl',
  'IDirect3DQuery9', 'IDirect3DQuery9Vtbl', 'IDirect3DSwapChain9',
  'IDirect3DSwapChain9Vtbl', 'ICreateDevEnum', 'ICreateDevEnumVtbl',
  'IOleInPlaceUIWindow', 'IOleInPlaceUIWindowVtbl',
  'IOleInPlaceActiveObject', 'IOleInPlaceActiveObjectVtbl',
  'IOleAdviseHolder', 'IOleAdviseHolderVtbl', 'IAdviseSink',
  'IAdviseSinkVtbl', 'IEnumSTATDATA', 'IEnumSTATDATAVtbl',
  'IStorage', 'IStorageVtbl',
  'IOfflineFilesDirectoryItem', 'IOfflineFilesDirectoryItemVtbl',
  'IOfflineFilesItem', 'IOfflineFilesItemVtbl',
  'IOfflineFilesTransparentCacheInfo',
  'IOfflineFilesTransparentCacheInfoVtbl',
  'tagDDDEVICEIDENTIFIER', 'tagDDDEVICEIDENTIFIER2', 'tagPALETTEENTRY',
  '_DDSURFACEDESC', '_DDSURFACEDESC2', '_DDBLTFX', '_DDBLTBATCH',
  '_DDOVERLAYFX', '_DDCAPS_DX7', '_RGNDATA',
  '_D3DADAPTER_IDENTIFIER9', '_D3DDISPLAYMODE', '_D3DCAPS9',
  '_D3DPRESENT_PARAMETERS_', '_D3DDEVICE_CREATION_PARAMETERS',
  '_D3DSURFACE_DESC', '_D3DLOCKED_RECT', '_D3DRASTER_STATUS',
  '_D3DGAMMARAMP', '_D3DVOLUME_DESC', '_D3DLOCKED_BOX', '_D3DBOX',
  '_D3DVERTEXBUFFER_DESC', '_D3DINDEXBUFFER_DESC', '_D3DRECT',
  '_D3DMATRIX', '_D3DVIEWPORT9', '_D3DMATERIAL9', '_D3DLIGHT9',
  '_D3DCLIPSTATUS9', '_D3DVERTEXELEMENT9', '_D3DRECTPATCH_INFO',
  '_D3DTRIPATCH_INFO',
  # DirectInput - определяем сами в dinput typedef
  'IDirectInputA', 'IDirectInputAVtbl', 'IDirectInputDeviceA',
  'IDirectInputDeviceAVtbl', 'DIDEVCAPS', 'DIDEVICEOBJECTINSTANCEA',
  'DIDEVICEOBJECTDATA', 'DIDEVICEINSTANCEA', 'DIDATAFORMAT',
  'DIPROPHEADER', 'DIPROPDWORD', 'DIPROPRANGE', 'DIMOUSESTATE',
  'DIMOUSESTATE2', 'DIOBJECTDATAFORMAT', 'DIACTIONA', 'DIACTIONFORMATA',
  '_DIDEVICEINSTANCEA', '_DIDEVCAPS', '_DIDEVICEOBJECTINSTANCEA',
  '_DIDEVICEOBJECTDATA', '_DIDATAFORMAT'
)

# enum MenuActions вставляется отдельно из IDA; unified-копия исключается
$enumDupBlockList = @('MenuActions')

$attrStrip = @(
  '\b__hex\b', '\b__udec\b', '\b__dec\b', '\b__tabform\([^)]*\)',
  '\b__off\b', '\b__strlit\([^)]*\)', '\b__unaligned\b'
)

$dinputTypedefLines = @(
  'typedef struct IDirectInputA IDirectInputA, *LPDIRECTINPUTA;',
  'typedef struct IDirectInputDeviceA IDirectInputDeviceA, *LPDIRECTINPUTDEVICEA;',
  'typedef HRESULT (__stdcall *LPDIENUMDEVICESCALLBACKA)(LPDIRECTINPUTDEVICEA, LPVOID);',
  'typedef HRESULT (__stdcall *LPDIENUMDEVICESCALLBACKW)(LPDIRECTINPUTDEVICEA, LPVOID);'
)

# ---------------------------------------------------------------- (1) чтение
if (-not (Test-Path -LiteralPath $UnifiedPath)) { throw "Unified not found: $UnifiedPath" }
if (-not (Test-Path -LiteralPath $IDAPath))     { throw "IDA not found: $IDAPath" }
$unified = Get-Content -LiteralPath $UnifiedPath
$ida     = Get-Content -LiteralPath $IDAPath
"unified: $($unified.Count) lines, ida: $($ida.Count) lines"

# ---------------------------------------------------------------- (2) индекс struct/enum-заголовков в IDA
# fast index: structName -> line number where 'struct __fixed Name {'
$idaStruct = @{}
$idaEnum   = @{}
for ($i = 0; $i -lt $ida.Count; $i++) {
  $l = $ida[$i]
  if ($l -match '^\s*struct (?:__fixed\s+|__unaligned\s+|__declspec\([^)]*\)\s+)*(?<name>[A-Za-z_][A-Za-z0-9_]*)\s*\{?\s*$' -and $Matches['name'] -notmatch '^__' -and -not $idaStruct.ContainsKey($Matches['name'])) {
    $idaStruct[$Matches['name']] = $i
  }
  if ($l -match '^\s*enum (?:__udec\s*|__dec\s*|__hex\s*)?(?<name>[A-Za-z_][A-Za-z0-9_]*)\s*(:.*)?$' -and $Matches['name'] -notmatch '^__' -and -not $idaEnum.ContainsKey($Matches['name'])) {
    $idaEnum[$Matches['name']] = $i
  }
}
"ida struct index: $($idaStruct.Count) зарегистрировано, enum: $($idaEnum.Count)"

# ---------------------------------------------------------------- (3) имена типов в unified
$typeNames = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
$enumNames = New-Object System.Collections.Generic.HashSet[string] ([System.StringComparer]::Ordinal)
$endIdx = if ($EndLine -lt 0) { $unified.Count } else { [Math]::Min($EndLine, $unified.Count) }
for ($idx = 0; $idx -lt $endIdx; $idx++) {
  $tt = $unified[$idx].TrimStart() -replace '\b__(?:udec|dec|bitmask)\b', ''
  if ($tt -match '^(?:struct|class|union)\s+([A-Za-z_][A-Za-z0-9_]*)' -and $Matches[1] -notmatch '^__') {
    [void]$typeNames.Add($Matches[1])
  }
  if ($tt -match '^enum\s+([A-Za-z_][A-Za-z0-9_]*)' -and $Matches[1] -notmatch '^__') {
    [void]$enumNames.Add($Matches[1]); [void]$typeNames.Add($Matches[1])
  }
}

# ---------------------------------------------------------------- (4) missing-блоки из IDA
$fixedNames = 'CameraOrPhysics','S162','S165','S200','Elements','AudioBuffer',`
  'AudioManager','S63_1','S202','MenuEntry','KeyState','Menu','Network','S86_8',`
  'HudBrief','S86_7','S86_2_1','HudArrow','S86_3','S86_4','S86_5','S86_10',`
  'Hud','HudBrief_S2','DMAudio','S15_0002','S15_001','S1501','S284','Map',`
  'Replay','S89_2','PoliceInfo','CarPhysics','CarPhysicsManager','Data16',`
  'S68_1','MapGm','SubSlots','ArenaSlots','PlayerData','Sound5','SoundCard',`
  'ArrowTrace','S291','S290','S280','Keybord','Random','ObjectPool','Taxi'

function Get-Body([string[]]$src, [int]$i0) {
  # i0 = индекс строки-заголовка ('struct Name' / 'enum Name'). Возвращает
  # только содержимое блока БЕЗ открывающей '{' и закрывающей '};' строк.
  $res = New-Object System.Collections.Generic.List[string]
  $depth = 0
  $i = $i0 + 1
  while ($i -lt $src.Count) {
    $t = $src[$i].Trim()
    if ($t -eq '{') {
      $i++; continue
    }
    if ($t -match '^\};?$') {
      if ($depth -le 0) { break }
      $depth--
      $i++; continue
    }
    if ($t.Contains('{') -and -not $t.EndsWith('{')) { $depth++ }
    $res.Add($src[$i])
    $i++
  }
  return $res.ToArray()
}

# enum MenuActions из IDA (до external enums и missing-полей)
$fixedEnums = 'Shop','KeyCode','KeyCode_1','ASCII_TABLE','Layout'
function Add-MissingEnum([string]$en) {
  if (-not $idaEnum.ContainsKey($en)) { Write-Host "WARN enum not found in IDA: $en"; return }
  $body = Get-Body $ida $idaEnum[$en]
  $lines = [System.Collections.Generic.List[string]]::new()
  foreach ($ln in $body) { $lines.Add(($ln -replace '\b__udec\b','' -replace '\b__dec\b','' -replace '\b__hex\b','').Trim()) }
  $t = $ida[$idaEnum[$en]].Trim() -replace '\b__udec\b','' -replace '\b__dec\b','' -replace '\b__hex\b',''
  $t = $t -replace '\s*\{?\s*$',''
  $linesOut = [System.Collections.Generic.List[string]]::new()
  $linesOut.Add("enum $en {")
  foreach ($ln in $lines) { $linesOut.Add($ln) }
  $linesOut.Add('};')
  $linesOut.Add('')
  return $linesOut.ToArray()
}
$menuActionsLines = [System.Collections.Generic.List[string]]::new()
for ($i = 5860; $i -lt 5880 -and $menuActionsLines.Count -eq 0; $i++) {
  if ($ida[$i] -match '^\s*enum\s+__udec\s+MenuActions\s*') {
    $body = Get-Body $ida $i
    foreach ($ln in $body) { $menuActionsLines.Add(($ln -replace '\b__udec\b','').Trim()) }
    [void]$typeNames.Add('MenuActions'); [void]$enumNames.Add('MenuActions')
  }
}

# ------------------------------------------------ external enums: VOCAL, DamageType и др.
$enumsPath = "C:\work\GTA2_RE\port\gta2_enums.h"
if (Test-Path -LiteralPath $enumsPath) {
  foreach ($el in (Get-Content -LiteralPath $enumsPath)) {
    if ($el -match '\benum\s+__int8\s+([A-Za-z_][A-Za-z0-9_]*)\b' -or $el -match '\benum\s+([A-Za-z_][A-Za-z0-9_]*)\s*$' -or $el -match '^\s*enum\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{' -or $el -match '\benum\s+([A-Za-z_][A-Za-z0-9_]*)\s*:\s*__int8\b') {
      $en = $Matches[1]
      if ($en -and $en -notmatch '^__') {
        [void]$enumNames.Add($en); [void]$typeNames.Add($en)
      }
    }
  }
}

$kwFieldName = @{
  'short'='short_'; 'bool'='bool_'; 'int'='int_'; 'enum'='enum_'; 'struct'='struct_';
  'union'='union_'; 'class'='class_'; 'char'='char_'; 'long'='long_'; 'float'='float_';
  'double'='double_'; 'void'='void_'; 'unsigned'='unsigned_'; 'signed'='signed_'
}

function Fix-TypeLine([string]$line) {
  $indent = [regex]::Match($line, '^\s*').Value
  $line = $line.TrimStart()
  $attrPrefix = $indent
  $tmp = $line
  while ($true) {
    if ($tmp -match '^__declspec\([^)]*\)\s*') {
      $attrPrefix += $Matches[0]; $tmp = $tmp.Substring($Matches[0].Length)
    }
    elseif ($tmp -match '^__unaligned\s+') {
      $attrPrefix += ' '; $tmp = $tmp -replace '^__unaligned\s+', ''
    }
    elseif ($tmp -match '^const\s+') {
      $attrPrefix += $Matches[0]; $tmp = $tmp.Substring($Matches[0].Length)
    }
    else { break }
  }
  if ($tmp -match '^(?<name>[A-Za-z_][A-Za-z0-9_]*)\s+(?<rest>[^;]*);\s*$') {
    $n = $Matches['name']
    $rest = $Matches['rest']
    # поле, имя которого == ключевое слово C++ (short/bool/int/...)
    if ($kwFieldName.ContainsKey($rest.Trim()) -and $rest -notmatch '\*') {
      return "$attrPrefix$n ${rest}_;"
    }
    $isSelf = $rest.TrimEnd() -cmatch ('^(\*\s*)?' + [regex]::Escape($n) + '\s*(\[[^;]*\])?\s*$')
    if ($typeNames.Contains($n) -and $n -notmatch '^__') {
      $kw = 'struct'
      if ($enumNames.Contains($n)) { $kw = 'enum' }
      if ($isSelf) {
if ($rest.Contains('*')) { return "$attrPrefix$kw $n *${n}_;"
      } else { return "$attrPrefix$kw $n ${n}_;"
      }
      }
      return "$attrPrefix$kw $n $rest;"
    }
    # самоссылка для не-тегов (FILE, GLuint...): просто переименуем поле
    if ($isSelf) {
      if ($rest.Contains('*')) { return "$attrPrefix$n *${n}_;"
      } else { return "$attrPrefix$n ${n}_;"
      }
    }
  }
  return $indent + $line
}

$missingBlocks = @{}
$missingOrder  = [System.Collections.Generic.List[string]]::new()
foreach ($fn in $fixedNames) {
  if ($fn -eq 'ArrowTrace') {
    $iA = -1
    for ($i = 7000; $i -lt 7200 -and $iA -lt 0; $i++) {
      if ($ida[$i] -match '^\s*struct __unaligned\s+__declspec\(align\(1\)\)\s+ArrowTrace\s*') { $iA = $i }
    }
    if ($iA -ge 0) {
      $missingBlocks[$fn] = (Get-Body $ida $iA); $missingOrder.Add($fn)
      [void]$typeNames.Add($fn)
    } else { Write-Host "WARN ArrowTrace not found" }
    continue
  }
  if ($idaStruct.ContainsKey($fn)) {
    $i0 = $idaStruct[$fn]
    $body = Get-Body $ida $i0
    $out = [System.Collections.Generic.List[string]]::new()
    foreach ($ln in $body) {
      $cl = $ln -replace '\b__unaligned\b','' -replace '\b__udec\b',''
      $cl = Fix-TypeLine $cl
      $out.Add($cl)
    }
    $missingBlocks[$fn] = $out.ToArray(); $missingOrder.Add($fn)
    [void]$typeNames.Add($fn)
  } else { Write-Host "WARN missing not found in IDA zone: $fn" }
}
"missing blocks извлечено: $($missingOrder.Count)"

# ---------------------------------------------------------------- (5) построчная чистка
$cleanLines = [System.Collections.Generic.List[string]]::new()
$inJunkBlock = $false
$inStructBlock = $false
$inBody = $false

$cnt = 0
foreach ($srcLine in $unified) {
  if ($cnt -ge $endIdx) { break }
  $cnt++
  $t = $srcLine.TrimStart()
  foreach ($pat in $attrStrip) { $t = $t -replace $pat, '' }

  if ($t -like 'struct __cppobj*') { $inJunkBlock = $true }
  if ($inJunkBlock) { if ($t -eq '};') { $inJunkBlock = $false }; continue }
  if ($inStructBlock) { if ($t -eq '};') { $inStructBlock = $false }; continue }

  # DirectInput junk в unified-зоне
  if ($t -match '^class\s+descriptor\s+displacement\s+container\s*($|\(#classinformer\))') { continue }
  if ($t -match '^struct\s+IDirect\w*\s+\*LPDIRECT\w+\s*;') { continue }
  if ($t -match '^typedef\s+struct\s+IDirect\w*\s+\*LPDIRECT\w+\s*;') { continue }

  if ($t -like 'struct*' -or $t -like 'class*' -or $t -like 'enum*') {
    if ($srcLine.Contains('<') -or $srcLine.Contains('>') -or $srcLine.Contains('::')) { continue }
    $tag = ''
    if ($t -match '^(?:struct|class|enum)\s+([A-Za-z_][A-Za-z0-9_]*)') { $tag = $Matches[1] }
    if ($enumDupBlockList -contains $tag) { $inStructBlock = $true; continue }
    if ($structBlockList -contains $tag) { $inStructBlock = $true; continue }
    $isJunk = $false
    foreach ($tok in $junkTokens) {
      if ($srcLine.IndexOf($tok, [System.StringComparison]::OrdinalIgnoreCase) -ge 0) { $isJunk = $true; break }
    }
    if ($isJunk) { continue }
    $inBody = $t -match '\{$'
  }
  if ($t -eq '{') { $inBody = $true }
  elseif ($t -eq '};') { $inBody = $false }

  if ($inBody) { $t = Fix-TypeLine $t }
  [void]$cleanLines.Add($t)
}
"clean zone lines: $($cleanLines.Count)"

# ---------------------------------------------------------------- (6) префикс (enum/typedef)
# missing struct-блоки НЕ печатаем здесь - они попадут в топосорт как участники $blocks.
$missingText = [System.Collections.Generic.List[string]]::new()
if ($menuActionsLines.Count -gt 0) {
  $missingText.Add('enum MenuActions : __int8 {')
  foreach ($ml in $menuActionsLines) { $missingText.Add($ml) }
  $missingText.Add('};')
  $missingText.Add('')
}
foreach ($fe in $fixedEnums) {
  $enLines = Add-MissingEnum $fe
  if ($enLines -and $enLines.Count -gt 0) {
    foreach ($el in $enLines) { $missingText.Add($el) }
    [void]$enumNames.Add($fe); [void]$typeNames.Add($fe)
  }
}
foreach ($dl in $dinputTypedefLines) { $missingText.Add($dl) }
$missingText.Add('')

# ---------------------------------------------------------------- (7) блоки + топосорт
$allLines = [System.Collections.Generic.List[string]]::new()
$allLines.Add('// gta2_clean.h - игровая зона unified + missing-типы из IDA')
$allLines.Add('// Авто-генерируется merge_header.ps1 (топологический порядок).')
$allLines.Add('')
# missing struct-блоки: заголовок 'struct Name {' + тело
foreach ($mn in $missingOrder) {
  $allLines.Add("struct $mn {")
  foreach ($ln in $missingBlocks[$mn]) { $allLines.Add($ln) }
  $allLines.Add('};')
  $allLines.Add('')
}
foreach ($cl in $cleanLines)  { $allLines.Add($cl) }

$blocks = [System.Collections.Generic.List[object]]::new()
$blockMap = @{}
$texts   = [System.Collections.Generic.List[string]]::new()
$i = 0; $n = $allLines.Count
while ($i -lt $n) {
  $l0 = $allLines[$i].Trim()
  if ($l0 -match '^(struct|class|union)\s+([A-Za-z_][A-Za-z0-9_]*)\s*\{?\s*$' -and $allLines[$i] -notmatch ';') {
    $bname = $Matches[2]
    $bLines = [System.Collections.Generic.List[string]]::new()
    $depth = 0; $j = $i
    while ($j -lt $n) {
      $tl = $allLines[$j].Trim()
      $bLines.Add($allLines[$j])
      if ($tl.Contains('{')) { $depth++ }
      if ($tl -match '^\};?') { $depth--; if ($depth -le 0) { break } }
      $j++
    }
    $dedup = [System.Collections.Generic.Dictionary[string,int]]::new([System.StringComparer]::Ordinal)
    for ($bIx = 0; $bIx -lt $bLines.Count; $bIx++) {
      $bl = $bLines[$bIx]
      $fld = [regex]::Match($bl, '([A-Za-z_][A-Za-z0-9_]*)\s*(\[[^;]*\])?\s*;\s*$')
      if (-not $fld.Success) { continue }
      $fname = $fld.Groups[1].Value
      if ($dedup.ContainsKey($fname)) {
        $newName = $fname + '_' + (++$dedup[$fname])
        $bLines[$bIx] = $bl -replace ([regex]::Escape($fname) + '(?=\s*(\[[^;]*\])?\s*;\s*$)'), $newName
        $dedup[$newName] = 0
      } else {
        $dedup[$fname] = 1
      }
    }
    $deps = [System.Collections.Generic.HashSet[string]]::new([System.StringComparer]::Ordinal)
    foreach ($bl in $bLines) {
      $bt = $bl.Trim()
      if ($bt -match '^\s*#') { continue }
      # "Type name;" | "Type name[NN];" с опциональным struct/enum/union префиксом, без '*'
      if ($bt -match '^(?:(?:struct|class|enum|union)\s+)?(?<t>[A-Za-z_][A-Za-z0-9_]*)\s+[A-Za-z_][A-Za-z0-9_]*(\[[^;]*\])?\s*;$' -and
          $bt -notmatch '\*' -and $bt -notmatch '^(?:unsigned|signed|__int|bool|char|short|long|float|double|int|byte|wchar_t|_BYTE|_WORD|_DWORD|_QWORD)\s') {
        $tn = $Matches['t']
        if ($tn -ne $bname) { [void]$deps.Add($tn) }
      }
    }
    $blk = [pscustomobject]@{ Name=$bname; Lines=$bLines.ToArray(); Deps=$deps; Ord=$blocks.Count }
    $blocks.Add($blk); $blockMap[$bname] = $blk
    $i = $j + 1
    continue
  }
  $texts.Add($allLines[$i]); $i++
}
"structs parsed: $($blocks.Count), text lines: $($texts.Count)"

# топосорт
$outBlocks = [System.Collections.Generic.List[object]]::new()
$state = @{}
function AddDep([object]$blk, [hashtable]$map, [hashtable]$st, [System.Collections.Generic.List[object]]$out) {
  $nm = $blk.Name
  if ($st[$nm] -eq 2) { return }
  if ($st[$nm] -eq 1) { Write-Host "CYCLE at $nm (skipped edge)"; return }
  $st[$nm] = 1
  foreach ($d in $blk.Deps) {
    if ($map.ContainsKey($d)) { AddDep $map[$d] $map $st $out }
  }
  $st[$nm] = 2
  $out.Add($blk)
}
foreach ($blk in $blocks) { AddDep $blk $blockMap $state $outBlocks }
"toposort order OK, blocks out: $($outBlocks.Count) (cycles skipped)"

# ---------------------------------------------------------------- (8) сборка
$sb = [System.Text.StringBuilder]::new()
foreach ($ln in ($allLines | Select-Object -First 3)) { [void]$sb.AppendLine($ln) }

# forward declarations: выводим тексты до первого struct отдельно, потом block set
$fwd = [System.Collections.Generic.List[string]]::new()
$afterFwd = [System.Collections.Generic.List[string]]::new()
$seenStruct = $false
foreach ($tx in $texts) {
  if ($seenStruct) { $afterFwd.Add($tx) }
  elseif ($tx -match '^struct\s+\w+\s*;' -or $tx.Trim() -eq '' -or $tx -match '^//' -or $tx -match '^/\*') { $fwd.Add($tx) }
  else { $seenStruct = $true; $afterFwd.Add($tx) }
}

# header: enum/typedef/dinput вставки идут ДО блоков
foreach ($ln in $missingText) { [void]$sb.AppendLine($ln) }
foreach ($blk in $outBlocks) {
  foreach ($ln in $blk.Lines) { [void]$sb.AppendLine($ln) }
  [void]$sb.AppendLine('')
}
foreach ($ln in $afterFwd) { [void]$sb.AppendLine($ln) }

Set-Content -LiteralPath $OutPath -Value $sb.ToString() -Encoding utf8
$lc = ($sb.ToString() -split "`n").Count
"output: $OutPath ($lc строк, structs=$($outBlocks.Count))"