#include "Win32Helper.h"

ULONG ConvertIPv4StringToUnsignedLongW(_In_ PWCHAR IpAddress)
{
	RTLIPV4STRINGTOADDRESSW RtlIpv4StringToAddressW = NULL;
	HMODULE hModule = NULL;
	IN_ADDR IpAddressObject = { 0 };
	LPCWSTR TerminatorObject = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	RtlIpv4StringToAddressW = (RTLIPV4STRINGTOADDRESSW)GetProcAddressA((DWORD64)hModule, "RtlIpv4StringToAddressW");
	if (!RtlIpv4StringToAddressW)
		return 0;

	if (RtlIpv4StringToAddressW(IpAddress, FALSE, &TerminatorObject, &IpAddressObject) != ERROR_SUCCESS)
		return FALSE;

	RtlIpv4StringToAddressW = NULL;

	return IpAddressObject.S_un.S_addr;
}

ULONG ConvertIPv4StringToUnsignedLongA(_In_ PCHAR IpAddress)
{
	RTLIPV4STRINGTOADDRESSA RtlIpv4StringToAddressA = NULL;
	HMODULE hModule = NULL;
	IN_ADDR IpAddressObject = { 0 };
	LPCSTR TerminatorObject = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	RtlIpv4StringToAddressA = (RTLIPV4STRINGTOADDRESSA)GetProcAddressA((DWORD64)hModule, "RtlIpv4StringToAddressA");
	if (!RtlIpv4StringToAddressA)
		return 0;

	if (RtlIpv4StringToAddressA(IpAddress, FALSE, &TerminatorObject, &IpAddressObject) != ERROR_SUCCESS)
		return FALSE;

	RtlIpv4StringToAddressA = NULL;

	return IpAddressObject.S_un.S_addr;
}