LONGLONG RfGetFileSizeFromPathDisposeHandleW(PWCHAR Path, DWORD dwFlagsAndAttributes)
{
	LARGE_INTEGER LargeInteger;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
		
	hHandle = CreateFileW(Path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, dwFlagsAndAttributes, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		return INVALID_FILE_SIZE;

	if (GetFileSizeEx(hHandle, &LargeInteger))
	{
		if (hHandle)
			CloseHandle(hHandle);
		return LargeInteger.QuadPart;
	}
	
	return INVALID_FILE_SIZE;
}

DWORD RfGetFileSizeFromPathDisposeHandleA(PCHAR Path, DWORD dwFlagsAndAttributes)
{
	DWORD Size = ERROR_SUCCESS;
	HANDLE hHandle = INVALID_HANDLE_VALUE;

	hHandle = CreateFileA(Path, GENERIC_READ, FILE_SHARE_READ | FILE_SHARE_WRITE | FILE_SHARE_DELETE, NULL, OPEN_EXISTING, dwFlagsAndAttributes, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		return INVALID_FILE_SIZE;

	Size = GetFileSize(hHandle, NULL);

	if (hHandle)
		CloseHandle(hHandle);

	return Size;
}
