# -*- coding: utf-8 -*-
"""Анализатор классов GTA2_RE: генерирует документы по каждому классу."""
import os, re

ROOT = r"C:\work\GTA2_RE\gta2"
OUTDIR = r"C:\work\GTA2_RE\Doc\Классы"

GAME = "Game"
ENGINE = "Engine"


def read(path):
    try:
        with open(path, "r", encoding="utf-8-sig", errors="replace") as f:
            return f.read()
    except OSError:
        return ""


def strip_comments(text):
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.S)
    text = re.sub(r"//[^\n]*", "", text)
    return text


def class_body(text, classname):
    """Возвращает текст внутри class <classname> { ... }."""
    m = re.search(r"\bclass\s+" + re.escape(classname) + r"\s*(?::\s*[A-Za-z_][A-Za-z0-9_<>\*&,\s]*)?\s*\{", text)
    if not m:
        return None
    body = text[m.end():]
    depth = 0
    i = 0
    while i < len(body):
        ch = body[i]
        if ch == "{":
            depth += 1
        elif ch == "}":
            if depth == 0:
                return body[:i]
            depth -= 1
        i += 1
    return body


def find_methods_in_header(path, classname):
    text = strip_comments(read(path))
    body = class_body(text, classname)
    if body is None:
        return []
    pat = re.compile(
        r"(?m)^[ \t]*(?:virtual\s+|static\s+)*"
        r"[A-Za-z_][A-Za-z0-9_<>\*&:\s]*\s+"
        r"([A-Za-z_~][A-Za-z0-9_]*)\s*"
        r"\(([^;{}]*)\)\s*(?:const\s*)?(?:override|final)?\s*;"
    )
    fs = set()
    for m in pat.finditer(body):
        name = m.group(1)
        args = m.group(2).strip()
        if args == "void":
            args = ""
        fs.add((name, args))
    return sorted(fs)


def find_definitions_in_cpp(path, classname):
    """Возвращает {name: {"start":int,"end":int}} (номера строк)."""
    lines = read(path).split("\n")
    if not lines or not "".join(lines).strip():
        return {}
    result = {}
    pat = re.compile(r"\b(" + re.escape(classname) + r")\s*::\s*([A-Za-z_~][A-Za-z0-9_]*)\s*\(")
    for lineno, l in enumerate(lines, start=1):
        stripped = strip_comments(l)
        seg = stripped.split("{")[0]
        for h in pat.finditer(seg):
            name = h.group(2)
            if name in result:
                continue
            # тело от текущей строки (не с начала файла!)
            depth = 0
            started = False
            end = lineno
            for j in range(lineno - 1, len(lines)):
                raw = lines[j]
                for ch in raw:
                    if ch == "{":
                        depth += 1
                        started = True
                    elif ch == "}":
                        depth -= 1
                        if started and depth == 0:
                            end = j + 1
                            break
                if started and depth == 0:
                    break
            result[name] = {"start": lineno, "end": end}
    return result


def is_stub(body):
    b = body.strip()
    # убираем комментарии для оценки реального кода
    nocom = re.sub(r"/\*.*?\*/", " ", b, flags=re.S)
    nocom = re.sub(r"//[^\n]*", "", nocom).strip()
    if re.fullmatch(r"\{\s*\}", b):
        return True
    first = nocom.find("{")
    if first < 0:
        return False
    body_after_brace = nocom[first + 1:].strip()
    if len(body_after_brace) > 150:
        return False
    inner = body_after_brace.replace("{", "").replace("}", "").strip()
    if inner == "":
        return True
    if re.fullmatch(r"return\s+(0|NULL|nullptr|false|true)\s*;", inner):
        return True
    # защитный код по структуре (большая функция с логикой) — не заглушка
    return len(inner) <= 20 and ";" in inner and not re.search(r"new\s|=\s|if\s*\(|for\s*\(|while\s*\(", inner)


def addr_from_body(body):
    """Адрес из комментария вида 'Адрес: 0x...' — только адреса дампа (6+ hex-цифр)."""
    m = re.search(r"0[xX][0-9a-fA-F]{6,8}", body)
    return m.group(0) if m else ""


def is_partial(body):
    """Частичная реализация: есть маркер TODO/FIXME/заглушк/нужна реализация."""
    return bool(re.search(r"TODO|FIXME|заглушк|нужна реализация|нужн[оа]\s+реализац", body, re.I))


def raw_body(lines, start, end):
    return "\n".join(lines[start - 1:end])


