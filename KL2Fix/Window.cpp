#include "Window.h"

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
}