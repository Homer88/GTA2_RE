#include "Global.h"
#include "HUD.h"


void HUD::LoadSpeedText() {
	this->SpeedText = gRegistry.SetTextConfig("text_speed", 3);
}
