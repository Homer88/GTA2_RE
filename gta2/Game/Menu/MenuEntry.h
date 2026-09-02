#ifndef ___MENU_ENTRY_H_
#define ___MENU_ENTRY_H_


// Структура MenuEntry (элемент меню)
// Размер: предположительно 0x50 байт
class MenuEntry {
public:
    int  MenuAction;             // +0x00 - тип действия
    unsigned int  X;                     // +0x04 - координата X
    unsigned int Y;                     // +0x08 - координата Y
    wchar_t TextMenuElementArray[50];    // +0x0C - текст надписи (50 байт)
    int PlayerSlot;              // +0x3E - слот игрока (выравнивание?)
    int PlayerSlotNext;
    int Index;///  Количество пунктов 
    char Flag[4];                // +0x42 - флаги видимости (4 байта)
    int SelectMenu;              //логика выбора действия 
    int StringLength;
    // Возможно есть выравнивание до 0x50
    MenuEntry();
    void Init();
    bool UpdateToPreviousActive();
    bool InitializeEntry();
} ;


#endif // !___MENU_ENTRY_H_
