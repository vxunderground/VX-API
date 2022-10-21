#include "Win32Helper.h"

DWORD MpfGetLsaPidFromRegistry(VOID)
{
	NTOPENKEY NtOpenKey = NULL;
	NTQUERYVALUEKEY NtQueryValueKey = NULL;
	NTCLOSE NtClose = NULL;
	UNICODE_STRING LsaRegistryPath = { 0 };
	UNICODE_STRING LsaValue = { 0 };
	OBJECT_ATTRIBUTES Attributes = { 0 };
	HANDLE hKey = NULL;
	NTSTATUS Status = STATUS_SUCCESS;
	HMODULE hModule = NULL;
	DWORD LsassPid = ERROR_SUCCESS;
	UCHAR Buffer[sizeof(KEY_VALUE_INFORMATION_CLASS) * sizeof(DWORD)] = { 0 };
	PKEY_VALUE_PARTIAL_INFORMATION ValueObject = (PKEY_VALUE_PARTIAL_INFORMATION)Buffer;
	DWORD BufferLength = 0;
	PDWORD dwDispose = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		goto EXIT_ROUTINE;

	NtOpenKey = (NTOPENKEY)GetProcAddressA((DWORD64)hModule, "NtOpenKey");
	NtQueryValueKey = (NTQUERYVALUEKEY)GetProcAddressA((DWORD64)hModule, "NtQueryValueKey");
	NtClose = (NTCLOSE)GetProcAddressA((DWORD64)hModule, "NtClose");

	if (!NtOpenKey || !NtQueryValueKey || !NtClose)
		goto EXIT_ROUTINE;
	
	RtlInitUnicodeString(&LsaRegistryPath, L"\\Registry\\Machine\\SYSTEM\\CurrentControlSet\\Control\\Lsa");
	RtlInitUnicodeString(&LsaValue, L"LsaPid");
	InitializeObjectAttributes(&Attributes, &LsaRegistryPath, OBJ_CASE_INSENSITIVE, NULL, NULL);

	Status = NtOpenKey(&hKey, KEY_QUERY_VALUE, &Attributes);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;

#pragma warning( push )
#pragma warning( disable : 6260)
	Status = NtQueryValueKey(hKey, &LsaValue, KeyValuePartialInformation, Buffer, (sizeof(KEY_VALUE_INFORMATION_CLASS) * sizeof(DWORD)), &BufferLength);
	if (!NT_SUCCESS(Status))
		goto EXIT_ROUTINE;
#pragma warning( pop ) 

	LsassPid = *(PDWORD)&ValueObject->Data[0];
	// = *dwDispose;

EXIT_ROUTINE:

	if (hKey)
		NtClose(hKey);

	return LsassPid;
}