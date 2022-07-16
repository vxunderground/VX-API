/*
Paper: Finding Interactive User COM Objects using PowerShell

Credit: James Forshaw
*/

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

HRESULT CreateProcessFromIHxHelpPaneServerW(PWCHAR UriFile)
{
	HRESULT Result = S_OK;
	GUID CLSID_IHxHelpPaneServer;
	GUID IID_IHxHelpPaneServer;

	IHxHelpPaneServer* Help = NULL;

	if (!SUCCEEDED(Result = CoInitializeIHxHelpIds(&CLSID_IHxHelpPaneServer, &IID_IHxHelpPaneServer)))
		return EhWin32FromHResult(Result);

	if (!SUCCEEDED(Result = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return EhWin32FromHResult(Result);

	if (!SUCCEEDED(CoCreateInstance(CLSID_IHxHelpPaneServer, NULL, CLSCTX_ALL, IID_IHxHelpPaneServer, (PVOID*)&Help)))
		return EhWin32FromHResult(Result);

	Result = Help->Execute(UriFile);

	if (Help)
		Help->Release();

	CoUninitialize();

	return EhWin32FromHResult(Result);
}
