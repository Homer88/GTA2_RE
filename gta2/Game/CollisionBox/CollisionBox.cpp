#include "CollisionBox.h"
#include "../../Engine/EventHandler/EventHandler.h"
#include "../../Engine/SpriteS1/SpriteS1.h"
#include <new>

CollisionBox* gCollisionBox = nullptr;


    // 0x00420FF0


int CollisionBox::GetOwnerID(void){
        return 0;
    }


    // 0x00421060


int CollisionBox::IsSpecialType(void){
        // IDA 0x482970+? used by sub_484E00 to optionally update weapon. Keep safe false.
        return 0;
    }


    // 0x00421080


int CollisionBox::IsUsable(void){
        return 0;
    }


    // 0x004340A0


int CollisionBox::GetFlag(void){
        return 0;
    }


    // 0x004825A0


int CollisionBox::SyncCarPosition(void){
        return 0;
    }


    // 0x004825C0


int CollisionBox::HandleExplosion(void){
        return 0;
    }


    // 0x00482630


int CollisionBox::AddToCheckpoints(void){
        return 0;
    }


    // 0x004826A0


int CollisionBox::RemoveFromCheckpoints(void){
        return 0;
    }


    // 0x004827B0


int CollisionBox::RequestRemoval(void){
        return 0;
    }


    // 0x00482970


int CollisionBox::GetS63(void){
        return 0;
    }


    // 0x00482980


int CollisionBox::SpriteS1SetLinks(void){
        return 0;
    }


    // 0x00482ED0


int CollisionBox::UpdateCarDoor(void){
        return 0;
    }


    // 0x00482F60


int CollisionBox::Deactivate(void){
        return 0;
    }


    // 0x00483C50


int CollisionBox::SetActive(void){
        return 0;
    }


    // 0x00483CC0


int CollisionBox::GetTileStyle(void){
        return 0;
    }


    // 0x00483EA0


int CollisionBox::FreeCollisionBox(void){
        return 0;
    }


    // 0x00484740


int CollisionBox::AttemptEnterCar(void){
        return 0;
    }


    // 0x00484760


int CollisionBox::Cleanup(void){
        return 0;
    }


    // 0x00484880


int CollisionBox::CreateEvent(void){
        return 0;
    }


    // 0x00485FD0


int CollisionBox::UpdateAnimTimer(void){
        return 0;
    }


    // 0x00486060


int CollisionBox::UpdateAnimation(void){
        return 0;
    }


    // 0x00487D70


int CollisionBox::UpdateByType(void){
        return 0;
    }


    // 0x00487E80


int CollisionBox::UpdateObject(void){
        return 0;
    }


// Guarded debug alloc: real pool has 3825 inline EventHandlers. We allocate on demand for GTA2_SPAWN_MOBJ=1.
EventHandler* CollisionBox::CollisionBoxAllocHandler() {
    // IDA 0x4829A0
    auto* eh = new (std::nothrow) EventHandler();
    if (!eh) return nullptr;
    eh->Reset();
    eh->NextElement = pS63;
    pS63 = eh;
    return eh;
}

EventHandler* CollisionBox::CollisionBoxAllocHandlerClear() {
    // IDA 0x4829C0
    auto* eh = new (std::nothrow) EventHandler();
    if (!eh) return nullptr;
    eh->Reset();
    eh->NextElement = nullptr;
    return eh;
}

EventHandler* CollisionBox::InitFromSpawn(EventHandler* eh, void* nodeId, int x, int y, int z, void* rot) {
    // IDA 0x483990 - requires PathNode node/SpriteS1. Guarded: only store basic fields.
    if (!eh) return nullptr;
    eh->S63_1 = nodeId;
    (void)x; (void)y; (void)z; (void)rot;
    return eh;
}

int CollisionBox::CollisionBoxDeleteHandler(EventHandler* eh) {
    // IDA 0x484D60 simplified: unlink from pS63 list.
    if (!eh) return 0;
    EventHandler* prev = nullptr;
    EventHandler* cur = pS63;
    while (cur) {
        if (cur == eh) {
            if (prev) prev->NextElement = cur->NextElement;
            else pS63 = cur->NextElement;
            cur->Reset();
            delete cur;
            return 1;
        }
        prev = cur;
        cur = cur->NextElement;
    }
    eh->Reset();
    delete eh;
    return 1;
}

EventHandler* CollisionBox::ReleaseHandler(EventHandler* eh) {
    if (!eh) return nullptr;
    eh->Reset();
    eh->NextElement = FirstElement;
    FirstElement = eh;
    return eh;
}
