#include "StringManipulation.h"

PCHAR SecureStringCopyA(_Inout_ PCHAR String1, _In_ LPCSTR String2, _In_ SIZE_T Size)
{
	PCHAR pChar = String1;

	while (Size-- && (*String1++ = *String2++) != '\0');

	return pChar;
}

PWCHAR SecureStringCopyW(_Inout_ PWCHAR String1, _In_ LPCWSTR String2, _In_ SIZE_T Size)
{
	PWCHAR pChar = String1;

	while (Size-- && (*String1++ = *String2++) != '\0');

	return pChar;
}