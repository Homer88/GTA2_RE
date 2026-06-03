#ifndef __FONT_H_
#define __FONT_H_

class Font {
public:
	unsigned short GetStringWidth(wchar_t* Text, unsigned short* stringLength);
	wchar_t GetCharHeight(wchar_t) ;

};



#endif // !__FONT_H_

