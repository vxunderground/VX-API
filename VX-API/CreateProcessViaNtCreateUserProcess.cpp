#include "Win32Helper.h"

#define PS_ATTRIBUTE_NUMBER_MASK    0x0000ffff
#define PS_ATTRIBUTE_THREAD         0x00010000 
#define PS_ATTRIBUTE_INPUT          0x00020000 
#define PS_ATTRIBUTE_ADDITIVE       0x00040000 

typedef enum _PS_ATTRIBUTE_NUM
{
	PsAttributeParentProcess,                 
	PsAttributeDebugPort,                      
	PsAttributeToken,                       
	PsAttributeClientId,                       
	PsAttributeTebAddress,                
	PsAttributeImageName,                    
	PsAttributeImageInfo,                     
	PsAttributeMemoryReserve,                  
	PsAttributePriorityClass,                  
	PsAttributeErrorMode,                      
	PsAttributeStdHandleInfo,                   
	PsAttributeHandleList,                     
	PsAttributeGroupAffinity,                  
	PsAttributePreferredNode,                   
	PsAttributeIdealProcessor,              
	PsAttributeUmsThread,                  
	PsAttributeMitigationOptions,             
	PsAttributeProtectionLevel,                
	PsAttributeSecureProcess,                 
	PsAttributeJobList,
	PsAttributeChildProcessPolicy,              
	PsAttributeAllApplicationPackagesPolicy,    
	PsAttributeWin32kFilter,
	PsAttributeSafeOpenPromptOriginClaim,
	PsAttributeBnoIsolation,
	PsAttributeDesktopAppPolicy,
	PsAttributeMax
} PS_ATTRIBUTE_NUM;

#define PsAttributeValue(Number, Thread, Input, Additive) \
    (((Number) & PS_ATTRIBUTE_NUMBER_MASK) | \
    ((Thread) ? PS_ATTRIBUTE_THREAD : 0) | \
    ((Input) ? PS_ATTRIBUTE_INPUT : 0) | \
    ((Additive) ? PS_ATTRIBUTE_ADDITIVE : 0))

#define RTL_USER_PROCESS_PARAMETERS_NORMALIZED              0x01
#define PS_ATTRIBUTE_IMAGE_NAME \
    PsAttributeValue(PsAttributeImageName, FALSE, TRUE, FALSE)

typedef struct _PS_ATTRIBUTE
{
	ULONG_PTR Attribute;
	SIZE_T Size;
	union
	{
		ULONG_PTR Value;
		PVOID ValuePtr;
	};
	PSIZE_T ReturnLength;
} PS_ATTRIBUTE, * PPS_ATTRIBUTE;

typedef struct _PS_ATTRIBUTE_LIST
{
	SIZE_T TotalLength;
	PS_ATTRIBUTE Attributes[2];
} PS_ATTRIBUTE_LIST, * PPS_ATTRIBUTE_LIST;

typedef enum _PS_CREATE_STATE
{
	PsCreateInitialState,
	PsCreateFailOnFileOpen,
	PsCreateFailOnSectionCreate,
	PsCreateFailExeFormat,
	PsCreateFailMachineMismatch,
	PsCreateFailExeName,
	PsCreateSuccess,
	PsCreateMaximumStates
} PS_CREATE_STATE;

