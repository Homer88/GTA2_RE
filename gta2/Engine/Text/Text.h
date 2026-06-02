#ifndef __TEXT_H_
#define __TEXT_H_


class Text {
public:
	char Language = 'e';
	char *Base;
	int NumberOfElements;
	Text();
	~Text();
	void* Bsearch(const void* pKey);
	wchar_t* ConvertWordsToBig(wchar_t* str);
	wchar_t ConvertToUpper(wchar_t str);
	unsigned __int16 Font::GetStringWidth(wchar_t*, unsigned __int16);
    unsigned __int16 Font::GetCharHeight(unsigned __int16);    
};

#endif
