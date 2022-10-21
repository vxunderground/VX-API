#include "Win32Helper.h"

BOOL GetSystemWindowsDirectoryA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer)
{
	PKUSER_SHARED_DATA SharedData = GetKUserSharedData();

	if (nBufferLength < StringLengthW(SharedData->NtSystemRoot))
		return FALSE;

	if (WCharStringToCharString(lpBuffer, SharedData->NtSystemRoot, nBufferLength) != 0)
		return TRUE;
	else
		return FALSE;
}

BOOL GetSystemWindowsDirectoryW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer)
{
	PKUSER_SHARED_DATA SharedData = GetKUserSharedData();

	if (nBufferLength < StringLengthW(SharedData->NtSystemRoot))
		return FALSE;

	if (StringCopyW(lpBuffer, SharedData->NtSystemRoot) == NULL)
		return FALSE;

	return TRUE;
}