#include "StringManipulation.h"

VOID ByteArrayToCharArrayA(_Inout_ PCHAR Destination, _In_ PBYTE Source, _In_ DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
		Destination[dwX] = (BYTE)Source[dwX];
}

VOID ByteArrayToCharArrayW(_Inout_ PWCHAR Destination, _In_ PBYTE Source, _In_ DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
		Destination[dwX] = (BYTE)Source[dwX];
}