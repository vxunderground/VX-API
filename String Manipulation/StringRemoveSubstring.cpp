PCHAR StringRemoveSubstringA(PCHAR String, CONST PCHAR Substring)
{
	DWORD Length = (DWORD)StringLengthA(Substring);
	PCHAR pPointer = String;

	if (Length == 0)
		return NULL;

	while ((pPointer = StringFindSubstringA(pPointer, Substring)) != NULL)
		RfCopyMemory(pPointer, pPointer + Length, StringLengthA(pPointer + Length) + 1);

	return String;
}

PWCHAR StringRemoveSubstringW(PWCHAR String, CONST PWCHAR Substring)
{
	DWORD Length = (DWORD)StringLengthW(Substring);
	PWCHAR pPointer = String;

	if (Length == 0)
		return NULL;

	while ((pPointer = StringFindSubstringW(pPointer, Substring)) != NULL)
		RfCopyMemory(pPointer, pPointer + Length, StringLengthW(pPointer + Length) + 1);

	return String;
}
