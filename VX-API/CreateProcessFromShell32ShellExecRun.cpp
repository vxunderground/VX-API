#include "Win32Helper.h"

BOOL CreateProcessFromShell32ShellExecRunW(LPCWSTR PathToFile)
{
	typedef VOID(WINAPI* SHELLEXEC_RUNDLLW)(HWND, HINSTANCE, LPCWSTR, INT);
	SHELLEXEC_RUNDLLW ShellExec_RunDllW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = TryLoadDllMultiMethodW((PWCHAR)L"shell32.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	ShellExec_RunDllW = (SHELLEXEC_RUNDLLW)GetProcAddressA((DWORD64)hMod, "ShellExec_RunDLLW");
	if (!ShellExec_RunDllW)
		goto EXIT_ROUTINE;

	ShellExec_RunDllW(NULL, NULL, PathToFile, SW_SHOW);

	bFlag = TRUE;

EXIT_ROUTINE:


	return bFlag;
}

BOOL CreateProcessFromShell32ShellExecRunA(LPCSTR PathToFile)
{
	typedef VOID(WINAPI* SHELLEXEC_RUNDLLA)(HWND, HINSTANCE, LPCSTR, INT);
	SHELLEXEC_RUNDLLA ShellExec_RunDllA = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = TryLoadDllMultiMethodW((PWCHAR)L"shell32.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	ShellExec_RunDllA = (SHELLEXEC_RUNDLLA)GetProcAddressA((DWORD64)hMod, "ShellExec_RunDLLA");
	if (!ShellExec_RunDllA)
		goto EXIT_ROUTINE;

	ShellExec_RunDllA(NULL, NULL, PathToFile, SW_SHOW);

	bFlag = TRUE;

EXIT_ROUTINE:

	return bFlag;
}