#include "StringManipulation.h"

VOID ByteArrayToCharArrayA(PCHAR Destination, PBYTE Source, DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
	{
		Destination[dwX] = (BYTE)Source[dwX];
	}
}

VOID ByteArrayToCharArrayW(PWCHAR Destination, PBYTE Source, DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
	{
		Destination[dwX] = (BYTE)Source[dwX];
	}
}