#include "Win32Helper.h"
#include <AtlBase.h>
#include <AtlCom.h>
#include <UIAutomation.h>



class EventHandler : public IUIAutomationFocusChangedEventHandler
{
private:
	LONG ReferenceIndex;
public:
	INT EventIndex;
	IUIAutomationElement* Pane = NULL;
	IUIAutomationCondition* UrlContext = NULL;

	EventHandler() : ReferenceIndex(1), EventIndex(0)
	{
	}

	ULONG STDMETHODCALLTYPE AddRef()
	{
		return InterlockedIncrement(&ReferenceIndex);
	}

	ULONG STDMETHODCALLTYPE Release()
	{
		ULONG Result = InterlockedDecrement(&ReferenceIndex);
		if (Result != ERROR_SUCCESS)
			return Result;

		if (Pane)
			Pane->Release();

		if (UrlContext)
			UrlContext->Release();

		delete this;
		return Result;
	}

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID Riid, PVOID* Interface)
	{
		if (Riid == __uuidof(IUnknown))
			*Interface = (IUIAutomationFocusChangedEventHandler*)(this);
		else if (Riid == __uuidof(IUIAutomationFocusChangedEventHandler))
			*Interface = (IUIAutomationFocusChangedEventHandler*)(this);
		else
		{
			*Interface = NULL;
			return E_NOINTERFACE;
		}
		this->AddRef();
		return S_OK;
	}

	HRESULT STDMETHODCALLTYPE HandleFocusChangedEvent(IUIAutomationElement* pSender)
	{
		HRESULT Result;
		IUIAutomationElement* Url = NULL;
		IValueProvider* Provider = NULL;
		CComVariant Variant;

		EventIndex++;

		Result = Pane->FindFirst(TreeScope_Descendants, UrlContext, &Url);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		if(Url == NULL)
			goto EXIT_ROUTINE;

		Result = Url->GetCurrentPropertyValue(UIA_ValueValuePropertyId, &Variant);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		if (!Variant.bstrVal)
			goto EXIT_ROUTINE;

		/*
		 
		
		
		1. Gets the current URL
		Result = Url->GetCurrentPattern(UIA_ValuePatternId, (IUnknown**)&Provider);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;
			
		
		2. Modify the URL to whatever you'd like
		Provider->SetValue(L"google.com");

		3. Send ENTER key to change URL
		INPUT Input[2] = { INPUT_KEYBOARD };
		Input[0].ki.wVk = VK_RETURN;
		Input[1] = Input[0];
		Input[1].ki.dwFlags |= KEYEVENTF_KEYUP;
		SendInput(2, Input, sizeof(INPUT));
	
			
		OR write to a file?:)	
			
		*/

		wprintf(L"Url: %ws\r\n", Variant.bstrVal);

	EXIT_ROUTINE:

		if (Url)
			Url->Release();

		if (Provider)
			Provider->Release();

		return S_OK;
	}
};

DWORD MpfComMonitorChromeSessionOnce(VOID)
{
	HWND hChrome = NULL;
	DWORD dwError = ERROR_SUCCESS;
	INT Length = 0;
	BOOL bFlag = FALSE, bHandlerPresent = FALSE;
	HRESULT Result = ERROR_SUCCESS;
	IUIAutomation *Automaton = NULL;
	IUIAutomationElement* Element = NULL;
	IUIAutomationCondition* Condition = NULL;
	IUIAutomationElementArray* Array = NULL;
	EventHandler *EventHandlerObject = NULL;

	EventHandlerObject = new EventHandler();
	if (!EventHandlerObject)
		return -1;

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

	Result = Automaton->ElementFromHandle(hChrome, &Element);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Automaton->CreatePropertyCondition(UIA_ControlTypePropertyId, CComVariant(UIA_PaneControlTypeId), &Condition);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Element->FindAll(TreeScope_Children, Condition, &Array);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Array->get_Length(&Length);
	for (INT i = 0; i < Length; i++)
	{
		CComBSTR NameObject;

		Result = Array->GetElement(i, &EventHandlerObject->Pane);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		EventHandlerObject->Pane->get_CurrentName(&NameObject);
		if (!SUCCEEDED(Result))
			goto EXIT_ROUTINE;

		if (StringCompareW(NameObject, L"Google Chrome") == ERROR_SUCCESS)
			break;

		EventHandlerObject->Pane->Release();
	}

	if (EventHandlerObject->Pane == NULL)
		goto EXIT_ROUTINE;

	Result = Automaton->CreatePropertyCondition(UIA_ControlTypePropertyId, CComVariant(UIA_EditControlTypeId), &EventHandlerObject->UrlContext);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Automaton->AddFocusChangedEventHandler(NULL, (IUIAutomationFocusChangedEventHandler*)EventHandlerObject);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;
	else
		bHandlerPresent = TRUE;

	for (;;) { Sleep(10); } //let event handler work

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = GetLastErrorFromTeb();

	if (Element)
		Element->Release();

	if (Array)
		Array->Release();

	if (Condition)
		Condition->Release();

	if(bHandlerPresent)
		Automaton->RemoveFocusChangedEventHandler((IUIAutomationFocusChangedEventHandler*)EventHandlerObject);

	if (Automaton)
		Automaton->Release();

	if (EventHandlerObject)
		EventHandlerObject->Release();

	CoUninitialize();

	return dwError;
}
