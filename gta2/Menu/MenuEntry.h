#ifndef ___MENU_ENTRY_H_
#define ___MENU_ENTRY_H_


// Структура MenuEntry (элемент меню)
// Размер: предположительно 0x50 байт
class MenuEntry {
public:
    int  MenuAction;             // +0x00 - тип действия
    float X;                     // +0x04 - координата X
    float Y;                     // +0x08 - координата Y
    char TextMenuElement[50];    // +0x0C - текст надписи (50 байт)
    int PlayerSlot;              // +0x3E - слот игрока (выравнивание?)
    char Flag[4];                // +0x42 - флаги видимости (4 байта)
    // Возможно есть выравнивание до 0x50
    MenuEntry();
    void Init();
} ;


#endif // !___MENU_ENTRY_H_
