DWORD GetLinkedDllCount(VOID)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	DWORD dwIndexHash = 0;
	DWORD dwCount = 0;

	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	for (; TRUE; dwCount++)
	{
		Module = (PLDR_MODULE)((PBYTE)Module->InMemoryOrderModuleList.Flink - 16);
		if (Module->BaseDllName.Buffer == NULL)
			break;
	}

	return dwCount;
}
