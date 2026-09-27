#!/usr/bin/env python
"""Regenerate translations/editsave_*.ts from the tr() strings in src/.

Hand-maintained .ts files drift from the source within one commit, so the
mapping is generated and the source strings are the single source of truth.
Re-run after changing any user-visible string:

    python tools/tools/make_translations.py
"""
from __future__ import annotations

import html
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]   # .../tools/EditSave
SRC = ROOT / "src"
OUT = ROOT / "translations"

# Context -> Russian translation. Contexts are the enclosing class name, which
# is what Qt uses for tr() and what lupdate records.
RU = {
    "FieldDefs": {
        "Pistol": "Пистолет",
        "Uzi SMG": "Пистолет-пулемёт (Узи)",
        "Rocket launcher": "Гранатомёт",
        "Electro Gun": "Электропушка",
        "Molotov cocktail": "Коктейль Молотова",
        "Grenade": "Граната",
        "Shotgun": "Дробовик",
        "Shocker": "Электрошокер",
        "Flamethrower": "Огнемёт",
        "Grenade launcher": "Подствольный гранатомёт",
        "Dual pistols": "Два пистолета",
        "Machine gun": "Пулемёт",
        "Unknown weapon 12": "Оружие 12 (не опознано)",
        "Unknown weapon 13": "Оружие 13 (не опознано)",
        "Unknown weapon 14": "Оружие 14 (не опознано)",
        "Point multiplier": "Множитель очков",
        "Extra life": "Дополнительная жизнь",
        "Health": "Здоровье",
        "Armor": "Броня",
        "Get out of jail card": "Карточка «выход из тюрьмы»",
        "COP bribe": "Взятка полиции",
        "Invulnerability": "Неуязвимость",
        "Double damage": "Двойной урон",
        "Fast reload": "Быстрая перезарядка",
        "Electro fingers": "Электропальцы",
        "Respect": "Уважение",
        "Invisibility": "Невидимость",
        "Instant gang": "Мгновенная банда",
        "Unknown powerup 13": "Неизвестный бонус 13",
        "Unknown powerup 14": "Неизвестный бонус 14",
        "Unknown powerup 15": "Неизвестный бонус 15",
        "Unknown powerup 16": "Неизвестный бонус 16",
        "point multiplier timer": "таймер множителя очков",
        "extra life timer": "таймер дополнительной жизни",
        "health pickup timer": "таймер подбора здоровья",
        "armour pickup timer": "таймер подбора брони",
        "get outta jail free card": "карточка «выход из тюрьмы»",
        "cop bribe": "взятка полиции",
        "invulnerability": "неуязвимость",
        "double damage": "двойной урон",
        "fast reload": "быстрая перезарядка",
        "electro fingers": "электропальцы",
        "respect / gang points": "уважение / очки банды",
        "invisibility": "невидимость",
        "instant gang access": "мгновенный доступ к банде",
        "not identified": "не определено",
        "Unknown": "Неизвестно",
        "no such slot": "нет такого слота",
        "Identity / level": "Личность / уровень",
        "Progress": "Прогресс",
        "Bonuses": "Бонусы",
        "Gang respect": "Уважение банд",
        "Weapons": "Оружие",
        "Unidentified (copied verbatim)": "Не определено (копируется как есть)",
        "Map-derived / unsafe": "Из карты / небезопасно",
    },
    "Cities": {
        "Liberty City": "Либерти-сити",
        "Industrial City": "Промышленный город",
        "Bilboa City": "Бильбао",
    },
    "DatTable": {
        "Apply to .dat": "Применить к .dat",
        "Discard edits": "Сбросить правки",
        "Unlock all 12": "Открыть все 12",
        "Lock all": "Закрыть все",
        "Player name:": "Имя игрока:",
        "arena": "город",
        "sub": "участок",
        "rec": "запись",
        "flag": "флаг",
        "best (money)": "лучший (деньги)",
        "last (money)": "последний (деньги)",
    },
    "FieldEditor": {
        "Pin this field: ignore edits instead of applying them":
            "Закрепить поле: игнорировать правки вместо применения",
        "Unsafe: tick to allow editing anyway":
            "Небезопасно: отметьте, чтобы разрешить правку",
    },
    "SaveFile": {
        "Arena %1 is out of range (0-2).": "Город %1 вне диапазона (0-2).",
    },
    # Free functions in SaveFile.cpp / FieldEditor.cpp use QObject::tr, which
    # Qt records under the QObject context rather than the file's class.
    "QObject": {
        "Arena %1 is out of range (0-2).": "Город %1 вне диапазона (0-2).",
    },
    "HexView": {
        "#": "#",
        ".dat records": "Записи .dat",
        "Refresh": "Обновить",
        "Region:": "Область:",
        "block0 (1864 B)": "block0 (1864 Б)",
        "block0 of %1": "block0 файла %1",
        "whole .svg": "весь .svg",
        "full .svg image (%1 B)": "полный образ .svg (%1 Б)",
        "id": "id",
        "extra": "extra",
        "offset": "смещение",
        "no .svg loaded": ".svg не загружен",
        "no .dat loaded": ".dat не загружен",
        "count field @0x12A = %1    non-empty rows = %2    of 300 slots":
            "поле счётчика @0x12A = %1    непустых строк = %2    из 300 слотов",
        "player = '%1'    header = 18 B    12 records x 9 B":
            "игрок = '%1'    заголовок = 18 Б    12 записей x 9 Б",
    },
    "main": {
        "Switch language": "Смена языка",
        "Language set to %1. The window will be rebuilt.\n\n"
        "Unsaved edits in the current window are lost.":
            "Язык переключён на %1. Окно будет пересоздано.\n\n"
            "Несохранённые правки в текущем окне будут потеряны.",
    },
    "MainWindow": {
        "GTA2 Save Editor": "Редактор сохранений GTA2",
        "Save dir:": "Папка сохранений:",
        "Slot:": "Слот:",
        "City:": "Город:",
        "New save...": "Новое сохранение...",
        "Build a fresh .svg + .dat pair in the current slot":
            "Создать новую пару .svg + .dat в текущем слоте",
        "Template:": "Шаблон:",
        "Reload from disk": "Перечитать с диска",
        "Apply edits": "Применить правки",
        "Write to disk": "Записать на диск",
        "Backup now": "Создать копию",
        "Fields": "Поля",
        "Weapons": "Оружие",
        ".dat records": "Записи .dat",
        "Map fingerprint": "Отпечаток карты",
        "Hex": "Hex",
        "Settings": "Настройки",
        "ready": "готово",
        "plyslot%1": "слот%1",
        "...": "...",
        "%1. %2": "%1. %2",
        "Liberty City": "Либерти-сити",
        "Industrial City": "Промышленный город",
        "Bilboa City": "Бильбао",
        "no .svg": ".svg не загружен",
        "no .dat": ".dat не загружен",
        "map=%1  city=%2  money=%3": "карта=%1  город=%2  деньги=%3",
        ".dat '%1' loaded": ".dat '%1' загружен",
        "** unsaved edits **": "** несохранённые правки **",
        "   |   ": "   |   ",
        "Select the player save folder": "Выберите папку сохранений",
        "Slot %1": "Слот %1",
        "Neither file could be read.\n\n%1\n\n"
        "Check the save directory above.":
            "Не удалось прочитать ни один файл.\n\n%1\n\n"
            "Проверьте указанную выше папку сохранений.",
        "Discard edits?": "Сбросить правки?",
        "There are unsaved edits. Switch folder and lose them?":
            "Есть несохранённые правки. Сменить папку и потерять их?",
        "field values applied to the in-memory save - "
        "press \"Write to disk\" to persist":
            "значения полей применены к сохранению в памяти — "
            "нажмите «Записать на диск», чтобы сохранить",
        "There are unsaved edits. Reload from disk and lose them?":
            "Есть несохранённые правки. Перечитать с диска и потерять их?",
        "applied to the in-memory save": "применено к сохранению в памяти",
        "Backup failed": "Ошибка резервной копии",
        "Cannot create %1": "Не удалось создать %1",
        "backed up %1 file(s) to %2": "скопировано файлов: %1 в %2",
        "Write failed": "Ошибка записи",
        "Could not write the save. See the status bar for details.":
            "Не удалось записать сохранение. Подробности в строке состояния.",
        "written: %1": "записано: %1",
        "Quit?": "Выход?",
        "There are unsaved edits. Quit anyway?":
            "Есть несохранённые правки. Всё равно выйти?",
        "No .svg is loaded.": ".svg не загружен.",
        "Arena %1 is out of range.": "Город %1 вне диапазона.",
        "Load a save before switching city":
            "Загрузите сохранение перед сменой города",
        "There are unsaved edits. Switch city and lose them?":
            "Есть несохранённые правки. Сменить город и потерять их?",
        "City switch failed": "Не удалось сменить город",
        "Switched to %1: names rewritten and %2 mission rows rebuilt from %3. "
        "Press \"Write to disk\" to save.":
            "Переключено на %1: имена перезаписаны, %2 строк миссий собрано из %3. "
        "Нажмите «Записать на диск» для сохранения.",
        "New save": "Новое сохранение",
        "The three trailing map-constant blocks are copied from an existing save. "
        "Pick any save from the selected city; block0 is built from scratch.":
            "Три хвостовых блока констант карты копируются из существующего "
        "сохранения. Выберите любое сохранение выбранного города; block0 "
        "строится с нуля.",
        "Will write %1/plyslot%2.svg and .dat for %3.":
            "Будет записано %1/plyslot%2.svg и .dat для %3.",
        "GTA2 saves (*.svg)": "Сохранения GTA2 (*.svg)",
        "Pick a template save": "Выберите сохранение-шаблон",
        "Create": "Создать",
        "Overwrite slot %1?": "Перезаписать слот %1?",
        "Slot %1 already contains a save. A timestamped backup is made first, "
        "then the slot is replaced. Continue?":
            "Слот %1 уже содержит сохранение. Сначала будет создана резервная "
        "копия с меткой времени, затем слот заменяется. Продолжить?",
        "New save failed": "Не удалось создать сохранение",
        "Unknown city.": "Неизвестный город.",
        "Created %1: %2, %3 mission rows, fresh .dat with no locations unlocked.":
            "Создано %1: %2, %3 строк миссий, новый .dat без открытых локаций.",
    },
    "WeaponTable": {
        "Ammo counters and powerup timers live in the .svg. A timer of 0 means the "
        "effect is not running; a non-zero value counts down while it lasts. Values "
        "written here are passed to the game as-is.":
            "Счётчики патронов и таймеры бонусов хранятся в .svg. Таймер 0 означает, "
            "что эффект не действует; ненулевое значение отсчитывается, пока он "
            "активен. Записанные значения передаются в игру как есть.",
        "Weapons": "Оружие",
        "Powerups": "Бонусы",
        "Slot": "Слот",
        "Name": "Название",
        "Ammo": "Патроны",
        "Timer": "Таймер",
        "Equipped:": "В руках:",
        "none": "нет",
        "weapon remap (0x%1)": "переназначение оружия (0x%1)",
        "game-side remap flag; leave as the game wrote it":
            "флаг переназначения на стороне игры; оставьте как записала игра",
        "All powerups = 0": "Все бонусы = 0",
        "Clears every powerup timer": "Обнуляет все таймеры бонусов",
        "Refill all ammo": "Пополнить все патроны",
        "Sets every ammo counter to 255": "Ставит 255 во все счётчики патронов",
        "%1 - %2": "%1 — %2",
    },
    "SettingsPage": {
        "Interface": "Интерфейс",
        "Scale:": "Масштаб:",
        "Language:": "Язык:",
        "Takes effect immediately, no restart needed":
            "Переключается сразу, перезапуск не нужен",
        "Save folder": "Папка сохранений",
        "Browse...": "Обзор...",
        "Current folder": "Текущая папка",
        "Use the current working folder": "Подставить рабочую папку приложения",
        "Folder holding plyslotN.svg / plyslotN.dat":
            "Папка с файлами plyslotN.svg / plyslotN.dat",
        "Game data": "Файлы игры",
        "Folder with wil.gmp / wil.sty / wil.scr and the other two cities.\n"
        "The mission table is rebuilt from the .scr when the city changes.":
            "Папка с wil.gmp / wil.sty / wil.scr и файлами двух других городов.\n"
            "Из .scr строится таблица миссий при смене города.",
        "Behaviour": "Поведение",
        "Make a timestamped backup before writing":
            "Автоматически делать резервную копию перед записью",
        "Ask for confirmation when quitting with unsaved edits":
            "Спрашивать подтверждение при выходе с несохранёнными правками",
        "Show the hex address column in the viewer":
            "Показывать колонку с hex-адресами в просмотре",
        "Open folder": "Открыть папку",
        "Reset all": "Сбросить всё",
        "Restore the default values.\nSave files are not affected.":
            "Вернуть значения по умолчанию.\nФайлы сохранений при этом не "
        "затрагиваются.",
        "Select the save folder": "Выберите папку сохранений",
        "Select the game data folder": "Выберите папку с файлами игры",
        "Normal size.": "Обычный размер.",
        "Extreme value of the range.": "Крайнее значение диапазона.",
        "Smaller interface - more data on screen.":
            "Уменьшенный интерфейс — больше данных на экране.",
        "Larger interface - easier on high-DPI displays.":
            "Увеличенный интерфейс — удобнее на высоких DPI.",
        "Config: %1": "Конфигурация: %1",
        "Font: %1, %2 pt, screen %3 DPI": "Шрифт: %1, %2 pt, экран %3 DPI",
    },
    "SaveFile": {
        "cannot open %1: %2": "не удалось открыть %1: %2",
        "cannot write %1: %2": "не удалось записать %1: %2",
        "%1 is %2 B, expected %3 B": "%1 имеет размер %2 Б, ожидалось %3 Б",
        "%1 is %2 B, block0 alone needs %3 B":
            "%1 имеет размер %2 Б, одному block0 нужно %3 Б",
        "%1 ends inside trailing block %2": "%1 обрывается внутри хвостового блока %2",
        "%1: trailing block %2 claims %3 B but only %4 B left":
            "%1: хвостовой блок %2 заявляет %3 Б, но осталось только %4 Б",
        "short write on length": "короткая запись длины",
        "short write on block0": "короткая запись block0",
        "short write on trailing block": "короткая запись хвостового блока",
        "short write on %1": "короткая запись %1",
        "No usable template: the save needs three trailing map-constant blocks "
        "and none could be read from %1. Open an existing save of this city "
        "first and use it as the template.":
            "Нет подходящего шаблона: сохранению нужны три хвостовых блока "
        "констант карты, а прочитать их из %1 не удалось. Сначала откройте "
        "существующее сохранение этого города и используйте его как шаблон.",
        "(nothing)": "(ничего)",
        "No .svg loaded.": ".svg не загружен.",
        "Mission script was not loaded.": "Скрипт миссий не загружен.",
        "%1 is not the mission script for %2 (%3).":
            "%1 не является скриптом миссий для %2 (%3).",
    },
    "ScriptFile": {
        "Cannot open %1: %2": "Не удалось открыть %1: %2",
    },
}

