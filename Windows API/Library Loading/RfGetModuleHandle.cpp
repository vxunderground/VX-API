HMODULE RfGetModuleHandleA(LPCSTR lpModuleName)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	CHAR wDllName[64] = { 0 };
	PLIST_ENTRY Head = &Peb->LoaderData->InMemoryOrderModuleList;
	PLIST_ENTRY Next = Head->Flink;
	Module = (PLDR_MODULE)((PBYTE)Next - 16);

	while (Next != Head)
	{
		Module = (PLDR_MODULE)((PBYTE)Next - 16);
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

	PLIST_ENTRY Head = &Peb->LoaderData->InMemoryOrderModuleList;
	PLIST_ENTRY Next = Head->Flink;
	Module = (PLDR_MODULE)((PBYTE)Next - 16);

	while (Next != Head)
	{
		Module = (PLDR_MODULE)((PBYTE)Next - 16);
		if (Module->BaseDllName.Buffer != NULL)
		{
			if (StringCompareW(lpModuleName, Module->BaseDllName.Buffer) == 0)
				return (HMODULE)Module->BaseAddress;
		}

		Next = Next->Flink;
	}

	return NULL;
}
