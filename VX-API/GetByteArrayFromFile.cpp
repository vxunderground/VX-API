#include "Win32Helper.h"

BOOL GetByteArrayFromFileW(_Inout_ PBYTE Buffer, _In_ PWCHAR Path, _In_ ULONGLONG BytesToRead)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	BOOL bFlag = FALSE;

	hHandle = CreateFileW(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, Buffer, (DWORD)BytesToRead, NULL, NULL))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return TRUE;
}

BOOL GetByteArrayFromFileA(_Inout_ PBYTE Buffer, _In_ PCHAR Path, _In_ ULONGLONG BytesToRead)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	BOOL bFlag = FALSE;

	hHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	if (!ReadFile(hHandle, Buffer, (DWORD)BytesToRead, NULL, NULL))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return TRUE;
}