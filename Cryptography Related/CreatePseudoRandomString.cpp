PWCHAR CreatePseudoRandomStringW(SIZE_T dwLength)
{
	WCHAR DataSet[] = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	PWCHAR String = NULL;

	String = (PWCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (sizeof(WCHAR) * (dwLength + 1)));
	if (String == NULL)
		return NULL;

#pragma warning (push)
#pragma warning (disable: 4018)
	for (INT dwN = 0; dwN < dwLength; dwN++)
	{
		INT Key = CreatePseudoRandomInteger() % (INT)(StringLengthW(DataSet) - 1);
		String[dwN] = DataSet[Key];
	}
#pragma warning (pop)

#pragma warning (push)
#pragma warning (disable: 6386)
	String[dwLength] = '\0';
#pragma warning (pop)

	return String;
}

PCHAR CreatePseudoRandomStringA(SIZE_T dwLength)
{
	CHAR DataSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	PCHAR String = NULL;

	String = (PCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (sizeof(CHAR) * (dwLength + 1)));
	if (String == NULL)
		return NULL;

#pragma warning (push)
#pragma warning (disable: 4018)
	for (INT dwN = 0; dwN < dwLength; dwN++)
	{
		INT Key = CreatePseudoRandomInteger() % (INT)(StringLengthA(DataSet) - 1);
		String[dwN] = DataSet[Key];
	}
#pragma warning (pop)

#pragma warning (push)
#pragma warning (disable: 6386)
	String[dwLength] = '\0';
#pragma warning (pop)

	return String;
}
