#include "Win32Helper.h"

#pragma warning( push )
#pragma warning( disable : 6101)
HANDLE IeFindFirstFileW(_In_ LPCWSTR lpFileName, _Out_ LPWIN32_FIND_DATAW lpFindFileData)
{
	typedef HANDLE(WINAPI* IEFINDFIRSTFILE)(LPCWSTR, LPWIN32_FIND_DATAW);
	IEFINDFIRSTFILE IEFindFirstFile = NULL;

	IEFindFirstFile = (IEFINDFIRSTFILE)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEFindFirstFile");
	if (!IEFindFirstFile)
		return FALSE;

	return IEFindFirstFile(lpFileName, lpFindFileData);
}

HANDLE IeFindFirstFileA(_In_ LPCSTR lpFileName, _Out_ LPWIN32_FIND_DATAA lpFindFileData)
{
	typedef HANDLE(WINAPI* IEFINDFIRSTFILE)(LPCWSTR, LPWIN32_FIND_DATAW);
	IEFINDFIRSTFILE IEFindFirstFile = NULL;
	WCHAR ccBuffer[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WIN32_FIND_DATAW FindData = { 0 };
	HANDLE hHandle = NULL;
	BOOL bFlag = FALSE;

	IEFindFirstFile = (IEFINDFIRSTFILE)GetProcAddressA((DWORD64)TryLoadDllMultiMethodW((PWCHAR)L"ieframe.dll"), "IEFindFirstFile");
	if (!IEFindFirstFile)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(ccBuffer, (PCHAR)lpFileName, StringLengthA(lpFileName)) == 0)
		goto EXIT_ROUTINE;

	hHandle = IEFindFirstFile(ccBuffer, &FindData);
	if (hHandle == NULL)
		goto EXIT_ROUTINE;

	lpFindFileData->dwFileAttributes = FindData.dwFileAttributes;
	lpFindFileData->nFileSizeHigh = FindData.nFileSizeHigh;
	lpFindFileData->nFileSizeLow = FindData.nFileSizeLow;
	lpFindFileData->dwReserved0 = FindData.dwReserved0;
	lpFindFileData->dwReserved1 = FindData.dwReserved1;
	lpFindFileData->ftCreationTime.dwLowDateTime = FindData.ftCreationTime.dwLowDateTime;
	lpFindFileData->ftCreationTime.dwHighDateTime = FindData.ftCreationTime.dwHighDateTime;
	lpFindFileData->ftLastWriteTime.dwLowDateTime = FindData.ftLastWriteTime.dwLowDateTime;
	lpFindFileData->ftLastWriteTime.dwHighDateTime = FindData.ftLastWriteTime.dwHighDateTime;
	lpFindFileData->ftLastAccessTime.dwLowDateTime = FindData.ftLastAccessTime.dwLowDateTime;
	lpFindFileData->ftLastAccessTime.dwHighDateTime = FindData.ftLastAccessTime.dwHighDateTime;

	if (WCharStringToCharString(lpFindFileData->cFileName, FindData.cFileName, StringLengthW(FindData.cFileName)) == 0)
		goto EXIT_ROUTINE;

	if (WCharStringToCharString(lpFindFileData->cAlternateFileName, FindData.cAlternateFileName, StringLengthW(FindData.cAlternateFileName)) == 0)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
	{
		if (hHandle)
			CloseHandle(hHandle);
	}

	return (bFlag ? hHandle : NULL);
}
#pragma warning( pop ) 