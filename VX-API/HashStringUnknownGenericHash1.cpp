#include "Win32Helper.h"

INT HashStringUnknownGenericHash1A(_In_ LPCSTR String)
{
	PCHAR Pointer;
	INT Generic;
	INT Hash = 0;

	for (Pointer = (PCHAR)String; *Pointer != '\0'; Pointer++)
	{
		Hash = (Hash << 4) + (INT)(*Pointer);
		Generic = Hash & 0xF0000000L;

		if (Generic != 0)
			Hash = Hash ^ (Generic >> 24);

		Hash = Hash & ~Generic;
	}

	return Hash;
}

INT HashStringUnknownGenericHash1W(_In_ LPCWSTR String)
{
	PWCHAR Pointer;
	INT Generic;
	INT Hash = 0;

	for (Pointer = (PWCHAR)String; *Pointer != '\0'; Pointer++)
	{
		Hash = (Hash << 4) + (INT)(*Pointer);
		Generic = Hash & 0xF0000000L;

		if (Generic != 0)
			Hash = Hash ^ (Generic >> 24);

		Hash = Hash & ~Generic;
	}

	return Hash;
}