#include "FileMgr.h"
#include "../Debug/DebugLogFile.h"
#include <string.h>

FileMgr *gFileMgr;

static FILE* g_fileMgrStream = nullptr;
static bool g_fileMgrOpen = false;
static char g_fileMgrPath[260] = {};

FileMgr::FileMgr() { Status = false; }
FileMgr::~FileMgr() {}

int FileMgr::SetFilePath(char* filename) { (void)filename; return 0; }
void FileMgr::LoadFronSprites() {}

FILE* FileMgr::WriteReadFile(const char* filename, const char* mode) {
	FILE* file = fopen(filename, mode);
	Status = file != 0;
	return file;
}
FILE* FileMgr::FileOpen(char* filename, char* mode) {
	FILE* f = fopen(filename, mode ? mode : "rb");
	Status = f != 0;
	return f;
}
FILE* FileMgr::FileOpen(char* filename) {
	return FileOpen(filename, "rb");
}
void FileMgr::ReadFile(void* outbuffer, void* inBuffer) {
	// Legacy signature in codebase; treat as no-op when args unknown.
	(void)outbuffer; (void)inBuffer;
}
void FileMgr::ReadFile(void* buffer, size_t SizeRead) {
	// Legacy signature; no FILE context. No-op.
	(void)buffer; (void)SizeRead;
}

FILE* FileMgr::FileOpenStatic(const char* filename, const char* mode) {
	// IDA 0x403160 shape: close previous, set path, open "rb", log 0x10/File.cpp/328 on fail, mark open.
	if (g_fileMgrOpen) {
		CloseFile();
	}
	const char* name = filename ? filename : "";
	strncpy(g_fileMgrPath, name, sizeof(g_fileMgrPath) - 1);
	g_fileMgrPath[sizeof(g_fileMgrPath) - 1] = 0;
	g_fileMgrStream = fopen(g_fileMgrPath[0] ? g_fileMgrPath : "", mode ? mode : "rb");
	if (!g_fileMgrStream) {
		DebugLog(0x10u, "File.cpp", 328);
		g_fileMgrOpen = false;
		return nullptr;
	}
	g_fileMgrOpen = true;
	return g_fileMgrStream;
}

int FileMgr::CloseFile() {
	// IDA 0x402EB0
	int result = 0;
	if (g_fileMgrOpen && g_fileMgrStream) {
		result = fclose(g_fileMgrStream);
		g_fileMgrOpen = false;
		g_fileMgrStream = nullptr;
		if (result) {
			DebugLog(0x11u, "File.cpp", 350);
		}
	}
	return result;
}

int FileMgr::SeekPtr(const void* sizePtr) {
	// IDA 0x402F60: reads *(DWORD*)size and fseek(stream, *size, SEEK_CUR)
	if (!g_fileMgrOpen || !g_fileMgrStream) {
		DebugLog(0x15u, "File.cpp", 421);
		return -1;
	}
	int off = 0;
	if (sizePtr) memcpy(&off, sizePtr, sizeof(int));
	int result = fseek(g_fileMgrStream, off, SEEK_CUR);
	if (result) {
		DebugLog(0xEu, "File.cpp", 403);
	}
	return result;
}

int FileMgr::Seek(int offset) {
	return SeekPtr(&offset);
}

size_t FileMgr::Read(void* buffer, size_t* sizePtr) {
	// IDA 0x402FB0/BN: stdcall(buffer,size*); DebugLog(0x15,"File.cpp",0x1BB) if not open;
	// Fread(buffer,gStream,*size,1)==1 else Error(0xF,0,0). RE returns bytes read; callers compare.
	if (!buffer || !sizePtr) return 0;
	size_t size = *sizePtr;
	if (size == 0) return 0;
	if (!g_fileMgrOpen || !g_fileMgrStream) {
		DebugLog(0x15u, "File.cpp", 443); // 0x1BB
		return 0;
	}
	size_t got = fread(buffer, (size_t)size, 1, g_fileMgrStream);
	if (got != 1) {
		DebugLog(0xFu, "File.cpp", 0);
		return 0;
	}
	return size;
}

int FileMgr::ReadLine(void* buffer, size_t* sizePtr) {
	// IDA/BN 0x403000: stdcall(buffer,size*); DebugLog(0x15,"File.cpp",0x1D1) if not open;
	// return Fread(buffer,gStream,*size,1)==1. Used by chunk-header loops (size=8).
	if (!buffer || !sizePtr) return 0;
	size_t size = *sizePtr;
	if (size == 0) return 0;
	if (!g_fileMgrOpen || !g_fileMgrStream) {
		DebugLog(0x15u, "File.cpp", 465); // 0x1D1
		return 0;
	}
	size_t got = fread(buffer, (size_t)size, 1, g_fileMgrStream);
	return got == 1 ? 1 : 0;
}
size_t FileMgr::ReadSize(void* buffer, size_t size) {
	return Read(buffer, &size);
}

bool FileMgr::IsOpen() { return g_fileMgrOpen && g_fileMgrStream != nullptr; }
FILE* FileMgr::GetStream() { return g_fileMgrStream; }
const char* FileMgr::GetPath() { return g_fileMgrPath; }


int  FileMgr::ReadToken(FILE* f, WORD* out) {
    unsigned char i = 0;
    int c;

    do {
        c = getc(f);
        if (c == '\n' || c == ' ')
            break;
        out[i++] = (WORD)c;
    } while (1);

    out[i] = 0;
    return c;
}