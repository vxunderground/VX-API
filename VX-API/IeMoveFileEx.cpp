#include "Win32Helper.h"

BOOL IEMoveFileExW(_In_ LPCWSTR lpExistingFileName, _In_ LPCWSTR lpNewFileName, _In_ DWORD dwFlags)
{
	typedef BOOL(WINAPI* IEMOVEFILEEX)(LPCWSTR, LPCWSTR, DWORD);
	IEMOVEFILEEX IeMoveFileEx = NULL;
	
	IeMoveFileEx = (IEMOVEFILEEX)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEMoveFileEx");
	if (!IeMoveFileEx)
		return FALSE;

	return IeMoveFileEx(lpExistingFileName, lpNewFileName, dwFlags);
}

BOOL IEMoveFileExA(_In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName, _In_ DWORD dwFlags)
{
	typedef BOOL(WINAPI* IEMOVEFILEEX)(LPCWSTR, LPCWSTR, DWORD);
	IEMOVEFILEEX IeMoveFileEx = NULL;
	WCHAR ccExisting[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR ccNew[MAX_PATH * sizeof(WCHAR)] = { 0 };

	IeMoveFileEx = (IEMOVEFILEEX)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEMoveFileEx");
	if (!IeMoveFileEx)
		return FALSE;

	if (CharStringToWCharString(ccExisting, (PCHAR)lpExistingFileName, StringLengthA(lpExistingFileName)) == 0)
		return FALSE;

	if (CharStringToWCharString(ccNew, (PCHAR)lpNewFileName, StringLengthA(lpNewFileName)) == 0)
		return FALSE;

	return IeMoveFileEx(ccExisting, ccNew, dwFlags);
}