#include "Win32Helper.h"

DWORD UnusedSubroutineQueryBufferSize(NTQUERYSYSTEMINFORMATION NtQuerySystemInformation)
{
	DWORD dwSize = ERROR_SUCCESS;

	NtQuerySystemInformation(SystemProcessInformation, NULL, 0, &dwSize);

	return (dwSize + 0x1000);
}

DWORD GetPidFromNtQuerySystemInformationW(_In_ PWCHAR BinaryNameWithFileExtension)
{
	NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = NULL;
	DWORD ProcessId = 0, Length = 0, dwOffset = 0;
	PSYSTEM_PROCESS_INFORMATION ProcessInformationPointer = NULL;
	HMODULE hModule = NULL;
	NTSTATUS Status = STATUS_SUCCESS;

	PSYSTEM_PROCESS_INFORMATION Process = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		goto EXIT_ROUTINE;

	NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddressA((DWORD64)hModule, "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		goto EXIT_ROUTINE;

	Length = UnusedSubroutineQueryBufferSize(NtQuerySystemInformation);
	if (Length == 0)
		goto EXIT_ROUTINE;

	Process = (PSYSTEM_PROCESS_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Length);
	if (Process == NULL)
		goto EXIT_ROUTINE;

	Status = NtQuerySystemInformation(SystemProcessInformation, Process, Length, &Length);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;

	ProcessInformationPointer = Process;
	do
	{
		if (ProcessInformationPointer->ImageName.Buffer)
		{
			if (StringCompareW(BinaryNameWithFileExtension, ProcessInformationPointer->ImageName.Buffer) == ERROR_SUCCESS)
				ProcessId = HandleToLong(ProcessInformationPointer->UniqueProcessId);
		}

		if (ProcessId != 0)
			break;
	
		ProcessInformationPointer = (PSYSTEM_PROCESS_INFORMATION)(((PBYTE)ProcessInformationPointer) + ProcessInformationPointer->NextEntryOffset);

	} while (ProcessInformationPointer->NextEntryOffset);

EXIT_ROUTINE:

	if (Process)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, Process);

	return ProcessId;
}

DWORD GetPidFromNtQuerySystemInformationA(_In_ PCHAR BinaryNameWithFileExtension)
{
	NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = NULL;
	DWORD ProcessId = 0, Length = 0, dwOffset = 0;
	PSYSTEM_PROCESS_INFORMATION ProcessInformationPointer = NULL;
	HMODULE hModule = NULL;
	NTSTATUS Status = STATUS_SUCCESS;
	WCHAR BinaryName[MAX_PATH * sizeof(WCHAR)] = { 0 };

	PSYSTEM_PROCESS_INFORMATION Process = NULL;

	if (CharStringToWCharString(BinaryName, BinaryNameWithFileExtension, StringLengthA(BinaryNameWithFileExtension)) == 0)
		return 0;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		goto EXIT_ROUTINE;

	NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddressA((DWORD64)hModule, "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		goto EXIT_ROUTINE;

	Length = UnusedSubroutineQueryBufferSize(NtQuerySystemInformation);
	if (Length == 0)
		goto EXIT_ROUTINE;

	Process = (PSYSTEM_PROCESS_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, Length);
	if (Process == NULL)
		goto EXIT_ROUTINE;

	Status = NtQuerySystemInformation(SystemProcessInformation, Process, Length, &Length);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;

	ProcessInformationPointer = Process;
	do
	{
		if (ProcessInformationPointer->ImageName.Buffer)
		{
			if (StringCompareW(BinaryName, ProcessInformationPointer->ImageName.Buffer) == ERROR_SUCCESS)
				ProcessId = HandleToLong(ProcessInformationPointer->UniqueProcessId);
		}

		if (ProcessId != 0)
			break;

		ProcessInformationPointer = (PSYSTEM_PROCESS_INFORMATION)(((PBYTE)ProcessInformationPointer) + ProcessInformationPointer->NextEntryOffset);

	} while (ProcessInformationPointer->NextEntryOffset);

EXIT_ROUTINE:

	if (Process)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, Process);

	return ProcessId;
}