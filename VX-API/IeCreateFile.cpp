#include "Win32Helper.h"

HANDLE IeCreateFileW(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile)
{
	typedef HANDLE(WINAPI* IECREATEFILE)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
	IECREATEFILE IeCreateFile = NULL;

	IeCreateFile = (IECREATEFILE)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IECreateFile");
	if (!IeCreateFile)
		return NULL;

	return IeCreateFile(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}

HANDLE IeCreateFileA(_In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile)
{
	typedef HANDLE(WINAPI* IECREATEFILE)(LPCWSTR, DWORD, DWORD, LPSECURITY_ATTRIBUTES, DWORD, DWORD, HANDLE);
	IECREATEFILE IeCreateFile = NULL;
	WCHAR ccBuffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

	IeCreateFile = (IECREATEFILE)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IECreateFile");
	if (!IeCreateFile)
		return NULL;

	if (CharStringToWCharString(ccBuffer, (PCHAR)lpFileName, StringLengthA(lpFileName)) == 0)
		return NULL;

	return IeCreateFile(ccBuffer, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
}