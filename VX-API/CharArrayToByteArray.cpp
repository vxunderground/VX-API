#include "StringManipulation.h"

VOID CharArrayToByteArrayA(_In_ PCHAR Char, _Inout_ PBYTE Byte, _In_ DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
		Byte[dwX] = (BYTE)Char[dwX];
}

VOID CharArrayToByteArrayW(_In_ PWCHAR Char, _Inout_ PBYTE Byte, _In_ DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
		Byte[dwX] = (BYTE)Char[dwX];
}