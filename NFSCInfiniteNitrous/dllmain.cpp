#include <windows.h>
#include <cstring>

void Init()
{
    DWORD baseAddress = reinterpret_cast<DWORD>(GetModuleHandleA("NFSC.exe"));
    
    constexpr unsigned char patch[4] =
    {
        0xB0, 0x01, // mov al, 1
        0x90,       // nop
		0x90        // nop
    };

    std::memcpy(reinterpret_cast<void*>(baseAddress + 0xAAE8B), patch, 4);
}

extern "C" __declspec(dllexport) void InitializeASI() {
    // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
    // Simplified condition for clarity; logic unchanged, there were a few redundant operations

    uintptr_t base = (uintptr_t)GetModuleHandleA(nullptr);
    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)(base);
    IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)(base + dos->e_lfanew);

    if (nt->OptionalHeader.AddressOfEntryPoint == 0x47E926)
        Init();

    else
        MessageBoxA(nullptr, "This .exe is not supported.\nPlease use v1.4 English nfsc.exe (6,88 MB (7.217.152 bytes)).", "NFSC Infinite Speedbreaker by Kevin4e", MB_ICONERROR);
}

BOOL APIENTRY DllMain(HMODULE, DWORD, LPVOID)
{
    return TRUE;
}