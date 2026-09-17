#include "SpriteMain.h"
#include "../SpriteS1/SpriteS1.h"
#include "../SpriteS2/SpriteS2.h"
#include "../SpriteS3/SpriteS3.h"
#include "../SpriteS4/SpriteS4.h"
#include <cstddef>
SpriteMain* gSpriteMain;

    // 0x00420600

SpriteMain::SpriteMain() {
    if (gSpriteS1 == NULL) {
        gSpriteS1 = new SpriteS1;
    }
    if (gSpriteS2 == NULL) {
        gSpriteS2 = new SpriteS2;
    }
    if (gSpriteS3==NULL){ 
        gSpriteS3 = new SpriteS3;
    }
    if (gSpriteS4 == NULL) {
        gSpriteS4 = new SpriteS4;
        
    }
    this->ptr=NULL;
    this->W=0;
    this->H = 0;
}



int SpriteMain::SetPosition(void){
        return 0;
    }


void SpriteMain::SetPosition(int x, int y, int z) {

    this->x = x;
    this->y = y;
    this->z = z;
}
    // 0x00420690


int SpriteMain::SetRotation(void){
        return 0;
    }


    // 0x004206C0


int SpriteMain::SetFrame(void){
        return 0;
    }


    // 0x004206F0


int SpriteMain::SetType(void){
        return 0;
    }


    // 0x00420710


int SpriteMain::SetCar(void){
        return 0;
    }


    // 0x00483E50


int SpriteMain::SetObject(void){
        return 0;
    }


    // 0x004B99F0


int SpriteMain::ResetState(void){
        return 0;
    }


    // 0x004BAB10


int SpriteMain::SetSize(void){
        return 0;
    }


    // 0x004BCB40


int SpriteMain::DrawArrow(void){
        return 0;
    }


    // 0x004BD290


int SpriteMain::Draw(void){
        return 0;
    }


    // 0x004BDDB0


int SpriteMain::CopySpriteData(void){
        return 0;
    }


    // 0x004BDEF0


int SpriteMain::DrawSprite(void){
        return 0;
    }
