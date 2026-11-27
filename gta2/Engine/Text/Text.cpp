#include "Text.h"
#include "../Registry/Registry.h"
#include <cstring>
#include <cstdlib>
#include <ctime>
#include <sys/stat.h>
#include <search.h>
#include <stdio.h>
#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#endif
#include "../Style/Style.h"
#include "../../Game/CameraOrPhysics/CameraOrPhysics.h"
#include "../../Game/Radar/Radar.h"
extern CameraOrPhysics* gCameraOrPhysics;
extern CameraOrPhysics* gCameraOrPhysics_5E3CC4;
#include "../Style/StyleTileLoader.h"
#include "../TextureManager/TextureManager.h"
#include "../Font/Font.h"
#include "../gbh/gbh.h"
#include "../../../d3ddll/d3ddll.h"
#include "../ultil/WinApi.h"
#include <map>
#include <vector>

Text *gText;
char PartGxt[255];
wchar_t gFontJapan[256] = { 0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87,  0x88, 0x89, 0x8A,
                            0x8B,  0x8C,  0x8D,  0x8E,  0x8F,  0x90,  0x91,  0x92,  0x93, 0x94, 0x95,
                            0x96,  0x80,  0x81,  0x82,  0x83,  0x84,  0x85,  0x86,  0x87, 0x88, 0x89,
                            0x8A,  0x8B,  0x8C,  0x8D,  0x8E,  0x8F,  0x90,  0x91,  0x92, 0x93, 0x94,
                            0x95,  0x0AD, 0x0AF, 0x0B0, 0x0B1, 0x0B2, 0x0B3, 0x0B4,
                            0x0B5, 0x0B6, 0x0B7, 0x0B8, 0x0B9, 0x0BA, 0x0BB, 0x0BC, 0x0BD,
                            0x0BE, 0x0BF, 0x0C0, 0x0C1, 0x0C2, 0x0C3, 0x0C4, 0x0C5, 0x0C6,
                            0x0C7, 0x0C8, 0x0C9, 0x0CA, 0x0CB, 0x0CC, 0x0CD, 0x0CE, 0x0CF,
                            0x0D0, 0x0D1, 0x0D2, 0x0D3, 0x0D4, 0x0D5, 0x0D6, 0x0D7, 0x0D8,
                            0x0D9, 0x0DA, 0x0DB, 0x0DC, 0x0DD, 0x0DE, 0x0DF, 0x0E0, 0x0E1,
                            0x0E2, 0x0E3, 0x0E4, 0x0E5, 0x0E6, 0x0E7, 0x0E8, 0x0E9, 0x0EA,
                            0x0EB, 0x0EC, 0x0ED, 0x0EE, 0x0EF, 0x0F0, 0x0F1, 0x0F2, 0x0F3,
                            0x0F4, 0x0F5, 0x0F6, 0x0F7, 0x0F8, 0x0F9, 0x0FA, 0x0FB, 0x0FC,
                            0x0FD, 0x0FE, 0x0FF, 0x80,  0x81,  0x82,  0x83,  0x84,  0x85, 0x86,
                            0x87,  0x88,  0x89,  0x8A,  0x8B,  0x8C,  0x8D,  0x8E,  0x8F, 0x90, 0x91,
                            0x92,  0x93,  0x94,  0x95,  0x96,  0x41,  0x84,  0x85,  0x45,
                            0x49,  0x4F,  0x55,  0x0AD, 0x0AF,
                            0x0B0, 0x0B1, 0x0B2, 0x0B3, 0x0B4, 0x0B5, 0x0B6, 0x0B7, 0x0B8,
                            0x0B9, 0x0BA, 0x0BB, 0x0BC, 0x0BD, 0x0BE, 0x0BF, 0x0C0, 0x0C1,
                            0x0C2, 0x0C3, 0x0C4, 0x0C5, 0x0C6, 0x0C7, 0x0C8, 0x0C9, 0x0CA,
                            0x0CB, 0x0CC, 0x0CD, 0x0CE, 0x0CF, 0x0D0, 0x0D1, 0x0D2, 0x0D3,
                            0x0D4, 0x0D5, 0x0D6, 0x0D7, 0x0D8, 0x0D9, 0x0DA, 0x0DB, 0x0DC,
                            0x0DD, 0x0DE, 0x0DF, 0x0E0, 0x0E1, 0x0E2, 0x0E3, 0x0E4, 0x0E5,
                            0x0E6, 0x0E7, 0x0E8, 0x0E9, 0x0EA, 0x0EB, 0x0EC, 0x0ED, 0x0EE,
                            0x0EF, 0x0F0, 0x0F1, 0x0F2, 0x0F3, 0x0F4, 0x0F5, 0x0F6, 0x0F7,
                            0x0F8, 0x0F9, 0x0FA, 0x0FB, 0x0FC, 0x0FD, 0x0FE, 0x0FF               };
wchar_t gFontEnglish[256] = { 0 };



int compare_strings(const void* a, const void* b) {
    return strcmp(*(const char**)a, *(const char**)b);
}

void Text::Load() {
    sprintf(PartGxt, "data\\%c.gxt", this->Language);
    this->LoadGCI();
}
void Text::LoadGCI() {

}
void* Text::Bsearch(const void* pKey) {
    wchar_t ** resultat=(wchar_t**)bsearch(pKey, (const char*)this->Base, this->NumberOfElements, 12, compare_strings);
    if (resultat) {
        return resultat;
    }
    else { return " "; }
}
void Text::Clear() {
    this->Base = 0;
    this->NumberOfElements = 0;
}

Text::Text() {
    this->Clear();                       // Base = NULL; Num = 0;
    //AutoClass4::AutoClass4(&this->AutoClass4); //TODO

    gRegistry->GetLanguage("language", gLanguage, 256);

    char lang = (char)gLanguage[0];
    if (lang == 'e' || lang == 'f' || lang == 'g' ||
        lang == 'i' || lang == 's' || lang== 'r' || lang == 'j')
    {
        this->Language = lang;
    }
    else
    {
        this->Language = 'e';                // по умолчанию — английский
    }




    /*
    char gLanguage[256];
    gRegistry->GetLanguage("language", gLanguage, 256);
    if (gLanguage[0] == 'e' ||
        gLanguage[0] == 'f' ||
        gLanguage[0] == 'g' ||
        gLanguage[0] == 'i' ||
        gLanguage[0] == 's' ||
        gLanguage[0] == 'j' ||
        gLanguage[0] == 'r')
        this->Language = gLanguage[0];
    else
        this->Language = 'e';*/
}

Text::~Text() {

}


wchar_t* Text::ConvertWordsToBig(wchar_t* str) {
    for (wchar_t* i = str; *i; ++i) {
        *i = this->ConvertToUpper(*i);
    }
    return L" ";
}


wchar_t Text::ConvertToUpper(wchar_t str) {

    switch (this->Language) {
    case 'e':
        if (str >= 'a' && str <= 'z')
            str=str - 32;
        break;
    case 'f':
        if (str >= 'a' && str <= 'z')
            str = str - 32;
        else  if (str >= 128 && str <= 255)
            str = gFontJapan[str];
        break;
    case 'g':
    case 'i':
    case 's':
        if (str >= 'a' && str <= 'z')
            str = str - 32;
        else if (str >= 128 && str <= 255)
            str = gFontEnglish[str];
        break;
    case 'r':
        if (str >= 'a' && str <= 'z')
            str = str - 32;
        if (str >= 'а' && str <= 'п')
            str = str - 32;
        if (str >= 'р' && str <= 'я')
            str = str - 80;
        if (str >= 'ё' )
            str = 'Ё';
         break;
    default:
        return str;
    }
    return str;
}


bool  Text::LanguageJapan() {
    return false;
}

DebugTextCmd gDebugTextCmds[kMaxDebugTextCmds];
int gDebugTextCmdCount = 0;

void ClearDebugTextCmds() { gDebugTextCmdCount = 0; }

static void AddDebugTextCmd(const char* t, int x, int y, unsigned short color, int style) {
    if (!t || gDebugTextCmdCount >= kMaxDebugTextCmds) return;
    DebugTextCmd& c = gDebugTextCmds[gDebugTextCmdCount++];
    snprintf(c.text, sizeof(c.text), "%s", t);
    c.text[sizeof(c.text)-1] = 0;
    c.x = x; c.y = y; c.color = color; c.style = style;
}

// IDA 0x4CC100 - gbh glyph-quad path. RE: guarded ASCII attempt + software overlay fallback.
// Real path requires confirmed Style layout/TextureManager banks/Float10/Radar/AddX globals.
static char gTextGbhBlocked[160] = "init";

enum TextAbi9Source : unsigned char {
    kAbi9None = 0,
    kAbi9Debug9 = 1,
    kAbi9Sidechannel = 2,
    kAbi9Log = 3,
    kAbi9Synthetic = 4, // debug-only known profile from controlled RE probe wrapper; not call-accurate
    kAbi9BA2C0Shape = 5, // debug-only BA2C0-shaped helper path; NOT original 0x4BA2C0 callsite/callstack proof
};
struct TextAbi9Tail {
    bool valid = false;
    TextAbi9Source source = kAbi9None;
    unsigned int a5_4 = 0;
    unsigned int a5_4_deref = 0;
    unsigned int a5_8 = 0;
    unsigned int a5_12_s202 = 0;
    unsigned int a5_12_f0 = 0;
    unsigned int a5_bridge = 0;
};
static TextAbi9Tail g_lastAbi9;

bool Text_GetLastAbi9(unsigned int* a5_4, unsigned int* a5_4_deref, unsigned int* a5_8,
                      unsigned int* a5_12_s202, unsigned int* a5_12_f0, unsigned int* a5_bridge) {
    if (!g_lastAbi9.valid) return false;
    if (a5_4) *a5_4 = g_lastAbi9.a5_4;
    if (a5_4_deref) *a5_4_deref = g_lastAbi9.a5_4_deref;
    if (a5_8) *a5_8 = g_lastAbi9.a5_8;
    if (a5_12_s202) *a5_12_s202 = g_lastAbi9.a5_12_s202;
    if (a5_12_f0) *a5_12_f0 = g_lastAbi9.a5_12_f0;
    if (a5_bridge) *a5_bridge = g_lastAbi9.a5_bridge;
    return true;
}

