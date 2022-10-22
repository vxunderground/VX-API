#include "Win32Helper.h"

DWORD CreateThreadAndWaitForCompletion(_In_ LPTHREAD_START_ROUTINE StartAddress, _In_ LPVOID Parameters, _In_ DWORD dwMilliseconds)
{
	HANDLE hThread = NULL;
	DWORD ExitCode = ERROR_SUCCESS;

	hThread = CreateThread(NULL, 0, StartAddress, Parameters, 0, NULL);
	if (hThread == NULL)
		return FALSE;

	WaitForSingleObject(hThread, dwMilliseconds);

	if (!GetExitCodeThread(hThread, &ExitCode))
		return -1;

	return ExitCode;
}