#include "Win32Helper.h"

BOOL IsDllLoadedW(_In_ LPCWSTR DllName)
{
	return (GetModuleHandleEx2W(DllName) == NULL ? FALSE : TRUE);
}

BOOL IsDllLoadedA(_In_ LPCSTR DllName)
{
	return (GetModuleHandleEx2A(DllName) == NULL ? FALSE : TRUE);
}