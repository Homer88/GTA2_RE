#ifndef __cAudioManager__H__
#define __cAudioManager__H__
#include <assert.h>
#include <Windows.h>

struct Car;
struct Player;

// AudioManager (S154) @0x005DCBC8, ext. size ~0x5578 (ida:unk_5DCBC8).
// Layout from dump gta2.exe.h /* 178 */ (field names/types preserved; most
// fields are raw charset dumps, hence anonymous).

/* 60959 */ enum VOCAL
{
  VOCAL_0 = 0u,
  VOCAL_INSANE_STUNT_BONUS = 1u,
  VOCAL_GRAND_THEFT_AUTO = 2u,
  VOCAL_WIPEOUT = 3u,
  VOCAL_EXPEDITIOUS_EXECUTION = 4u,
  VOCAL_GENOCIDE = 5u,
  VOCAL_COP_KILLA = 6u,
  VOCAL_CAR_JACKA = 7u,
  VOCAL_ELVIS_HAS_LEFT_THE_BUILDING = 8u,
  VOCAL_ACCURACY_BONUS = 9u,
  VOCAL_BACK_TO_FRONT_BONUS = 10u,
  VOCAL_MEDICAL_EMERGENCY = 11u,
  VOCAL_KILL_FRENZY = 12u,
  VOCAL_13 = 13u,
  VOCAL_14 = 14u,
  VOCAL_15 = 15u,
  VOCAL_16 = 16u,
  VOCAL_BUSTED = 17u,
  VOCAL_FRENZY_FAILED = 18u,
  VOCAL_FRENZY_PASSED = 19u,
  VOCAL_FRYING_TONIGHT = 20u,
  VOCAL_GAME_OVER = 21u,
  VOCAL_JOB_COMPLETE = 22u,
  VOCAL_JOB_FAILED = 23u,
  VOCAL_AND_REMEMBER__RESPECT_IS_EVERYTHING = 24u,
  VOCAL_SHOCKING = 25u,
  VOCAL_MMM____SOMETHIN_S_COOKIN = 26u,
  VOCAL_TIMES_UP__PAL = 27u,
  VOCAL_TOASTED = 28u,
  VOCAL_WASTED = 29u,
  VOCAL_bombarmed = 30u,
  VOCAL_laugh6 = 31u,
  VOCAL_LAUGH__changes_each_time_you_play_it = 32u,
  VOCAL_RACE_OVER = 33u,
  VOCAL_SECOND_LAP = 34u,
  VOCAL_FINAL_LAP = 35u,
  VOCAL_RACE_ON = 36u,
  VOCAL_HEY__30_PEOPLE_DOWN__MULTIPLIER_X2 = 37u,
  VOCAL_OOH__60_PEOPLE_DOWN__MULTIPLIER_X3 = 38u,
  VOCAL_NICE__90_PEOPLE_DOWN__MULTIPLIER_X4 = 39u,
  VOCAL_GREAT__120_PEOPLE_DOWN__MULTIPLIER_X5 = 40u,
  VOCAL_OUTSTANDING__150_PEOPLE_DOWN__MULTIPLIER_X6 = 41u,
  VOCAL_TIME_OUT = 42u,
  VOCAL_YOUR_TIME_IS_EXTENDED = 43u,
  VOCAL_TIME_S_UP__PAL___duplicate = 44u,
  VOCAL_Oh__sorry_about_that____Did_that_hurt = 45u,
  VOCAL_Nice_work = 46u,
  VOCAL_CHOCTASTIC = 47u,
  VOCAL_RASPBERRY_RIPPLE = 48u,
  VOCAL_YOU_SHOT_YOUR_LOAD = 49u,
  VOCAL_OOH____DID_THAT_HURT = 50u,
  VOCAL_DEATH_TO_ICE_CREAM_VANS = 51u,
  VOCAL_CRISPY_CRITTER = 52u,
  VOCAL_YOU_RE_TOAST__BUDDY = 53u,
  VOCAL_EAT_LEADEN_DEATH__PUNK = 54u,
  VOCAL_THAT_S_GOTTA_HURT = 55u,
  VOCAL_SORRY_ABOUT_THAT = 56u,
  VOCAL_XIN_LOI__MY_MAN = 57u,
  VOCAL_DAMN_SUNDAY_DRIVERS = 58u,
  VOCAL_SUCK_IT_AND_SEE = 59u,
  VOCAL_TASTE_MY_WRATH__ICE_CREAM_BOY = 60u,
  VOCAL_HALLELUJAH__ANOTHER_SOUL_SAVED = 61u,
  VOCAL_DAMNATION__NO_DONATION__NO_SALVATION = 62u,
  VOCAL_63 = 63u,
  VOCAL_64 = 64u,
};

