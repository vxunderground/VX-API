#include "StringManipulation.h"

VOID RtlInitEmptyUnicodeString(_Inout_ PUNICODE_STRING UnicodeString, _In_ PWCHAR Buffer, _In_ USHORT BufferSize)
{
	UnicodeString->Length = 0;
	UnicodeString->MaximumLength = BufferSize;
	UnicodeString->Buffer = Buffer;

	return;
}