
#ifndef __MIKE_H_
#define __MIKE_H_
#include "../BuildingModel/BuildingModel.h"

class Mike{

    public:
        // переменные 
        BuildingModel _BuildingModel[5];
        Mike();

    // 0x004741A0
    int DoMiKe_EM(void);
    // 0x00474530
    int ShowStats(void);
};
extern Mike* gMike;
#endif // !__MIKE_H_