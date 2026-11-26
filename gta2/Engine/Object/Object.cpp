#include "Object.h"
#include "../../Game/CollisionBox/CollisionBox.h"
#include "../../Engine/EventHandler/EventHandler.h"
#include "../../Game/PathNode/PathNode.h"
#include <cstdio>
#include <cstdlib>

Object* gObject;
    // 0x004828F0


int Object::GetSelectionData(void){
        return 0;
    }


    // 0x00483D90


int Object::CollectGameObjectData(void){
        return 0;
    }


    // 0x00484AD0


int Object::SetCollisionIndex(void){
        return 0;
    }


    // 0x00484CF0


int Object::ExitInGameMenu(void){
        return 0;
    }


    // 0x00485540


int Object::SpawnPedObject(void){
        return 0;
    }


    // 0x00485640


int Object::SpawnTrains(void){
        return 0;
    }


    // 0x00485E40


int Object::SpawnPickupObjects(void){
        return 0;
    }


    // 0x00485ED0


int Object::CreateInitialObjects(void){
        return 0;
    }


    // 0x00487ED0


int Object::RemoveDeadObjects(void){
        return 0;
    }


int Object::SpawnObject(int a, int x, int y, int z) {
    // Legacy 4-arg form used by some callsites; rot unknown. Keep debug-visible, no real pool.
    return SpawnObject(a, x, y, z, 0);
}

static int gMobjRealSpawnEnabled() {
    const char* v = getenv("GTA2_SPAWN_MOBJ");
    return v && v[0] == '1';
}

int Object::SpawnObject(int Type, int x, int y, int z, short rot) {
    // IDA 0x4852E0: EventHandler* Object::SpawnObject(type,x,y,z,rot) -> sub_484E00 + AddToCheckpoints.
    // Real pool is not fully ported. For MOBJ debug, attempt a very narrow guarded "real-lite" alloc
    // only when GTA2_SPAWN_MOBJ=1 and required globals exist; otherwise keep debug record.
    int debugId = 0;
    if (m_debugSpawnedCount < kMaxDebugSpawnedObjects) {
        DebugSpawnedObject& o = m_debugSpawned[m_debugSpawnedCount];
        o.type = Type; o.x = x; o.y = y; o.z = z; o.rot = rot; o.id = m_debugSpawnedCount + 1;
        ++m_debugSpawnedCount;
        debugId = o.id;
    }

    EventHandler* eh = nullptr;
    if (gMobjRealSpawnEnabled() && gCollisionBox && gPathNode) {
        void* node = gPathNode->GetNode(Type);
        if (node) {
            int nodeState92 = *(int*)((unsigned char*)node + 92);
            // Minimal safe case: ordinary node, no special car/turret/pool dependencies.
            // IDA sub_484E00 handles many cases; we only allow simple alloc+init+AddToCheckpoints.
            if (nodeState92 != 2 && nodeState92 != 3) {
                eh = gCollisionBox->CollisionBoxAllocHandlerClear();
                if (eh) {
                    eh->field_20 = 2;
                    gCollisionBox->InitFromSpawn(eh, (void*)(intptr_t)Type, x, y, z, (void*)(intptr_t)(unsigned short)rot);
                    eh->S63_1 = (void*)(intptr_t)Type;
                    // AddToCheckpoints is guarded stub until checkpoint layout is confirmed.
                    eh->AddToCheckpoints();
                }
            }
        }
    }

    if (getenv("GTA2_MOBJ_TRACE")) {
        FILE* tf = fopen("gta2_mobj_trace.log", "a");
        if (tf) {
            fprintf(tf, "ObjectSpawn, type=%d x=%d y=%d z=%d rot16=%u (0x%04X) id=%d eh=%p\n",
                Type, x, y, z, (unsigned)(unsigned short)rot, (unsigned)(unsigned short)rot, debugId, (void*)eh);
            fclose(tf);
        }
    }
    return debugId;
}
void Object::Object_Update(void){}
