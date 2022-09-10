#include "Win32Helper.h"

DWORD GetCurrentWindowTextA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->WindowTitle.Length)
		return 0;

	return (DWORD)WCharStringToCharString(lpBuffer, ProcessParameters->WindowTitle.Buffer, ProcessParameters->WindowTitle.MaximumLength);
}

DWORD GetCurrentWindowTextW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->WindowTitle.Length)
		return 0;

	if (StringCopyW(lpBuffer, ProcessParameters->WindowTitle.Buffer) == NULL)
		return 0;

	return ProcessParameters->WindowTitle.Length;
}