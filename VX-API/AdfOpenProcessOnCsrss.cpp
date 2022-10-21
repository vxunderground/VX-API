#include "Win32Helper.h"

BOOL AdfOpenProcessOnCsrss(VOID)
{
	HMODULE hNtdll = NULL;
	CSRGETPROCESSID CsrGetProcessId = NULL;
	HANDLE hCsrHandle = NULL;

	hNtdll = GetModuleHandleEx2W(L"ntdll.dll");
	if (hNtdll == NULL)
		return FALSE;

	CsrGetProcessId = (CSRGETPROCESSID)GetProcAddressA((DWORD64)hNtdll, "CsrGetProcessId");
	if (CsrGetProcessId == NULL)
		return FALSE;

	hCsrHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, CsrGetProcessId());
	if (hCsrHandle == NULL)
		return FALSE;

	if (hCsrHandle)
		CloseHandle(hCsrHandle);

	CsrGetProcessId = NULL;

	return TRUE;
}