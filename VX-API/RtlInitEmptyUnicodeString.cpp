#include "StringManipulation.h"

VOID RtlInitEmptyUnicodeString(_Inout_ PUNICODE_STRING UnicodeString)
{
	UnicodeString->Length = 0;
	UnicodeString->MaximumLength = sizeof(UNICODE_STRING);
	UnicodeString->Buffer = NULL;

	return;
}