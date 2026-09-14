# Bink

- **Место**: `gta2/Engine/Bink/`
- **Файлы**: `.cpp` 185 строк, `.h` 70 строк
- **Методов**: 18
- **Полностью реализовано**: 18
- **Частично (TODO/незавершено)**: 0
- **Заглушки**: 0
- **Объявлено, но не определено**: 0
- **Реализация в целом: ~100%** (полные + 0.5*частичные)

## Полностью реализованные методы

| метод | строка | строк кода | адрес из дампа |
|---|---|---|---|
| `Open(const char* filename, unsigned int flags = 0)` | 41 | 8 |  |
| `Close()` | 50 | 9 |  |
| `IsOpen()` | 60 | 4 |  |
| `BufferOpen(HWND hWnd, int width, int height, int flags)` | 65 | 7 |  |
| `BufferClose()` | 73 | 11 |  |
| `IsBufferOpen()` | 85 | 4 |  |
| `DoFrame()` | 90 | 5 |  |
| `NextFrame()` | 96 | 5 |  |
| `Wait()` | 102 | 5 |  |
| `CopyToBuffer(void* dst, int dstPitch, int dstBpp, int srcX, int srcY, int width, int height, int flags)` | 108 | 5 |  |
| `CopyToBufferSlow(void* dst, int dstPitch, int dstBpp, int srcX, int srcY, int width, int height, int flags)` | 114 | 5 |  |
| `BufferBlit(int flags)` | 120 | 5 |  |
| `BufferLock()` | 126 | 5 |  |
| `BufferUnlock()` | 132 | 5 |  |
| `BufferSetOffset(int x, int y)` | 138 | 7 |  |
| `GetSummary(BINKSUMMARY* pSummary)` | 146 | 8 |  |
| `SetSoundSystem(void* soundSystem, void* param)` | 155 | 5 |  |
| `SetIOSize(unsigned int ioSize)` | 161 | 5 |  |