bool Text_WasLastAbi9Callsite() {
    return g_lastAbi9.valid && g_lastAbi9.source == kAbi9Debug9;
}

struct GbhDebugDetail {
    unsigned int attempts = 0;
    unsigned int draws = 0;
    unsigned int quads = 0;
    int lastFlags = 0;
    unsigned int lastDiff = 0;
    float lastX = 0, lastY = 0, lastW = 0, lastH = 0;
    unsigned int lastTex = 0;
    unsigned int frame = 0;
};
static GbhDebugDetail g_gbhDebug;

unsigned int Text_GetGbhDebugFrame() { return g_gbhDebug.frame; }
unsigned int Text_GetGbhDebugAttempts() { return g_gbhDebug.attempts; }
unsigned int Text_GetGbhDebugDraws() { return g_gbhDebug.draws; }
unsigned int Text_GetGbhDebugQuads() { return g_gbhDebug.quads; }
int Text_GetGbhDebugLastFlags() { return g_gbhDebug.lastFlags; }
unsigned int Text_GetGbhDebugLastDiff() { return g_gbhDebug.lastDiff; }
unsigned int Text_GetGbhDebugLastTex() { return g_gbhDebug.lastTex; }
void Text_GetGbhDebugLastRect(float* x, float* y, float* w, float* h) {
    if (x) *x = g_gbhDebug.lastX; if (y) *y = g_gbhDebug.lastY;
    if (w) *w = g_gbhDebug.lastW; if (h) *h = g_gbhDebug.lastH;
}
void Text_GbhDebugNextFrame() { g_gbhDebug.frame++; }

static void Text_LogGbhReason(const char* reason) {
    const char* e = std::getenv("GTA2_TEXT_GBH");
    if (!e || e[0] != '1') return;
    if (!reason) reason = "null";
    static char last[160] = "";
    if (std::strncmp(last, reason, sizeof(last)-1) == 0) return;
    std::strncpy(last, reason, sizeof(last)-1); last[sizeof(last)-1] = 0;
    FILE* f = std::fopen("gta2_text_gbh_reason.log", "a");
    if (f) { std::fprintf(f, "%s\n", reason); std::fclose(f); }
}
static void Text_SetGbhBlocked(const char* reason) {
    if (!reason) reason = "unknown";
    std::strncpy(gTextGbhBlocked, reason, sizeof(gTextGbhBlocked)-1);
    gTextGbhBlocked[sizeof(gTextGbhBlocked)-1] = 0;
    Text_LogGbhReason(gTextGbhBlocked);
}
const char* Text_GetGbhBlockedReason() { return gTextGbhBlocked ? gTextGbhBlocked : "unknown"; }

static char gTextGbhExtra9[128] = "extra9=none";
const char* Text_GetGbhExtra9Debug() { return gTextGbhExtra9; }

static void Text_DebugCaptureAbi9Internal(TextAbi9Source source, const char* srcName, const char* blockedReason,
                                           unsigned int x6_a5_4, unsigned int x7_a5_8,
                                           unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0,
                                           unsigned int a5_bridge) {
    const char* forceGbh = std::getenv("GTA2_TEXT_GBH");
    if (!forceGbh || forceGbh[0] != '1') return;
    unsigned int a5_4_val = 0;
    if (x6_a5_4) {
        __try { a5_4_val = *(unsigned int*)x6_a5_4; }
        __except (EXCEPTION_EXECUTE_HANDLER) { a5_4_val = 0xDEADBEEF; }
    }
    g_lastAbi9.valid = true;
    g_lastAbi9.source = source;
    g_lastAbi9.a5_4 = x6_a5_4;
    g_lastAbi9.a5_4_deref = a5_4_val;
    g_lastAbi9.a5_8 = x7_a5_8;
    g_lastAbi9.a5_12_s202 = x8_a5_12_s202;
    g_lastAbi9.a5_12_f0 = x9_a5_12_field0;
    g_lastAbi9.a5_bridge = a5_bridge;
    snprintf(gTextGbhExtra9, sizeof(gTextGbhExtra9),
             "src=%s x6=%08X *=%08X x7=%08X x8=%08X x9=%08X a5=%08X",
             srcName ? srcName : "?", x6_a5_4, a5_4_val, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0, a5_bridge);
    gTextGbhExtra9[sizeof(gTextGbhExtra9)-1] = 0;
    Text_SetGbhBlocked(blockedReason ? blockedReason : "abi9-callsite-unknown");
}

void Text_DebugCaptureAbi9Callsite(unsigned int x6_a5_4, unsigned int x7_a5_8,
                                    unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0,
                                    unsigned int a5_bridge) {
    Text_DebugCaptureAbi9Internal(kAbi9Debug9, "dbg9", "abi9-callsite-dbg9",
                                  x6_a5_4, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0, a5_bridge);
}

void Text_DebugCaptureAbi9BA2C0Shape(unsigned int x6_a5_4, unsigned int x7_a5_8,
                                     unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0,
                                     unsigned int a5_bridge) {
    // Debug-only: BA2C0-shaped helper path. NOT original 0x4BA2C0 callsite/callstack proof.
    Text_DebugCaptureAbi9Internal(kAbi9BA2C0Shape, "ba2c0-shape", "abi9-callsite-ba2c0-shape",
                                  x6_a5_4, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0, a5_bridge);
}

struct Gta2Abi9SidechannelView {
    volatile LONG seq;
    DWORD caller;
    DWORD a1, a2, a3, a4, a5;
    DWORD a5_4, a5_4_deref, a5_8, a5_12_s202, a5_12_f0;
    DWORD tick;
};

static bool Text_TryConsumeAbi9Sidechannel() {
#ifdef _WIN32
    // Debug-only, best-effort. Requires dllLoad hook publishing Local\\GTA2_TEXT_ABI9_V1 when GTA2_TEXT_GBH=1.
    static HANDLE s_map = NULL;
    static Gta2Abi9SidechannelView* s_view = NULL;
    static LONG s_lastSeq = 0;
    if (!s_map) {
        s_map = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\GTA2_TEXT_ABI9_V1");
        if (s_map) s_view = (Gta2Abi9SidechannelView*)MapViewOfFile(s_map, FILE_MAP_READ, 0, 0, sizeof(Gta2Abi9SidechannelView));
        else {
            // Debug-only: optionally load dllLoad for ABI9 sidechannel in RE builds where it's not auto-loaded.
            // Gated by GTA2_TEXT_GBH_LOAD_DLLLOAD=1; no behavior change otherwise.
            static bool triedLoad = false;
            const char* loadEnv = std::getenv("GTA2_TEXT_GBH_LOAD_DLLLOAD");
            if (!triedLoad && loadEnv && loadEnv[0] == '1') {
                triedLoad = true;
                HMODULE hm = LoadLibraryA("abi9pub.dll");
                if (!hm) hm = LoadLibraryA("gta2-resurection.dll");
                if (!hm) hm = LoadLibraryA("dllLoad.dll");
                static char s_loadMsg[96];
                if (hm) snprintf(s_loadMsg, sizeof(s_loadMsg), "abi9-dllload-loaded=%p", (void*)hm);
                else snprintf(s_loadMsg, sizeof(s_loadMsg), "abi9-dllload-load-failed=%lu", (unsigned long)GetLastError());
                s_loadMsg[sizeof(s_loadMsg)-1] = 0;
                Text_SetGbhBlocked(s_loadMsg);
                s_map = OpenFileMappingA(FILE_MAP_READ, FALSE, "Local\\GTA2_TEXT_ABI9_V1");
                if (s_map) s_view = (Gta2Abi9SidechannelView*)MapViewOfFile(s_map, FILE_MAP_READ, 0, 0, sizeof(Gta2Abi9SidechannelView));
            } else {
                static bool once=false; if(!once){once=true; Text_SetGbhBlocked("abi9-sidechannel-no-map");}
            }
        }
    }
    if (!s_view) return false;
    for (int tries = 0; tries < 3; ++tries) {
        LONG seq1 = InterlockedCompareExchange((volatile LONG*)&s_view->seq, 0, 0);
        if (seq1 <= 0 || (seq1 & 1) != 0) return false; // no data or writer in progress
        Gta2Abi9SidechannelView snap = *s_view;
        LONG seq2 = InterlockedCompareExchange((volatile LONG*)&s_view->seq, 0, 0);
        if (seq1 != seq2 || (seq2 & 1) != 0) continue;
        if (snap.seq == s_lastSeq) return false; // already consumed
        DWORD ageMs = GetTickCount() - snap.tick;
        if (ageMs > 3000u) { s_lastSeq = snap.seq; Text_SetGbhBlocked("abi9-sidechannel-stale"); return false; }
        s_lastSeq = snap.seq;
        g_lastAbi9.valid = true;
        g_lastAbi9.source = kAbi9Sidechannel;
        g_lastAbi9.a5_4 = snap.a5_4;
        g_lastAbi9.a5_4_deref = snap.a5_4_deref;
        g_lastAbi9.a5_8 = snap.a5_8;
        g_lastAbi9.a5_12_s202 = snap.a5_12_s202;
        g_lastAbi9.a5_12_f0 = snap.a5_12_f0;
        g_lastAbi9.a5_bridge = snap.a5;
        static char s_reason[128];
        snprintf(s_reason, sizeof(s_reason), "abi9-sidechannel seq=%08lX", (unsigned long)snap.seq);
        s_reason[sizeof(s_reason)-1] = 0;
        Text_SetGbhBlocked(s_reason);
        return true;
    }
    return false;
#else
    return false;
#endif
}

