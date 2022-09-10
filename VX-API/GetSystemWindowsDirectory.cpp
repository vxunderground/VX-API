#include "Win32Helper.h"

BOOL GetSystemWindowsDirectoryA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PKUSER_SHARED_DATA SharedData = GetKUserSharedData();

	if (nBufferLength < StringLengthW(SharedData->NtSystemRoot))
		return FALSE;

	if (WCharStringToCharString(lpBuffer, SharedData->NtSystemRoot, nBufferLength) != 0)
		return TRUE;
	else
		return FALSE;
}

BOOL GetSystemWindowsDirectoryW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PKUSER_SHARED_DATA SharedData = GetKUserSharedData();

	if (nBufferLength < StringLengthW(SharedData->NtSystemRoot))
		return FALSE;

	if (StringCopyW(lpBuffer, SharedData->NtSystemRoot) == NULL)
		return FALSE;

	return TRUE;
}