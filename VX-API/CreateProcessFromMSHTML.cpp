#include "Win32Helper.h"

//CreateProcessFromMsHTMLW(L"vbscript:CreateObject(\"WScript.Shell\").Run(\"calc.exe\",0)(Window.Close)")
//CreateProcessFromMsHTMLW(L"\"javascript:close((V=(v=new ActiveXObject('SAPI.SpVoice')).GetVoices()).count&&v.Speak('Hello! I am '+V(0).GetAttribute('Gender')))\"");


BOOL CreateProcessFromMsHTMLW(LPCWSTR MshtaCommand)
{
	typedef HRESULT(WINAPI* RUNHTMLAPPLICATION)(HINSTANCE, HINSTANCE, LPSTR, INT);
	RUNHTMLAPPLICATION RunHtmlApplication = NULL;
	HMODULE hMod = NULL;
	WCHAR wBinaryBuffer[MAX_PATH * sizeof(WCHAR)] = { 0 };
	WCHAR Payload[MAX_PATH * sizeof(WCHAR) * 2] = { 0 };
	BOOL bFlag = FALSE;

	if (GetProcessPathFromLoaderLoadModuleW(MAX_PATH * sizeof(WCHAR), wBinaryBuffer) == 0)
		goto EXIT_ROUTINE;

	StringConcatW(Payload, L"\"");
	StringConcatW(Payload, wBinaryBuffer);
	StringConcatW(Payload, L"\"");
	StringConcatW(Payload, L" ");
	StringConcatW(Payload, MshtaCommand);

	if (!RtlSetBaseUnicodeCommandLine(Payload))
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"mshtml.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	RunHtmlApplication = (RUNHTMLAPPLICATION)GetProcAddressA((DWORD64)hMod, "RunHTMLApplication");
	if (!RunHtmlApplication)
		goto EXIT_ROUTINE;

	RunHtmlApplication(NULL, NULL, NULL, 0);

	bFlag = TRUE;

EXIT_ROUTINE:

	return bFlag;
}