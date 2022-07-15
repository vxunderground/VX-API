BOOL RfDeleteFileA(PCHAR Path)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;

	if (Path == NULL)
		return FALSE;

	if (!IsPathValidA(Path))
		return FALSE;

	hHandle = CreateFileA(Path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	CloseHandle(hHandle);

	return TRUE;
}

BOOL RfDeleteFileW(PWCHAR Path)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;

	if (Path == NULL)
		return FALSE;

	if (!IsPathValidW(Path))
		return FALSE;

	hHandle = CreateFileW(Path, GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_FLAG_DELETE_ON_CLOSE, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	CloseHandle(hHandle);

	return TRUE;
}
