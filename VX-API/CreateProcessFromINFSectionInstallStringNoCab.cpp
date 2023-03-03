#include "Win32Helper.h"

/*

Example .inf file
_______________
///////////////
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
[version]
signature = $Chicago$
AdvancedInf = 2.5

[DefaultInstall_SingleUser]
RunPostSetupCommands = Tag1

[Tag1]
C:\Windows\system32\calc.exe
_______________
///////////////
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
*/

BOOL CreateProcessFromINFSectionInstallStringNoCabW(LPCWSTR PathToInfFile, LPCWSTR NameOfSection)
{
	typedef HRESULT(WINAPI* LAUNCHINFSECTIONW)(HWND, HINSTANCE, PWSTR, INT);
	LAUNCHINFSECTIONW LaunchINFSectionW = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	WCHAR InfExecutionBuffer[MAX_PATH * 2] = { 0 };

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	LaunchINFSectionW = (LAUNCHINFSECTIONW)GetProcAddressA((DWORD64)hMod, "LaunchINFSectionW");
	if (!LaunchINFSectionW)
		goto EXIT_ROUTINE;

	if (StringCopyW(InfExecutionBuffer, PathToInfFile) == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatW(InfExecutionBuffer, L",") == NULL) 
		goto EXIT_ROUTINE;

	if (StringConcatW(InfExecutionBuffer, NameOfSection) == NULL) 
		goto EXIT_ROUTINE;

	if (StringConcatW(InfExecutionBuffer, L",") == NULL) 
		goto EXIT_ROUTINE;

	if (StringConcatW(InfExecutionBuffer, L"1") == NULL) 
		goto EXIT_ROUTINE;

	if (StringConcatW(InfExecutionBuffer, L",") == NULL) 
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(LaunchINFSectionW(NULL, NULL, InfExecutionBuffer, 0)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}

BOOL CreateProcessFromINFSectionInstallStringNoCabA(LPCSTR PathToInfFile, LPCSTR NameOfSection)
{
	typedef HRESULT(WINAPI* LAUNCHINFSECTION)(HWND, HINSTANCE, PSTR, INT);
	LAUNCHINFSECTION LaunchINFSection = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	CHAR InfExecutionBuffer[MAX_PATH * 2] = { 0 };

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	LaunchINFSection = (LAUNCHINFSECTION)GetProcAddressA((DWORD64)hMod, "LaunchINFSection");
	if (!LaunchINFSection)
		goto EXIT_ROUTINE;

	if (StringCopyA(InfExecutionBuffer, PathToInfFile) == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(InfExecutionBuffer, ",") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(InfExecutionBuffer, NameOfSection) == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(InfExecutionBuffer, ",") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(InfExecutionBuffer, "1") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(InfExecutionBuffer, ",") == NULL)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(LaunchINFSection(NULL, NULL, InfExecutionBuffer, 0)))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}