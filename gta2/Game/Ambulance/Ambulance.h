
#ifndef ___Ambulance__H__
#define ___Ambulance__H__

class Ambulance {
public:
	bool Status;
	Ambulance() {};
	~Ambulance() {};

// ==== импорт имён из gm ====
    // 1 функций
    // 0x00472F60: Ambulance::FindFreeSlot
    void FindFreeSlot();
};
#endif // !___Ambulance__H__