#include "Win32Helper.h"

HMODULE ProxyWorkItemLoadLibraryW(_In_ LPCWSTR lpModuleName)
{
	NTWAITFORSINGLEOBJECT NtWaitForSingleObject = NULL;
	RTLQUEUEWORKITEM RtlQueueWorkItem = NULL;
	NTSTATUS Status = STATUS_SUCCESS;
	LARGE_INTEGER Timeout = { 0 };

	NtWaitForSingleObject = (NTWAITFORSINGLEOBJECT)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "NtWaitForSingleObject");
	RtlQueueWorkItem = (RTLQUEUEWORKITEM)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "RtlQueueWorkItem");

	if (!NtWaitForSingleObject || !RtlQueueWorkItem)
		return NULL;

	if(RtlQueueWorkItem((PRTL_WORK_ITEM_ROUTINE)&LoadLibraryW, (PVOID)lpModuleName, WT_EXECUTEDEFAULT) != STATUS_SUCCESS)
		return NULL;

	Timeout.QuadPart = -500000;

	NtWaitForSingleObject(GetCurrentProcessNoForward(), FALSE, &Timeout);

	return GetModuleHandleEx2W(lpModuleName);
}

HMODULE ProxyWorkItemLoadLibraryA(_In_ LPCSTR lpModuleName)
{
	NTWAITFORSINGLEOBJECT NtWaitForSingleObject = NULL;
	RTLQUEUEWORKITEM RtlQueueWorkItem = NULL;
	NTSTATUS Status = STATUS_SUCCESS;
	LARGE_INTEGER Timeout = { 0 };

	NtWaitForSingleObject = (NTWAITFORSINGLEOBJECT)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "NtWaitForSingleObject");
	RtlQueueWorkItem = (RTLQUEUEWORKITEM)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "RtlQueueWorkItem");

	if (!NtWaitForSingleObject || !RtlQueueWorkItem)
		return NULL;

	if(RtlQueueWorkItem((PRTL_WORK_ITEM_ROUTINE)&LoadLibraryA, (PVOID)lpModuleName, WT_EXECUTEDEFAULT) != STATUS_SUCCESS)
		return NULL;

	Timeout.QuadPart = -500000;

	NtWaitForSingleObject(GetCurrentProcessNoForward(), FALSE, &Timeout);

	return GetModuleHandleEx2A(lpModuleName);
}