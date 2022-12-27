#include "Win32Helper.h"

ULONG HashStringFowlerNollVoVariant1aA(_In_ LPCSTR String)
{
	ULONG Hash = 0x811c9dc5;

	while (*String)
	{
		Hash ^= (UCHAR)*String++;
		Hash *= 0x01000193;
	}

	return Hash;
}

ULONG HashStringFowlerNollVoVariant1aW(_In_ LPCWSTR String)
{
	ULONG Hash = 0x811c9dc5;

	while (*String)
	{
		Hash ^= (UCHAR)*String++;
		Hash *= 0x01000193;
	}

	return Hash;
}