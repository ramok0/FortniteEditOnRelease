#pragma once

#include <polyhook2/Detour/x64Detour.hpp>

namespace EditOnRelease {
	namespace strings {
		constexpr const wchar_t* EditModeInputComponent = L"EditModeInputComponent0";
		constexpr const char* CompleteBuildingEditInteraction = "CompleteBuildingEditInteraction";
	}

	namespace original_functions {
		inline void* (*BuildingEditReset)(void*);
		inline void* (*EditSelect)(void*);
	}

	namespace addresses {
		inline void* (*BuildingEditReset)(void*);
		inline void* (*EditSelect)(void*);
		inline char(*CompleteBuildingEditInteraction)(void*);
	}

	namespace hooks {
		void* __fastcall BuildingEditReset(void* a1);
		void* __fastcall EditSelect(void* a1);

		inline PLH::x64Detour* BuildingEditResetHook;
		inline PLH::x64Detour* EditSelectHook;
	}

	inline bool g_UseEditOnRelease = true;

	bool find_functions(void);

	bool place_hooks();
}