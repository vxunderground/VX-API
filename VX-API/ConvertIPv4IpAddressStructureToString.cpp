#include "Win32Helper.h"

#pragma warning( push )
#pragma warning( disable : 6101)
BOOL ConvertIPv4IpAddressStructureToStringW(_In_ PIN_ADDR Address, _Out_ PWCHAR Buffer)
{
#pragma warning( pop ) 
	RTLIPV4ADDRESSTOSTRINGW RtlIpv4AddressToStringW = NULL;
	HMODULE hModule = NULL;
	WCHAR DisposeableObject[32] = { 0 };

	if (Buffer == NULL)
		return FALSE;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return FALSE;

	RtlIpv4AddressToStringW = (RTLIPV4ADDRESSTOSTRINGW)GetProcAddressA((DWORD64)hModule, "RtlIpv4AddressToStringW");
	if (!RtlIpv4AddressToStringW)
		return FALSE;

	RtlIpv4AddressToStringW(Address, Buffer);

	RtlIpv4AddressToStringW = NULL;

	return TRUE;
}

#pragma warning( push )
#pragma warning( disable : 6101)
BOOL ConvertIPv4IpAddressStructureToStringA(_In_ PIN_ADDR Address, _Out_ PCHAR Buffer)
{
#pragma warning( pop ) 
	RTLIPV4ADDRESSTOSTRINGA RtlIpv4AddressToStringA = NULL;
	HMODULE hModule = NULL;
	WCHAR DisposeableObject[32] = { 0 };

	if (Buffer == NULL)
		return FALSE;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return FALSE;

	RtlIpv4AddressToStringA = (RTLIPV4ADDRESSTOSTRINGA)GetProcAddressA((DWORD64)hModule, "RtlIpv4AddressToStringA");
	if (!RtlIpv4AddressToStringA)
		return FALSE;

	RtlIpv4AddressToStringA(Address, Buffer);

	RtlIpv4AddressToStringA = NULL;

	return TRUE;
}