#ifndef __DMAudio_H_
#define __DMAudio_H_

class DMAudio {
public:
	char _CDvol;
	char _SFXVol;
	void InitAudioManager();
	void InitAudioManager3D();
	void SetCDVol(char CDvol);
	void SetSFXVol(char SFXVol);
	void Init3DSound(int Vol3D);
	bool Get3DSound();

};
#endif // !__DMAudio_H_

