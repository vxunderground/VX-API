#include "Win32Helper.h"

#define WTS_CURRENT_SERVER_HANDLE ((HANDLE)NULL)

DWORD GetPidFromWindowsTerminalServiceW(_In_ PWCHAR BinaryNameWithFileExtension)
{
	PWTS_PROCESS_INFOW ProcessInformation = NULL;
	DWORD ProcessId = ERROR_SUCCESS, dwNumberOfProcesses = ERROR_SUCCESS;

	if (!WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &ProcessInformation, &dwNumberOfProcesses))
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

	if (ProcessInformation)
		WTSFreeMemory(ProcessInformation);

	return ProcessId;
}

DWORD GetPidFromWindowsTerminalServiceA(_In_ PCHAR BinaryNameWithFileExtension)
{
	PWTS_PROCESS_INFOW ProcessInformation = NULL;
	DWORD ProcessId = ERROR_SUCCESS, dwNumberOfProcesses = ERROR_SUCCESS;
	WCHAR Buffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(Buffer, BinaryNameWithFileExtension, StringLengthA(BinaryNameWithFileExtension)) == 0)
		goto EXIT_ROUTINE;

	if (!WTSEnumerateProcessesW(WTS_CURRENT_SERVER_HANDLE, NULL, 1, &ProcessInformation, &dwNumberOfProcesses))
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

	if (ProcessInformation)
		WTSFreeMemory(ProcessInformation);

	return ProcessId;
}