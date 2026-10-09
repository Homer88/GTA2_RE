# convert_module.ps1 - конвертация декомпилированных тел модуля в компилируемые
# свободные функции с плоским неймспейсом gta2:: (без C++ классов).
#   Class::name(...)   ->  gta2::Class_name(...)  (self-параметр переименовывается)
#   __thiscall         ->  убирается (по умолчанию)
#   this               ->  self  (только в теле/параметрах)
# Перед каждой функцией добавляется #include "gta2_shim.h" (один раз).
# Результат: $Out/<module>/*.cpp

param(
  [string]$Module,
  [string]$InRoot = "dump\unified",
  [string]$OutRoot = "port\out",
  [string]$RenamesFile = "build_manual\unified\call_renames.tsv"
)

# таблица переименований вызовов: Cls_OldName(MEMBER без класса) -> Cls_NewName
# (вызовы в телах используют Ghidra/IDA-имена, а определения — канонические)
$callRename = @{}
if (Test-Path $RenamesFile) {
  foreach ($line in Get-Content $RenamesFile) {
    $p = $line -split "`t"
    if ($p.Count -eq 2 -and $p[0] -and $p[1]) { $callRename[$p[0]] = $p[1] }
  }
}

$srcDir = Join-Path $InRoot $Module
$dstDir = Join-Path $OutRoot $Module
if (-not (Test-Path $srcDir)) { Write-Error "нет модуля: $srcDir"; exit 1 }
New-Item -ItemType Directory -Path $dstDir -Force | Out-Null

# self-поля из clean.h: член "<type> T_;" (Fix-TypeLine переименовал "T *T;" > "T *T_;")
# Исключения: члены, которые НЕ переименовывались (напр. "void *Car;" в классе Car).
$noSelfField = @('Car')
$selfFields = @()
if (Test-Path 'port\gta2_clean.h') {
  $cleanTxt = Get-Content -LiteralPath 'port\gta2_clean.h' -Raw
  foreach ($m in [regex]::Matches($cleanTxt, '(?m)^\s*(?:struct\s+)?(?<t>[A-Za-z_]\w*)\s+(\**)\s*\k<t>_(\s*;|\s*\[)')) {
    if ($noSelfField -notcontains $m.Groups['t'].Value -and $selfFields -notcontains $m.Groups['t'].Value) { $selfFields += $m.Groups['t'].Value }
  }
}
# self-поля-скаляры (не массивы): декомпилятор пишет "->T[0]", а член скалярный -
# снимаем "[0]".
$scalarFieldDrop0 = @('S104_','BaseCar_')

# параметры-сам для неполных типов: в определениях пишем "struct X *self" как в прото.
# Параметр "X *self" в qualified-определении ("RET gta2::Cls_meth(X *self, ...)")
# обязан совпадать с прототипом ("struct X *self"): MSVC ищет X внутри namespace
# gta2, где одноимённая глобальная структура не видна -> C2061/C2664.
# Квалифицируются только реальные структуры из gta2_clean.h; typedef/enum/forward-only
# типы (SearchType, GlassInfo) через "struct" недопустимы и ломают компиляцию.
$elabParams = @()
if (Test-Path 'port\gta2_clean.h') {
  $cleanAll = Get-Content -LiteralPath 'port\gta2_clean.h' -Raw
  $defined = New-Object 'System.Collections.Generic.HashSet[string]'
  foreach ($m in [regex]::Matches($cleanAll, '(?ms)^struct\s+(?<n>[A-Za-z_]\w*)\s*\{')) {
    [void]$defined.Add($m.Groups['n'].Value)
  }
  foreach ($m in [regex]::Matches($cleanAll, '(?m)^struct\s+(?<n>[A-Za-z_]\w*)\s*\*\s*\k<n>_\s*;')) {
    [void]$defined.Add($m.Groups['n'].Value)
  }
  foreach ($n in $defined) { if ($elabParams -notcontains $n) { $elabParams += $n } }
}
# forward-only структуры (тела нет в clean.h, объявлены как "struct X;" в shim) -
# тоже квалифицируем: Police, MissionManager, Movie, Keybord, GlassInfo и т.п.
# Берём ТОЛЬКО явные "struct X;" из shim: там гарантированно структуры, в отличие
# от gta2_protos.h, где "struct Y *" встречается у typedef/enum (SearchType).
if (Test-Path 'port\gta2_shim.h') {
  $shimAll = Get-Content -LiteralPath 'port\gta2_shim.h' -Raw
  $fwdBlock = [regex]::Match($shimAll, '(?s)//\s*forward-объявления.*?(?=#include|\r?\n\s*//\s*---\s*системные)')
  $fwdSrc = if ($fwdBlock.Success) { $fwdBlock.Value } else { $shimAll }
  foreach ($m in [regex]::Matches($fwdSrc, '(?m)^\s*struct\s+(?<n>[A-Za-z_]\w*)\s*;')) {
    if ($elabParams -notcontains $m.Groups['n'].Value) { $elabParams += $m.Groups['n'].Value }
  }
  # Типы, уже видимые в gta2 через "using ::X;" в shim, квалифицировать НЕЛЬЗЯ:
  # "struct X *self" конфликтует с using-декларацией -> C7624 ("definition of X
  # hides existing declaration"). Их резолвинг уже работает.
  foreach ($m in [regex]::Matches($shimAll, 'using\s+::(?<n>[A-Za-z_]\w*)\s*;')) {
    $n = $m.Groups['n'].Value
    $elabParams = $elabParams | Where-Object { $_ -ne $n }
  }
}
# известные переименования имён членов: Ghidra-имя -> unified-имя
# (каждый парой явных regex: массив @(,@(a,b)) шлетов схлопывает вложенность)