struct Elements
{
};

struct AudioBuffer
{
    __int16 isActive;
    __int16 dataSize;
    int sampleRate;
    int endOffset;
    __int16 field_C;
};

struct AudioManager
{
    char AudioObject;
    char IsUserPaused;
    char field_2;
    char field_3;
    int field_4;
    unsigned __int8 field_8;
    char field_9;
    char field_A;
    char field_B;
    unsigned char field_C;
    char field_D;
    char field_E;
    char field_F;
    unsigned int field_10;
    int SampleRate;
    char field_18;
    char field_19;
    char field_1A;
    char field_1B;
    char SampCount;
    bool Sound3D;
    char field_1E;
    char field_1F;
    char field_20;
    unsigned __int8 EffectsVolume;
    unsigned __int8 MusicVolume;
    char field_23;
    bool SFXVol;
    unsigned __int8 CDVol;
    char volume;
    char field_27;
    Car* Car;
    char field_2C;
    char field_2D;
    char field_2E;
    char field_2F;
    int field_30;
    char field_34;
    char field_35;
    char field_36;
    char field_37;
    struct Player* Player;
    struct Player* Player1;
    int field_40;
    int SoundCar;
    char field_48;
    char field_49;
    char field_4A;
    char field_4B;
    int field_4C;
    int HZ;
    unsigned __int8 field_54;
    char field_55;
    char field_56;
    char field_57;
    int field_58;
    char field_5C;
    char field_5D;
    char field_5E;
    char field_5F;
    int field_60;
    int field_64;
    int field_68;
    int field_6C;
    char Volume;
    char field_71;
    char field_72;
    char field_73;
    char field_74;
    char field_75;
    char field_76;
    char field_77;
    int field_78;
    int field_7C;
    char field_80;
    char field_81;
    char field_82;
    char field_83;
    int field_84;
    int field_88;
    int field_8C;
    char field_90;
    char field_91;
    char field_92;
    char field_93;
    int field_94;
    unsigned __int8 field_98;
    char field_99;
    char field_9A;
    char field_9B;
    int Arr32_S155;
    char field_A0;
    char field_A1;
    char field_A2;
    char gapA3;
    char field_A4;
    char field_A5;
    char field_A6;
    char field_A7;
    char field_A8;
    char field_A9;
    char field_AA;
    char field_AB;
    char field_AC;
    char field_AD;
    char field_AE;
    char field_AF;
    char field_B0;
    char field_B1;
    char field_D0;
    char field_D1;
    char field_D2;
    char field_D3;
    char field_D4;
    char field_D5;
    char field_D6;
    char field_D7;
    char field_D8;
    char field_D9;
    char field_DA;
    char field_DB;
    char field_DC;
    char field_DD;
    char field_DE;
    char field_DF;
    char field_E0;
    char field_E1;
    char field_E2;
    char field_E3;
    char field_E4;
    unsigned char gapE5[96];
    char field_145;
    char gap146;
    char field_1BF;
    char field_30D;
    char field_4A9;
    char field_5CE;
    char field_805;
    char field_8B6;
    char field_A24;
    char field_B1A;
    char field_BA8;
    char field_C70;
    char field_CD0;
    char field_D43;
    char field_D87;
    unsigned __int8 field_D8F;
    char field_DA2;
    char field_DBA;
    unsigned int field_DBC[1];
    int field_DC0;
    char field_DC4;
    char field_DC5;
    char field_DC6;
    char field_DC7;
    char field_DC8;
    char field_DC9;
    char field_DCA;
    char field_DCB;
    char field_DCC;
    char field_DCD;
    char field_DCE;
    char field_DCF;
    char field_DD0;
    char field_DD1;
    char field_DD2;
    char field_DD3;
    int field_DD4;
    char field_DD8;
    char field_DD9;
    char field_DDA;
    char field_DDB;
    char field_DDC;
    char field_DDD;
    char field_DDE;
    char field_DDF;
    float field_DE0;
    char field_DE4;
    char field_DE5;
    char field_DE6;
    char field_DE7;
    int field_DE8;
    char field_DEC;
    char field_DED;
    char field_DEE;
    char field_DEF;
    char field_DF0;
    char field_DF1;
    char field_DF2;
    char field_DF3;
    char field_E02;
    char field_E03;
    int field_E04;
    char field_E08;
    char field_E09;
    char field_E0A;
    char field_E0B;
    char field_E0C;
    char field_E0D;
    char field_E0E;
    char field_E0F;
    char field_E10;
    char field_E11;
    char field_E12;
    char field_E13;
    char field_E14;
    char field_E15;
    char field_E16;
    char field_E17;
    char field_E18;
    char field_E19;
    char field_E1A;
    char field_E1B;
    int field_E1C;
    char field_E20;
    char field_E21;
    char field_E22;
    char field_E23;
    char field_E24;
    char field_E37;
    unsigned char gapE38[638];
    char field_10B6;
    unsigned char gap10B7[692];
    char field_136B;
    char gap136C;
    char field_1395;
    char field_1397;
    char field_139C;
    char field_13C4;
    char field_13D0;
    char field_13D4;
    char field_13E2;
    char field_13F0;
    char field_13FA;
    char field_141E;
    char field_1442;
    char field_1448;
    char field_144B;
    char field_1451;
    int field_1454;
    int field_1458;
    int field_145C;
    int field_1468;
    int field_146C;
    int field_1470;
    __int16 Rotation;
    unsigned char gap1476[2];
    int Length;
    Elements Elements_1[1];
    char field_1488;
    unsigned char gap1489[3];
    int field_1489;
    unsigned char gap1490[110];
    char field_14FB;
    unsigned char gap14FF[21];
    char field_1514;
    char field_1515;
    __int16 gap1516;
    unsigned char gap1518[47];
    char field_1547;
    unsigned char gap1548[124];
    char field_15C1;
    char gap15C2;
    unsigned char gap15C6[3];
    unsigned char gap15C9[4948];
    int field_291D;
    unsigned char gap2921[6954];
    char field_4448;
    int Ids[1];
    char gap4454;
    char field_4455;
    char field_4456;
    char field_4457;
    char field_4458;
    char field_4459;
    char field_445A;
    char field_445B;
    char field_445C;
    char field_445D;
    char field_445E;
    char field_445F;
    char field_4460;
    char field_4461;
    char field_4462;
    char field_4463;
    char field_4464;
    char field_4465;
    char field_4466;
    char field_4467;
    char field_4468;
    char field_4469;
    char field_536C;
    char field_5370;
    unsigned char gap5371[144];
    char field_5401;
    unsigned char gap5402;
    char field_5400;
    char gap5404;
    char field_5405;
    char field_5406;
    char field_5407;
    char field_5408;
    char field_5409;
    char field_540A;
    char field_540B;
    char field_540C;
    char field_540D;
    char field_5419;
    char field_542C;
    char field_542D;
    char field_542E;
    char field_542F;
    char field_5430;
    char field_5431;
    char field_5432;
    char field_5433;
    char field_5434;
    char field_5435;
    char field_5436;
    char field_5437;
    char field_5438;
    char field_5439;
    char field_543A;
    char field_543B;
    int Index;
    int field_543C;
    int field_5440;
    int field_5444;
    char field_544C;
    char field_544D;
    char field_544E;
    char field_544F;
    int field_5450;
    int relToAudio;
    char field_5454;
    char gap5459;
    char field_545A;
    char field_545B;
    char field_545C;
    char field_545D;
    char field_545E;
    char field_545F;
    int field_5460;
    enum VOCAL VOCAL;
    enum VOCAL Vocal;
    int field_5468;
    int field_546C;
    int field_5470;
    int field_5474;
    int field_5478;
    __int16 gap5480;
    char field_5482;
    unsigned char gap5483[101];
    AudioBuffer AudioBuffer[4];
    unsigned char gap5520[4];
    char field_5510;
    unsigned char gap5525[7];
    char field_5518[15];
    char field_553B;
    char field_553C;
    char field_553D;
    char field_553E;
    char field_553F;
    char field_5540;
    char field_5541;
    char field_5542;
    char field_5543;
    char field_5544;
    char field_5545;
    char field_5546;
    char field_5547;
    char field_5548;
    char field_5549;
    char field_554A;
    char field_554B;
    char field_554C;
    char field_554D;
    char field_554E;
    char field_554F;
    char field_5550;
    char field_5551;
    char field_5552;
    char field_5553;
    char field_5554;
    char field_5555;
    char field_5556;
    char field_5557;
    char field_5558;
    char field_5559;
    char field_555A;
    char field_555B;
    char field_555C;
    char field_555D;
    char field_555E;
    char field_555F;
    char field_5560;
    char field_5561;
};
static_assert(sizeof(AudioManager) == 0x5562, "Error Size AudioManager");
#endif // !__cAudioManager__H__