#include "Win32Helper.h"

DWORD64 LdrLoadGetProcedureAddress(VOID)
{
	PBYTE pFunctionName = NULL;
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;
	HMODULE hModule = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return 0;

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, (PBYTE*)&hModule);

	IMAGE_EXPORT_DIRECTORY* ExportTable = (PIMAGE_EXPORT_DIRECTORY)((DWORD64)hModule + Optional->DataDirectory[0].VirtualAddress);
	PDWORD FunctionNameAddressArray = (PDWORD)((LPBYTE)(DWORD64)hModule + ExportTable->AddressOfNames);
	PDWORD FunctionAddressArray = (PDWORD)((LPBYTE)(DWORD64)hModule + ExportTable->AddressOfFunctions);
	PWORD FunctionOrdinalAddressArray = (PWORD)((LPBYTE)(DWORD64)hModule + ExportTable->AddressOfNameOrdinals);

	for (DWORD dwX = 0; dwX < ExportTable->NumberOfNames; dwX++)
	{
		pFunctionName = FunctionNameAddressArray[dwX] + (PBYTE)hModule;

		if (StringCompareA((PCHAR)pFunctionName, "LdrGetProcedureAddress") == 0)
			return ((DWORD64)hModule + FunctionAddressArray[FunctionOrdinalAddressArray[dwX]]);
	}

	return 0;
}