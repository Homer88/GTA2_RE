#ifndef __MATCH_H_
#define __MATCH_H_

// Математика игры GTA2.
//
// Внутренние координаты игра хранит в собственном формате Float10
// (название из IDA-дампа). Это знаковое целое, у которого 14 младших бит -
// дробная часть: разрешение 1/16384 «мировой единицы» (фиксированная точка Q14).
// Декодирование в дампе: Float10::EncodedFloatToRegularFloat = raw * 0.000061035156
// (gta2.exe.c:2455); кодирование = округление (value * 16384.0) (функция
// sub_4D6DFC = стандартное double->__int64, см. Sinus gta2.exe.c:12515).
//
// Зачем авторы это сделали: координаты/скорости складываются и сравниваются
// целочисленной арифметикой (быстро и без ошибок округления на длинных дистанциях),
// а в float/двойной они переводятся только там, где нужны синусы, корни и т.п.
// Поэтому у Float10 нет операций умножения/деления другу на друга - в игре такие
// вычисления делаются через временный float.

// Углы в игре отсчитываются от 0 до 1440 (вся окружность - 1440 «градусов»).
// Перевод в радианы (множитель из дампа при вызовах cos/sin, напр. gta2.exe.c:12628):
//   rad = angle * 2*PI / 1440 = angle * PI * 0.001388888888888889

class Float10 {
public:
	Float10() : m_Val(0) {}
	explicit Float10(long raw) : m_Val(raw) {}

	// Кодирование значения в Float10: округление value*16384 до ближайшего целого
	// (как sub_4D6DFC - обычный double->int).
	static Float10 FromFloat(double value) { return Float10((long)(value * 16384.0)); }

	// То же, но исходное значение уже целое (например углы/пиксели карты):
	// raw = value * 16384.
	static Float10 FromInt(long value) { return Float10(value * 16384L); }

	// Декодирование: value = raw * 0.000061035156 (= 1/16384 = 2^-14).
	double ToFloat() const { return (double)m_Val * 0.000061035156; }

	// Декодирование в целое: округление raw/16384 до ближайшего (как sub_4D6DFC).
	// Целочисленное (без плавающей точки, поэтому не зависит от приближённой
	// константы декодера): для положительных добавляем половину шага 16384/2.
	long ToInt() const {
		long h = 16384 / 2;
		return (m_Val + (m_Val >= 0 ? h : -h)) / 16384;
	}

	long Raw() const { return m_Val; }
	void SetRaw(long raw) { m_Val = raw; }

	// Сложение/вычитание/сравнение - как у целых (в игре координаты складываются
	// прямо как int-ы, без промежуточного float).
	Float10& operator+=(Float10 o) { m_Val += o.m_Val; return *this; }
	Float10& operator-=(Float10 o) { m_Val -= o.m_Val; return *this; }

private:
	long m_Val; // значение в Q14: 14 младших бит - дробная часть
};

inline Float10 operator+(Float10 a, Float10 b) { return Float10(a.Raw() + b.Raw()); }
inline Float10 operator-(Float10 a, Float10 b) { return Float10(a.Raw() - b.Raw()); }
inline bool operator==(Float10 a, Float10 b)  { return a.Raw() == b.Raw(); }
inline bool operator!=(Float10 a, Float10 b)  { return a.Raw() != b.Raw(); }
inline bool operator<(Float10 a, Float10 b)   { return a.Raw() < b.Raw(); }
inline bool operator>(Float10 a, Float10 b)   { return a.Raw() > b.Raw(); }

// Перевод игрового угла окружности (0..1440) в радианы.
inline double Angle1440ToRad(long angle)
{
	return (double)angle * 3.141592654 * 0.001388888888888889;
}

#endif // !__MATCH_H_