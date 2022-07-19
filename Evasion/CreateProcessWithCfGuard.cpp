/*
must pass pointer of PPROCESS_INFORMATION to function, callee is responsible for closing handles
eg 

	CloseHandle(PihProcess);
	CloseHandle(Pi.hThread);
*/

typedef struct _PROC_THREAD_ATTRIBUTE {
	ULONG64 Attribute;
	ULONG64 Size;
	ULONG64 Value;
}PROC_THREAD_ATTRIBUTE, * PPROC_THREAD_ATTRIBUTE;

typedef struct _PROC_THREAD_ATTRIBUTE_LIST {
	ULONG PresentFlags;
	ULONG AttributeCount;
	ULONG LastAttribute;
	ULONG SpareUlong0;
	struct _PROC_THREAD_ATTRIBUTE* ExtendedFlagsAttribute;
	struct _PROC_THREAD_ATTRIBUTE Attributes[1];
}PROC_THREAD_ATTRIBUTE_LIST, * PPROC_THREAD_ATTRIBUTE_LIST;

BOOL UnusedSubroutineInitializeProcThreadAttributeList(LPPROC_THREAD_ATTRIBUTE_LIST lpAttributeList, DWORD dwAttributeCount, DWORD dwFlags, PSIZE_T lpSize)
{
	BOOL bFlag = FALSE;
	DWORD dwSize = ERROR_SUCCESS;

	if (dwFlags || (dwAttributeCount > 0x1B))
	{
		SetLastError(ERROR_INVALID_PARAMETER);
		return bFlag;
	}

	dwSize = (24 * (dwAttributeCount + 1));

	if (lpAttributeList && *lpSize >= dwSize)
	{
		lpAttributeList->PresentFlags = 0;
		lpAttributeList->ExtendedFlagsAttribute = 0;
		lpAttributeList->AttributeCount = dwAttributeCount;
		lpAttributeList->LastAttribute = 0;
		bFlag = TRUE;
	}
	else
		SetLastError(ERROR_INSUFFICIENT_BUFFER);

	*lpSize = dwSize;
	return bFlag;
}

DWORD UnusedSubroutineGetProcThreadAttributeListSize(VOID)
{
	SIZE_T dwSize = 0;

	UnusedSubroutineInitializeProcThreadAttributeList(NULL, 1, 0, &dwSize);

	return dwSize;
}

VOID UnusedSubroutineUpdateProcThreadAttribute(LPPROC_THREAD_ATTRIBUTE_LIST AttributeList, DWORD_PTR Attribute, PVOID Policy, SIZE_T Size)
{
	PPROC_THREAD_ATTRIBUTE ExtendedAttributes;

	AttributeList->PresentFlags |= (1 << (Attribute & 0x0000FFFF));

	ExtendedAttributes = AttributeList->Attributes;
	ExtendedAttributes->Attribute = Attribute;
	ExtendedAttributes->Size = Size;
	ExtendedAttributes->Value = (ULONG64)Policy;
	AttributeList->LastAttribute++;

	return;
}

BOOL CreateProcessWithCfGuardW(PPROCESS_INFORMATION Pi, PWCHAR Path)
{
	BOOL bFlag = FALSE;
	PPROC_THREAD_ATTRIBUTE_LIST ThreadAttributes = NULL;
	SIZE_T dwAttributeSize = 0;
	DWORD64 Policy = PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_ON;

	STARTUPINFOEXW Si; RfZeroMemory(&Si, sizeof(STARTUPINFOEXW));
	Si.StartupInfo.cb = sizeof(STARTUPINFOEXW);
	RfZeroMemory(Pi, sizeof(PROCESS_INFORMATION));

	dwAttributeSize = UnusedSubroutineGetProcThreadAttributeListSize();
	if (dwAttributeSize == 0)
		goto EXIT_ROUTINE;

	ThreadAttributes = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(RfGetProcessHeap(), HEAP_ZERO_MEMORY, dwAttributeSize);
	if (ThreadAttributes == NULL)
		goto EXIT_ROUTINE;

	if(!UnusedSubroutineInitializeProcThreadAttributeList(ThreadAttributes, 1, 0, &dwAttributeSize))
		goto EXIT_ROUTINE;

	UnusedSubroutineUpdateProcThreadAttribute(ThreadAttributes, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &Policy, sizeof(DWORD64));
	
	Si.lpAttributeList = ThreadAttributes;

	if (!CreateProcessW(Path, NULL, NULL, NULL, TRUE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &Si.StartupInfo, Pi))
		goto EXIT_ROUTINE;

	Si.lpAttributeList = ThreadAttributes;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (ThreadAttributes)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, (PPROC_THREAD_ATTRIBUTE_LIST)ThreadAttributes);

	return bFlag;
}

BOOL CreateProcessWithCfGuardA(PPROCESS_INFORMATION Pi, PCHAR Path)
{
	BOOL bFlag = FALSE;
	PPROC_THREAD_ATTRIBUTE_LIST ThreadAttributes = NULL;
	SIZE_T dwAttributeSize = 0;
	DWORD64 Policy = PROCESS_CREATION_MITIGATION_POLICY_BLOCK_NON_MICROSOFT_BINARIES_ALWAYS_ON;

	STARTUPINFOEXA Si; RfZeroMemory(&Si, sizeof(STARTUPINFOEXA));
	Si.StartupInfo.cb = sizeof(STARTUPINFOEXW);
	RfZeroMemory(Pi, sizeof(PROCESS_INFORMATION));

	dwAttributeSize = UnusedSubroutineGetProcThreadAttributeListSize();
	if (dwAttributeSize == 0)
		goto EXIT_ROUTINE;

	ThreadAttributes = (PPROC_THREAD_ATTRIBUTE_LIST)HeapAlloc(RfGetProcessHeap(), HEAP_ZERO_MEMORY, dwAttributeSize);
	if (ThreadAttributes == NULL)
		goto EXIT_ROUTINE;

	if (!UnusedSubroutineInitializeProcThreadAttributeList(ThreadAttributes, 1, 0, &dwAttributeSize))
		goto EXIT_ROUTINE;

	UnusedSubroutineUpdateProcThreadAttribute(ThreadAttributes, PROC_THREAD_ATTRIBUTE_MITIGATION_POLICY, &Policy, sizeof(DWORD64));

	Si.lpAttributeList = ThreadAttributes;

	if (!CreateProcessA(Path, NULL, NULL, NULL, TRUE, EXTENDED_STARTUPINFO_PRESENT, NULL, NULL, &Si.StartupInfo, Pi))
		goto EXIT_ROUTINE;

	Si.lpAttributeList = ThreadAttributes;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (ThreadAttributes)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, (PPROC_THREAD_ATTRIBUTE_LIST)ThreadAttributes);

	return bFlag;
}
