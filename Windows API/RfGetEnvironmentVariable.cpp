DWORD RfGetEnvironmentVariableW(LPCWSTR Name, LPWSTR Buffer, DWORD Size)
{
	UNICODE_STRING uString; RtlZeroMemory(&uString, sizeof(UNICODE_STRING));
	UNICODE_STRING Variable; RtlZeroMemory(&Variable, sizeof(UNICODE_STRING));
	DWORD Token[1] = { 61 };
	LPWSTR String = NULL;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = (PRTL_USER_PROCESS_PARAMETERS)GetPeb()->ProcessParameters;
	LPWSTR Environment = (LPWSTR)ProcessParameters->Environment;
	LPWSTR lpszPtr = (LPWSTR)Environment;
	PWCHAR Pointer;

	BOOL bFlag = FALSE;

	String = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WCHAR) * 2);
	if (String == NULL)
		goto EXIT_ROUTINE;

	DecimalToAsciiW(String, Token, 1);

	Name = CaplockStringW((PWCHAR)Name);
	if (Name == NULL)
		goto EXIT_ROUTINE;

	RtlInitUnicodeString(&Variable, (PWCHAR)Name);

	while (*lpszPtr)
	{
		DWORD dwVariableHash = 0;
		DWORD dwPointerHash = 0;
		lpszPtr += StringLengthW(lpszPtr) + 1;
		Pointer = StringTokenW(lpszPtr, String);
		if (Pointer == NULL)
			goto EXIT_ROUTINE;

		Pointer = CaplockStringW((PWCHAR)Pointer);

		dwVariableHash = HashStringDjb2W(Variable.Buffer);
		dwPointerHash = HashStringDjb2W(lpszPtr);

		if (dwVariableHash == dwPointerHash)
		{
			lpszPtr += StringLengthW(lpszPtr) + 1;
			Pointer = StringTokenW(lpszPtr, String);
			if (Pointer == NULL)
				goto EXIT_ROUTINE;

			RtlInitUnicodeString(&uString, Pointer);
			break;
		}

	}

	if (StringCopyW(Buffer, uString.Buffer) == NULL)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (String)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, String);

	return (bFlag == TRUE ? uString.Length : 0);
}

DWORD RfGetEnvironmentVariableA(LPCSTR Name, LPSTR Buffer, DWORD Size)
{
	UNICODE_STRING uString; RtlZeroMemory(&uString, sizeof(UNICODE_STRING));
	UNICODE_STRING Variable; RtlZeroMemory(&Variable, sizeof(UNICODE_STRING));
	DWORD Token[1] = { 61 };
	LPWSTR String = NULL;
	PRTL_USER_PROCESS_PARAMETERS ProcessParameters = (PRTL_USER_PROCESS_PARAMETERS)GetPeb()->ProcessParameters;
	LPWSTR Environment = (LPWSTR)ProcessParameters->Environment;
	LPWSTR lpszPtr = (LPWSTR)Environment;
	PWCHAR Pointer;
	PWCHAR pwName = NULL;

	BOOL bFlag = FALSE;

	String = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WCHAR) * 2);
	if (String == NULL)
		goto EXIT_ROUTINE;

	pwName = (LPWSTR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, sizeof(WCHAR) * 2);
	if (pwName == NULL)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString(pwName, (PCHAR)Name, 256) == 0)
		goto EXIT_ROUTINE;

	DecimalToAsciiW(String, Token, 1);

	pwName = CaplockStringW((PWCHAR)pwName);
	if (Name == NULL)
		goto EXIT_ROUTINE;

	RtlInitUnicodeString(&Variable, (PWCHAR)pwName);

	while (*lpszPtr)
	{
		DWORD dwVariableHash = 0;
		DWORD dwPointerHash = 0;
		lpszPtr += StringLengthW(lpszPtr) + 1;
		Pointer = StringTokenW(lpszPtr, String);
		if (Pointer == NULL)
			goto EXIT_ROUTINE;

		Pointer = CaplockStringW((PWCHAR)Pointer);

		dwVariableHash = HashStringDjb2W(Variable.Buffer);
		dwPointerHash = HashStringDjb2W(lpszPtr);

		if (dwVariableHash == dwPointerHash)
		{
			lpszPtr += StringLengthW(lpszPtr) + 1;
			Pointer = StringTokenW(lpszPtr, String);
			if (Pointer == NULL)
				goto EXIT_ROUTINE;

			RtlInitUnicodeString(&uString, Pointer);
			break;
		}

	}

	if (WCharStringToCharString(Buffer, uString.Buffer, uString.MaximumLength) == 0)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (pwName)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, pwName);

	if (String)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, String);

	return (bFlag == TRUE ? uString.Length : 0);
}
