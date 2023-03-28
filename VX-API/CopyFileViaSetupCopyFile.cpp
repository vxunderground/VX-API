#include "Win32Helper.h"

BOOL CopyFileViaSetupCopyFileW(LPCWSTR Source, LPCWSTR Destination)
{
	return SetupDecompressOrCopyFileW(Source, Destination, FILE_COMPRESSION_NONE);
}


BOOL CopyFileViaSetupCopyFileA(LPCSTR Source, LPCSTR Destination)
{
	WCHAR wSource[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR wDestination[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(wSource, (PCHAR)Source, StringLengthA(Source) * sizeof(WCHAR)) == 0)
		return FALSE;

	if (CharStringToWCharString(wDestination, (PCHAR)Destination, StringLengthA(Destination) * sizeof(WCHAR)) == 0)
		return FALSE;

	return SetupDecompressOrCopyFileW(wSource, wDestination, FILE_COMPRESSION_NONE);
}