def analyze_class(folder, classname):
    cpp_files = [f for f in os.listdir(folder) if f.lower().endswith(".cpp")]
    h_files = [f for f in os.listdir(folder) if f.lower().endswith(".h")]

    methods = [m for hf in h_files for m in find_methods_in_header(os.path.join(folder, hf), classname)]
    declared = {name for (name, _) in methods}

    defs = {}
    for cf in cpp_files:
        dd = find_definitions_in_cpp(os.path.join(folder, cf), classname)
        if dd:
            raw = read(os.path.join(folder, cf)).split("\n")
            for n, d in dd.items():
                d["body"] = raw_body(raw, d["start"], d["end"])
                d["lines"] = d["end"] - d["start"] + 1
            defs.update(dd)

    implemented, partials, stubs, missing = [], [], [], []
    for (name, args) in methods:
        if name in defs:
            d = defs[name]
            addr = addr_from_body(d["body"])
            entry = (name, args, d["start"], d["lines"], addr)
            if is_stub(d["body"]):
                stubs.append(entry)
            elif is_partial(d["body"]):
                partials.append(entry)
            else:
                implemented.append(entry)
        else:
            missing.append((name, args))

    extra = sorted(n for n in defs
                   if n not in declared and not n.startswith("~")
                   and n != classname)
    cpp_lines = sum(len(read(os.path.join(folder, f)).split("\n")) for f in cpp_files)
    h_lines = sum(len(read(os.path.join(folder, f)).split("\n")) for f in h_files)
    return {"methods": methods, "implemented": implemented, "partials": partials,
            "stubs": stubs, "missing": missing, "extra": extra,
            "cpp_lines": cpp_lines, "h_lines": h_lines}


def main():
    os.makedirs(OUTDIR, exist_ok=True)
    summary = []
    for lib in (GAME, ENGINE):
        base = os.path.join(ROOT, lib)
        for d in sorted(os.listdir(base)):
            folder = os.path.join(base, d)
            if not os.path.isdir(folder):
                continue
            if not os.path.exists(os.path.join(folder, "CMakeLists.txt")):
                continue
            if not any(f.lower().endswith(".cpp") for f in os.listdir(folder)):
                continue
            info = analyze_class(folder, d)
            total = len(info["methods"])
            # частичные учитываются с коэффициентом 0.5
            pct = round(100.0 * (len(info["implemented"]) + 0.5 * len(info["partials"])) / total) if total else 0

            L = [f"# {d}", "",
                 f"- **Место**: `gta2/{lib}/{d}/`",
                 f"- **Файлы**: `.cpp` {info['cpp_lines']} строк, `.h` {info['h_lines']} строк",
                 f"- **Методов**: {total}"]
            if total:
                L += [f"- **Полностью реализовано**: {len(info['implemented'])}",
                      f"- **Частично (TODO/незавершено)**: {len(info['partials'])}",
                      f"- **Заглушки**: {len(info['stubs'])}",
                      f"- **Объявлено, но не определено**: {len(info['missing'])}",
                      f"- **Реализация в целом: ~{pct}%** (полные + 0.5*частичные)"]
            else:
                L.append("- **Методов не найдено** (структура данных / глобальные функции)")
            L.append("")

            def section(title, rows, show_addr=True):
                if not rows:
                    return []
                hdr = "| метод | строка | строк кода | адрес из дампа |" if show_addr else "| метод | строка | строк кода |"
                sep = "|---|---|---|---|" if show_addr else "|---|---|---|"
                s = [f"## {title}", "", hdr, sep]
                for r in sorted(rows, key=lambda x: x[2]):
                    name, args, line, bl = r[0], r[1], r[2], r[3]
                    addr = r[4] if show_addr else ""
                    if show_addr:
                        s.append(f"| `{name}({args})` | {line} | {bl} | {addr} |")
                    else:
                        s.append(f"| `{name}({args})` | {line} | {bl} |")
                s.append("")
                return s

            L += section("Полностью реализованные методы", info["implemented"])
            L += section("Частично реализованные (есть TODO/не завершены)", info["partials"])
            L += section("Заглушки (мини-тела / return-заглушки)", info["stubs"])
            if info["missing"]:
                L += ["## Объявлены в .h, но не определены", ""]
                L += [f"- `{n}({a})`" for (n, a) in sorted(info["missing"])]
                L.append("")
            if info["extra"]:
                L += ["## Свободные функции в .cpp (глобальные)", "",
                      ", ".join(f"`{n}`" for n in info["extra"]), ""]

            with open(os.path.join(OUTDIR, f"{d}.md"), "w", encoding="utf-8") as f:
                f.write("\n".join(L))
            summary.append((d, f"gta2/{lib}/{d}", total,
                            len(info["implemented"]), len(info["partials"]), pct,
                            len(info["stubs"]), len(info["missing"]), info["cpp_lines"]))

    with open(os.path.join(OUTDIR, "README.md"), "w", encoding="utf-8") as f:
        f.write("# Классы GTA2_RE: состояние реализации\n\n")
        f.write("Сводная таблица (по `<Класс>`.md — детали).\n\n")
        f.write("| Класс | Путь | Методов | Полн. | Частичн. | Заглушки | Нет опр. | ~% | Строк cpp |\n")
        f.write("|---|---|---|---|---|---|---|---|---|\n")
        for (cn, rel, total, full, part, pct, st, miss, cpp) in sorted(summary, key=lambda r: r[5], reverse=True):
            f.write(f"| {cn} | `{rel}` | {total} | {full} | {part} | {st} | {miss} | {pct}% | {cpp} |\n")
    print(f"Готово: {len(summary)} документов в {OUTDIR}")


if __name__ == "__main__":
    main()