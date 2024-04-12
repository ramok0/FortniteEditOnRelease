#include <Windows.h>
#include <iostream>

#include <edit_on_release.h>

void dll_main() {
    AllocConsole();
    freopen_s(reinterpret_cast<FILE**>(stdout), "CONOUT$", "w", stdout);

    if (!EditOnRelease::find_functions()) {
        std::cout << "Failed to find functions !" << std::endl;
    }

    if (EditOnRelease::place_hooks()) {
        std::cout << "Hooks placed successfully!" << std::endl;
    }

    std::cout << "The edit on release is ready !"
        << std::endl
        << "Press F3 to Toggle Edit On Release"
        << std::endl;

    while (true) {

        if (GetAsyncKeyState(VK_F3) & 1) {
            EditOnRelease::g_UseEditOnRelease = !EditOnRelease::g_UseEditOnRelease;
            std::cout << "Edit On Release: " << (EditOnRelease::g_UseEditOnRelease ? "Enabled" : "Disabled") << std::endl;
        }

        Sleep(1000);
    }
}


BOOL APIENTRY DllMain(
    HMODULE hModule,
    DWORD  ul_reason_for_call,
    LPVOID lpReserved
)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH) {
        CreateThread(0, 0, (LPTHREAD_START_ROUTINE)dll_main, 0, 0, 0);
    }

    return TRUE;
}