#include "Win32Helper.h"

BOOL IsProcessRunningAsAdmin2(VOID)
{
	ISNTADMIN IsNtAdmin = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;

	hMod = LoadLibraryW(L"advpack.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	IsNtAdmin = (ISNTADMIN)GetProcAddressA((DWORD64)hMod, "IsNTAdmin");
	if (!IsNtAdmin)
		goto EXIT_ROUTINE;

	bFlag = IsNtAdmin(0, NULL);

EXIT_ROUTINE:

	if (hMod)
		FreeLibrary(hMod);

	return bFlag;
}