#include "Win32Helper.h"

BOOL UnusedSubroutineRepair64bitImportAddressTable(PBYTE ExecutableMemoryBaseAddress)
{
	PIMAGE_DOS_HEADER DosHeader = NULL;
	PIMAGE_NT_HEADERS NtHeader = NULL;
	PIMAGE_FILE_HEADER FileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER OptionalHeader = NULL;
	PIMAGE_DATA_DIRECTORY ImportAddressTable = NULL;
	PIMAGE_IMPORT_DESCRIPTOR ImportDescriptor = NULL;

	if (!RtlLoadPeHeaders(&DosHeader, &NtHeader, &FileHeader, &OptionalHeader, &ExecutableMemoryBaseAddress))
		return FALSE;

	ImportAddressTable = &OptionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_IMPORT];
	if (ImportAddressTable == NULL)
		return FALSE;

	for (ULONGLONG Size = 0; Size < ImportAddressTable->Size; Size += sizeof(IMAGE_IMPORT_DESCRIPTOR)) 
	{
		LPSTR LibraryString = NULL;
		HMODULE hModule = NULL;
		ImportDescriptor = (PIMAGE_IMPORT_DESCRIPTOR)(ImportAddressTable->VirtualAddress + Size + (ULONG_PTR)ExecutableMemoryBaseAddress);

		if (ImportDescriptor->OriginalFirstThunk == NULL && ImportDescriptor->FirstThunk == NULL) 
			break;

		LibraryString = (LPSTR)((ULONGLONG)ExecutableMemoryBaseAddress + ImportDescriptor->Name);
		hModule = LoadLibraryA(LibraryString);

		for(ULONGLONG OffsetField = ERROR_SUCCESS, OffsetThunk = ERROR_SUCCESS;;)
		{
			PIMAGE_THUNK_DATA FieldThunk = (PIMAGE_THUNK_DATA)(ULONGLONG(ExecutableMemoryBaseAddress) + OffsetField + ImportDescriptor->FirstThunk);
			PIMAGE_THUNK_DATA OriginalThunk = (PIMAGE_THUNK_DATA)(ULONGLONG(ExecutableMemoryBaseAddress) + OffsetThunk + (ImportDescriptor->OriginalFirstThunk == NULL ? ImportDescriptor->FirstThunk : ImportDescriptor->OriginalFirstThunk));
		
			if (OriginalThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG32 || OriginalThunk->u1.Ordinal & IMAGE_ORDINAL_FLAG64)
			{
				if (hModule != NULL)
					FieldThunk->u1.Function = (ULONGLONG)GetProcAddressA((DWORD64)hModule, (PCHAR)(OriginalThunk->u1.Ordinal & 0xFFFF));
			}

			if (FieldThunk->u1.Function == NULL) 
			{
				if (hModule != NULL)
					FreeLibrary(hModule);

				break;
			}

			if (FieldThunk->u1.Function == OriginalThunk->u1.Function) 
			{
				PIMAGE_IMPORT_BY_NAME ImportNameString = (PIMAGE_IMPORT_BY_NAME)(ULONGLONG(ExecutableMemoryBaseAddress) + OriginalThunk->u1.AddressOfData);
				if (ImportNameString != NULL)
				{
					if(hModule != NULL)
						FieldThunk->u1.Function = (ULONGLONG)GetProcAddress(hModule, ImportNameString->Name); //GetProcAddressA has fatal error...
				}
			}
			OffsetField += sizeof(IMAGE_THUNK_DATA);
			OffsetThunk += sizeof(IMAGE_THUNK_DATA);
		}

		if (hModule != NULL)
			FreeLibrary(hModule);
	}

	return TRUE;
}

DWORD MpfExecute64bitPeBinaryInMemoryFromByteArrayNoReloc(_In_ PBYTE BinaryImage)
{
	PIMAGE_DOS_HEADER DosHeader = NULL;
	PIMAGE_NT_HEADERS NtHeader = NULL;
	PIMAGE_FILE_HEADER FileHeader = NULL;
	PIMAGE_OPTIONAL_HEADER OptionalHeader = NULL;
	PIMAGE_DATA_DIRECTORY RelocationDirectory = NULL;
	PIMAGE_SECTION_HEADER SectionHeaderArray = NULL;
	PBYTE ExecutableMemoryBaseAddress = NULL;
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	ULONGLONG ExecutionPointer = ERROR_SUCCESS;

	if (!RtlLoadPeHeaders(&DosHeader, &NtHeader, &FileHeader, &OptionalHeader, &BinaryImage))
		return -1;

	ExecutableMemoryBaseAddress = (PBYTE)VirtualAlloc((LPVOID)OptionalHeader->ImageBase, OptionalHeader->SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (!ExecutableMemoryBaseAddress)
	{
		ExecutableMemoryBaseAddress = (PBYTE)VirtualAlloc(NULL, OptionalHeader->SizeOfImage, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
		if (!ExecutableMemoryBaseAddress)
			return -1;
	}

	OptionalHeader->ImageBase = (ULONGLONG)ExecutableMemoryBaseAddress;
	CopyMemoryEx(ExecutableMemoryBaseAddress, BinaryImage, OptionalHeader->SizeOfHeaders);

	SectionHeaderArray = (PIMAGE_SECTION_HEADER)(ULONGLONG(NtHeader) + sizeof(IMAGE_NT_HEADERS));
	for (DWORD dwX = 0; dwX < FileHeader->NumberOfSections; dwX++)
	{
		CopyMemoryEx(LPVOID(ULONGLONG(ExecutableMemoryBaseAddress) + SectionHeaderArray[dwX].VirtualAddress), LPVOID(ULONGLONG(BinaryImage) + SectionHeaderArray[dwX].PointerToRawData), SectionHeaderArray[dwX].SizeOfRawData);
	}

	if (!UnusedSubroutineRepair64bitImportAddressTable(ExecutableMemoryBaseAddress))
		goto EXIT_ROUTINE;

	ExecutionPointer = (ULONGLONG)(ExecutableMemoryBaseAddress) + OptionalHeader->AddressOfEntryPoint;

	((VOID(*)())ExecutionPointer)();

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		VirtualFree(ExecutableMemoryBaseAddress, 0, MEM_RELEASE);

	return dwError;
}