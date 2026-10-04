// gta2_clean.h - игровая зона unified + missing-типы из IDA
// Авто-генерируется merge_header.ps1 (топологический порядок).

enum MenuActions : __int8 {
MENUACTION_NONE = 0u,
MENUACTION_CHANGEPAGE = 1u,
MENUACTION_SETPLAYERNAME = 2u,
};

enum Shop {
Smith_and_Heston_s = 25000u,          ///< Устанавливает на автомобиль игрока стационарный пулемёт. Название гаража — явная отсылка на Smith Wesson — реально существующую компанию, производящую оружие.
Gold_Mines = 50000u,                  ///< Оборудует автомобиль игрока 10 транспортными минами, которые могут быть сброшены с автомобиля. Этот сервис доступен только в Жилом и Промышленном районах.
Red_Army_Surplus = 5000u,             ///< Устанавливает на машину бомбу, которая взрывается спустя 3 секунды после активации — нажатия на команду «огонь» в машине.
Hell_Oil = 10000u,                    ///< 	Даёт машине игрока 10 единиц нефти, которая может быть сброшена и разлита с автомобиля.
};

enum KeyCode {
Key_ESC = 1u,
Key_2 = 2u,
Key_3 = 3u,
Key_4 = 4u,
Key_5 = 5u,
Key_6 = 6u,
Key_7 = 7u,
Key_8 = 8u,
Key_9 = 9u,
Key_10 = 10u,
Key_11 = 11u,
Key_12 = 12u,
Key_13 = 13u,
Key_Backspace = 14u,
Key_Tab = 15u,
Key_16 = 16u,
Key_17 = 17u,
Key_18 = 18u,
Key_19 = 19u,
Key_20 = 20u,
Key_21 = 21u,
Key_22 = 22u,
Key_23 = 23u,
Key_24 = 24u,
Key_25 = 25u,
Key_26 = 26u,
Key_27 = 27u,
Key_Enter = 28u,
Key_29 = 29u,
Key_30 = 30u,
Key_31 = 31u,
Key_32 = 32u,
Key_33 = 33u,
Key_34 = 34u,
Key_35 = 35u,
Key_36 = 36u,
Key_37 = 37u,
Key_38 = 38u,
Key_39 = 39u,
Key_40 = 40u,
Key_41 = 41u,
Key_LeftShift = 42u,
Key_43 = 43u,
Key_Z = 44u,
Key_X = 45u,
Key_C = 46u,
Key_47 = 47u,
Key_48 = 48u,
Key_49 = 49u,
Key_50 = 50u,
Key_51 = 51u,
Key_52 = 52u,
Key_53 = 53u,
Key_RShift = 54u,
Key_55 = 55u,
Key_LeftAlt = 56u,
Key_Space = 57u,
Key_CapsLock = 58u,
Key_59 = 59u,
Key_60 = 60u,
Key_61 = 61u,
Key_62 = 62u,
Key_63 = 63u,
Key_64 = 64u,
Key_65 = 65u,
Key_66 = 66u,
Key_67 = 67u,
Key_68 = 68u,
Key_69 = 69u,
Key_70 = 70u,
Key_71 = 71u,
Key_72 = 72u,
Key_73 = 73u,
Key_74 = 74u,
Key_75 = 75u,
Key_76 = 76u,
Key_77 = 77u,
Key_Plus = 78u,
Key_79 = 79u,
Key_80 = 80u,
Key_81 = 81u,
Key_82 = 82u,
Key_DelNumPade = 83u,
Key_84 = 84u,
Key_85 = 85u,
Key_86 = 86u,
Key_87 = 87u,
Key_88 = 88u,
Key_89 = 89u,
Key_90 = 90u,
Key_91 = 91u,
Key_92 = 92u,
Key_93 = 93u,
Key_94 = 94u,
Key_95 = 95u,
Key_96 = 96u,
Key_97 = 97u,
Key_98 = 98u,
Key_99 = 99u,
Key_100 = 100u,
Key_101 = 101u,
Key_102 = 102u,
Key_103 = 103u,
Key_104 = 104u,
Key_105 = 105u,
Key_106 = 106u,
Key_107 = 107u,
Key_108 = 108u,
Key_109 = 109u,
Key_110 = 110u,
Key_111 = 111u,
Key_112 = 112u,
Key_113 = 113u,
Key_114 = 114u,
Key_115 = 115u,
Key_116 = 116u,
Key_117 = 117u,
Key_118 = 118u,
Key_119 = 119u,
Key_120 = 120u,
Key_121 = 121u,
Key_122 = 122u,
Key_123 = 123u,
Key_124 = 124u,
Key_125 = 125u,
Key_126 = 126u,
Key_127 = 127u,
Key_128 = 128u,
Key_129 = 129u,
Key_130 = 130u,
Key_131 = 131u,
Key_132 = 132u,
Key_133 = 133u,
Key_134 = 134u,
Key_135 = 135u,
Key_136 = 136u,
Key_137 = 137u,
Key_138 = 138u,
Key_139 = 139u,
Key_140 = 140u,
Key_141 = 141u,
Key_142 = 142u,
Key_143 = 143u,
Key_144 = 144u,
Key_145 = 145u,
Key_146 = 146u,
Key_147 = 147u,
Key_148 = 148u,
Key_149 = 149u,
Key_150 = 150u,
Key_151 = 151u,
Key_152 = 152u,
Key_153 = 153u,
Key_154 = 154u,
Key_155 = 155u,
Key_156 = 156u,
Key_157 = 157u,
Key_158 = 158u,
Key_159 = 159u,
Key_160 = 160u,
Key_161 = 161u,
Key_162 = 162u,
Key_163 = 163u,
Key_164 = 164u,
Key_165 = 165u,
Key_166 = 166u,
Key_167 = 167u,
Key_168 = 168u,
Key_169 = 169u,
Key_170 = 170u,
Key_171 = 171u,
Key_172 = 172u,
Key_173 = 173u,
Key_174 = 174u,
Key_175 = 175u,
Key_176 = 176u,
Key_177 = 177u,
Key_178 = 178u,
Key_179 = 179u,
Key_180 = 180u,
Key_181 = 181u,
Key_182 = 182u,
Key_183 = 183u,
Key_184 = 184u,
Key_185 = 185u,
Key_186 = 186u,
Key_187 = 187u,
Key_188 = 188u,
Key_189 = 189u,
Key_190 = 190u,
Key_191 = 191u,
Key_192 = 192u,
Key_193 = 193u,
Key_194 = 194u,
Key_195 = 195u,
Key_196 = 196u,
Key_197 = 197u,
Key_198 = 198u,
Key_199 = 199u,
Key_200 = 200u,
Key_201 = 201u,
Key_202 = 202u,
Key_203 = 203u,
Key_204 = 204u,
Key_205 = 205u,
Key_206 = 206u,
Key_207 = 207u,
Key_208 = 208u,
Key_209 = 209u,
Key_210 = 210u,
Key_211 = 211u,
Key_212 = 212u,
Key_213 = 213u,
Key_214 = 214u,
Key_215 = 215u,
Key_216 = 216u,
Key_217 = 217u,
Key_218 = 218u,
Key_219 = 219u,
Key_220 = 220u,
Key_221 = 221u,
Key_222 = 222u,
Key_223 = 223u,
Key_224 = 224u,
Key_225 = 225u,
Key_226 = 226u,
Key_227 = 227u,
Key_228 = 228u,
Key_229 = 229u,
Key_230 = 230u,
Key_231 = 231u,
Key_232 = 232u,
Key_233 = 233u,
Key_234 = 234u,
Key_235 = 235u,
Key_236 = 236u,
Key_237 = 237u,
Key_238 = 238u,
Key_239 = 239u,
Key_240 = 240u,
Key_241 = 241u,
Key_242 = 242u,
Key_243 = 243u,
Key_244 = 244u,
Key_245 = 245u,
Key_246 = 246u,
Key_247 = 247u,
Key_248 = 248u,
Key_249 = 249u,
Key_250 = 250u,
Key_251 = 251u,
Key_252 = 252u,
Key_253 = 253u,
Key_254 = 254u,
Key_255 = 255u,
Key_256 = 256u,
Key_257 = 257u,
Key_258 = 258u,
Key_259 = 259u,
Key_260 = 260u,
Key_261 = 261u,
Key_262 = 262u,
Key_263 = 263u,
Key_264 = 264u,
Key_265 = 265u,
Key_266 = 266u,
Key_267 = 267u,
Key_268 = 268u,
Key_269 = 269u,
Key_270 = 270u,
Key_271 = 271u,
Key_272 = 272u,
Key_273 = 273u,
Key_274 = 274u,
Key_275 = 275u,
Key_276 = 276u,
Key_277 = 277u,
Key_278 = 278u,
Key_279 = 279u,
Key_280 = 280u,
Key_281 = 281u,
Key_282 = 282u,
Key_283 = 283u,
Key_EnterNumPade = 284u,
Key_285 = 285u,
Key_286 = 286u,
Key_287 = 287u,
Key_288 = 288u,
Key_289 = 289u,
Key_290 = 290u,
Key_291 = 291u,
Key_292 = 292u,
Key_293 = 293u,
Key_294 = 294u,
Key_295 = 295u,
Key_296 = 296u,
Key_297 = 297u,
Key_298 = 298u,
Key_299 = 299u,
Key_300 = 300u,
Key_301 = 301u,
Key_302 = 302u,
Key_303 = 303u,
Key_304 = 304u,
Key_305 = 305u,
Key_306 = 306u,
Key_307 = 307u,
Key_308 = 308u,
Key_309 = 309u,
Key_310 = 310u,
Key_311 = 311u,
Key_312 = 312u,
Key_313 = 313u,
Key_314 = 314u,
Key_315 = 315u,
Key_316 = 316u,
Key_317 = 317u,
Key_318 = 318u,
Key_319 = 319u,
Key_320 = 320u,
Key_321 = 321u,
Key_322 = 322u,
Key_323 = 323u,
Key_324 = 324u,
Key_Pause = 325u,
Key_326 = 326u,
Key_327 = 327u,
Key_Up = 328u,
Key_PageUP = 329u,
Key_330 = 330u,
Key_Left = 331u,
Key_332 = 332u,
Key_333 = 333u,
Key_334 = 334u,
Key_End = 335u,
Key_Down = 336u,
Key_PageDown = 337u,
Key_338 = 338u,
Key_339 = 339u,
Key_340 = 340u,
};

enum KeyCode_1 {
ESC_I = 0u,
del_i = 1u,
ent_i = 2u,
bspc_i = 3u,
up_i = 4u,
down_i = 5u,
left_i = 6u,
right_i = 7u,
edtnm_i = 8u,
clrsl_i = 9u,
delch_i = 10u,
name_i = 11u,
};

enum ASCII_TABLE {
ASCII_TABLE_0 = 0u,
ASCII_0 = 48u,
ASCII_49 = 49u,
ASCII_50 = 50u,
ASCII_51 = 51u,
ASCII_52 = 52u,
ASCII_53 = 53u,
ASCII_54 = 54u,
ASCII_55 = 55u,
ASCII_56 = 56u,
ASCII_9 = 57u,
ASCII_58 = 58u,
ASCII_59 = 59u,
ASCII_60 = 60u,
ASCII_61 = 61u,
ASCII_62 = 62u,
ASCII_63 = 63u,
ASCII_64 = 64u,
ASCII_A = 65u,
ASCII_66 = 66u,
ASCII_67 = 67u,
ASCII_68 = 68u,
ASCII_69 = 69u,
ASCII_70 = 70u,
ASCII_71 = 71u,
ASCII_72 = 72u,
ASCII_73 = 73u,
ASCII_74 = 74u,
ASCII_75 = 75u,
ASCII_76 = 76u,
ASCII_77 = 77u,
ASCII_78 = 78u,
ASCII_79 = 79u,
ASCII_80 = 80u,
ASCII_81 = 81u,
ASCII_82 = 82u,
ASCII_83 = 83u,
ASCII_84 = 84u,
ASCII_85 = 85u,
ASCII_86 = 86u,
ASCII_87 = 87u,
ASCII_88 = 88u,
ASCII_89 = 89u,
ASCII_Z = 90u,
ASCII_91 = 91u,
ASCII_92 = 92u,
ASCII_93 = 93u,
ASCII_94 = 94u,
ASCII_95 = 95u,
};

enum Layout {
eng_kb = 0u,
fre_kb = 1u,
ger_kb = 2u,
ita_kb = 3u,
spa_kb = 4u,
por_kb = 5u,
};

typedef struct IDirectInputA IDirectInputA, *LPDIRECTINPUTA;
typedef struct IDirectInputDeviceA IDirectInputDeviceA, *LPDIRECTINPUTDEVICEA;
typedef HRESULT (__stdcall *LPDIENUMDEVICESCALLBACKA)(LPDIRECTINPUTDEVICEA, LPVOID);
typedef HRESULT (__stdcall *LPDIENUMDEVICESCALLBACKW)(LPDIRECTINPUTDEVICEA, LPVOID);

struct cameraPosTarget
{
struct Player *Player;
int field_4;
struct CameraOrPhysics *CameraOrPhysics_;
struct Car *Car_;
int field_10;
int field_14;
struct S32 *S32_;
struct Player *Player_;
int field_20;
int field_24;
};

struct CameraOrPhysics {
  int cameraPosTarget2;
  struct cameraPosTarget cameraPosTarget_[4];
  int Index;
  int HalfWidth;
  int ScreenY;
  int ScreenH;
};

