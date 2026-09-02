// Заглушки недостающих внешних символов, на которые ссылаются скомпилированные
// (не-заглушенные) части Menu.cpp, Registry.cpp и т.п. Реализации появятся позже.

#include "../Player/PlayerSlotSlave.h"
#include "../../Engine/ultil/WinApi.h"

wchar_t* WinApi::CopyWideString(wchar_t* dest, wchar_t* source) {
    if (dest && source) {
        wchar_t* p = dest;
        while (*source) {
            *p++ = *source++;
        }
        *p = 0;
    }
    return dest;
}

PlayerSlotSlave::PlayerSlotSlave() {
}

void DebugLog(int, char*, int) {
}
