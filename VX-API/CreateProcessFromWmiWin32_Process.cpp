#include "Win32Helper.h"

DWORD CreateProcessFromWmiWin32_ProcessW(LPCWSTR BinaryPath)
{
	HRESULT Result;
	IWbemLocator* Locator = NULL;
	IWbemServices* Services = NULL;
	IWbemClassObject* Win32ProcessStartupObject = NULL;
	IWbemClassObject* StartupInstance = NULL;
	IWbemClassObject* Win32ProcessObject = NULL;
	IWbemClassObject* ParameterInformationObject = NULL;
	IWbemClassObject* ParametersObject = NULL;
	IWbemClassObject* StartupResponseObject = NULL;
	VARIANT varCommand;
	VARIANT vtDispatch;

	BOOL bFlag = FALSE;
	DWORD dwError = ERROR_SUCCESS;

	Result = CoInitializeEx(0, COINIT_MULTITHREADED);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoCreateInstance(CLSID_WbemLocator, NULL, 1, IID_IWbemLocator, (LPVOID*)&Locator);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Locator->ConnectServer((BSTR)L"ROOT\\CIMV2", NULL, NULL, 0, NULL, 0, 0, &Services);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoSetProxyBlanket(Services, RPC_C_AUTHN_WINNT, RPC_C_AUTHZ_NONE, NULL, RPC_C_AUTHN_LEVEL_CALL, RPC_C_IMP_LEVEL_IMPERSONATE, NULL, EOAC_NONE);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Services->GetObjectW((BSTR)L"Win32_ProcessStartup", 0, NULL, &Win32ProcessStartupObject, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Win32ProcessStartupObject->SpawnInstance(0, &StartupInstance);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Services->GetObjectW((BSTR)L"Win32_Process", 0, NULL, &Win32ProcessObject, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Win32ProcessObject->GetMethod((BSTR)L"Create", 0, &ParameterInformationObject, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = ParameterInformationObject->SpawnInstance(0, &ParametersObject);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	VariantInit(&varCommand);
	varCommand.vt = VT_BSTR;
	varCommand.bstrVal = (BSTR)BinaryPath;

	Result = ParametersObject->Put((BSTR)L"CommandLine", 0, &varCommand, 0);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	VariantInit(&vtDispatch);
	vtDispatch.vt = VT_DISPATCH;
	vtDispatch.byref = StartupInstance;

	Result = ParametersObject->Put((BSTR)L"ProcessStartupInformation", 0, &vtDispatch, 0);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = Services->ExecMethod((BSTR)L"Win32_Process", (BSTR)L"Create", 0, NULL, ParametersObject, &StartupResponseObject, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
	{
		if (Result != S_OK)
			dwError = Win32FromHResult(Result);
		else
			dwError = GetLastErrorFromTeb();
	}

	if (Locator)
		Locator->Release();

	if (Services)
		Services->Release();

	if (Win32ProcessStartupObject)
		Win32ProcessStartupObject->Release();

	if (StartupInstance)
		StartupInstance->Release();

	if (Win32ProcessObject)
		Win32ProcessObject->Release();

	if (ParameterInformationObject)
		ParameterInformationObject->Release();

	if (ParametersObject)
		ParametersObject->Release();

	if (StartupResponseObject)
		StartupResponseObject->Release();

	CoUninitialize();

	return dwError;
}