#include "Win32Helper.h"

BOOL CreateProcessFromUrlOpenUrlW(LPCWSTR PathToUrlFile)
{
	typedef VOID(WINAPI* OPENURL)(HWND, HINSTANCE, LPCSTR);
	OPENURL OpenUrl = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	CHAR ccPathToUrlFile[MAX_PATH] = { 0 };

	if (WCharStringToCharString(ccPathToUrlFile, (PWCHAR)PathToUrlFile, StringLengthW(PathToUrlFile)) == 0)
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"url.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	OpenUrl = (OPENURL)GetProcAddressA((DWORD64)hMod, "OpenURL");
	if (!OpenUrl)
		goto EXIT_ROUTINE;

	OpenUrl(NULL, NULL, ccPathToUrlFile);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL CreateProcessFromUrlOpenUrlA(LPCSTR PathToUrlFile)
{
	typedef VOID(WINAPI* OPENURL)(HWND, HINSTANCE, LPCSTR);
	OPENURL OpenUrl = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"url.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	OpenUrl = (OPENURL)GetProcAddressA((DWORD64)hMod, "OpenUrl");
	if (!OpenUrl)
		goto EXIT_ROUTINE;

	OpenUrl(NULL, NULL, PathToUrlFile);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}