
#ifndef __PLAYERDATA_H_
#define __PLAYERDATA_H_

#include "../PlayerSlotSlave/PlayerSlotSlave.h"

class PlayerData{
    public:

        void* PlayerName;
        PlayerSlotSlave PlayerSlotSave[8];



    // 0x00452200
    int ApplyMoneyCheatIfApplicable(void);
    // 0x004A87B0
    int Dtor(void);
    // 0x004A8820
    int FindFile_Plyslot(void);
    // 0x004A8910
    int LoadPlayerSlot(void);
    // 0x004A89E0
    int WriteFileNamePlayer(void);
    int WriteFileNamePlayer(char Slot);
    int WriteFileNamePlayer(wchar_t Slot);
    int WriteFileNamePlayer(wchar_t* NamePlayer);
    // 0x004A8A90
    int MarkSubSlotComplete(void);
    // 0x004A8B00
    int MarkAllSubSlotsComplete(void);
    // 0x004A8B60
    int ReadHiscores(void);
    // 0x004A8B80
    int SetDefaultHiscores(void);
    // 0x004A8CB0
    int LoadHiscores(void);
    // 0x004A8D80
    int SaveHiscores(void);
    // 0x004A8ED0
    int InitAllHiscores(void);
    // 0x004A8F90
    int RecordPlayerScore(void);
    // 0x004A9050
    int LoadScoreEntry(void);
    // 0x004A90A0
    int UpdateHiscores(void);


// ==== импорт имён из gm ====
    // 2 функций
    // 0x0049E240: PlayerData::ShowNumber
    void ShowNumber();
    // 0x004D6DCA: PlayerData::CreateEntry
    void CreateEntry();
};
#endif // !__PLAYERDATA_H_