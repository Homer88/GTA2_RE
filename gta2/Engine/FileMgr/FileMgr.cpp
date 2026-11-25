#include "FileMgr.h"

FileMgr *gFileMgr;


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