#include "Player/Player.h"
#include "../Ped/Ped.h"
#include "PedManager.h"


PedManager gPedManager;



PedManager::PedManager() {

    for (int i = 0; i < 199; i++) {
        this->ArrayPed[i].NextPed = &this->ArrayPed[i + 1];
    }
    this->ArrayPed[199].NextPed = NULL;
    this->FirstPed = &this->ArrayPed[0];
    this->NextPed = NULL; //возможно имя currentPed
    this->PedInUse = 0;


}
PedManager::~PedManager() {
    this->FirstPed = NULL;
    this->NextPed = NULL;

}

    // 0x00403890


Ped* PedManager::GetPed(void){
    Ped* pPed = this->FirstPed;
    this->FirstPed = pPed->NextPed;
    pPed->NextPed = this->NextPed;
    this->NextPed = pPed;
    pPed->CleanupAndUpdateOccupationCounts();

    return pPed;
    }


    // 0x00435530


Ped* PedManager::GetNextPed(void){
    return this->NextPed;
    }



    // 0x0043DB40


int PedManager::SpawnPedAtPosition(void){
        return 0;
    }


    // 0x00445960


int PedManager::UpdatePeds(void){
        return 0;
    }
