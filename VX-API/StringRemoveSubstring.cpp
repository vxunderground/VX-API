#include "StringManipulation.h"

PCHAR StringRemoveSubstringA(_Inout_ PCHAR String, _In_ CONST PCHAR Substring)
{
	DWORD Length = (DWORD)StringLengthA(Substring);
	PCHAR pPointer = String;

	if (Length == 0)
		return NULL;

	while ((pPointer = StringFindSubstringA(pPointer, Substring)) != NULL)
		CopyMemoryEx(pPointer, pPointer + Length, StringLengthA(pPointer + Length) + 1);

	return String;
}

PWCHAR StringRemoveSubstringW(_Inout_ PWCHAR String, _In_ CONST PWCHAR Substring)
{
	DWORD Length = (DWORD)StringLengthW(Substring);
	PWCHAR pPointer = String;

	if (Length == 0)
		return NULL;

	while ((pPointer = StringFindSubstringW(pPointer, Substring)) != NULL)
		CopyMemoryEx(pPointer, pPointer + Length, StringLengthW(pPointer + Length) + 1);

	return String;
}