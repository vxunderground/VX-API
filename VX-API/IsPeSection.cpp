#include "Win32Helper.h"

BOOL IsPeSectionW(_In_ LPCWSTR PathToBinary, _In_ LPCWSTR PeSectionName)
{
	BOOL bFlag = FALSE;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	PBYTE Buffer = NULL;
	LONGLONG SizeOfTargetBinary = 0L;

	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;

	PIMAGE_SECTION_HEADER Section = NULL;
	PIMAGE_SECTION_HEADER SectionHeaderArray = NULL;

	CHAR SectionName[32] = { 0 };

	if (WCharStringToCharString(SectionName, (PWCHAR)PeSectionName, StringLengthW(PeSectionName)) == 0)
		goto EXIT_ROUTINE;

	SizeOfTargetBinary = GetFileSizeFromPathW((PWCHAR)PathToBinary, FILE_ATTRIBUTE_NORMAL);
	if (SizeOfTargetBinary == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	hHandle = CreateFileW(PathToBinary, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	Buffer = (PBYTE)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, SizeOfTargetBinary);
	if (Buffer == NULL)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, Buffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	if (!RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &Buffer))
		goto EXIT_ROUTINE;

	SectionHeaderArray = (PIMAGE_SECTION_HEADER)(ULONGLONG(Nt) + sizeof(IMAGE_NT_HEADERS));
	for (DWORD dwX = 0; dwX < File->NumberOfSections; dwX++)
	{
		if (StringCompareA((PCHAR)SectionHeaderArray[dwX].Name, SectionName) == ERROR_SUCCESS)
			bFlag = TRUE;
	}

EXIT_ROUTINE:

	if (Buffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Buffer);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}

BOOL IsPeSectionA(_In_ LPCSTR PathToBinary, _In_ LPCSTR PeSectionName)
{
	BOOL bFlag = FALSE;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	PBYTE Buffer = NULL;
	LONGLONG SizeOfTargetBinary = 0L;

	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;

	PIMAGE_SECTION_HEADER Section = NULL;
	PIMAGE_SECTION_HEADER SectionHeaderArray = NULL;

	SizeOfTargetBinary = GetFileSizeFromPathW((PWCHAR)PathToBinary, FILE_ATTRIBUTE_NORMAL);
	if (SizeOfTargetBinary == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	hHandle = CreateFileA(PathToBinary, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	Buffer = (PBYTE)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, SizeOfTargetBinary);
	if (Buffer == NULL)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, Buffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	if (!RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &Buffer))
		goto EXIT_ROUTINE;

	SectionHeaderArray = (PIMAGE_SECTION_HEADER)(ULONGLONG(Nt) + sizeof(IMAGE_NT_HEADERS));
	for (DWORD dwX = 0; dwX < File->NumberOfSections; dwX++)
	{
		if (StringCompareA((PCHAR)SectionHeaderArray[dwX].Name, PeSectionName) == ERROR_SUCCESS)
			bFlag = TRUE;
	}

EXIT_ROUTINE:

	if (Buffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Buffer);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}