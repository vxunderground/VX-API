#include "Win32Helper.h"

DWORD CreateProcessViaNtCreateUserProcessA(PCHAR BinaryPath)
{
	NTCREATEUSERPROCESS NtCreateUserProcess;
	RTLCREATEPROCESSPARAMETERSEX RtlCreateProcessParametersEx;
	RTLDESTROYPROCESSPARAMETERS RtlDestroyProcessParameters;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = NULL;
	UNICODE_STRING NtImagePath = {0};
	WCHAR MsDosFullPath[MAX_PATH * sizeof(WCHAR)] = { 0 };
	PS_CREATE_INFO CreateInfo = { 0 };
	HMODULE hModule;
	PPS_ATTRIBUTE_LIST AttributeList = NULL;
	HANDLE hHandle = NULL, hThread = NULL;
	DWORD dwError = ERROR_SUCCESS;
	WCHAR wBinaryPath[MAX_PATH * sizeof(WCHAR)] = { 0 };

	CreateInfo.Size = sizeof(CreateInfo);
	CreateInfo.State = PsCreateInitialState;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return GetLastErrorFromTeb();

	NtCreateUserProcess = (NTCREATEUSERPROCESS)GetProcAddressA((DWORD64)hModule, "NtCreateUserProcess");
	if (NtCreateUserProcess == NULL)
		return GetLastErrorFromTeb();

	RtlCreateProcessParametersEx = (RTLCREATEPROCESSPARAMETERSEX)GetProcAddressA((DWORD64)hModule, "RtlCreateProcessParametersEx");
	if (RtlCreateProcessParametersEx == NULL)
		return GetLastErrorFromTeb();

	RtlDestroyProcessParameters = (RTLDESTROYPROCESSPARAMETERS)GetProcAddressA((DWORD64)hModule, "RtlDestroyProcessParameters");
	if (RtlDestroyProcessParameters == NULL)
		return GetLastErrorFromTeb();

	CharStringToWCharString(wBinaryPath, BinaryPath, StringLengthA(BinaryPath));
	StringCopyW(MsDosFullPath, (PWCHAR)L"\\??\\");
	StringConcatW(MsDosFullPath, wBinaryPath);

	RtlInitUnicodeString(&NtImagePath, MsDosFullPath);

	if (RtlCreateProcessParametersEx(&ProcessParameters, &NtImagePath, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, RTL_USER_PROCESS_PARAMETERS_NORMALIZED) != ERROR_SUCCESS)
		return GetLastErrorFromTeb();

	AttributeList = (PPS_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, sizeof(PS_ATTRIBUTE));
	if (AttributeList)
	{
		AttributeList->TotalLength = sizeof(PS_ATTRIBUTE_LIST) - sizeof(PS_ATTRIBUTE);
		AttributeList->Attributes[0].Attribute = PS_ATTRIBUTE_IMAGE_NAME;
		AttributeList->Attributes[0].Size = NtImagePath.Length;
		AttributeList->Attributes[0].Value = (ULONG_PTR)NtImagePath.Buffer;

		if (NtCreateUserProcess(&hHandle, &hThread, PROCESS_ALL_ACCESS, THREAD_ALL_ACCESS, NULL, NULL, NULL, NULL, ProcessParameters, &CreateInfo, AttributeList) != ERROR_SUCCESS)
			dwError = GetLastErrorFromTeb(); //?
	}

	if (AttributeList)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, AttributeList);

	if (ProcessParameters)
		RtlDestroyProcessParameters(ProcessParameters);

	return dwError;
}


DWORD CreateProcessViaNtCreateUserProcessW(PWCHAR BinaryPath)
{
	NTCREATEUSERPROCESS NtCreateUserProcess;
	RTLCREATEPROCESSPARAMETERSEX RtlCreateProcessParametersEx;
	RTLDESTROYPROCESSPARAMETERS RtlDestroyProcessParameters;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = NULL;
	UNICODE_STRING NtImagePath = {0};
	WCHAR MsDosFullPath[MAX_PATH * sizeof(WCHAR)] = { 0 };
	PS_CREATE_INFO CreateInfo = { 0 };
	HMODULE hModule;
	PPS_ATTRIBUTE_LIST AttributeList = NULL;
	HANDLE hHandle = NULL, hThread = NULL;
	DWORD dwError = ERROR_SUCCESS;

	CreateInfo.Size = sizeof(CreateInfo);
	CreateInfo.State = PsCreateInitialState;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return GetLastErrorFromTeb();

	NtCreateUserProcess = (NTCREATEUSERPROCESS)GetProcAddressA((DWORD64)hModule, "NtCreateUserProcess");
	if (NtCreateUserProcess == NULL)
		return GetLastErrorFromTeb();

	RtlCreateProcessParametersEx = (RTLCREATEPROCESSPARAMETERSEX)GetProcAddressA((DWORD64)hModule, "RtlCreateProcessParametersEx");
	if (RtlCreateProcessParametersEx == NULL)
		return GetLastErrorFromTeb();

	RtlDestroyProcessParameters = (RTLDESTROYPROCESSPARAMETERS)GetProcAddressA((DWORD64)hModule, "RtlDestroyProcessParameters");
	if (RtlDestroyProcessParameters == NULL)
		return GetLastErrorFromTeb();

	StringCopyW(MsDosFullPath, (PWCHAR)L"\\??\\");
	StringConcatW(MsDosFullPath, BinaryPath);

	RtlInitUnicodeString(&NtImagePath, MsDosFullPath);

	if (RtlCreateProcessParametersEx(&ProcessParameters, &NtImagePath, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, RTL_USER_PROCESS_PARAMETERS_NORMALIZED) != ERROR_SUCCESS)
		return GetLastErrorFromTeb();

	AttributeList = (PPS_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, sizeof(PS_ATTRIBUTE));
	if (AttributeList)
	{
		AttributeList->TotalLength = sizeof(PS_ATTRIBUTE_LIST) - sizeof(PS_ATTRIBUTE);
		AttributeList->Attributes[0].Attribute = PS_ATTRIBUTE_IMAGE_NAME;
		AttributeList->Attributes[0].Size = NtImagePath.Length;
		AttributeList->Attributes[0].Value = (ULONG_PTR)NtImagePath.Buffer;

		if (NtCreateUserProcess(&hHandle, &hThread, PROCESS_ALL_ACCESS, THREAD_ALL_ACCESS, NULL, NULL, NULL, NULL, ProcessParameters, &CreateInfo, AttributeList) != ERROR_SUCCESS)
			dwError = GetLastErrorFromTeb(); //?
	}

	if (AttributeList)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, AttributeList);

	if (ProcessParameters)
		RtlDestroyProcessParameters(ProcessParameters);

	return dwError;
}
