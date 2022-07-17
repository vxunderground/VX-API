DWORD OleGetClipboardDataA(PCHAR Buffer)
{
	DWORD dwError = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	IDataObject* DataObject = NULL;
	BOOL bFlag = FALSE;

	FORMATETC Format = { CF_TEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM Medium;
	LPCSTR Data = NULL;

	Result = OleGetClipboard(&DataObject);
	if (FAILED(Result))
		goto EXIT_ROUTINE;

	if (!DataObject)
		goto EXIT_ROUTINE;

	Result = DataObject->GetData(&Format, &Medium);
	if (FAILED(Result))
		goto EXIT_ROUTINE;

	if (Medium.hGlobal == NULL)
		goto EXIT_ROUTINE;

	Data = (LPCSTR)GlobalLock(Medium.hGlobal);
	if (Data == NULL)
		goto EXIT_ROUTINE;

	SecureStringCopyA(Buffer, Data, StringLengthA(Data));

EXIT_ROUTINE:

	if (!bFlag)
	{
		if (Result != S_OK)
			dwError = EhWin32FromHResult(Result);
		else
			dwError = EhGetLastError();
	}

#pragma warning( push )
#pragma warning( disable : 6001)
	if (Medium.hGlobal != NULL)
		GlobalUnlock(Medium.hGlobal);
#pragma warning( pop ) 

	if (DataObject)
		DataObject->Release();

	return dwError;
}

DWORD OleGetClipboardDataW(PWCHAR Buffer)
{
	DWORD dwError = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	IDataObject* DataObject = NULL;
	BOOL bFlag = FALSE;

	FORMATETC Format = { CF_TEXT, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	STGMEDIUM Medium;
	LPCSTR Data = NULL;

	Result = OleGetClipboard(&DataObject);
	if (FAILED(Result))
		goto EXIT_ROUTINE;

	if (!DataObject)
		goto EXIT_ROUTINE;

	Result = DataObject->GetData(&Format, &Medium);
	if (FAILED(Result))
		goto EXIT_ROUTINE;

	if (Medium.hGlobal == NULL)
		goto EXIT_ROUTINE;

	Data = (LPCSTR)GlobalLock(Medium.hGlobal);
	if (Data == NULL)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(Buffer, (PCHAR)Data, StringLengthA(Data)) == 0)
		goto EXIT_ROUTINE;

EXIT_ROUTINE:

	if (!bFlag)
	{
		if (Result != S_OK)
			dwError = EhWin32FromHResult(Result);
		else
			dwError = EhGetLastError();
	}

#pragma warning( push )
#pragma warning( disable : 6001)
	if (Medium.hGlobal != NULL)
		GlobalUnlock(Medium.hGlobal);
#pragma warning( pop ) 

	if (DataObject)
		DataObject->Release();

	return dwError;
}
