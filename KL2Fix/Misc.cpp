#include "Misc.h"

const char* SkipIntrosStr = "SplashMenuEnd";
const char* DebugMenuStr = "CheatMenu";

void Misc::Install() {
    if (GetPrivateProfileIntA("KL2Fix", "DebugMenu", 0, ConfigPath) == 1) Patch<const char*>(0x007B04B6, DebugMenuStr);
    else if (GetPrivateProfileIntA("KL2Fix", "SkipIntros", 1, ConfigPath) == 1) Patch<const char*>(0x007B04B6, SkipIntrosStr);
}