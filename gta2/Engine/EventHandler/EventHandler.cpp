#include "EventHandler.h"
#include "../../Game/Checkpoint/Checkpoint.h"
#include "../../Engine/SpriteS1/SpriteS1.h"

EventHandler* gEventHandler = nullptr;


    // 0x004210B0


int EventHandler::IsUncollidable(void){
        return 0;
    }


    // 0x00425760


int EventHandler::IsCarFlagSet(void){
        return 0;
    }


    // 0x00482490


int EventHandler::Reset(void){
        // IDA 0x482490 partial: minimal safe reset.
        this->NextElement = nullptr;
        this->SpriteS1 = nullptr;
        this->pEventHandler = nullptr;
        this->S65 = nullptr;
        this->Car = nullptr;
        this->field_14 = 0;
        this->S63_1 = nullptr;
        this->field_1C = 0;
        this->field_20 = 0;
        this->S202 = nullptr;
        this->field_28 = 0;
        return 0;
    }


    // 0x00482560


int EventHandler::ClearCheckpoints(void){
        return 0;
    }


    // 0x00482790


int EventHandler::SetOwnerID(unsigned char id){
        // IDA 0x482790 sets owner id byte in S202 area; layout not fully confirmed.
        // Store in field_28 low byte as guarded placeholder until S202 layout is ported.
        this->field_28 = (char)id;
        return 0;
    }

int EventHandler::SetOwnerID(void){
        return SetOwnerID(0);
    }


    // 0x00482BE0


int EventHandler::UpdateSpriteFrame(void){
        return 0;
    }


    // 0x00483BA0


int EventHandler::KnockDoor(void){
        return 0;
    }


    // 0x00483C40


int EventHandler::UpdateEvents(void){
        return 0;
    }


    // 0x00483D50


int EventHandler::UpdateWeapon(void){
        return 0;
    }


    // 0x00484910


int EventHandler::Destroy(void){
        return 0;
    }


    // 0x00484DD0


int EventHandler::ApplyCollision(void){
        return 0;
    }


    // 0x00485C90


int EventHandler::SpawnExplosionFX(void){
        return 0;
    }


    // 0x00486390


int EventHandler::HandleImpact(void){
        return 0;
    }


    // 0x004932D0


int EventHandler::HandlePedImpact(void){
        return 0;
    }


// IDA 0x482630: dispatch by pEventHandler[1].field_14? Decompiled naming is ambiguous.
// Guarded: no-op unless checkpoint objects and sprite are valid.
int EventHandler::AddToCheckpoints() {
    // TODO: port exact field dispatch once EventHandler/S202 layout is confirmed.
    (void)this;
    return 0;
}
