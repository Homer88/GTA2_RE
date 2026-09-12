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

MenuItem::MenuItem()
{
    Reset();
}

MenuItem::~MenuItem()
{
    // Деструктор пустой - нет динамических ресурсов
}

// ============================================================================
// Методы инициализации
// ============================================================================

void MenuItem::Initialize(bool  isActive,  short X, int Y, bool  IndexMenuActions, const wchar_t* description)
{
    IsActive = isActive;
    this->X = X;
    this->Y = Y;
    this->IndexMenuActions = IndexMenuActions;
    
    if (description != 0)
    {
        SetDescription(description);
    }
}

void MenuItem::SetDescription(const wchar_t* text, size_t maxLength)
{
    if (text == 0)
    {
        Description[0] = L'\0';
        return;
    }
    
    // Безопасное копирование с ограничением длины
    size_t copyLen = (maxLength < 49) ? maxLength : 49;
    wcsncpy(Description, text, copyLen);
    Description[copyLen] = L'\0';  // Гарантируем нуль-терминатор
}

void MenuItem::Reset()
{
    IsActive = 0;
    this->X = 0;
    this->Y = 0;
    this->IndexMenuActions = false;
    
    // Очищаем строку описания
    std::memset(Description, 0, sizeof(Description));
}

void MenuItem::CopyFrom(const MenuItem& other)
{
    IsActive = other.IsActive;
    this->X = other.X;
    this->Y = other.Y;
    this->IndexMenuActions = other.IndexMenuActions;
    
    // Копируем строку описания
    std::memcpy(Description, other.Description, sizeof(Description));
}