static bool Text_TryIngestAbi9FromLog() {
    // Debug-only bridge: dllLoad HookDrawGTATextRaw logs ABI9 tuples to gta2_text_abi.log in same process cwd.
    // This is best-effort diagnostics, not authoritative ABI proof. Gated by env.
    const char* env = std::getenv("GTA2_TEXT_GBH_ABI9_FROM_LOG");
    if (!env || env[0] != '1') return false;
    struct _stat st;
    if (_stat("gta2_text_abi.log", &st) != 0) return false;
    // Require recent log to avoid stale-file false authorization. 120s window for smoke/debug.
    std::time_t now = std::time(nullptr);
    if (st.st_mtime <= 0 || (now - st.st_mtime) > 120) {
        Text_SetGbhBlocked("abi9-log-stale");
        return false;
    }
    FILE* f = std::fopen("gta2_text_abi.log", "rb");
    if (!f) return false;
    if (std::fseek(f, 0, SEEK_END) != 0) { std::fclose(f); return false; }
    long sz = std::ftell(f);
    if (sz <= 0) { std::fclose(f); return false; }
    long start = sz > 4096 ? sz - 4096 : 0;
    std::fseek(f, start, SEEK_SET);
    std::vector<char> buf((size_t)(sz - start) + 1, 0);
    size_t n = std::fread(buf.data(), 1, buf.size() - 1, f);
    std::fclose(f);
    buf[n] = 0;
    // Find last line starting with "ABI9 "
    const char* last = nullptr;
    for (const char* p = buf.data(); *p; ++p) {
        if ((p == buf.data() || p[-1] == '\n') && std::strncmp(p, "ABI9 ", 5) == 0) last = p;
    }
    if (!last) return false;
    unsigned int a5_4 = 0, a5_4_deref = 0, a5_8 = 0, s202 = 0, f0 = 0;
    // Expected: ... a5_4=0019FD70 *a5_4=00000002 a5_8=00000000 a5_12.S202=00000000 a5_12.f0=00000000
    const char* pA54 = std::strstr(last, "a5_4=");
    const char* pD = std::strstr(last, "*a5_4=");
    const char* pA58 = std::strstr(last, "a5_8=");
    const char* pS = std::strstr(last, "a5_12.S202=");
    const char* pF = std::strstr(last, "a5_12.f0=");
    if (!pA54 || !pD || !pA58 || !pS || !pF) return false;
    if (std::sscanf(pA54, "a5_4=%x", &a5_4) != 1) return false;
    if (std::sscanf(pD, "*a5_4=%x", &a5_4_deref) != 1) return false;
    if (std::sscanf(pA58, "a5_8=%x", &a5_8) != 1) return false;
    if (std::sscanf(pS, "a5_12.S202=%x", &s202) != 1) return false;
    if (std::sscanf(pF, "a5_12.f0=%x", &f0) != 1) return false;
    g_lastAbi9.valid = true;
    g_lastAbi9.source = kAbi9Log;
    g_lastAbi9.a5_4 = a5_4;
    g_lastAbi9.a5_4_deref = a5_4_deref;
    g_lastAbi9.a5_8 = a5_8;
    g_lastAbi9.a5_12_s202 = s202;
    g_lastAbi9.a5_12_f0 = f0;
    g_lastAbi9.a5_bridge = 0;
    Text_SetGbhBlocked("abi9-ingested-log");
    return true;
}

static void Text_CaptureAbi9Tail(unsigned int x6_a5_4, unsigned int x7_a5_8,
                                  unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0,
                                  unsigned int a5_bridge, TextAbi9Source source = kAbi9Debug9) {
    unsigned int a5_4_val = 0;
    if (x6_a5_4) {
        __try { a5_4_val = *(unsigned int*)x6_a5_4; }
        __except (EXCEPTION_EXECUTE_HANDLER) { a5_4_val = 0xDEADBEEF; }
    }
    g_lastAbi9.valid = true;
    g_lastAbi9.source = source;
    g_lastAbi9.a5_4 = x6_a5_4;
    g_lastAbi9.a5_4_deref = a5_4_val;
    g_lastAbi9.a5_8 = x7_a5_8;
    g_lastAbi9.a5_12_s202 = x8_a5_12_s202;
    g_lastAbi9.a5_12_f0 = x9_a5_12_field0;
    g_lastAbi9.a5_bridge = a5_bridge;
    const char* srcName = (source == kAbi9Synthetic) ? "syn" :
                          (source == kAbi9Sidechannel) ? "sch" :
                          (source == kAbi9Log) ? "log" :
                          (source == kAbi9BA2C0Shape) ? "ba2c0-shape" :
                          (source == kAbi9Debug9) ? "dbg9" : "none";
    snprintf(gTextGbhExtra9, sizeof(gTextGbhExtra9),
             "src=%s x6=%08X *=%08X x7=%08X x8=%08X x9=%08X a5=%08X",
             srcName, x6_a5_4, a5_4_val, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0, a5_bridge);
    gTextGbhExtra9[sizeof(gTextGbhExtra9)-1] = 0;
}

void DrawGTATextRaw_Debug9(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                            unsigned int x6_a5_4, unsigned int x7_a5_8,
                            unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0) {
    // Debug-only ABI probe. IDA 0x4CC100: ret 0x24, extra stack args a5_4(ptr),a5_8(int),a5_12(S202).
    // a1a toggles between *a5_4 and 8; a5_12.field_0 toggles between v7(a5_8) and 0.
    // We only log when GTA2_TEXT_GBH=1; never alter default rendering.
    const char* forceGbh = std::getenv("GTA2_TEXT_GBH");
    if (forceGbh && forceGbh[0] == '1') {
        Text_CaptureAbi9Tail(x6_a5_4, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0, (unsigned int)a5);
        // If we see confirmed ASCII-safe extra args, report in reason; still no real draw.
        static char s_reason[160];
        snprintf(s_reason, sizeof(s_reason), "abi9 %s", gTextGbhExtra9);
        s_reason[sizeof(s_reason)-1] = 0;
        Text_SetGbhBlocked(s_reason);
    }
    DrawGTATextRaw(a1, arg4, arg8, a4, a5);
}

void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                    unsigned int x6_a5_4, unsigned int x7_a5_8,
                    unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0) {
    // 9-arg overload for IDA 0x4CC100 tail. Capture ABI9 only in debug GBH mode, so normal
    // callers/behavior stay unchanged unless GTA2_TEXT_GBH=1 gates are active.
    const char* forceGbh = std::getenv("GTA2_TEXT_GBH");
    if (forceGbh && forceGbh[0] == '1') {
        // Default 9-arg captures are debug-only ABI probes; mark as dbg9.
        // Real/original 0x4BA2C0-shaped capture should go through explicit debug helper with distinct source.
        Text_CaptureAbi9Tail(x6_a5_4, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0, (unsigned int)a5, kAbi9Debug9);
        static char s_reason[160];
        snprintf(s_reason, sizeof(s_reason), "abi9-ov %s", gTextGbhExtra9);
        s_reason[sizeof(s_reason)-1] = 0;
        Text_SetGbhBlocked(s_reason);
    }
    DrawGTATextRaw(a1, arg4, arg8, a4, a5);
}

static char s_chainDetail[128] = "";
static bool Text_ProbeGbhAsciiChain(wchar_t* a1, unsigned short styleId, int* outOk, int* outTotal, bool* outHasToggle) {
    // Debug-only probe for IDA 0x4CC100 ASCII non-kanji glyph chain. No gbh_DrawQuad.
    // Confirms Style glyph chain only; TM-owned real handle is probed separately under GTA2_TEXT_GBH_DRAW.
    s_chainDetail[0] = 0;
    if (outOk) *outOk = 0;
    if (outTotal) *outTotal = 0;
    if (outHasToggle) *outHasToggle = false;
    if (!a1 || !gStyle) { snprintf(s_chainDetail,sizeof(s_chainDetail),"no-style a1=%p gs=%p", (void*)a1,(void*)gStyle); return false; }
    int ok = 0, total = 0;
    for (int i = 0; a1[i] && total < 32; ++i) {
        wchar_t wc = a1[i];
        if (wc == L'\n' || wc == L' ') continue;
        if (wc == L'#') { if (outHasToggle) *outHasToggle = true; continue; }
        if (wc < 33 || wc > 126) continue; // non-ASCII/non-kanji subset only
        ++total;
        unsigned short ch = (unsigned short)(wc - 33);
        short spriteId = gStyle->GetSpriteID(styleId, (short)ch);
        unsigned short base = gStyle->GetBaseIndex(7, spriteId);
        int spr = gStyle->GetSprite(base);
        if (spr != 0) ++ok;
        else if (s_chainDetail[0] == 0) {
            char c = (wc >= 32 && wc < 127) ? (char)wc : '?';
            snprintf(s_chainDetail, sizeof(s_chainDetail), "miss st=%u wc=%c sid=%d base=%u spr=0", (unsigned)styleId, c, (int)spriteId, (unsigned)base);
        }
    }
    if (outOk) *outOk = ok;
    if (outTotal) *outTotal = total;
    if (total == 0) snprintf(s_chainDetail,sizeof(s_chainDetail),"no-ascii st=%u", (unsigned)styleId);
    return total > 0 && ok == total;
}

struct GbhFontTexCache {
    bool inited = false;
    bool failed = false;
    GbhApi api;
    std::map<unsigned int, gbh_Texture*> texBySprite; // key: sprite base index
};

static GbhFontTexCache& Text_GetGbhFontCache() {
    static GbhFontTexCache c;
    return c;
}

struct TextPaletteModeDebug {
    int flags;           // IDA return: gTimeDayAndNight|mode bits (0x80/8576/8832) or 0
    std::uint32_t diff;  // vert diff for modes 1/2: (a1<<27)|0xFFFFFF; mode 0 leaves diff unchanged in IDA
    bool hasDiff;
};

static TextPaletteModeDebug Text_SetPaletteModeDebug(unsigned char a1, int a2) {
    // IDA 0x4CB050 (Lighting::SetPaletteMode). Guarded debug approximation.
    // Original writes diff into glyph vert globals unk_673400/420/440/460 for modes 1/2.
    extern int gTimeDayAndNight;
    TextPaletteModeDebug r{0, 0x00FFFFFFu, false};
    if (a2 == 0) { r.flags = gTimeDayAndNight | 0x80; return r; }
    if (a2 == 1 || a2 == 2) {
        r.diff = ((std::uint32_t)a1 << 27) | 0x00FFFFFFu;
        r.hasDiff = true;
        r.flags = gTimeDayAndNight | (a2 == 1 ? 8576 : 8832);
        return r;
    }
    return r;
}

