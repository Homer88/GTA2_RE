#ifndef __DEBUG_H_
#define __DEBUG_H_


//0x2Bu, "registry.cpp", 232
void DebugLog(int CodeError, char* ErrorFile, int code);
void DebugLog(char* ErrorFile);
void DebugLog(const char* ErrorFile);
void DebugLog(void* Structure, void* offsetPole, char *text);

void DebugLog(wchar_t* ErrorFile);
void DebugLog(bool* ErrorFile);
void DebugLog(unsigned char* ErrorFile);
void DebugLog(int ErrorFile);
void DebugLog(char* text, int ErrorFile);
void DebugLog(unsigned char ErrorFile);
void MsgError(char* ErrorMsg);
void MsgError(char* Descript, char* ErrorMsg);
int writeFileLog(char* FileName, char* str, char* error, unsigned int  data);
int writeFileLog(char* FileName, char* str, char* error, char* data);
int writeFileLog(char* FileName, char* str, char* error, BYTE  *data);
int writeFileLog(char* FileName, LPCSTR lpValueName, char* str, char* error, BYTE* data);
int writeFileLog(char* FileName, char* str, char* error, bool*  address);

#endif // !__DEBUG_H_
