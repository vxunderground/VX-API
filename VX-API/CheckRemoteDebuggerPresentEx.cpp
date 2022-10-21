#include "Win32Helper.h"

BOOL CheckRemoteDebuggerPresent2(_In_ HANDLE hHandle, _Inout_ PBOOL pbDebuggerPresent)
{
	NTQUERYINFORMATIONPROCESS NtQueryInformationProcess = NULL;
	NTSTATUS Status = 0;
	DWORD dwProcessDebugPort = 0, dwReturnValue = 0;
	*pbDebuggerPresent = FALSE;

	if (hHandle == NULL)
		return FALSE;

	HMODULE hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return FALSE;

	NtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS)GetProcAddressA((DWORD64)hModule, "NtQueryInformationProcess");
	if (!NtQueryInformationProcess)
		return FALSE;

	Status = NtQueryInformationProcess(hHandle, ProcessDebugPort, &dwProcessDebugPort, sizeof(DWORD), &dwReturnValue);
	if (NT_SUCCESS(Status) && dwProcessDebugPort == -1)
		return TRUE;

	*pbDebuggerPresent = TRUE;

	NtQueryInformationProcess = NULL;

	return TRUE;
}