# имена функций в прото (для квалификации голых вызовов "name(" -> "gta2::name(")
$protoNames = @()
if (Test-Path 'port\gta2_protos.h') {
  foreach ($ln in Get-Content -LiteralPath 'port\gta2_protos.h') {
    $mm = [regex]::Match($ln, '([A-Za-z_]\w*)\s*\(')
    if ($mm.Success) {
      $nm = $mm.Groups[1].Value
      if ($protoNames -notcontains $nm) { $protoNames += $nm }
    }
  }
}

# сигнатура: RET __cc [Class::]name( params )
$sigRe = '(?m)^(?<ret>[A-Za-z_][\w \*<>,\[\]&()]*?)__(?:thiscall|cdecl|stdcall|fastcall|vectorcall)\s+(?:(?<cls>[A-Za-z_]\w*)::)?(?<name>\w+)\s*\((?<params>(?:[^()]|\([^()]*\))*)\)'

function Convert-Text([string]$txt) {
  # 1) сигнатуры определений
  $txt = [regex]::Replace($txt, $sigRe, {
    param($m)
    $ret = $m.Groups['ret'].Value.Trim()
    if (-not $ret) { return $m.Value }
    $cls = $m.Groups['cls'].Value
    $name = $m.Groups['name'].Value
    $params = $m.Groups['params'].Value
    # this -> self в параметрах
    $params = [regex]::Replace($params, '(?<cls2>[A-Za-z_]\w*)\s*\*\s*this\b', '$1 *self')
    $params = [regex]::Replace($params, '\bthis\b', 'self')
    # параметр "X *self" для неполных (forward-only) типов должен совпадать
    # с объявлением прото ("struct Police *self"); иначе MSVC видит другой тип
    foreach ($et in $elabParams) {
      $params = [regex]::Replace($params, '(?<![A-Za-z0-9_])(?<!struct )(?<!\bstruct )' + $et + '(\s*\*\s*)self\b', 'struct ' + $et + '$1self')
    }
    $q = if ($cls) { "$cls" + "_" } else { "" }
    return "$ret gta2::$q$name($params)"
  })

  # 2) this -> self в теле
  $txt = [regex]::Replace($txt, '\bthis\b', 'self')

  # 3) квалифицированные вызовы: Class::f( -> gta2::Class_f(
  #    без повторной конвертации уже готовых gta2::X_( и без gta2:: в сигнатурах;
  #    если имя вызова есть в таблице переименований — подставляем каноническое
  $txt = [regex]::Replace($txt, '(?<!:)([A-Za-z_][\w]*?)::([A-Za-z_]\w*)\s*\(', {
    param($m)
    if ($m.Groups[1].Value -eq 'gta2') { return $m.Value }
    $agg = $m.Groups[1].Value + '_' + $m.Groups[2].Value
    if ($callRename.ContainsKey($agg)) { return 'gta2::' + $callRename[$agg] + '(' }
    return 'gta2::' + $agg + '('
  })

  # 4) self-поля: Fix-TypeLine переименовал члены вида "T *T;" в "T *T_;",
  #    а тела обращаются "->T". Переписываем "->T" -> "->T_" для таких членов.
  foreach ($sf in $selfFields) {
    $txt = [regex]::Replace($txt, '->' + $sf + '(?![A-Za-z0-9_])', '->' + $sf + '_')
  }
  # для скалярных self-полей снимаем индекс "[0]" (Ghidra всегда пишет первый элемент)
  foreach ($sc in $scalarFieldDrop0) {
    $txt = [regex]::Replace($txt, '->' + $sc + '\s*\[0\]', '->' + $sc)
  }

  # 5) известные переименования имён членов (Ghidra-имя -> unified-имя)
  #    стрелочная форма "->CarCurrent", и точечная "S104_.Weapon" (структура-член)
  $txt = $txt -creplace '->CarCurrent(?![A-Za-z0-9_])', '->CurrentCar'
  $txt = $txt -creplace '(->|\.)Weapon(?![A-Za-z0-9_])', '$1Weapon_'

  # 6) голые вызовы функций из прото: name( -> gta2::name(
  foreach ($pn in $protoNames) {
    $txt = [regex]::Replace($txt, '(?<![A-Za-z0-9_:])' + [regex]::Escape($pn) + '(?=\s*\()', 'gta2::' + $pn)
  }

  # 7) синтез-члены Ghidra "gBufferSize._NNNN_4_": offset/4-индекс в массиве int
  $txt = [regex]::Replace($txt, '\bgBufferSize\.(_[0-9A-Fa-f]+_[0-9]+_)\b', {
    param($m)
    $chunks = $m.Groups[1].Value -split '_'
    $off = [Convert]::ToInt32('0x' + $chunks[1], 16)
    $elem = [int]$chunks[2]
    if ($elem -eq 0) { return 'gBufferSize[0x0]' }
    return "gBufferSize[0x$([Convert]::ToString($off / $elem, 16))]"
  })

  # 8) точечные исправления сигнатур вызовов:
  #    Car::sub_403800 в IDA-форме передаёт "(int)&X" (это адрес); параметр — указатель
  $txt = [regex]::Replace($txt, '(Car_sub_403800\(\(Car \*\)&[A-Za-z0-9_]+, )\(int\)&', '$1&')

  # 9) семантические правки: _free = MSVC free; gCameraOrPhysics_0 = копия глобала;
  #    Callback-указатели (GUID в параметрах ломает синтаксис MSVC); лишние аргументы
  #    декомпилятора; S169-вызовы из Medical (типы-предки); strcpy 3-арг = sprintf
  $txt = $txt -creplace '\b_free\(', 'free('
  $txt = $txt -creplace '\bgCameraOrPhysics_0\b', 'gCameraOrPhysics'
  $txt = $txt -creplace 'HRESULT \(__stdcall \*DirectDrawCreate\)\(GUID \*, LPDIRECTDRAW \*, IUnknown \*\)', 'int (__stdcall *DirectDrawCreate)(void *, LPDIRECTDRAW *, struct IUnknown *)'
  $txt = $txt -creplace '\(HRESULT \(__stdcall \*\)\(GUID \*, LPDIRECTDRAW \*, IUnknown \*\)\)GetProcAddress', '(int (__stdcall *)(void *, LPDIRECTDRAW *, struct IUnknown *))GetProcAddress'
  $txt = $txt -creplace '\bgta2::sub_4023E0\(([A-Za-z0-9_]+), \(int\)[A-Za-z0-9_]*\)', 'gta2::sub_4023E0($1)'
  $txt = $txt -creplace '\bgta2::Car_IsTrainOrTrainCarriage\(\(Car \*\)\(local_30 \+ 4\),\(Car \*\)&DAT_005d2e44\)', 'gta2::Car_IsTrainOrTrainCarriage((Car *)(local_30 + 4))'
  $txt = $txt -creplace '\bstrcpy\(([^,]+), "%c:", ([^)]+)\)', 'sprintf($1, "%c:", $2)'
  $txt = $txt -creplace 'gta2::S169_GetInUse\(pS169\)', 'gta2::S169_GetInUse((struct S169 *)pS169)'
  $txt = $txt -creplace 'gta2::S169_S169\(pAutoClass4\)', 'gta2::S169_S169((struct S169 *)pAutoClass4)'
  $txt = $txt -creplace 'gta2::S169_SetInUse\(pAutoClass4\)', 'gta2::S169_SetInUse((struct S169 *)pAutoClass4)'
  $txt = $txt -creplace 'gta2::S202_SetToNewVal\(s110,\(Matrix3D \*\)\(\*param_2 \* \*self\)\)', 'gta2::S202_SetToNewVal((S202 *)s110,(SpriteS1 *)(*param_2 * *(_DWORD *)self))'
  # subtypes/частично-раскастованные вызовы (типы-предки, сырые слоты, выход int*):
  $txt = $txt -creplace 'gta2::sub_402660(v23, self)', 'gta2::sub_402660(v23, (_DWORD *)self)'
  $txt = $txt -creplace '\bError\(([A-Za-z0-9_]+)\)', 'gta2::ErrorLine($1)'
  $txt = $txt -creplace 'gta2::Player_sub_401B40\(\s*(?:struct\s+)?SpawnPoint\s*\*\)', 'gta2::Player_sub_401B40((Player *)'
  $txt = $txt -creplace 'gta2::Ped_GetYCoordinate\(([A-Za-z0-9_]+),\s*\(int\)&([A-Za-z0-9_]+)\)', 'gta2::Ped_GetYCoordinate($1, &$2)'
  $txt = $txt -creplace 'gta2::Ped_GetYCoordinate\(([A-Za-z0-9_]+),\s*\(int\)([A-Za-z0-9_]+)\)', 'gta2::Ped_GetYCoordinate($1, (int *)$2)'
  $txt = $txt -creplace 'gta2::S169_sub_404900\(([A-Za-z0-9_]+),', 'gta2::S169_sub_404900((SpawnPoint *)$1,'
  $txt = $txt -creplace 'gta2::S169_sub_4049F0\(([A-Za-z0-9_]+)\)', 'gta2::S169_sub_4049F0((SpawnPoint *)$1)'
  $txt = $txt -creplace 'gta2::CarSystemManager_sub_401C40\(\s*([A-Za-z0-9_]+)\s*,\s*([A-Za-z0-9_]+)\)', 'gta2::CarSystemManager_sub_401C40($1, (Game *)$2)'
  $txt = $txt -creplace 'gta2::Ped_SetCurrentCar\(([^,\n]+), \(([^)\n]*)\)->field_10B\)', 'gta2::Ped_SetCurrentCar($1, (Car *)(($2)->field_10B))'
  $txt = $txt -creplace 'gta2::S169_S169\(\s*\(AIController \*\)\s*([A-Za-z0-9_]+)\s*\)', 'gta2::S169_S169((struct S169 *)$1)'
  # MSVC: NAN - макрос (0.0f/0.0f), "NAN(x)" не компилируется. Ghidra-вид "a != NAN(a)"
  # = проверка "не NaN" -> "a != (a != a)". Аргумент может быть "x" или "x[3]".
  $txt = $txt -creplace '\bNAN\(([A-Za-z0-9_]+(?:\[[0-9A-Fa-fx]+\])*)\)', '($1 != $1)'

  return $txt
}

