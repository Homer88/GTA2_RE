#ifndef __MENU_SLOT_CONFIGURE_H_
#define __MENU_SLOT_CONFIGURE_H_

/**
 * @brief Структура конфигурации слота меню (ранее S139)
 * 
 * Размер: 8 байт (0x08)
 * Адрес в оригинале: Используется внутри структуры Menu
 * 
 * Назначение: Хранит расширенную конфигурацию слота игрока,
 * включая настройки управления и состояние готовности.
 */
class  MenuSlotConfig {
public:
    // Смещение 0x00
    unsigned char slotId;           // ID слота (0-7)
    
    // Смещение 0x01
    unsigned char inputDevice;      // Устройство ввода: 0 - KB, 1 - Gamepad, 2 - Network
    
    // Смещение 0x02
    unsigned char teamId;           // ID команды (для мультиплеера)
    
    // Смещение 0x03
    unsigned char carClass;         // Предпочитаемый класс автомобиля
    
    // Смещение 0x04
    unsigned char flags;           // Флаги состояния (битовая маска)
    
    // Смещение 0x08 (конец, но размер может быть выровнен в массивах)

    // Статический размер структуры
    static constexpr size_t Size = 0x08;

    /**
     * @brief Конструктор
     * Адрес: 0x00452D10 (предположительно, рядом с S138)
     */
    MenuSlotConfig();

    /**
     * @brief Деструктор
     * Адрес: 0x00452D20
     */
    ~MenuSlotConfig();

    /**
     * @brief Инициализация значениями по умолчанию
     * Адрес: 0x00452D30
     */
    void Init();

    /**
     * @brief Установка устройства ввода
     * @param device Тип устройства
     */
    void SetInputDevice(unsigned char device);

    /**
     * @brief Проверка флага активности
     * @return true если слот активен
     */
    bool IsActive() const;

    /**
     * @brief Сброс конфигурации
     */
    void Reset();
};

#endif // !__MENU_SLOT_CONFIGURE_H_
