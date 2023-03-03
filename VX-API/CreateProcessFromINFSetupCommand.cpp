#include "Win32Helper.h"

#define RSC_FLAG_INF 1
#define RSC_FLAG_QUIET 4

BOOL CreateProcessFromINFSetupCommandW(LPCWSTR PathToInfFile, LPCWSTR NameOfSection)
{
	typedef HRESULT(WINAPI* RUNSETUPCOMMANDW)(HWND, LPCWSTR, LPCWSTR, LPCWSTR, LPCWSTR, PHANDLE, DWORD, LPVOID);
	RUNSETUPCOMMANDW RunSetupCommandW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"advpack.dll");

	RunSetupCommandW = (RUNSETUPCOMMANDW)GetProcAddressA((DWORD64)hMod, "RunSetupCommandW");
	if (!RunSetupCommandW)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(RunSetupCommandW(NULL, PathToInfFile, NameOfSection, L".", NULL, NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL CreateProcessFromINFSetupCommandA(LPCSTR PathToInfFile, LPCSTR NameOfSection)
{
	typedef HRESULT(WINAPI* RUNSETUPCOMMANDA)(HWND, LPCSTR, LPCSTR, LPCSTR, LPCSTR, PHANDLE, DWORD, LPVOID);
	RUNSETUPCOMMANDA RunSetupCommandA = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"advpack.dll");

	RunSetupCommandA = (RUNSETUPCOMMANDA)GetProcAddressA((DWORD64)hMod, "RunSetupCommandA");
	if (!RunSetupCommandA)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(RunSetupCommandA(NULL, PathToInfFile, NameOfSection, ".", NULL, NULL, RSC_FLAG_INF | RSC_FLAG_QUIET, NULL)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}