foreach ($file in Get-ChildItem -LiteralPath $srcDir -Filter *.cpp) {
  $txt = Get-Content -LiteralPath $file.FullName -Raw
  $conv = Convert-Text $txt
  # защита от "shadow-локальных": если локальная переменная названа как тип
  # ("Ped *Ped;"), голое "Ped" в последующих объявлениях ("Ped *v4;") становится
  # переменной. Квалифицируем все объявления такого типа через "struct X *".
  $shadowTags = @{}
  foreach ($m in [regex]::Matches($conv, '(?m)^\s*(?:struct\s+)?([A-Za-z_]\w*)\s+(\*+)\s*\1\s*(?:;|\[)')) {
    $shadowTags[$m.Groups[1].Value] = $true
  }
  foreach ($t in $shadowTags.Keys) {
    $conv = [regex]::Replace($conv, '(?m)^(\s*)(?:struct\s+)?' + [regex]::Escape($t) + '(\s+)(\*+)(\s*[A-Za-z_]\w*\s*;)', '$1struct ' + $t + '$2$3$4')
  }

  $hdr = '#include "gta2_shim.h"' + [Environment]::NewLine + [Environment]::NewLine
  $dst = Join-Path $dstDir $file.Name
  Set-Content -LiteralPath $dst -Value ($hdr + $conv) -Encoding ascii
}

"converted: $Module ($((Get-ChildItem $dstDir -Filter *.cpp).Count) files) -> $dstDir"