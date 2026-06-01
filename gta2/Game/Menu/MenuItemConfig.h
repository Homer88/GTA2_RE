#ifndef ___MENUITEMCONFIGURE_H_
#define ___MENUITEMCONFIGURE_H_
/**
 * @file MenuItemConfig.h
 * @brief Конфигурация текстового элемента меню
 * 
 * Оригинальное имя: S140
 * Размер: 108 байт (6 полей)
 * Используется: массив элементов меню или настроек
 * 
 * Предназначение: Хранит конфигурацию текстового элемента меню:
 * - fild: Флаг активности / типа элемента
 * - field_1: Дополнительные флаги / подтип
 * - field_2: Значение параметра 1 (ID, индекс)
 * - field_4: Значение параметра 2 (счетчик, состояние)
 * - Selecet: Текущий выбранный вариант (для списков)
 * - str[50]: Текстовое описание элемента (Unicode)
 */
#include <wchar.h>

/**
 * @class MenuItemConfig
 * @brief Конфигурация текстового элемента меню
 * 
 * Адрес конструктора: 0x00452D10 (предположительно)
 * Адрес деструктора: 0x00452D20 (предположительно)
 * Адрес метода инициализации: 0x00452D30 (предположительно)
 */

class  MenuItem{
public:
    unsigned short X,Y;
    bool IsActive;           ///< Флаг активности
    bool IndexMenuActions;
    wchar_t  Description[50];
    /**
     * @brief Флаг активности / типа элемента
     * 0 = неактивен
     * 1 = активен
     * Другие значения = специальные типы элементов
     */
    //uint8_t IsActive;             // +0x00 (fild)
    
    /**
     * @brief Дополнительные флаги / подтип элемента
     * Битовые флаги или подкатегория элемента меню
     */
    //uint8_t SubType;              // +0x01 (field_1)
    
    /**
     * @brief Параметр 1: ID или индекс элемента
     * Может быть ссылкой на другую структуру или идентификатором
     */
    //uint16_t Param1;              // +0x02 (field_2)
    
    /**
     * @brief Параметр 2: Счетчик или состояние
     * Дополнительное числовое значение (счетчик, позиция, значение)
     */
    //uint32_t Param2;              // +0x04 (field_4)
    
    /**
     * @brief Текущий выбранный вариант
     * Для элементов со списком вариантов хранит текущий выбор
     * 0-based индекс или специальное значение
     */
    //uint32_t SelectedIndex;       // +0x08 (Selecet)
    
    /**
     * @brief Текстовое описание элемента
     * Unicode строка до 50 символов (100 байт)
     * Содержит отображаемое название элемента меню
     */
    //wchar_t Description[50];      // +0x0C (str)
    
    // Статический размер: 108 байт
   /// static_assert(sizeof(MenuItemConfig) == 108, "MenuItemConfig must be 108 bytes");
    
    /**
     * @brief Конструктор
     * Инициализирует все поля в 0/null
     */
    MenuItem();
    
    /**
     * @brief Деструктор
     * Очищает ресурсы (если есть)
     */
    ~MenuItem();
    
    /**
     * @brief Инициализация элемента меню
     * @param isActive Активность элемента
     * @param subType Подтип элемента
     * @param param1 Первый параметр (ID/индекс)
     * @param param2 Второй параметр (счетчик/состояние)
     * @param selectedIndex Начальный выбранный индекс
     * @param description Текстовое описание (Unicode строка)
     */
    
    void Initialize(bool  isActive, short X, int Y, bool  IndexMenuActions, const wchar_t* description);
    
    /**
     * @brief Установка текстового описания
     * @param text Unicode строка для установки
     * @param maxLength Максимальная длина копируемой строки
     */
    void SetDescription(const wchar_t* text, size_t maxLength = 49);
    
    /**
     * @brief Получение текстового описания
     * @return Указатель на внутреннюю строку описания
     */
    //const wchar_t* GetDescription() const { return Description; }
    
    /**
     * @brief Проверка активности элемента
     * @return true если элемент активен
     */
    bool IsActiveElement() const { return IsActive != false; }
    
    /**
     * @brief Установка активности
     * @param active Новое состояние активности
     */
    void SetActive(bool active) { IsActive = active ? 1 : 0; }
    
    /**
     * @brief Установка подтипа
     * @param type Новый подтип элемента
     */
    //void SetSubType(char type) { SubType = type; }
    
    /**
     * @brief Установка первого параметра
     * @param id Значение параметра 1
     */
  //  void SetParam1(short id) { Param1 = id; }
    
    /**
     * @brief Установка второго параметра
     * @param value Значение параметра 2
     */
   /// void SetParam2(short value) { Param2 = value; }
    
    /**
     * @brief Установка выбранного индекса
     * @param index Индекс выбранного элемента
     */
   // void SetSelectedIndex(short index) { SelectedIndex = index; }
    
    /**
     * @brief Получение выбранного индекса
     * @return Текущий выбранный индекс
     */
   // short GetSelectedIndex() const { return SelectedIndex; }
    
    /**
     * @brief Сброс всех настроек элемента
     */
    void Reset();
    
    /**
     * @brief Копирование из другой структуры
     * @param other Источник для копирования
     */
    void CopyFrom(const MenuItem& other);
};


#endif
