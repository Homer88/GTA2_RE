#ifndef __WINDOWS_H___MY_FILE___
#define __WINDOWS_H___MY_FILE___
typedef  unsigned int uint;
typedef  unsigned short ushort;

void __stdcall GetVersionLaunch(int* pMajorVersion, int* pMinorVersion);
void __stdcall GetDebugParam();
bool __stdcall  AllGtxFile();
void __stdcall InitDefautValue();
#endif // !__WINDOWS_H___MY_FILE___

