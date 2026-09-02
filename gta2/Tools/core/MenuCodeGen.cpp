#include "MenuCodeGen.h"

#include <cstdio>
#include <sstream>

namespace gta2tools {

namespace {

// Текст wchar -> литерал L"\xNNNN\xNNNN..." (шестнадцатеричные эскейпы, чтобы
// сгенерированный .cpp не зависел от кодировки файла и собирался на любом компиляторе).
std::string WToEscapes(const std::wstring& s)
{
	std::ostringstream o;
	for (size_t i = 0; i < s.size(); i++) {
		char buf[8];
		sprintf(buf, "\\x%04X", (unsigned)s[i]);
		o << buf;
	}
	return o.str();
}

} // namespace

std::string GenerateMenuCode(const MenuProjectModel& p)
{
	std::ostringstream o;
	o << "// Сгенерировано GTA2 MenuEditor. Менять вручную не рекомендуется.\n";
	o << "#include \"MenuPage.h\"\n\n";

	for (size_t pi = 0; pi < p.pages.size(); pi++) {
		const MenuPageModel& pg = p.pages[pi];
		size_t n = pg.entries.size();
		if (n > 10)
			n = 10;

		o << "static void BuildPage" << pg.id << "(MenuPage& page)\n{\n";
		o << "    page.NumberMenuItems[0] = " << (int)n << ";\n";
		o << "    page.NumberMenuItems[1] = 0;\n";

		for (size_t i = 0; i < n; i++) {
			const MenuEntryModel& e = pg.entries[i];
			o << "    { MenuEntry& e = page.MenuEntryArray[" << i << "];\n";
			o << "      e.X = " << e.x << "; e.Y = " << e.y << "; e.Index = " << (int)i << ";\n";
			o << "      e.MenuAction = " << e.action << "; e.SelectMenu = " << e.target << ";\n";
			o << "      e.StringLength = " << (int)e.text.size() << ";\n";
			o << "      swprintf(e.TextMenuElementArray, 50, L\"" << WToEscapes(e.text) << "\");\n";
			o << "    }\n";
		}
		o << "}\n\n";
	}

	o << "// Сборка страницы по номеру (точка входа логики меню).\n";
	o << "void MenuLogicBuild(int pageId, MenuPage& page)\n{\n";
	o << "    switch (pageId)\n    {\n";
	for (size_t pi = 0; pi < p.pages.size(); pi++) {
		const MenuPageModel& pg = p.pages[pi];
		o << "    case " << pg.id << ": BuildPage" << pg.id << "(page); break;\n";
	}
	o << "    default: break;\n";
	o << "    }\n}\n";

	return o.str();
}

} // namespace gta2tools