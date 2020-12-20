#include "pch.h"
#include "debug.h"

typedef BOOL(WINAPI* ORGFP) (HDC, int, int, int, int, HDC, int, int, DWORD);
ORGFP originFunc = BitBlt;

BOOL WINAPI DetourFunc(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop) {
	WriteLog(TEXT("Function called : BitBlt(0x%X, %d, %d, %d, %d, 0x%X, %d, %d, 0x%X)\n"),
		(DWORD)hdc, x, y, cx, cy, (DWORD)hdcSrc, x1, y1, rop);

	return originFunc(hdc, x, y, cx, cy, hdcSrc, x1, y1, rop);
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
	if (DetourIsHelperProcess())
		return TRUE;

	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		AllocConsole();
		DetourRestoreAfterWith();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourAttach(&(PVOID&)originFunc, DetourFunc);
		DetourTransactionCommit();
		break;
	case DLL_PROCESS_DETACH:
		FreeConsole();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)originFunc, DetourFunc);
		DetourTransactionCommit();
		break;
	}

	return TRUE;
}