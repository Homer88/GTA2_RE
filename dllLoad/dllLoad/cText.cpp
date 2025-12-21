#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>

#include "cText.h"

Text *gText = (Text*)0x00671550;

bool GetLanguageJapan(Text* pText) {

	MessageBox(0, L"Попали в cText", 0, 0);
	return pText->Language == 'j';
}

int cmp_strings(const void* p1, const void* p2) {
	const wchar_t* str1 = *(const wchar_t**)p1;
	const wchar_t* str2 = *(const wchar_t**)p2;
	return wcscmp(str1, str2);
}

void * __stdcall Bsearch(const void* pKey) {

	void* data = bsearch(pKey, gText->Base, gText->Number, 12, cmp_strings);
	if (data)
		return data;


	return (void*)" ";
}
wchar_t* __stdcall Bsearch(const wchar_t* pKey) {
	// Предположим, что gText->Base — массив указателей на wchar_t*
	// Размер элементов — это указатель, поэтому sizeof(wchar_t*)
	/**wchar_t** result = (wchar_t**)bsearch(
		&pKey,                   // указатель на ключ
		gText->Base,             // массив базовых данных
		gText->Number,           // количество элементов
		sizeof(wchar_t*),        // размер каждого элемента
		cmp_strings              // функция сравнения
	);*/
	//if (result) {
//		return *result; // возвращаем найденную строку
	//}
	return (wchar_t*)L" "; // возвращаем пробел, если не найдено
}


const wchar_t** __stdcall Bsearch(Text* pthis, const void* pKey) {

	const wchar_t** data =(const wchar_t**)bsearch(&pKey, gText->Base, gText->Number, 12, cmp_strings);
	if (data)
		return data;


	return (const wchar_t**)" ";
}