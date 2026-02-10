#pragma once
#include <MemoryMgr.h>
#define ARRAY_SIZE(v) (sizeof(v) / sizeof(v[0]))
using namespace Memory::VP::DynBase;
inline const char* ConfigPath = ".\\KL2Fix.ini";

inline uintptr_t operator""_g(unsigned long long val)
{
    return DynBaseAddress(static_cast<uintptr_t>(val));
}

class Utils {
public:
    static void ReplaceShader(int Address, unsigned char(&Dest)[], int Size) {
        Patch(Address, Size);
        Patch(Address + 5, (int)Dest);
    }

    static void LAAPatch() {
        HMODULE Module = GetModuleHandleA(nullptr);
        auto* DOS = (IMAGE_DOS_HEADER*)Module;
        auto* NT = (IMAGE_NT_HEADERS*)((BYTE*)Module + DOS->e_lfanew);

        if (NT->FileHeader.Characteristics & IMAGE_FILE_LARGE_ADDRESS_AWARE) return;

        if (MessageBoxA(nullptr,"Your game isn't LAA patched!\nThis can cause heap allocation crashes.\nPatch it now?", "LAA Patch", MB_YESNO | MB_ICONQUESTION) != IDYES) return;

        char ExePath[MAX_PATH];
        GetModuleFileNameA(nullptr, ExePath, MAX_PATH);

        char TempPath[MAX_PATH];
        char BakPath[MAX_PATH];
        sprintf_s(TempPath, "%s.laa", ExePath);
        sprintf_s(BakPath, "%s.bak", ExePath);

        DeleteFileA(TempPath);
        DeleteFileA(BakPath);

        if (!CopyFileA(ExePath, TempPath, FALSE)) {
            MessageBoxA(nullptr, "Failed to copy executable.\nTry running as admin.", "LAA Patch", MB_ICONERROR);
            return;
        }

        FILE* File = nullptr;
        if (fopen_s(&File, TempPath, "rb+") || !File) {
            DeleteFileA(TempPath);
            MessageBoxA(nullptr, "Failed to open temp file!\nTry running as admin.", "LAA Patch", MB_ICONERROR);
            return;
        }

        IMAGE_DOS_HEADER DOSHeader{};
        IMAGE_NT_HEADERS NTHeader{};

        fread(&DOSHeader, sizeof(DOSHeader), 1, File);
        fseek(File, DOSHeader.e_lfanew, SEEK_SET);
        fread(&NTHeader, sizeof(NTHeader), 1, File);

        NTHeader.FileHeader.Characteristics |= IMAGE_FILE_LARGE_ADDRESS_AWARE;

        fseek(File, DOSHeader.e_lfanew, SEEK_SET);
        fwrite(&NTHeader, sizeof(NTHeader), 1, File);

        fclose(File);

        MoveFileExA(ExePath, BakPath, MOVEFILE_REPLACE_EXISTING);

        if (!MoveFileA(TempPath, ExePath)) {
            MoveFileA(BakPath, ExePath);
            MessageBoxA(nullptr, "Failed to replace executable!\n\nTry running as admin.", "LAA Patch", MB_ICONERROR);
            return;
        }

        MessageBoxA(nullptr, "LAA patch applied successfully!\nBackup created.\n\nThe game will restart when you close this window.", "LAA Patch", MB_ICONINFORMATION);

        STARTUPINFOA StartupInfo{};
        PROCESS_INFORMATION ProcessInformation{};
        StartupInfo.cb = sizeof(StartupInfo);

        if (CreateProcessA(
            ExePath,
            nullptr, 
            nullptr,
            nullptr,
            FALSE,
            0,
            nullptr,
            nullptr,
            &StartupInfo,
            &ProcessInformation)) {
            CloseHandle(ProcessInformation.hThread);
            CloseHandle(ProcessInformation.hProcess);
        }

        ExitProcess(ERROR_SUCCESS);
    };
};