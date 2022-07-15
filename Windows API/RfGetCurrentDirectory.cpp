DWORD RfGetCurrentDirectoryA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (ProcessParameters->CurrentDirectory.DosPath.Length > nBufferLength)
		return ERROR_FAILURE_RETURN;

	return (DWORD)WCharStringToCharString(lpBuffer, ProcessParameters->CurrentDirectory.DosPath.Buffer, ProcessParameters->CurrentDirectory.DosPath.MaximumLength);
}

DWORD RfGetCurrentDirectoryW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (ProcessParameters->CurrentDirectory.DosPath.Length > nBufferLength)
		return ERROR_FAILURE_RETURN;

	if (StringCopyW(lpBuffer, ProcessParameters->CurrentDirectory.DosPath.Buffer) == NULL)
		return ERROR_FAILURE_RETURN;

	return ProcessParameters->CurrentDirectory.DosPath.Length;
}
