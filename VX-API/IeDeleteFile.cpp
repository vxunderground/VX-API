#include "Win32Helper.h"

BOOL IeDeleteFileW(_In_ LPCWSTR lpFileName)
{
	typedef BOOL(WINAPI* IEDELETEFILE)(LPCWSTR);
	IEDELETEFILE IeDeleteFile = NULL;

	IeDeleteFile = (IEDELETEFILE)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEDeleteFile");
	if (!IeDeleteFile)
		return FALSE;

	return IeDeleteFile(lpFileName);
}

BOOL IeDeleteFileA(_In_ LPCSTR lpFileName)
{
	typedef BOOL(WINAPI* IEDELETEFILE)(LPCWSTR);
	IEDELETEFILE IeDeleteFile = NULL;
	WCHAR ccBuffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

	IeDeleteFile = (IEDELETEFILE)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEDeleteFile");
	if (!IeDeleteFile)
		return FALSE;

	if (CharStringToWCharString(ccBuffer, (PCHAR)lpFileName, StringLengthA(lpFileName)) == 0)
		return FALSE;

	return IeDeleteFile(ccBuffer);
}