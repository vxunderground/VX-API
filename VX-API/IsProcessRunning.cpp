#include "Win32Helper.h"

#include <psapi.h>

BOOL IsProcessRunningA(_In_ LPCSTR ProcessNameWithExtension)
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
		CHAR ProcessStringName[MAX_PATH] = { 0 };

		if (ProcessIdArray[dwIndex] == 0)
			continue;

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessIdArray[dwIndex]);
		if (hProcess == NULL)
			continue;

		if (!K32EnumProcessModules(hProcess, &Module, sizeof(Module), &NumberOfBytesReturned))
			continue;

		if (K32GetModuleBaseNameA(hProcess, Module, ProcessStringName, sizeof(ProcessStringName) / sizeof(WCHAR)) == 0)
			continue;

		if (hProcess)
			CloseHandle(hProcess);
		
		if (StringCompareA(ProcessNameWithExtension, ProcessStringName) == 0)
				return TRUE;
	}

	return FALSE;
}

BOOL IsProcessRunningW(_In_ LPCWSTR ProcessNameWithExtension)
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
		WCHAR ProcessStringName[MAX_PATH] = { 0 };

		if (ProcessIdArray[dwIndex] == 0)
			continue;

		hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, ProcessIdArray[dwIndex]);
		if (hProcess == NULL)
			continue;

		if (!K32EnumProcessModules(hProcess, &Module, sizeof(Module), &NumberOfBytesReturned))
			continue;

		if (K32GetModuleBaseNameW(hProcess, Module, ProcessStringName, sizeof(ProcessStringName) / sizeof(WCHAR)) == 0)
			continue;

		if (hProcess)
			CloseHandle(hProcess);

		if (StringCompareW(ProcessStringName, ProcessNameWithExtension) == 0)
			return TRUE;
	}

	return FALSE;
}