struct S162 {
  int field_0;
  ushort field_4;
  char field_6;
  char field_7;
  int field_8;
  int field_C;
  ushort field_10;
  ushort field_12;
  int field_14;
  int field_18;
  int field_1C;
  int field_20;
  char field_24;
  char field_25;
  char field_26;
  char field_27;
  ushort field_28;
  char field_2A;
  char field_2B;
};

struct S165 {
  struct S162 S162_Arr10[10];
  int field_1B8;
  int Cycle;
};

struct S200 {
  char A;
  char B;
  char C;
};

struct Elements {
};

struct AudioBuffer {
  __int16 isActive;
  __int16 dataSize;
  int sampleRate;
  int endOffset;
  __int16 field_C;
};

struct AudioManager {
  char AudioObject;
  char IsUserPaused;
  char field_2;
  char field_3;
  int field_4;
  unsigned __int8 field_8;
  char field_9;
  char field_A;
  char field_B;
  byte field_C;
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
  struct Car *Car_;
  char field_2C;
  char field_2D;
  char field_2E;
  char field_2F;
  int field_30;
  char field_34;
  char field_35;
  char field_36;
  char field_37;
  struct Player *Player_;
  struct Player *Player1;
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
  _BYTE gapE5[96];
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
  _BYTE gapE38[638];
  char field_10B6;
  _BYTE gap10B7[692];
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
  _BYTE gap1476[2];
  int Length;
  struct Elements Elements_1[1];
  char field_1488;
  _BYTE gap1489[3];
  int field_1489;
  _BYTE gap1490[110];
  char field_14FB;
  _BYTE gap14FF[21];
  char field_1514;
  char field_1515;
  __int16 gap1516;
  _BYTE gap1518[47];
  char field_1547;
  _BYTE gap1548[124];
  char field_15C1;
  char gap15C2;
  _BYTE gap15C6[3];
  _BYTE gap15C9[4948];
  int field_291D;
  _BYTE gap2921[6954];
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
  char field_4464 ;
  char field_4465;
  char field_4466;
  char field_4467;
  char field_4468;
  char field_4469;
  char field_536C;
  char field_5370;
  _BYTE gap5371[144];
  char field_5401;
  _BYTE gap5402;
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
  enum VOCAL VOCAL_;
  enum VOCAL Vocal;
  int field_5468;
  int field_546C;
  int field_5470;
  int field_5474;
  int field_5478;
  __int16 gap5480;
  char field_5482;
  _BYTE gap5483[101];
  struct AudioBuffer AudioBuffer_;
  _BYTE gap5520[4];
  char field_5510;
  _BYTE gap5525[7];
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

struct S63_1 {
  enum DamageType DamageType_;
  char field_4;
  char field_5;
  char field_6;
  char field_7;
  char field_8;
  char field_9;
  char field_A;
  char field_B;
  char field_C;
  char field_D;
  char field_E;
  char field_F;
  char field_10;
  char field_11;
  char field_12;
  char field_13;
  char field_14;
  char field_15;
  char field_16;
  char field_17;
  char field_18;
  char field_19;
  char field_1A;
  char field_1B;
  char field_1C;
  char field_1D;
  char field_1E;
  char field_1F;
  char field_20;
  char field_21;
  char field_22;
  char field_23;
  char field_24;
  char field_25;
  char field_26;
  char field_27;
  char field_28;
  char field_29;
  char field_2A;
  char field_2B;
  char field_2C;
  char field_2D;
  char field_2E;
  char field_2F;
  __int16 field_30;
  char field_32;
  char field_33;
  char field_34;
};

struct S202 {
  int field_0;
  struct S202 *S202_;
  struct CarSystemManager *CarSystemManager_;
  int field_C;
  struct Weapon *field_10;
  struct Player *pPlayer;
  _DWORD field_18;
  unsigned __int8 field_1C;
  char field_1D;
  char field_1E;
  char field_1F;
};

struct MenuEntry {
  enum MenuActions MenuActions_;
  char field_1;
  __int16 X;
  __int16 Y;
  wchar_t TextMenuElement[50];
  __int16 StringLength;
  __int16 field_6C;
  ushort PlayerSlot;
  __int16 Plyrslot1;
  byte Flag[4];
  int field_76;
  int field_7A;
  unsigned __int16 Index;
  __int16 SelectMenu;
};

struct KeyState {
  unsigned __int8 left;
  unsigned __int8 Right;
  unsigned __int8 up;
  unsigned __int8 down;
  unsigned __int8 enter;
  unsigned __int8 esc;
  unsigned __int8 del;
};

struct GUI
{
char Interface;
char PlayerArena;
__int16 X;
__int16 Y;
wchar_t Sprite[50];
__int16 dX;
__int16 dY;
};

struct MenuItem
{
__int16 X;
__int16 Y;
bool IndexMenuActions;
char field_5;
};

struct MenuPage
{
unsigned __int16 CurrentMenuPage;
unsigned __int16 NextMenuPage;
struct MenuEntry MenuEntry_;
struct GUI GUI_;
struct MenuItem MenuItem_;
ushort IndexMenuActions;
__int16 SelectActiveElementDefault;
};

struct MenuDataBlock
{
char field_0;
char field_1;
char field_2;
char field_3;
};

struct MenuItemConfig
{
char fild;
char field_1;
_WORD field_2;
unsigned __int16 field_4;
_WORD Selecet;
wchar_t str[50];
};

struct MenuSlotConfig
{
__int16 Index;
struct MenuItemConfig MenuItemConfig_;
};

struct Menu {
  LPDIRECTINPUTA DirectInput;
  LPDIRECTINPUTDEVICEA InputDevice;
  char Keys[256];
  int FrontendState;
  char KeyboardAcquired;
  char FrontendKeysEnabled;
  char field_10E;
  char field_10F;
  int State;
  int field_114;
  int field_118;
  ushort FontStyle;
  ushort PageNumber;
  __int16 CountPage;
  struct MenuPage MenuPageArray[17];
  wchar_t *PlayerName;
  void *field_C990;
  void *field_C994;
  void *field_C998;
  __int16 field_C99C;
  unsigned __int8 Length;
  char field_C99F;
  __int16 Key;
  __int16 field_C9A2;
  wchar_t MenuItems[9];
  unsigned __int8 CurrentMenuItemsIndex;
  char field_C9B7;
  struct KeyState NewKeyState;
  struct KeyState OldKeyState;
  char field_C9C6;
  char field_C9C7;
  int TimeToWaitDemoStart;
  char FrameCounter;
  bool isChaet;
  char field_C9CE;
  char field_C9CF;
  int TimeToWaitBeforeDemoStart;
  __int16 gapC9D4;
  char field_C9D6[50];
  char field_CA08[10];
  char field_CA12;
  char field_CA13;
  __int16 gapCA13;
  char field_CA15[200];
  char field_CADD[50];
  char field_CB0F[50];
  char field_CB41[50];
  char field_CB72[50];
  char field_CBA4[50];
  char field_CBD6[50];
  char field_CC08[50];
  char field_CC3A[50];
  char field_CC6C[50];
  char field_CC9E[50];
  char field_CCD0[50];
  char field_EDB6[50];
  char field_CD36[1000];
  char field_D11E[1000];
  char field_D506[500];
  char field_D6FA[500];
  char field_D8EE[500];
  char field_DAE2[500];
  char field_DCD6[500];
  char field_DECA[1000];
  char field_E2B2[1000];
  char field_E69A[1000];
  char field_EA82[500];
  char field_EC76[200];
  char field_ED3E[100];
  char field_EDA2[50];
  struct MenuDataBlock MenuDataBlock_;
  enum MenuPic MenuPic_;
  char field_EDF5;
  __int16 field_EDF6;
  char field_EDF8;
  char PlayerSlot;
  struct MenuSlotConfig MenuSlotConfig_;
  __int16 field_1EB1C;
  char field_1EB1E;
  char field_1EB1F;
  struct Player *Player_;
  unsigned __int16 Index;
  char PlayerSlotSave[1];
  char field_1EB27;
  char field_1EB28;
  char field_1EB29;
  char field_1EB2A;
  char field_1EB2B;
  char field_1EB2C;
  char field_1EB2D;
  char BonusStage[8];
  char field_1EB36;
  char field_1EB37;
  char field_1EB38;
  char field_1EB39;
  char A1EB3A;
  char AAAA[1];
  unsigned __int8 CountArena;
  byte AAA[1];
  char field_1EB3F;
};

struct Network {
  struct Player *Player_;
  int field_4;
  int field_8;
  int field_C;
  int field_10;
  char field_14;
  char field_15;
  char field_16;
  char field_17;
  char field_18;
  char field_19;
  char field_1A;
  char field_1B;
  char field_1C;
  char field_1D;
  char field_1E;
  char field_1F;
  char field_20;
  char field_21;
  char field_22;
  char field_23;
  char field_24;
  char field_25;
  char field_26;
  char field_27;
  char field_28;
  char field_29;
  char field_2A;
  char field_2B;
  int arr6[6];
  int Select;
  int arr30[30];
  int arr321[32];
  char field_143;
  char field_1EE;
  char field_2C7;
  char field_316;
  char field_32A;
  char field_33F;
  char field_34A;
  char field_369;
  char field_374;
  char field_37E;
  char field_392;
  char field_3A2;
  char field_3AF;
  char field_3B2;
  char field_3B4;
  char field_3B5;
  char field_3B9;
  char field_3E2;
  char field_464;
  char field_4E7;
  char field_53B;
  int field_5C4;
  int field_5C8;
  void *field_5CC;
  int Index;
  int field_5D4;
  HANDLE HANDLE_;
  int field_5DC;
  LPVOID *field_5E0;
  char field_5E4;
  char field_5E5;
  char field_5E6;
  char field_5E7;
  char field_5E8;
  char field_5E9;
  char field_5EA;
  char field_5EB;
  char field_5EC;
  char field_5ED;
  char field_5EE;
  char field_5EF;
  char field_5F0;
  char field_5F1;
  char field_5F2;
  char field_5F3;
  char field_5F4;
  char field_5F5;
  char field_5F6;
  char field_5F7;
  char field_5F8;
  char field_5F9;
  char field_5FA;
  char field_5FB;
  char field_5FC;
  char field_5FD;
  char field_5FE;
  char field_5FF;
  _BYTE gap600[8];
  char field_608;
  _BYTE gap609[8];
  char field_611;
  char field_614;
  char field_615;
  _BYTE gap616[73];
  char field_65F;
  _BYTE gap660[37];
  char field_685;
  _BYTE gap686[3];
  char field_689;
  char field_68A;
  char field_68B;
  char field_68C;
  char field_68D;
  char field_68E;
  _BYTE gap68F[14];
  char field_69D;
  _BYTE gap69E[5];
  char field_6A3;
  _BYTE gap6A4[2];
  char field_6A6;
  _BYTE gap6A7[2];
  char field_6A9;
  _BYTE gap6AA[6];
  char field_6B0;
  char field_6B2;
  _BYTE gap6B3[7];
  char field_6BA;
  char field_6BC;
  _BYTE gap6BD[4];
  char field_6C1;
  char field_6C2;
  _BYTE gap6C3[7];
  char field_6CA;
  char field_6CB;
  _BYTE gap6CC;
  char field_6CD;
  _BYTE gap6CE[12];
  char field_6DA;
  _BYTE gap6DB[12];
  char field_6E7;
  _BYTE gap6E8[11];
  char field_6F3;
  _BYTE gap6F4[15];
  char field_703;
  int arr20[20];
  wchar_t ARR[144];
  int arr20_1[20];
  char field_8C7;
  char field_8D2;
  char field_8D6;
  char field_8D9;
  char field_8DB;
  int buffer1_0x1800;
  int buffer_0x1800;
  int Time;
  int field_8E8;
  char field_8EC;
  char field_8ED;
  int field_8F0;
  char field_900;
  char field_901;
  char field_902;
  char field_903;
  Network *Network_;
  char field_908;
  __int16 field_909;
  char field_BBA;
  char field_BE0;
  char field_BFE;
  char field_C08;
  char field_C11;
  char field_C1A;
  char field_C23;
  char field_C3D;
  char field_C58;
  char field_C67;
  char field_C8B;
  char field_C9E;
  char field_CA8;
  char field_CAC;
  char field_CAD;
  char field_CB0;
  int field_CB4;
  char field_CB8;
  char field_CEC;
  char field_E8A;
  char field_105B;
};

struct S86_8 {
  unsigned __int8 field_0;
  char field_1;
  wchar_t str[65];
  void *field_84;
  int field_88;
  int field_8C;
  int field_90;
  unsigned __int8 field_94;
  char field_95;
  char field_96;
  char field_97;
};

struct HudBrief {
  unsigned __int16 field_0;
  char field_2;
  char field_500;
  char field_501;
  char field_502;
  char field_503;
  __int16 field_504;
  char field_506;
  char field_507;
  void *field_508;
  int field_50C;
  int field_510;
  int field_514;
  int field_518;
  char field_51C;
  char field_51D;
  char field_51E;
  char field_51F;
  char field_520;
  char field_521;
  char field_522;
  char field_523;
  int field_524;
  char field_528;
  char field_529;
  char field_52A;
  char field_52B;
  char field_52C;
  char field_52D;
  char field_52E;
  char field_52F;
  char field_530;
  char field_531;
  char field_532;
  char field_533;
  char field_534;
  char field_535;
  char field_536;
  char field_537;
  char field_538;
  char field_539;
  char field_53A;
  char field_53B;
  char field_53C;
  char field_53D;
  char field_53E;
  char field_53F;
  char field_540;
  char field_541;
  char field_542;
  char field_543;
  char field_544;
  char field_545;
  char field_546;
  char field_547;
  char field_548;
  char field_549;
  char field_54A;
  char field_54B;
  char field_54C;
  char field_54D;
  char field_54E;
  char field_54F;
  char field_582;
  char field_59A;
  char field_5E5;
  char field_603;
  char field_62C;
  char field_644;
  char field_653;
  char field_654;
  char field_655;
  char field_656;
  char field_657;
  char field_658;
  char field_659;
  char field_662;
  char field_665;
  char field_667;
  char field_670;
  char field_679;
  char field_68A;
  char field_690;
  char field_699;
  char field_69F;
  char field_6A5;
  char field_6AE;
  char field_6B7;
  char field_6C0;
  char field_6C9;
  char field_6D2;
  char field_6D8;
  char field_6E1;
  char field_6EA;
  int field_6EC;
  char field_6F0;
  char field_6F3;
  char field_6F6;
  struct HudBrief_S2 *HudBrief_S2_;
  int field_6FC;
  struct HudBrief_S2 *pHudBrief_S2;
};

struct S86_7 {
  char field_0;
  int field_C0;
  int field_16F4;
  int field_16F8;
  S86_7 *field_16FC;
};

struct ArrowTrace {
  int field_0;
  int field_4;
  int field_8;
  Player *CurrentPlayer;
  int m_nType;
  int m_vPos;
  int m_vPos1;
  int m_vPos3;
  char field_23;
};

struct S86_2_1 {
  int Point;
  int Point2;
  __int16 m_nPointRotation;
  char field_A;
  char field_B;
  char field_C;
  char field_D;
  char field_E;
  char field_F;
  char field_10;
  char field_11;
  char field_12;
  char field_13;
  char field_14;
  char field_15;
  char field_16;
  char field_17;
  char field_18;
  char field_19;
  char field_1A;
  char field_1B;
  char field_1C;
  char field_1D;
  char field_1E;
  char field_1F;
  unsigned int isSelect;
  __int16 m_nSpriteId;
  __int16 field_26;
  struct Gang *Gang_;
  bool m_bVisible;
  bool ArrowVisible;
  char field_2E;
  char field_2F;
  ArrowTrace m_ArrowTrace;
  ArrowTrace m_SecondArrowTrace;
  ArrowTrace *ArrowTrace_;
};

struct HudArrow {
  struct S86_2_1 S86_2_1_;
  byte field_83C;
  HudArrow *HudArrowNext;
  char field_844;
  char field_845;
  char field_846;
  char field_847;
};

struct S86_3 {
  char field_0;
  char field_1;
  char field_2;
  char field_3;
  int field_4;
  int field_8;
};

struct S86_4 {
  struct S86_3 S83_3[6];
  int CopStars;
  int field_4C;
  int field_50;
  char field_54;
};

struct S86_5 {
  char field_A;
  char field_B;
  char field_C;
  char field_D;
  char field_E;
};

struct S86_10 {
  char field_0;
  char field_1;
  char field_2;
  char field_3;
};

struct S167
{
int field_0;
int field_4;
int Sound;
};

struct S166
{
struct S167 S167_;
};

struct HudMessage
{
char m_nTimeToShow;
char PlayerArena;
wchar_t gap[100];
wchar_t str[121];
int m_nStringWidth;
int m_nNumberLines;
int m_nType;
};

struct Hud {
  char field_0;
  _BYTE gap1;
  wchar_t field_2[17];
  __int16 SpriteId;
  _BYTE gap26[7];
  char ArrowVisible;
  _BYTE gap2E;
  char field_2F;
  _BYTE gap30[20];
  int field_44;
  int field_48;
  struct S86_8 S86_8_;
  struct HudBrief HudBrief_;
  struct S166 S166_;
  struct S86_7 S86_7_;
  struct HudArrow HudArrow_;
  struct S86_4 struc_S86_4;
  char s;
  char gap27B6;
  char field_27B7;
  char field_27B8;
  char field_27B9;
  char field_27BA;
  char field_27BB;
  __int16 gap27BC;
  void *field_2840;
  struct S86_5 S86_5_;
  struct HudMessage HudMessage_;
  struct S86_10 S86_10_;
  _BYTE S86_9[10];
  char field_2A2A;
  char field_2A2B;
  char field_2A2C;
  char field_2A2D;
  char field_2A2E;
  char field_2A2F;
  char field_2A30;
  char field_2A31;
  char field_2A32;
  char field_2A33;
  char field_2A34;
  char field_2A35;
  char field_2A36;
  char field_2A37;
  char field_2A38;
  char field_2A39;
  char field_2A3A;
  char field_2A3B;
  char field_2A3C;
  char field_2A3D;
  char field_2A3E;
  char field_2A3F;
  char field_2A40;
  char field_2A41;
  char field_2A42;
  char field_2A43;
  char field_2A44;
  char field_2A45;
  char field_2A46;
  char field_2A47;
  char field_2A48;
  char field_2A49;
  char field_2A4A;
  char field_2A4B;
  char field_2A4C;
  char field_2A4D;
  char field_2A4E;
  char field_2A4F;
  char field_2022;
  char field_2023;
  char field_2024;
  char field_2025;
  char field_2026;
  char gap2027;
  char field_2A89;
  char field_2A8A;
  char field_2A8B;
  char field_2A8C;
  char field_2A8D;
  char field_2A8E;
  char field_2A8F;
  char field_2A90;
  char field_2A91;
  char field_2A92;
  char field_2A93;
  char field_2A94;
  char field_2A95;
  char field_2A96;
  char field_2A97;
  char field_2A98;
  char field_2A99;
  char field_2A9A;
  char field_2A9B;
  char field_2A9C;
  char field_2A9D;
  char field_2A9E;
  char field_2A9F;
  char field_2AA0;
  char field_2040;
  char field_2041;
  char field_2042;
  char field_2043;
  char field_2044;
  char field_2045;
  char field_2046;
  char field_2047;
  char field_2048;
  char field_2049;
  char field_204A;
  char field_204B;
  char field_204C;
  char field_204D;
  char field_204E;
  char field_204F;
  char field_2050;
  char field_2051;
  char field_2052;
  __int16 gap2053;
  __int16 gap2055;
  char gap2AF8;
  char field_2AFB;
  char field_2AFC;
  char field_2AFD;
  char field_2AFE;
  void *field_2AF0;
  int TextSpeed;
};

struct HudBrief_S2 {
  char field_0;
  char field_1;
  int field_2;
  char field_6;
  char field_7;
  void *field_8;
  struct HudBrief_S2 *nextHudBrief_S2;
  char field_10;
  char field_11;
};

struct DMAudio {
  struct CameraOrPhysics *CameraOrPhysics_;
  char gap4;
  char field_5;
  char field_6;
  char field_7;
  char field_8;
  char field_9;
  char field_A;
  char field_B;
  char field_C;
  char field_D;
  char field_E;
  char field_F;
  char field_10;
  char field_11;
  char field_12;
  char field_13;
  char field_0;
  char field_15[1000];
  char field_3FD[100];
  char field_461[1000];
  char field_849[500];
  char field_A3D[2000];
  char field_120D[1000];
  char field_15F5[1000];
  char field_19DD[400];
  char field_1B6D[500];
  char field_1D61[2000];
  char field_2531[1000];
  char field_2919[1000];
  char field_2D01[500];
  char field_2EF5[50];
  char field_2F27[25];
  char field_2F40[20];
  char field_2F54[10];
  char field_2F5E[10];
  char field_2F68[10];
  char field_2F72;
  char field_2F73;
  char field_2F74;
  char field_2F75;
  char field_2F76;
  char field_2F77;
  char field_2F78;
};

struct S15_0002 {
  __int16 field_0;
  __int16 field_2;
  __int16 field_4;
  __int16 field_6;
  __int16 field_8;
  __int16 field_A;
  __int16 field_C;
  __int16 field_E;
  byte field_10;
  __int16 field_11;
};

struct S15_001 {
  __int16 field_0;
  __int16 field_2;
  __int16 field_4;
  __int16 field_6;
  __int16 field_8;
  __int16 field_A;
};

struct S1501 {
  char field;
  _BYTE gap1[2046];
  char field_0;
};

struct S284 {
  int Car[256];
  unsigned __int8 CountModelCar;
};

struct Map {
  void *FileLoad[65536];
  FILE *File;
  int field_40004;
  int field_40008;
  int field_4000C;
};

struct Replay {
  char field;
  char field_1;
  char field_2;
  char field_3;
  int Flag;
  char Anry_48[48];
  int field_38;
  int LPBUFFER_120000[120000];
  int field_7533C;
  int field_75340;
  unsigned __int8 field_75344;
  unsigned __int8 index;                ///< придел 3
  char field_75346;
  char field_75347;
  char field_75348;
  char field_75349;
  char field_7534A;
  char field_7534B;
  char field_7534C;
  char field_7534D;
};

struct S89_2 {
  int field_0[56];
};

struct PoliceInfo {
  char field_0;
  char field_1;
};

struct CarPhysics {
  char Model;
  char turbo;
  char value;
  char pad;
  float mass;
  float field_8;
  float field_C;
  float field_10;
  float field_14;
  float field_18;
  float field_1C;
  float field_20;
  float field_24;
  float field_28;
  float field_2C;
  float field_30;
  float field_34;
  float field_38;
  float field_3C;
  float field_40;
  float field_44;
};

struct CarPhysicsManager {
  struct CarPhysics CarPhysicsArray[83];
};

struct Data16 {
  int field_0;
  int field_4;
  int field_8;
  int field_C;
};

struct S68_1 {
  int field_0[255];
  char field_3FC;
};

struct MapGm {
  char gmpFile[256];
  char styFile[256];
  char ScriptFile[256];
  char SaveFile[256];
  unsigned __int8 playerArea;
  unsigned __int8 bonusStage;
  char Gang;
  char PlayerSlotSave;
  char Bonus;
  char field_405;
  char field_406;
  char field_407;
  int PlayerArena1[10];
  int field_430;
  int field_434;
  __int16 field_438;
  byte field_43A;
  byte field_43B;
  __int16 FragLimit;
  char field_43E;
  char field_43F;
  unsigned __int8 field_440;
  char field_441;
  char field_442;
  char field_443;
  int field_444;
  __int16 field_448[1];
  char field_44A;
  char field_44B;
  char field_44C;
  char field_44D;
  char field_44E;
  char field_44F;
  char field_450;
  char field_451;
  char field_452;
  char field_453;
  char field_454;
  char field_455;
  char field_456;
  char field_457;
  char field_458;
  char field_459;
  char field_45A;
  char field_45B;
  char field_45C;
  char field_45D;
  char field_45E;
  char field_45F;
  char field_460;
  char field_461;
  char field_462;
  char field_463;
  char field_464;
  char field_465;
  char field_466;
  char field_467;
  char field_468;
  char field_469;
  char field_46A;
  char field_46B;
  char field_46C;
  char field_46D;
  char field_46E;
  char field_46F;
  char field_470;
  char field_471;
  char field_472;
  char field_473;
  char field_474;
  char field_475;
  char field_476;
  char field_477;
  char field_478;
  char field_479;
  char field_47A;
  char field_47B;
  char field_47C;
  char field_47D;
  char field_47E;
  char field_47F;
  char field_480;
  char field_481;
  char field_482;
  char field_483;
  char field_484;
  char field_485;
  char field_486;
  char field_487;
  char field_488;
  char field_489;
  char field_48A;
  char field_48B;
  char field_48C;
  char field_48D;
  char field_48E;
  char field_48F;
  wchar_t PlayerID[4];
  char field_498;
  char field_499;
  char field_49A;
  char field_49B;
  int PlayerArena[4];
  char field_4AC;
  char field_4AD;
  char field_4AE;
  char field_4AF;
  char field_4B0;
  char field_4B1;
  char field_4B2;
  char field_4B3;
  wchar_t string_Arr0x16[16];
  _BYTE gap4D4[156];
  char field_570;
  char field_571;
  char field_572;
  char field_573;
  int SpecialTokens;
};

struct SubSlots {
  byte BonusStage[3][4];
};

struct ArenaSlots {
  struct SubSlots SubSlot[4];
};

struct S151
{
wchar_t ALAN[10];
int field_14;
wchar_t BRIAN[10];
int field_2C;
wchar_t COLIN[10];
int field_44;
wchar_t DAVE[10];
int field_5C;
wchar_t ERIC[10];
int field_74;
wchar_t FRANK[10];
int field_8C;
wchar_t Graeme[10];
int field_A4;
wchar_t HECTOR[10];
int field_BC;
wchar_t IMOGEN[10];
int field_D4;
wchar_t JACKSON[10];
int field_EC;
};

struct PlayerSlotSave
{
struct ArenaSlots ArenaSlots_;
wchar_t PlayerName[8];
__int16 field_A0;
char field_A2;
char field_0;
};

struct PlayerData {
  int field;
  int field_4;
  int field_8;
  int field_C;
  __int16 field_10;
  __int16 gap12;
  char field_14;
  char field_15;
  char field_3D;
  char field_5D;
  char field_99;
  struct S151 s151;
  char field_1E7;
  char field_21A;
  char field_16B0[1];
  char field_17DC;
  char field_17DD;
  char field_17DE;
  char field_17DF;
  char field_17E0;
  char field_17E1;
  char field_17E2;
  char field_17E3;
  char field_17E4;
  char field_17E5;
  char field_17E6;
  char field_17E7;
  char field_17E8;
  char field_17E9;
  char field_17EA;
  char field_17EB;
  char field_17EC;
  char field_17ED;
  char field_17EE;
  char field_17EF;
  char field_17F0;
  char field_17F1;
  char field_17F2;
  char field_17F3;
  char field_17F4;
  char field_17F5;
  char field_17F6;
  char field_17F7;
  char field_17F8;
  char field_17F9;
  char field_17FA;
  char field_17FB;
  char field_17FC;
  char field_17FD;
  char field_17FE;
  char field_17FF;
  byte arr_0x28[40];
  _BYTE gap1828[48];
  char field_1858;
  char field_1859;
  char field_185A;
  char field_185B;
  char field_185C;
  char field_185D;
  char field_185E;
  char field_185F;
  char field_1860;
  char field_1861;
  char field_1862;
  char field_1863;
  char field_1864;
  char field_1865;
  char field_1866;
  char field_1867;
  char field_1868;
  char field_1869;
  char field_186A;
  char field_186B;
  char field_186C;
  char field_186D;
  char field_186E;
  char field_186F;
  char field_1870;
  char field_1871;
  char field_1872;
  char field_1873;
  char field_1874;
  char field_1875;
  char field_1876;
  char field_1877;
  int field_1878[1];
  char field_187C;
  char field_187D;
  char field_187E;
  char field_187F;
  char field_1880;
  char field_1881;
  char field_1882;
  char field_1883;
  int field_1884[1];
  char field_1888;
  char field_1889;
  char field_188A;
  char field_188B;
  char field_188C;
  char field_188D;
  char field_188E;
  char field_188F;
  struct S151 S151_arr[12];
  struct S151 S151_;
  struct S151 S151_1;
  struct S151 *S151_2;
  char field_25B4;
  char field_25B5;
  char field_25B6;
  char field_25B7;
  char field_25B8;
  char field_25B9;
  _BYTE gap25BA;
  char field_25BB;
  _BYTE gap25BC[40];
  char field_25E4;
  _BYTE gap25E5[26];
  char field_25FF;
  _BYTE gap2600[26];
  char field_261A;
  _BYTE gap261B[20];
  char field_262F;
  _BYTE gap2630[26];
  char field_264A;
  _BYTE gap264B[50];
  char field_267D;
  _BYTE gap267E[21];
  char field_2693;
  char field_2694;
  char field_2695;
  char field_2696;
  char field_2697;
  char field_2698;
  char field_2699;
  char field_269A;
  char field_269B;
  char field_269C;
  char field_269D;
  char field_269E;
  char field_269F;
  struct PlayerSlotSave PlayerSlotSave_;
};

struct Sound5 {
  int field_0;
  int field_4;
  int field_8;
};

struct SoundCard {
  int AudioStream;
  char Path[4];
  struct Sound5 field_8;
  int field_14;
  char field_18;
  char field_19;
  char field_1A;
  char field_1B;
  int field_1C;
  int Rate;
  char Volume;
  char field_25;
  char field_26;
  char field_27;
  int field_28;
  char field_2C;
  char field_2D;
  char field_2E;
  char field_2F;
  int field_30;
  int field_34;
  int field_38;
  int field_3C;
  char field_40;
  char field_41;
  char field_42;
  char field_43;
  int field_44;
  int field_48;
  int field_4C;
  char field_50;
  char field_51;
  char field_52;
  char field_53;
  char field_54;
  byte isStreamActive;
  char field_56;
  char field_57;
  char sampleHandles[64];
  int SampleStatus;
  int stream_volume[1];
  int field_A0;
  char field_A4;
  char field_A5;
  char field_A6;
  char field_A7;
  char field_A8;
  char field_A9;
  char field_AA;
  char field_AB;
  char field_AC[1];
  char field_AD;
  char field_AE;
  char field_AF;
  char field_B0[1];
  char field_B1;
  char field_B2;
  char field_B3;
  char field_B4[1];
  char field_B5;
  char field_B6;
  char field_B7;
  char field_B8[1];
  char Pa1;
  char field_BA;
  char field_BB;
  char field_BC[1];
  char field_BD;
  char field_BE;
  char field_BF;
  char field_C0;
  char field_C1;
  char field_C2;
  char field_C3;
  char field_C4;
  char field_C5;
  char field_C6;
  char field_C7;
  char field_C8;
  char field_C9;
  char field_CA;
  char field_CB;
  char field_CC;
  char field_CD;
  char field_CE;
  char field_CF;
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
  int allocatedMemory;
  int memoryBuffer;
  byte totalSamples;
  byte AudioChannels;
  bool active3DSamples;
  int providerList[2];
  _BYTE gap1EBC[1016];
  int currentProviderEntry;
  _BYTE gap22B8[1020];
  int listenerID;
  int environmentPreset;
  int providerFlags;
  int current3DProvider;
  char sample3DHandles[64];
  float positionX;
  float positionY;
  float positionZ;
  void *total3DProviders;
  bool EffectsEnabled;
  _BYTE gap2715[8860];
  char field_B9;
};

struct S291 {
  int field_0;
};

struct S290 {
  struct S291 S291_;
};

struct S280 {
  struct PoliceInfo PoliceInfo_;
};

struct Keybord {
  __int16 CodeKey[256];
  Layout Layout_;
};

struct Random {
  int RandomNumberReal;
};

struct ObjectPool {
  struct Passenger *Passenger_;
  char field_4;
  char field_5;
  int arr99[99];
  _BYTE gap194[399];
  char field_0;
};

struct Taxi {
  char field_0;
  char field_1;
  char field_2;
  char field_3;
};

struct CarDoor
{
byte AnimationFrame[4];
int doorState;
struct Ped *PedInDoor;
byte field_C;
char rezerv_1;
char rezerv_2;
char Rezerv_3;
};

struct Car
{
void *Car;
struct Passenger *Passenger_;
struct PlayerStats *PlayerStats_;
struct CarDoor CarDoor_;
struct Car *LastCar;
struct SpriteS1 *CarSprite;
struct Ped *Driver;
struct Player *Player_;
struct EngineStruct *EngineStruct_;
struct Model *Model_;
void *TrailerCtrl;
int field_68;
int ID;
Ped *lastDamagingPed;                 ///< Damaged
__int16 Damage;
__int16 field_76;
__int16 PhysicsBitmask;
char field_7A;
char field_7B;
enum SearchType SearchType_;
char field_80;
char field_81;
char field_82;
char field_83;
CarModel CarType;
int Mask;
char FireState;
char field_8D;
char AlarmTime;
char field_8F;
enum DamageType DamageType_;
char DamageShotTimer;
char PlayerId;
char field_96;
char field_97;
int locksDoor;
CAR_ENGINE_STATE engineState;
TRAFFIC_CAR_TYPE trafficCarType;
char sirenState;
char sirenPhase;
char field_A6;
char horn;
char field_A8;
char FireTimer;
char field_AA;
char field_AB;
int field_AC;
int field_B0;
void *currentUpgradeSound;
char field_B8;
char field_B9;
char field_BA;
char field_0;
};

struct S32
{
char currentData;
char field_1;
char field_2;
char field_3;
struct S32 *prev_field;
struct S32 *NextElement;
};

struct Player
{
byte CurrentPlayer;
struct Player *Player_;
KeyPlayer Rotate;
enum FW FW_;
struct S103 *S103_;
__int16 Sw;
__int16 TypeWeapon;
struct S103 *S103_1;
__int16 SelectWeaponNext;
char field_1E;
char field_1F;
struct S103 *pS103;
int ID;
struct S103 *S103_2;
__int16 MoneyValue;
unsigned __int8 Ids;
char field_2F;
struct S103 *S103_5;
struct Gangs *RESPECT;
struct S103 *field_38;
int field_3C;
struct S103 *S103_4;
enum DEATH_REASON DeathReason;
struct Tango *Tango1;
int Sound;
int field_50;
int field_54;
int field_58;
struct Car *sCar1;
int field_60;
int field_64;
int MultiPlayerMode;
int field_6C;
byte Up;
byte Down;
byte Left;
byte Right;
byte prevWeapon;
byte nextWeapon;
byte debugKey1;
byte debugKey2;
bool Forward;
bool Backward;
bool RotateLeft;
bool RotateRight;
bool Attack;
bool Enter;
bool Jump;
bool NextWeaponZ;
bool PrevWeaponX;
bool keySpecial;
bool keySpecial2;
char field_83;
int field_84;
int field_88;
char AttackIsChanged;
char field_8D;
byte PlayerNext;
char field_8F;
struct CameraOrPhysics *CameraOrPhysics1;
char field_94;
char field_95;
char field_96;
char field_97;
int State;
struct AudioManager *AudioManager_;
int field_A0;
_BYTE gapA4[3];
char field_A7;
char field_A8;
char field_A9;
unsigned __int8 sbw;
unsigned __int8 tpa;
char field_AC;
_BYTE gapAD[11];
struct S131 *S1__;
_BYTE gapBC[23];
char field_D3;
_BYTE gapD4[7];
char field_DB;
_BYTE gapDC[14];
char field_EA;
_BYTE gapEB[12];
char field_F7;
_BYTE gapF8[10];
char field_102;
_BYTE gap103[18];
char field_115;
char field_116;
char field_117;
int field_118;
int field_11C;
int field_120;
char field_124;
char field_125;
char field_126;
char field_127;
int field_128;
int field_12C;
int field_130;
_BYTE gap134[24];
struct CameraOrPhysics *CameraOrPhysics_;
_BYTE gap150[4];
char field_154;
_BYTE gap155[62];
char field_193;
_BYTE gap194[18];
char field_1A6;
_BYTE gap1A7[32];
char field_1C7;
_BYTE gap1C8[9];
char field_1D1;
int field_1D4;
int field_1D8;
int field_1DC;
_BYTE gap1E0[4];
int Camer_X_View;
int Camer_Y_View;
int Camer_Z_View;
_BYTE gap1F0[3];
char field_1F3;
_BYTE gap1F4[6];
char field_1FA;
_BYTE gap1FB[7];
char field_202;
_BYTE gap203[5];
struct CameraOrPhysics *CameraOrPhysics2;
char field_20C;
_BYTE gap20D[28];
char field_229;
_BYTE gap22A[35];
char field_24D;
_BYTE gap24E[11];
char field_259;
_BYTE gap25A[17];
char field_26B;
_BYTE gap26C[32];
char field_28C;
_BYTE gap28D[11];
char field_298;
_BYTE gap299[5];
char field_29E;
char field_29F;
int AuxGameCameraX;
int AuxGameCameraY;
int AuxGameCameraZ;
_BYTE gap2AC[24];
struct Ped *MainPed;
struct Ped *pPassenger;
struct Car *sCar2;
char field_2D0;
struct PlayerStats *Money;
_BYTE gap2D8[107];
char field_343;
_BYTE gap344[160];
char field_3E4;
_BYTE gap3E5[53];
char field_41A;
_BYTE gap41B[46];
char field_449;
_BYTE gap44A[31];
char field_469;
char field_46A;
char field_46B;
char field_46C;
char field_46D;
char field_46E;
char field_46F;
char field_470;
char field_471;
char field_472;
char field_473;
char field_474;
char field_475;
char field_476;
char field_477;
char field_478;
char field_479;
char field_47A;
char field_47B;
char field_47C;
char field_47D;
char field_47E;
char field_47F;
char field_480;
_BYTE gap481[9];
char field_48A;
_BYTE gap48B[437];
char field_640;
int field_644;
_BYTE gap648[48];
int field_678;
int field_67C;
unsigned __int16 field_680;
__int16 field_682;
struct PlayerStats *Lives;
_BYTE gap688[52];
struct PlayerStats *MultiPlayer;
char field_6C0;
_BYTE gap6C1[24];
char field_6D9;
_BYTE gap6DA[11];
char field_6E5;
_BYTE gap6E6[6];
char field_6EC;
__declspec(align(4)) char field_6F0;
__declspec(align(4)) POWERUP_TYPE PowerUp[18];
struct Weapon *sWeapon[28];
__int16 SelectWeapon;
bool quit1;
char field_78B;
struct Ped *sPed1;
_BYTE gap790[4];
char Network;
_BYTE gap795[9];
char field_79E;
_BYTE gap79F[157];
wchar_t string_Arr0x16[16];
};

struct Passenger
{
struct Passenger *Passenger_;
struct Passenger *PassengerPrev;
};

struct PlayerStats
{
int MoneyValue;
int field_4;
char field_8;
char field_9[1];
_BYTE gapA[10];
int reverseCount;
__declspec(align(16)) Player *ToSaveSlot;
_BYTE gap24[2];
char field_26;
char field_27;
unsigned __int8 field_28;
__int16 MaxDigitsInValue;
__int16 Min;
unsigned __int16 DigitOffsetForAnimationOfChange;
int Max;
__int16 field_34;
__int16 ID;
struct PlayerStats *PlayerStats1;
char field_3C;
char field_3D;
char field_3E;
char field_3F;
char field_40;
char field_41;
char field_42;
char field_43;
char field_44;
char field_45;
byte field_46;
char field_47;
char field_48;
char field_49;
char field_4A;
char field_4B;
char field_4C;
char field_4D;
char field_4E;
char field_4F;
char field_50;
char field_51;
char field_52;
char field_53;
char field_54;
char field_55;
char field_56;
char field_57;
char field_58;
char field_59;
char field_5A;
char field_5B;
char field_5C;
char field_5D;
char field_5E;
char field_5F;
char field_60;
char field_61;
char field_62;
char field_63;
char field_64;
char field_65;
char field_66;
char field_67;
char field_68;
char field_69;
char field_6A;
char field_6B;
char field_6C;
char field_6D;
char field_6E;
char field_6F;
int field_70;
char field_74;
char field_75;
char field_76;
char field_77;
unsigned int Cycle1;
__int16 excutin;
char field_7E;
char field_7F;
int field_80;
__int16 elvis_d;
__int16 gencide;
__int16 copkill;
__int16 carjaka;
byte Arr_int_64[256];
int field_18C;
int fly_car;
int field_194;
char accurcy;
char field_199;
char field_19A;
char field_19B;
int wrngway;
int Cycle;
char em_dest;
char field_1A5;
char field_1A6;
char field_1A7;
struct S165 S165_;
struct Player *sPlayer;
char field_1AC;
_BYTE gap36D[658];
char field_5FF;
};

struct Ped
{
struct S200 S200_;
char field_CB;
char field_CC;
char field_CD;
char field_CE;
char field_CF;
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
char field_E5;
char field_E6;
char field_E7;
char field_E8;
char field_E9;
char field_EA;
char field_EB;
char field_EC;
char field_ED;
char field_EE;
char field_EF;
char field_F0;
char field_F1;
char field_F2;
char field_F3;
char field_F4;
char field_F5;
char field_F6;
char field_F7;
char field_F8;
char field_F9;
char field_FA;
struct Player *isPlayer;
char field_FF;
char field_100;
char field_101;
char field_102;
char field_103;
char field_104;
char field_105;
char field_106;
struct GameObject *GameObject2;
char field_10B;
char field_10C;
char field_10D;
char field_10E;
struct Weapon *WeaponSelect;
char field_113;
char field_114;
char field_115;
char field_116;
__int16 field_117;
char field_119;
char field_11A;
char field_11B;
char field_11C;
char field_11D;
char field_11E;
char field_11F;
char field_120;
char field_121;
char field_122;
char field_123;
char field_124;
char field_125;
char field_126;
char field_127;
__int16 field_128;
char field_12A;
char field_12B;
__int16 field_12C;
__int16 field_12E;
__int16 field_130;
__int16 field_132;
__int16 field_134;
char field_136;
char field_137;
struct GameObject *GameObject1;
int field_13C;
struct Car *Car1;
struct Ped *sPed1;
struct Ped *Driver;
struct Ped *LinkedPed;
struct Car *Vehicle;
struct Car *CurrentVehicle;
struct Car *TargetCarForEnter;
struct Player *Player_;
struct Ped *NextPed;
struct S169 *S169_;
struct GameObject *GameObject_;
struct Car *CurrentCar;
struct Weapon *SelectedWeapon;
struct Weapon *Weapon1;
struct Weapon *Weapon2;
struct Gang *Gang_;
struct Ped *DriverPed;
int field_184;
struct Ped *LastCharPunched;
struct Ped *field_18C;
struct S94 *S94_;
int field_194;
struct Ped *sPed3;
struct Gang *Gang1;
int PedId;
__int16 TargetCarDoor1;
__int16 PoliceStar1;
struct Ped *ElvisLeader;
int XCoordinate;
int PositionY;
int Camer_Z_View;
int PositionX1;
int PositionY1;
int PositionZ2;
int X;
int Y;
int Z;
int field_1D0;
int field_1D4;
int field_1D8;
enum Occupation OCCUPATION;
struct Ped *DriverPed1;
int PositionZ1;
int field_1E8;
int field_1EC;
int field_1F0;
int field_1F4;
int CurrentAction1;
int field_1FC;
int ID;
int IDPed;
__int16 Invulnerability;
__int16 PoliceStar;
__int16 field_20C;
unsigned __int16 field_20E;
__int16 field_210;
__int16 field_212;
__int16 field_214;
__int16 Health;
__int16 ObjectiveTimer;
__int16 CarStateTimer;
unsigned int Flags;
int field_220;
char field_224;
char DamageState;
unsigned __int8 ExitAnimState;
char field_227;
int field_228;
int field_22C;
int field_230;
char field_234;
char field_235;
char field_236;
char field_237;
enum SearchType SearchType_;
char CarId;
char field_23D;
char field_23E;
char field_23F;
ALL_PED Occupation;
enum Remap Remap_;
char field_245;
char field_246;
char field_247;
int TargetCarDoor;
char AnimationState;
char field_24D;
char field_24E;
char field_24F;
int field_250;
char field_254;
char field_255;
char field_256;
char field_257;
int ActionState;
int CurrentAction;
char field_260;
char field_261;
char field_262;
char field_263;
char field_264;
unsigned __int8 field_265;
char field_266;
char field_267;
char field_268;
char field_269;
char field_26A;
char field_26B;
enum GraphicType GraphicType_;
int field_270;
int GangCarModel;
enum PedState PedState_;
int field_27C;
int SavedState;
int field_284;
int field_288;
int field_28C;
int DamageType;
};

struct CarTransforms
{
struct SpriteS1 *SpriteS1_;
struct GameObject *GameObject_;
struct SpriteS3 *SpriteS3_;
struct CarTransforms *NextElement;
int PositionX;
int PositionY;
int PositionZ;
int spriteId;
__int16 Remap;
__int16 field_22;
int field_24;
char field_28;
int sprite_type;
int field_30;
int field_34;
int field_38;
};

struct SpriteS1
{
struct SpriteS1 *FirstElement;
struct CarTransforms S3_arr5031[5031];
};

struct EngineStruct
{
struct EngineStruct *ElementNext;
int field_4;
char field_8;
char field_9;
char field_A;
char field_B;
struct EngineStruct *FirstElement;
struct CarSystemManager *CarSystemManager_;
void *field_14;
void *field_18;
int field_1C;
int field_20;
int Flags;
char JuncIdx;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_33;
int field_34;
int field_38;
int field_3C;
int field_40;
int field_44;
int field_48;
int field_4C;
int field_50;
__int16 field_54;
__int16 field_56;
__int16 field_58;
__int16 field_5A;
int field_5C;
int field_60;
int field_64;
struct Car *Car_;
struct EngineStruct *NextElement;
int field_70;
int field_74;
};

struct Model
{
CarModel ModelCar;
struct Ped *Ped_;
int field_8;
int field_C;
char field_10;
char field_11;
char field_12;
char field_13;
int field_14;
struct Ped *DriverPed;
int field_1C;
char field_20;
char field_21;
char field_22;
char field_23;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
__int16 field_2A;
unsigned __int16 field_2C;
__int16 field_2E;
struct Ped *sPed;
char field_34;
char field_35;
char field_36;
char field_37;
char field_38;
char field_39;
char field_3A;
char field_3B;
char field_3C;
char field_3D;
char field_3E;
char field_3F;
};

struct S104
{
struct Weapon *Weapon_;
void *field_4;
int field_8;
int field_C;
int field_10;
int field_14;
int field_18;
int field_1C;
int field_20;
int field_24;
struct Arsenal *Turrel;
int field_2C;
struct EventHandler *S63;
struct EventHandler *S63_1;
struct EventHandler *S63_2;
struct EventHandler *S63_3;
struct EventHandler *S63_4;
struct EventHandler *S63_5;
struct EventHandler *S63_6;
struct EventHandler *S63_7;
struct EventHandler *S63_8;
struct EventHandler *S63_9;
int field_58;
void *field_5C;
struct SpriteS1 *SpriteS1_4;
struct SpriteS1 *SpriteS1_;
int field_68;
int field_6C;
int field_70;
struct SpriteS1 *SpriteS1_1;
int field_78;
struct cameraPosTarget *cameraPosTarget3;
struct Player *pPlayer;
struct Player *Player1;
int field_88;
struct Player *Player_;
struct CameraOrPhysics *CameraOrPhysics1;
int field_94;
int field_98;
int field_9C;
int field_A0;
void *field_A4;
struct Player *Player4;
struct Player *Player3;
struct CameraOrPhysics *CameraOrPhysics_;
int field_B4;
struct SpriteS1 *SpriteS1_2;
int field_BC;
int field_C0;
struct Car *Car1;
struct Car *Car2;
struct Car *Car3;
struct Car *Car4;
int field_D4;
int field_D8;
int field_DC;
int field_E0;
int field_E4;
int field_E8;
int field_EC;
int field_F0;
int field_F4;
int field_F8;
int field_FC;
int field_100;
int field_104;
int field_108;
int field_10C;
struct Player *Player2;
struct CameraOrPhysics *CameraOrPhysics2;
int field_118;
int field_11C;
int field_120;
int field_124;
int field_128;
int field_12C;
int field_130;
int field_134;
int field_138;
int field_13C;
__int16 field_140;
unsigned int Driver;
int field_148;
char field_14C;
char field_14D;
char field_14E;
char field_14F;
unsigned int field_150;
char field_154;
char field_155;
char field_156;
char field_157;
int field_158;
};

struct S103
{
struct S104 S104_;
int Idex;
};

struct Gang
{
bool inUse;
GANG CurrentGang;
char NameGang[10];
char field_C;
char field_D;
char field_E;
char field_F;
char field_10;
_BYTE gap11[240];
char remap;
char pad;
char field_103;
struct Weapon *Weapon1;
struct Weapon *Weapon2;
struct Weapon *Weapon3;
bool max_out;
char field_111;
char field_112;
char field_113;
char field_114;
char field_115;
char field_116;
char field_117;
char field_118;
char field_119;
char field_11A;
char Reting;
byte Prestige[8];
char field_124;
_BYTE gap125[7];
int X;
int Y;
int Z;
GANG NextGang;
byte Visible;
char field_13A;
char field_13B;
CarModel CarType;
char Car_remap;
char field_141;
char field_142;
char field_0;
};

struct Gangs
{
struct Gang Gang_;
};

struct Tango
{
int field;
struct Tango *Tango_;
int Select;
struct Car *TargetCar;
int field_10;
_BYTE gap14[8];
struct Car *Car_;
struct Ped *Ped_;
__int16 field_24;
char field_26;
char field_0;
};

struct S131
{
int Sound;
struct cameraPosTarget S132[80];
int Index;
};

struct Weapon
{
unsigned __int16 Ammo;
char TimeToReload;
char field_3;
int SMG;
int field_8;
int field_C;
__int16 short_;
char field_12;
char field_13;
struct Car *Car_;
struct Weapon *NextWeapon;
WeaponType TypeWeapon;
char field_20;
char field_21;
char field_22;
char field_23;
struct Ped *Ped_;
int SoundWeapon;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
};

struct GameObject
{
struct GameObject *NextGameObject1;
char field_4;
char Remap;
char field_6;
char field_7;
int field_8;
int field_C;
int field_10;
__int16 field_14;
char field_16;
char field_17;
int field_18;
int ProbablyPhysics;
int field_20;
int field_24;
__int16 field_28;
__int16 field_2A;
__int16 field_2C;
char field_2E;
char field_2F;
int field_30;
__int16 short_;
char field_36;
char field_37;
int Speed;
struct GameObject *NextGameObject;
__int16 Rotation;
__int16 field_42;
char field_44;
char field_45;
__int16 field_46;
char field_48;
char field_49;
__int16 CigaretteIdleTimer;
struct Car *Car1;
struct Car *Car2;
char field_54;
char field_55;
char field_56;
char field_57;
int field_58;
int field_5C;
int field_60;
int field_64;
char field_68;
char field_69;
char field_6A;
char field_6B;
int field_6C;
char field_70;
char field_71;
char field_72;
char field_73;
__int16 field_74;
char field_76;
char field_77;
struct GameObject *GameObject_;
struct Ped *Ped_;
struct SpriteS1 *SpriteS1_;
struct Car *GetVehicle;
struct Car *Car_;
int field_8C;
int Speed1;
int field_94;
int deltaX;
int deltaY;
int field_A0;
int teleportX;
int teleportY;
int teleportZ;
int field_B0;
};

struct S169
{
struct Ped *Ped1[1];
struct Ped *Ped_Arr9[9];
char field_28;
char field_29;
char field_2A;
char field_2B;
struct Ped *Ped_;
int field_30;
unsigned __int8 Index;
char field_35;
char field_36;
char field_37;
int field_38;
struct Ped *pPed;
int field_40;
};

struct S94
{
struct S200 S200_;
};

struct CarSystemManager
{
unsigned __int16 Index;
char field_2;
char field_3;
int field_4;
struct Weapon *Weapon_;
struct Car *Car_;
char field_10;
char field_11;
char field_12;
char field_13;
int ID;
char field_18;
char field_19;
char Count;
char field_1B;
int field_1C;
int field_20;
int field_24;
int RecycledCars;
int field_2C;
int field_30;
int UnitCars;
int field_38;
int MissionCars;
int RecycledCars_1;
int field_44;
int field_48;
struct Player *Player_;
char field_50;
char field_51;
char field_52;
char field_53;
char field_54;
char Count1;
char field_56;
char field_57;
CarModel CarType;
char field_5C;
char field_5D;
char field_5E;
char field_5F;
int field_60;
struct SpriteS1 *SpriteS1_0;
bool bool_;
bool DoFreeShopping;
char field_6A;
char field_0;
};

struct Arsenal
{
void *Sprite;
__int16 Count;
__int16 field_6;
};

struct EventHandler
{
struct EventHandler *NextElement;
struct SpriteS1 *SpriteS1_;
struct EventHandler *pEventHandler;
struct S65 *S65_;
struct Car *Car_;
int field_14;
struct S63_1 *S63_1_;
char field_1C;
char field_1D;
char field_1E;
char field_1F;
int field_20;
struct S202 *S202_;
char field_28;
char field_29;
char field_2A;
char field_0;
};

struct S39
{
int field_0;
struct SpriteS3 *SpriteS3_;
struct AudioSourceParams *field_8;
int field_C;
__int16 field_10;
__int16 field_12;
};

struct SpriteS3
{
struct S39 S39_Arr48[48];
int field_3C0;
int Res;
int AdressArray;
};

struct S65
{
struct S65 *NextElement;
__int16 field_4;
__int16 field_6;
};

struct AudioSourceParams
{
int field;
struct AudioSourceParams *AudioSourceParams_;
int AudioSourceParams1;
int AudioSourceParams2;
int field_10;
int field_14;
};

struct S2_111
{
_BYTE gap0[19];
char field_0;
};

struct S3_f
{
_BYTE gap0[4203];
char field_0;
};

struct S4_d
{
_BYTE gap0[879];
char field_0;
};

struct s5_1
{
_BYTE gap0[12035];
char field_0;
};

struct S6_a
{
byte field_0[16];
char field_10;
char field_11;
char field_12;
char field_13;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
char field_1C;
char field_1D;
char field_1E;
char field_1F;
char field_20;
char field_21;
char field_22;
char field_23;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_33;
char field_34;
char field_35;
char field_36;
char field_37;
char field_38;
char field_39;
char field_3A;
char field_3B;
char field_3C;
char field_3D;
char field_3E;
char field_3F;
char field_40;
char field_41;
char field_42;
char field_43;
char field_44;
char field_45;
char field_46;
char field_47;
char field_48;
char field_49;
char field_4A;
char field_4B;
char field_4C;
char field_4D;
char field_4E;
char field_4F;
char field_50;
char field_51;
char field_52;
char field_53;
char field_54;
char field_55;
char field_56;
char field_57;
char field_58;
char field_59;
char field_5A;
char field_5B;
char field_5C;
char field_5D;
char field_5E;
char field_5F;
char field_60;
char field_61;
char field_62;
char field_63;
char field_64;
char field_65;
char field_66;
char field_67;
char field_68;
char field_69;
char field_6A;
char field_6B;
char field_6C;
char field_6D;
char field_6E;
char field_6F;
char field_70;
char field_71;
char field_72;
char field_73;
char field_74;
char field_75;
char field_76;
char field_77;
char field_78;
char field_79;
char field_7A;
char field_7B;
char field_7C;
char field_7D;
char field_7E;
char field_7F;
char field_80;
char field_81;
char field_82;
char field_83;
char field_84;
char field_85;
char field_86;
char field_87;
char field_88;
char field_89;
char field_8A;
char field_8B;
char field_8C;
char field_8D;
char field_8E;
char field_8F;
char field_90;
char field_91;
char field_92;
char field_93;
char field_94;
char field_95;
char field_96;
char field_97;
char field_98;
char field_99;
char field_9A;
char field_9B;
char field_9C;
char field_9D;
char field_9E;
char field_9F;
char field_A0;
char field_A1;
char field_A2;
char field_A3;
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
char field_B2;
char field_B3;
char field_B4;
char field_B5;
char field_B6;
char field_B7;
char field_B8;
char field_B9;
char field_BA;
char field_BB;
char field_BC;
char field_BD;
char field_BE;
char field_BF;
char field_C0;
char field_C1;
char field_C2;
char field_C3;
char field_C4;
char field_C5;
char field_C6;
char field_C7;
char field_C8;
char field_C9;
char field_CA;
char field_CB;
char field_CC;
char field_CD;
char field_CE;
char field_CF;
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
char field_E5;
char field_E6;
char field_E7;
char field_E8;
char field_E9;
char field_EA;
char field_EB;
char field_EC;
char field_ED;
char field_EE;
char field_EF;
char field_F0;
char field_F1;
char field_F2;
char field_F3;
char field_F4;
char field_F5;
char field_F6;
char field_F7;
char field_F8;
char field_F9;
char field_FA;
char field_FB;
char field_FC;
char field_FD;
char field_FE;
char field_FF;
char field_100;
char field_101;
char field_102;
char field_103;
char field_104;
char field_105;
char field_106;
char field_107;
char field_108;
char field_109;
char field_10A;
char field_10B;
char field_10C;
char field_10D;
char field_10E;
char field_10F;
char field_110;
char field_111;
char field_112;
char field_113;
char field_114;
char field_115;
char field_116;
char field_117;
char field_118;
char field_119;
char field_11A;
char field_11B;
char field_11C;
char field_11D;
char field_11E;
char field_11F;
char field_120;
char field_121;
char field_122;
char field_123;
char field_124;
char field_125;
char field_126;
char field_127;
char field_128;
char field_129;
_BYTE gap12A[80];
char field_199;
char field_200;
};

struct S7_3
{
_BYTE gap0[2687];
char field_0;
};

struct S8__a
{
_BYTE gap0[107];
char field_0;
};

struct S9___
{
_BYTE gap0[531];
char field_0;
};

struct S10__a
{
_BYTE gap0[794279];
char field_0;
};

struct S11__a
{
_BYTE gap0[603];
char field_0;
};

struct S12__d
{
_BYTE gap0[83];
char field_0;
};

struct SpriteStructure
{
_BYTE gap0[7];
char field_0;
};

struct S41
{
char field_0;
char field_1;
char field_2;
char field_3;
struct EventHandler *S63;
};

struct GangInfo
{
struct GangInfo *NextElement1;
_BYTE gap4[8];
struct S41 S41_;
int NextElement;
_BYTE gap30[24];
char field_48;
_BYTE gap49[2];
char field_0;
};

struct SpriteS2
{
struct SpriteS3 *FirstElement;
struct GangInfo S40_ARR5031[5031];
};

struct s219
{
char S208;
_BYTE gap1[255];
struct S218 *S218_;
};

struct S218
{
_BYTE gap0[256];
char field_0;
};

struct Z1
{
_BYTE gap0[131615];
char field_0;
};

struct Game
{
unsigned int Status;
struct Player *ArrayPlayer[6];
struct Player *CurrentPlayer;
unsigned __int8 CurrentPlayerCopy;
unsigned __int8 Index;
bool field_22;
unsigned __int8 MaxIdx;
unsigned __int8 PlayerInFocus;
char field_25;
char field_26;
char field_27;
int isDead;
int State;
bool NoFrameLimit;
int SkipPolice;
struct Player *PlayerMain;
char gSkilPolice;
char field_3D;
char field_3E;
char field_3F;
};

struct S100_Aaa
{
_BYTE gap0[256];
char field_0;
};

struct S900
{
__int16 Index;
char field_2;
_BYTE gap3[253];
__int16 field_100;
};

struct S801
{
char field_0;
_BYTE gap1[58];
char field_3B;
_BYTE gap3C;
char field_3D;
char field_3E;
char field_3F;
char field_40;
char field_41;
char field_42;
char field_43;
char field_44;
char field_45;
char field_46;
char field_47;
char field_48;
char field_49;
char field_4A;
char field_4B;
char field_4C;
char field_4D;
char field_4E;
char field_4F;
char field_50;
char field_51;
char field_52;
char field_53;
char field_54;
_BYTE gap55[68];
char field_99;
char field_9A;
char field_9B;
char field_9C;
char field_9D;
char field_9E;
char field_9F;
char field_A0;
char field_A1;
char field_A2;
char field_A3;
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
char field_B2;
char field_B3;
char field_B4;
char field_B5;
char field_B6;
char field_B7;
char field_B8;
char field_B9;
char field_BA;
char field_BB;
char field_BC;
char field_BD;
char field_BE;
char field_BF;
char field_C0;
char field_C1;
char field_C2;
char field_C3;
char field_C4;
char field_C5;
char field_C6;
char field_C7;
char field_C8;
char field_C9;
char field_CA;
char field_CB;
char field_CC;
char field_CD;
char field_CE;
char field_CF;
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
_BYTE gapDC[336];
char field_100;
};

struct S6_1
{
char n1;
char field_1;
char field_2;
char field_3;
int field_4;
char field_8;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
char field_10;
char field_11;
char field_12;
char field_13;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
char field_1C;
char field_1D;
char field_1E;
char field_1F;
char field_20;
char field_21;
char field_22;
char field_23;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_33;
char field_34;
char field_35;
char field_36;
char field_37;
char field_38;
char field_39;
_BYTE gap3A[21821];
char field_0;
};

struct S6_2
{
_BYTE gap0[4096];
char field_0;
};

struct MissionScriptObjectData
{
struct MissionScriptObjectData *NextElement;
__int16 field_4;
char field_6;
char field_7;
int field_8;
char field_C;
char field_D;
__int16 field_E;
char field_10;
char field_11;
__int16 field_12;
byte arr[252];
__int16 field_110;
char field_112;
char field_113;
struct S29 *S29_;
char field_118;
char field_119;
__int16 field_11A;
};

struct MissionScriptObjects
{
struct MissionScriptObjectData *FirstElement;
struct MissionScriptObjectData *MissionScriptObjectDataNextElement;
struct MissionScriptObjectData MissionScriptObjectData_;
__int16 field_8E8;
char field_8EA;
char field_8EB;
};

struct Viewport
{
int Data1;
__int16 Data2;
struct Viewport *NextElement;
};

struct Camera
{
struct Viewport *FirstElement;
struct Viewport S34[50];
};

struct WeaponDatabase
{
struct Weapon *sWeapon;
struct Weapon *NextWeapon;
struct Weapon sWeapon_Arr255[255];
__int16 field_2FD8;
char field_2FDA;
char field_2FDB;
};

struct S350
{
int field_0;
char field_4;
char field_5;
char field_6;
char field_7;
__int16 field_8;
char field_A;
char field_B;
};

struct General
{
int Cycle;
int field_4;
};

struct Text
{
FILE *Base;
size_t Num;
int AutoClass4;
_BYTE gapC[4];
char Language;
_BYTE gap11[2];
char field_0;
};

struct Registry
{
LPDWORD field_0;
int field_4;
char field_8;
char field_9;
char field_A;
char field_B;
};

struct Style
{
__int16 field;
__int16 field_2;
unsigned __int16 field_4;
unsigned __int16 field_6;
unsigned __int16 PalitrePal;
char field_A;
char field_B;
int field_C;
struct S15_0002 *S15_0002_;
struct S15_001 *field_14;
int field_18;
struct Car *Car_;
int field_20;
int field_24;
FILE *field_28;
int field_2C;
int field_30;
int field_34;
int field_38;
int Tiles;
struct S1501 *S1501_;
int field_44;
int field_48;
int field_4C;
int field_50;
int field_54;
int field_58;
struct S284 *pCar_5C;
int delx3;
char *recy;
__int16 n_recy;
bool ColourDepth;
char pad2;
int arr1024[1024];
};

struct S16_01
{
_BYTE gap0[800];
int field_320;
};

struct MapRelatedStruct
{
struct Map *Map_;
struct S16_01 S16_01_;
FILE *Buffer_ZONE;
int count;
int field_330;
int field_334;
FILE *Buffer_MOBJ;
FILE *Buffer_LGHT;
FILE *Buffer_ANIM;
int field_344;
int field_348;
int field_34C;
int field_350;
int field_354;
int field_358;
int field_35C;
int field_360;
ushort field_364;
__int16 field_366;
char Len;
char field_369;
char field_36A;
char field_36B;
char field_36C;
char field_36D;
char field_36E;
char field_36F;
};

struct S16_02
{
__int16 field;
__int16 field_2;
__int16 field_4;
__int16 field_6;
__int16 field_8;
char field_A;
char field_B;
char field_C;
char field_0;
};

struct EntityManager
{
int dword_5EB854;
int dword_5EB854_;
int field_8;
char field_C;
char field_D;
char field_E;
char field_F;
char field_10;
char field_11;
char field_12;
char field_13;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
char field_1C;
char field_1D;
_BYTE gap1E[11648];
char field_0;
char field_2D9F;
_BYTE gap2DA0[348];
int field_2EFC;
int field_2F00;
};

struct VideoModeEntry
{
int field_0;
};

struct Display
{
struct VideoModeEntry VideoModeEntry_;
};

struct S20_01
{
int FirstElement;
int field_4;
int field_8;
};

struct RenderManager
{
struct S20_01 ARR_1000[1000];
int field_2EE0;
};

struct CameraManager
{
char field;
_BYTE gap1[3999];
struct CameraManager *CameraManager_;
};

struct BuildingModel
{
int field_0;
int field_4;
};

struct S24_01
{
char field_0;
char field_1;
char field_2;
char field_3;
};

struct S24
{
struct S24_01 data[30];
int field_78;
int field_7C;
};

struct Mike
{
struct BuildingModel S23[5];
struct S24 S24_;
_BYTE gap2A8[2000];
int field_A78;
int field_A7C;
};

struct CarsPrefabs
{
struct Car *sCar2;
struct Car *Car3;
struct Car sCarArr306[306];
__int16 CarsCount;
__int16 field_E0C2;
};

struct VehiclePool
{
struct VehiclePool *DATA;
struct VehiclePool *NextElement;
char field_8;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
struct CarSystemManager *CarSystemManager_;
char DATA1;
char field_15;
char field_16;
char field_17;
};

struct S45
{
char dat;
struct VehiclePool S46[300];
};

struct GameEntity
{
int CurrentElement;
struct GameEntity *S1;
int field_8;
struct GameEntity *FirstElement;
struct S41 S41_Arr4[4];
struct GameEntity *S1_1;
char field_34;
char field_35;
char field_36;
char field_37;
struct GameEntity *S1_2;
int field_3C;
char field_40;
char field_41;
char field_42;
char field_43;
char field_44;
char field_45;
char field_46;
char field_47;
char field_48;
char field_49;
char field_4A;
char field_4B;
char field_4C;
char field_4D;
char field_4E;
char field_4F;
char field_50;
char field_51;
char field_52;
char field_53;
char field_54;
char field_55;
char field_56;
char field_57;
__int16 special_buffer;
char field_5A;
char field_5B;
int field_5C;
char field_60;
char field_61;
char field_62;
char field_63;
char field_64;
char field_65;
char field_66;
char field_67;
char field_68;
char field_69;
char field_6A;
char field_6B;
char field_6C;
char field_6D;
char field_6E;
char field_6F;
char field_70;
char field_71;
char field_72;
char field_73;
char field_74;
char field_75;
char field_76;
char field_77;
char field_78;
char field_79;
char field_7A;
char field_7B;
int field_7C;
int field_80;
char field_84;
char field_85;
char field_86;
char field_87;
char field_88;
char field_89;
char field_8A;
char field_8B;
char field_8C;
char field_8D;
char field_8E;
char field_8F;
char field_90;
char field_91;
char field_92;
char field_93;
int field_94;
char field_98;
char field_99;
char field_9A;
char field_9B;
char field_9C;
char field_9D;
char field_9E;
char field_9F;
char field_A0;
char field_A1;
char field_A2;
char field_A3;
char NextElement;
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
char field_0;
};

struct CCarsPrefabs
{
struct GameEntity *GameEntity_;
struct GameEntity CGameEntity[306];
};

struct CarAudioSettings
{
char Flag;
char sirenActive;
char hornActive;
struct AudioSourceParams *AudioSourceParams_;
char sirenActive1;
char field_9;
char field_A;
char field_B;
struct Player *Player_;
int int_;
};

struct CarPhysicsWorld
{
struct EngineStruct *FirstElement;
struct EngineStruct EngineStruct_;
};

struct Trailer
{
int field_0;
struct Trailer *NextElement;
struct Car *Car_;
int field_C;
};

struct CarColorsPalette
{
struct Trailer *FirstElement;
struct Trailer Trailer_Arr10[10];
};

struct MissionObjective
{
char a;
char field_1;
char field_2;
char field_3;
_BYTE gap4[302];
char field_132;
_BYTE gap133[224];
char field_0;
};

struct S901
{
_BYTE gap0[1863];
char field_0;
};

struct TrafficManager
{
struct S32 *FirstElement;
struct S32 S32_;
};

struct Object
{
struct EventHandler *field_0;
struct EventHandler *field_4;
struct EventHandler S63[3825];
__int16 field_29174;
char field_29176;
char field_29177;
};

struct Character
{
unsigned __int16 field_0;
unsigned __int8 dummy_chars;
char field_3;
char field_4;
char field_5;
char Num_peds_on_screen;
bool Bunt;
struct SpriteS1 *SpriteS1_;
};

struct Radar
{
int field_0;
int Time;
int DeltaTime;
};

struct Timing
{
int field;
int timeGetTime;
int field_8;
int field_C;
int timeGetTime_1;
int Sec_100;
struct Radar S36[5];
};

struct SpriteEntry
{
void *ptr;
__int16 W;
__int16 pad;
};

struct SP
{
char field;
char field_1;
char field_2;
char field_3;
char field_4;
char field_5;
char field_6;
char field_7;
char field_8;
char field_9;
char field_A;
char field_B;
struct SpriteS1 *SpriteS1_;
char field_10;
char field_11;
char field_12;
_BYTE gap13[40];
char field_0;
};

struct SpriteS4
{
int dat;
struct VehiclePool S46_Arr300[300];
};

struct Input2
{
char field_0;
};

struct S88
{
int field_0;
GLuint *GLuint_;
__int16 field_8;
__int16 field_A;
};

struct S89
{
struct S89_2 *S89_2_;
unsigned __int16 Count;
__int16 field_6;
int sprite_type;
int field_C;
char field_10;
char field_11;
char field_12;
char field_13;
};

struct TextureManager
{
void *BufferTexture4M[1024];
char field_1000;
bool TexturesInitialised;
char field_1002;
char field_1003;
GLuint *Buffer_Arr48[48];
struct S88 Arr_96_S88[96];
GLuint *Texture;
struct S89 S89_;
__int16 field_15D4;
__int16 PalitrePal;
};

struct FileMgr
{
FILE *FILE_;
FILE *File1;
SIZE_T field_8;
int field_C;
int field_10;
int field_14;
int field_18;
int field_1C;
int field_20;
char field_24;
char field_25;
char field_26;
char field_27;
};

struct TangoMain
{
struct Tango Tango_Arr[2];
__int16 field_50;
char field_52;
char field_0;
};

struct S128
{
_BYTE gap0[19];
char field_0;
};

struct S127
{
unsigned __int16 index;
unsigned __int16 field_2;
struct S128 S128_;
};

struct S125
{
char field;
char field_1;
char field_2;
char field_3;
int field_4[9];
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_33;
__int16 field_34;
char field_36;
char field_37;
int field_38;
int field_3C;
char field_40;
char field_41;
char field_42;
char field_43;
int field_44;
__int16 field_48;
char field_4A;
char field_4B;
int field_4C;
};

struct S124
{
struct S125 *S125_1;
struct Game *Game_;
struct S125 S125_;
};

struct S123
{
__int16 Arr_element;
__int16 count;
struct S124 S124_;
int field_FC;
};

struct S121
{
struct Model Model_;
};

struct S122
{
char field0;
char field_1;
char field_2;
char field_3;
int field_4;
int field_8;
struct S122 *S122_;
char field_10;
char field_11;
char field_12;
char field_13;
int field_14;
int field_18;
int field_1C;
char field_20;
char field_21;
char field_22;
char field_23;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
__int16 field_2A;
__int16 field_2C;
__int16 field_2E;
int field_30;
__int16 field_34;
char field_36;
char field_37;
int field_38;
char field_3C;
char field_3D;
char field_3E;
char field_3F;
};

struct S119
{
struct Car *Car_;
struct Car *pCar;
int ID;
int field_C;
int field_10;
int field_14;
struct S103 *S103_1;
int field_1C;
struct S103 *S103_2;
int field_24;
struct S103 *S103_;
int Player;
struct S103 *S103_3;
char field_34;
char field_35;
char field_36;
char field_37;
int field_38;
char field_3C;
char field_3D;
char field_3E;
char field_3F;
char field_40;
char field_41;
char field_42;
char field_43;
struct Car *Car1;
};

struct S116
{
int Next;
int field_4;
void *field_8;
int Next1;
int field_10;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
struct S116 *NextElement;
int field_20;
int field_24;
};

struct S115
{
struct S116 *FirstElement;
int field_4;
struct S116 S116_;
__int16 field_1D4C8;
char field_1D4CA;
char field_0;
};

struct S112
{
__int16 field;
char X;
char Y;
char Z;
char field_5;
char field_6;
char field_7;
int field_8;
int field_C;
struct S110 *S110_;
struct S113 *S113_;
__int16 field_18;
char field_1A;
char field_1B;
int field_1C;
int field_20;
int State;
char field_28;
char field_29;
__int16 field_2A;
__int16 field_2C;
char field_2E;
char field_2F;
int field_30;
char field_34;
char field_35;
char field_36;
char field_0;
};

struct S113
{
struct Ped *Ped_;
void *field_4;
int field_8;
int field_C;
char field_10;
char field_11;
char field_12;
char field_13;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
char field_1C;
char field_1D;
char field_1E;
char field_1F;
struct S112 *S112_;
int field_28;
int field_2C;
int field_30;
int field_34;
int field_38;
int field_3C;
int field_40;
int field_44;
int field_48;
int field_4C;
int field_50;
int field_54;
int field_58;
int field_5C;
int field_60;
int field_64;
int field_68;
int field_6C;
char field_70;
char field_71;
char field_72;
char field_73;
char field_74;
char Count;
__int16 field_76;
char field_78;
char field_79;
__int16 Max900;
};

struct S110
{
struct Car *Car_;
struct Ped *Ped_;
struct S169 *NPC;
int field_C;
int field_10;
int field_14;
__int16 field_18;
__int16 field_1A;
__int16 field_1C;
char field_1E;
char field_1F;
int field_20;
int field_24;
int field_28;
char field_2C;
char field_2D;
char field_2E;
char field_0;
};

struct PoliceRoadblock
{
char field;
char field_1;
char field_2;
char field_3;
int field_4;
char field_8;
char field_9;
char field_A;
char field_B;
__int16 field_C;
char field_E;
char field_F;
struct Car *Car_;
struct Car *Car1;
struct Car *Car2;
struct Car *Car3;
struct Car *Car4;
struct Car *Car5;
struct EventHandler *S63;
struct EventHandler *S63_1;
struct EventHandler *S63_2;
struct EventHandler *S63_3;
struct EventHandler *S63_4;
struct EventHandler *S63_5;
struct EventHandler *S63_6;
struct EventHandler *S63_7;
struct EventHandler *S63_8;
struct EventHandler *S63_9;
struct EventHandler *S63_10;
struct EventHandler *field_54;
int field_58;
int field_5C;
int field_60;
int field_64;
int field_68;
int field_6C;
int field_70;
int field_74;
int field_78;
int field_7C;
int field_80;
int field_84;
struct Ped *Ped_;
struct Ped *Ped1;
struct Ped *Ped2;
struct Ped *Ped3;
struct Ped *Ped4;
struct Ped *Ped5;
struct AudioSourceParams *S9;
_BYTE gapA4[571];
char field_0;
};

struct S109
{
struct S110 S110_;
};

struct S108
{
int field;
int field_4;
int field_8;
struct Player *Player_;
ushort a2;
SHORT field_12;
ushort field_14;
char field_16;
char field_17;
int Cycle;
ushort field_1C;
ushort field_1E;
char field_20;
char field_21;
char field_22;
char field_23;
int field_24;
int field_28;
};

struct S107
{
struct S108 S108_;
int Index;
int Count;
unsigned __int8 field_14A8;
char field_14A9;
char field_14AA;
char field_14AB;
};

struct S106
{
char field;
char field_1;
char field_2;
char field_3;
char field_4;
char field_5;
char field_6;
char field_7;
char field_8;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
char field_10;
char field_11;
char field_12;
char field_13;
struct Car *Car_;
int field_18;
struct Weapon *field_1C;
int field_20;
int field_24;
int field_28;
int Select;
};

struct S105
{
struct S106 S106_;
int count;
};

struct S101
{
char field;
char field_1;
char field_2;
char field_3;
char field_4;
char field_5;
char field_6;
char field_7;
char field_8;
char field_9;
char field_A;
char field_B;
struct CarSystemManager *CarSystemManager_;
char field_10;
char field_11;
char field_12;
char field_13;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
char field_1C;
char field_1D;
char field_1E;
char field_1F;
struct CarSystemManager *CarSystemManager_1;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_0;
};

struct S102
{
struct S101 S101_;
char field_780;
char field_781;
char field_782;
char field_783;
char field_784;
char field_785;
char field_786;
char field_787;
char field_788;
char field_789;
char field_78A;
char field_78B;
char field_78C;
char field_78D;
char field_78E;
char field_78F;
char field_790;
char field_791;
char field_792;
char field_793;
char field_794;
char field_795;
char field_796;
char field_797;
char field_798;
char field_799;
char field_79A;
char field_79B;
char field_79C;
char field_79D;
char field_79E;
char field_79F;
char field_7A0;
char field_7A1;
char field_7A2;
char field_7A3;
char field_7A4;
byte field_7A5;
char field_7A6;
char field_0;
};

struct S100
{
struct S101 S101_;
char field_3C0;
char field_3C1;
char field_3C2;
char field_3C3;
char field_3C4;
char field_3C5;
char field_3C6;
char field_3C7;
char field_3C8;
char field_3C9;
char field_3CA;
char field_3CB;
char field_3CC;
char field_3CD;
char field_3CE;
char field_3CF;
char field_3D0;
char field_3D1;
char field_3D2;
char field_3D3;
};

struct Particles
{
struct EventHandler *pS63;
struct EventHandler field_4;
};

struct Particle1
{
_BYTE gap0;
char field_1;
char field_2;
char field_3;
int field_4;
int field_8;
int field_C;
int field_10;
int field_14;
int field_18;
struct Particles *Particles_;
int field_20;
struct CarSystemManager *CarSystemManager_;
struct SpriteS1 *SpriteS1_1;
__int16 Select;
unsigned __int16 field_2E;
struct SpriteS1 *SpriteS1_;
int field_34;
int field_38;
struct Particle1 *Particle1_;
struct S65 *S65_;
__int16 field_44;
unsigned __int8 field_46;
char field_47;
char field_48;
char field_49;
char field_4A;
char field_0;
};

struct Particle
{
struct Particle1 *FirstElement;
struct Particle1 *Particle1_;
struct Particle1 Particle1_ARR[500];
__int16 field_9478;
__int16 field_947A;
};

struct CarEngines
{
int EngineState[256];
struct PoliceInfo *PoliceInfo_;
int Arr_256_1[256];
struct CarPhysicsManager *CarPhysicsManager_;
};

struct S95
{
struct Passenger *Passenger1;
char field_4;
char field_5;
char field_6;
char field_7;
int field_8;
__int16 field_C;
char field_E;
char field_F;
char field_10;
char field_11;
char field_12;
char field_13;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
__int16 field_1C;
__int16 field_1E;
char field_20;
char field_21;
char field_22;
char field_23;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
__int16 field_2E;
char field_30;
char field_31;
char field_32;
char field_33;
__int16 field_34;
__int16 field_36;
char field_38;
char field_39;
__int16 field_3A;
struct Passenger *Passenger_;
char Buffer_0x2310[8976];
int field_2350;
char field_2354;
char field_2355;
char field_2356;
char field_2357;
char field_2358;
char field_2359;
char field_235A;
char field_235B;
char field_235C;
char field_235D;
char field_235E;
char field_235F;
char field_2360;
char field_2361;
char field_2362;
char field_2363;
char field_2364;
char field_2365;
char field_2366;
char field_2367;
char field_2368;
char field_2369;
char field_236A;
char field_236B;
char field_236C;
char field_236D;
char field_236E;
char field_236F;
char field_2370;
char field_2371;
char field_2372;
char field_2373;
char field_2374;
char field_2375;
char field_2376;
char field_2377;
char field_2378;
char field_2379;
char field_237A;
char field_237B;
char field_237C;
char field_237D;
char field_237E;
char field_237F;
char field_2380;
char field_2381;
char field_2382;
char field_2383;
char field_2384;
char field_2385;
char field_2386;
char field_2387;
char field_2388;
char field_2389;
char field_238A;
char field_238B;
char field_238C;
char field_238D;
char field_238E;
char field_238F;
char field_2390;
char field_2391;
char field_2392;
char field_2393;
char field_2394;
char field_2395;
char field_2396;
char field_2397;
char field_2398;
char field_2399;
char field_239A;
char field_239B;
char field_239C;
char field_239D;
char field_239E;
char field_239F;
char field_23A0;
char field_23A1;
char field_23A2;
char field_23A3;
char field_23A4;
char field_23A5;
char field_23A6;
char field_23A7;
char field_23A8;
char field_23A9;
char field_23AA;
char field_23AB;
char field_23AC;
char field_23AD;
char field_23AE;
char field_23AF;
char field_23B0;
char field_23B1;
char field_23B2;
char field_23B3;
char field_23B4;
char field_23B5;
char field_23B6;
char field_23B7;
char field_23B8;
char field_23B9;
char field_23BA;
char field_23BB;
char field_23BC;
char field_23BD;
char field_23BE;
char field_23BF;
char field_23C0;
char field_23C1;
char field_23C2;
char field_23C3;
char field_23C4;
char field_23C5;
char field_23C6;
char field_23C7;
char field_23C8;
char field_23C9;
char field_23CA;
char field_23CB;
char field_23CC;
char field_23CD;
char field_23CE;
char field_23CF;
char field_23D0;
char field_23D1;
char field_23D2;
char field_23D3;
char field_23D4;
char field_23D5;
char field_23D6;
char field_23D7;
char field_23D8;
char field_23D9;
char field_23DA;
char field_23DB;
char field_23DC;
char field_23DD;
char field_23DE;
char field_23DF;
char field_23E0;
char field_23E1;
char field_23E2;
char field_23E3;
char field_23E4;
char field_23E5;
char field_23E6;
char field_23E7;
char field_23E8;
char field_23E9;
char field_23EA;
char field_23EB;
char field_23EC;
char field_23ED;
char field_23EE;
char field_23EF;
char field_23F0;
char field_23F1;
char field_23F2;
char field_23F3;
char field_23F4;
char field_23F5;
char field_23F6;
char field_23F7;
char field_23F8;
char field_23F9;
char field_23FA;
char field_23FB;
char field_23FC;
char field_23FD;
char field_23FE;
char field_23FF;
char field_2400;
char field_2401;
char field_2402;
char field_2403;
char field_2404;
char field_2405;
char field_2406;
char field_2407;
char field_2408;
char field_2409;
char field_240A;
char field_240B;
char field_240C;
char field_240D;
char field_240E;
char field_240F;
char field_2410;
char field_2411;
char field_2412;
char field_2413;
char field_2414;
char field_2415;
char field_2416;
char field_2417;
char field_2418;
char field_2419;
char field_241A;
char field_241B;
char field_241C;
char field_241D;
char field_241E;
char field_241F;
char field_2420;
char field_2421;
char field_2422;
char field_2423;
char field_2424;
char field_2425;
__int16 field_2426;
char field_2428;
char field_2429;
char field_242A;
char field_242B;
char field_242C;
char field_242D;
char field_242E;
char field_242F;
char field_2430;
char field_2431;
char field_2432;
char field_2433;
char field_2434;
char field_2435;
char field_2436;
char field_2437;
char field_2438;
char field_2439;
char field_243A;
char field_243B;
char field_243C;
char field_243D;
char field_243E;
char field_243F;
char field_2440;
char field_2441;
char field_2442;
char field_2443;
char field_2444;
char field_2445;
char field_2446;
char field_2447;
char field_2448;
char field_2449;
char field_244A;
char field_244B;
char field_244C;
char field_244D;
char field_244E;
char field_244F;
char field_2450;
char field_2451;
char field_2452;
char field_2453;
char field_2454;
char field_2455;
char field_2456;
char field_2457;
char field_2458;
char field_2459;
char field_245A;
char field_245B;
char field_245C;
char field_245D;
_BYTE gap245E[2861];
char field_2F8B;
char field_2F8C;
char field_2F8D;
char field_2F8E;
char field_2F8F;
char field_2F90;
char field_2F91;
char field_2F92;
char field_2F93;
char field_2F94;
char field_2F95;
char field_2F96;
char field_2F97;
char field_2F98;
char field_2F99;
char field_2F9A;
char field_2F9B;
char field_2F9C;
char field_2F9D;
char field_2F9E;
char field_2F9F;
__int16 field_2FA0;
char field_2FA2;
char field_2FA3;
char field_2FA4;
char field_2FA5;
char field_2FA6;
 __declspec(align(1)) __int16 field_2FA7;
char field_2FA9;
char field_2FAA;
char field_2FAB;
char field_2FAC;
char field_2FAD;
char field_2FAE;
char field_2FAF;
char field_2FB0;
char field_2FB1;
char field_2FB2;
char field_2FB3;
char field_2FB4;
char field_2FB5;
char field_2FB6;
char field_2FB7;
char field_2FB8;
char field_2FB9;
char field_2FBA;
char field_2FBB;
char field_2FBC;
char field_2FBD;
char field_2FBE;
char field_2FBF;
char field_2FC0;
char field_2FC1;
char field_2FC2;
char field_2FC3;
char field_2FC4;
char field_2FC5;
char field_2FC6;
char field_2FC7;
char field_2FC8;
char field_2FC9;
char field_2FCA;
char field_2FCB;
char field_2FCC;
char field_2FCD;
char field_2FCE;
char field_2FCF;
char field_2FD0;
char field_2FD1;
char field_2FD2;
char field_2352;
};

struct S93_1
{
struct S94 S94_;
byte Arr48[48];
__int16 field_1D7C;
};

struct S92
{
__int16 field_0;
__int16 field_2;
__int16 field_4;
char field_6;
char field_7;
struct S92 *S92_;
struct S92 *S92__2;
};

struct JuncIds
{
__int16 Count;
unsigned __int8 field_2;
char field_3;
__int16 field_4;
char field_6;
char field_7;
struct Data16 Arr_316_Data16[396];
char field_18C8;
char field_18C9;
char field_18CA;
_BYTE gap18CB[2381];
byte Arr_0x6400[25600];
ushort index;
unsigned __int16 field_861A;
struct S92 S92_;
struct S92 *S92__2;
__int16 Arr_0x884[2180];
__int16 arr_0x884[2180];
byte arr0x220[544];
char field_CC60;
char field_CC61;
unsigned __int16 field_CC62;
unsigned __int16 field_CC64;
unsigned __int16 Index;
};

struct TrafficLigthStruct
{
struct S202 S202_;
char field_180;
char field_181;
char field_182;
char field_183;
char field_184;
char field_185;
_BYTE gap186[10];
unsigned __int16 index;
enum TRAFFIC_PHASE Phase;
char Timer;
};

struct S85
{
char field0;
__declspec(align(4)) char field_4;
char field_5;
char field_6;
char field_7;
char field_8;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
char field_10;
_BYTE gap11[783];
int field_320;
};

struct BaseCar
{
int field;
int field_4;
int field_8;
int field_C;
int count;
int Status;
int field_18;
int field_1C;
struct BaseCar *S82;
int SkipTrains;
int field_28;
__int16 field_2C;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_0;
};

struct Bus
{
char Car1;
char field_1;
char field_2;
char field_3;
__int16 field_4;
char field_6;
char field_7;
int Status;
struct Car *Car_;
void *field_10;
char field_14;
char field_15;
char field_16;
char field_17;
char field_18;
char field_19;
char field_1A;
char field_1B;
char field_1C;
char field_1D;
char field_1E;
char field_1F;
char field_20;
char field_21;
char field_22;
char field_23;
char field_24;
char field_25;
char field_26;
char field_27;
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_33;
char field_34;
char field_35;
char field_36;
char field_37;
void *field_38;
char field_3C;
char field_3D;
char field_3E;
char field_3F;
char field_40;
char field_41;
char field_42;
char field_43;
char field_44;
char field_45;
char field_46;
char field_47;
int field_48;
int field_4C;
int field_50;
char field_54;
char field_55;
char SkipCount;
char field_0;
};

struct PublicTransport
{
struct BaseCar BaseCar_;
struct Bus BUS[10];
struct Bus BusMetrics;
char field_1818;
char field_1819;
char field_181A;
char field_181B;
};

struct Medical
{
char field;
char field_1;
char field_2;
char field_3;
struct S110 *S110_;
struct Ped *Ped_;
int field_C;
struct Passenger Passenger_;
int field_14;
int field_18;
};

struct Ambulance
{
char field_0;
char field_1;
char field_2;
char field_3;
struct Passenger Passenger_;
struct Ped *Ped1;
void *uns;
_BYTE gap14[67];
_BYTE gap57[121];
struct Medical Medical_;
};

struct S374
{
char field_0;
char field_1;
char field_2;
char field_3;
int field_4;
};

struct HudElement
{
int field;
int field_4;
int field_8;
int field_C;
struct Ped *Ped_;
int ID;
int field_18;
__int16 field_1C;
__int16 field_1E;
int field_20;
int field_24;
char field_28;
char field_29;
char field_2A;
char field_2B;
char field_2C;
char field_2D;
char field_2E;
char field_2F;
int field_30;
int field_34;
};

struct Door
{
struct HudElement S76[22];
__int16 field_4D0;
__int16 field_4D2;
};

struct S373
{
char NextElement;
char field_1;
char field_2;
char field_3;
char NextElement1;
char field_5;
char field_6;
char field_7;
char field_8;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
};

struct MenuInfo
{
void *field_0;
char field_4;
char field_5;
char field_6;
char field_7;
char field_8;
char field_9;
char field_A;
char field_B;
char field_C;
char field_D;
char field_E;
char field_F;
struct S373 S373_;
int field_2C0;
};

struct TileAnim
{
char field_0;
char field_1;
};

struct TileAnim2
{
__int16 field;
__int16 field_2;
__int16 field_4;
__int16 field_6;
__int16 field_8;
__int16 field_A;
int field_C;
__int16 field_10;
char TileAnim;
char field_13;
struct TileAnim2 *NextTileAnim2;
};

struct TileAnim1
{
struct TileAnim2 *TileAnim2_;
struct TileAnim2 *NextS71;
struct TileAnim2 TileAnim2_Arr50[50];
__int16 field_4B8;
char field_4BA;
char field_0;
};

struct ScriptThread
{
struct S68_1 field[1];
__declspec(align(4)) char field_4;
char field_5;
char field_6;
char field_7;
char Count;
char field_9;
_BYTE gapA[2029];
char field_0;
};

struct CollisionBox
{
struct EventHandler *FirstElement;
struct EventHandler *pS63;
struct EventHandler S63[3825];
__int16 field_29174;
char field_29176;
char field_0;
};

struct TriggerVolume
{
struct S65 *FirstElement;
struct S65 S65_;
};

struct S67
{
int field;
__int16 field_4;
char field_6;
char field_7;
struct S67 *NextElement;
int field_C;
int field_10;
char field_14;
char field_15;
char field_16;
char field_17;
int field_18;
int field_1C;
int field_20;
int field_24;
__int16 field_28;
__int16 field_2A;
__int16 field_2C;
char field_2E;
char field_2F;
char field_30;
char field_31;
char field_32;
char field_33;
int field_34;
byte field_38;
char field_39;
char field_3A;
char field_0;
};

struct S66
{
struct S67 *FirstElement;
struct S67 S67_;
};

struct S58
{
int field;
int field_4;
int field_8;
int field_C;
int field_10;
int field_14;
int field_18;
__int16 field_1C;
__int16 field_1E;
char field_20;
char field_21;
char field_22;
char field_23;
int field_24;
int field_28;
int field_2C;
int field_30;
int field_34;
int field_38;
int field_3C;
int field_40;
int field_44;
int field_48;
int field_4C;
int field_50;
int field_54;
int field_58;
int field_5C;
char field_60;
byte byte_;
char field_62;
char field_63;
char field_64;
char field_65;
char field_66;
char field_67;
int field_68;
unsigned __int8 field_6C;
char field_6D;
char field_6E;
char field_6F;
int field_70;
};

struct PathNode
{
unsigned __int16 Index;
char field_2;
char field_3;
struct S58 S58_;
byte buffer_0x4B0[1200];
__int16 field_8CA4;
char field_8CA6;
char field_0;
};

struct Collide
{
int Index;
int Index_1;
int field_8;
};

struct PickupInfo
{
struct SpriteS1 *SpriteS1_;
char field_4;
char field_5;
char field_6;
char field_7;
int arr_4095[4095];
char field_4004;
char field_4005;
char field_4006;
char field_4007;
char field_4008;
char field_4009;
char field_400A;
char field_400B;
_BYTE gap400C[16372];
int field_8000;
};

struct PowerUp
{
int field_0;
int field_4;
int field_8;
int Array6000[6000];
_BYTE gap5DCC[47987];
char field_1193F;
int field_11940;
};

struct Checkpoint
{
int field[256];
};

struct PedManager
{
struct Ped *FirstElement;
struct Ped *NextPed;
struct Ped Ped_;
__int16 PedsInUse;
char field_203AA;
char field_203AB;
};

struct PedPool
{
struct GameObject *FirstGameObject;
struct GameObject GameObject_;
};


