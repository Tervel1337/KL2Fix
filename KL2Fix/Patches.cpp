#include "Patches.h"
#include "Window.h"
#include "GPU.h"
#include "Misc.h"
#include "FileLoader.h"

void Patches::Init() {
    GPU::Install();
    Misc::Install();
    Window::Install();
    FileLoader::Install();
}