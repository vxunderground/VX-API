DWORD RfGetCurrentWindowTextA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->WindowTitle.Length)
		return ERROR_FAILURE_RETURN;

	return (DWORD)WCharStringToCharString(lpBuffer, ProcessParameters->WindowTitle.Buffer, ProcessParameters->WindowTitle.MaximumLength);
}

DWORD RfGetCurrentWindowTextW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->WindowTitle.Length)
		return ERROR_FAILURE_RETURN;

	if (StringCopyW(lpBuffer, ProcessParameters->WindowTitle.Buffer) == NULL)
		return ERROR_FAILURE_RETURN;

	return ProcessParameters->WindowTitle.Length;
}
