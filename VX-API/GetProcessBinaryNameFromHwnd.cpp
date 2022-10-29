#include "Win32Helper.h"

BOOL GetProcessBinaryNameFromHwndW(_In_ HWND ProcessHwnd, _Inout_ PWCHAR BinaryName, _In_ DWORD BufferSize)
{
	WCHAR Buffer[MAX_PATH * sizeof(WCHAR)] = { 0 };
	DWORD ProcessId = ERROR_SUCCESS;
	HANDLE hHandle = NULL;
	BOOL bFlag = FALSE;
	DWORD dwError = 0;
	DWORD dwLength = MAX_PATH * sizeof(WCHAR);

	GetWindowThreadProcessId(ProcessHwnd, &ProcessId);

	hHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId);
	if (hHandle == NULL)
		return FALSE;

	if (!QueryFullProcessImageNameW(hHandle, 0, Buffer, &dwLength))
		goto EXIT_ROUTINE;

	if (MAX_PATH * sizeof(WCHAR) > BufferSize)
		goto EXIT_ROUTINE;

	if (StringCopyW(BinaryName, Buffer) == NULL)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}

BOOL GetProcessBinaryNameFromHwndA(_In_ HWND ProcessHwnd, _Inout_ PCHAR BinaryName, _In_ DWORD BufferSize)
{
	CHAR Buffer[MAX_PATH * sizeof(WCHAR)] = { 0 };
	DWORD ProcessId = ERROR_SUCCESS;
	HANDLE hHandle = NULL;
	BOOL bFlag = FALSE;
	DWORD dwError = 0;
	DWORD dwLength = MAX_PATH * sizeof(WCHAR);

	GetWindowThreadProcessId(ProcessHwnd, &ProcessId);

	hHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessId);
	if (hHandle == NULL)
		return FALSE;

	if (!QueryFullProcessImageNameA(hHandle, 0, Buffer, &dwLength))
		goto EXIT_ROUTINE;

	if (MAX_PATH * sizeof(WCHAR) > BufferSize)
		goto EXIT_ROUTINE;

	if (StringCopyA(BinaryName, Buffer) == NULL)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}