static int Text_GbhRegisterPhysPaletteDebug(GbhApi& api, unsigned int physIdx) {
    // Debug-only. IDA: TextureManagerRegisterPalitre registers ColourBank per physical palette;
    // gbh_RegisterPalette(palId, pData) reads/writes 256 entries at stride 64 DWORDs and MUTATES buffer.
    // StyleTiles_GetPhysPalette returns pageBase+inPage*4 pointer matching PPAL strided layout.
    static int s_slotByPhys[4096];
    static bool s_slotInit = false;
    static int s_nextSlot = 900; // reserved high slots, avoid colliding with game low slots
    if (!s_slotInit) { for (int i = 0; i < 4096; ++i) s_slotByPhys[i] = -1; s_slotInit = true; }
    if (physIdx >= 4096u) return -1;
    if (s_slotByPhys[physIdx] >= 0) return s_slotByPhys[physIdx];
    if (s_nextSlot > 1023) { Text_SetGbhBlocked("gbh-pal-slots-exhausted"); return -1; }
    const StyleTileAssets* sta = StyleTiles_Get();
    if (!sta || !sta->loaded) { Text_SetGbhBlocked("gbh-pal-no-style"); return -1; }

    const unsigned char* palPtr = StyleTiles_GetPhysPalette(physIdx);
    if (!palPtr) { Text_SetGbhBlocked("gbh-pal-ptr-miss"); return -1; }
    // Copy strided column: 256 colors * 64 DWORD stride = 64KB window. RegisterPalette mutates it.
    std::vector<unsigned long> buf(256u * 64u, 0);
    for (int i = 0; i < 256; ++i) {
        // StyleTiles_GetPhysPalette returns base at color0 for this palette; color i is +i*64*4.
        const unsigned char* src = palPtr + (size_t)i * 64u * 4u;
        // Bounds: palPtr is inside ppal page; ensure within ppalBytes.
        size_t off = (size_t)(src - sta->ppal);
        if (off + 4u <= sta->ppalBytes) {
            std::memcpy(&buf[(size_t)i * 64u], src, 4u);
        }
    }
    if (!api.RegisterPalette) return -1;
    int slot = s_nextSlot++;
    api.RegisterPalette(slot, &buf[0]);
    s_slotByPhys[physIdx] = slot;
    return slot;
}

static gbh_Texture* Text_GetOrCreateDebugSolidTexture(GbhApi& api) {
    // Debug-only known-good probe texture: 16x16, all pixels index 1, palette index 1 = white.
    // Used only when GTA2_TEXT_GBH_DRAW_DEBUG_SOLID=1 to validate gbh_DrawQuad/render path visibility.
    static gbh_Texture* s_tex = nullptr;
    static bool s_failed = false;
    if (s_tex || s_failed) return s_tex;
    static unsigned char s_pixels[16 * 16];
    for (int i = 0; i < 16 * 16; ++i) s_pixels[i] = 1;
    static unsigned long s_pal[256 * 64];
    std::memset(s_pal, 0, sizeof(s_pal));
    // gbh_RegisterPalette reads 256 entries at stride 64 DWORDs and mutates buffer.
    // Fill index 1 with opaque white in low 32 bits (common ARGB/XRGB slot used by d3ddll).
    s_pal[1 * 64] = 0xFFFFFFFFu;
    s_pal[0 * 64] = 0x00000000u;
    static int s_palSlot = -1;
    if (s_palSlot < 0) {
        if (!api.RegisterPalette) { s_failed = true; Text_SetGbhBlocked("dbg-solid-no-regpal"); return nullptr; }
        s_palSlot = 970; // reserved debug slot
        api.RegisterPalette(s_palSlot, &s_pal[0]);
    }
    if (!api.RegisterTexture) { s_failed = true; Text_SetGbhBlocked("dbg-solid-no-regtex"); return nullptr; }
    s_tex = api.RegisterTexture(16, 16, s_pixels, s_palSlot, 0);
    if (!s_tex) { s_failed = true; Text_SetGbhBlocked("dbg-solid-regtex-null"); return nullptr; }
    if (api.AssignPalette) api.AssignPalette(s_tex, s_palSlot);
    if (api.LockTexture) api.LockTexture(s_tex);
    if (api.UnlockTexture) api.UnlockTexture(s_tex);
    Text_SetGbhBlocked("dbg-solid-tex-ok");
    return s_tex;
}

static gbh_Texture* Text_GetOrCreateGbhFontTexture(unsigned short fontStyle, unsigned short glyphCharMinus33) {
    // Debug-only, GTA2_TEXT_GBH_DRAW=1 path only. Creates real gbh_Texture* via gbh_RegisterTexture.
    // Bypasses full TextureManager/PacketInfo/S89 pipeline; narrow ASCII probe only.
    GbhFontTexCache& c = Text_GetGbhFontCache();
    if (c.failed) return nullptr;
    if (!c.inited) {
        c.inited = true;
        c.api = Gbh_TryGetLoadedApi();
        if (!c.api.loaded || !c.api.RegisterTexture) { c.failed = true; return nullptr; }
    }
    if (!gStyle) return nullptr;
    short spriteId = gStyle->GetSpriteID(fontStyle, (short)glyphCharMinus33);
    unsigned short base = gStyle->GetBaseIndex(7, spriteId);
    if (base == 0) return nullptr;
    auto it = c.texBySprite.find(base);
    if (it != c.texBySprite.end()) return it->second;

    int spr = gStyle->GetSprite(base);
    if (spr == 0) return nullptr;
    unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
    unsigned char w = sp[4];
    unsigned char h = sp[5];
    unsigned char* data = reinterpret_cast<unsigned char*>(*reinterpret_cast<unsigned int*>(sp + 0)); // IDA: *(_DWORD*)Sprite
    if (!data || w == 0 || h == 0) return nullptr;

    // IDA PacketInfo::LoadPalettedTextures for font bank 7 (Setup 6,7): uses get_global_palette_id(gStyle, field_C==7, v5)
    // then GetPhysPalette. For glyph probe, palette index semantics not fully confirmed; try global palette id 0 as safe debug.
    // TODO: confirm exact palette from Style field_C/field_18 and glyph remap.
    unsigned short globalPal = (unsigned short)gStyle->get_global_palette_id(7, 0);
    short physPal = gStyle->GetPhysPalette(globalPal);
    int palSlot = Text_GbhRegisterPhysPaletteDebug(c.api, (unsigned int)(unsigned short)physPal);
    if (palSlot < 0) { if (gTextGbhBlocked[0] == 0) Text_SetGbhBlocked("gbh-pal-reg-fail"); return nullptr; }

    gbh_Texture* tex = c.api.RegisterTexture((short)w, (short)h, data, palSlot, 0);
    if (!tex) { Text_SetGbhBlocked("gbh-regtex-null"); return nullptr; }
    c.texBySprite[base] = tex;
    return tex;
}

