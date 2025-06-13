#include "Global.h"
#include "DMAudio.h"


DMAudio	gDMAudio;

void DMAudio::InitAudioManager() {

	// надо дебужить файл звуковой библиотеки
	/*SoundCard* result; // eax

	result = gSoundCard;
	if (gSoundCard)
		return (SoundCard*)AIL_digital_handle_release(gSoundCard);
	return result;*/
}
void DMAudio::InitAudioManager3D(){

	gAudioManager.filder_0x98 = 1;
	gAudioManager.InitArray();
	gAudioManager.filder_0x98 = 0;
	gAudioManager.InitArray();
	gAudioManager.DefauntParam();
	gAudioManager.filder_0x1450 = 0;
	///return gSoundCard && AIL_digital_handle_reacquire(gSoundCard)




}

void DMAudio::SetCDVol(char CDvol) {
	this->_CDvol = CDvol;
}

void DMAudio::SetSFXVol(char SFXVol) {
	this->_SFXVol = SFXVol;
}
void DMAudio::Init3DSound(int Vol3D) {
   /* char v2; // al
    char v4; // cl

    if (!(_BYTE)gAudioManager)
        return 0;
    if (pSound3DConfigure == *((_BYTE*)&gAudioManager + 29))
        return 1;
    if (!pSound3DConfigure)
    {
        if (SoundCard::ReinitializeAudioSystem((SoundCard*)&gSoundCard))
        {
            *((_BYTE*)&gAudioManager + 29) = Sound3D_Off;
            *((_BYTE*)&gAudioManager + 16) = 16;
            return 1;
        }
        SoundCard::Initialize3DAudioWithDirectSound((SoundCard*)&gSoundCard, (bool*)&gAudioManager + 28);
        v4 = *((_BYTE*)&gAudioManager + 28);
        *((_BYTE*)&gAudioManager + 29) = 1;
        *((_BYTE*)&gAudioManager + 16) = v4;
        return 0;
    }
    if (SoundCard::Initialize3DAudioWithDirectSound((SoundCard*)&gSoundCard, (bool*)&gAudioManager + 28))
    {
        v2 = *((_BYTE*)&gAudioManager + 28);
        *((_BYTE*)&gAudioManager + 29) = 1;
        *((_BYTE*)&gAudioManager + 16) = v2;
        return 1;
    }
    else
    {
        SoundCard::ReinitializeAudioSystem((SoundCard*)&gSoundCard);
        *((_BYTE*)&gAudioManager + 29) = 0;
        *((_BYTE*)&gAudioManager + 16) = 16;
        return 0;
    }*/
}


bool DMAudio::Get3DSound() {
    ///FIXME
    if (gAudioManager.Status)
        return gAudioManager.Sound3D;
    return false;
}