#include "Gameplay.h"
#include "Timing.h"

bool& AimAssistEnabled = *(bool*)0x00DDB8F4_g;
float& DrainK = *(float*)0x00CEB3EC_g;

const int UpdateTapQTEBar = 0x0077D3A0_g;
void __fastcall UpdateDrainK(float* This) {
    static const float K60 = 0.1350000054f; // this is the vanilla value, which is hardcoded anyway
    float DT = Timing::Frametime * 60.0f;
    DrainK = K60 * powf(DT, 0.70f);

    ((void(__thiscall*)(float*))UpdateTapQTEBar)(This);
}

const int IsTargetSelected = 0x00477730_g;
bool __fastcall IsTargetSelectedHook(int This, void* Dummy, int Target, bool Snap) {
    if (!AimAssistEnabled) return false;
    else return ((bool(__thiscall*)(int, int, bool))IsTargetSelected)(This, Target, Snap);
}

void Gameplay::Install() {
    Patch<char>(0x0077D45C, 0xBA);
    Patch<int>(0x0077D45D, (int)&Timing::FT60FPS); // the tapping itself needs a static frametime
    Nop(0x0077D461, 1);
    Patch<short>(0x0077D463, 0x9002);
    InjectHook(0x005FE81C, &UpdateDrainK, HookType::Call);
    InjectHook(0x005FE566, &UpdateDrainK, HookType::Call);

    InjectHook(0x008FECEA, &IsTargetSelectedHook, HookType::Call);
}