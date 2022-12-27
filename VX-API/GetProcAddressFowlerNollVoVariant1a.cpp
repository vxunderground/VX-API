#include "Win32Helper.h"

DWORD64 __stdcall GetProcAddressFowlerNollVoVariant1a(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash)
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

		DWORD dwFunctionHash = HashStringFowlerNollVoVariant1aA((PCHAR)pFunctionName);
		if (Hash == dwFunctionHash)
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