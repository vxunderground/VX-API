#include "Win32Helper.h"

DWORD HashStringDjb2A(_In_ LPCSTR String)
{
	ULONG Hash = 5381;
	INT c = 0;

	while (c = *String++)
		Hash = ((Hash << 5) + Hash) + c;

	return Hash;
}

DWORD HashStringDjb2W(_In_ LPCWSTR String)
{
	ULONG Hash = 5381;
	INT c = 0;

	while (c = *String++)
		Hash = ((Hash << 5) + Hash) + c;

	return Hash;
}