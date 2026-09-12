
#ifndef __MEDICAL_H_
#define __MEDICAL_H_


class Medical{
    public:

    // 0x00473170
    int CreateCrew(void);
    // 0x00473320
    int UpdateVehicle(void);
    // 0x00473410
    int UpdatePassengers(void);


// ==== импорт имён из gm ====
    // 1 функций
    // 0x00472FB0: Medical::AddPassenger
    void AddPassenger();
};
#endif // !__MEDICAL_H_