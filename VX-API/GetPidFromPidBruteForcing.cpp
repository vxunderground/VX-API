#include "Win32Helper.h"

DWORD GetPidFromPidBruteForcingW(_In_ PWCHAR ProcessNameWithExtension)
{
	DWORD ProcessId = ERROR_SUCCESS;
	SYSTEM_PROCESS_IMAGE_NAME_INFORMATION SystemProcessInformation = { 0 };
	NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = NULL;
	HMODULE hModule = NULL;
	BOOL bUnload = FALSE;

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"ntdll.dll");

	if (!hModule)
		goto EXIT_ROUTINE;

	NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddressA((DWORD64)hModule, "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		goto EXIT_ROUTINE;

	for (DWORD dwProcessIdAddress = 0x00000008; dwProcessIdAddress < 0xFFFFFFFC; dwProcessIdAddress += 0x00000004)
	{
		WCHAR ImageName[MAX_PATH * sizeof(WCHAR)] = { 0 };
		NTSTATUS Status = STATUS_SUCCESS;

		if (ProcessId != ERROR_SUCCESS)
			break;
		
		SystemProcessInformation.ProcessId = LongToHandle(dwProcessIdAddress);
		SystemProcessInformation.ImageName.Buffer = ImageName;
		SystemProcessInformation.ImageName.Length = 0;
		SystemProcessInformation.ImageName.MaximumLength = sizeof(ImageName);

		Status = NtQuerySystemInformation(SystemProcessIdInformation, &SystemProcessInformation, sizeof(SystemProcessInformation), NULL);
		if (!NT_SUCCESS(Status))
			continue;

		PathStripPathW(SystemProcessInformation.ImageName.Buffer);

		if (StringCompareW(ProcessNameWithExtension, SystemProcessInformation.ImageName.Buffer) == ERROR_SUCCESS)
			ProcessId = dwProcessIdAddress;
	}

EXIT_ROUTINE:

	return ProcessId;
}

DWORD GetPidFromPidBruteForcingA(_In_ PCHAR ProcessNameWithExtension)
{
	DWORD ProcessId = ERROR_SUCCESS;
	SYSTEM_PROCESS_IMAGE_NAME_INFORMATION SystemProcessInformation = { 0 };
	NTQUERYSYSTEMINFORMATION NtQuerySystemInformation = NULL;
	HMODULE hModule = NULL;
	BOOL bUnload = FALSE;
	WCHAR BinaryNameString[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(BinaryNameString, ProcessNameWithExtension, StringLengthA(ProcessNameWithExtension)) == 0)
		goto EXIT_ROUTINE;

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"ntdll.dll");

	if (!hModule)
		goto EXIT_ROUTINE;

	NtQuerySystemInformation = (NTQUERYSYSTEMINFORMATION)GetProcAddressA((DWORD64)hModule, "NtQuerySystemInformation");
	if (!NtQuerySystemInformation)
		goto EXIT_ROUTINE;

	for (DWORD dwProcessIdAddress = 0x00000008; dwProcessIdAddress < 0xFFFFFFFC; dwProcessIdAddress += 0x00000004)
	{
		WCHAR ImageName[MAX_PATH * sizeof(WCHAR)] = { 0 };
		NTSTATUS Status = STATUS_SUCCESS;

		if (ProcessId != ERROR_SUCCESS)
			break;

		SystemProcessInformation.ProcessId = LongToHandle(dwProcessIdAddress);
		SystemProcessInformation.ImageName.Buffer = ImageName;
		SystemProcessInformation.ImageName.Length = 0;
		SystemProcessInformation.ImageName.MaximumLength = sizeof(ImageName);

		Status = NtQuerySystemInformation(SystemProcessIdInformation, &SystemProcessInformation, sizeof(SystemProcessInformation), NULL);
		if (!NT_SUCCESS(Status))
			continue;

		PathStripPathW(SystemProcessInformation.ImageName.Buffer);

		if (StringCompareW(BinaryNameString, SystemProcessInformation.ImageName.Buffer) == ERROR_SUCCESS)
			ProcessId = dwProcessIdAddress;
	}

EXIT_ROUTINE:

	return ProcessId;
}