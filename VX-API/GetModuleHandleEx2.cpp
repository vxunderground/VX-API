#include "Win32Helper.h"

HMODULE GetModuleHandleEx2A(_In_ LPCSTR lpModuleName)
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
			ZeroMemoryEx(wDllName, sizeof(wDllName));
			WCharStringToCharString(wDllName, Module->BaseDllName.Buffer, 64);

			CHAR InitialModuleName[256] = { 0 };
			CHAR IdentifiedModuleName[256] = { 0 };

			if (StringCopyA(InitialModuleName, (PCHAR)lpModuleName) == NULL)
				return NULL;

			if (StringCopyA(IdentifiedModuleName, wDllName) == NULL)
				return NULL;

			PCHAR ComparisonObject1 = CaplockStringA(InitialModuleName);
			PCHAR ComparisonObject2 = CaplockStringA(IdentifiedModuleName);


			if (StringCompareA(ComparisonObject1, ComparisonObject2) == 0)
				return (HMODULE)Module->BaseAddress;
		}

		Next = Next->Flink;
	}

	return NULL;
}

HMODULE GetModuleHandleEx2W(_In_ LPCWSTR lpModuleName)
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
			WCHAR InitialModuleName[256] = { 0 };
			WCHAR IdentifiedModuleName[256] = { 0 };

			if (StringCopyW(InitialModuleName, (PWCHAR)lpModuleName) == NULL)
				return NULL;

			if (StringCopyW(IdentifiedModuleName, Module->BaseDllName.Buffer) == NULL)
				return NULL;

			PWCHAR ComparisonObject1 = CaplockStringW(InitialModuleName);
			PWCHAR ComparisonObject2 = CaplockStringW(IdentifiedModuleName);

			if (StringCompareW(ComparisonObject1, ComparisonObject2) == 0)
				return (HMODULE)Module->BaseAddress;
		}

		Next = Next->Flink;
	}

	return NULL;
}
