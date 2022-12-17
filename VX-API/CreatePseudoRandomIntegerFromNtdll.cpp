#include "Win32Helper.h"

ULONG CreatePseudoRandomIntegerFromNtdll(_In_ ULONG Seed)
{
	RTLUNIFORM RtlUniform = NULL;
	HMODULE hModule = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	RtlUniform = (RTLUNIFORM)GetProcAddressA((DWORD64)hModule, "RtlUniform");
	if (!RtlUniform)
		return 0;

	return RtlUniform(&Seed);
}