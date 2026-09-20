#include "PlayerSlotSlave.h"
#include <cstddef>

PlayerSlotSlave::PlayerSlotSlave(){

	this->Value = 0;
	this->ActiveArenaSlot = 0;
	//this->PlayerName = (wchar_t)NULL;
}

unsigned int PlayerSlotSlave::GetValue() {

	return this->Value;
}

void   PlayerSlotSlave::SetValue(unsigned int Value) {
	this->Value = Value;
}

void   PlayerSlotSlave::SetMultiPlayer(unsigned int Value) {
	this->Value = Value;
}

unsigned int PlayerSlotSlave::GetMultiPlayer() {
	return this->Value ;
}