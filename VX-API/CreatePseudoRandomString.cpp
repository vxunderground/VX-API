#include "Win32Helper.h"

PWCHAR CreatePseudoRandomStringW(_In_ SIZE_T dwLength, _In_ ULONG Seed)
{
	WCHAR DataSet[] = L"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	PWCHAR String = NULL;

	String = (PWCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, (sizeof(WCHAR) * (dwLength + 1)));
	if (String == NULL)
		return NULL;

#pragma warning (push)
#pragma warning (disable: 4018)
	for (INT dwN = 0; dwN < dwLength; dwN++)
	{
		INT Key = CreatePseudoRandomInteger(Seed) % (INT)(StringLengthW(DataSet) - 1);
		String[dwN] = DataSet[Key];
	}
#pragma warning (pop)

#pragma warning (push)
#pragma warning (disable: 6386)
	String[dwLength] = '\0';
#pragma warning (pop)

	return String;
}

PCHAR CreatePseudoRandomStringA(_In_ SIZE_T dwLength, _In_ ULONG Seed)
{
	CHAR DataSet[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
	PCHAR String = NULL;

	String = (PCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, (sizeof(CHAR) * (dwLength + 1)));
	if (String == NULL)
		return NULL;

#pragma warning (push)
#pragma warning (disable: 4018)
	for (INT dwN = 0; dwN < dwLength; dwN++)
	{
		INT Key = CreatePseudoRandomInteger(Seed) % (INT)(StringLengthA(DataSet) - 1);
		String[dwN] = DataSet[Key];
	}
#pragma warning (pop)

#pragma warning (push)
#pragma warning (disable: 6386)
	String[dwLength] = '\0';
#pragma warning (pop)

	return String;
}