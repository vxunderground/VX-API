#include "Win32Helper.h"

DWORD64 __stdcall GetProcAddressA(_In_ DWORD64 ModuleBase, _In_ LPCSTR lpProcName)
{
	PBYTE pFunctionName = NULL;
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;
	LDRGETPROCEDUREADDRESS LdrGetProcedureAddress = NULL;
	DWORD64 FunctionAddress = ERROR_SUCCESS;
	ANSI_STRING ForwardFunctionString = { 0 };

	LdrGetProcedureAddress = (LDRGETPROCEDUREADDRESS)LdrLoadGetProcedureAddress();

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, (PBYTE*)&ModuleBase);

	IMAGE_EXPORT_DIRECTORY* ExportTable = (PIMAGE_EXPORT_DIRECTORY)(ModuleBase + Optional->DataDirectory[0].VirtualAddress);
	PDWORD FunctionNameAddressArray = (PDWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfNames);
	PDWORD FunctionAddressArray = (PDWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfFunctions);
	PWORD FunctionOrdinalAddressArray = (PWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfNameOrdinals);

	for (DWORD dwX = 0; dwX < ExportTable->NumberOfNames; dwX++)
	{
		pFunctionName = FunctionNameAddressArray[dwX] + (PBYTE)ModuleBase;
		
		if (StringCompareA((PCHAR)pFunctionName, lpProcName) == 0)
		{
			FunctionAddress = (DWORD64)ModuleBase + FunctionAddressArray[FunctionOrdinalAddressArray[dwX]];
			if (FunctionAddress >= (ModuleBase + Optional->DataDirectory[0].VirtualAddress) && 
				FunctionAddress < (ModuleBase + Optional->DataDirectory[0].VirtualAddress) + (ModuleBase + Optional->DataDirectory[0].Size))
			{
				ForwardFunctionString.Buffer = (PCHAR)pFunctionName;
				ForwardFunctionString.Length = (USHORT)StringLengthA((PCHAR)pFunctionName);
				ForwardFunctionString.MaximumLength = ForwardFunctionString.Length + sizeof(CHAR);

				if (LdrGetProcedureAddress((HMODULE)ModuleBase, &ForwardFunctionString, 0, &FunctionAddress) != STATUS_SUCCESS)
					return 0;
			}

			return FunctionAddress;
		}
	}

	return 0;
}

DWORD64 __stdcall GetProcAddressW(_In_ DWORD64 ModuleBase, _In_ LPCWSTR lpProcName)
{
	PBYTE pFunctionName = NULL;
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;
	LDRGETPROCEDUREADDRESS LdrGetProcedureAddress = NULL;
	DWORD64 FunctionAddress = ERROR_SUCCESS;
	ANSI_STRING ForwardFunctionString = { 0 };

	LdrGetProcedureAddress = (LDRGETPROCEDUREADDRESS)LdrLoadGetProcedureAddress();

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, (PBYTE*)&ModuleBase);

	IMAGE_EXPORT_DIRECTORY* ExportTable = (PIMAGE_EXPORT_DIRECTORY)(ModuleBase + Optional->DataDirectory[0].VirtualAddress);
	PDWORD FunctionNameAddressArray = (PDWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfNames);
	PDWORD FunctionAddressArray = (PDWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfFunctions);
	PWORD FunctionOrdinalAddressArray = (PWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfNameOrdinals);

	for (DWORD dwX = 0; dwX < ExportTable->NumberOfNames; dwX++)
	{
		WCHAR wFunctionName[256] = { 0 };
		pFunctionName = FunctionNameAddressArray[dwX] + (PBYTE)ModuleBase;

		if (CharStringToWCharString(wFunctionName, (PCHAR)pFunctionName, 256) == 0)
			break;

		if (StringCompareW(wFunctionName, lpProcName) == 0)
		{
			FunctionAddress = (DWORD64)ModuleBase + FunctionAddressArray[FunctionOrdinalAddressArray[dwX]];
			if (FunctionAddress >= (ModuleBase + Optional->DataDirectory[0].VirtualAddress) &&
				FunctionAddress < (ModuleBase + Optional->DataDirectory[0].VirtualAddress) + (ModuleBase + Optional->DataDirectory[0].Size))
			{
				ForwardFunctionString.Buffer = (PCHAR)pFunctionName;
				ForwardFunctionString.Length = (USHORT)StringLengthA((PCHAR)pFunctionName);
				ForwardFunctionString.MaximumLength = ForwardFunctionString.Length + sizeof(CHAR);

				if (LdrGetProcedureAddress((HMODULE)ModuleBase, &ForwardFunctionString, 0, &FunctionAddress) != STATUS_SUCCESS)
					return 0;
			}

			return FunctionAddress;
		}
	}

	return 0;
}