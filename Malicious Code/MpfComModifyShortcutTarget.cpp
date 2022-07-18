/*
LnkPath = L"C:\\Users\\User1\\Desktop\\Chrome.exe.lnk" <--- MUST BE .LNK!
NewValue = L"C:\\Windows\\System32\\calc.exe"

Chrome.exe.lnk on desktop now launches calc.exe
*/

BOOL MpfComModifyShortcutTargetW(PWCHAR LnkPath, PWCHAR NewValue)
{
	HRESULT Result = S_OK;
	IShellLinkW* Shell = NULL;
	IPersistFile* Persist = NULL;
	BOOL bFlag = FALSE;
	WIN32_FIND_DATAW Dispose = {0};
	WCHAR PathData[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CoInitialize(NULL) != S_OK)
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (VOID**)(&Shell));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Shell->QueryInterface(IID_IPersistFile, (VOID**)&Persist);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (Persist->Load(LnkPath, STGM_READ) != S_OK)
		goto EXIT_ROUTINE;

#pragma warning(push)
#pragma warning(disable: 6001)
	if (Shell->GetPath(PathData, (MAX_PATH * sizeof(WCHAR)), (WIN32_FIND_DATAW*)&Dispose, SLGP_SHORTPATH) != S_OK)
		goto EXIT_ROUTINE;
#pragma warning(pop)

	if (Shell->SetPath(NewValue) != S_OK)
		goto EXIT_ROUTINE;

	if (Persist->Save(LnkPath, FALSE) != S_OK)
		goto EXIT_ROUTINE;

	if (Shell->Resolve(NULL, SLR_ANY_MATCH) != S_OK)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (Persist)
		Persist->Release();

	if (Shell)
		Shell->Release();

	CoUninitialize();

	return bFlag;
}

BOOL MpfComModifyShortcutTargetA(PCHAR LnkPath, PCHAR NewValue)
{
	HRESULT Result = S_OK;
	IShellLinkW* Shell = NULL;
	IPersistFile* Persist = NULL;
	BOOL bFlag = FALSE;
	WIN32_FIND_DATAW Dispose = { 0 };
	WCHAR PathData[MAX_PATH * sizeof(WCHAR)] = { 0 };

	WCHAR lpwLnkPath[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR lpwNewValue[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(lpwLnkPath, LnkPath, StringLengthA(LnkPath)) == 0)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(lpwNewValue, NewValue, StringLengthA(NewValue)) == 0)
		goto EXIT_ROUTINE;

	if (CoInitialize(NULL) != S_OK)
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_ShellLink, NULL, CLSCTX_INPROC_SERVER, IID_IShellLink, (VOID**)(&Shell));
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Shell->QueryInterface(IID_IPersistFile, (VOID**)&Persist);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (Persist->Load(lpwLnkPath, STGM_READ) != S_OK)
		goto EXIT_ROUTINE;

#pragma warning(push)
#pragma warning(disable: 6001)
	if (Shell->GetPath(PathData, (MAX_PATH * sizeof(WCHAR)), (WIN32_FIND_DATAW*)&Dispose, SLGP_SHORTPATH) != S_OK)
		goto EXIT_ROUTINE;
#pragma warning(pop)

	if (Shell->SetPath(lpwNewValue) != S_OK)
		goto EXIT_ROUTINE;

	if (Persist->Save(lpwLnkPath, FALSE) != S_OK)
		goto EXIT_ROUTINE;

	if (Shell->Resolve(NULL, SLR_ANY_MATCH) != S_OK)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (Persist)
		Persist->Release();

	if (Shell)
		Shell->Release();

	CoUninitialize();

	return bFlag;
}
