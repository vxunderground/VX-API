#include "Win32Helper.h"

DWORD CreateProcessByWindowsRHotKeyExW(_In_ PWCHAR FullPathToBinary)
{
    HWND RunWindow = NULL;
    HWND EditWindow = NULL;
    HWND TopWindowForChildElement = NULL;
    INPUT ExecuteHotkey[4] = { 0 };
    UINT Result = ERROR_SUCCESS;

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

    TopWindowForChildElement = FindWindowExW(RunWindow, NULL, L"ComboBox", NULL);
    if (TopWindowForChildElement == NULL)
        return GetLastErrorFromTeb();

    EditWindow = FindWindowExW(TopWindowForChildElement, NULL, L"Edit", NULL);
    if (EditWindow == NULL)
        return GetLastErrorFromTeb();

    if (SetFocus(RunWindow) == NULL)
        return GetLastErrorFromTeb();

    for (DWORD dwX = 0; dwX < StringLengthW(FullPathToBinary); dwX++)
    {
        PostMessageW(EditWindow, WM_CHAR, (WCHAR)FullPathToBinary[dwX], 0);
    }

    PostMessageW(RunWindow, WM_KEYDOWN, VK_RETURN, NULL);

    return ERROR_SUCCESS;
}

DWORD CreateProcessByWindowsRHotKeyExA(_In_ PCHAR FullPathToBinary)
{
    HWND RunWindow = NULL;
    HWND EditWindow = NULL;
    HWND TopWindowForChildElement = NULL;
    INPUT ExecuteHotkey[4] = { 0 };
    UINT Result = ERROR_SUCCESS;

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

    TopWindowForChildElement = FindWindowExA(RunWindow, NULL, "ComboBox", NULL);
    if (TopWindowForChildElement == NULL)
        return GetLastErrorFromTeb();

    EditWindow = FindWindowExA(TopWindowForChildElement, NULL, "Edit", NULL);
    if (EditWindow == NULL)
        return GetLastErrorFromTeb();

    if (SetFocus(RunWindow) == NULL)
        return GetLastErrorFromTeb();

    for (DWORD dwX = 0; dwX < StringLengthA(FullPathToBinary); dwX++)
    {
        PostMessageA(EditWindow, WM_CHAR, (CHAR)FullPathToBinary[dwX], 0);
    }

    PostMessageW(RunWindow, WM_KEYDOWN, VK_RETURN, NULL);

    return ERROR_SUCCESS;
}