#include "Win32Helper.h"

BOOL AdfIsCreateProcessDebugEventCodeSet(VOID)
{
	WCHAR FilePath[MAX_PATH * sizeof(WCHAR)] = { 0 };
	HANDLE hHandle = INVALID_HANDLE_VALUE;

	if (GetProcessPathFromUserProcessParametersW((MAX_PATH * sizeof(WCHAR)), FilePath) == 0)
		return FALSE;

	hHandle = CreateFileW(FilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hHandle == INVALID_HANDLE_VALUE)
		return TRUE;

	if (hHandle)
		CloseHandle(hHandle);

	return FALSE;
}