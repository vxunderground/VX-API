#include "Win32Helper.h"

UINT32 HashStringJenkinsOneAtATime32BitA(_In_ PCHAR String)
{
	SIZE_T Index = 0;
	UINT32 Hash = 0;
	SIZE_T Length = StringLengthA(String);

	while (Index != Length)
	{
		Hash += String[Index++];
		Hash += Hash << 10;
		Hash ^= Hash >> 6;
	}

	Hash += Hash << 3;
	Hash ^= Hash >> 11;
	Hash += Hash << 15;

	return Hash;
}

UINT32 HashStringJenkinsOneAtATime32BitW(_In_ PWCHAR String)
{
	SIZE_T Index = 0;
	UINT32 Hash = 0;
	SIZE_T Length = StringLengthW(String);

	while (Index != Length)
	{
		Hash += String[Index++];
		Hash += Hash << 10;
		Hash ^= Hash >> 6;
	}

	Hash += Hash << 3;
	Hash ^= Hash >> 11;
	Hash += Hash << 15;

	return Hash;
}