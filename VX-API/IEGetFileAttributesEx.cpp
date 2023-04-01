#include "Win32Helper.h"

#pragma warning( push )
#pragma warning( disable : 6101)
BOOL IEGetFileAttributesExW(_In_ LPCWSTR lpFileName, _In_ GET_FILEEX_INFO_LEVELS fInfoLevelId, _Out_ LPVOID lpFileInformation)
{
	typedef BOOL(WINAPI* IEGETFILEATTRIBUTESEX)(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
	IEGETFILEATTRIBUTESEX IeGetFileAttributesExW = NULL;

	IeGetFileAttributesExW = (IEGETFILEATTRIBUTESEX)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEGetFileAttributesEx");
	if (!IeGetFileAttributesExW)
		return FALSE;

	return IeGetFileAttributesExW(lpFileName, fInfoLevelId, lpFileInformation);
}

BOOL IEGetFileAttributesExA(_In_ LPCSTR lpFileName, _In_ GET_FILEEX_INFO_LEVELS fInfoLevelId, _Out_ LPVOID lpFileInformation)
{
	typedef BOOL(WINAPI* IEGETFILEATTRIBUTESEX)(LPCWSTR, GET_FILEEX_INFO_LEVELS, LPVOID);
	IEGETFILEATTRIBUTESEX IeGetFileAttributesExW = NULL;
	WCHAR ccBuffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

	IeGetFileAttributesExW = (IEGETFILEATTRIBUTESEX)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEGetFileAttributesEx");
	if (!IeGetFileAttributesExW)
		return FALSE;

	if (CharStringToWCharString(ccBuffer, (PCHAR)lpFileName, StringLengthA(lpFileName)) == 0)
		return FALSE;

	return IeGetFileAttributesExW(ccBuffer, fInfoLevelId, lpFileInformation);
}
#pragma warning( pop ) 