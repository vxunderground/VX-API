DWORD GetInMemoryModulePathFromLoaderLoadModuleA(DWORD nBufferLength, PCHAR lpBuffer)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	if (nBufferLength < Module->FullDllName.Length)
		return ERROR_FAILURE_RETURN;

	return (DWORD)WCharStringToCharString(lpBuffer, Module->FullDllName.Buffer, Module->FullDllName.MaximumLength);
}

DWORD GetInMemoryModulePathFromLoaderLoadModuleW(DWORD nBufferLength, PWCHAR lpBuffer)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	if(nBufferLength < Module->FullDllName.Length)
		return ERROR_FAILURE_RETURN;

	if (StringCopyW(lpBuffer, Module->FullDllName.Buffer) == NULL)
		return ERROR_FAILURE_RETURN;

	return Module->FullDllName.Length;
}
