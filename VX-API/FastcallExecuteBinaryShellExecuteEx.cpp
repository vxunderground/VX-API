#include "Win32Helper.h"

BOOL FastcallExecuteBinaryShellExecuteExW(_In_ PWCHAR FullPathToBinary, _In_ PWCHAR OptionalParameters)
{
	SHELLEXECUTEINFOW Execute = { 0 };

	Execute.cbSize = sizeof(SHELLEXECUTEINFOW);
	Execute.lpVerb = L"open";
	Execute.nShow = SW_SHOW;

	if (!FullPathToBinary)
		return FALSE;

	Execute.lpFile = FullPathToBinary;

	if (OptionalParameters)
		Execute.lpParameters = OptionalParameters;

	return ShellExecuteExW(&Execute);
}

BOOL FastcallExecuteBinaryShellExecuteExA(_In_ PCHAR FullPathToBinary, _In_ PCHAR OptionalParameters)
{
	SHELLEXECUTEINFOA Execute = { 0 };

	Execute.cbSize = sizeof(SHELLEXECUTEINFOW);
	Execute.lpVerb = "open";
	Execute.nShow = SW_SHOW;

	if (!FullPathToBinary)
		return FALSE;

	Execute.lpFile = FullPathToBinary;

	if (OptionalParameters)
		Execute.lpParameters = OptionalParameters;

	return ShellExecuteExA(&Execute);
}