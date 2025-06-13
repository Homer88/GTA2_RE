#include "Global.h"
#include "AudioManager.h"

AudioManager gAudioManager;


int AudioManager::InitArray() {
	
	int v3;

	for (int i = 0; i < this->count; ++i){

		v3 = i + 16 * this->filder_0x98;
		//this->gap146[v3 + 3158] = v1;
	}
	//this->gap146[result + 3190] = 0;


	return 0;
}

void AudioManager::DefauntParam() {
	//FIXME
}