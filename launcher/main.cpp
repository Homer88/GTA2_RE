// GTA2Launcher - самодостаточный EXE: встраивает наши d3ddll.dll и mss32.dll
// как RCDATA-ресурсы, кладёт их в папку игры (если версия отличается) и
// запускает gta2-resurected.exe / gta2.exe.
//
// Использование: положить GTA2Launcher.exe в папку с игрой и запустить.
// Либо запустить с аргументом: GTA2Launcher.exe --dir=<путь к папке игры>
// или выбрать папку игры вручную (кнопка "Выбрать папку игры").

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <commdlg.h>
#include <stdio.h>

#define IDR_D3DDLL    1001
#define IDR_MSS32     1002

#define IDC_PATH      2001
#define IDC_STATUS    2002
#define IDC_PICK      2003
#define IDC_PLAY      2004
#define IDC_EXIT      2005
#define IDC_WARN      2006

static const char* g_iniName  = "gta2launcher.ini";
static char g_exeDir[MAX_PATH];
static char g_gameDir[MAX_PATH];
static char g_gameExe[MAX_PATH];
static char g_iniPath[MAX_PATH];

// ------------------------------------------------------------------ helpers

static void PathFromSelf(char* out, size_t size)
{
    char buf[MAX_PATH];
    DWORD n = GetModuleFileNameA(0, buf, MAX_PATH);
    if (n == 0 || n >= MAX_PATH) { out[0] = 0; return; }
    char* slash = strrchr(buf, '\\');
    if (slash) *slash = 0;
    lstrcpynA(out, buf, (int)size);
}

static void WriteIni(void)
{
    WritePrivateProfileStringA("game", "dir", g_gameDir, g_iniPath);
}

// ------------------------------------------------------------------ driver

/* Сравниваем размер существующего файла с размером ресурса; если отличается
   или файла нет - пишем новую версию. Возвращает 1=установлено, 2=ok, 0=ошибка. */
static int InstallResource(HINSTANCE hInst, int resId, const char* dest)
{
    HRSRC hr = FindResourceA(hInst, MAKEINTRESOURCE(resId), RT_RCDATA);
    if (!hr) return 0;
    HGLOBAL hg = LoadResource(hInst, hr);
    if (!hg) return 0;
    const BYTE* data = (const BYTE*)LockResource(hg);
    DWORD sz = SizeofResource(hInst, hr);
    if (!data || sz == 0) return 0;

    DWORD curSz = 0;
    HANDLE hf = CreateFileA(dest, GENERIC_READ, FILE_SHARE_READ, 0, OPEN_EXISTING, 0, 0);
    if (hf != INVALID_HANDLE_VALUE) {
        GetFileSizeEx(hf, (LARGE_INTEGER*)&curSz);
        CloseHandle(hf);
    }

    if (hf != INVALID_HANDLE_VALUE && curSz == sz) return 2;

    hf = CreateFileA(dest, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, 0, 0);
    if (hf == INVALID_HANDLE_VALUE) return 0;
    DWORD wr = 0;
    BOOL ok = WriteFile(hf, data, sz, &wr, 0);
    CloseHandle(hf);
    return (ok && wr == sz) ? 1 : 0;
}

static void RefreshStatus(HWND hwnd)
{
    char d3d[MAX_PATH], mss[MAX_PATH], txt[512];
    wsprintfA(d3d, "%s\\d3ddll.dll", g_gameDir);
    wsprintfA(mss, "%s\\mss32.dll",  g_gameDir);

    int dOk = InstallResource(0, 0, 0); // no-op placeholder
    (void)dOk;

    WIN32_FIND_DATAA fd;
    char st_d3d[32] = "нет", st_mss[32] = "нет";
    HANDLE f1 = FindFirstFileA(d3d, &fd);
    if (f1 != INVALID_HANDLE_VALUE) { wsprintfA(st_d3d, "%u", fd.nFileSizeLow); FindClose(f1); }
    HANDLE f2 = FindFirstFileA(mss, &fd);
    if (f2 != INVALID_HANDLE_VALUE) { wsprintfA(st_mss, "%u", fd.nFileSizeLow); FindClose(f2); }

    wsprintfA(txt, "d3ddll.dll: %s байт   |   mss32.dll: %s байт", st_d3d, st_mss);
    SetDlgItemTextA(hwnd, IDC_STATUS, txt);
    wsprintfA(txt, "Папка игры:  %s", g_gameDir);
    SetDlgItemTextA(hwnd, IDC_PATH, txt);
}

