DWORD GetInMemoryModulePathFromProcessParametersA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->ImagePathName.Length)
		return ERROR_FAILURE_RETURN;

	return (DWORD)WCharStringToCharString(lpBuffer, ProcessParameters->ImagePathName.Buffer, ProcessParameters->ImagePathName.MaximumLength);
}

DWORD GetInMemoryModulePathFromProcessParametersW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = GetPeb()->ProcessParameters;

	if (nBufferLength < ProcessParameters->ImagePathName.Length)
		return ERROR_FAILURE_RETURN;

	if (StringCopyW(lpBuffer, ProcessParameters->ImagePathName.Buffer) == NULL)
		return ERROR_FAILURE_RETURN;

	return ProcessParameters->ImagePathName.Length;
}
