#include "Win32Helper.h"
#include <comdef.h>
#include <Wbemidl.h>

#pragma comment(lib, "wbemuuid.lib")

DWORD GetPidFromWmiComInterfaceW(_In_ PWCHAR BinaryNameWithFileExtension)
{
	IWbemLocator* Locator = NULL;
	IWbemServices* Services = NULL;
	IEnumWbemClassObject* Enumerator = NULL;
	IWbemClassObject* Object = NULL;
	DWORD ProcessId = ERROR_SUCCESS;
	HRESULT Result = S_OK;

	Result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (!SUCCEEDED(Result))
		return 0;

	Result = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&Locator);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Locator->ConnectServer((BSTR)L"ROOT\\CIMV2", NULL, NULL, NULL, 0, NULL, NULL, &Services);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoSetProxyBlanket(Services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Services->ExecQuery((BSTR)L"WQL", (BSTR)L"SELECT * FROM Win32_Process", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &Enumerator);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	while (Enumerator)
	{
		if (ProcessId != ERROR_SUCCESS)
			break;

		ULONG uReturned = ERROR_SUCCESS;
		VARIANT ProcessData; VariantInit(&ProcessData);
		VARIANT VariantProcessId; VariantInit(&VariantProcessId);

		Result = Enumerator->Next(WBEM_INFINITE, 1, &Object, &uReturned);
		if (!SUCCEEDED(Result))
			continue;

		if (uReturned == 0)
			continue;

		Result = Object->Get(L"Name", 0, &ProcessData, NULL, NULL);
		if (SUCCEEDED(Result))
		{
			if (StringCompareW(BinaryNameWithFileExtension, V_BSTR(&ProcessData)) == ERROR_SUCCESS)
			{
				Result = Object->Get(L"ProcessId", 0, &VariantProcessId, NULL, NULL);
				if(SUCCEEDED(Result))
					ProcessId = V_UI4(&VariantProcessId);
			}
		}

		VariantClear(&ProcessData);
		VariantClear(&VariantProcessId);

		if (Object)
			Object->Release();
	}

EXIT_ROUTINE:

	if (Enumerator)
		Enumerator->Release();

	if (Services)
		Services->Release();

	if (Locator)
		Locator->Release();

	CoUninitialize();

	return (Result != S_OK ? Win32FromHResult(Result) : ProcessId);
}

DWORD GetPidFromWmiComInterfaceA(_In_ PCHAR BinaryNameWithFileExtension)
{
	IWbemLocator* Locator = NULL;
	IWbemServices* Services = NULL;
	IEnumWbemClassObject* Enumerator = NULL;
	IWbemClassObject* Object = NULL;
	DWORD ProcessId = ERROR_SUCCESS;
	HRESULT Result = S_OK;
	WCHAR BinaryNameWchar[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString(BinaryNameWchar, BinaryNameWithFileExtension, StringLengthA(BinaryNameWithFileExtension)) == 0)
		return 0;

	Result = CoInitializeEx(NULL, COINIT_MULTITHREADED);
	if (!SUCCEEDED(Result))
		return 0;

	Result = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_WbemLocator, NULL, CLSCTX_INPROC_SERVER, IID_IWbemLocator, (LPVOID*)&Locator);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Locator->ConnectServer((BSTR)L"ROOT\\CIMV2", NULL, NULL, NULL, 0, NULL, NULL, &Services);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoSetProxyBlanket(Services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Services->ExecQuery((BSTR)L"WQL", (BSTR)L"SELECT * FROM Win32_Process", WBEM_FLAG_FORWARD_ONLY | WBEM_FLAG_RETURN_IMMEDIATELY, NULL, &Enumerator);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	while (Enumerator)
	{
		if (ProcessId != ERROR_SUCCESS)
			break;

		ULONG uReturned = ERROR_SUCCESS;
		VARIANT ProcessData; VariantInit(&ProcessData);
		VARIANT VariantProcessId; VariantInit(&VariantProcessId);

		Result = Enumerator->Next(WBEM_INFINITE, 1, &Object, &uReturned);
		if (!SUCCEEDED(Result))
			continue;

		if (uReturned == 0)
			continue;

		Result = Object->Get(L"Name", 0, &ProcessData, NULL, NULL);
		if (SUCCEEDED(Result))
		{
			if (StringCompareW(BinaryNameWchar, V_BSTR(&ProcessData)) == ERROR_SUCCESS)
			{
				Result = Object->Get(L"ProcessId", 0, &VariantProcessId, NULL, NULL);
				if (SUCCEEDED(Result))
					ProcessId = V_UI4(&VariantProcessId);
			}
		}

		VariantClear(&ProcessData);
		VariantClear(&VariantProcessId);

		if (Object)
			Object->Release();
	}

EXIT_ROUTINE:

	if (Enumerator)
		Enumerator->Release();

	if (Services)
		Services->Release();

	if (Locator)
		Locator->Release();

	CoUninitialize();

	return (Result != S_OK ? Win32FromHResult(Result) : ProcessId);
}