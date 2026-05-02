#ifndef __MENU_STRING_SLOT_H_
#define __MENU_STRING_SLOT_H_

#include <string>


/**
 * @brief Структура S140 (переименована в MenuStringSlot)
 * 
 * Предположительное назначение: Строковый элемент меню или локализованная строка конфигурации.
 * Содержит флаги, идентификатор выбора и широкую строку (Unicode).
 * 
 * Исходный размер: 108 байт
 */
class  MenuStringSlot {
public:
    unsigned char  fild;          // 0x00 - Флаг состояния или типа
    unsigned char  field_1;       // 0x01 - Дополнительный флаг
    unsigned short field_2;       // 0x02 - Параметр (возможно, ID или смещение)
    unsigned short field_4;       // 0x04 - Параметр (возможно, цвет или стиль)
    unsigned short Select;        // 0x06 - Индекс выбора или активный статус
    wchar_t  str[50];       // 0x08 - Текстовое содержимое (Unicode, макс 49 симв + \0)

    // Статическая константа размера строки
    static constexpr size_t MAX_STRING_LENGTH = 50;

    // Конструктор по умолчанию (инициализация нулями)
    MenuStringSlot();
       

    // Конструктор с параметрами
    MenuStringSlot::MenuStringSlot(unsigned char flags, unsigned short id, const wchar_t* text);

    // Геттеры
    unsigned char getFlags()const;
    unsigned short getId()const;
    unsigned short getSelectIndex()const;
    
    std::wstring getText() const;

    // Сеттеры
    void setFlags(unsigned char flags);
    void setId(unsigned short id);
    void setSelectIndex(unsigned short index);
    
    void setText(const wchar_t* text);

    // Проверка размера структуры (для отладки)
    static constexpr size_t expectedSize();
};



#endif // !__MENU_STRING_SLOT_H_