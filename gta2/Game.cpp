#include "Global.h"
#include "Game.h"

Game::Game(){

}

Game::~Game() {
    Player Player1;
    gSkilPolice = this->pSkipPolice;
    gDMAudio.~DMAudio();
    int index = 0;
    if (this->MaxIdx) {
       /* Player1 = this->pPlayer1;
        do {
            if (Player1.Status) {
                Player1.~Player();
            }
            *Player1 = NULL;
            ++index;
            ++Player1;
        } while (index < this->MaxIdx);*/
    }

    gGeneral.~General();
    gText.~Text();
    //gText = NULL;
    gStyle.~Style();
    gMapRelatedStruct.~MapRelatedStruct();
    // gS17.~S17();
    gDisplay.~Display();
    if (gPedManager.Status) {
        gPedManager.~PedManager();
    }
    if (gCarSystemManager.Status) {
        gCarSystemManager.~CarSystemManager();
    }
    // gS25.~S25();
    if (gMissionManager.Status) {
        gMissionManager.~MissionManager();
    }

    //if (gS33.Status) {
     //   gS33.~S33();
   // }
   // if (gS57.Status)
    //    gS57.~S57();
    if (gObject.Status)
        gObject.~Object();
    if (gCharacter.Status)
        gCharacter.~Character();
   // free(gMike);
    //gMike = 0;
    if (gTiming.Status)
        gTiming.~Timing();
    
    if (gSpriteEntry.Status)
        gSpriteEntry.~SpriteEntry();
    if (gCollide.Status)
        gCollide.~Collide();

        //if (gS68.Status)
      //  S68::S68_Des(gS68, 1);
    if (gPublicTransport.Status)
        gPublicTransport.~PublicTransport();
    if (gTaxi.Status)
        gTaxi.~Taxi();
    if (gTileAnim.Status)
        gTileAnim.~TileAnim();
    if (gTurrel.Status)
        gTurrel.~Turrel();
    if (gDoor.Status)
        gDoor.~Door();
   
    if (gAmbulance.Status)
        gAmbulance.~Ambulance();
    if (gHUD.Status)
        gHUD.~HUD();
   
    if (gTextureManager.Status)
        gTextureManager.~TextureManager();
   
    if (gTrafficLigthStruct.Status)
        gTrafficLigthStruct.~TrafficLigthStruct();
   
   // free(gJuncIds);
    //gJuncIds = 0;
    //if (gS93)
     //   S93::~S93();
    //if (gS95)
     //   S95::S95_des(gS95, 1);
    
    if (gCarEngines.Status)
        gCarEngines.~CarEngines();
    if (gParticles.Status)
        gParticles.~Particles();
   /* if (gS100)
        S100::S100_des(gS100, 1);
    gS100 = 0;
    if (gS102)
        S102::S102_des(gS102, 1);
    gS102 = 0;
    if (gS103)
        S103::S103_des(gS103, 1);
    gS103 = 0;
    if (gS105)
        S105::S105_des(gS105, 1);
    gS105 = 0;
    free(gS107);
    gS107 = 0;
    if (gS109)
        S109::S109_des(gS109, 1);*/
    if (gPolice.Status)
        gPolice.~Police();
    //if (gS115)
      //  S115::S115_des(gS115, 1);
   // if (gGangs.Status)
     //   gGangs.~Gangs();
   
    //if (gS119)
      //  S119::S119_des(gS119, 1);
    //gS119 = 0;
    //if (gS121)
      //  S121::S121_des(gS121, 1);
    
    if (!gExplodingOn)
    {
       // if (gS123)
         //   S123::S123_des(gS123, 1);
        //gS123 = 0;
    }
   // if (gS127)
     //   S127::S127_des(gS127, 1);
    //gS127 = 0;
    //if (gS129)
      //  S129::S129_des(gS129, 1);
         if (gCameraOrPhysics.Status)
        gCameraOrPhysics.~CameraOrPhysics();
    
    if (gFileMgr.Status)
    {
        gFileMgr.~FileMgr();
        
    }
    this->CurentPlayer = 0;
    //this->pPlayer = 0;

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