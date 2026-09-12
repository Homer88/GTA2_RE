
#ifndef __INPUT2_H_
#define __INPUT2_H_


class Input2{
    public:

    // 0x0044B9E0
    int S18_Des(void);
    // 0x0044BA60
    int GetDeviceState(void);
    // 0x0044BCF0
    int SetupJoystick(void);
    // 0x0044BED0
    int Init(void);
    // 0x0044BF30
    int LoadControlKeys(void);
    // 0x0044C070
    int ReadButton(void);


// ==== импорт имён из gm ====
    // 2 функций
    // 0x0044BC40: Input2::CreateKeyboard
    void CreateKeyboard();
    // 0x0044BF70: Input2::Initialise
    void Initialise();
};
#endif // !__INPUT2_H_