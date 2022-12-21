#include "Win32Helper.h"

//Microsoft doesn't natively support password protected ZIP files. Hahahaha

BOOL MpfExtractMaliciousPayloadFromZipFileNoPasswordW(_In_ PWCHAR FullPathToZip, _In_ PWCHAR FullPathToExtractionDirectory)
{
	IDispatch* Items = 0;
	IShellDispatch* Dispatch = 0L;
	Folder* ZippedFile = 0L;
	Folder* Destination = 0L;
	FolderItems* FilesInside = 0L;
	LONG NumberOfFiles = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	VARIANT Options, OutFolder, InZipFile, Item;
	BOOL bFlag = FALSE;

	if (!SUCCEEDED(Result = CoInitialize(NULL)))
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_IShellDispatch, (PVOID*)&Dispatch);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	InZipFile.vt = VT_BSTR;
	InZipFile.bstrVal = FullPathToZip;

	Result = Dispatch->NameSpace(InZipFile, &ZippedFile);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	OutFolder.vt = VT_BSTR;
	OutFolder.bstrVal = FullPathToExtractionDirectory;

	Result = Dispatch->NameSpace(OutFolder, &Destination);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = ZippedFile->Items(&FilesInside);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = FilesInside->get_Count(&NumberOfFiles);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (NumberOfFiles < 1)
		goto EXIT_ROUTINE;

	Result = FilesInside->QueryInterface(IID_IDispatch, (PVOID*)&Items);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Item.vt = VT_DISPATCH;
	Item.pdispVal = Items;
	Options.vt = VT_I4;
	Options.lVal = 1024 | 512 | 16 | 4;

	Result = Destination->CopyHere(Item, Options);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if(Items)
		Items->Release();

	if(FilesInside)
		FilesInside->Release();

	if(Destination)
		Destination->Release();

	if(ZippedFile)
		ZippedFile->Release();

	if (Dispatch)
		Dispatch->Release();

	CoUninitialize();

	return bFlag;
}

BOOL MpfExtractMaliciousPayloadFromZipFileNoPasswordA(_In_ PCHAR FullPathToZip, _In_ PCHAR FullPathToExtractionDirectory)
{
	IDispatch* Items = 0;
	IShellDispatch* Dispatch = 0L;
	Folder* ZippedFile = 0L;
	Folder* Destination = 0L;
	FolderItems* FilesInside = 0L;
	LONG NumberOfFiles = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	VARIANT Options, OutFolder, InZipFile, Item;
	BOOL bFlag = FALSE;

	WCHAR Source[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR CopyDestination[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(Source, FullPathToZip, MAX_PATH * sizeof(WCHAR)) == 0)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(CopyDestination, FullPathToExtractionDirectory, MAX_PATH * sizeof(WCHAR)) == 0)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(Result = CoInitialize(NULL)))
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_Shell, NULL, CLSCTX_INPROC_SERVER, IID_IShellDispatch, (PVOID*)&Dispatch);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	InZipFile.vt = VT_BSTR;
	InZipFile.bstrVal = Source;

	Result = Dispatch->NameSpace(InZipFile, &ZippedFile);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	OutFolder.vt = VT_BSTR;
	OutFolder.bstrVal = CopyDestination;

	Result = Dispatch->NameSpace(OutFolder, &Destination);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = ZippedFile->Items(&FilesInside);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = FilesInside->get_Count(&NumberOfFiles);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (NumberOfFiles < 1)
		goto EXIT_ROUTINE;

	Result = FilesInside->QueryInterface(IID_IDispatch, (PVOID*)&Items);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Item.vt = VT_DISPATCH;
	Item.pdispVal = Items;
	Options.vt = VT_I4;
	Options.lVal = 1024 | 512 | 16 | 4;

	Result = Destination->CopyHere(Item, Options);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (Items)
		Items->Release();

	if (FilesInside)
		FilesInside->Release();

	if (Destination)
		Destination->Release();

	if (ZippedFile)
		ZippedFile->Release();

	if (Dispatch)
		Dispatch->Release();

	CoUninitialize();

	return bFlag;
}