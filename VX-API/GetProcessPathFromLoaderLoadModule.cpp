#include "Win32Helper.h"

DWORD GetProcessPathFromLoaderLoadModuleA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	if (nBufferLength < Module->FullDllName.Length)
		return 0;

	return (DWORD)WCharStringToCharString(lpBuffer, Module->FullDllName.Buffer, Module->FullDllName.MaximumLength);
}

DWORD GetProcessPathFromLoaderLoadModuleW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer)
{
	PPEB Peb = GetPeb();
	PLDR_MODULE Module = NULL;
	Module = (PLDR_MODULE)((PBYTE)Peb->LoaderData->InMemoryOrderModuleList.Flink - 16);

	if (nBufferLength < Module->FullDllName.Length)
		return 0;

	if (StringCopyW(lpBuffer, Module->FullDllName.Buffer) == NULL)
		return 0;

	return Module->FullDllName.Length;
}