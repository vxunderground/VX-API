#include "Win32Helper.h"

DWORD AlignSection(_In_ DWORD Size, _In_ DWORD Align, _In_ DWORD Address)
{
	if (!(Size % Align))
		return Address + Size;

	return Address + (Size / Align + 1) * Align;
}

BOOL AddSectionToPeFileW(_In_ LPCWSTR Path, _In_ LPCWSTR SectionName, _In_ DWORD SectionSizeInBytes)
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
	WORD Offset = ERROR_SUCCESS;

	DWORD SectionCharacteristics = ERROR_SUCCESS;

	CHAR DisposeableObject[32] = { 0 };

	if (WCharStringToCharString(DisposeableObject, (PWCHAR)SectionName, StringLengthW(SectionName)) == 0)
		goto EXIT_ROUTINE;

	if(IsPeSectionW(Path, SectionName))
		return TRUE;

	SizeOfTargetBinary = GetFileSizeFromPathW((PWCHAR)Path, FILE_ATTRIBUTE_NORMAL);
	if (SizeOfTargetBinary == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	hHandle = CreateFileW(Path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	FileBuffer = (PBYTE)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, SizeOfTargetBinary);
	if (FileBuffer == NULL)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, FileBuffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	if (!RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &FileBuffer))
		goto EXIT_ROUTINE;

	Section = (PIMAGE_SECTION_HEADER)(FileBuffer + Dos->e_lfanew + sizeof(IMAGE_NT_HEADERS));
	Offset = File->NumberOfSections;

	RtlZeroMemory(&Section[Offset], sizeof(IMAGE_SECTION_HEADER));
	RtlCopyMemory(&Section[Offset].Name, DisposeableObject, StringLengthA(DisposeableObject));

	Section[Offset].Misc.VirtualSize = AlignSection(SectionSizeInBytes, Optional->SectionAlignment, 0);
	Section[Offset].VirtualAddress = AlignSection(Section[Offset - 1].Misc.VirtualSize, Optional->SectionAlignment, Section[Offset - 1].VirtualAddress);
	Section[Offset].SizeOfRawData = AlignSection(SectionSizeInBytes, Optional->FileAlignment, 0);
	Section[Offset].PointerToRawData = AlignSection(Section[Offset - 1].SizeOfRawData, Optional->FileAlignment, Section[Offset - 1].PointerToRawData);

	SectionCharacteristics = IMAGE_SCN_MEM_WRITE |
		IMAGE_SCN_CNT_CODE |
		IMAGE_SCN_CNT_UNINITIALIZED_DATA |
		IMAGE_SCN_MEM_EXECUTE |
		IMAGE_SCN_CNT_INITIALIZED_DATA |
		IMAGE_SCN_MEM_READ;


	Section[Offset].Characteristics = SectionCharacteristics;

	if (SetFilePointer(hHandle, Section[Offset].PointerToRawData + Section[Offset].SizeOfRawData, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		goto EXIT_ROUTINE;

	if (!SetEndOfFile(hHandle))
		goto EXIT_ROUTINE;

	Optional->SizeOfImage = Section[Offset].VirtualAddress + Section[Offset].Misc.VirtualSize;
	File->NumberOfSections += 1;

	if (SetFilePointer(hHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		goto EXIT_ROUTINE;

	if (!WriteFile(hHandle, FileBuffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (FileBuffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, FileBuffer);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}

BOOL AddSectionToPeFileA(_In_ LPCSTR Path, _In_ LPCSTR SectionName, _In_ DWORD SectionSizeInBytes)
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
	WORD Offset = ERROR_SUCCESS;

	DWORD SectionCharacteristics = ERROR_SUCCESS;

	if (IsPeSectionA(Path, SectionName))
		return TRUE;

	SizeOfTargetBinary = GetFileSizeFromPathA((PCHAR)Path, FILE_ATTRIBUTE_NORMAL);
	if (SizeOfTargetBinary == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	hHandle = CreateFileA(Path, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	FileBuffer = (PBYTE)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, SizeOfTargetBinary);
	if (FileBuffer == NULL)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, FileBuffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	if (!RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &FileBuffer))
		goto EXIT_ROUTINE;

	Section = (PIMAGE_SECTION_HEADER)(FileBuffer + Dos->e_lfanew + sizeof(IMAGE_NT_HEADERS));
	Offset = File->NumberOfSections;

	RtlZeroMemory(&Section[Offset], sizeof(IMAGE_SECTION_HEADER));
	RtlCopyMemory(&Section[Offset].Name, SectionName, StringLengthA(SectionName));

	Section[Offset].Misc.VirtualSize = AlignSection(SectionSizeInBytes, Optional->SectionAlignment, 0);
	Section[Offset].VirtualAddress = AlignSection(Section[Offset - 1].Misc.VirtualSize, Optional->SectionAlignment, Section[Offset - 1].VirtualAddress);
	Section[Offset].SizeOfRawData = AlignSection(SectionSizeInBytes, Optional->FileAlignment, 0);
	Section[Offset].PointerToRawData = AlignSection(Section[Offset - 1].SizeOfRawData, Optional->FileAlignment, Section[Offset - 1].PointerToRawData);

	SectionCharacteristics = IMAGE_SCN_MEM_WRITE |
		IMAGE_SCN_CNT_CODE |
		IMAGE_SCN_CNT_UNINITIALIZED_DATA |
		IMAGE_SCN_MEM_EXECUTE |
		IMAGE_SCN_CNT_INITIALIZED_DATA |
		IMAGE_SCN_MEM_READ;


	Section[Offset].Characteristics = SectionCharacteristics;

	if (SetFilePointer(hHandle, Section[Offset].PointerToRawData + Section[Offset].SizeOfRawData, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		goto EXIT_ROUTINE;

	if (!SetEndOfFile(hHandle))
		goto EXIT_ROUTINE;

	Optional->SizeOfImage = Section[Offset].VirtualAddress + Section[Offset].Misc.VirtualSize;
	File->NumberOfSections += 1;

	if (SetFilePointer(hHandle, 0, NULL, FILE_BEGIN) == INVALID_SET_FILE_POINTER)
		goto EXIT_ROUTINE;

	if (!WriteFile(hHandle, FileBuffer, (DWORD)SizeOfTargetBinary, NULL, NULL))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (FileBuffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, FileBuffer);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}