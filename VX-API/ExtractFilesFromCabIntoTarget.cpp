#include "Win32Helper.h"

BOOL ExtractFilesFromCabIntoTargetW(LPCWSTR CabFile, LPCWSTR OutputDirectory)
{
	EXTRACTFILESW ExtractFilesW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	ExtractFilesW = (EXTRACTFILESW)GetProcAddressA((DWORD64)hMod, "ExtractFilesW");
	if (!ExtractFilesW)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(ExtractFilesW(CabFile, OutputDirectory, 0, NULL, NULL, 0)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL ExtractFilesFromCabIntoTargetA(LPCSTR CabFile, LPCSTR OutputDirectory)
{
	EXTRACTFILESW ExtractFilesW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	WCHAR ccCab[MAX_PATH * sizeof(WCHAR)] = {0};
	WCHAR ccOut[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(ccCab, (PCHAR)CabFile, StringLengthA(CabFile)) == 0)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(ccOut, (PCHAR)OutputDirectory, StringLengthA(OutputDirectory)) == 0)
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	ExtractFilesW = (EXTRACTFILESW)GetProcAddressA((DWORD64)hMod, "ExtractFilesW");
	if (!ExtractFilesW)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(ExtractFilesW(ccCab, ccOut, 0, NULL, NULL, 0)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}