static bool Text_TryDrawGbhAscii(wchar_t* a1, int arg4, int arg8, unsigned short a4, int /*a5*/) {
    // Narrow guarded ASCII non-kanji subset of IDA 0x4CC100. Default off.
    // Hard gates: GTA2_TEXT_GBH_DRAW=1, gbh exports loaded, TM-backed font-bank7 real handle.
    // Confirmed from IDA 0x4CC100: '#' toggles (a1a,a5_12.field_0) between (*a5_4,v7) and (8,0).
    // Unconfirmed in RE: a5_4/v7 source contract, nonzero a1a semantics, SetPaletteMode global diff,
    // SpriteS1/Radar/Point2D/Float10/AddX transforms, kanji/FileMgr, full TM/PacketInfo ownership.
    // Uses screen-space quad approximation (NOT IDA transform). Any doubt => false.
    const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
    if (!drawEnv || drawEnv[0] != '1') { Text_SetGbhBlocked("gbh-draw-env-off"); return false; }
    if (!a1 || !gStyle || !gTextureManager) { Text_SetGbhBlocked("gbh-draw-no-style/tm"); return false; }
    for (int i = 0; a1[i]; ++i) {
        if (a1[i] == L'#') { Text_SetGbhBlocked("gbh-draw-has-toggle-unsupported"); return false; }
    }
    GbhApi api = Gbh_TryGetLoadedApi();
    if (!api.loaded || !api.DrawQuad) { Text_SetGbhBlocked("gbh-api-miss"); return false; }

    union { std::uint32_t u; float f; } zbits; zbits.u = 953267991u;
    int x = arg4;
    int y = arg8;
    bool drewAny = false;
    gbh_VertRaw verts[4];

    for (int i = 0; a1[i]; ++i) {
        wchar_t wc = a1[i];
        if (wc == L'\n') { y += 16; x = arg4; continue; }
        if (wc == L'#') { continue; }
        if (wc == L' ') { x += 8; continue; }
        if (wc < 33 || wc > 126) { x += 8; continue; }

        unsigned short ch = (unsigned short)(wc - 33);
        short spriteId = gStyle->GetSpriteID(a4, (short)ch);
        unsigned short base = gStyle->GetBaseIndex(7, spriteId);
        int spr = gStyle->GetSprite(base);
        if (spr == 0) { Text_SetGbhBlocked("glyph-sprite-miss"); return false; }
        // Prefer TM debug path for real gbh_Texture*. Observed EU ABI: a1a/*a5_4==2 (bank2/GetStyleTexture S89[0]).
    // Debug-only solid texture probe bypasses style/TM glyph chain to validate render visibility.
    int bank2Tex = GetTexture(gTextureManager, 7, spriteId, 2, 0);
    gbh_Texture* tex = nullptr;
    int usedBank = 0;
    const char* dbgSolid = std::getenv("GTA2_TEXT_GBH_DRAW_DEBUG_SOLID");
    if (dbgSolid && dbgSolid[0] == '1') {
        tex = Text_GetOrCreateDebugSolidTexture(api);
        usedBank = 99;
    } else if (bank2Tex != 0) { tex = (gbh_Texture*)(uintptr_t)(unsigned int)bank2Tex; usedBank = 2; }
    else {
        tex = (gbh_Texture*)gTextureManager->GetDebugGbhFontTexture(7, spriteId, 7, 0);
        if (tex) usedBank = 7;
    }
    if (!tex) {
        static char s_texMiss[128];
        const char* r = gTextureManager->GetDebugFontS89Bank7().reason;
        const char* r2 = gTextureManager->GetDebugBank2Style().reason;
        snprintf(s_texMiss, sizeof(s_texMiss), "tex-miss sid=%u base=%u b2=%s b7=%s gbh=%s",
                 (unsigned)(unsigned short)spriteId, (unsigned)base, (r2&&*r2)?r2:"?", (r && *r) ? r : "unknown", Gbh_GetLastError());
        s_texMiss[sizeof(s_texMiss)-1] = 0;
        Text_SetGbhBlocked(s_texMiss);
        return false;
    }

        unsigned char* sp = reinterpret_cast<unsigned char*>(spr);
        float w = (float)(sp[4] ? sp[4] : 8);
        float h = (float)(sp[5] ? sp[5] : 8);
        float uMax = w - 0.000099999997f;
        float vMax = h - 0.000099999997f;
        // IDA 0x4CB050: sets vert diff to (a1<<27)|0xFFFFFF for modes 1/2; returns gTimeDayAndNight|flags.
        // We don't have glyph vert globals; apply diff directly and use flags in DrawQuad.
        // TODO: derive palMode/a1 from real text kind/color mode (a5_12 in 0x4CC100).
        TextPaletteModeDebug pm = Text_SetPaletteModeDebug(0, 1);
        int modeFlags = pm.flags;
        std::uint32_t diff = pm.hasDiff ? pm.diff : 0x00FFFFFFu;
        const char* dbgQuad = std::getenv("GTA2_TEXT_GBH_DRAW_DEBUG_QUAD");
        const char* dbgDiff = std::getenv("GTA2_TEXT_GBH_DRAW_DEBUG_DIFF");
        const char* dbgFlags = std::getenv("GTA2_TEXT_GBH_DRAW_DEBUG_FLAGS");
        if (dbgDiff && dbgDiff[0] == '1') diff = 0xFFFFFFFFu; // debug-only visibility probe
        float fx = (float)x, fy = (float)y;
        float qw = w, qh = h;
        float dbgZ = zbits.f;
        if (dbgQuad && dbgQuad[0] == '1') {
            fx = 100.0f; fy = 100.0f; qw = 200.0f; qh = 50.0f; dbgZ = 0.5f;
            // UVs are in texture-pixel space; gbh_DrawQuad multiplies by cache field_C (1/width).
            // d3ddll Texture layout: +14 Width(u16), +16 Height(u16).
            unsigned char* tb = (unsigned char*)tex;
            unsigned short tw = tb ? *(unsigned short*)(tb + 14) : 0;
            unsigned short th = tb ? *(unsigned short*)(tb + 16) : 0;
            if (tw > 0 && th > 0) { uMax = (float)tw - 0.000099999997f; vMax = (float)th - 0.000099999997f; }
            else { uMax = 63.5f; vMax = 63.5f; }
        }

        verts[0] = {fx, fy, dbgZ, 1.0f, diff, 0, 0.0f, 0.0f};
        verts[1] = {fx + qw, fy, dbgZ, 1.0f, diff, 0, uMax, 0.0f};
        verts[2] = {fx + qw, fy + qh, dbgZ, 1.0f, diff, 0, uMax, vMax};
        verts[3] = {fx, fy + qh, dbgZ, 1.0f, diff, 0, 0.0f, vMax};

        // IDA: gbh_DrawQuad(v24.Ped | 0x20000, Filed_14, &flt_6733F0, 255)
        // SAFETY: real gbh_Texture* from gbh_RegisterTexture, palette registered in reserved slot copy.
        // Still unconfirmed: a1a/a5 palette select, Lighting diff/flags, transform/coord/w/spec, TM/PacketInfo.
        // Only call gbh_DrawQuad with explicit GTA2_TEXT_GBH_DRAW_FORCE=1.
        int drawFlags = (modeFlags | 0x20000);
        if (dbgFlags && dbgFlags[0] == '1') drawFlags = 0x20000; // debug-only: isolate mode bits
        const char* forceDraw = std::getenv("GTA2_TEXT_GBH_DRAW_FORCE");
        if (!forceDraw || forceDraw[0] != '1') {
            char buf[160];
            snprintf(buf, sizeof(buf), "gbh-bank%d-ok-draw-blocked a5=%d pal=%u pm=%d gbh=%s mod=%s",
                     usedBank, 0, 0u, modeFlags, Gbh_GetLastError(), Gbh_GetModulePath());
            static char s_block[160];
            std::memcpy(s_block, buf, sizeof(s_block));
            s_block[sizeof(s_block)-1] = 0;
            Text_SetGbhBlocked(s_block);
            return false;
        }
        // Guard against dual GBH state: RE temp buildsrc statically links D3DDLL.lib.
        // Any module-resolved GBH API (ok-module / ok-debug-loadlibrary) may use different
        // state than the static-linked renderer. Block FORCE unless explicitly allowed.
        const char* gbhErr = Gbh_GetLastError();
        if (gbhErr && std::strcmp(gbhErr, "ok-static") != 0) {
            const char* allowDual = std::getenv("GTA2_TEXT_GBH_ALLOW_DUAL_STATE");
            if (!allowDual || allowDual[0] != '1') {
                static char s_dual[160];
                snprintf(s_dual, sizeof(s_dual), "gbh-force-blocked-dual-state gbh=%s mod=%s", gbhErr ? gbhErr : "?", Gbh_GetModulePath());
                s_dual[sizeof(s_dual)-1] = 0;
                Text_SetGbhBlocked(s_dual);
                return false;
            }
        }
        Text_SetGbhBlocked("gbh-draw-force-calling");
        g_gbhDebug.attempts++;
        g_gbhDebug.lastFlags = drawFlags;
        g_gbhDebug.lastDiff = diff;
        g_gbhDebug.lastX = fx; g_gbhDebug.lastY = fy; g_gbhDebug.lastW = qw; g_gbhDebug.lastH = qh;
        g_gbhDebug.lastTex = (unsigned int)(uintptr_t)tex;
        {
            unsigned char* tb = (unsigned char*)tex;
            unsigned int texSig = tb ? ((unsigned int)tb[0] | ((unsigned int)tb[1] << 8) | ((unsigned int)tb[2] << 16) | ((unsigned int)tb[3] << 24)) : 0; // ID,field_2
            unsigned short ttw = tb ? *(unsigned short*)(tb + 14) : 0; // Width
            unsigned short tth = tb ? *(unsigned short*)(tb + 16) : 0; // Height
            unsigned int palData = tb ? *(unsigned int*)(tb + 24) : 0;      // Texture::pPaltData
            unsigned int nextCache = tb ? *(unsigned int*)(tb + 28) : 0;    // Texture::NextCache
            unsigned int palValid = tb ? (unsigned int)tb[18] : 0;
            unsigned int flagsB = tb ? (unsigned int)tb[19] : 0;
            unsigned int locked = tb ? *(unsigned int*)(tb + 8) : 0;        // Texture::pLockedPixels
            unsigned int orig = tb ? *(unsigned int*)(tb + 20) : 0;         // Texture::pOriginalPixelData
            static char s_draw[512];
            snprintf(s_draw, sizeof(s_draw),
                     "gbh-draw-call f=%u a=%u q=%u flags=0x%X diff=0x%08X tex=%08X sig=%08X x=%.1f y=%.1f w=%.1f h=%.1f z=%.6f tw=%u th=%u uv=%.2f,%.2f pv=%u pd=%08X nc=%08X fl=%u lk=%08X og=%08X bk=%d st=%u sid=%u base=%u g=%u",
                     g_gbhDebug.frame, g_gbhDebug.attempts, g_gbhDebug.quads, drawFlags, diff,
                     g_gbhDebug.lastTex, texSig, fx, fy, qw, qh, dbgZ, (unsigned)ttw, (unsigned)tth, uMax, vMax,
                     palValid, palData, nextCache, flagsB, locked, orig, usedBank, (unsigned)a4, (unsigned)(unsigned short)spriteId, (unsigned)base, (unsigned)ch);
            s_draw[sizeof(s_draw)-1] = 0;
            Text_LogGbhReason(s_draw);
        }

        // Debug-only: dump drawn texture pixels as grayscale BMP for identity proof.
        // Gated by GTA2_TEXT_GBH_DUMP_TEX=1. Optional filters: GTA2_TEXT_GBH_DUMP_TEX_TW/TH/SID,
        // GTA2_TEXT_GBH_DUMP_TEX_MAX (default 1). Writes gta2_text_gbh_texdump_<n>_sid<sid>_<tw>x<th>.bmp in cwd.
        {
            const char* dumpEnv = std::getenv("GTA2_TEXT_GBH_DUMP_TEX");
            if (dumpEnv && dumpEnv[0] == '1') {
                static int s_dumpedCount = 0;
                const char* maxEnv = std::getenv("GTA2_TEXT_GBH_DUMP_TEX_MAX");
                int maxDump = 1;
                if (maxEnv && maxEnv[0]) { int v = std::atoi(maxEnv); if (v > 0 && v <= 64) maxDump = v; }
                if (s_dumpedCount < maxDump) {
                    unsigned char* tb = (unsigned char*)tex;
                    unsigned short tw = tb ? *(unsigned short*)(tb + 14) : 0;
                    unsigned short th = tb ? *(unsigned short*)(tb + 16) : 0;
                    const char* twEnv = std::getenv("GTA2_TEXT_GBH_DUMP_TEX_TW");
                    const char* thEnv = std::getenv("GTA2_TEXT_GBH_DUMP_TEX_TH");
                    const char* sidEnv = std::getenv("GTA2_TEXT_GBH_DUMP_TEX_SID");
                    bool match = true;
                    if (twEnv && twEnv[0] && (int)tw != std::atoi(twEnv)) match = false;
                    if (thEnv && thEnv[0] && (int)th != std::atoi(thEnv)) match = false;
                    if (sidEnv && sidEnv[0] && (int)(unsigned short)spriteId != std::atoi(sidEnv)) match = false;
                    if (match) {
                        unsigned char* pixels = tb ? *(unsigned char**)(tb + 20) : nullptr; // pOriginalPixelData
                        bool lockedHere = false;
                        if (!pixels && api.LockTexture) {
                            api.LockTexture(tex);
                            lockedHere = true;
                            pixels = tb ? *(unsigned char**)(tb + 8) : nullptr; // pLockedPixels
                        }
                        if (pixels && tw > 0 && th > 0 && tw <= 512 && th <= 512) {
                            unsigned int stride = ((tw * 3u + 3u) & ~3u);
                            unsigned int imgSize = stride * th;
                            unsigned int fileSize = 54u + imgSize;
                            unsigned char hdr[54];
                            std::memset(hdr, 0, sizeof(hdr));
                            hdr[0]='B'; hdr[1]='M';
                            std::memcpy(hdr+2, &fileSize, 4);
                            unsigned int off = 54; std::memcpy(hdr+10, &off, 4);
                            unsigned int ih = 40; std::memcpy(hdr+14, &ih, 4);
                            int w32=(int)tw, h32i=(int)th; std::memcpy(hdr+18,&w32,4); std::memcpy(hdr+22,&h32i,4);
                            unsigned short planes=1,bpp=24; std::memcpy(hdr+26,&planes,2); std::memcpy(hdr+28,&bpp,2);
                            std::memcpy(hdr+34, &imgSize, 4);
                            char fname[128];
                            snprintf(fname, sizeof(fname), "gta2_text_gbh_texdump_%d_sid%u_b%u_g%u_%ux%u.bmp",
                                     s_dumpedCount, (unsigned)(unsigned short)spriteId, (unsigned)base, (unsigned)ch, (unsigned)tw, (unsigned)th);
                            FILE* f = std::fopen(fname, "wb");
                            if (f) {
                                std::fwrite(hdr, 1, 54, f);
                                std::vector<unsigned char> row(stride, 0);
                                for (int yb = (int)th - 1; yb >= 0; --yb) {
                                    std::memset(&row[0], 0, stride);
                                    for (unsigned int xb = 0; xb < tw; ++xb) {
                                        unsigned char idx = pixels[(unsigned int)yb * tw + xb];
                                        row[xb*3+0] = idx; row[xb*3+1] = idx; row[xb*3+2] = idx;
                                    }
                                    std::fwrite(&row[0], 1, stride, f);
                                }
                                std::fclose(f);
                                static char s_dumpMsg[160];
                                snprintf(s_dumpMsg, sizeof(s_dumpMsg), "gbh-texdump-ok %s", fname);
                                s_dumpMsg[sizeof(s_dumpMsg)-1] = 0;
                                Text_LogGbhReason(s_dumpMsg);
                                ++s_dumpedCount;
                            } else {
                                Text_LogGbhReason("gbh-texdump-fopen-fail");
                            }
                        } else {
                            static char s_np[96];
                            snprintf(s_np, sizeof(s_np), "gbh-texdump-no-pixels tw=%u th=%u og=%08X lk=%08X", (unsigned)tw, (unsigned)th,
                                     tb ? *(unsigned int*)(tb+20) : 0u, tb ? *(unsigned int*)(tb+8) : 0u);
                            s_np[sizeof(s_np)-1] = 0;
                            Text_LogGbhReason(s_np);
                        }
                        if (lockedHere && api.UnlockTexture) api.UnlockTexture(tex);
                    }
                }
            }
        }
        api.DrawQuad(drawFlags, tex, reinterpret_cast<gbh_Vert*>(verts), 255);
        g_gbhDebug.quads++;
        drewAny = true;
        x += (int)(dbgQuad && dbgQuad[0] == '1' ? w : qw);
        if (x > 2000) break;
    }
    if (drewAny) {
        g_gbhDebug.draws++;
        Text_SetGbhBlocked("gbh-draw-attempted");
    }
    return drewAny;
}

