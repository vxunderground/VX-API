#include "StringManipulation.h"

PWCHAR StringConcatW(_Inout_ PWCHAR String, _In_ PWCHAR String2)
{
	StringCopyW(&String[StringLengthW(String)], String2);

	return String;
}

PCHAR StringConcatA(_Inout_ PCHAR String, _In_ PCHAR String2)
{
	StringCopyA(&String[StringLengthA(String)], String2);

	return String;
}