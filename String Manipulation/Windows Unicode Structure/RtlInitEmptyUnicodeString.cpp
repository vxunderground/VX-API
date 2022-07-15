VOID RtlInitEmptyUnicodeString(PUNICODE_STRING UnicodeString, PWCHAR Buffer, USHORT BufferSize)
{
	UnicodeString->Length = 0;
	UnicodeString->MaximumLength = BufferSize;
	UnicodeString->Buffer = Buffer;

	return;
}
