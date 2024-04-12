
#include <edit_on_release.h>
#include <Windows.h>
#include <memcury.h>



#pragma comment(lib, "lib/polyhook2.lib")
#pragma comment(lib, "lib/asmjit.lib")
#pragma comment(lib, "lib/asmtk.lib")
#pragma comment(lib, "lib/Zydis.lib")

bool EditOnRelease::find_functions(void)
{
    addresses::EditSelect = Memcury::Scanner::FindStringRef(L"EditModeInputComponent0")
        .ScanFor({ 0x48, 0x8d, 0x05 }, true, 1)
        .RelativeOffset(3)
        .GetAs<decltype(addresses::EditSelect)>();

    addresses::BuildingEditReset = Memcury::Scanner::FindStringRef(strings::EditModeInputComponent)
        .ScanFor({ 0x48, 0x8d, 0x05 }, true, 2)
        .RelativeOffset(3)
        .GetAs<decltype(addresses::EditSelect)>();

    addresses::CompleteBuildingEditInteraction = Memcury::Scanner::FindStringRef(strings::CompleteBuildingEditInteraction, true)
        .ScanFor({ 0x48, 0x8D }, false, 0)
        .RelativeOffset(3)
        .GetAs<decltype(addresses::CompleteBuildingEditInteraction)>();

    return true;
}

void* __fastcall EditOnRelease::hooks::BuildingEditReset(void* a1)
{
    void* result = EditOnRelease::original_functions::BuildingEditReset(a1);

    if (EditOnRelease::g_UseEditOnRelease) {
        EditOnRelease::addresses::CompleteBuildingEditInteraction(a1);
    }

    return result;
}

void* __fastcall EditOnRelease::hooks::EditSelect(void* a1)
{
    void* result = EditOnRelease::original_functions::EditSelect(a1);

    if (EditOnRelease::g_UseEditOnRelease) {
        EditOnRelease::addresses::CompleteBuildingEditInteraction(a1);
    }

    return result;
}

bool EditOnRelease::place_hooks()
{
    hooks::EditSelectHook = new PLH::x64Detour((uint64_t)addresses::EditSelect, (uint64_t)EditOnRelease::hooks::EditSelect, (uint64_t*)&EditOnRelease::original_functions::EditSelect);
    hooks::BuildingEditResetHook = new PLH::x64Detour((uint64_t)addresses::BuildingEditReset, (uint64_t)EditOnRelease::hooks::BuildingEditReset, (uint64_t*)&EditOnRelease::original_functions::BuildingEditReset);

    return hooks::EditSelectHook->hook() && hooks::BuildingEditResetHook->hook();
}