#pragma once



// �������� ������� ��������� ���������
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void GetVersion(DWORD *pMajorVersion, DWORD *pMinorVersion);
void FindGraphiDevace();

