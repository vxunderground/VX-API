#include "Win32Helper.h"

BOOL ReadDataFromPeSectionW(_In_ LPCWSTR Path, _In_ LPCWSTR SectionName, _Inout_ PBYTE ReadData, _Inout_opt_ PDWORD DataReadInBytes)
{
	BOOL bFlag = FALSE;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	LONGLONG SizeOfTargetBinary = 0L;

	PBYTE FileBuffer = NULL;
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;

	PIMAGE_SECTION_HEADER Section = NULL;
	PIMAGE_SECTION_HEADER SectionHeaderArray = NULL;

	DWORD NumberOfBytesRead = ERROR_SUCCESS;
	CHAR DisposableObject[32] = { 0 };

	WCharStringToCharString(DisposableObject, (PWCHAR)SectionName, StringLengthW(SectionName));

	SizeOfTargetBinary = GetFileSizeFromPathW((PWCHAR)Path, FILE_ATTRIBUTE_NORMAL);
	if (SizeOfTargetBinary == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	hHandle = CreateFileW(Path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	FileBuffer = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, SizeOfTargetBinary);
	if (FileBuffer == NULL)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, FileBuffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &FileBuffer);

	SectionHeaderArray = (PIMAGE_SECTION_HEADER)(ULONGLONG(Nt) + sizeof(IMAGE_NT_HEADERS));
	for (DWORD dwX = 0; dwX < File->NumberOfSections; dwX++)
	{
		if (StringCompareA((PCHAR)SectionHeaderArray[dwX].Name, DisposableObject) == ERROR_SUCCESS)
		{
			if (SetFilePointer(hHandle, SectionHeaderArray[dwX].PointerToRawData, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
				goto EXIT_ROUTINE;

			if (!ReadFile(hHandle, ReadData, SectionHeaderArray[dwX].SizeOfRawData, &NumberOfBytesRead, NULL))
				goto EXIT_ROUTINE;
			else {

				if (DataReadInBytes != NULL)
					*DataReadInBytes = NumberOfBytesRead;

				break;
			}
		}
	}

	bFlag = TRUE;

EXIT_ROUTINE:

	if (FileBuffer)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, FileBuffer);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}

BOOL ReadDataFromPeSectionA(_In_ LPCSTR Path, _In_ LPCSTR SectionName, _Inout_ PBYTE ReadData, _Inout_opt_ PDWORD DataReadInBytes)
{
	BOOL bFlag = FALSE;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	LONGLONG SizeOfTargetBinary = 0L;

	PBYTE FileBuffer = NULL;
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;

	PIMAGE_SECTION_HEADER Section = NULL;
	PIMAGE_SECTION_HEADER SectionHeaderArray = NULL;

	DWORD NumberOfBytesRead = ERROR_SUCCESS;

	SizeOfTargetBinary = GetFileSizeFromPathA((PCHAR)Path, FILE_ATTRIBUTE_NORMAL);
	if (SizeOfTargetBinary == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	hHandle = CreateFileA(Path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	FileBuffer = (PBYTE)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, SizeOfTargetBinary);
	if (FileBuffer == NULL)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, FileBuffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &FileBuffer);

	SectionHeaderArray = (PIMAGE_SECTION_HEADER)(ULONGLONG(Nt) + sizeof(IMAGE_NT_HEADERS));
	for (DWORD dwX = 0; dwX < File->NumberOfSections; dwX++)
	{
		if (StringCompareA((PCHAR)SectionHeaderArray[dwX].Name, SectionName) == ERROR_SUCCESS)
		{
			if (SetFilePointer(hHandle, SectionHeaderArray[dwX].PointerToRawData, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
				goto EXIT_ROUTINE;

			if (!ReadFile(hHandle, ReadData, SectionHeaderArray[dwX].SizeOfRawData, &NumberOfBytesRead, NULL))
				goto EXIT_ROUTINE;
			else {

				if(DataReadInBytes != NULL)
					*DataReadInBytes = NumberOfBytesRead;

				break;
			}
		}
	}

	bFlag = TRUE;

EXIT_ROUTINE:

	if (FileBuffer)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, FileBuffer);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}