void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5) {
    if (!a1) return;
    // IDA 0x4CC100 signature in decompile is deceptive: extra stack args (a5_4/a5_8/a5_12) used.
    // RE keeps 5-arg bridge; real gbh draw remains guarded and default-off.
    if (gStyle && gTextureManager) {
        unsigned short probe = a4;
        (void)gStyle->GetRemapColour16(&probe);
        (void)gStyle->GetRemapColour32(&probe);
    }
    const char* forceGbh = std::getenv("GTA2_TEXT_GBH");
    if (forceGbh && forceGbh[0] == '1') {
        if (!gStyle || !gTextureManager) { Text_SetGbhBlocked("no-style/tm"); }
        else {
            int ok = 0, total = 0;
            bool hasToggle = false;
            bool chainOk = Text_ProbeGbhAsciiChain(a1, a4, &ok, &total, &hasToggle);
            if (!chainOk) {
                static char s_chain[64];
                snprintf(s_chain, sizeof(s_chain), "%s ok=%d/%d %s", (total > 0) ? "glyph-chain-miss" : "no-ascii", ok, total, s_chainDetail);
                s_chain[sizeof(s_chain)-1] = 0;
                Text_SetGbhBlocked(s_chain);
            } else if (hasToggle) {
                // IDA 0x4CC100: '#' toggles (a1a,a5_12.field_0) between (*a5_4,v7) and (8,0).
                // a5_4/v7 contract not fully confirmed in RE callers; keep draw guarded.
                Text_SetGbhBlocked("chain-ok-has-toggle-a1a-unsupported");
            } else {
                const char* drawEnv = std::getenv("GTA2_TEXT_GBH_DRAW");
                GbhApi api = Gbh_TryGetLoadedApi();
                static char s_gbhProbeBuf[96];
                if (!drawEnv || drawEnv[0] != '1') {
                    snprintf(s_gbhProbeBuf, sizeof(s_gbhProbeBuf), "chain-ok-gbh-%s:draw-env-off",
                             api.loaded ? "ok" : "miss");
                } else {
                    short probeSid = gStyle->GetSpriteID(a4, 0);
                    unsigned short probeBase = gStyle->GetBaseIndex(7, probeSid);
                    // IDA 0x4CC100: GetTexture(gTM,7,SpriteID,a1a,a5_12.field_0), a4=a1a bank selector.
                    // EU ABI logs show *a5_4==2 (bank2/GetStyleTexture S89[0]); bank7/8 only on toggle/other paths.
                    // RE 5-arg bridge has no a5_4/v7; probe observed EU bank2 and guarded bank7 subset.
                    int bank2Tex = GetTexture(gTextureManager, 7, probeSid, 2, 0);
                    int bank7Tex = (int)(uintptr_t)gTextureManager->GetDebugGbhFontTexture(7, probeSid, 7, 0);
                    if (bank2Tex != 0) {
                        snprintf(s_gbhProbeBuf, sizeof(s_gbhProbeBuf),
                                 "chain-ok-bank2 sid=%u base=%u tex=%08X gbh=%s mod=%s",
                                 (unsigned)(unsigned short)probeSid, (unsigned)probeBase, (unsigned)bank2Tex, Gbh_GetLastError(), Gbh_GetModulePath());
                    } else if (bank7Tex != 0) {
                        snprintf(s_gbhProbeBuf, sizeof(s_gbhProbeBuf),
                                 "chain-ok-tm7-ok sid=%u base=%u bank=7 pal=0 gbh=%s",
                                 (unsigned)(unsigned short)probeSid, (unsigned)probeBase, Gbh_GetLastError());
                    } else {
                        const char* r7 = gTextureManager->GetDebugFontS89Bank7().reason;
                        const char* r2 = gTextureManager->GetDebugBank2Style().reason;
                        snprintf(s_gbhProbeBuf, sizeof(s_gbhProbeBuf),
                                 "chain-ok-bank2-miss b2=%s b7=%s sid=%u base=%u gbh=%s mod=%s",
                                 r2?r2:"?", r7?r7:"?", (unsigned)(unsigned short)probeSid, (unsigned)probeBase, Gbh_GetLastError(), Gbh_GetModulePath());
                    }
                }
                s_gbhProbeBuf[sizeof(s_gbhProbeBuf)-1] = 0;
                Text_SetGbhBlocked(s_gbhProbeBuf);
                // Experimental draw only after chain+TM handle ok and explicit draw env.
                if (drawEnv && drawEnv[0] == '1') {
                    // ABI9 safety gate: IDA 0x4CC100 uses *a5_4 as a1a (bank selector) and a5_12.(S202,field_0)
                    // for SetPaletteMode/GetTexture. RE 5-arg bridge loses these args. Only allow observed
                    // EU ASCII-safe profile from debug9 caller; block others with reason (debug-only, no draw).
                    // Consume ABI9 snapshot: prevents stale tail from authorizing unrelated 5-arg calls.
                    TextAbi9Tail abi9 = g_lastAbi9;
                    g_lastAbi9.valid = false;
                    if (abi9.valid) {
                        bool abiOk = (abi9.a5_4_deref == 2u) && (abi9.a5_8 == 0u) &&
                                     (abi9.a5_12_s202 == 0u) && (abi9.a5_12_f0 == 0u);
                        bool syntheticAbi = (abi9.source == kAbi9Synthetic || abi9.source == kAbi9BA2C0Shape);
                        const char* syntheticEnv = std::getenv("GTA2_TEXT_GBH_ALLOW_SYNTHETIC_ABI9");
                        bool allowSynthetic = syntheticEnv && syntheticEnv[0] == '1';
                        if (abiOk && syntheticAbi && !allowSynthetic) {
                            Text_SetGbhBlocked((abi9.source == kAbi9BA2C0Shape) ? "gbh-abi9-ba2c0-shape-blocked" : "gbh-abi9-synthetic-blocked");
                            abiOk = false;
                        }
                        if (!abiOk && syntheticAbi) {
                            // keep blocked reason
                        } else if (!abiOk) {
                            static char s_abiBlk[160];
                            snprintf(s_abiBlk, sizeof(s_abiBlk),
                                     "gbh-abi9-blocked *a5_4=%08X a5_8=%08X s202=%08X f0=%08X",
                                     abi9.a5_4_deref, abi9.a5_8, abi9.a5_12_s202, abi9.a5_12_f0);
                            s_abiBlk[sizeof(s_abiBlk)-1] = 0;
                            Text_SetGbhBlocked(s_abiBlk);
                        } else {
                            if (abi9.source == kAbi9BA2C0Shape) Text_SetGbhBlocked("gbh-abi9-ba2c0-shape-eu-allowed");
                            else if (syntheticAbi) Text_SetGbhBlocked("gbh-abi9-synthetic-eu-allowed");
                            g_gbhDebug.frame++;
                            bool gbhDrew = Text_TryDrawGbhAscii(a1, arg4, arg8, a4, a5);
                            // Debug-only: skip ASCII overlay when gbh draw attempted/succeeded, for visual verification.
                            // Default off; overlay fallback remains the normal path.
                            if (gbhDrew) {
                                const char* noOverlay = std::getenv("GTA2_TEXT_GBH_DRAW_NO_OVERLAY");
                                if (noOverlay && noOverlay[0] == '1') {
                                    Text_SetGbhBlocked("gbh-draw-attempted-no-overlay");
                                    return;
                                }
                            }
                        }
                    } else {
                        // No ABI9 tail observed in this 5-arg path. RE bridge loses a5_4/a5_8/a5_12.
                        // Debug-only: prefer live ABI9 sidechannel from dllLoad hook (same session), else optional log ingest.
                        // Not authoritative for this specific call; only allows known-safe EU profile.
                        bool gotAbi9 = Text_TryConsumeAbi9Sidechannel();
                        const char* abi9Src = "sidechannel";
                        if (!gotAbi9) { gotAbi9 = Text_TryIngestAbi9FromLog(); abi9Src = "log"; }
                        if (gotAbi9) {
                            TextAbi9Tail abi9log = g_lastAbi9;
                            g_lastAbi9.valid = false;
                            bool abiOk = (abi9log.a5_4_deref == 2u) && (abi9log.a5_8 == 0u) &&
                                         (abi9log.a5_12_s202 == 0u) && (abi9log.a5_12_f0 == 0u);
                            bool syntheticAbi = (abi9log.source == kAbi9Synthetic || abi9log.source == kAbi9BA2C0Shape);
                            const char* syntheticEnv = std::getenv("GTA2_TEXT_GBH_ALLOW_SYNTHETIC_ABI9");
                            bool allowSynthetic = syntheticEnv && syntheticEnv[0] == '1';
                            if (abiOk && syntheticAbi && !allowSynthetic) {
                                Text_SetGbhBlocked((abi9log.source == kAbi9BA2C0Shape) ? "gbh-abi9-ba2c0-shape-blocked" : "gbh-abi9-synthetic-blocked");
                                abiOk = false;
                            }
                            if (!abiOk && syntheticAbi) {
                                // keep blocked reason
                            } else if (!abiOk) {
                                static char s_abiBlk[160];
                                snprintf(s_abiBlk, sizeof(s_abiBlk),
                                         "gbh-abi9-%s-blocked *a5_4=%08X a5_8=%08X s202=%08X f0=%08X",
                                         abi9Src, abi9log.a5_4_deref, abi9log.a5_8, abi9log.a5_12_s202, abi9log.a5_12_f0);
                                s_abiBlk[sizeof(s_abiBlk)-1] = 0;
                                Text_SetGbhBlocked(s_abiBlk);
                            } else {
                                static char s_ok[64];
                                if (abi9log.source == kAbi9BA2C0Shape) snprintf(s_ok, sizeof(s_ok), "gbh-abi9-ba2c0-shape-eu-allowed");
                                else snprintf(s_ok, sizeof(s_ok), "gbh-abi9-from-%s-eu", abi9Src);
                                s_ok[sizeof(s_ok)-1] = 0;
                                Text_SetGbhBlocked(s_ok);
                                g_gbhDebug.frame++;
                                bool gbhDrew = Text_TryDrawGbhAscii(a1, arg4, arg8, a4, a5);
                                if (gbhDrew) {
                                    const char* noOverlay = std::getenv("GTA2_TEXT_GBH_DRAW_NO_OVERLAY");
                                    if (noOverlay && noOverlay[0] == '1') {
                                        Text_SetGbhBlocked("gbh-draw-attempted-no-overlay");
                                        return;
                                    }
                                }
                            }
                        } else {
                            // Default: block FORCE draw to avoid wrong bank/palette/mode; require explicit opt-in.
                            const char* allowNoAbi9 = std::getenv("GTA2_TEXT_GBH_ALLOW_NO_ABI9");
                            const char* assumeEu = std::getenv("GTA2_TEXT_GBH_ASSUME_ABI9_EU");
                            if ((allowNoAbi9 && allowNoAbi9[0] == '1') || (assumeEu && assumeEu[0] == '1')) {
                                // Debug-only: assume observed EU ASCII-safe profile. Not ABI-confirmed for this call.
                                // GTA2_TEXT_GBH_ASSUME_ABI9_EU=1 is the narrower name; ALLOW_NO_ABI9 kept for compat.
                                Text_SetGbhBlocked((assumeEu && assumeEu[0] == '1') ? "gbh-abi9-assumed-eu" : "gbh-abi9-missing-allowed");
                                g_gbhDebug.frame++;
                                bool gbhDrew = Text_TryDrawGbhAscii(a1, arg4, arg8, a4, a5);
                                if (gbhDrew) {
                                    const char* noOverlay = std::getenv("GTA2_TEXT_GBH_DRAW_NO_OVERLAY");
                                    if (noOverlay && noOverlay[0] == '1') {
                                        Text_SetGbhBlocked("gbh-draw-attempted-no-overlay");
                                        return;
                                    }
                                }
                            } else {
                                Text_SetGbhBlocked("gbh-abi9-missing-blocked");
                            }
                        }
                    }
                }
            }
        }
    } else {
        Text_SetGbhBlocked("gbh-env-off");
    }

    // ASCII overlay fallback. IDA 0x4CC100: '#' toggles (a1a,a5_12.field_0) between (*a5_4,v7) and (8,0).
    char tmp[128];
    int j = 0;
    int x = arg4;
    int y = arg8;
    unsigned short color = a4;
    unsigned short altColor = (unsigned short)a5;
    bool useAlt = false;
    int lineH = 16;
    extern Font* gFont;
    if (gFont) {
        int ch = gFont->GetCharHeight(color);
        if (ch > 0 && ch < 64) lineH = ch;
    }
    for (int i = 0; a1[i] && j < 127; ++i) {
        wchar_t wc = a1[i];
        if (wc == L'\n') {
            tmp[j] = 0;
            AddDebugTextCmd(tmp, x, y, useAlt ? altColor : color, a5);
            j = 0;
            y += lineH;
            x = arg4;
            continue;
        }
        if (wc == L'#') {
            useAlt = !useAlt;
            continue;
        }
        if (wc == L' ' || (wc >= 32 && wc < 127)) tmp[j++] = (char)wc;
        else tmp[j++] = '?';
    }
    tmp[j] = 0;
    if (j > 0) AddDebugTextCmd(tmp, x, y, useAlt ? altColor : color, a5);
}

