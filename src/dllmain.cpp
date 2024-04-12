// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"

void Main() {
    //Sleep(60000);

    EditOnRelease::FunctionPointers functions = EditOnRelease::find_functions();

    EditOnRelease::original_functions::CompleteBuildingEditInteraction = functions.CompleteBuildingEditInteraction;

    if (!EditOnRelease::place_hooks(functions)) {
        MessageBoxA(nullptr, "Failed to place hooks", "FortniteEditOnRelease", MB_ICONERROR);
        return;
    }

    std::cout << "The edit on release is ready !"
        << std::endl
        << "Press F3 to Toggle Edit On Release";

    while (true) {

        if (GetAsyncKeyState(VK_F3) & 1) {
            EditOnRelease::g_UseEditOnRelease = !EditOnRelease::g_UseEditOnRelease;
            std::cout << "Edit On Release: " << (EditOnRelease::g_UseEditOnRelease ? "Enabled" : "Disabled") << std::endl;
        }

        Sleep(1000);
    }
}

BOOL WINAPI DllMain(
    HINSTANCE hinstDLL,  // handle to DLL module
    DWORD fdwReason,     // reason for calling function
    LPVOID lpvReserved)  // reserved
{
    //  DisableThreadLibraryCalls(hinstDLL);

    if (fdwReason == DLL_PROCESS_ATTACH)
    {
        CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)Main, nullptr, 0, nullptr);
    }
}