/**
 * @file MenuItemConfig.cpp
 * @brief Реализация структуры MenuItemConfig (S140)
 * 
 * Конфигурация текстового элемента меню GTA 2
 * Размер: 108 байт
 */


#include <cstring>
#include "MenuItemConfig.h"


// ============================================================================
// Конструкторы и деструкторы
// ============================================================================

MenuItemConfig::MenuItemConfig()
{
    Reset();
}

MenuItemConfig::~MenuItemConfig()
{
    // Деструктор пустой - нет динамических ресурсов
}

// ============================================================================
// Методы инициализации
// ============================================================================

void MenuItemConfig::Initialize(char isActive, char subType,
                                 short param1, int param2,
                                 int selectedIndex, const wchar_t* description)
{
    IsActive = isActive;
    SubType = subType;
    Param1 = param1;
    Param2 = param2;
    SelectedIndex = selectedIndex;
    
    if (description != nullptr)
    {
        SetDescription(description);
    }
}

void MenuItemConfig::SetDescription(const wchar_t* text, size_t maxLength)
{
    if (text == nullptr)
    {
        Description[0] = L'\0';
        return;
    }
    
    // Безопасное копирование с ограничением длины
    size_t copyLen = (maxLength < 49) ? maxLength : 49;
    wcsncpy(Description, text, copyLen);
    Description[copyLen] = L'\0';  // Гарантируем нуль-терминатор
}

void MenuItemConfig::Reset()
{
    IsActive = 0;
    SubType = 0;
    Param1 = 0;
    Param2 = 0;
    SelectedIndex = 0;
    
    // Очищаем строку описания
    std::memset(Description, 0, sizeof(Description));
}

void MenuItemConfig::CopyFrom(const MenuItemConfig& other)
{
    IsActive = other.IsActive;
    SubType = other.SubType;
    Param1 = other.Param1;
    Param2 = other.Param2;
    SelectedIndex = other.SelectedIndex;
    
    // Копируем строку описания
    std::memcpy(Description, other.Description, sizeof(Description));
}