typedef struct _PS_CREATE_INFO {
	SIZE_T Size;
	PS_CREATE_STATE State;
	union {
		struct {
			union {
				ULONG InitFlags;
				struct {
					UCHAR WriteOutputOnExit : 1;
					UCHAR DetectManifest : 1;
					UCHAR IFEOSkipDebugger : 1;
					UCHAR IFEODoNotPropagateKeyState : 1;
					UCHAR SpareBits1 : 4;
					UCHAR SpareBits2 : 8;
					USHORT ProhibitedImageCharacteristics : 16;
				} s1;
			} u1;
			ACCESS_MASK AdditionalFileAccess;
		} InitState;
		struct { HANDLE FileHandle; } FailSection;
		struct { USHORT DllCharacteristics; } ExeFormat;
		struct { HANDLE IFEOKey; } ExeName;
		struct {
			union {
				ULONG OutputFlags;
				struct {
					UCHAR ProtectedProcess : 1;
					UCHAR AddressSpaceOverride : 1;
					UCHAR DevOverrideEnabled : 1;
					UCHAR ManifestDetected : 1;
					UCHAR ProtectedProcessLight : 1;
					UCHAR SpareBits1 : 3;
					UCHAR SpareBits2 : 8;
					USHORT SpareBits3 : 16;
				} s2;
			} u2;
			HANDLE FileHandle;
			HANDLE SectionHandle;
			ULONGLONG UserProcessParametersNative;
			ULONG UserProcessParametersWow64;
			ULONG CurrentParameterFlags;
			ULONGLONG PebAddressNative;
			ULONG PebAddressWow64;
			ULONGLONG ManifestAddress;
			ULONG ManifestSize;
		} SuccessState;
	};
} PS_CREATE_INFO, * PPS_CREATE_INFO;


DWORD CreateProcessViaNtCreateUserProcessA(PCHAR BinaryPath)
{
	typedef NTSTATUS(NTAPI* NTCREATEUSERPROCESS)(
		PHANDLE,
		PHANDLE,
		ACCESS_MASK,
		ACCESS_MASK,
		POBJECT_ATTRIBUTES,
		POBJECT_ATTRIBUTES,
		ULONG,
		ULONG,
		PRTL_USER_PROCESS_PARAMETERS,
		PPS_CREATE_INFO,
		PPS_ATTRIBUTE_LIST
		);

	typedef NTSTATUS(NTAPI* RTLCREATEPROCESSPARAMETERSEX)(
		PRTL_USER_PROCESS_PARAMETERS*,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PVOID,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		ULONG
		);

	typedef NTSTATUS(NTAPI* RTLDESTROYPROCESSPARAMETERS)(PRTL_USER_PROCESS_PARAMETERS);

	NTCREATEUSERPROCESS NtCreateUserProcess;
	RTLCREATEPROCESSPARAMETERSEX RtlCreateProcessParametersEx;
	RTLDESTROYPROCESSPARAMETERS RtlDestroyProcessParameters;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = NULL;
	UNICODE_STRING NtImagePath;
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
		return GetLastErrorEx();

	NtCreateUserProcess = (NTCREATEUSERPROCESS)GetProcAddressA((DWORD64)hModule, "NtCreateUserProcess");
	if (NtCreateUserProcess == NULL)
		return GetLastErrorEx();

	RtlCreateProcessParametersEx = (RTLCREATEPROCESSPARAMETERSEX)GetProcAddressA((DWORD64)hModule, "RtlCreateProcessParametersEx");
	if (RtlCreateProcessParametersEx == NULL)
		return GetLastErrorEx();

	RtlDestroyProcessParameters = (RTLDESTROYPROCESSPARAMETERS)GetProcAddressA((DWORD64)hModule, "RtlDestroyProcessParameters");
	if (RtlDestroyProcessParameters == NULL)
		return GetLastErrorEx();

	CharStringToWCharString(wBinaryPath, BinaryPath, StringLengthA(BinaryPath));
	StringCopyW(MsDosFullPath, (PWCHAR)L"\\??\\");
	StringConcatW(MsDosFullPath, wBinaryPath);

	RtlInitUnicodeString(&NtImagePath, MsDosFullPath);

	if (RtlCreateProcessParametersEx(&ProcessParameters, &NtImagePath, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, RTL_USER_PROCESS_PARAMETERS_NORMALIZED) != ERROR_SUCCESS)
		return GetLastErrorEx();

	AttributeList = (PPS_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeapEx(), HEAP_ZERO_MEMORY, sizeof(PS_ATTRIBUTE));
	if (AttributeList)
	{
		AttributeList->TotalLength = sizeof(PS_ATTRIBUTE_LIST) - sizeof(PS_ATTRIBUTE);
		AttributeList->Attributes[0].Attribute = PS_ATTRIBUTE_IMAGE_NAME;
		AttributeList->Attributes[0].Size = NtImagePath.Length;
		AttributeList->Attributes[0].Value = (ULONG_PTR)NtImagePath.Buffer;

		if (NtCreateUserProcess(&hHandle, &hThread, PROCESS_ALL_ACCESS, THREAD_ALL_ACCESS, NULL, NULL, NULL, NULL, ProcessParameters, &CreateInfo, AttributeList) != ERROR_SUCCESS)
			dwError = GetLastErrorEx(); //?
	}

	if (AttributeList)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, AttributeList);

	if (ProcessParameters)
		RtlDestroyProcessParameters(ProcessParameters);

	return dwError;
}


