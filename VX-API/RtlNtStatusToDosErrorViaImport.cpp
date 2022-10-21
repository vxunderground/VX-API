#include "Win32Helper.h"

DWORD RtlNtStatusToDosErrorViaImport(_In_ NTSTATUS Status)
{
	RTLNTSTATUSTODOSERROR RtlNtStatusToDosError;
	HMODULE hModule = NULL;
	DWORD dwError = ERROR_SUCCESS;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return -1;

	RtlNtStatusToDosError = (RTLNTSTATUSTODOSERROR)GetProcAddressA((DWORD64)hModule, "RtlNtStatusToDosError");
	if (!RtlNtStatusToDosError)
		return -1;

	dwError = RtlNtStatusToDosError(Status);

	RtlNtStatusToDosError = NULL;

	return dwError;
}