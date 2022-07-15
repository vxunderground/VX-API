HRESULT CoInitializeIHxHelpIds(LPGUID Clsid, LPGUID Iid)
{
	HRESULT Result = S_OK;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec58ae-07a1-11d9-b15e-000d56bfe6ee}", Clsid)))
		return Result;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec592c-07a1-11d9-b15e-000d56bfe6ee}", Iid)))
		return Result;

	return Result;
}

HRESULT CoInitializeIHxInteractiveUserIds(LPGUID Clsid, LPGUID Iid)
{
	HRESULT Result = S_OK;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec58e7-07a1-11d9-b15e-000d56bfe6ee}", Clsid)))
		return Result;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec595b-07a1-11d9-b15e-000d56bfe6ee}", Iid)))
		return Result;

	return Result;
}

HRESULT CreateProcessFromIHxInteractiveUserW(PWCHAR UriFile)
{
	HRESULT Result = S_OK;
	GUID CLSID_IHxInteractiveUser;
	GUID IID_IHxInteractiveUser;
	IHxInteractiveUser* User = NULL;

	if(!SUCCEEDED(Result = CoInitializeIHxInteractiveUserIds(&CLSID_IHxInteractiveUser, &IID_IHxInteractiveUser)))
		return EhWin32FromHResult(Result);

	if (!SUCCEEDED(Result = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return EhWin32FromHResult(Result);

	if (!SUCCEEDED(Result = CoCreateInstance(CLSID_IHxInteractiveUser, NULL, CLSCTX_ALL, IID_IHxInteractiveUser, (PVOID*)&User)))
		return EhWin32FromHResult(Result);

	User->Execute(UriFile);

	if (User)
		User->Release();

	CoUninitialize();

	return EhWin32FromHResult(Result);
}
