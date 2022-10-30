#include "Win32Helper.h"

INT ShlwapiWCharStringToCharString(_In_ PWCHAR InString, _Inout_ PCHAR OutString, _In_ INT BufferSize)
{
	return SHUnicodeToAnsi(InString, OutString, BufferSize);
}