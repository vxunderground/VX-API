#include "Win32Helper.h"

DWORD GetTokenInformationBufferSize(HANDLE hToken)
{
	PTOKEN_GROUPS TokenGroup = NULL;
	DWORD dwReturn = ERROR_SUCCESS;

	GetTokenInformation(hToken, TokenGroups, (LPVOID)TokenGroup, 0, &dwReturn);

	return dwReturn;
}

LPWSTR GetCurrentUserSidW(VOID)
{
	PSID Sid = NULL;
	PTOKEN_GROUPS TokenGroup = NULL;
	DWORD dwError = ERROR_SUCCESS, dwIndex = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	LPWSTR pSid = NULL;
	HANDLE hToken = NULL;

	if (!OpenProcessToken(GetCurrentProcessNoForward(), TOKEN_ALL_ACCESS, &hToken))
		return NULL;

	dwError = GetTokenInformationBufferSize(hToken);
	if (dwError == 0)
		goto EXIT_ROUTINE;

	TokenGroup = (PTOKEN_GROUPS)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwError);
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

			Sid = (PSID)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwError);
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
		dwError = GetLastErrorFromTeb();

	if (TokenGroup)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, TokenGroup);

	if (Sid)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Sid);

	if (hToken)
		CloseHandle(hToken);

	return (bFlag ? pSid : NULL);
}

LPSTR GetCurrentUserSidA(VOID)
{
	PSID Sid = NULL;
	PTOKEN_GROUPS TokenGroup = NULL;
	DWORD dwError = ERROR_SUCCESS, dwIndex = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	LPSTR pSid = NULL;
	HANDLE hToken = NULL;

	if (!OpenProcessToken(GetCurrentProcessNoForward(), TOKEN_ALL_ACCESS, &hToken))
		return NULL;

	dwError = GetTokenInformationBufferSize(hToken);
	if (dwError == 0)
		goto EXIT_ROUTINE;

	TokenGroup = (PTOKEN_GROUPS)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwError);
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

			Sid = (PSID)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwError);
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
		dwError = GetLastErrorFromTeb();

	if (TokenGroup)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, TokenGroup);

	if (Sid)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Sid);

	if (hToken)
		CloseHandle(hToken);

	return (bFlag ? pSid : NULL);
}