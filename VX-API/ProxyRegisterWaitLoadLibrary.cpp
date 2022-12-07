#include "Win32Helper.h"

HMODULE ProxyRegisterWaitLoadLibraryW(_In_ LPCWSTR lpModuleName)
{
	RTLREGISTERWAIT RtlRegisterWait = NULL;
	RTLDEREGISTERWAITEX RtlDeregisterWaitEx = NULL;
	NTWAITFORSINGLEOBJECT NtWaitForSingleObject = NULL;
	HANDLE WaitObject = NULL, EventObject = NULL;
	HMODULE hReturn = NULL;
	LARGE_INTEGER Timeout = { 0 };
	Timeout.QuadPart = 500;

	NtWaitForSingleObject = (NTWAITFORSINGLEOBJECT)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "NtWaitForSingleObject");
	RtlRegisterWait = (RTLREGISTERWAIT)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "RtlRegisterWait");
	RtlDeregisterWaitEx = (RTLDEREGISTERWAITEX)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "RtlDeregisterWaitEx");

	if (!RtlRegisterWait || !NtWaitForSingleObject || !RtlDeregisterWaitEx)
		goto EXIT_ROUTINE;

	EventObject = CreateEventW(NULL, FALSE, FALSE, NULL);
	if (EventObject == NULL)
		goto EXIT_ROUTINE;

	if (RtlRegisterWait(&WaitObject, EventObject, (WORKERCALLBACKFUNC)LoadLibraryW, (PVOID)lpModuleName, 0, WT_EXECUTEDEFAULT) != STATUS_SUCCESS)
		goto EXIT_ROUTINE;
	else
		NtWaitForSingleObject(EventObject, FALSE, &Timeout);

	hReturn = GetModuleHandleEx2W(lpModuleName);

EXIT_ROUTINE:

	if (EventObject)
		CloseHandle(EventObject);

	if(WaitObject)
		RtlDeregisterWaitEx(WaitObject, NULL);

	return hReturn;
}

HMODULE ProxyRegisterWaitLoadLibraryA(_In_ LPCSTR lpModuleName)
{
	RTLREGISTERWAIT RtlRegisterWait = NULL;
	RTLDEREGISTERWAITEX RtlDeregisterWaitEx = NULL;
	NTWAITFORSINGLEOBJECT NtWaitForSingleObject = NULL;
	HANDLE WaitObject = NULL, EventObject = NULL;
	HMODULE hReturn = NULL;
	LARGE_INTEGER Timeout = { 0 };
	Timeout.QuadPart = 500;

	NtWaitForSingleObject = (NTWAITFORSINGLEOBJECT)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "NtWaitForSingleObject");
	RtlRegisterWait = (RTLREGISTERWAIT)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "RtlRegisterWait");
	RtlDeregisterWaitEx = (RTLDEREGISTERWAITEX)GetProcAddressA((DWORD64)GetModuleHandleEx2W(L"ntdll.dll"), "RtlDeregisterWaitEx");

	if (!RtlRegisterWait || !NtWaitForSingleObject || !RtlDeregisterWaitEx)
		goto EXIT_ROUTINE;

	EventObject = CreateEventW(NULL, FALSE, FALSE, NULL);
	if (EventObject == NULL)
		goto EXIT_ROUTINE;

	if (RtlRegisterWait(&WaitObject, EventObject, (WORKERCALLBACKFUNC)LoadLibraryA, (PVOID)lpModuleName, 0, WT_EXECUTEDEFAULT) != STATUS_SUCCESS)
		goto EXIT_ROUTINE;
	else
		NtWaitForSingleObject(EventObject, FALSE, &Timeout);

	hReturn = GetModuleHandleEx2A(lpModuleName);

EXIT_ROUTINE:

	if (EventObject)
		CloseHandle(EventObject);

	if (WaitObject)
		RtlDeregisterWaitEx(WaitObject, NULL);

	return hReturn;
}