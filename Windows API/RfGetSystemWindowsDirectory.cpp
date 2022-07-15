BOOL RfGetSystemWindowsDirectoryA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PKUSER_SHARED_DATA SharedData = GetKUserSharedData();

	if (nBufferLength < StringLengthW(SharedData->NtSystemRoot))
		return FALSE;

	if (WCharStringToCharString(lpBuffer, SharedData->NtSystemRoot, nBufferLength) != 0)
		return TRUE;
	else
		return FALSE;
}

BOOL RfGetSystemWindowsDirectoryW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PKUSER_SHARED_DATA SharedData = GetKUserSharedData();

	if (nBufferLength < StringLengthW(SharedData->NtSystemRoot))
		return FALSE;

	if (StringCopyW(lpBuffer, SharedData->NtSystemRoot) == NULL)
		return FALSE;

	return TRUE;
}
