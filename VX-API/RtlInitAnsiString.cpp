#include "StringManipulation.h"

VOID RtlInitAnsiString(_Inout_ PANSI_STRING DestinationString, _In_ PCSTR SourceString)
{
    SIZE_T Size;

    if (SourceString)
    {
        Size = StringLengthA(SourceString);
        if (Size > (65535 - sizeof(CHAR))) Size = 65535 - sizeof(CHAR);
        DestinationString->Length = (USHORT)Size;
        DestinationString->MaximumLength = (USHORT)Size + sizeof(CHAR);
    }
    else
    {
        DestinationString->Length = 0;
        DestinationString->MaximumLength = 0;
    }

    DestinationString->Buffer = (PCHAR)SourceString;
}