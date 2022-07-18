/*
If the desktop icons are visible, makes them invisible
If the desktop icons are invisible, makes them visible
*/

DWORD UnusedSubroutineInterfaceQueryDesktopView(REFIID Riid, PVOID* Pp)
{
	DWORD dwError = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	IShellWindows* ShellWindows = NULL;
	IShellBrowser* Browser = NULL;
	IShellView* View = NULL;
	CComVariant Desktop(CSIDL_DESKTOP); //initialize
	CComVariant IDisposeObject;
	IDispatch* Dispatch = NULL;
	IServiceProvider* Provider = NULL;

	Result = CoCreateInstance(CLSID_ShellWindows, NULL, CLSCTX_ALL, IID_IShellWindows, (VOID**)(&ShellWindows));
	if (!SUCCEEDED(Result))
		return EhWin32FromHResult(Result);

	dwError = 0;
	Result = ShellWindows->FindWindowSW(&Desktop, &IDisposeObject, SWC_DESKTOP, (PLONG)&dwError, SWFO_NEEDDISPATCH, &Dispatch);
	if (!SUCCEEDED(Result))
		goto FAILURE;
	else
		dwError = ERROR_SUCCESS;

	Result = Dispatch->QueryInterface(IID_IServiceProvider, (VOID**)&Provider);
	if (!SUCCEEDED(Result))
		goto FAILURE;

	Result = Provider->QueryService(SID_STopLevelBrowser, IID_PPV_ARGS(&Browser));
	if (!SUCCEEDED(Result))
		goto FAILURE;

	Result = Browser->QueryActiveShellView(&View);
	if (!SUCCEEDED(Result))
		goto FAILURE;

	Result = View->QueryInterface(Riid, Pp);
	if (!SUCCEEDED(Result))
		goto FAILURE;

	if (Provider)
		Provider->Release();

	if (Browser)
		Browser->Release();

	if (View)
		View->Release();

	if (ShellWindows)
		ShellWindows->Release();

	return ERROR_SUCCESS;

FAILURE:

	dwError = EhWin32FromHResult(Result);

	if (Provider)
		Provider->Release();

	if (Browser)
		Browser->Release();

	if (View)
		View->Release();

	if (ShellWindows)
		ShellWindows->Release();

	return dwError;
}

BOOL MpfComHideDesktopIconsToggle(VOID)
{
	DWORD dwError = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	IFolderView2* FolderView2 = NULL;

	if (CoInitialize(NULL) != S_OK)
		goto EXIT_ROUTINE;

	dwError = UnusedSubroutineInterfaceQueryDesktopView(IID_PPV_ARGS(&FolderView2));
	if (dwError != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	dwError = 0;
	Result = FolderView2->GetCurrentFolderFlags(&dwError);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = FolderView2->SetCurrentFolderFlags(FWF_NOICONS, dwError ^ FWF_NOICONS);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (FolderView2)
		FolderView2->Release();

	CoUninitialize();

	return ERROR_SUCCESS;

EXIT_ROUTINE:

	dwError = EhWin32FromHResult(Result);

	if (FolderView2)
		FolderView2->Release();

	CoUninitialize();

	return dwError;
}
