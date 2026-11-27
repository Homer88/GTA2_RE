#ifndef __TEXT_H_
#define __TEXT_H_


class Text {
public:
	char Language = 'e';
	char *Base;
	int NumberOfElements;
	Text();
	~Text();
	void Clear();
	void Load();
	void LoadGCI();
	void* Bsearch(const void* pKey);
	wchar_t* ConvertWordsToBig(wchar_t* str);
	wchar_t ConvertToUpper(wchar_t str);
    bool  LanguageJapan();	
};
extern Text* gText;
extern char gLanguage[256];

// RE minimal text draw bridge. Real IDA: DrawGTATextRaw @ 0x4CC100 draws glyph quads via gbh.
// Current build has no gbh text pipeline; these queue ASCII text for main.cpp software overlay.
struct DebugTextCmd {
    char text[128];
    int x;
    int y;
    unsigned short color;
    int style;
};
enum { kMaxDebugTextCmds = 64 };
extern DebugTextCmd gDebugTextCmds[kMaxDebugTextCmds];
extern int gDebugTextCmdCount;
void ClearDebugTextCmds();
void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5);
const char* Text_GetGbhBlockedReason();
unsigned int Text_GetGbhDebugFrame();
unsigned int Text_GetGbhDebugAttempts();
unsigned int Text_GetGbhDebugDraws();
unsigned int Text_GetGbhDebugQuads();
int Text_GetGbhDebugLastFlags();
unsigned int Text_GetGbhDebugLastDiff();
unsigned int Text_GetGbhDebugLastTex();
void Text_GetGbhDebugLastRect(float* x, float* y, float* w, float* h);
void Text_GbhDebugNextFrame();
// Debug-only 9-arg ABI probe for IDA 0x4CC100 (ret 0x24). Logs extra args when GTA2_TEXT_GBH=1;
// delegates to 5-arg guarded path. No default behavior change.
void DrawGTATextRaw_Debug9(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                            unsigned int x6_a5_4, unsigned int x7_a5_8,
                            unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0);
// 9-arg overload matching IDA 0x4CC100 stack tail. Captures ABI9 for guarded FORCE gate, then
// delegates to 5-arg bridge. Safe: no behavior change unless GTA2_TEXT_GBH=1 debug gates.
void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                    unsigned int x6_a5_4, unsigned int x7_a5_8,
                    unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0);
// Debug-only: last seen ABI9 tail args for 0x4CC100 (ret 0x24). Valid only when GTA2_TEXT_GBH=1
// and a call went through DrawGTATextRaw_Debug9/9-arg overload. Not authoritative for 5-arg callsites.
bool Text_GetLastAbi9(unsigned int* a5_4, unsigned int* a5_4_deref, unsigned int* a5_8,
                      unsigned int* a5_12_s202, unsigned int* a5_12_f0, unsigned int* a5_bridge);
// Debug-only: true when the last ABI9 snapshot came from a 9-arg debug/callsite capture,
// not from synthetic/log/sidechannel ingestion. Not a retail proof by itself.
bool Text_WasLastAbi9Callsite();
// Debug-only: capture ABI9 from a real RE callsite that has IDA-visible tail args.
// Gated by GTA2_TEXT_GBH=1 and marks source as callsite(Debug9), not synthetic.
void Text_DebugCaptureAbi9Callsite(unsigned int x6_a5_4, unsigned int x7_a5_8,
                                    unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0,
                                    unsigned int a5_bridge);
// Debug-only: BA2C0-shaped helper capture. Distinct source from dbg9; blocked by default
// unless GTA2_TEXT_GBH_ALLOW_SYNTHETIC_ABI9=1. NOT call-accurate/original 0x4BA2C0 proof.
void Text_DebugCaptureAbi9BA2C0Shape(unsigned int x6_a5_4, unsigned int x7_a5_8,
                                     unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0,
                                     unsigned int a5_bridge);
void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, int a4, int a5); // compat overload
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5); // IDA 0x4539F0
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, int a4, int a5); // compat overload
void DrawGTATextRawMain_Debug9(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                                unsigned int x6_a5_4, unsigned int x7_a5_8,
                                unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0);
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                        unsigned int x6_a5_4, unsigned int x7_a5_8,
                        unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0);
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3); // RE screen-coord bridge
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4); // IDA 0x4C7280 compat (world->screen in original)
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4, int a5); // compat with original 5-arg tail
// Debug-only: IDA 0x4C7280-like ABI9 tail capture with runtime-derived a5. No world->screen port. Not proof.
void DrawGTATextRaw_7280_Debug(wchar_t* a1, int x, int y, unsigned short a4);
// Debug-only faithful tail-shape port of IDA sub_4BA2C0 @ 0x4BA2C0: real stack locals for
// a5_4(var_8==2)/a5_8==0/a5_12==0,0 and runtime-derived a5 from gCameraOrPhysics+0xA8.
// Not a full original callsite port (no Radar world->screen), not retail per-callstack proof.
void DrawGTATextRaw_BA2C0_Debug(wchar_t* a1, int x, int y, unsigned short a4);
// Debug-only closer raw port attempt. Gated+SEH; RE layout uncertain. Not proof.
void DrawGTATextRaw_BA2C0_DebugRaw(wchar_t* a1, int a2, void* a3_radarLike, unsigned short a4);

#endif
