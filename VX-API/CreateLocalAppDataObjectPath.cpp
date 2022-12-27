#include "Win32Helper.h"

BOOL CreateLocalAppDataObjectPathW(_Inout_ PWCHAR pBuffer, _In_ LPCWSTR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (GetEnvironmentVariableW(L"LOCALAPPDATA", pBuffer, Size) == 0)
		return FALSE;

	if (StringConcatW(pBuffer, Path) == 0)
		return FALSE;

	if (bDoesObjectExist)
	{
		if (!IsPathValidW(pBuffer))
			return FALSE;
	}

	return TRUE;
}

BOOL CreateLocalAppDataObjectPathA(_Inout_ PCHAR pBuffer, _In_ LPCSTR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (GetEnvironmentVariableA("LOCALAPPDATA", pBuffer, Size) == 0)
		return FALSE;

	if (StringConcatA(pBuffer, Path) == 0)
		return FALSE;

	if (bDoesObjectExist)
	{
		if (!IsPathValidA(pBuffer))
			return FALSE;
	}

	return TRUE;
}
