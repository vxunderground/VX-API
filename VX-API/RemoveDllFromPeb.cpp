#include "Win32Helper.h"

VOID RemoveEntryList(LIST_ENTRY* Entry)
{
	if (Entry != NULL) {
		PLIST_ENTRY OldFlink;
		PLIST_ENTRY OldBlink;
		OldFlink = Entry->Flink;
		OldBlink = Entry->Blink;
		OldFlink->Blink = OldBlink;
		OldBlink->Flink = OldFlink;
		Entry->Flink = NULL;
		Entry->Blink = NULL;
	}
}

BOOL RemoveDllFromPebW(_In_ LPCWSTR lpModuleName) {
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
			{
				RemoveEntryList(&Module->InLoadOrderModuleList);
				RemoveEntryList(&Module->InInitializationOrderModuleList);
				RemoveEntryList(&Module->InMemoryOrderModuleList);
				RemoveEntryList(&Module->HashTableEntry);

				return TRUE;
			}
		}
		Next = Next->Flink;
	}

	return FALSE;
}

BOOL RemoveDllFromPebA(_In_ LPCSTR lpModuleName) {
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
			ZeroMemoryEx(wDllName, sizeof(wDllName));
			WCharStringToCharString(wDllName, Module->BaseDllName.Buffer, 64);
			if (StringCompareA(lpModuleName, wDllName) == 0)
			{
				RemoveEntryList(&Module->InLoadOrderModuleList);
				RemoveEntryList(&Module->InInitializationOrderModuleList);
				RemoveEntryList(&Module->InMemoryOrderModuleList);
				RemoveEntryList(&Module->HashTableEntry);

				return TRUE;
			}
		}
		Next = Next->Flink;
	}

	return FALSE;
}