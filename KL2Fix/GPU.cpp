#include "GPU.h"
#include "Timing.h"
#include "Shaders.h"

int SetPSConstFAddr = 0x006985E0_g;
void SetPixelShaderConstantF(int Reg, float* Data, int N) {
    ((int(__cdecl*)(int, float*, int))SetPSConstFAddr)(Reg, Data, N);
}

void __cdecl FixNoiseUV(int Reg, float* Data, int N) {
    static float LastY = 0.0f, LastZ = 0.0f, Acc = 0.0f;
    float FT = (Timing::Frametime > 0 && Timing::Frametime <= 0.1f) ? Timing::Frametime : Timing::FT60FPS;

    if (FT >= Timing::FT60FPS) {
        Acc = 0.0f;
        SetPixelShaderConstantF(Reg, Data, N);
        return;
    }

    Acc += FT;
    if (Acc >= Timing::FT60FPS) {
        Acc -= Timing::FT60FPS;
        LastY = Data[1];
        LastZ = Data[2];
    }

    Data[1] = LastY;
    Data[2] = LastZ;

    SetPixelShaderConstantF(Reg, Data, N);
}

void GPU::Install() {
    InjectHook(0x00793A1A, &FixNoiseUV, HookType::Call);

    Utils::ReplaceShader(0x004167F2, NoiseShader, sizeof(NoiseShader));
    Utils::ReplaceShader(0x00416927, ExposureShader, sizeof(ExposureShader));
}