void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, int a4, int a5) {
    DrawGTATextRaw(a1, arg4, arg8, (unsigned short)a4, a5);
}

// IDA 0x4539F0: thin wrapper.
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5) {
    DrawGTATextRaw(a1, arg4, arg8, a4, a5);
}

void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, int a4, int a5) {
    DrawGTATextRaw(a1, arg4, arg8, (unsigned short)a4, a5);
}

void DrawGTATextRawMain_Debug9(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                                unsigned int x6_a5_4, unsigned int x7_a5_8,
                                unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0) {
    // Debug-only: capture ABI9 like DrawGTATextRaw_Debug9, but preserve DrawGTATextRawMain call shape.
    DrawGTATextRaw_Debug9(a1, arg4, arg8, a4, a5, x6_a5_4, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0);
}

void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5,
                        unsigned int x6_a5_4, unsigned int x7_a5_8,
                        unsigned int x8_a5_12_s202, unsigned int x9_a5_12_field0) {
    // 9-arg overload matching DrawGTATextRaw ABI9 tail. Captures debug ABI9 then delegates.
    DrawGTATextRaw(a1, arg4, arg8, a4, a5, x6_a5_4, x7_a5_8, x8_a5_12_s202, x9_a5_12_field0);
}

// IDA 0x4C7280: world->screen via Radar::WorldCoordinateToScreenCoord, then DrawGTATextRaw.
// RE bridge: treat a2/a3 as screen coords when Radar path is unavailable.
static bool Text_GbhDebugEnabled() {
    const char* e = std::getenv("GTA2_TEXT_GBH");
    return e && e[0] == '1';
}

void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3) {
    if (Text_GbhDebugEnabled()) {
        // Debug-only RE 9-arg callsite. Tail modeled on IDA 0x4BA2C0/0x453590 case 0:
        // real stack locals: v28==2 (*a5_4==2), a5_8==0, a5_12.s202==0, a5_12.f0==0.
        // IDA 0x4C7280 original tail comes from Tango/SpriteS1/camera; RE layout incomplete.
        // Real 9-arg shape with real stack tail, NOT retail per-callstack proof.
        unsigned int abi9_a5_4_case0 = 2u;
        unsigned int abi9_a5_8 = 0u;
        unsigned int abi9_a5_12_s202 = 0u;
        unsigned int abi9_a5_12_f0 = 0u;
        DrawGTATextRaw(a1, a2, a3, (unsigned short)0, 0x4000,
                       (unsigned int)&abi9_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0);
        return;
    }
    DrawGTATextRaw(a1, a2, a3, 0, 0);
}

void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4) {
    // TODO: IDA 0x4C7280 converts world coords using Radar::WorldCoordinateToScreenCoord
    // and passes (v7, v3->BaseCar[0].field) as color args. RE uses screen coords and a4 as color.
    if (Text_GbhDebugEnabled()) {
        unsigned int abi9_a5_4_case0 = 2u;
        unsigned int abi9_a5_8 = 0u;
        unsigned int abi9_a5_12_s202 = 0u;
        unsigned int abi9_a5_12_f0 = 0u;
        DrawGTATextRaw(a1, a2, a3, a4, 0x4000,
                       (unsigned int)&abi9_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0);
        return;
    }
    DrawGTATextRaw(a1, a2, a3, a4, 0);
}

