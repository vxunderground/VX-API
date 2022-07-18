/*
FileToClone can be a path to any file. The file does not matter, but it must exist
NewFileName is the file you want to create. It can named anything and in any dir you have permissions to create a file in

Credit: Jonas Lyk
*/
BOOL CreateFileFromDsCopyFromSharedFileW(PWCHAR NewFileName, PWCHAR FileToClone)
{
	typedef struct __DATA_SHARE_SCOPE_ENTRY {
		INT ScopeType;
		PWCHAR ScopeValue;
	}DATA_SHARE_SCOPE_ENTRY, * PDATA_SHARE_SCOPE_ENTRY;

	typedef struct __DATA_SHARE_SCOPE {
		INT ScopeCount;
		DATA_SHARE_SCOPE_ENTRY Entries[20];
	}DATA_SHARE_SCOPE, * PDATA_SHARE_SCOPE;

	typedef struct __DATA_SHARE_CTRL {
		INT SharePermission;
		INT ShareMode;
		DATA_SHARE_SCOPE Scope;
	}DATA_SHARE_CTRL, * PDATA_SHARE_CTRL;

	typedef HRESULT(WINAPI* DSCREATESHAREDFILETOKEN)(LPCWSTR, PDATA_SHARE_CTRL, INT, INT, WCHAR**);
	typedef HRESULT(WINAPI* DSCOPYFROMSHAREDFILE)(LPCWSTR, LPCWSTR);

	DATA_SHARE_CTRL Share; RfZeroMemory(&Share, sizeof(DATA_SHARE_CTRL));
	LPWSTR SidString = NULL;
	HANDLE hToken = NULL;
	DSCREATESHAREDFILETOKEN DsCreateSharedFileToken = NULL;
	DSCOPYFROMSHAREDFILE DsCopyFromSharedFile = NULL;
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	PWCHAR TokenData = NULL;
	HMODULE hDsClient = NULL;

	hDsClient = LoadLibraryW(L"DSCLIENT.DLL");
	if (hDsClient == NULL)
		return FALSE;

	DsCreateSharedFileToken = (DSCREATESHAREDFILETOKEN)RfGetProcAddressA((DWORD64)hDsClient, "DSCreateSharedFileToken");
	DsCopyFromSharedFile = (DSCOPYFROMSHAREDFILE)RfGetProcAddressA((DWORD64)hDsClient, "DSCopyFromSharedFile");

	if (!DsCreateSharedFileToken || !DsCopyFromSharedFile)
		goto EXIT_ROUTINE;

	if ((SidString = GetCurrentUserSidW(hToken, FALSE)) == NULL)
		goto EXIT_ROUTINE;

	Share.SharePermission = 2;
	Share.ShareMode = 3;
	Share.Scope.ScopeCount = 1;
	Share.Scope.Entries[0].ScopeType = 0;
	Share.Scope.Entries[0].ScopeValue = SidString;

	DsCreateSharedFileToken(FileToClone, &Share, 0, 0, &TokenData);
	if (TokenData == NULL)
		goto EXIT_ROUTINE;

	if (DsCopyFromSharedFile(TokenData, NewFileName) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = EhGetLastError();

	if (SidString)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, SidString);

	if (hToken)
		CloseHandle(hToken);

	return bFlag;
}

BOOL CreateFileFromDsCopyFromSharedFileA(PCHAR NewFileName, PCHAR FileToClone)
{
	typedef struct __DATA_SHARE_SCOPE_ENTRY {
		INT ScopeType;
		PWCHAR ScopeValue;
	}DATA_SHARE_SCOPE_ENTRY, * PDATA_SHARE_SCOPE_ENTRY;

	typedef struct __DATA_SHARE_SCOPE {
		INT ScopeCount;
		DATA_SHARE_SCOPE_ENTRY Entries[20];
	}DATA_SHARE_SCOPE, * PDATA_SHARE_SCOPE;

	typedef struct __DATA_SHARE_CTRL {
		INT SharePermission;
		INT ShareMode;
		DATA_SHARE_SCOPE Scope;
	}DATA_SHARE_CTRL, * PDATA_SHARE_CTRL;

	typedef HRESULT(WINAPI* DSCREATESHAREDFILETOKEN)(LPCWSTR, PDATA_SHARE_CTRL, INT, INT, WCHAR**);
	typedef HRESULT(WINAPI* DSCOPYFROMSHAREDFILE)(LPCWSTR, LPCWSTR);

	DATA_SHARE_CTRL Share; RfZeroMemory(&Share, sizeof(DATA_SHARE_CTRL));
	LPWSTR SidString = NULL;
	HANDLE hToken = NULL;
	DSCREATESHAREDFILETOKEN DsCreateSharedFileToken = NULL;
	DSCOPYFROMSHAREDFILE DsCopyFromSharedFile = NULL;
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	PWCHAR TokenData = NULL;
	HMODULE hDsClient = NULL;

	WCHAR FileToCloneWchar[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR NewFileNameWchar[MAX_PATH * sizeof(WCHAR)] = { 0 };

	if (CharStringToWCharString((PWCHAR)FileToCloneWchar, FileToClone, (MAX_PATH * sizeof(WCHAR))) == 0)
		goto EXIT_ROUTINE;

	if (CharStringToWCharString((PWCHAR)NewFileNameWchar, NewFileName, (MAX_PATH * sizeof(WCHAR))) == 0)
		goto EXIT_ROUTINE;

	hDsClient = LoadLibraryW(L"DSCLIENT.DLL");
	if (hDsClient == NULL)
		return FALSE;

	DsCreateSharedFileToken = (DSCREATESHAREDFILETOKEN)RfGetProcAddressA((DWORD64)hDsClient, "DSCreateSharedFileToken");
	DsCopyFromSharedFile = (DSCOPYFROMSHAREDFILE)RfGetProcAddressA((DWORD64)hDsClient, "DSCopyFromSharedFile");

	if (!DsCreateSharedFileToken || !DsCopyFromSharedFile)
		goto EXIT_ROUTINE;

	if ((SidString = GetCurrentUserSidW(hToken, FALSE)) == NULL)
		goto EXIT_ROUTINE;

	Share.SharePermission = 2;
	Share.ShareMode = 3;
	Share.Scope.ScopeCount = 1;
	Share.Scope.Entries[0].ScopeType = 0;
	Share.Scope.Entries[0].ScopeValue = SidString;

	DsCreateSharedFileToken((PWCHAR)FileToCloneWchar, &Share, 0, 0, &TokenData);
	if (TokenData == NULL)
		goto EXIT_ROUTINE;

	if (DsCopyFromSharedFile(TokenData, (PWCHAR)NewFileNameWchar) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = EhGetLastError();

	if (SidString)
		HeapFree(RfGetProcessHeap(), HEAP_ZERO_MEMORY, SidString);

	if (hToken)
		CloseHandle(hToken);

	return bFlag;
}
