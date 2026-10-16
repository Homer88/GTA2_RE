
#ifndef __MAP_GM_H_
#define __MAP_GM_H_

#include <string.h>

// Êëàññ MapGm (ìîäóëü êàðòû) — âîññòàíîâëåí ïî äàìïó GTA2.exe.
// Ñòðóêòóðà ñîîòâåòñòâóåò gta2.exe.h (dump\Ghidra, ñòð. 56854).
// Ðàçìåòêà ìàññèâîâ 0x490..0x4b4 óòî÷íåíà ïî äèçàññåìáëåðó ResetSettings
// (asm 0045e630): PlayerID (4*short) + PlayerArena (10*int) +
// string_Arr0x16 (6 * 16 wchar) — íå ïåðåñåêàþòñÿ.
//
// Â îòëè÷èå îò àâòîìàòè÷åñêîé ðàçìåòêè Ghidra, ãäå ñìåæíûå áàéòû
// íàçâàíû field_XXX, çäåñü îáúåäèíåíû òîëüêî ïîëÿ, ðåàëüíî èñïîëüçóåìûå
// ôóíêöèÿìè äàìïà; îñòàëüíûå áàéòû çàíèìàþò íåèñïîëüçóåìûå gap-ìàññèâû.

typedef enum TYPE_GAME {
	FRAG_GAME = 1,
	POINT_GAME = 2,
	TAG_GAME = 3
} TYPE_GAME;

typedef enum STATUS_ROW {
	
	 p0 = 0x0,
	 p1 = 0x1,
	 p2 = 0x2,
	 p3 = 0x3,
	 p4 = 0x4,
	 VehiclesHijacked = 0x5,
	 CiviliansRunDown = 0x6,
	 CiviliansMurdered = 0x7,
	 LawmenKilled = 0x8,
	 GangMembersKilled = 0x9,
  
}STATUS_ROW;
struct StatusLastGame {
	unsigned int value[10];
	/* unsigned int p0;
	unsigned int p1;
	unsigned int p2;
	unsigned int p3;
	unsigned int p4;
	unsigned int vehicles_hijacked;
	unsigned int civilians_run_down;
	unsigned int civilians_murdered;
	unsigned int lawmen_killed;
	unsigned int gang_members_killed;
  */
};
struct KillPlayer {   /* ñòðîêà ìàòðèöû óáèéñòâ: killPlayer[killer].KillPlayerN = ñêîëüêî ðàç killer óáèë èãðîêà N */
	unsigned short KillPlayerRow[6]; /* óáèë èãðîêà ñ ID 0 */

};
extern wchar_t gNetworkNickName[16];
class MapGm {
public:
	// 0x000 .. 0x0ff — ïóòü ê êàðòå (.gmp)
	char gmpFile[256];
	// 0x100 .. 0x1ff — ïóòü ê ñòèëþ (.sty)
	char styFile[256];
	// 0x200 .. 0x2ff — ïóòü ê ñêðèïòó (.scr)
	char sctiptFile[256];
	// 0x300 .. 0x3ff — ïóòü ê ôàéëó ñîõðàíåíèÿ
	char saveFile[256];
	// 0x400 .. 0x404 — áàéòîâûå íàñòðîéêè
	unsigned char playerArena;      // 0x400
	unsigned char BonusStage;      // 0x401
	unsigned char Gang;            // 0x402
	unsigned char PlayerSlotSave;  // 0x403
	unsigned char Bonus;           // 0x404
	// 0x405 .. 0x407 — íå èñïîëüçóþòñÿ
	char gap405[3];
	// 0x408 .. 0x42f — ìàññèâ î÷êîâ/àðåí
	StatusLastGame StatusTable;                 // 0x408
	unsigned int AutoDamageCost;
	unsigned int FugitiveFactor;