void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4, int a5) {
    // Compat: accept original-style 5th arg; RE still uses screen coords.
    if (Text_GbhDebugEnabled()) {
        unsigned int abi9_a5_4_case0 = 2u;
        unsigned int abi9_a5_8 = 0u;
        unsigned int abi9_a5_12_s202 = 0u;
        unsigned int abi9_a5_12_f0 = 0u;
        int a5Bridge = (a5 == 0) ? 0x4000 : a5;
        DrawGTATextRaw(a1, a2, a3, a4, a5Bridge,
                       (unsigned int)&abi9_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0);
        return;
    }
    DrawGTATextRaw(a1, a2, a3, a4, a5);
}

void DrawGTATextRaw_7280_Debug(wchar_t* a1, int x, int y, unsigned short a4) {
    // Debug-only: IDA 0x4C7280 tail shape matches 0x4BA2C0 in EU-safe case:
    // 0,0,0,&var_8(var_8==2), a5=*(gCameraOrPhysics+0xA8), a4, *v4, *v5, a1.
    // Keeps screen coords (no Radar world->screen port) but captures ABI9 tail with
    // runtime-derived a5. Not full original callsite/semantics port, not retail proof.
    if (!Text_GbhDebugEnabled()) {
        DrawGTATextRaw(a1, x, y, a4, 0);
        return;
    }
    unsigned int var_8_a5_4_case0 = 2u;
    unsigned int abi9_a5_8 = 0u;
    unsigned int abi9_a5_12_s202 = 0u;
    unsigned int abi9_a5_12_f0 = 0u;
    int a5_rt = 0x4000;
    bool a5_from_runtime = false;
    CameraOrPhysics* camForA5 = gCameraOrPhysics_5E3CC4 ? gCameraOrPhysics_5E3CC4 : gCameraOrPhysics;
    if (camForA5) {
        bool camA5ok = false;
        int camA5raw = camForA5->GetBA2C0A5Value(camA5ok);
        if (camA5ok && camA5raw != 0) { a5_rt = camA5raw; a5_from_runtime = true; }
    }
    if (!a5_from_runtime) Text_LogGbhReason("abi9-7280-a5-fallback");
    Text_DebugCaptureAbi9BA2C0Shape((unsigned int)&var_8_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0, (unsigned int)a5_rt);
    DrawGTATextRaw(a1, x, y, a4, a5_rt,
                   (unsigned int)&var_8_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0);
}

static bool Radar_WorldCoordinateToScreenCoord_Raw(int radarField0, int a3BaseCar0Field, int* out) {
    // IDA 0x401B60 Radar::WorldCoordinateToScreenCoord:
    // result = (this->field_0 * (__int64)a3->BaseCar[0].field) >> 14; S202::SetToNewVal(a2,result)
    if (!out) return false;
    *out = Radar::WorldCoordinateToScreenCoord_Formula(radarField0, a3BaseCar0Field);
    return true;
}

void DrawGTATextRaw_BA2C0_Debug(wchar_t* a1, int x, int y, unsigned short a4) {
    // Debug-only faithful tail-shape port of IDA sub_4BA2C0 @ 0x4BA2C0.
    // Original: 9-push tail (0,0,0,&var_8(var_8==2), a5=[gCameraOrPhysics+0xA8], a4, *v4, *v5, a1)
    // and world->screen via Radar::WorldCoordinateToScreenCoord. RE layout for Radar/camera is not
    // fully verified; we keep screen coords and runtime-derived a5, with real stack locals for tail.
    // NOT a full original callsite port, NOT retail per-callstack proof.
    if (!Text_GbhDebugEnabled()) {
        DrawGTATextRaw(a1, x, y, a4, 0);
        return;
    }
    unsigned int var_8_a5_4_case0 = 2u; // IDA: [esp+18h+var_8]=2
    unsigned int abi9_a5_8 = 0u;
    unsigned int abi9_a5_12_s202 = 0u;
    unsigned int abi9_a5_12_f0 = 0u;
    int a5_rt = 0x4000;
    bool a5_from_runtime = false;
    CameraOrPhysics* camForA5 = gCameraOrPhysics_5E3CC4 ? gCameraOrPhysics_5E3CC4 : gCameraOrPhysics;
    if (camForA5) {
        bool camA5ok = false;
        int camA5raw = camForA5->GetBA2C0A5Value(camA5ok);
        // IDA 0x4BA2C0: v3=&gCameraOrPhysics_5E3CC4->cameraPosTarget[4].field_4; a5=v3->BaseCar[0].field
        // cameraPosTarget[4]@0xA0, field_4@+4 => absolute +0xA4. Runtime-derived read, SEH-guarded.
        // Not full original callsite proof (no Radar world->screen/original caller args/layout).
        if (camA5ok && camA5raw != 0) { a5_rt = camA5raw; a5_from_runtime = true; }
        static bool s_probeLogged = false;
        if (!s_probeLogged) {
            s_probeLogged = true;
            // Debug-only read-only layout probe around IDA cameraPosTarget[4] (+0xA0, stride 0x28). SEH-guarded, no writes.
            unsigned int camA0=0,camA4=0,camA8=0,camAC=0; int okA0=0,okA4=0,okA8=0,okAC=0;
            __try { camA0 = *(unsigned int*)((char*)camForA5 + 0xA0); okA0=1; } __except(EXCEPTION_EXECUTE_HANDLER){ okA0=0; }
            __try { camA4 = *(unsigned int*)((char*)camForA5 + 0xA4); okA4=1; } __except(EXCEPTION_EXECUTE_HANDLER){ okA4=0; }
            __try { camA8 = *(unsigned int*)((char*)camForA5 + 0xA8); okA8=1; } __except(EXCEPTION_EXECUTE_HANDLER){ okA8=0; }
            __try { camAC = *(unsigned int*)((char*)camForA5 + 0xAC); okAC=1; } __except(EXCEPTION_EXECUTE_HANDLER){ okAC=0; }
            FILE* pf = std::fopen("gta2_text_gbh_reason.log", "a");
            if (pf) {
                std::fprintf(pf, "abi9-ba2c0-probe cam=%p cam5=%p A0_fild=%d:%08X A4_field4=%d:%08X A8_cam=%d:%08X AC_car=%d:%08X a5raw=%08X\n",
                             (void*)gCameraOrPhysics, (void*)gCameraOrPhysics_5E3CC4, okA0, camA0, okA4, camA4, okA8, camA8, okAC, camAC, (unsigned int)camA5raw);
                std::fclose(pf);
            }
        }
    }
    if (!a5_from_runtime) Text_LogGbhReason("abi9-ba2c0-a5-fallback");
    Text_DebugCaptureAbi9Callsite((unsigned int)&var_8_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0, (unsigned int)a5_rt);
    DrawGTATextRaw(a1, x, y, a4, a5_rt,
                   (unsigned int)&var_8_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0);
}

void DrawGTATextRaw_BA2C0_DebugRaw(wchar_t* a1, int a2, void* a3_radarLike, unsigned short a4) {
    // Debug-only closer port of IDA sub_4BA2C0 @ 0x4BA2C0. Raw/guarded reads:
    // - a5 from gCameraOrPhysics_5E3CC4->cameraPosTarget[4].field_4 (+0xA4)
    // - Radar::WorldCoordinateToScreenCoord formula @ 0x401B60: (field_0 * a3.BaseCar[0].field) >> 14
    // - ABI9 tail real stack locals: &var_8==2,0,0,0
    // a3_radarLike layout not fully verified in RE; gated+SEH. NOT retail per-callstack proof.
    if (!Text_GbhDebugEnabled()) {
        DrawGTATextRaw(a1, a2, 0, a4, 0);
        return;
    }
    unsigned int var_8_a5_4_case0 = 2u;
    unsigned int abi9_a5_8 = 0u;
    unsigned int abi9_a5_12_s202 = 0u;
    unsigned int abi9_a5_12_f0 = 0u;
    int a5_rt = 0x4000;
    bool a5_from_runtime = false;
    int sx = a2;
    int sy = 0;
    bool radar_ok = false;
    __try {
        CameraOrPhysics* camForA5 = gCameraOrPhysics_5E3CC4 ? gCameraOrPhysics_5E3CC4 : gCameraOrPhysics;
        if (camForA5) {
            bool camA5ok = false;
            int camA5raw = camForA5->GetBA2C0A5Value(camA5ok);
            if (camA5ok && camA5raw != 0) { a5_rt = camA5raw; a5_from_runtime = true; }
        }
        if (a3_radarLike && a3_radarLike != (void*)camForA5) {
            // Debug-only best-effort: treat a3_radarLike as Radar-like with field_0 at +0.
            // Original BA2C0 uses two coord inputs and specific Radar/PublicTransport objects;
            // RE layout/object identity not verified here. Do not count as call-accurate proof.
            int radarField0 = *(int*)a3_radarLike;
            int base = a5_from_runtime ? a5_rt : a2;
            Radar_WorldCoordinateToScreenCoord_Raw(radarField0, base, &sx);
            Radar_WorldCoordinateToScreenCoord_Raw(radarField0, base, &sy);
            radar_ok = true;
        }
    }
    __except (EXCEPTION_EXECUTE_HANDLER) {
        radar_ok = false;
    }
    if (!a5_from_runtime) Text_LogGbhReason("abi9-ba2c0-a5-fallback");
    Text_LogGbhReason(radar_ok ? "abi9-ba2c0-raw-radar" : "abi9-ba2c0-raw-screen");
    Text_DebugCaptureAbi9BA2C0Shape((unsigned int)&var_8_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0, (unsigned int)a5_rt);
    DrawGTATextRaw(a1, sx, sy, a4, a5_rt,
                   (unsigned int)&var_8_a5_4_case0, abi9_a5_8, abi9_a5_12_s202, abi9_a5_12_f0);
}

void DrawGTATextRaw_A2C0_Debug(wchar_t* a1, int x, int y, unsigned short a4) {
    // IDA 0x4BA2C0 signature is (a1,a2,a3=SpriteS1/PublicTransport-like). We don't have a verified
    // RE Radar object/layout at the Hud callsite, so this wrapper keeps the original 4-arg HUD usage
    // and routes through BA2C0-shaped debug capture. NOT original callsite/callstack proof.
    Text_LogGbhReason("abi9-a2c0-debug-shape");
    DrawGTATextRaw_BA2C0_Debug(a1, x, y, a4);
}
