#include "Patches.h"
#include "Window.h"
#include "GPU.h"
#include "Misc.h"

void Patches::Init() {
    GPU::Install();
    Misc::Install();
    Window::Install();
}