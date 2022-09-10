#include "Win32Helper.h"

BOOL CreateWindowsObjectPathW(PWCHAR pBuffer, PWCHAR Path, DWORD Size, BOOL bDoesObjectExist)
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

BOOL CreateWindowsObjectPathA(PCHAR pBuffer, PCHAR Path, DWORD Size, BOOL bDoesObjectExist)
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