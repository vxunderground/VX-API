#include "Win32Helper.h"
//
//BOOL GetResourceData(HMODULE hModule, WORD ResourceId, PVOID* ppResourceRawData, PDWORD psResourceDataSize) {
//
//	CHAR*				pBaseAddr		= (CHAR*)hModule;
//	PIMAGE_DOS_HEADER 		pImgDosHdr		= (PIMAGE_DOS_HEADER)pBaseAddr;
//	PIMAGE_NT_HEADERS 		pImgNTHdr		= (PIMAGE_NT_HEADERS)(pBaseAddr + pImgDosHdr->e_lfanew);
//	PIMAGE_OPTIONAL_HEADER 		pImgOptionalHdr 	= (PIMAGE_OPTIONAL_HEADER)&pImgNTHdr->OptionalHeader;
//	PIMAGE_DATA_DIRECTORY 		pDataDir		= (PIMAGE_DATA_DIRECTORY)&pImgOptionalHdr->DataDirectory[IMAGE_DIRECTORY_ENTRY_RESOURCE];
//	
//	PIMAGE_RESOURCE_DIRECTORY	pResourceDir	= NULL, pResourceDir2	= NULL, pResourceDir3	= NULL;
//	PIMAGE_RESOURCE_DIRECTORY_ENTRY pResourceEntry	= NULL, pResourceEntry2 = NULL, pResourceEntry3 = NULL;
//	
//	PIMAGE_RESOURCE_DATA_ENTRY	pResource	= NULL;
//
//
//	pResourceDir   = (PIMAGE_RESOURCE_DIRECTORY)(pBaseAddr + pDataDir->VirtualAddress);
//	pResourceEntry = (IMAGE_RESOURCE_DIRECTORY_ENTRY*)(pResourceDir + 1);
//
//
//	for (size_t i = 0; i < (pResourceDir->NumberOfNamedEntries + pResourceDir->NumberOfIdEntries); i++) {
//
//		if (pResourceEntry[i].DataIsDirectory == 0)
//			break;
//		
//		pResourceDir2   = (PIMAGE_RESOURCE_DIRECTORY)(pBaseAddr + pDataDir->VirtualAddress + (pResourceEntry[i].OffsetToDirectory & 0x7FFFFFFF));
//		pResourceEntry2 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResourceDir2 + 1);
//
//		if (pResourceEntry2->DataIsDirectory == 1 && pResourceEntry2->Id == ResourceId){
//
//			pResourceDir3   = (PIMAGE_RESOURCE_DIRECTORY)(pBaseAddr + pDataDir->VirtualAddress + (pResourceEntry2->OffsetToDirectory & 0x7FFFFFFF));
//			pResourceEntry3 = (PIMAGE_RESOURCE_DIRECTORY_ENTRY)(pResourceDir3 + 1);
//
//			pResource = (PIMAGE_RESOURCE_DATA_ENTRY)(pBaseAddr + pDataDir->VirtualAddress + (pResourceEntry3->OffsetToData & 0x7FFFFFFF));
//
//			*ppResourceRawData  = (PVOID)(pBaseAddr + (pResource->OffsetToData));
//			*psResourceDataSize = pResource->Size;
//
//			break;
//		}
//
//	}
//
//	if (*ppResourceRawData != NULL && *psResourceDataSize != NULL)
//		return TRUE;
//
//	return FALSE;
//}

