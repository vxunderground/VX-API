/*

pBuffer == OUT
Path == concatted, must have \\ in front i.e. L"\\File.exe"

Credit: smelly__vx
*/
BOOL CreateLocalAppDataObjectPathW(PWCHAR pBuffer, PWCHAR Path, DWORD Size, BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (RfGetEnvironmentVariableW(L"LOCALAPPDATA", pBuffer, Size) == 0)
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

BOOL CreateLocalAppDataObjectPathA(PCHAR pBuffer, PCHAR Path, DWORD Size, BOOL bDoesObjectExist)
{
	if (pBuffer == NULL)
		return FALSE;

	if (RfGetEnvironmentVariableA("LOCALAPPDATA", pBuffer, Size) == 0)
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
