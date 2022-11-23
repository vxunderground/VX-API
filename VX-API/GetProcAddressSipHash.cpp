#include "Win32Helper.h"

DWORD64 __stdcall GetProcAddressSipHash(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash)
{
    PBYTE pFunctionName = NULL;
    PIMAGE_DOS_HEADER Dos = NULL;
    PIMAGE_NT_HEADERS Nt = NULL;
    PIMAGE_FILE_HEADER File = NULL;
    PIMAGE_OPTIONAL_HEADER Optional = NULL;

    RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, (PBYTE*)&ModuleBase);

    IMAGE_EXPORT_DIRECTORY* ExportTable = (PIMAGE_EXPORT_DIRECTORY)(ModuleBase + Optional->DataDirectory[0].VirtualAddress);
    PDWORD FunctionNameAddressArray = (PDWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfNames);
    PDWORD FunctionAddressArray = (PDWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfFunctions);
    PWORD FunctionOrdinalAddressArray = (PWORD)((LPBYTE)ModuleBase + ExportTable->AddressOfNameOrdinals);

    for (DWORD dwX = 0; dwX < ExportTable->NumberOfNames; dwX++)
    {
        pFunctionName = FunctionNameAddressArray[dwX] + (PBYTE)ModuleBase;

        DWORD dwFunctionHash = HashStringSipHashA((PCHAR)pFunctionName);
        if (Hash == dwFunctionHash)
            return ((DWORD64)ModuleBase + FunctionAddressArray[FunctionOrdinalAddressArray[dwX]]);
    }

    return 0;
}
