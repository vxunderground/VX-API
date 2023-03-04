#include "Win32Helper.h"


BOOL SleepObfuscationViaVirtualProtect(_In_ DWORD dwSleepTimeInMilliseconds, _In_ PUCHAR Key)
{
	BOOL bFlag = FALSE;
	NTCONTINUE NtContinue = NULL;
	SYSTEMFUNCTION032 SystemFunction032 = NULL;
	HMODULE hNtdll = NULL, hAdvapi32 = NULL;

	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;

	HMODULE ImageBaseAddress = NULL;

	CONTEXT ContextThread = { 0 }, RopVirtualProtectReadWrite = { 0 }, RopSystemFunction032Encryption = { 0 }, RopWaitForSingleObject = { 0 };
	CONTEXT RopSystemFunction032Decryption = { 0 }, RopVirtualProtectExecute = { 0 }, RopSetEvent = { 0 };
	AB_STRING BinaryKey = { 0 }, ImageBuffer = { 0 };

	HANDLE hTimer = NULL, hTimerQueue = NULL, hEvent = NULL;

	DWORD PreviousProtectionAttribute = ERROR_SUCCESS;

	hNtdll = GetModuleHandleEx2W(L"ntdll.dll");
	if (hNtdll == NULL)
		goto EXIT_ROUTINE;

	hAdvapi32 = TryLoadDllMultiMethodW((PWCHAR)L"advapi32.dll");
	if (hAdvapi32 == NULL)
		goto EXIT_ROUTINE;

	NtContinue = (NTCONTINUE)GetProcAddressA((DWORD64)hNtdll, "NtContinue");
	SystemFunction032 = (SYSTEMFUNCTION032)GetProcAddressW((DWORD64)hAdvapi32, L"SystemFunction032");

	if (!NtContinue || !SystemFunction032)
		goto EXIT_ROUTINE;

	ImageBaseAddress = GetPeFileBaseAddress();
	if (ImageBaseAddress == NULL)
		goto EXIT_ROUTINE;

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, (PBYTE*)&ImageBaseAddress);

	hEvent = CreateEventW(0, 0, 0, 0);
	if (hEvent == NULL)
		goto EXIT_ROUTINE;

	hTimerQueue = CreateTimerQueue();
	if (hTimerQueue == NULL)
		goto EXIT_ROUTINE;

	BinaryKey.Buffer = Key;
	BinaryKey.Length = BinaryKey.MaximumLength = 17;

	ImageBuffer.Buffer = (PUCHAR)ImageBaseAddress;
	ImageBuffer.Length = ImageBuffer.MaximumLength = Optional->SizeOfImage;

	if (!CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)RtlCaptureContext, &ContextThread, 0, 0, WT_EXECUTEINTIMERTHREAD))
		goto EXIT_ROUTINE;

	WaitForSingleObject(hEvent, 0x32);

	if (CopyMemoryEx(&RopVirtualProtectReadWrite, &ContextThread, sizeof(CONTEXT)) == NULL)
		goto EXIT_ROUTINE;

	if (CopyMemoryEx(&RopSystemFunction032Encryption, &ContextThread, sizeof(CONTEXT)) == NULL)
		goto EXIT_ROUTINE;

	if (CopyMemoryEx(&RopWaitForSingleObject, &ContextThread, sizeof(CONTEXT)) == NULL)
		goto EXIT_ROUTINE;

	if (CopyMemoryEx(&RopSystemFunction032Decryption, &ContextThread, sizeof(CONTEXT)) == NULL)
		goto EXIT_ROUTINE;

	if (CopyMemoryEx(&RopVirtualProtectExecute, &ContextThread, sizeof(CONTEXT)) == NULL)
		goto EXIT_ROUTINE;
	
	if (CopyMemoryEx(&RopSetEvent, &ContextThread, sizeof(CONTEXT)) == NULL)
		goto EXIT_ROUTINE;

	// VirtualProtect
	RopVirtualProtectReadWrite.Rsp -= 8;
	RopVirtualProtectReadWrite.Rip = (DWORD64)VirtualProtect;
	RopVirtualProtectReadWrite.Rcx = (DWORD64)ImageBaseAddress;
	RopVirtualProtectReadWrite.Rdx = Optional->SizeOfImage;
	RopVirtualProtectReadWrite.R8 = PAGE_READWRITE;
	RopVirtualProtectReadWrite.R9 = (DWORD64)&PreviousProtectionAttribute;

	// SystemFunction032
	RopSystemFunction032Encryption.Rsp -= 8;
	RopSystemFunction032Encryption.Rip = (DWORD64)SystemFunction032;
	RopSystemFunction032Encryption.Rcx = (DWORD64)&ImageBuffer;
	RopSystemFunction032Encryption.Rdx = (DWORD64)&BinaryKey;

	// WaitForSingleObject
	RopWaitForSingleObject.Rsp -= 8;
	RopWaitForSingleObject.Rip = (DWORD64)WaitForSingleObject;
	RopWaitForSingleObject.Rcx = (DWORD64)GetCurrentProcessNoForward();
	RopWaitForSingleObject.Rdx = dwSleepTimeInMilliseconds;

	// SystemFunction032
	RopSystemFunction032Decryption.Rsp -= 8;
	RopSystemFunction032Decryption.Rip = (DWORD64)SystemFunction032;
	RopSystemFunction032Decryption.Rcx = (DWORD64)&ImageBuffer;
	RopSystemFunction032Decryption.Rdx = (DWORD64)&BinaryKey;

	// VirtualProtect
	RopVirtualProtectExecute.Rsp -= 8;
	RopVirtualProtectExecute.Rip = (DWORD64)VirtualProtect;
	RopVirtualProtectExecute.Rcx = (DWORD64)ImageBaseAddress;
	RopVirtualProtectExecute.Rdx = Optional->SizeOfImage;
	RopVirtualProtectExecute.R8 = PAGE_EXECUTE_READWRITE;
	RopVirtualProtectExecute.R9 = (DWORD64)&PreviousProtectionAttribute;

	// SetEvent
	RopSetEvent.Rsp -= 8;
	RopSetEvent.Rip = (DWORD64)SetEvent;
	RopSetEvent.Rcx = (DWORD64)hEvent;

	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)NtContinue, &RopVirtualProtectReadWrite, 100, 0, WT_EXECUTEINTIMERTHREAD);
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)NtContinue, &RopSystemFunction032Encryption, 200, 0, WT_EXECUTEINTIMERTHREAD);
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)NtContinue, &RopWaitForSingleObject, 300, 0, WT_EXECUTEINTIMERTHREAD);
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)NtContinue, &RopSystemFunction032Decryption, 400, 0, WT_EXECUTEINTIMERTHREAD);
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)NtContinue, &RopVirtualProtectExecute, 500, 0, WT_EXECUTEINTIMERTHREAD);
	CreateTimerQueueTimer(&hTimer, hTimerQueue, (WAITORTIMERCALLBACK)NtContinue, &RopSetEvent, 600, 0, WT_EXECUTEINTIMERTHREAD);

	WaitForSingleObject(hEvent, INFINITE);

	bFlag = TRUE;

EXIT_ROUTINE:

#pragma warning( push )
#pragma warning( disable : 6031)
	if(hTimerQueue)
		DeleteTimerQueue(hTimerQueue);
#pragma warning( pop ) 

	return bFlag;
}