#include "Font.h"
#include "../Style/Style.h"

Font *gFont;
extern Style* gStyle;

unsigned short Font::GetStringWidth(wchar_t* Text, unsigned short stringLength) {
	// IDA 0x4CB0C0: uses Style remap/width tables.
	// Use StyleGetRemapColour when idaView is available; otherwise keep 8px fallback.
	if (!Text) return 0;
	unsigned short cur = 0;
	unsigned short maxW = 0;
	unsigned short spaceW = 8;
	unsigned short style = stringLength;
	if (gStyle) {
		short remap = gStyle->GetRemapColour16(&style);
		if (remap > 0 && remap < 64) spaceW = (unsigned short)remap;
	}
	for (int i = 0; Text[i] && i < 1024; ++i) {
		wchar_t c = Text[i];
		if (c == L' ') cur = (unsigned short)(cur + spaceW);
		else if (c == L'\n') { if (cur > maxW) maxW = cur; cur = 0; }
		else if (c == L'#') { /* toggle in IDA */ }
		else {
			unsigned short glyphW = 8;
			if (gStyle && gStyle->GetIdaView()) {
				unsigned short ch = (unsigned short)c;
				glyphW = gStyle->StyleGetRemapColour((wchar_t*)&style, &ch);
				if (glyphW == 0 || glyphW > 64) glyphW = 8;
			}
			cur = (unsigned short)(cur + glyphW);
		}
	}
	if (cur > maxW) maxW = cur;
	return maxW;
}

unsigned short Font::GetNumberLines(wchar_t* Text, unsigned short maxWidth) {
	// IDA 0x4CC0C0: returns total pixel height = charHeight + charHeight per '\n'.
	// maxWidth/style handling is simplified in RE (no Style width tables).
	if (!Text) return 0;
	int ch = GetCharHeight((unsigned short)maxWidth);
	if (ch <= 0) ch = 8;
	int h = ch;
	for (int i = 0; Text[i]; ++i) {
		if (Text[i] == L'\n') h += ch;
	}
	return (unsigned short)h;
}

int Font::GetCharHeight(unsigned short style) {
	// IDA 0x4539B0: returns Style::GetRemapColour32(gStyle, &style).
	if (gStyle) {
		unsigned short s = style;
		short h = gStyle->GetRemapColour32(&s);
		if (h > 0 && h < 64) return h;
	}
	return 8;
}

wchar_t Font::GetCharHeight(wchar_t) {
	return 8;
}