// ------------------------------------------------------------------ main

static void PickGameDir(HWND hwnd)
{
    OPENFILENAMEA ofn = { 0 };
    char fname[MAX_PATH] = { 0 };
    ofn.lStructSize = sizeof(ofn);
    ofn.hwndOwner = hwnd;
    ofn.lpstrFilter = "GTA2 exe\0gta2.exe;gta2-resurected.exe\0Все файлы\0*.*\0";
    ofn.lpstrFile = fname;
    ofn.nMaxFile = MAX_PATH;
    ofn.lpstrTitle = "Выберите gta2.exe или gta2-resurected.exe";
    ofn.Flags = OFN_FILEMUSTEXIST | OFN_NOCHANGEDIR;
    if (!GetOpenFileNameA(&ofn)) return;

    char dir[MAX_PATH];
    lstrcpynA(dir, fname, MAX_PATH);
    char* slash = strrchr(dir, '\\');
    if (!slash) return;
    *slash = 0;
    lstrcpynA(g_gameDir, dir, MAX_PATH);
    wsprintfA(g_gameExe, "%s\\%s", g_gameDir, (char*)ofn.lpstrFile);
    slash = strrchr(g_gameExe, '\\');
    if (slash) lstrcpyA(slash + 1, ofn.lpstrFile);
    WriteIni();
    RefreshStatus(hwnd);
}

static void DoInstall(HWND hwnd)
{
    char d3d[MAX_PATH], mss[MAX_PATH], txt[512];
    wsprintfA(d3d, "%s\\d3ddll.dll", g_gameDir);
    wsprintfA(mss, "%s\\mss32.dll",  g_gameDir);
    HINSTANCE hi = GetModuleHandleA(0);
    int r1 = InstallResource(hi, IDR_D3DDLL, d3d);
    int r2 = InstallResource(hi, IDR_MSS32,  mss);
    wsprintfA(txt, "Установка драйверов: d3ddll=%s mss32=%s",
        r1 == 1 ? "обновлён" : (r1 == 2 ? "не требуется" : "ОШИБКА"),
        r2 == 1 ? "обновлён" : (r2 == 2 ? "не требуется" : "ОШИБКА"));
    SetDlgItemTextA(hwnd, IDC_WARN, txt);
}

