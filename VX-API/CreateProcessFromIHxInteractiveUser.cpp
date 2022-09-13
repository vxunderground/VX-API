#include "Win32Helper.h"

struct __declspec(uuid("8cec595b-07a1-11d9-b15e-000d56bfe6ee"))
	IHxInteractiveUser : public IUnknown {
	virtual VOID __stdcall Execute(PWCHAR pcUrl) = 0;
};

HRESULT CoInitializeIHxInteractiveUserIds(LPGUID Clsid, LPGUID Iid)
{
	HRESULT Result = S_OK;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec58e7-07a1-11d9-b15e-000d56bfe6ee}", Clsid)))
		return Result;

	if (!SUCCEEDED(Result = CLSIDFromString(L"{8cec595b-07a1-11d9-b15e-000d56bfe6ee}", Iid)))
		return Result;

	return Result;
}

HRESULT CreateProcessFromIHxInteractiveUserW(_In_ PWCHAR UriFile)
{
	HRESULT Result = S_OK;
	GUID CLSID_IHxInteractiveUser;
	GUID IID_IHxInteractiveUser;
	IHxInteractiveUser* User = NULL;

	if (!SUCCEEDED(Result = CoInitializeIHxInteractiveUserIds(&CLSID_IHxInteractiveUser, &IID_IHxInteractiveUser)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(Result = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(Result = CoCreateInstance(CLSID_IHxInteractiveUser, NULL, CLSCTX_ALL, IID_IHxInteractiveUser, (PVOID*)&User)))
		return Win32FromHResult(Result);

	User->Execute(UriFile);

	if (User)
		User->Release();

	CoUninitialize();

	return Win32FromHResult(Result);
}

HRESULT CreateProcessFromIHxInteractiveUserA(_In_ PCHAR UriFile)
{
	HRESULT Result = S_OK;
	GUID CLSID_IHxInteractiveUser;
	GUID IID_IHxInteractiveUser;
	IHxInteractiveUser* User = NULL;
	PWCHAR wUriFile = NULL;
	DWORD dwLength = 0;

	if (!SUCCEEDED(Result = CoInitializeIHxInteractiveUserIds(&CLSID_IHxInteractiveUser, &IID_IHxInteractiveUser)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(Result = CoInitializeEx(NULL, COINIT_MULTITHREADED)))
		return Win32FromHResult(Result);

	if (!SUCCEEDED(Result = CoCreateInstance(CLSID_IHxInteractiveUser, NULL, CLSCTX_ALL, IID_IHxInteractiveUser, (PVOID*)&User)))
		return Win32FromHResult(Result);

	dwLength = (DWORD)StringLengthA(UriFile);
	if (dwLength == 0)
		goto EXIT_ROUTINE;

	wUriFile = (PWCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwLength);
	if(wUriFile == NULL)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(wUriFile, UriFile, dwLength) == 0)
		goto EXIT_ROUTINE;

	User->Execute(wUriFile);

EXIT_ROUTINE:

	if (User)
		User->Release();

	if (wUriFile)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, wUriFile);

	CoUninitialize();

	return Win32FromHResult(Result);
}