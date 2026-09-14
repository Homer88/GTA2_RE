#include "Random.h"
int gSeed;
Random *gRandom;

    // 0x00472C00


unsigned char Random::GetZoneIndex(int arg0){
        return 0;
    }


    // 0x00472E90


int Random::PauseGame(void){
        return 0;
    }




int  Random::Restart() {

    return this->SetSeed(1);
}
int  Random::SetSeed(int seed) {
    gSeed = seed;
    return seed;
}