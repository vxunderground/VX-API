#include "Win32Helper.h"

BOOL CreateProcessFromUrlFileProtocolHandlerW(LPCWSTR PathToUrlFile)
{
	typedef HINSTANCE(WINAPI* FILEPROTOCOLHANDLERA)(HWND, HINSTANCE, LPCSTR, INT);
	FILEPROTOCOLHANDLERA FileProtocolHandlerA = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	CHAR ccPathToUrlFile[MAX_PATH] = { 0 };

	if (WCharStringToCharString(ccPathToUrlFile, (PWCHAR)PathToUrlFile, StringLengthW(PathToUrlFile)) == 0)
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"url.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	FileProtocolHandlerA = (FILEPROTOCOLHANDLERA)GetProcAddressA((DWORD64)hMod, "FileProtocolHandlerA");
	if (!FileProtocolHandlerA)
		goto EXIT_ROUTINE;

	FileProtocolHandlerA(NULL, NULL, ccPathToUrlFile, SW_SHOW);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL CreateProcessFromUrlFileProtocolHandlerA(LPCSTR PathToUrlFile)
{
	typedef HINSTANCE(WINAPI* FILEPROTOCOLHANDLERA)(HWND, HINSTANCE, LPCSTR, INT);
	FILEPROTOCOLHANDLERA FileProtocolHandlerA = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"url.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	FileProtocolHandlerA = (FILEPROTOCOLHANDLERA)GetProcAddressA((DWORD64)hMod, "FileProtocolHandlerA");
	if (!FileProtocolHandlerA)
		goto EXIT_ROUTINE;

	FileProtocolHandlerA(NULL, NULL, PathToUrlFile, SW_SHOW);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}