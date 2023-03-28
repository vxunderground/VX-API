#include "Win32Helper.h"

BOOL DeleteDirectoryAndSubDataViaDelNodeW(LPCWSTR FullPathToDirectory)
{
	DELNODEW DelNodeW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	DelNodeW = (DELNODEW)GetProcAddressA((DWORD64)hMod, "DelNodeW");
	if (!DelNodeW)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(DelNodeW(FullPathToDirectory, 0)))
		goto EXIT_ROUTINE;


	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL DeleteDirectoryAndSubDataViaDelNodeA(LPCSTR FullPathToDirectory)
{
	DELNODEW DelNodeW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	WCHAR ccBuffer[MAX_PATH * sizeof(WCHAR)] = {0};

	if(CharStringToWCharString(ccBuffer, (PCHAR)FullPathToDirectory, StringLengthA(FullPathToDirectory)) == 0)
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	DelNodeW = (DELNODEW)GetProcAddressA((DWORD64)hMod, "DelNodeW");
	if (!DelNodeW)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(DelNodeW(ccBuffer, 0)))
		goto EXIT_ROUTINE;


	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}