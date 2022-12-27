#include "Win32Helper.h"

BOOL IsPathValidA(_In_ LPCSTR FilePath)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;

	hFile = CreateFileA(FilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	if (hFile)
		CloseHandle(hFile);

	return TRUE;
}

BOOL IsPathValidW(_In_ LPCWSTR FilePath)
{
	HANDLE hFile = INVALID_HANDLE_VALUE;

	hFile = CreateFileW(FilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
		return FALSE;

	if (hFile)
		CloseHandle(hFile);

	return TRUE;
}
