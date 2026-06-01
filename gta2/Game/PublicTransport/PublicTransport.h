#ifndef ___PublicTransport___H___
#define ___PublicTransport___H___


#include "Bus.h"

class PublicTransport {
public:
	bool       Status;
	class Bus  BUS[10];
	class Bus  BusMetrics;

	PublicTransport() {};
	~PublicTransport() {};
};

#endif // !1