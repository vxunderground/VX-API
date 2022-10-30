#include "Win32Helper.h"

INT ShlwapiCharStringToWCharString(_In_ PCHAR InString, _Inout_ PWCHAR OutString, _In_ INT BufferSize)
{
	return SHAnsiToUnicode(InString, OutString, BufferSize);
}