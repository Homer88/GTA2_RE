#ifndef _TEXT_H__
#define _TEXT_H__

#include <assert.h>

struct Text
{
	void *Base;
	size_t Number;
	Text* NextText;
	unsigned char un10;
	unsigned char un11;
	unsigned char un12;
	unsigned char un13;
	unsigned char Language;
	unsigned char uns15;
	unsigned char uns16;
	unsigned char uns17;


};

static_assert (sizeof(Text) == 0x14, "Error size Text");
//static Text* gText = (Text*)0x00671550;


bool GetLanguageJapan(Text* pText);
//wchar_t __stdcall Bsearch(const void* pKey);
void* __stdcall Bsearch(const void* pKey);
const wchar_t** __stdcall Bsearch(Text* pthis, const void* pKey);
wchar_t* __stdcall Bsearch(const wchar_t* pKey);


#endif // !_Text_H__

