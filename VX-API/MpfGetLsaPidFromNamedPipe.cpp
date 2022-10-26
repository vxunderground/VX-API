#include "Win32Helper.h"

DWORD MpfGetLsaPidFromNamedPipe(VOID)
{
	UNICODE_STRING Pipe = { 0 };
	NTOPENFILE NtOpenFile = NULL;
	NTFSCONTROLFILE NtfsControlFile = NULL;
	NTCLOSE NtClose = NULL;
	HMODULE hModule = NULL;
	IO_STATUS_BLOCK IoBlock = { 0 };
	OBJECT_ATTRIBUTES Attributes = { 0 };
	DWORD ProcessId = ERROR_SUCCESS;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	NTSTATUS Status = STATUS_SUCCESS;
	LPSTR InputBuffer = (LPSTR)"ServerProcessId";

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"ntdll.dll");
	if (hModule == NULL)
		return -1;

	NtOpenFile = (NTOPENFILE)GetProcAddressA((DWORD64)hModule, "NtOpenFile");
	NtfsControlFile = (NTFSCONTROLFILE)GetProcAddressA((DWORD64)hModule, "NtFsControlFile");
	NtClose = (NTCLOSE)GetProcAddressA((DWORD64)hModule, "NtClose");

	if (!NtOpenFile || !NtfsControlFile || !NtClose)
		return -1;

	RtlInitUnicodeString(&Pipe, L"\\Device\\NamedPipe\\lsass");

	InitializeObjectAttributes(&Attributes, &Pipe, OBJ_CASE_INSENSITIVE, 0, NULL);

	Status = NtOpenFile(&hHandle, FILE_READ_ATTRIBUTES, &Attributes, &IoBlock, FILE_SHARE_READ, NULL);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;

	Status = NtfsControlFile(hHandle, NULL, NULL, NULL, &IoBlock, FSCTL_PIPE_GET_PIPE_ATTRIBUTE, InputBuffer, (ULONG)StringLengthA(InputBuffer) + 1, &ProcessId, sizeof(DWORD));
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;


EXIT_ROUTINE:

	if (hHandle)
		NtClose(hHandle);

	return ProcessId;
}