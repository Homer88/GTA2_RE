#include "CarInfo.h"

namespace gta2 {

// ---------------------------------------------------------------------------
// Разбор пакета CARI: последовательность записей переменной длины.
// Формат (filerecords.pas:27, clsSTY.cls:154, Unit1.pas:628):
//   [14 байт фикс] + remap[num_remaps] + [1 байт num_doors] + door[num_doors]*2
// ---------------------------------------------------------------------------
bool CarInfoList::Parse(const unsigned char* data, size_t size)
{
	m_cars.clear();
	m_ok = false;

	size_t pos = 0;
	while (pos + 14 <= size) {
		CarInfo c;
		c.model           = data[pos + 0];
		c.sprite          = data[pos + 1];
		c.w               = data[pos + 2];
		c.h               = data[pos + 3];
		c.num_remaps      = data[pos + 4];
		c.passengers      = data[pos + 5];
		c.wreck           = data[pos + 6];
		c.rating          = data[pos + 7];
		c.front_wheel_offset  = static_cast<signed char>(data[pos + 8]);
		c.rear_wheel_offset   = static_cast<signed char>(data[pos + 9]);
		c.front_window_offset = static_cast<signed char>(data[pos + 10]);
		c.rear_window_offset  = static_cast<signed char>(data[pos + 11]);
		c.info_flags      = data[pos + 12];
		c.info_flags_2    = data[pos + 13];
		pos += 14;

		// Перекраски: num_remaps байт.
		if (pos + c.num_remaps > size) { m_cars.clear(); return false; }
		for (int i = 0; i < c.num_remaps; i++)
			c.remap.push_back(data[pos + i]);
		pos += c.num_remaps;

		// Число дверей (1 байт).
		if (pos + 1 > size) { m_cars.clear(); return false; }
		c.num_doors = data[pos];
		pos += 1;

		// Двери: по 2 байта rx, ry.
		if (pos + (size_t)c.num_doors * 2 > size) { m_cars.clear(); return false; }
		for (int i = 0; i < c.num_doors; i++) {
			CarDoor d;
			d.rx = static_cast<signed char>(data[pos + (size_t)i * 2 + 0]);
			d.ry = static_cast<signed char>(data[pos + (size_t)i * 2 + 1]);
			c.door.push_back(d);
		}
		pos += (size_t)c.num_doors * 2;

		m_cars.push_back(c);
	}

	m_ok = true;
	return true;
}

std::vector<unsigned char> CarInfoList::Save() const
{
	std::vector<unsigned char> out;
	for (size_t i = 0; i < m_cars.size(); i++) {
		const CarInfo& c = m_cars[i];
		out.push_back(c.model);
		out.push_back(c.sprite);
		out.push_back(c.w);
		out.push_back(c.h);
		out.push_back(c.num_remaps);
		out.push_back(c.passengers);
		out.push_back(c.wreck);
		out.push_back(c.rating);
		out.push_back(static_cast<unsigned char>(c.front_wheel_offset));
		out.push_back(static_cast<unsigned char>(c.rear_wheel_offset));
		out.push_back(static_cast<unsigned char>(c.front_window_offset));
		out.push_back(static_cast<unsigned char>(c.rear_window_offset));
		out.push_back(c.info_flags);
		out.push_back(c.info_flags_2);

		for (size_t r = 0; r < c.remap.size(); r++)
			out.push_back(c.remap[r]);
		out.push_back(c.num_doors);
		for (size_t d = 0; d < c.door.size(); d++) {
			out.push_back(static_cast<unsigned char>(c.door[d].rx));
			out.push_back(static_cast<unsigned char>(c.door[d].ry));
		}
	}
	return out;
}

} // namespace gta2
