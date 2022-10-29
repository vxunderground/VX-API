#include "Win32Helper.h"

const static GUID IClassFactorClsid = { 0x13709620, 0xc279, 0x11ce, { 0xa4, 0x9e, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00 } };

DWORD CreateProcessFromIShellDispatchInvokeW(_In_ PWCHAR BinaryPath)
{
	HRESULT Result = S_OK;
	HMODULE hModule = NULL;
	DLLGETCLASSOBJECT DllGetClassObject = NULL;
	IClassFactory* ClassFactory = NULL;
	IDispatch* Dispatch = NULL;
	DISPID Id = 0;
	VARIANT Variant = { VT_EMPTY };
	VARIANT Output = { VT_EMPTY };
	DISPPARAMS DispatchParameters;
	LPOLESTR MemberString = (PWCHAR)L"ShellExecute";

	hModule = TryLoadDllMultiMethodW((PWCHAR)L"Shell32.dll");
	if (hModule == NULL)
		return GetLastErrorFromTeb();

	DllGetClassObject = (DLLGETCLASSOBJECT)GetProcAddressA((DWORD64)hModule, "DllGetClassObject");
	if (DllGetClassObject == NULL)
	{
		Result = E_FAIL; goto EXIT_ROUTINE;
	}

	Result = CoInitialize(NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = DllGetClassObject(IClassFactorClsid, IID_IClassFactory, (PVOID*)&ClassFactory);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = ClassFactory->CreateInstance(NULL, IID_IDispatch, (PVOID*)&Dispatch);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Dispatch->GetIDsOfNames(IID_NULL, &MemberString, 1, LOCALE_USER_DEFAULT, &Id);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Variant.vt = VT_BSTR;
	Variant.bstrVal = SysAllocString(BinaryPath);
	DispatchParameters.rgvarg = &Variant;
	DispatchParameters.rgdispidNamedArgs = NULL;
	DispatchParameters.cArgs = 1;
	DispatchParameters.cNamedArgs = 0;

	Result = Dispatch->Invoke(Id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &DispatchParameters, &Output, NULL, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (Dispatch)
		Dispatch->Release();

	if (ClassFactory)
		ClassFactory->Release();

	if (Variant.bstrVal)
		SysFreeString(Variant.bstrVal);

	CoUninitialize();

	return Win32FromHResult(Result);
}

DWORD CreateProcessFromIShellDispatchInvokeA(_In_ PCHAR BinaryPath)
{
	HRESULT Result = S_OK;
	HMODULE hModule = NULL;
	DLLGETCLASSOBJECT DllGetClassObject = NULL;
	IClassFactory* ClassFactory = NULL;
	IDispatch* Dispatch = NULL;
	DISPID Id = 0;
	VARIANT Variant = { VT_EMPTY };
	VARIANT Output = { VT_EMPTY };
	DISPPARAMS DispatchParameters;
	LPOLESTR MemberString = (PWCHAR)L"ShellExecute";
	WCHAR wBinaryPath[MAX_PATH * sizeof(WCHAR)] = { 0 };

	CharStringToWCharString(wBinaryPath, BinaryPath, StringLengthA(BinaryPath));

	hModule = LoadLibraryW(L"Shell32.dll");
	if (hModule == NULL)
		return GetLastErrorFromTeb();

	DllGetClassObject = (DLLGETCLASSOBJECT)GetProcAddressA((DWORD64)hModule, "DllGetClassObject");
	if (DllGetClassObject == NULL)
	{
		Result = E_FAIL; goto EXIT_ROUTINE;
	}

	Result = CoInitialize(NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = DllGetClassObject(IClassFactorClsid, IID_IClassFactory, (PVOID*)&ClassFactory);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = ClassFactory->CreateInstance(NULL, IID_IDispatch, (PVOID*)&Dispatch);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Dispatch->GetIDsOfNames(IID_NULL, &MemberString, 1, LOCALE_USER_DEFAULT, &Id);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Variant.vt = VT_BSTR;
	Variant.bstrVal = SysAllocString(wBinaryPath);
	DispatchParameters.rgvarg = &Variant;
	DispatchParameters.rgdispidNamedArgs = NULL;
	DispatchParameters.cArgs = 1;
	DispatchParameters.cNamedArgs = 0;

	Result = Dispatch->Invoke(Id, IID_NULL, LOCALE_USER_DEFAULT, DISPATCH_METHOD, &DispatchParameters, &Output, NULL, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (Dispatch)
		Dispatch->Release();

	if (ClassFactory)
		ClassFactory->Release();

	if (Variant.bstrVal)
		SysFreeString(Variant.bstrVal);

	CoUninitialize();

	return Win32FromHResult(Result);
}