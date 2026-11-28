#include "Gangs.h"
#include "../Gang/Gang.h"
#include <windows.h>


Gangs *gGangs;

Gangs::Gangs() {

	//Gang* pGang = new Gang[10];

}

Gangs::~Gangs() {
}


Gang* Gangs::GetNextGang() {
	return NULL;
}
Gang* Gangs::GetFirstUsedGang(){
	return NULL;
}
// 0x0045DC70 IDA/BN Gangs::SetGang: return &ArrayGang[Gang]. RE field-name impl; C++ indexing uses RE Gang stride.
Gang* Gangs::SetGang(GANG gang) {
	return &this->ArrayGang[gang];
}
