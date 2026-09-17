#include "SpriteS2.h"
#include <cstddef>
SpriteS2* gSpriteS2;

    // 0x004BC950

SpriteS2::SpriteS2(){
    // Конструкторы GangInfo уже вызваны автоматически компилятором

  // Связываем элементы в односвязный список
    for (int i = 0; i < 5030; ++i) {
        this->ArrayGangInfo[i].NextGangInfo = &this->ArrayGangInfo[i + 1];
    }

    // Последний элемент — конец списка
    this->ArrayGangInfo[5030].NextGangInfo = NULL;

    // Указатель на голову списка
    this->FirstGangInfo = &this->ArrayGangInfo[0];
}
int SpriteS2::SpriteS2Dtor(void){
        return 0;
    }


    // 0x004BC9F0


int SpriteS2::SpriteS2Alloc(void){
        return 0;
    }


    // 0x004BCA10


int SpriteS2::Free(void){
        return 0;
    }
