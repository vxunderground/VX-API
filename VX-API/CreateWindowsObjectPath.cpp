#include "Win32Helper.h"

BOOL CreateWindowsObjectPathW(_Inout_ PWCHAR pBuffer, _In_ PWCHAR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (!GetSystemWindowsDirectoryW(Size, pBuffer))
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

BOOL CreateWindowsObjectPathA(_Inout_ PCHAR pBuffer, _In_ PCHAR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (!GetSystemWindowsDirectoryA(Size, pBuffer))
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