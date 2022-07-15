HMODULE RfGetModuleHandleA(LPCSTR lpModuleName)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	CHAR wDllName[64] = { 0 };

	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	while (Module != NULL)
	{
		Module = (PLDR_MODULE)((PBYTE)Module->InMemoryOrderModuleList.Flink - 16);
		if (Module->BaseDllName.Buffer != NULL)
		{
			RfZeroMemory(wDllName, sizeof(wDllName));
			WCharStringToCharString(wDllName, Module->BaseDllName.Buffer, 64);
			if (StringCompareA(lpModuleName, wDllName) == 0)
				return (HMODULE)Module->BaseAddress;
		}
	}

	return NULL;
}

HMODULE RfGetModuleHandleW(LPCWSTR lpModuleName)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;

	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	while (Module != NULL)
	{
		Module = (PLDR_MODULE)((PBYTE)Module->InMemoryOrderModuleList.Flink - 16);
		if (Module->BaseDllName.Buffer != NULL)
		{
			if (StringCompareW(lpModuleName, Module->BaseDllName.Buffer) == 0)
				return (HMODULE)Module->BaseAddress;
		}
	}

	return NULL;
}
