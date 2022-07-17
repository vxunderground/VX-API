/*

pBuffer == OUT
Path == concatted, must have \\ in front i.e. L"\\File.exe"

Credit: smelly__vx
*/
BOOL CreateWindowsObjectPathW(PWCHAR pBuffer, PWCHAR Path, DWORD Size, BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (!RfGetSystemWindowsDirectoryW(Size, pBuffer))
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

	if (!RfGetSystemWindowsDirectoryA(Size, pBuffer))
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
