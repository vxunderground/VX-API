#include "Win32Helper.h"

BOOL CreateProcessFromZipfldrRouteCallW(LPCWSTR PathToFile)
{
	typedef VOID(WINAPI* ROUTETHECALL)(HWND, HINSTANCE, LPCSTR);
	ROUTETHECALL RouteTheCall = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	CHAR ccPath[MAX_PATH] = { 0 };

	hMod = LoadLibraryW(L"zipfldr.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	if (WCharStringToCharString(ccPath, (PWCHAR)PathToFile, StringLengthW(PathToFile)) == NULL)
		goto EXIT_ROUTINE;

	RouteTheCall = (ROUTETHECALL)GetProcAddressA((DWORD64)hMod, "RouteTheCall");
	if (!RouteTheCall)
		goto EXIT_ROUTINE;

	RouteTheCall(NULL, NULL, ccPath);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL CreateProcessFromZipfldrRouteCallA(LPCSTR PathToFile)
{
	typedef VOID(WINAPI* ROUTETHECALL)(HWND, HINSTANCE, LPCSTR);
	ROUTETHECALL RouteTheCall = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"zipfldr.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	RouteTheCall = (ROUTETHECALL)GetProcAddressA((DWORD64)hMod, "RouteTheCall");
	if (!RouteTheCall)
		goto EXIT_ROUTINE;

	RouteTheCall(NULL, NULL, PathToFile);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}