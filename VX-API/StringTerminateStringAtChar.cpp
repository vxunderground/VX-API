#include "StringManipulation.h"

PCHAR StringTerminateStringAtCharA(_Inout_ PCHAR String, _In_ INT Character)
{
	DWORD Length = (DWORD)StringLengthA(String);

	for (DWORD Index = 0; Index < Length; Index++)
	{
		if (String[Index] == Character)
		{
			String[Index] = '\0';
			return String;
		}
	}

	return NULL;
}

PWCHAR StringTerminateStringAtCharW(_Inout_ PWCHAR String, _In_ INT Character)
{
	DWORD Length = (DWORD)StringLengthW(String);

	for (DWORD Index = 0; Index < Length; Index++)
	{
		if (String[Index] == Character)
		{
			String[Index] = '\0';
			return String;
		}
	}

	return NULL;
}