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
	int sub_410660();
	int sub_410530(int* pAudioObject);
	int sub_410540(int SampleRate);
	int sub_410520();

	DMAudio() {};
	~DMAudio() {};

};

extern DMAudio gDMAudio;
#endif // !__DMAudio_H_

