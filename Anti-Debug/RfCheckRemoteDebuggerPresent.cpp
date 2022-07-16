/*

Created via ReactOS and IDA

Credit: smelly__vx
*/
BOOL RfCheckRemoteDebuggerPresent(HANDLE hHandle, PBOOL pbDebuggerPresent)
{
	typedef enum _PROCESSINFOCLASS
	{
		ProcessBasicInformation = 0,
		ProcessDebugPort = 7,
		ProcessWow64Information = 26,
		ProcessImageFileName = 27,
		ProcessBreakOnTermination = 29
	} PROCESSINFOCLASS;

	typedef NTSTATUS(NTAPI* NTQUERYINFORMATIONPROCESS)(HANDLE, PROCESSINFOCLASS, PVOID, ULONG, PULONG);
	*pbDebuggerPresent = FALSE;
	NTQUERYINFORMATIONPROCESS NtQueryInformationProcess = NULL;
	NTSTATUS Status = 0;
	DWORD dwProcessDebugPort = 0, dwReturnValue = 0;

	if (hHandle == NULL)
		return FALSE;

	HMODULE hModule = RfGetModuleHandleW(L"ntdll.dll");
	if (hModule == NULL)
		return FALSE;

	NtQueryInformationProcess = (NTQUERYINFORMATIONPROCESS)RfGetProcAddressW((DWORD64)hModule, L"NtQueryInformationProcess");
	if (!NtQueryInformationProcess)
		return FALSE;

	Status = NtQueryInformationProcess(hHandle, ProcessDebugPort, &dwProcessDebugPort, sizeof(DWORD), &dwReturnValue);
	if (NT_SUCCESS(Status) && dwProcessDebugPort == -1)
		return TRUE;

	*pbDebuggerPresent = TRUE;

	return TRUE;
}
