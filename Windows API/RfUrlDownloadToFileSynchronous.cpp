DWORD RfUrlDownloadToFileSynchronousW(PWCHAR Url, PWCHAR SavePath)
{
	typedef HRESULT(WINAPI* URLDOWNLOADFILE)(LPUNKNOWN, LPCTSTR, LPCTSTR, DWORD, LPBINDSTATUSCALLBACK);
	class DownloadProgressRoutine : public IBindStatusCallback {
	private:
		BOOL AbortOperation = FALSE;
		BOOL OperationCompleted = FALSE;
		DWORD dwFileSize = ERROR_SUCCESS;
	public:

		HRESULT __stdcall QueryInterface(const IID&, void**) { return E_NOINTERFACE; }
		ULONG STDMETHODCALLTYPE AddRef(void) { return 1; }
		ULONG STDMETHODCALLTYPE Release(void) { return 1; }
		HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG* pnPriority) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) { return S_OK; }
		virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk) { return E_NOTIMPL; }
		virtual BOOL STDMETHODCALLTYPE IsDownloadComplete(VOID)
		{
			return OperationCompleted;
		}
		virtual HRESULT STDMETHODCALLTYPE AbortDownload(VOID)
		{
			AbortOperation = TRUE;
			return E_NOTIMPL;
		}
		virtual DWORD STDMETHODCALLTYPE GetServerReportedFileSize(VOID)
		{
			return dwFileSize;
		}
		virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
		{
			if (ulProgress == ulProgressMax)
				OperationCompleted = TRUE;

			dwFileSize = ulProgressMax;

			if (AbortOperation)
				return E_ABORT;

			return S_OK;
		}
	};

	HRESULT Result = S_OK;
	DownloadProgressRoutine DownloadCallback;
	DWORD dwError = ERROR_SUCCESS;
	URLDOWNLOADFILE UrlDownloadToFileW = NULL;
	HMODULE Urlmon;
	BOOL bFlag = FALSE;

	Urlmon = LoadLibraryW(L"Urlmon.dll");
	if (Urlmon == NULL)
		goto EXIT_ROUTINE;

	UrlDownloadToFileW = (URLDOWNLOADFILE)RfGetProcAddressA((DWORD64)Urlmon, "URLDownloadToFileW");
	if (!UrlDownloadToFileW)
		goto EXIT_ROUTINE;

	Result = UrlDownloadToFileW(0, Url, SavePath, 0, (IBindStatusCallback*)(&DownloadCallback));
	if (Result != S_OK)
		goto EXIT_ROUTINE;

	while (!DownloadCallback.IsDownloadComplete())
	{
		Sleep(100);
	}

	dwError = RfGetFileSizeFromPathDisposeHandleW(SavePath, FILE_ATTRIBUTE_NORMAL);
	if (dwError == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	if (DownloadCallback.GetServerReportedFileSize() != dwError)
		goto EXIT_ROUTINE;

	bFlag = TRUE;
	dwError = ERROR_SUCCESS;

EXIT_ROUTINE:

	if (!bFlag)
	{
		if (Result != S_OK)
			dwError = EhWin32FromHResult(Result);
		else
			dwError = EhGetLastError();
	}

	if (Urlmon)
		FreeLibrary(Urlmon);

	return dwError;
}

DWORD RfUrlDownloadToFileSynchronousA(PCHAR Url, PCHAR SavePath)
{
	typedef HRESULT(WINAPI* URLDOWNLOADFILE)(LPUNKNOWN, LPCSTR, LPCSTR, DWORD, LPBINDSTATUSCALLBACK);
	class DownloadProgressRoutine : public IBindStatusCallback {
	private:
		BOOL AbortOperation = FALSE;
		BOOL OperationCompleted = FALSE;
		DWORD dwFileSize = ERROR_SUCCESS;
	public:

		HRESULT __stdcall QueryInterface(const IID&, void**) { return E_NOINTERFACE; }
		ULONG STDMETHODCALLTYPE AddRef(void) { return 1; }
		ULONG STDMETHODCALLTYPE Release(void) { return 1; }
		HRESULT STDMETHODCALLTYPE OnStartBinding(DWORD dwReserved, IBinding* pib) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE GetPriority(LONG* pnPriority) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE OnLowResource(DWORD reserved) { return S_OK; }
		virtual HRESULT STDMETHODCALLTYPE OnStopBinding(HRESULT hresult, LPCWSTR szError) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE GetBindInfo(DWORD* grfBINDF, BINDINFO* pbindinfo) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE OnDataAvailable(DWORD grfBSCF, DWORD dwSize, FORMATETC* pformatetc, STGMEDIUM* pstgmed) { return E_NOTIMPL; }
		virtual HRESULT STDMETHODCALLTYPE OnObjectAvailable(REFIID riid, IUnknown* punk) { return E_NOTIMPL; }
		virtual BOOL STDMETHODCALLTYPE IsDownloadComplete(VOID)
		{
			return OperationCompleted;
		}
		virtual HRESULT STDMETHODCALLTYPE AbortDownload(VOID)
		{
			AbortOperation = TRUE;
			return E_NOTIMPL;
		}
		virtual DWORD STDMETHODCALLTYPE GetServerReportedFileSize(VOID)
		{
			return dwFileSize;
		}
		virtual HRESULT __stdcall OnProgress(ULONG ulProgress, ULONG ulProgressMax, ULONG ulStatusCode, LPCWSTR szStatusText)
		{
			if (ulProgress == ulProgressMax)
				OperationCompleted = TRUE;

			dwFileSize = ulProgressMax;

			if (AbortOperation)
				return E_ABORT;

			return S_OK;
		}
	};

	HRESULT Result = S_OK;
	DownloadProgressRoutine DownloadCallback;
	DWORD dwError = ERROR_SUCCESS;
	URLDOWNLOADFILE UrlDownloadToFileA = NULL;
	HMODULE Urlmon;
	BOOL bFlag = FALSE;

	Urlmon = LoadLibraryW(L"Urlmon.dll");
	if (Urlmon == NULL)
		goto EXIT_ROUTINE;

	UrlDownloadToFileA = (URLDOWNLOADFILE)RfGetProcAddressA((DWORD64)Urlmon, "URLDownloadToFileA");
	if (!UrlDownloadToFileA)
		goto EXIT_ROUTINE;

	Result = UrlDownloadToFileA(0, Url, SavePath, 0, (IBindStatusCallback*)(&DownloadCallback));
	if (Result != S_OK)
		goto EXIT_ROUTINE;

	while (!DownloadCallback.IsDownloadComplete())
	{
		Sleep(100);
	}

	dwError = RfGetFileSizeFromPathDisposeHandleA(SavePath, FILE_ATTRIBUTE_NORMAL);
	if (dwError == INVALID_FILE_SIZE)
		goto EXIT_ROUTINE;

	if (DownloadCallback.GetServerReportedFileSize() != dwError)
		goto EXIT_ROUTINE;

	bFlag = TRUE;
	dwError = ERROR_SUCCESS;

EXIT_ROUTINE:

	if (!bFlag)
	{
		if (Result != S_OK)
			dwError = EhWin32FromHResult(Result);
		else
			dwError = EhGetLastError();
	}

	if (Urlmon)
		FreeLibrary(Urlmon);

	return dwError;
}
