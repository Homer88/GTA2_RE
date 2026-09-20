#include "FileMgr.h"

FileMgr *gFileMgr;


FileMgr::FileMgr() {
};
FileMgr::~FileMgr() {};

int FileMgr::SetFilePath(char* filename) {

	return 0;
}
void FileMgr::LoadFronSprites() {

}
FILE* FileMgr::WriteReadFile(const char* filename, const char* mode) {

	FILE* file=fopen(filename,mode);
	

	return file;
};
FILE* FileMgr::FileOpen(char* filename, char* mode) {
	return (FILE*)NULL;
};
FILE* FileMgr::FileOpen(char* filename) {
	return (FILE*)NULL;
};
void FileMgr::ReadFile(void* outbuffer, void* inBuffer) {};
void FileMgr::ReadFile(void* buffer, size_t SizeRead) {};


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