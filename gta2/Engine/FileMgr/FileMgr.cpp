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
	// IDA 0x402FB0 no-cfunc in export. Guarded RE impl: fread(size,1,stream).
	if (!buffer || !sizePtr) return 0;
	size_t size = *sizePtr;
	if (size == 0) return 0;
	if (!g_fileMgrOpen || !g_fileMgrStream) {
		DebugLog(0x15u, "File.cpp", 421);
		return 0;
	}
	clearerr(g_fileMgrStream);
	size_t got = fread(buffer, 1, size, g_fileMgrStream);
	if (got != size && ferror(g_fileMgrStream)) {
		DebugLog(0x12u, "File.cpp", 0);
	}
	return got;
}

int FileMgr::ReadLine(void* /*ctx*/, char* buffer, size_t* sizePtr) {
	// IDA 0x403000 no-cfunc. Guarded behavior for known chunk-header callers:
	// for(size=8; ReadLine(a1,a1,&size); size=8) if(chunk_size) parse_chunk(a1,chunk_size)
	if (!buffer || !sizePtr) return 0;
	*sizePtr = 0;
	if (!g_fileMgrOpen || !g_fileMgrStream) return 0;
	unsigned char hdr[8] = {};
	size_t got = fread(hdr, 1, 8, g_fileMgrStream);
	if (got != 8) return 0;
	memcpy(buffer, hdr, 4);
	unsigned int chunkSize = 0;
	memcpy(&chunkSize, hdr + 4, 4);
	*sizePtr = (size_t)chunkSize;
	return 1;
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