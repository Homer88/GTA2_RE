//данный файлы  библиотека Binkw32.dll 
//версия 3.0
#include <windows.h>
#include <cstdlib>   // Для malloc
#include <climits>   // Для INT_MAX
#include <cstdint>   // Для uintptr_t (если доступен)
#include "global.h"
#include "binkw32.h"





BOOL  __stdcall DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved){
	    if (fdwReason == 1 && !dword_1002E9D4)
		    DisableThreadLibraryCalls(hinstDLL);
		return TRUE;
}
BOOL __stdcall DllEntryPoint(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved){

}


int __stdcall BinkCheckCursor(HWND hWnd, LONG a2, LONG a3, int a4, int a5) {
    int v5; // edi
    struct tagPOINT Point; // [esp+8h] [ebp-10h] BYREF
    struct tagPOINT pCursorPos; // [esp+10h] [ebp-8h] BYREF

    v5 = 0;
    if (!gSM_CXCURSOR)
    {
        gSM_CXCURSOR = GetSystemMetrics(SM_CXCURSOR);
        gSM_CYCURSOR = GetSystemMetrics(SM_CYCURSOR);
    }
    Point.x = a2;
    Point.y = a3;
    if (hWnd)
        ClientToScreen(hWnd, &Point);
    GetCursorPos(&pCursorPos);
    if (gSM_CXCURSOR + pCursorPos.x > Point.x
        && pCursorPos.x < a4 + Point.x
        && gSM_CYCURSOR + pCursorPos.y > Point.y
        && pCursorPos.y < a5 + Point.y)
    {
        do
            ++v5;
        while (ShowCursor(0) >= 0);
    }
    return v5;
}

int __stdcall BinkRestoreCursor(int restoreCount) {// Проверка на недопустимые значения
    if (restoreCount <= 0) {
        return -1; // Некорректный аргумент
    }

    int currentVisibilityCount = 0;

    // Явно вызываем ShowCursor N раз
    for (int i = 0; i < restoreCount; ++i)
    {
        currentVisibilityCount = ShowCursor(TRUE);
    }

    return currentVisibilityCount; // Возвращаем итоговый счётчик
}

// Выделяет память с выравниванием на ALIGNMENT байт
void* __stdcall radmalloc(size_t size)
{
    // Проверка корректности размера
    if (size == 0 || size > static_cast<size_t>(INT_MAX) - ALIGNMENT) {
        return NULL;
    }

    // Выделяем память с запасом
    void* raw_ptr = malloc(size + ALIGNMENT);
    if (raw_ptr == NULL) {
        return NULL;
    }

    // Вычисляем смещение для выравнивания
    const size_t offset = ALIGNMENT - (
        (reinterpret_cast<uintptr_t>(raw_ptr)) & ALIGN_MASK
        );

    // Получаем выровненный указатель
    char* aligned_ptr = static_cast<char*>(raw_ptr) + offset;

    // Сохраняем смещение в байте перед блоком
    *(aligned_ptr - 1) = static_cast<unsigned char>(offset);

    return aligned_ptr;
}

// Освобождает память, выделенную через radmalloc
void __stdcall radfree(void* aligned_ptr)
{
    // Проверка на нулевой указатель
    if (aligned_ptr == nullptr)
    {
        return;
    }

    // 1. Получаем смещение, сохраненное перед выровненным блоком
    const auto offset = *(
        static_cast<const unsigned char*>(aligned_ptr) - 1
        );

    // 2. Восстанавливаем исходный указатель
    void* original_ptr = static_cast<unsigned char*>(aligned_ptr) - offset;

    // 3. Освобождаем память
    free(original_ptr);
}