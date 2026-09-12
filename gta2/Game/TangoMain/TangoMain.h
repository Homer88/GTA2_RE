
#ifndef __TANGOMAIN_H_
#define __TANGOMAIN_H_


class TangoMain{
    public:

    // 0x00450BC0
    int EndTango(void);
    // 0x00450CA0
    int Reset(void);
    // 0x00450CD0
    int UpdateTango(void);
    // 0x00450F10
    int RunAction(void);
    // 0x00451510
    int CanStartTango(void);
};

#endif // !__TANGOMAIN_H_