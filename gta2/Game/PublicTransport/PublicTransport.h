
#ifndef ___PublicTransport___H___
#define ___PublicTransport___H___


#include "Bus.h"

class PublicTransport {
public:
	bool       Status;

	PublicTransport();
	~PublicTransport();


// ==== импорт имён из gm ====
    // 2 функций
    // 0x004B0CF0: PublicTransport::FindVisibleBus
    void FindVisibleBus();
    // 0x004B0F20: PublicTransport::Update
    void Update();

    class Bus  BusMetrics;
    class Bus  BUS[10];
};
#endif // !1