# tr() / translate("Ctx", "literal") / QT_TRANSLATE_NOOP("Ctx", "literal")
RE_TR = re.compile(r'\btr\(\s*(?:QStringLiteral\()?"((?:[^"\\]|\\.)*)"\s*\)')
RE_TRANSLATE = re.compile(
    r'QCoreApplication::translate\(\s*"([A-Za-z0-9_]+)"\s*,\s*'
    r'(?:QStringLiteral\()?"((?:[^"\\]|\\.)*)"')
RE_NOOP = re.compile(
    r'QT_TRANSLATE_NOOP\(\s*"([A-Za-z0-9_]+)"\s*,\s*'
    r'(?:QStringLiteral\()?"((?:[^"\\]|\\.)*)"')
# %1 placeholders differ in width between adjacent literals, so adjacent
# strings separated by a newline inside one tr() are joined before matching.
RE_TR_CONCAT = re.compile(
    r'\btr\(("(?:"(?:[^"\\]|\\.)*"\s*)+)\)', re.S)


def unescape(s: str) -> str:
    return (s.replace('\\n', '\n').replace('\\t', '\t')
             .replace('\\"', '"').replace('\\\\', '\\'))


def escape(s: str) -> str:
    return (s.replace('\\', '\\\\').replace('"', '\\"')
             .replace('\n', '\\n').replace('\t', '\\t'))


