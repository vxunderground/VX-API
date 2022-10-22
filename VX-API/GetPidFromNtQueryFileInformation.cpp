#include "Win32Helper.h"

DWORD GetPidFromNtQueryFileInformationW(_In_ PWCHAR FullBinaryPath)
{
	RTLDOSPATHNAMETONTPATHNAME_U RtlDosPathNameToNtPathName_U = NULL;
	NTOPENFILE NtOpenFile = NULL;
	NTCLOSE NtClose = NULL;
	NTQUERYINFORMATIONFILE NtQueryInformationFile = NULL;
	DWORD ProcessId = ERROR_SUCCESS, dwProcessInformationListArrayLength = 16384; //full size, unnecessary allocation amount
	HMODULE hModule = NULL;
	UNICODE_STRING NtBinaryPath = { 0 };
	OBJECT_ATTRIBUTES Attributes = { 0 };
	NTSTATUS Status = STATUS_SUCCESS;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	IO_STATUS_BLOCK IoBlock = { 0 };
	PFILE_PROCESS_IDS_USING_FILE_INFORMATION ProcessIdArray;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	if (!IsPathValidW(FullBinaryPath))
		return 0;

	RtlDosPathNameToNtPathName_U = (RTLDOSPATHNAMETONTPATHNAME_U)GetProcAddressA((DWORD64)hModule, "RtlDosPathNameToNtPathName_U");
	NtOpenFile = (NTOPENFILE)GetProcAddressA((DWORD64)hModule, "NtOpenFile");
	NtClose = (NTCLOSE)GetProcAddressA((DWORD64)hModule, "NtClose");
	NtQueryInformationFile = (NTQUERYINFORMATIONFILE)GetProcAddressA((DWORD64)hModule, "NtQueryInformationFile");

	if (!RtlDosPathNameToNtPathName_U || !NtOpenFile || !NtClose || !NtQueryInformationFile)
		return 0;

	if (!RtlDosPathNameToNtPathName_U(FullBinaryPath, &NtBinaryPath, NULL, NULL))
		return 0;

	InitializeObjectAttributes(&Attributes, &NtBinaryPath, OBJ_CASE_INSENSITIVE, 0, NULL);

	Status = NtOpenFile(&hHandle, FILE_READ_ATTRIBUTES, &Attributes, &IoBlock, FILE_SHARE_READ, NULL);
	if (!NT_SUCCESS(Status))
		return 0;

	ProcessIdArray = (PFILE_PROCESS_IDS_USING_FILE_INFORMATION)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwProcessInformationListArrayLength);
	if (ProcessIdArray == NULL)
		goto EXIT_ROUTINE;

	Status = NtQueryInformationFile(hHandle, &IoBlock, ProcessIdArray, dwProcessInformationListArrayLength, FileProcessIdsUsingFileInformation);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;

#pragma warning( push )
#pragma warning( disable : 4244)
	ProcessId = ProcessIdArray->ProcessIdList[0];
#pragma warning( pop ) 

EXIT_ROUTINE:

	if (hHandle)
		NtClose(hHandle);

	if (ProcessIdArray)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, ProcessIdArray);

	return ProcessId;
}

DWORD GetPidFromNtQueryFileInformationA(_In_ PCHAR FullBinaryPath)
{
	RTLDOSPATHNAMETONTPATHNAME_U RtlDosPathNameToNtPathName_U = NULL;
	NTOPENFILE NtOpenFile = NULL;
	NTCLOSE NtClose = NULL;
	NTQUERYINFORMATIONFILE NtQueryInformationFile = NULL;
	DWORD ProcessId = ERROR_SUCCESS, dwProcessInformationListArrayLength = 16384; //full size, unnecessary allocation amount
	HMODULE hModule = NULL;
	UNICODE_STRING NtBinaryPath = { 0 };
	OBJECT_ATTRIBUTES Attributes = { 0 };
	NTSTATUS Status = STATUS_SUCCESS;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	IO_STATUS_BLOCK IoBlock = { 0 };
	PFILE_PROCESS_IDS_USING_FILE_INFORMATION ProcessIdArray;
	WCHAR BinaryPathString[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(BinaryPathString, FullBinaryPath, StringLengthA(FullBinaryPath)) == 0)
		return 0;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	if (!IsPathValidW(BinaryPathString))
		return 0;

	RtlDosPathNameToNtPathName_U = (RTLDOSPATHNAMETONTPATHNAME_U)GetProcAddressA((DWORD64)hModule, "RtlDosPathNameToNtPathName_U");
	NtOpenFile = (NTOPENFILE)GetProcAddressA((DWORD64)hModule, "NtOpenFile");
	NtClose = (NTCLOSE)GetProcAddressA((DWORD64)hModule, "NtClose");
	NtQueryInformationFile = (NTQUERYINFORMATIONFILE)GetProcAddressA((DWORD64)hModule, "NtQueryInformationFile");

	if (!RtlDosPathNameToNtPathName_U || !NtOpenFile || !NtClose || !NtQueryInformationFile)
		return 0;

	if (!RtlDosPathNameToNtPathName_U(BinaryPathString, &NtBinaryPath, NULL, NULL))
		return 0;

	InitializeObjectAttributes(&Attributes, &NtBinaryPath, OBJ_CASE_INSENSITIVE, 0, NULL);

	Status = NtOpenFile(&hHandle, FILE_READ_ATTRIBUTES, &Attributes, &IoBlock, FILE_SHARE_READ, NULL);
	if (!NT_SUCCESS(Status))
		return 0;

	ProcessIdArray = (PFILE_PROCESS_IDS_USING_FILE_INFORMATION)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwProcessInformationListArrayLength);
	if (ProcessIdArray == NULL)
		goto EXIT_ROUTINE;

	Status = NtQueryInformationFile(hHandle, &IoBlock, ProcessIdArray, dwProcessInformationListArrayLength, FileProcessIdsUsingFileInformation);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;

#pragma warning( push )
#pragma warning( disable : 4244)
	ProcessId = ProcessIdArray->ProcessIdList[0];
#pragma warning( pop ) 

EXIT_ROUTINE:

	if (hHandle)
		NtClose(hHandle);

	if (ProcessIdArray)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, ProcessIdArray);

	return ProcessId;
}