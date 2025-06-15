#include "Global.h"
#include "HUD.h"

HUD gHUD;
void HUD::LoadSpeedText() {
	this->SpeedText = gRegistry.SetTextConfig("text_speed", 3);
}
