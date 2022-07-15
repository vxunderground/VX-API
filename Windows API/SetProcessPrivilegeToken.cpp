BOOL SetProcessPrivilegeToken(DWORD PrivilegeEnum)
{
	HANDLE Process = RfGetCurrentProcess();
	HANDLE Token = INVALID_HANDLE_VALUE;
	TOKEN_PRIVILEGES Privileges = { 0 };
	DWORD TokenLength = 0;
	LUID LocalId = { 0 };
	BOOL bFlag = FALSE;
	WCHAR PrivilegeString[256] = { 0 };

	if (!OpenProcessToken(Process, TOKEN_QUERY | TOKEN_ADJUST_PRIVILEGES, &Token))
		return FALSE;

	switch (PrivilegeEnum)
	{
		case 0:
		{
			StringCopyW(PrivilegeString, (PWCHAR)L"SeDebugPrivilege");
			break;
		}
		case 1:
		{
			StringCopyW(PrivilegeString, (PWCHAR)L"SeBackupPrivilege");
			break;
		}
		default:
			goto EXIT_ROUTINE;
	}

	if (LookupPrivilegeValueW(NULL, PrivilegeString, &LocalId))
	{
		Privileges.Privileges[0].Luid = LocalId;
		Privileges.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
		Privileges.PrivilegeCount = 1;

		if (!AdjustTokenPrivileges(Token, FALSE, &Privileges, 0, NULL, &TokenLength))
			goto EXIT_ROUTINE;

	}

	bFlag = TRUE;

EXIT_ROUTINE:

	if (Token)
		CloseHandle(Token);

	return bFlag;
}
