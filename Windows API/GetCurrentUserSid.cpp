/*
hToken can be NULL
DisposeProcessHandle closes hToken automatically
if DisposeProcessHandle is FALSE you need to close it yourself
The value returned by this function needs to be freed with HeapFree
*/
LPWSTR GetCurrentUserSidW(HANDLE hToken, BOOL DisposeProcessHandle)
{
	typedef BOOL(WINAPI* CONVERTSIDTOSTRINGSIDW)(PSID, LPWSTR*);
	CONVERTSIDTOSTRINGSIDW ConvertSidToStringSidW;
	PSID Sid = NULL;
	PTOKEN_GROUPS TokenGroup = NULL;
	DWORD dwError = ERROR_SUCCESS, dwIndex = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	LPWSTR pSid = NULL;
	HMODULE hAdvapi = NULL;

	hAdvapi = LoadLibraryW(L"Advapi32.dll");
	if (hAdvapi == NULL)
		goto EXIT_ROUTINE;

	ConvertSidToStringSidW = (CONVERTSIDTOSTRINGSIDW)RfGetProcAddressA((DWORD64)hAdvapi, "ConvertSidToStringSidW");
	if (!ConvertSidToStringSidW)
		goto EXIT_ROUTINE;

	if (!OpenProcessToken(RfGetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
		return NULL;

	dwError = GetTokenInformationBufferSize(hToken);
	if (dwError == 0)
		goto EXIT_ROUTINE;

	TokenGroup = (PTOKEN_GROUPS)HeapAlloc(RfGetProcessHeap(), HEAP_ZERO_MEMORY, dwError);
	if (TokenGroup == NULL)
		goto EXIT_ROUTINE;

	if (!GetTokenInformation(hToken, TokenGroups, (LPVOID)TokenGroup, dwError, &dwError))
		goto EXIT_ROUTINE;

	for (; dwIndex < TokenGroup->GroupCount; dwIndex++)
	{
		if ((TokenGroup->Groups[dwIndex].Attributes & SE_GROUP_LOGON_ID) == SE_GROUP_LOGON_ID)
		{
			if (!IsValidSid(TokenGroup->Groups[dwIndex].Sid))
				continue;

			dwError = GetLengthSid(TokenGroup->Groups[dwIndex].Sid);

			Sid = (PSID)HeapAlloc(RfGetProcessHeap(), HEAP_ZERO_MEMORY, dwError);
			if (Sid == NULL)
				goto EXIT_ROUTINE;

			if (!CopySid(dwError, Sid, TokenGroup->Groups[dwIndex].Sid))
				goto EXIT_ROUTINE;

			if (!ConvertSidToStringSidW(Sid, &pSid))
				goto EXIT_ROUTINE;
			else
				break;
		}
	}

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = EhGetLastError();

	if (TokenGroup)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, TokenGroup);

	if (Sid)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, Sid);

	if (hAdvapi)
		FreeLibrary(hAdvapi);

	if (DisposeProcessHandle)
	{
		if (hToken)
			CloseHandle(hToken);
	}

	return (bFlag ? pSid : NULL);
}

LPSTR GetCurrentUserSidA(HANDLE hToken, BOOL DisposeProcessHandle)
{
	typedef BOOL(WINAPI* CONVERTSIDTOSTRINGSIDA)(PSID, LPSTR*);
	CONVERTSIDTOSTRINGSIDA ConvertSidToStringSidA;
	PSID Sid = NULL;
	PTOKEN_GROUPS TokenGroup = NULL;
	DWORD dwError = ERROR_SUCCESS, dwIndex = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	LPSTR pSid = NULL;
	HMODULE hAdvapi = NULL;

	hAdvapi = LoadLibraryW(L"Advapi32.dll");
	if (hAdvapi == NULL)
		goto EXIT_ROUTINE;

	ConvertSidToStringSidA = (CONVERTSIDTOSTRINGSIDA)RfGetProcAddressA((DWORD64)hAdvapi, "ConvertSidToStringSidA");
	if (!ConvertSidToStringSidA)
		goto EXIT_ROUTINE;

	if (!OpenProcessToken(RfGetCurrentProcess(), TOKEN_ALL_ACCESS, &hToken))
		return NULL;

	dwError = GetTokenInformationBufferSize(hToken);
	if (dwError == 0)
		goto EXIT_ROUTINE;

	TokenGroup = (PTOKEN_GROUPS)HeapAlloc(RfGetProcessHeap(), HEAP_ZERO_MEMORY, dwError);
	if (TokenGroup == NULL)
		goto EXIT_ROUTINE;

	if (!GetTokenInformation(hToken, TokenGroups, (LPVOID)TokenGroup, dwError, &dwError))
		goto EXIT_ROUTINE;

	for (; dwIndex < TokenGroup->GroupCount; dwIndex++)
	{
		if ((TokenGroup->Groups[dwIndex].Attributes & SE_GROUP_LOGON_ID) == SE_GROUP_LOGON_ID)
		{
			if (!IsValidSid(TokenGroup->Groups[dwIndex].Sid))
				continue;

			dwError = GetLengthSid(TokenGroup->Groups[dwIndex].Sid);

			Sid = (PSID)HeapAlloc(RfGetProcessHeap(), HEAP_ZERO_MEMORY, dwError);
			if (Sid == NULL)
				goto EXIT_ROUTINE;

			if (!CopySid(dwError, Sid, TokenGroup->Groups[dwIndex].Sid))
				goto EXIT_ROUTINE;

			if (!ConvertSidToStringSidA(Sid, &pSid))
				goto EXIT_ROUTINE;
			else
				break;
		}
	}

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = EhGetLastError();

	if (TokenGroup)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, TokenGroup);

	if (Sid)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, Sid);

	if (hAdvapi)
		FreeLibrary(hAdvapi);

	if (DisposeProcessHandle)
	{
		if (hToken)
			CloseHandle(hToken);
	}

	return (bFlag ? pSid : NULL);
}
