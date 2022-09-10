#include "Win32Helper.h"

DWORD GetProcessPathFromProcessParametersA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->ImagePathName.Length)
		return 0;

	return (DWORD)WCharStringToCharString(lpBuffer, ProcessParameters->ImagePathName.Buffer, ProcessParameters->ImagePathName.MaximumLength);
}

DWORD GetProcessPathFromProcessParametersW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->ImagePathName.Length)
		return 0;

	if (StringCopyW(lpBuffer, ProcessParameters->ImagePathName.Buffer) == NULL)
		return 0;

	return ProcessParameters->ImagePathName.Length;
}