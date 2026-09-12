
#ifndef __CARPAIR_H_
#define __CARPAIR_H_


class CarPair{
    public:

    // 0x0040F400 Ped * __thiscall
    // (new_class) старый: CarsPrefabs::GetDriver -> GetPed
    void* GetPed();

    // 0x0040F410 int __thiscall
    // (new_class) старый: CarsPrefabs::GetOtherCar -> GetOtherCar
    int GetOtherCar(int arg0,int arg1);

    // 0x0040F430 void __thiscall
    // (new_class) старый: CarsPrefabs::LinkCars -> LinkCars
    void LinkCars(void *arg0,int arg1);

    // 0x0040F450 void __thiscall
    // (new_class) старый: CarsPrefabs::AttachPlayers -> ProcessBothCars
    void ProcessBothCars();

    // 0x0040F470 void __thiscall
    // (new_class) старый: CarsPrefabs::RemovePlayers -> ReleaseBothCars
    void ReleaseBothCars();

    // 0x0040FB20 uint __thiscall
    // (new_class) старый: Car::UpdateLinkedCar -> Validate
    unsigned int Validate();

};
#endif // !__CARPAIR_H_
