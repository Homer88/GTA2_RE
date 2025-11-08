// dllmain.cpp : Определяет точку входа для приложения DLL.
#include <iostream>
//#include <cstdlib>
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <malloc.h>
//#include <assert.h>

#include "detours.h"
//#include "pch.h"
//  файлы конфигурации 
#include "InitMapGM.h"
//#include "InitS20Fun.h"
#include "DebugLogFile.h"

#include "cDirectX.h"
//#include "cGang.h"
//#include "cGangs.h"
#include "cMapGm.h"
//#include "cPed.h"
//
//#include "cS8.h"
//#include "cS19.h"
//#include "cS20.h"
//#include "cText.h"
//
//#include "cWeapon.h"
#include "cWindow.h"

#pragma comment(lib, "detours.lib")

int FunMapGM();
///void  FunS20();
void printError(LONG Error, PVOID address);

unsigned int Error;

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  dwReason,
                       LPVOID lpReserved
                     )
{

    // Получить дескриптор окна консоли
    HWND consoleWindow = GetConsoleWindow();

    if (consoleWindow != NULL) {
        // Спрятать окно
        ShowWindow(consoleWindow, SW_HIDE);
    }

    LPVOID _InfoVersion = (LPVOID)0x004D0920;
    LPVOID _InitDiretX =  (LPVOID)0x004031c0;
    LPVOID _GetDebugParam = (LPVOID)0x00451930;

    LPVOID  _AllGtxFile = (LPVOID)0x00451800;
    
    //LPVOID _CopyNameGang= (LPVOID)0x0045DB40;
    
    
    ///S19
   // LPVOID _SetPararam_0 = (LPVOID)0x004c4d60;
    
    //cText
    //LPVOID _GetLanguageJapan = (LPVOID)0x00452E60;
    // Weapons
    //LPVOID _FUN_00433810 = (LPVOID)0x00433810;
    ///LPVOID _Weapon_FUN_004cca10 = (LPVOID)0x004cca10;
    
    AllocConsole();
    switch (dwReason){
     

    case DLL_PROCESS_ATTACH:
       /// MessageBox(0, L"Load Dll!", 0, 0);
       
        DetourRestoreAfterWith();
        if (DetourTransactionBegin() != NO_ERROR)
        {
            OutputDebugStringA("error DetourTransactionBegin");
            return FALSE;
        }

        if (DetourUpdateThread(GetCurrentThread()) != NO_ERROR)
        {
            printf("error DetourUpdateThread");
            return FALSE;
        }

        Error = DetourAttach(&_InfoVersion, (PVOID)GetVersionLaunch);
        printError(Error, _InfoVersion);

        /*DetourAttach(&_SetPararam_0, (PVOID)SetPararam_0);
        DetourAttach(&_CopyNameGang, (PVOID)CopyNameGang);
        DetourAttach(&_SetPararam_0, (PVOID)SetPararam_0);
        DetourAttach(&_GetLanguageJapan, (PVOID)GetLanguageJapan);
        DetourAttach(&_FUN_00433810, (PVOID)SetTypeWeapons);
        DetourAttach(&_Weapon_FUN_004cca10, (PVOID)Weapon_FUN_004cca10);
        */
        Error =  DetourAttach(&_InitDiretX, (PVOID)InitDiretX);
        printError(Error, _InitDiretX);

        Error = DetourAttach(&_GetDebugParam, (PVOID)GetDebugParam);
        printError(Error, _GetDebugParam);

        Error = DetourAttach(&_AllGtxFile, (PVOID)AllGtxFile);
        printError(Error, _AllGtxFile);
        //*/
        //FunS20();
        FunMapGM();
        if (DetourTransactionCommit() != NO_ERROR)
        {
            printf("error DetourTransactionCommit");
            return FALSE;
        }
     break;
   case DLL_THREAD_ATTACH:
   case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
      break;
    }
    //DetourRestoreAfterWith();
    printf("Dettach and shutdown everything\n");
    return true;
}


void printError(LONG Error, PVOID address) {


    switch (Error)
    {
    case ERROR_INVALID_BLOCK:
        MessageBox(0, L"ERROR_INVALID_BLOCK", 0, 0);
        break;
    case ERROR_INVALID_HANDLE:
        MessageBox(0, L"ERROR_INVALID_HANDLE", 0, 0);
        break;
    case ERROR_INVALID_OPERATION:
        MessageBox(0, L"ERROR_INVALID_OPERATION", 0, 0);
        writeFileLog((char*)"windows.txt", (char*)"addres=", (char*)"Error ", (unsigned int)address);
        break;
    case ERROR_NOT_ENOUGH_MEMORY:
        MessageBox(0, L"ERROR_NOT_ENOUGH_MEMORY", 0, 0);
        break;
    case NO_ERROR:
        //MessageBox(0, L"NO_ERROR", 0, 0);
        break;
    default:
        break;
    }
}



int FunMapGM()
{
    //Error=  DetourAttach(&_LoadFileResurce     ,  (PVOID)LoadFileResurce);
   // printError(Error, _LoadFileResurce);
    //Error = DetourAttach(&_SetSaveFile         ,  (PVOID)SetSaveFile);
    //printError(Error, _SetSaveFile);
    //Error = DetourAttach(&_SetPlayerArena      ,  (PVOID)SetPlayerArena);
    //printError(Error, _SetPlayerArena);
   // Error = DetourAttach(&_SetSaveFile         ,  (PVOID)SetSaveFile);
   // printError(Error, _SetSaveFile);
    //Error = DetourAttach(&_SetPlayerArena      ,  (PVOID)SetPlayerArena);
    //printError(Error, _SetPlayerArena);
    //Error = DetourAttach(&_SetBonusStage       ,  (PVOID)SetBonusStage);
    //printError(Error, _SetBonusStage);
   // Error = DetourAttach(&_Set_FUN_0045E4B0    ,  (PVOID)Set_FUN_0045E4B0);
    //printError(Error, _Set_FUN_0045E4B0);
    //Error = DetourAttach(&_SetPlayerSlotSave   ,  (PVOID)SetPlayerSlotSave);
    //printError(Error, _SetPlayerSlotSave);
    //Error = DetourAttach(&_SetBonus            ,  (PVOID)SetBonus);
    //printError(Error, _SetBonus);
    return 0;
};

/*void FunS20() {
    DetourAttach(&_SetPararm_0x2ee0, (PVOID)SetPararm_0x2ee0);
}*/