#include "Win32Helper.h"

VOID InvokeCertFindChainInStoreCallbackRoutine(LPVOID lpParameter)
{
	/*
	
	HCERTSTORE hCertStore = NULL;
	CERT_CHAIN_FIND_ISSUER_PARA Issuer = { 0 };

	hCertStore = CertOpenStore(CERT_STORE_PROV_SYSTEM, 0, NULL, CERT_SYSTEM_STORE_CURRENT_USER, L"My");
	if (hCertStore == NULL)
		return;

	Issuer.cbSize = sizeof(CERT_CHAIN_FIND_ISSUER_PARA);
	Issuer.pfnFindCallback = (PFN_CERT_CHAIN_FIND_BY_ISSUER_CALLBACK)lpParameter;

	CertFindChainInStore(hCertStore, X509_ASN_ENCODING, 0, CERT_CHAIN_FIND_BY_ISSUER, &Issuer, NULL);

	if(hCertStore)
		CertCloseStore(hCertStore, 0);
		
	*/
}

BOOL MpfSceViaCertFindChainInStore(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	/*
	
	
	!!! UNIMPLEMENTED - UNABLE TO GET SHELLCODE EXECUTION WORKING!!!


	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeCertFindChainInStoreCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
	
	*/

	return FALSE;
}