#include "Win32Helper.h"

BOOL IeCreateDirectoryW(_In_ LPCWSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	typedef BOOL(WINAPI* IECREATEDIRECTORY)(LPCWSTR, LPSECURITY_ATTRIBUTES);
	IECREATEDIRECTORY IECreateDirectory = NULL;

	IECreateDirectory = (IECREATEDIRECTORY)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IECreateDirectory");
	if (!IECreateDirectory)
		return FALSE;

	return IECreateDirectory(lpPathName, lpSecurityAttributes);
}

BOOL IeCreateDirectoryA(_In_ LPCSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes)
{
	typedef BOOL(WINAPI* IECREATEDIRECTORY)(LPCWSTR, LPSECURITY_ATTRIBUTES);
	IECREATEDIRECTORY IECreateDirectory = NULL;
	WCHAR ccBuffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

	IECreateDirectory = (IECREATEDIRECTORY)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IECreateDirectory");
	if (!IECreateDirectory)
		return FALSE;

	if (CharStringToWCharString(ccBuffer, (PCHAR)lpPathName, StringLengthA(lpPathName)) == 0)
		return FALSE;

	return IECreateDirectory(ccBuffer, lpSecurityAttributes);
}