static void DoPlay(HWND hwnd)
{
    if (!g_gameExe[0]) { SetDlgItemTextA(hwnd, IDC_WARN, "Сначала выберите папку игры."); return; }
    DoInstall(hwnd);

    char cur[MAX_PATH];
    GetCurrentDirectoryA(MAX_PATH, cur);
    SetCurrentDirectoryA(g_gameDir);

    STARTUPINFOA si = { 0 };
    si.cb = sizeof(si);
    PROCESS_INFORMATION pi = { 0 };
    BOOL ok = CreateProcessA(0, g_gameExe, 0, 0, FALSE,
                             CREATE_DEFAULT_ERROR_MODE | CREATE_NEW_PROCESS_GROUP,
                             0, g_gameDir, &si, &pi);
    SetCurrentDirectoryA(cur);
    if (!ok) {
        char txt[256];
        wsprintfA(txt, "Не удалось запустить: %s", g_gameExe);
        SetDlgItemTextA(hwnd, IDC_WARN, txt);
        return;
    }
    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
    SendMessageA(hwnd, WM_CLOSE, 0, 0);
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wp, LPARAM lp)
{
    switch (msg) {
    case WM_CREATE:
        CreateWindowA("STATIC", "GTA2 Launcher", WS_CHILD | WS_VISIBLE | SS_LEFT,
                      14, 12, 340, 24, hwnd, 0, GetModuleHandleA(0), 0);
        CreateWindowA("STATIC", g_gameDir, WS_CHILD | WS_VISIBLE | SS_LEFT,
                      14, 36, 400, 40, hwnd, (HMENU)IDC_PATH, GetModuleHandleA(0), 0);
        CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT,
                      14, 78, 400, 40, hwnd, (HMENU)IDC_STATUS, GetModuleHandleA(0), 0);
        CreateWindowA("STATIC", "", WS_CHILD | WS_VISIBLE | SS_LEFT,
                      14, 100, 400, 40, hwnd, (HMENU)IDC_WARN, GetModuleHandleA(0), 0);
        CreateWindowA("BUTTON", "Выбрать папку игры", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                      14, 132, 160, 30, hwnd, (HMENU)IDC_PICK, GetModuleHandleA(0), 0);
        CreateWindowA("BUTTON", "Играть", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                      192, 132, 110, 30, hwnd, (HMENU)IDC_PLAY, GetModuleHandleA(0), 0);
        CreateWindowA("BUTTON", "Выход", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
                      322, 132, 90, 30, hwnd, (HMENU)IDC_EXIT, GetModuleHandleA(0), 0);
        RefreshStatus(hwnd);
        return 0;
    case WM_COMMAND:
        switch (LOWORD(wp)) {
        case IDC_PICK:  PickGameDir(hwnd);  break;
        case IDC_PLAY:  DoPlay(hwnd);       break;
        case IDC_EXIT:  SendMessageA(hwnd, WM_CLOSE, 0, 0); break;
        }
        return 0;
    case WM_DESTROY:
        WriteIni();
        PostQuitMessage(0);
        return 0;
    }
    return DefWindowProcA(hwnd, msg, wp, lp);
}

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hPrev, LPSTR lpCmd, int nShow)
{
    PathFromSelf(g_exeDir, MAX_PATH);
    lstrcpynA(g_gameDir, g_exeDir, MAX_PATH);
    wsprintfA(g_iniPath, "%s\\%s", g_exeDir, g_iniName);

    char dir[512] = { 0 };
    GetPrivateProfileStringA("game", "dir", "", dir, 512, g_iniPath);
    if (dir[0]) lstrcpynA(g_gameDir, dir, MAX_PATH);

    const char* a = strstr(lpCmd, "--dir=");
    if (a) {
        char d[MAX_PATH];
        lstrcpynA(d, a + 6, MAX_PATH);
        char* sp = strchr(d, ' ');
        if (sp) *sp = 0;
        if (d[0]) lstrcpynA(g_gameDir, d, MAX_PATH);
    }

    wsprintfA(g_gameExe, "%s\\gta2-resurected.exe", g_gameDir);
    if (GetFileAttributesA(g_gameExe) == INVALID_FILE_ATTRIBUTES) {
        wsprintfA(g_gameExe, "%s\\gta2.exe", g_gameDir);
        if (GetFileAttributesA(g_gameExe) == INVALID_FILE_ATTRIBUTES)
            g_gameExe[0] = 0;
    }

    WNDCLASSA wc = { 0 };
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInst;
    wc.hCursor = LoadCursorA(0, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
    wc.lpszClassName = "GTA2LauncherWnd";
    RegisterClassA(&wc);

    RECT r = { 0, 0, 430, 180 };
    AdjustWindowRect(&r, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU, FALSE);
    HWND hwnd = CreateWindowA("GTA2LauncherWnd", "GTA2 Launcher",
        WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU,
        CW_USEDEFAULT, CW_USEDEFAULT,
        r.right - r.left, r.bottom - r.top,
        0, 0, hInst, 0);
    if (!hwnd) return 1;
    ShowWindow(hwnd, nShow);
    UpdateWindow(hwnd);

    MSG msg;
    while (GetMessageA(&msg, 0, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessageA(&msg);
    }
    return 0;
}