#include "stdafx.h"
#include "Interface/Init.h"
#include "utils/smc.h"
#include <xkelib.h>

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	switch (ul_reason_for_call) {
		case DLL_PROCESS_ATTACH:
			if (!smc::is_tray_open() || XboxKrnlVersion->Build != KERNEL_VERSION) {
				HANDLE hThread; DWORD hThreadID;
				ExCreateThread(&hThread, 0, &hThreadID, (PVOID)XapiThreadStartup, (LPTHREAD_START_ROUTINE)init::entry, hModule, 0x1c000427);
				XSetThreadProcessor(hThread, 4);
				ResumeThread(hThread);
				CloseHandle(hThread);
				return TRUE;
			}

			break;

		case DLL_PROCESS_DETACH:
			FreeLibraryAndExitThread(hModule, 0);
			break;
	}

	*(WORD*)((DWORD)hModule + 64) = 1;
	return FALSE;
}