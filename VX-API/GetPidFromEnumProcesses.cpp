#include "Win32Helper.h"

#include <psapi.h>

DWORD GetPidFromEnumProcessesW(_In_ PWCHAR ProcessNameWithExtension)
{
	HANDLE hProcess = NULL;

	DWORD ProcessIdArray[1024] = { 0 };
	DWORD ProcessIdArraySize = 0;
	DWORD NumberOfBytesReturned = 0;

	if (!K32EnumProcesses(ProcessIdArray, sizeof(ProcessIdArray), &NumberOfBytesReturned))
		return FALSE;

	ProcessIdArraySize = NumberOfBytesReturned / sizeof(DWORD);

	for (DWORD dwIndex = 0; dwIndex < ProcessIdArraySize; dwIndex++)
	{
		HMODULE Module = NULL;
		DWORD dwProcessId = ERROR_SUCCESS;
		WCHAR ProcessStringName[MAX_PATH * sizeof(WCHAR)] = {0};

		if (ProcessIdArray[dwIndex] == 0)
			continue;

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessIdArray[dwIndex]);
		if (hProcess == NULL)
			continue;

		if (!K32EnumProcessModules(hProcess, &Module, sizeof(Module), &NumberOfBytesReturned))
			continue;

		if (K32GetModuleBaseNameW(hProcess, Module, ProcessStringName, sizeof(ProcessStringName) / sizeof(WCHAR)) == 0)
			continue;

		if (StringCompareW(ProcessNameWithExtension, ProcessStringName) == 0)
			dwProcessId = GetProcessId(hProcess);

		CloseHandle(hProcess);

		if (dwProcessId != 0)
			return dwProcessId;
	}

	return 0;
}

DWORD GetPidFromEnumProcessesA(_In_ PCHAR ProcessNameWithExtension)
{
	HANDLE hProcess = NULL;

	DWORD ProcessIdArray[1024] = { 0 };
	DWORD ProcessIdArraySize = 0;
	DWORD NumberOfBytesReturned = 0;

	if (!K32EnumProcesses(ProcessIdArray, sizeof(ProcessIdArray), &NumberOfBytesReturned))
		return FALSE;

	ProcessIdArraySize = NumberOfBytesReturned / sizeof(DWORD);

	for (DWORD dwIndex = 0; dwIndex < ProcessIdArraySize; dwIndex++)
	{
		HMODULE Module = NULL;
		DWORD dwProcessId = ERROR_SUCCESS;
		CHAR ProcessStringName[MAX_PATH] = { 0 };

		if (ProcessIdArray[dwIndex] == 0)
			continue;

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessIdArray[dwIndex]);
		if (hProcess == NULL)
			continue;

		if (!K32EnumProcessModules(hProcess, &Module, sizeof(Module), &NumberOfBytesReturned))
			continue;

		if (K32GetModuleBaseNameA(hProcess, Module, ProcessStringName, sizeof(ProcessStringName) / sizeof(CHAR)) == 0)
			continue;

		if (StringCompareA(ProcessNameWithExtension, ProcessStringName) == 0)
			dwProcessId = GetProcessId(hProcess);

		CloseHandle(hProcess);

		if (dwProcessId != 0)
			return dwProcessId;
	}

	return 0;
}