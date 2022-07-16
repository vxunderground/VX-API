/*
Some debuggers can be detected by using the kernel32!OpenProcess() function on the csrss.exe process. 
The call will succeed only if the user for the process is a member of the administrators group and 
has debug privileges.

Credit: Checkpoint Research
*/

BOOL AdfOpenProcessOnCsrss(VOID)
{
	typedef DWORD(WINAPI* CSRGETPROCESSID)(VOID);
	HMODULE hNtdll = NULL;
	CSRGETPROCESSID CsrGetProcessId = NULL;
	HANDLE hCsrHandle = NULL;

	hNtdll = RfGetModuleHandleW(L"ntdll.dll");
	if (hNtdll == NULL)
		return FALSE;

	CsrGetProcessId = (CSRGETPROCESSID)RfGetProcAddressA((DWORD64)hNtdll, "CsrGetProcessId");
	if (CsrGetProcessId == NULL)
		return FALSE;

	hCsrHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CsrGetProcessId());
	if (hCsrHandle == NULL)
		return FALSE;

	if (hCsrHandle)
		CloseHandle(hCsrHandle);

	return TRUE;
}
