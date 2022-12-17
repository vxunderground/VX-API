#include "Win32Helper.h"

DWORD CreateProcessByWindowsRHotKeyW(_In_ PWCHAR FullPathToBinary)
{
	INPUT ExecuteHotkey[4] = { 0 };
    INPUT BinaryInputBuffer[2] = { 0 };
    INPUT ExecuteBinaryCommand[2] = { 0 };
    UINT Result = ERROR_SUCCESS;
    HWND RunWindow = NULL;

	ExecuteHotkey[0].type = INPUT_KEYBOARD;
	ExecuteHotkey[0].ki.wVk = VK_LWIN;

    ExecuteHotkey[1].type = INPUT_KEYBOARD;
    ExecuteHotkey[1].ki.wVk = 0x52;

    ExecuteHotkey[2].type = INPUT_KEYBOARD;
    ExecuteHotkey[2].ki.wVk = 0x52;
    ExecuteHotkey[2].ki.dwFlags = KEYEVENTF_KEYUP;

    ExecuteHotkey[3].type = INPUT_KEYBOARD;
    ExecuteHotkey[3].ki.wVk = VK_LWIN;
    ExecuteHotkey[3].ki.dwFlags = KEYEVENTF_KEYUP;

    Result = SendInput(ARRAYSIZE(ExecuteHotkey), ExecuteHotkey, sizeof(INPUT));
    if (Result != ARRAYSIZE(ExecuteHotkey))
        return Win32FromHResult(Result);

    Sleep(100);

    RunWindow = FindWindowW(NULL, L"Run");
    if (RunWindow == NULL)
        return GetLastErrorFromTeb();

   if(!AttachThreadInput(GetCurrentThreadId(), GetWindowThreadProcessId(GetAncestor(RunWindow, GA_ROOT), NULL), TRUE))
       return GetLastErrorFromTeb();

    if(SetFocus(RunWindow) == NULL)
        return GetLastErrorFromTeb();

    for (DWORD dwX = 0; dwX < StringLengthW(FullPathToBinary); dwX++)
    {
        BinaryInputBuffer[0].type = INPUT_KEYBOARD;
        BinaryInputBuffer[0].ki.wVk = VkKeyScanW(FullPathToBinary[dwX]);

        BinaryInputBuffer[1].type = INPUT_KEYBOARD;
        BinaryInputBuffer[1].ki.wVk = VkKeyScanW(FullPathToBinary[dwX]);
        BinaryInputBuffer[1].ki.dwFlags = KEYEVENTF_KEYUP;

        Result = SendInput(ARRAYSIZE(BinaryInputBuffer), BinaryInputBuffer, sizeof(INPUT));
        if (Result != ARRAYSIZE(BinaryInputBuffer))
            return Win32FromHResult(Result);
    }

    ExecuteBinaryCommand[0].type = INPUT_KEYBOARD;
    ExecuteBinaryCommand[0].ki.wVk = 0x0D;

    ExecuteBinaryCommand[1].type = INPUT_KEYBOARD;
    ExecuteBinaryCommand[1].ki.wVk = 0x0D;
    ExecuteBinaryCommand[1].ki.dwFlags = KEYEVENTF_KEYUP;

    Result = SendInput(ARRAYSIZE(ExecuteBinaryCommand), ExecuteBinaryCommand, sizeof(INPUT));
    if (Result != ARRAYSIZE(ExecuteBinaryCommand))
        return Win32FromHResult(Result);
    
    return ERROR_SUCCESS;
}

DWORD CreateProcessByWindowsRHotKeyA(_In_ PCHAR FullPathToBinary)
{
    INPUT ExecuteHotkey[4] = { 0 };
    INPUT BinaryInputBuffer[2] = { 0 };
    INPUT ExecuteBinaryCommand[2] = { 0 };
    UINT Result = ERROR_SUCCESS;
    HWND RunWindow = NULL;

    ExecuteHotkey[0].type = INPUT_KEYBOARD;
    ExecuteHotkey[0].ki.wVk = VK_LWIN;

    ExecuteHotkey[1].type = INPUT_KEYBOARD;
    ExecuteHotkey[1].ki.wVk = 0x52;

    ExecuteHotkey[2].type = INPUT_KEYBOARD;
    ExecuteHotkey[2].ki.wVk = 0x52;
    ExecuteHotkey[2].ki.dwFlags = KEYEVENTF_KEYUP;

    ExecuteHotkey[3].type = INPUT_KEYBOARD;
    ExecuteHotkey[3].ki.wVk = VK_LWIN;
    ExecuteHotkey[3].ki.dwFlags = KEYEVENTF_KEYUP;

    Result = SendInput(ARRAYSIZE(ExecuteHotkey), ExecuteHotkey, sizeof(INPUT));
    if (Result != ARRAYSIZE(ExecuteHotkey))
        return Win32FromHResult(Result);

    Sleep(100);

    RunWindow = FindWindowW(NULL, L"Run");
    if (RunWindow == NULL)
        return GetLastErrorFromTeb();

    if (!AttachThreadInput(GetCurrentThreadId(), GetWindowThreadProcessId(GetAncestor(RunWindow, GA_ROOT), NULL), TRUE))
        return GetLastErrorFromTeb();

    if (SetFocus(RunWindow) == NULL)
        return GetLastErrorFromTeb();

    for (DWORD dwX = 0; dwX < StringLengthA(FullPathToBinary); dwX++)
    {
        BinaryInputBuffer[0].type = INPUT_KEYBOARD;
        BinaryInputBuffer[0].ki.wVk = VkKeyScanA(FullPathToBinary[dwX]);

        BinaryInputBuffer[1].type = INPUT_KEYBOARD;
        BinaryInputBuffer[1].ki.wVk = VkKeyScanA(FullPathToBinary[dwX]);
        BinaryInputBuffer[1].ki.dwFlags = KEYEVENTF_KEYUP;

        Result = SendInput(ARRAYSIZE(BinaryInputBuffer), BinaryInputBuffer, sizeof(INPUT));
        if (Result != ARRAYSIZE(BinaryInputBuffer))
            return Win32FromHResult(Result);
    }

    ExecuteBinaryCommand[0].type = INPUT_KEYBOARD;
    ExecuteBinaryCommand[0].ki.wVk = 0x0D;

    ExecuteBinaryCommand[1].type = INPUT_KEYBOARD;
    ExecuteBinaryCommand[1].ki.wVk = 0x0D;
    ExecuteBinaryCommand[1].ki.dwFlags = KEYEVENTF_KEYUP;

    Result = SendInput(ARRAYSIZE(ExecuteBinaryCommand), ExecuteBinaryCommand, sizeof(INPUT));
    if (Result != ARRAYSIZE(ExecuteBinaryCommand))
        return Win32FromHResult(Result);

    return ERROR_SUCCESS;
}