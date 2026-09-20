#include "Keybord.h"
#include "../FileMgr/FileMgr.h"
#include "../Debug/DebugLogFile.h"
#include <windows.h>
#include <winuser.h>
#include <stdio.h>
Keybord* gKeybord;

    // 0x00461060
Keybord::Keybord() {
    this->Layout = KB_ENG;

}

int Keybord::LoadKeybord(){
    this->Layout = KB_ENG;

    // Получаем строку вида "00000409"
    char layoutName[9] = { 0 };
    GetKeyboardLayoutNameA(layoutName);

    // Парсим последние две hex-цифры
    unsigned int layoutId = 0;
    sscanf(&layoutName[6], "%x", &layoutId);

   /* const char* cfgPath = NULL;
    switch (layoutId)
    {
    case 0x07: this->Layout = KB_GER; cfgPath = "data\\keyboard\\ger_kb.cfg"; break;
    case 0x0A: this->Layout = KB_SPA; cfgPath = "data\\keyboard\\spa_kb.cfg"; break;
    case 0x0C: this->Layout = KB_FRE; cfgPath = "data\\keyboard\\fre_kb.cfg"; break;
    case 0x10: this->Layout = KB_ITA; cfgPath = "data\\keyboard\\ita_kb.cfg"; break;
    case 0x16: this->Layout = KB_POR; cfgPath = "data\\keyboard\\por_kb.cfg"; break;
    default:   this->Layout = KB_ENG; cfgPath = "data\\keyboard\\eng_kb.cfg"; break;
    }

    FILE* f = gFileMgr->WriteReadFile(cfgPath, "rt");
    if (!f) {
        DebugLog(0x97, "keybrd.cpp", 172);
        // оригинал продолжает работу и падает на fclose(NULL)
    }

    WORD* pCodeKey = this->CodeKey;   // CodeKey — массив WORD[256]
    for (int i = 0; i < 256; ++i)
    {
        WORD values[6];
        gFileMgr->ReadToken(f, values);   // читает строку и парсит два числа

        if (values[0] == 126)
            pCodeKey[i] = 0;
        else if (values[0] == 96)
            pCodeKey[i] = values[1];
        else
            pCodeKey[i] = 0;
    }

    return fclose(f);*/
    //возможно потом  отладим а так смысла нету.
    return 0;
    }


    // 0x004611F0


int Keybord::Keydown(){
        return 0;
    }

