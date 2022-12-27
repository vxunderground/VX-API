#include "Win32Helper.h"

VOID InvokeCreateThreadpoolWaitCallbackRoutine(LPVOID lpParameter)
{
	/*
	
	HANDLE hEvent;
	PTP_WAIT Wait = NULL;

	hEvent = CreateEventW(NULL, FALSE, FALSE, NULL);
	if (hEvent == NULL)
		goto EXIT_ROUTINE;

	Wait = CreateThreadpoolWait((PTP_WAIT_CALLBACK)lpParameter, NULL, NULL);
	if(Wait == NULL)
		goto EXIT_ROUTINE;

	SetThreadpoolWait(Wait, hEvent, 0);

	SetEvent(hEvent);

	WaitForThreadpoolWaitCallbacks(Wait, FALSE);

	SetEvent(hEvent);

	Sleep(10000); //arbitrary sleep time...

EXIT_ROUTINE:

	if (hEvent)
		CloseHandle(hEvent);

	return;

	*/
}

BOOL MpfSceViaCreateThreadpoolWait(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	/*
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCreateThreadpoolWaitCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
	
	*/

	return FALSE;
}