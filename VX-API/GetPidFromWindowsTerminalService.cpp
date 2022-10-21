#include "Win32Helper.h"

#define WTS_CURRENT_SERVER_HANDLE ((HANDLE)NULL)

DWORD GetPidFromWindowsTerminalServiceW(_In_ PWCHAR BinaryNameWithFileExtension)
{
	PWTS_PROCESS_INFOW ProcessInformation = NULL;
	WTSFREEMEMORY WtsFreeMemory = NULL;
	WTSENUMERATEPROCESSES WtsEnumerateProcessesW;
	DWORD ProcessId = ERROR_SUCCESS, dwNumberOfProcesses = ERROR_SUCCESS;
	HMODULE hModule = NULL;
	BOOL bUnload = FALSE;

	if (!IsDllLoadedW(L"Wtsapi32.dll"))
	{
		hModule = LoadLibraryW(L"Wtsapi32.dll");
		if (hModule == NULL)
			goto EXIT_ROUTINE;

		bUnload = TRUE;
	}
	else {
		hModule = GetModuleHandleEx2W(L"Wtsapi32.dll");
		if (hModule == NULL)
			goto EXIT_ROUTINE;
	}

	WtsEnumerateProcessesW = (WTSENUMERATEPROCESSES)GetProcAddressW((DWORD64)hModule, L"WTSEnumerateProcessesW");
	WtsFreeMemory = (WTSFREEMEMORY)GetProcAddressW((DWORD64)hModule, L"WTSFreeMemory");

	if (!WtsEnumerateProcessesW || !WtsFreeMemory)
		goto EXIT_ROUTINE;

	if (!WtsEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &ProcessInformation, &dwNumberOfProcesses))
		goto EXIT_ROUTINE;

	if (ProcessInformation == NULL)
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0; dwX < dwNumberOfProcesses; dwX++)
	{
		if (StringCompareW(BinaryNameWithFileExtension, ProcessInformation[dwX].pProcessName) == ERROR_SUCCESS)
		{
			ProcessId = ProcessInformation[dwX].ProcessId;
			break;
		}
	}

EXIT_ROUTINE:

	if (bUnload)
		FreeLibrary(hModule);

	if (ProcessInformation)
		WtsFreeMemory(ProcessInformation);

	return ProcessId;
}

DWORD GetPidFromWindowsTerminalServiceA(_In_ PCHAR BinaryNameWithFileExtension)
{
	PWTS_PROCESS_INFOW ProcessInformation = NULL;
	WTSFREEMEMORY WtsFreeMemory = NULL;
	WTSENUMERATEPROCESSES WtsEnumerateProcessesW;
	DWORD ProcessId = ERROR_SUCCESS, dwNumberOfProcesses = ERROR_SUCCESS;
	HMODULE hModule = NULL;
	BOOL bUnload = FALSE;
	WCHAR Buffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(Buffer, BinaryNameWithFileExtension, StringLengthA(BinaryNameWithFileExtension)) == 0)
		goto EXIT_ROUTINE;

	if (!IsDllLoadedW(L"Wtsapi32.dll"))
	{
		hModule = LoadLibraryW(L"Wtsapi32.dll");
		if (hModule == NULL)
			goto EXIT_ROUTINE;

		bUnload = TRUE;
	}
	else {
		hModule = GetModuleHandleEx2W(L"Wtsapi32.dll");
		if (hModule == NULL)
			goto EXIT_ROUTINE;
	}

	WtsEnumerateProcessesW = (WTSENUMERATEPROCESSES)GetProcAddressW((DWORD64)hModule, L"WTSEnumerateProcessesW");
	WtsFreeMemory = (WTSFREEMEMORY)GetProcAddressW((DWORD64)hModule, L"WTSFreeMemory");

	if (!WtsEnumerateProcessesW || !WtsFreeMemory)
		goto EXIT_ROUTINE;

	if (!WtsEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &ProcessInformation, &dwNumberOfProcesses))
		goto EXIT_ROUTINE;

	if (ProcessInformation == NULL)
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0; dwX < dwNumberOfProcesses; dwX++)
	{
		if (StringCompareW(Buffer, ProcessInformation[dwX].pProcessName) == ERROR_SUCCESS)
		{
			ProcessId = ProcessInformation[dwX].ProcessId;
			break;
		}
	}

EXIT_ROUTINE:

	if (bUnload)
		FreeLibrary(hModule);

	if (ProcessInformation)
		WtsFreeMemory(ProcessInformation);

	return ProcessId;
}