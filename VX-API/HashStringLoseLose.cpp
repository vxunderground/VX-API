#include "Win32Helper.h"

DWORD HashStringLoseLoseA(_In_ LPCSTR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash += c;

	return Hash;
}

DWORD HashStringLoseLoseW(_In_ LPCWSTR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash += c;

	return Hash;
}