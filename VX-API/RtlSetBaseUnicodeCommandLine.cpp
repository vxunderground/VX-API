#include "Win32Helper.h"

BOOL RtlSetBaseUnicodeCommandLine(_In_ PWCHAR CommandLinePayload)
{
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;
	HMODULE hKernelBase = NULL;
	PBYTE BaseAddress = NULL;
	BOOL bFlag = FALSE;
	PIMAGE_SECTION_HEADER SectionHeaderArray = NULL;
	PULONG_PTR DataSegment = ERROR_SUCCESS;
	DWORD NumberOfPointers = ERROR_SUCCESS;
	PWSTR CommandLineString = NULL;
	PSTR CommandLineStringA = NULL;
	PUNICODE_STRING CommandLineUnicodeString = NULL;
	PANSI_STRING CommandLineAnsiString = NULL;
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;

	hKernelBase = TryLoadDllMultiMethodW((PWCHAR)L"kernelbase.dll");
	if (!hKernelBase)
		goto EXIT_ROUTINE;

	BaseAddress = (PBYTE)hKernelBase;

	if (!RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &BaseAddress))
		goto EXIT_ROUTINE;

	SectionHeaderArray = (PIMAGE_SECTION_HEADER)(ULONGLONG(Nt) + sizeof(IMAGE_NT_HEADERS));
	for (DWORD dwX = 0; dwX < File->NumberOfSections; dwX++)
	{
		if (StringCompareA((PCHAR)SectionHeaderArray[dwX].Name, ".data") == ERROR_SUCCESS)
		{
			DataSegment = (PULONG_PTR)(BaseAddress + SectionHeaderArray[dwX].VirtualAddress);
			NumberOfPointers = SectionHeaderArray[dwX].Misc.VirtualSize / sizeof(ULONG_PTR);
			bFlag = TRUE;
			break;
		}
	}

	if (!bFlag)
		goto EXIT_ROUTINE;
	else
		bFlag = FALSE;

	CommandLineString = GetCommandLineW();
	if (CommandLineString == NULL)
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0; dwX < NumberOfPointers; dwX++)
	{
		CommandLineUnicodeString = (PUNICODE_STRING)&DataSegment[dwX];
		__try
		{
			if (StringCompareW(CommandLineUnicodeString->Buffer, CommandLineString) == 0)
			{
				RtlInitUnicodeString(CommandLineUnicodeString, CommandLinePayload);
				break;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { continue; }
	}

	CommandLineStringA = GetCommandLineA();
	if (CommandLineStringA == NULL)
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0; dwX < NumberOfPointers; dwX++)
	{
		CommandLineAnsiString = (PANSI_STRING)&DataSegment[dwX];
		__try
		{
			if (StringCompareA(CommandLineAnsiString->Buffer, CommandLineStringA) == 0)
			{
				CHAR ccBuffer[MAX_PATH] = { 0 };
				ANSI_STRING AnsiString = { 0 };

				if (WCharStringToCharString(ccBuffer, CommandLinePayload, StringLengthW(CommandLinePayload)) == 0)
					goto EXIT_ROUTINE;

				RtlInitAnsiString(&AnsiString, ccBuffer);

				if (CopyMemoryEx(&DataSegment[dwX], &AnsiString, sizeof(ANSI_STRING)) == NULL)
					goto EXIT_ROUTINE;

				break;
			}
		}
		__except (EXCEPTION_EXECUTE_HANDLER) { continue; }
	}

	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	for (DWORD dwX = 0; TRUE; dwX++)
	{
		Module = (PLDR_MODULE)((PBYTE)Module->InMemoryOrderModuleList.Flink - 16);
		if (Module->BaseDllName.Buffer == NULL)
			break;
	}

	bFlag = TRUE;

EXIT_ROUTINE:

	return bFlag;
}