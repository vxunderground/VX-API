#include "Win32Helper.h"

DWORD GetCurrentDirectoryExA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (ProcessParameters->CurrentDirectory.DosPath.Length > nBufferLength)
		return 0;

	return (DWORD)WCharStringToCharString(lpBuffer, ProcessParameters->CurrentDirectory.DosPath.Buffer, ProcessParameters->CurrentDirectory.DosPath.MaximumLength);
}

DWORD GetCurrentDirectoryExW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (ProcessParameters->CurrentDirectory.DosPath.Length > nBufferLength)
		return 0;

	if (StringCopyW(lpBuffer, ProcessParameters->CurrentDirectory.DosPath.Buffer) == NULL)
		return 0;

	return ProcessParameters->CurrentDirectory.DosPath.Length;
}