	// 0x438 .. 0x443 — íàñòðîéêè ôðàãîâ è ðåæèìà
	short field_438;               // 0x438  (field15; SetField15/GetField15)
	unsigned char field_43A;       // 0x43a  (field16)
	unsigned char EndGameFlag;       // 0x43b  (field17; get_45E700)
	int FragLimit;                 // 0x43c  (ÑÑ‡Ñ‘Ñ‚Ñ‡Ð¸Ðº/Ð»Ð¸Ð¼Ð¸Ñ‚ Ñ„Ñ€Ð°Ð³Ð¾Ð²; ShowLimitFrame)
	unsigned char DataLast;       // 0x440  (field21)
	unsigned char Best;       // 0x441  (field22)
	unsigned char Index;       // 0x442  (field23; SetField23/Get_45E760)  Ð²Ð¾Ð·Ð¼Ð¾Ð¶Ð½Ð¾ ÐºÐ¾Ð»Ð¸Ñ‡ÐµÑÑ‚Ð²Ð¾ Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð²
	// 0x443 .. 0x447 â€” Ð²Ñ‹Ñ€Ð°Ð²Ð½Ð¸Ð²Ð°Ð½Ð¸Ðµ
	char gap443;
	int Count;                 //  Ð’Ñ€ÐµÐ¼Ñ Ð´Ð¾ Ð¾ÐºÐ½Ñ‡Ð°Ð½Ð¸Ðµ Ð¸Ð³Ñ€Ñ‹ 0x444  (field25; Get_field_444)
	// 0x448 .. 0x48f â€” ÑƒÐºÐ°Ð·Ð°Ñ‚ÐµÐ»ÑŒ/Ð·Ð°Ñ€ÐµÐ·ÐµÑ€Ð²Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð½Ð°Ñ Ð¾Ð±Ð»Ð°ÑÑ‚ÑŒ
	KillPlayer killPlayer[6];             // 0x448 (Ð±Ð°Ð·Ð° Ð¾Ð±Ð»Ð°ÑÑ‚Ð¸ 3*6 dword)
	// 0x490 .. 0x497 â€” ID Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð² (Ð¿Ð¾ 4)
	short PlayerID[6];             // 0x490
	// 0x498 .. 0x4af â€” Ð°Ñ€ÐµÐ½Ñ‹/Ð¾Ñ‡ÐºÐ¸ Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð² (Ð¿Ð¾ 4)
	int PlayerArena[6];            // 0x49Ð¡
	// 0x4b0 .. 0x573 â€” 6 ÑÑ‚Ñ€Ð¾Ðº Ð¿Ð¾ 16 wchar (Ð¸Ð¼ÐµÐ½Ð° Ð¸Ð³Ñ€Ð¾ÐºÐ¾Ð²)
	wchar_t NetworkNickName[6][16];// 0x4b4
	// 0x574 .. 0x578 â€” ÐºÐ¾Ð»Ð¸Ñ‡ÐµÑÑ‚Ð²Ð¾ SpecialTokens
	int SpecialTokens;             // 0x574

	MapGm();
	~MapGm();

	// --- ÑÐµÑ‚Ñ‚ÐµÑ€Ñ‹ Ð¸Ð¼Ñ‘Ð½ Ñ„Ð°Ð¹Ð»Ð¾Ð² ---
	char* SetMapName(char* Source);
	char* SetStyleName(char* Source);
	char* SetScripName(char* Source);
	char* SetSaveFile(char* Source);

	void SetPlayerArena(char value);
	void SetBonusStage(char value);
	void SetGang(char value);
	void SetPlayerSlotSave(char value);
	void SetBonus(char value);

	// --- Ð³ÐµÑ‚Ñ‚ÐµÑ€Ñ‹ Ð¸Ð¼Ñ‘Ð½ Ñ„Ð°Ð¹Ð»Ð¾Ð² ---
	char* GetMapName();
	char* GetStyleFile();
	char* GetScriptName();
	char* GetSaveFile();

	unsigned char GetPlayerArena();
	unsigned char GetBonusStage();
	unsigned char GetGang();
	unsigned char GetPlayerSlotSave();
	unsigned char GetBonus();

	// 0x0045e570/ çàïèñü/÷òåíèå Arr10[i]
	void SetPlayerArena(unsigned char index, int value);
	// 0x0045e590
	unsigned int GetAreaData(unsigned char index);

	// 0x0045e5b0
	void SetAutoDamageCost(int value);// (gm) ñòàðûé: SetCarCost -> SetAwardValue1
	// 0x0045e5c0
	int GetAutoDamageCost();
	
	//045e5d0
	void SetFugitiveFactor(unsigned int value);
	// 0x0045e5e0
	unsigned int  GetFugitiveFactor();
	// 0x0045e5f0/0x0045e600 â€” field15_0x438
	void SetField15(short value) { field_438 = value; }
	short GetField15() { return field_438; }

	// 0x0045e610/0x0045e620 â€” field16_0x43a
	void SetField16(char value) { field_43A = (unsigned char)value; }
	char Get_45E620() { return (char)field_43A; }

	// 0x0045e630 â€” ÑÐ±Ñ€Ð¾Ñ Ð½Ð°ÑÑ‚Ñ€Ð¾ÐµÐº Ð·Ð°Ð¿Ð¸ÑÐ¸ (Ð¸Ð¼ÐµÐ½Ð°/Ñ„Ñ€Ð°Ð³Ð¸/ÑÑ‚Ñ€Ð¾ÐºÐ¸)
	void ResetSettings();

