#include "pch.h"

DWORD WriteLog(LPCTSTR format, ...);
BOOL WINAPI MyBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop);

BOOL(WINAPI* originFunc) (HDC, int, int, int, int, HDC, int, int, DWORD) = BitBlt;
BOOL(WINAPI* detourFunc) (HDC, int, int, int, int, HDC, int, int, DWORD) = MyBitBlt;

DWORD WriteLog(LPCTSTR lpszFormat, ...) {
	TCHAR szLog[512];
	DWORD dwCharsWritten;

	va_list args;
	va_start(args, lpszFormat);
	_vstprintf_s(szLog, 512, lpszFormat, args);
	va_end(args);

	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), szLog, _tcslen(szLog), &dwCharsWritten, NULL);

	return dwCharsWritten;
}

BOOL WINAPI MyBitBlt(HDC hdc, int x, int y, int cx, int cy, HDC hdcSrc, int x1, int y1, DWORD rop) {
	WriteLog(TEXT("Function called : Bitblt(0x%X, %d, %d, %d, %d, 0x%X, %d, %d, 0x%X)\n"),
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
		DetourAttach(&(PVOID&)originFunc, detourFunc);
		DetourTransactionCommit();
		break;
	case DLL_PROCESS_DETACH:
		FreeConsole();
		DetourTransactionBegin();
		DetourUpdateThread(GetCurrentThread());
		DetourDetach(&(PVOID&)originFunc, detourFunc);
		DetourTransactionCommit();
		break;
	}

	return TRUE;
}