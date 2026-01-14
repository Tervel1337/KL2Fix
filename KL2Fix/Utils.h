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
};