def context_for(path: Path) -> str:
    name = path.stem
    if name == "cli_main":
        return "cli_main"
    return name


def collect(path: Path) -> dict[str, set[str]]:
    text = path.read_text(encoding="utf-8", errors="replace")
    ctx = context_for(path)
    found: dict[str, set[str]] = {}

    for m in RE_TR_CONCAT.finditer(text):
        lits = re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1))
        if lits:
            found.setdefault(ctx, set()).add(unescape("".join(lits)))
    for m in RE_TR.finditer(text):
        found.setdefault(ctx, set()).add(unescape(m.group(1)))
    for rx, has_ctx in ((RE_TRANSLATE, True), (RE_NOOP, True)):
        for m in rx.finditer(text):
            found.setdefault(m.group(1), set()).add(unescape(m.group(2)))
    return found


def render(code: str, lang: str, table: dict[str, dict[str, str]]) -> str:
    out = ['<?xml version="1.0" encoding="utf-8"?>', "<!DOCTYPE TS>",
           f'<TS version="2.1" language="{lang}">']
    for ctx in sorted(table):
        strings = table[ctx]
        out.append("<context>")
        out.append(f"    <name>{html.escape(ctx)}</name>")
        for s in sorted(strings):
            tr = strings.get(s, "")
            out.append("    <message>")
            out.append(f"        <source>{html.escape(s)}</source>")
            if tr:
                out.append(f"        <translation>{html.escape(tr)}</translation>")
            else:
                out.append('        <translation type="unfinished"></translation>')
            out.append("    </message>")
        out.append("</context>")
    out.append("</TS>")
    return "\n".join(out) + "\n"


def main() -> int:
    allstrings: dict[str, set[str]] = {}
    for p in sorted(SRC.glob("*.cpp")):
        for ctx, strings in collect(p).items():
            allstrings.setdefault(ctx, set()).update(strings)

    OUT.mkdir(exist_ok=True)

    # English catalogue: identity translations, so the file exists as a
    # template and a new string shows up as unfinished rather than missing.
    en = {c: {s: s for s in strings} for c, strings in allstrings.items()}
    (OUT / "editsave_en.ts").write_text(
        render("en", "en_US", en), encoding="utf-8")

    ru = {c: RU.get(c, {}) for c in allstrings}
    missing = [
        (c, s) for c in allstrings for s in sorted(allstrings[c])
        if s not in RU.get(c, {})
    ]
    (OUT / "editsave_ru.ts").write_text(
        render("ru", "ru_RU", ru), encoding="utf-8")

    print(f"contexts: {len(allstrings)}  strings: {sum(len(v) for v in allstrings.values())}")
    if missing:
        print(f"untranslated (kept as English, {len(missing)}):")
        for c, s in missing:
            print(f"  {c}: {s!r}")
    return 0


if __name__ == "__main__":
    sys.exit(main())
