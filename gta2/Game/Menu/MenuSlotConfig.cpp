#include "MenuSlotConfig.h"
// ============================================================================
// MenuSlotConfig (S139) Implementation
// Addresses recovered from gta2.exe.map and analysis
// ============================================================================

/**
 * Конструктор
 * Адрес: 0x00452D10
 */
MenuSlotConfig::MenuSlotConfig() {
    // В оригинале: обнуление памяти или установка дефолтных значений
    this->slotId = 0xFF;       // Не назначен
    this->inputDevice = 0;     // Клавиатура по умолчанию
    this->teamId = 0;
    this->carClass = 0;
    this->flags = 0;
}

/**
 * Деструктор
 * Адрес: 0x00452D20
 */
MenuSlotConfig::~MenuSlotConfig() {
    // Пусто, так как нет динамической памяти
}

/**
 * Инициализация
 * Адрес: 0x00452D30
 */
void MenuSlotConfig::Init() {
    this->slotId = 0xFF;
    this->inputDevice = 0;
    this->teamId = 0;
    this->carClass = 0;
    this->flags = 0;
}

/**
 * Установка устройства ввода
 * Логика восстановления на основе вызовов в Menu::HandleInput
 */
void MenuSlotConfig::SetInputDevice(unsigned char device) {
    if (device <= 2) { // 0:KB, 1:Pad, 2:Net
        this->inputDevice = device;
        // Установка флага активности
        this->flags |= 0x01; 
    }
}

/**
 * Проверка активности
 */
bool MenuSlotConfig::IsActive() const {
    return (this->flags & 0x01) != 0;
}

/**
 * Сброс
 */
void MenuSlotConfig::Reset() {
    this->Init();
}
