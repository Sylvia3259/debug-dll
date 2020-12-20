#pragma once
#include "pch.h"

DWORD WriteLogA(LPCSTR lpszFormat, ...);
DWORD WriteLogW(LPCWSTR lpszFormat, ...);

#ifdef UNICODE
#define WriteLog  WriteLogW
#else
#define WriteLog  WriteLogA
#endif