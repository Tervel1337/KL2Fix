#include "GPU.h"
#include "Timing.h"
#include "Shaders.h"

// these values are used on console as well as when you have sharpen disabled on PC
#define BASE_RES_WIDTH 1024.0f
#define BASE_RES_HEGIHT 600.0f

const int& D3DDevice = *(int*)0x00DD2640_g;

float GetScale() {
    int Width = *(int*)(D3DDevice + 0x90);
    return Width / BASE_RES_WIDTH;
}

const int SetPSConstFAddr = 0x006985E0_g;
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

void __cdecl ScaleCA(int Reg, float* Data, int N) {
    float Scale = GetScale();
	Data[0] *= Scale;
	Data[1] *= Scale;
    Data[3] *= Scale;
    SetPixelShaderConstantF(Reg, Data, N);
}

void __cdecl ScaleSSAO(int Reg, float* Data, int N) {
    float Scale = GetScale();
    Data[0] *= Scale;
    SetPixelShaderConstantF(Reg, Data, N);
}

void GPU::Install() {
    InjectHook(0x00793A1A, &FixNoiseUV, HookType::Call);
	InjectHook(0x00611B1A, &ScaleCA, HookType::Call);
    InjectHook(0x007C299E, &ScaleSSAO, HookType::Call);

    Utils::ReplaceShader(0x004167F2, NoiseShader, sizeof(NoiseShader));
    Utils::ReplaceShader(0x00416927, ExposureShader, sizeof(ExposureShader));
}