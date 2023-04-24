#include "Win32Helper.h"

BOOL IERemoveDirectoryW(_In_ LPCWSTR lpPathName)
{
	typedef BOOL(WINAPI* IEREMOVEDIRECTORY)(LPCWSTR);
	IEREMOVEDIRECTORY IeRemoveDirectory = NULL;

	IeRemoveDirectory = (IEREMOVEDIRECTORY)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IERemoveDirectory");
	if (!IeRemoveDirectory)
		return FALSE;

	return IeRemoveDirectory(lpPathName);
}

BOOL IERemoveDirectoryA(_In_ LPCSTR lpPathName)
{
	typedef BOOL(WINAPI* IEREMOVEDIRECTORY)(LPCWSTR);
	IEREMOVEDIRECTORY IeRemoveDirectory = NULL;
	WCHAR ccPathName[MAX_PATH * sizeof(WCHAR)] = { 0 };

	IeRemoveDirectory = (IEREMOVEDIRECTORY)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IERemoveDirectory");
	if (!IeRemoveDirectory)
		return FALSE;

	if (CharStringToWCharString(ccPathName, (PCHAR)lpPathName, StringLengthA(lpPathName)) == 0)
		return FALSE;

	return IeRemoveDirectory(ccPathName);
}