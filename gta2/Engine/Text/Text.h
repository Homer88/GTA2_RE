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
void DrawGTATextRaw(wchar_t* a1, int arg4, int arg8, int a4, int a5); // compat overload
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, unsigned short a4, int a5); // IDA 0x4539F0
void DrawGTATextRawMain(wchar_t* a1, int arg4, int arg8, int a4, int a5); // compat overload
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3); // RE screen-coord bridge
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4); // IDA 0x4C7280 compat (world->screen in original)
void DrawGTATextRaw_7280(wchar_t* a1, int a2, int a3, unsigned short a4, int a5); // compat with original 5-arg tail

#endif
