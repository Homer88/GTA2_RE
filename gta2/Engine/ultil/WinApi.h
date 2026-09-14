/*
Иструменты для работы ПО.
*/
#ifndef ___WIN_API___H__
#define ___WIN_API___H__
#include <windows.h>


typedef enum TimeDay {
	DAY = 32768,
	NIGHT = 0,
}TimeDay;
typedef enum ModeSize {
	FullScreen = 1,
	WindowScreen = 0,
}ModeSize;
class WinApi{
	public:
		WinApi();
		char* Convertor_wchar_t_ToChar(wchar_t* Text);
		wchar_t* CopyWideString(wchar_t* dest, wchar_t* source);
		
		void GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion);
		void InitTimer();
		void GetDebugParam();
		bool AllGtxFile();
		void DefautInitParam();
		void FindGraphicDevice();
		void ConfigureVideoDevice();
		bool ConfigureVideoWindow();
		void SetShowCursor();
		int SetVideoPlayer();
		void SetGamma();
		bool SetVideoGamma(int Gamma);
		char VideoCheck1();
		void VideoCheck();
		void DirectInput2();// удалю когда напишу полностью directx 
		~WinApi();
};



 
#endif  //___WIN_API___H__
