#include "Win32Helper.h"

DWORD IsRegistryKeyValidW(_In_ HKEY PredefinedKey, _In_ PWCHAR Path)
{
	HKEY hKey = NULL;
	DWORD dwError = ERROR_SUCCESS;

	dwError = RegOpenKeyExW(PredefinedKey, Path, 0, GENERIC_READ | GENERIC_WRITE, &hKey);

	if (hKey)
		RegCloseKey(hKey);

	return dwError;
}

DWORD IsRegistryKeyValidA(_In_ HKEY PredefinedKey, _In_ PCHAR Path)
{
	HKEY hKey = NULL;
	DWORD dwError = ERROR_SUCCESS;

	dwError = RegOpenKeyExA(PredefinedKey, Path, 0, GENERIC_READ | GENERIC_WRITE, &hKey);

	if (hKey)
		RegCloseKey(hKey);

	return dwError;
}