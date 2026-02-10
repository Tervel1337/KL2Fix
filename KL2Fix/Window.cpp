#include "Window.h"

const int WndProc = 0x00714810_g;
LRESULT __stdcall WndProcHook(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam) {
    if (Msg == WM_CLOSE) ExitProcess(EXIT_SUCCESS);
    return ((LRESULT(__stdcall*)(HWND, UINT, WPARAM, LPARAM))WndProc)(hWnd, Msg, wParam, lParam);
}

void Window::Install() {
    if (GetPrivateProfileIntA("KL2Fix", "BorderlessWindowed", 0, ConfigPath) == 1) {
        Patch<char>(0x00CDADB8, 0); // force windowed
        Nop(0x0056B969, 2); // override style
        Patch<int>(0x0056B96C, WS_POPUP | WS_VISIBLE);
        Patch<int>(0x006FCA89, WS_EX_APPWINDOW);
        Patch<char>(0x005C0DCD, 0x14); // fix res
        Patch<char>(0x005C0DD2, 0x10);
        Patch<char>(0x0056BB56, SW_SHOWMAXIMIZED);
    }

    if (GetPrivateProfileIntA("KL2Fix", "FixSecondMonitor", 1, ConfigPath) == 1) Patch<char>(0x0043F220, 0xC3);

    if (GetPrivateProfileIntA("KL2Fix", "TrueAltF4", 0, ConfigPath) == 1) Patch<int>(0x006FCAD0, (int)&WndProcHook);
}