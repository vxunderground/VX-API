#include "Win32Helper.h"

struct __declspec(uuid("{8cec592c-07a1-11d9-b15e-000d56bfe6ee}"))
	IHxHelpPaneServer : public IUnknown {
	virtual HRESULT __stdcall DisplayTask(PWCHAR) = 0;
	virtual HRESULT __stdcall DisplayContents(PWCHAR) = 0;
	virtual HRESULT __stdcall DisplaySearchResults(PWCHAR) = 0;
	virtual HRESULT __stdcall Execute(const PWCHAR) = 0;
};

HRESULT CoInitializeIHxHelpIds(LPGUID Clsid, LPGUID Iid)
{
	HRESULT Result = S_OK;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec58ae-07a1-11d9-b15e-000d56bfe6ee}", Clsid)))
		return Result;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec592c-07a1-11d9-b15e-000d56bfe6ee}", Iid)))
		return Result;

	return Result;
}

HRESULT CreateProcessFromIHxHelpPaneServerW(_In_ PWCHAR UriFile)
{
	HRESULT Result = S_OK;
	GUID CLSID_IHxHelpPaneServer;
	GUID IID_IHxHelpPaneServer;

	IHxHelpPaneServer* Help = NULL;

	if (!SUCCEEDED(Result = CoInitializeIHxHelpIds(&CLSID_IHxHelpPaneServer, &IID_IHxHelpPaneServer)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(Result = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(CoCreateInstance(CLSID_IHxHelpPaneServer, NULL, CLSCTX_ALL, IID_IHxHelpPaneServer, (PVOID*)&Help)))
		return Win32FromHResult(Result);

	Result = Help->Execute(UriFile);

	if (Help)
		Help->Release();

	CoUninitialize();

	return Win32FromHResult(Result);
}

HRESULT CreateProcessFromIHxHelpPaneServerA(_In_ PCHAR UriFile)
{
	HRESULT Result = S_OK;
	GUID CLSID_IHxHelpPaneServer;
	GUID IID_IHxHelpPaneServer;
	IHxHelpPaneServer* Help = NULL;
	PWCHAR wUriFile = NULL;
	DWORD dwLength = 0;

	if (!SUCCEEDED(Result = CoInitializeIHxHelpIds(&CLSID_IHxHelpPaneServer, &IID_IHxHelpPaneServer)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(Result = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(CoCreateInstance(CLSID_IHxHelpPaneServer, NULL, CLSCTX_ALL, IID_IHxHelpPaneServer, (PVOID*)&Help)))
		return Win32FromHResult(Result);

	dwLength = (DWORD)StringLengthA(UriFile);
	if (dwLength == 0)
		goto EXIT_ROUTINE;

	wUriFile = (PWCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwLength);
	if (wUriFile == NULL)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(wUriFile, UriFile, dwLength) == 0)
		goto EXIT_ROUTINE;

	Result = Help->Execute(wUriFile);

EXIT_ROUTINE:

	if (Help)
		Help->Release();

	if (wUriFile)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, wUriFile);

	CoUninitialize();

	return Win32FromHResult(Result);

}