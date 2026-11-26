#ifndef __FONT_H_
#define __FONT_H_

class Font {
public:
	unsigned short GetStringWidth(wchar_t* Text, unsigned short stringLength); // IDA 0x4CB0C0
	unsigned short GetNumberLines(wchar_t* Text, unsigned short maxWidth); // IDA 0x4CC0C0 returns pixel height
	int GetCharHeight(unsigned short style); // IDA 0x4539B0
	wchar_t GetCharHeight(wchar_t); // legacy compat

};



#endif // !__FONT_H_