DWORD CreateProcessViaNtCreateUserProcessW(PWCHAR BinaryPath)
{
	typedef NTSTATUS(NTAPI* NTCREATEUSERPROCESS)(
		PHANDLE,
		PHANDLE,
		ACCESS_MASK,
		ACCESS_MASK,
		POBJECT_ATTRIBUTES,
		POBJECT_ATTRIBUTES,
		ULONG,
		ULONG,
		PRTL_USER_PROCESS_PARAMETERS,
		PPS_CREATE_INFO,
		PPS_ATTRIBUTE_LIST
		);

	typedef NTSTATUS(NTAPI* RTLCREATEPROCESSPARAMETERSEX)(
		PRTL_USER_PROCESS_PARAMETERS*,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PVOID,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		PUNICODE_STRING,
		ULONG
		);

	typedef NTSTATUS(NTAPI* RTLDESTROYPROCESSPARAMETERS)(PRTL_USER_PROCESS_PARAMETERS);

	NTCREATEUSERPROCESS NtCreateUserProcess;
	RTLCREATEPROCESSPARAMETERSEX RtlCreateProcessParametersEx;
	RTLDESTROYPROCESSPARAMETERS RtlDestroyProcessParameters;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = NULL;
	UNICODE_STRING NtImagePath;
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
		return GetLastErrorEx();

	NtCreateUserProcess = (NTCREATEUSERPROCESS)GetProcAddressA((DWORD64)hModule, "NtCreateUserProcess");
	if (NtCreateUserProcess == NULL)
		return GetLastErrorEx();

	RtlCreateProcessParametersEx = (RTLCREATEPROCESSPARAMETERSEX)GetProcAddressA((DWORD64)hModule, "RtlCreateProcessParametersEx");
	if (RtlCreateProcessParametersEx == NULL)
		return GetLastErrorEx();

	RtlDestroyProcessParameters = (RTLDESTROYPROCESSPARAMETERS)GetProcAddressA((DWORD64)hModule, "RtlDestroyProcessParameters");
	if (RtlDestroyProcessParameters == NULL)
		return GetLastErrorEx();

	StringCopyW(MsDosFullPath, (PWCHAR)L"\\??\\");
	StringConcatW(MsDosFullPath, BinaryPath);

	RtlInitUnicodeString(&NtImagePath, MsDosFullPath);

	if (RtlCreateProcessParametersEx(&ProcessParameters, &NtImagePath, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL, RTL_USER_PROCESS_PARAMETERS_NORMALIZED) != ERROR_SUCCESS)
		return GetLastErrorEx();

	AttributeList = (PPS_ATTRIBUTE_LIST)HeapAlloc(GetProcessHeapEx(), HEAP_ZERO_MEMORY, sizeof(PS_ATTRIBUTE));
	if (AttributeList)
	{
		AttributeList->TotalLength = sizeof(PS_ATTRIBUTE_LIST) - sizeof(PS_ATTRIBUTE);
		AttributeList->Attributes[0].Attribute = PS_ATTRIBUTE_IMAGE_NAME;
		AttributeList->Attributes[0].Size = NtImagePath.Length;
		AttributeList->Attributes[0].Value = (ULONG_PTR)NtImagePath.Buffer;

		if (NtCreateUserProcess(&hHandle, &hThread, PROCESS_ALL_ACCESS, THREAD_ALL_ACCESS, NULL, NULL, NULL, NULL, ProcessParameters, &CreateInfo, AttributeList) != ERROR_SUCCESS)
			dwError = GetLastErrorEx(); //?
	}

	if (AttributeList)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, AttributeList);

	if (ProcessParameters)
		RtlDestroyProcessParameters(ProcessParameters);

	return dwError;
}
