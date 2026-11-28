#include "CarSystemManager.h"



CarSystemManager *gCarSystemManager;

CarSystemManager::CarSystemManager() {}
CarSystemManager::~CarSystemManager() {}
    // 0x00401C10


int CarSystemManager::ClampValues(void){
        return 0;
    }


    // 0x00401C40


int CarSystemManager::AddCarToSystem(void){
        return 0;
    }


    // 0x00401C60


int CarSystemManager::CarPool_Get(void){
        return 0;
    }


    // 0x00401C80


int CarSystemManager::PedPool_Get(void){
        return 0;
    }


    // 0x0040E590


// 0x0040E590 IDA/BN CarSystemManager::SetIndexDefautCarManager: Index=0. RE field-name impl.
void CarSystemManager::SetIndexDefautCarManager(void) {
    this->Index = 0;
}


    // 0x0040E5A0


int CarSystemManager::GetCarFromPool(void){
        return 0;
    }


    // 0x0040E670


// 0x0040E670 IDA/BN CarSystemManager::greater_than: return Index > (unsigned short)*a2. RE field-name impl.
bool CarSystemManager::greater_than(unsigned short* a2) {
    return this->Index > (int)*a2;
}


    // 0x0041E0F0


// 0x0041E0F0 IDA/BN CarSystemManager::less_than: return Index < (unsigned short)*a2. RE field-name impl.
bool CarSystemManager::less_than(unsigned short* a2) {
    return this->Index < (int)*a2;
}


    // 0x00420A10


int CarSystemManager::SetupCarLists(void){
        return 0;
    }


    // 0x00420C00


int CarSystemManager::UpdateFreeShopping(void){
        return 0;
    }


    // 0x00420CE0


int CarSystemManager::CanAddCar(void){
        return 0;
    }


    // 0x004212D0


int CarSystemManager::GetIndexedValue(void){
        return 0;
    }


    // 0x00421960


int CarSystemManager::GetDummyDriver(void){
        return 0;
    }


    // 0x00426E10


int CarSystemManager::SpawnCar(void){
        return 0;
    }


    // 0x00426E40


int CarSystemManager::SpawnCarAtPos(void){
        return 0;
    }


    // 0x00428EC0


int CarSystemManager::CreateCarWithTurret(void){
        return 0;
    }


    // 0x00428F70


int CarSystemManager::InitialiseCar(void){
        return 0;
    }


    // 0x00447CB0


int CarSystemManager::PrepareArray(void){
        return 0;
    }


    // 0x00447D30


// 0x00447D30 IDA/BN CarSystemManager::AdvanceIndex: if (++Index == 1000) Index = 0. RE field-name impl; keeps int signature.
int CarSystemManager::AdvanceIndex(void){
        if (++this->Index == 1000) {
            this->Index = 0;
        }
        return 0;
    }


    // 0x004C39F0


int CarSystemManager::CycleMode(void){
        return 0;
    }

void CarSystemManager::Update(void){}

// 0x0040F4C0 IDA/BN CarSystemManager::less_or_equal: return Index <= (unsigned short)*a2. RE field-name impl.
bool CarSystemManager::less_or_equal(short* a2) {
    return this->Index <= (int)(unsigned short)*a2;
}
