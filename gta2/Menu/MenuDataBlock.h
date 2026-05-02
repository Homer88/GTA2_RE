// ============================================================================
// Структура CMenuDataBlock (ранее S138)
// Размер: 4 байта
// Адрес в памяти: уточнить по дампу
// ============================================================================
#ifndef ___CMENUDATABLOCK__H__
#define ___CMENUDATABLOCK__H__



class MenuDataBlock {

public:
    char field_0; // смещение 0x0 - флаг состояния
    char field_1; // смещение 0x1
    char field_2; // смещение 0x2
    char field_3; // смещение 0x3

    // Конструктор: адрес 0x00061CE0
    MenuDataBlock();

    // Деструктор: адрес 0x00061CF0
    ~MenuDataBlock();

    // Загрузка данных: адрес 0x00061D00 (ранее sub_452D00)
    void Load();
};

#endif //___CMENUDATABLOCK__H__