	// 0x0045e700
	char GetEndGameFlag();

	// 0x0045e710 
	int GetLimitFrag();

	// 0x0045e720
	unsigned char GetDataLast();
	// 0x0045e730
	char GetBest();

	// 0x0045e740 //Player Max Count
	void SetIndex(char value);
	// 0x0045e760
	char GetIndex();

	// 0x0045e770/0x0045e7a0 â€” ÑÑ‚Ñ€Ð¾ÐºÐ¸ Ð¸Ð¼Ñ‘Ð½
	void SetNetworkNickName(unsigned short index, wchar_t* Source);
	// 0x0045e7a0
	wchar_t* GetNetworkNickName(unsigned short index);

	// 0x0045e7c0 â€” PlayerArena[i] += delta
	void AddScore(unsigned char index, int value);

	// 0x0045e7f0 â€” PlayerArena[i] / PlayerID[i]
	int GetPlayerArena(unsigned char id);
	// 0x0045e810
	short GetPlayerID(unsigned char id);

	// 0x0045e830 â€” field_448[6*a2 + a3] (ÑÑ‚Ð¸Ð»Ð¸Ð·Ð¾Ð²Ð°Ð½Ð¾ Ð¿Ð¾Ð´ PlayerID)
	unsigned short MapGm::GetScoreRow(unsigned char value, unsigned char row);

	// 0x0045e8d0 â€” Ð·Ð°Ð³Ñ€ÑƒÐ·ÐºÐ° Ð¸Ð¼Ñ‘Ð½ Ñ„Ð°Ð¹Ð»Ð¾Ð² Ð¸Ð· Ñ€ÐµÐµÑÑ‚Ñ€Ð° + ÑÐ±Ñ€Ð¾Ñ Ð½Ð°ÑÑ‚Ñ€Ð¾ÐµÐº
	int LoadFileResurce();

	// 0x0045ec20 â€” ÐºÐ¾Ð¿Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ðµ Ð½Ð°ÑÑ‚Ñ€Ð¾ÐµÐº Ð¸Ð· Player (Ð·Ð°Ð²Ð¸ÑÐ¸Ñ‚ Ð¾Ñ‚ Player)
	void LoadFromBuffer(void* player);

	// 0x0045ec70 â€” Ñ€ÐµÐ³Ð¸ÑÑ‚Ñ€Ð°Ñ†Ð¸Ñ Ñ„Ñ€Ð°Ð³Ð° Ð¸Ð³Ñ€Ð¾ÐºÐ° (Ð·Ð°Ð²Ð¸ÑÐ¸Ñ‚ Ð¾Ñ‚ Player/PlayerStats)
	void RegisterKill(unsigned char id, unsigned char a3);

	// SpecialTokens
	void SetSpecialTokensDefault() { this->SpecialTokens = 0; }
	int GetSpecialTokens() { return SpecialTokens; }
	void SetSpecialTokens(int value) { SpecialTokens = value; }
	void IncrementSpecialTokens() { ++SpecialTokens; }
	// 0x00476b10 â€” Ñ‚Ð¾ Ð¶Ðµ, Ñ‡Ñ‚Ð¾ SetSpecialTokens (Ð²Ð¾Ð·Ð²Ñ€Ð°Ñ‰Ð°ÐµÑ‚ value)
	int sub_476B10(int value) { SpecialTokens = value; return value; }

	// 0x00453a40 â€” ÐºÐ¾Ð´Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ðµ bonus stage: (playerArea << 4) | param2
	int EncodeBonusStage(unsigned char param2) { return (playerArena << 4) | param2; }
	// 0x00453a60 â€” Ð´ÐµÐºÐ¾Ð´Ð¸Ñ€Ð¾Ð²Ð°Ð½Ð¸Ðµ bonus stage
	void DecodeBonusStage(unsigned char bonusStage, unsigned char* playerArenaOut, unsigned char* out4);

	// 0x00461dc0 â€” Get_field_444
	int GetCount();


// ==== Ð¸Ð¼Ð¿Ð¾Ñ€Ñ‚ Ð¸Ð¼Ñ‘Ð½ Ð¸Ð· gm ====
    // 2 Ñ„ÑƒÐ½ÐºÑ†Ð¸Ð¹
    // 0x0045E5D0: MapGm::SetAwardValue2
    // 0x004C7370: MapGm::IsNotMode3
    void IsNotMode3();
};
extern MapGm* gMapGm;
#endif //__MAP_GM_H_