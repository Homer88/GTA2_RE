#include "MenuStringSlot.h"

// В данной реализации все методы инлайн в заголовочном файле.
// Этот файл создан для соблюдения структуры проекта и возможности
// расширения функциональности в будущем (например, логирование,
// сложная валидация или взаимодействие с другими системами).

MenuStringSlot::MenuStringSlot() 
    : fild(0)
        , field_1(0)
        , field_2(0)
        , field_4(0)
        , Select(0)
    {
        std::memset(str, 0, sizeof(str));
    }

MenuStringSlot::MenuStringSlot(unsigned char flags, unsigned short id, const wchar_t* text)
    : fild(flags)
    , field_1(0)
    , field_2(id)
    , field_4(0)
    , Select(0)
{
    std::memset(str, 0, sizeof(str));
    if (text) {
        std::wcsncpy(str, text, MAX_STRING_LENGTH - 1);
        str[MAX_STRING_LENGTH - 1] = L'\0';
    }
}


unsigned char MenuStringSlot::getFlags() const { 
    return fild; 
}
unsigned short MenuStringSlot::getId() const { 
    return field_2;
}
unsigned short MenuStringSlot::getSelectIndex() const { 
    return Select; 
}
std::wstring MenuStringSlot::getText() const {
    return std::wstring(str);
}



// Сеттеры
void MenuStringSlot::setFlags(unsigned char flags) { fild = flags; }
void MenuStringSlot::setId(unsigned short id) { field_2 = id; }
void MenuStringSlot::setSelectIndex(unsigned short index) { Select = index; }


void MenuStringSlot::setText(const wchar_t* text) {
    if (text) {
        std::wcsncpy(str, text, MAX_STRING_LENGTH - 1);
        str[MAX_STRING_LENGTH - 1] = L'\0';
    }
    else {
        std::memset(str, 0, sizeof(str));
    }
}


constexpr size_t MenuStringSlot::expectedSize() {
    return 108;
}