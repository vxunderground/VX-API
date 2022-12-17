#include "Win32Helper.h"

ULONG ConvertCharacterStringToIntegerUsingNtdllA(_In_ PCHAR InString)
{
	RTLCHARTOINTEGER RtlCharToInteger = NULL;
	HMODULE hModule = NULL;
	ULONG ConvertedString = ERROR_SUCCESS;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	RtlCharToInteger = (RTLCHARTOINTEGER)GetProcAddressA((DWORD64)hModule, "RtlCharToInteger");
	if (!RtlCharToInteger)
		return 0;

	if (RtlCharToInteger(InString, 10, &ConvertedString) != STATUS_SUCCESS)
		return 0;

	return ConvertedString;
}

ULONG ConvertCharacterStringToIntegerUsingNtdllW(_In_ PWCHAR InString)
{
	RTLCHARTOINTEGER RtlCharToInteger = NULL;
	HMODULE hModule = NULL;
	ULONG ConvertedString = ERROR_SUCCESS;
	CHAR pBuffer[MAX_PATH] = { 0 };

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	RtlCharToInteger = (RTLCHARTOINTEGER)GetProcAddressA((DWORD64)hModule, "RtlCharToInteger");
	if (!RtlCharToInteger)
		return 0;

	WCharStringToCharString(pBuffer, InString, StringLengthW((PWCHAR)InString));

	if (RtlCharToInteger(pBuffer, 10, &ConvertedString) != STATUS_SUCCESS)
		return 0;

	return ConvertedString;
}