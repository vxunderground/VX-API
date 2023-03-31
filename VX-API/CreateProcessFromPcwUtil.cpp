#include "Win32Helper.h"

BOOL CreateProcessFromPcwUtilW(_In_ LPCWSTR PathToBinary)
{
	typedef VOID(WINAPI* LAUNCHAPPLICATIONW)(HWND, HINSTANCE, LPCWSTR);
	LAUNCHAPPLICATIONW LaunchApplicationW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"pcwutl.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	LaunchApplicationW = (LAUNCHAPPLICATIONW)GetProcAddressA((DWORD64)hMod, "LaunchApplicationW");
	if (!LaunchApplicationW)
		goto EXIT_ROUTINE;

	LaunchApplicationW(NULL, NULL, PathToBinary);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL CreateProcessFromPcwUtilA(_In_ LPCSTR PathToBinary)
{
	typedef VOID(WINAPI* LAUNCHAPPLICATIONW)(HWND, HINSTANCE, LPCWSTR);
	LAUNCHAPPLICATIONW LaunchApplicationW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	WCHAR wBinaryPath[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(wBinaryPath, (PCHAR)PathToBinary, StringLengthA(PathToBinary)) == NULL)
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"pcwutl.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	LaunchApplicationW = (LAUNCHAPPLICATIONW)GetProcAddressA((DWORD64)hMod, "LaunchApplicationW");
	if (!LaunchApplicationW)
		goto EXIT_ROUTINE;

	LaunchApplicationW(NULL, NULL, wBinaryPath);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}