#ifndef ___CARPHYSICS___H_
#define ___CARPHYSICS___H_

// Статические характеристики машины, загружаемые из файла *.gci
// через CarEngines (CarEngines::CarInfo).
//
// Файловое представление GTA2 оригинала: Sony_2D_style_cars. В памяти
// игра хранит по одной такой записи на машину. Порядок полей и их
// типы получены из декомпилированного загрузчика (sub_41D230 пишет
// значения подряд, продвигая указатель) и реального файла nyc.gci:
//
//   model {model}                     - байт (1)
//   turbo {turbo}                     - байт (1)
//   value {value}                     - байт (1)
//   pad   {pad}                       - байт (1)
//   далее 17 f-параметров по 4 байта (float).
//
// Итого 4 + 17*4 = 72 байта на запись. Совпадает с new(72*NumberOfCars).

// Постоянная запись физики одной машины (бывш. S285, 72 байта).
struct CarPhysics
{
	char model;                 // 0x00 {model}                    номер модели
	char turbo;                 // 0x01 {turbo}                    тип турбонаддува
	char value;                 // 0x02 {value}                    ценность/очки машины
	char pad;                   // 0x03 {pad}                      выравнивание/резерв
	float mass;                 // 0x04 {mass}                     масса
	float front_drive_bias;     // 0x08 {front drive bias}         смещение тяги на передние колёса
	float front_mass_bias;      // 0x0C {front mass bias}          смещение массы вперёд
	float brake_friction;       // 0x10 {brake friction}           трение тормозов
	float turn_in;              // 0x14 {turn in}                  коэффициент входа в поворот
	float turn_ratio;           // 0x18 {turn ratio}               передаточное число руля
	float rear_end_stability;   // 0x1C {rear end stability}       устойчивость задней оси
	float handbrake_slide_value;// 0x20 {handbrake slide value}    значение скольжения ручника
	float thrust;               // 0x24 {thrust}                   тяга/ускорение
	float max_speed;            // 0x28 {max_speed}                максимальная скорость
	float anti_strength;        // 0x2C {anti strength}            сила противодействия (сноса)
	float skid_threshhold;      // 0x30 {skid threshhold}          порог заноса
	float gear1_multiplier;     // 0x34 {gear1 multiplier}         множитель 1-й передачи
	float gear2_multiplier;     // 0x38 {gear2 multiplier}         множитель 2-й передачи
	float gear3_multiplier;     // 0x3C {gear3 multiplier}         множитель 3-й передачи
	float gear2_speed;          // 0x40 {gear2 speed}              скорость 2-й передачи
	float gear3_speed;          // 0x44 {gear3 speed}              скорость 3-й передачи
};                              // 0x48 = 72 байта

// Менеджер записей физики машин (бывш. S286). Владеет массивом
// записей CarPhysics, распределяемым при загрузке .gci
// (new(72*NumberOfCars)), по одной на машину.
class CarPhysicsManager
{
public:
	CarPhysics *Entries;        // массив записей физики (72 байта каждая)
	int         NumberOfCars;   // число машин в массиве
};
#endif // !___CarPhysics___H_
