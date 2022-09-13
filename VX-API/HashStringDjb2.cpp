#include "Win32Helper.h"

DWORD HashStringDjb2A(_In_ PCHAR String)
{
	ULONG Hash = 5381;
	INT c;

	while (c = *String++)
		Hash = ((Hash << 5) + Hash) + c;

	return Hash;
}

DWORD HashStringDjb2W(_In_ PWCHAR String)
{
	ULONG Hash = 5381;
	INT c;

	while (c = *String++)
		Hash = ((Hash << 5) + Hash) + c;

	return Hash;
}