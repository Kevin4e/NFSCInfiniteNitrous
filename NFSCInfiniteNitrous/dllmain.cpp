#include <windows.h>
#include <cstring>

void Init()
{
    constexpr unsigned char patch[4] =
    {
        0xB0, 0x01, // mov al, 1
        0x90,       // nop
        0x90        // nop
    };

    std::memcpy(reinterpret_cast<void*>(0x4AAE8B), patch, 4);
}

extern "C" __declspec(dllexport) void InitializeASI() {
    // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
    // Optimizations and simplified condition for clarity; logic unchanged, there were a few redundant operations

    IMAGE_NT_HEADERS* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(0x400108);

    if (nt->OptionalHeader.AddressOfEntryPoint == 0x47E926)
        Init();

    else
        MessageBoxA(nullptr, "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).", "NFSC Infinite Nitrous by Kevin4e", MB_ICONERROR);
}