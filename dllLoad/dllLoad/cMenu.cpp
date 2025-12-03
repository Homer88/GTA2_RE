#include <Windows.h>
#include <stdio.h>
#include "cMenu.h"


static  Menu* gMenu = (Menu*)0x005EB160;

//char gNamePlayerASCII[80] ;
unsigned char*gNamePlayerASCII = (unsigned char*)0x00671880;
int len = 0;

//char* __thiscall Menu::WCHARToChar(Menu* this, char* PlayerName)
unsigned char * __stdcall WCHARToChar(Menu* pthis, wchar_t *PlayerName)
{
    if (!PlayerName) {
        gNamePlayerASCII[0] = '\0';
        return gNamePlayerASCII;
    }

    int i = 0;
    const wchar_t* src = PlayerName;
    constexpr int MAX_LENGTH = 79; // Один символ для нуль-терминатора

    // Преобразуем до 79 символов (последний остаётся для '\0')
    while (*src != L'\0' && i < MAX_LENGTH) {
        if (*src < 0x80) { // ASCII символ
            gNamePlayerASCII[i] = static_cast<char>(*src);
        }
        else { // Не-ASCII символ - заменяем на '#'
            gNamePlayerASCII[i] = '#';
        }
        ++src;
        ++i;
    }
    gNamePlayerASCII[i] = '\0';
    return gNamePlayerASCII;
}


//char __thiscall Menu::PlayerCheat(Menu* this, wchar_t* PlayerName)
char __stdcall PlayerCheat(Menu* pthis, wchar_t* edx, wchar_t* PlayerName)
{
    MessageBox(NULL, PlayerName, 0, 0);
    printf("test");
    unsigned char *chName=WCHARToChar(pthis, PlayerName);
    OutputDebugStringA("error DetourTransactionBegin");
    MessageBox(NULL, (LPCWSTR)gNamePlayerASCII, NULL, NULL);
    MessageBox(NULL, (LPCWSTR)chName, 0, 0);
    MessageBox(NULL, L"Дальши идем", 0, 0);
    return 0;



}