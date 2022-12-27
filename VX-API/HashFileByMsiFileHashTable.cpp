#include "Win32Helper.h"

//NOTE: PULONG must be pointed to an array of ULONG integers e.g. ULONG FileHash[4] = { 0 };
BOOL HashFileByMsiFileHashTableW(_In_ LPCWSTR Path, _Inout_ PULONG FileHash)
{
	MSIGETFILEHASHW MsiGetFileHashW = NULL;
	MSIFILEHASHINFO Hash = { 0 };
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;

	Hash.dwFileHashInfoSize = sizeof(Hash);

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"msi.dll");
	if (hModule == NULL)
		return FALSE;

	MsiGetFileHashW = (MSIGETFILEHASHW)GetProcAddressA((DWORD64)hModule, "MsiGetFileHashW");
	if (MsiGetFileHashW == NULL)
		goto EXIT_ROUTINE;

	if (!IsPathValidW(Path))
		goto EXIT_ROUTINE;

	Hash.dwFileHashInfoSize = sizeof(MSIFILEHASHINFO);
	if (MsiGetFileHashW(Path, 0, &Hash) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0; dwX < 4; dwX++)
		FileHash[dwX] = Hash.dwData[dwX];

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	MsiGetFileHashW = NULL;

	return bFlag;
}

BOOL HashFileByMsiFileHashTableA(_In_ LPCSTR Path, _Inout_ PULONG FileHash)
{
	MSIGETFILEHASHA MsiGetFileHashA = NULL;
	MSIFILEHASHINFO Hash = { 0 };
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;

#pragma warning( push )
#pragma warning( disable : 6384)
	if ((sizeof(FileHash) / sizeof(ULONG)) < 4)
		return FALSE;
#pragma warning( pop )

	Hash.dwFileHashInfoSize = sizeof(Hash);

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"msi.dll");
	if (hModule == NULL)
		return FALSE;

	MsiGetFileHashA = (MSIGETFILEHASHA)GetProcAddressW((DWORD64)hModule, L"MsiGetFileHashA");
	if (MsiGetFileHashA == NULL)
		goto EXIT_ROUTINE;

	if (!IsPathValidA(Path))
		goto EXIT_ROUTINE;

	Hash.dwFileHashInfoSize = sizeof(MSIFILEHASHINFO);
	if (MsiGetFileHashA(Path, 0, &Hash) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0; dwX < 4; dwX++)
		FileHash[dwX] = Hash.dwData[dwX];

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	MsiGetFileHashA = NULL;

	return bFlag;
}