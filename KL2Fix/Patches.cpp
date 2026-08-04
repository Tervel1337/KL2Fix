#include "Patches.h"
#include "Window.h"
#include "GPU.h"
#include "Misc.h"
#include "FileLoader.h"
#include "Gameplay.h"
#include "CEG.h"
void Patches::Init() {
    CEG::Install();
    if (GetPrivateProfileIntA("KL2Fix", "DisableLAAPatcher", 0, ConfigPath) == 0) Utils::LAAPatch();
    GPU::Install();
    Misc::Install();
    Window::Install();
    FileLoader::Install();
    Gameplay::Install();
}