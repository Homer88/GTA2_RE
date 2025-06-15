#include "Global.h"
#include "Game.h"
Game gGame;

Game::Game(){

}

Game::~Game(){
    
}



void* Game::InitPlayerOrTimer() {
   // if (this->PlayerMain == NULL) {

    //}
    InitTimer();
    if (gHUD.Status == NULL) {
        gHUD.LoadSpeedText();

    }
    return 0;
}