#include "Win32Helper.h"

INT main(VOID)
{
	DWORD dwError = ERROR_SUCCESS;
	PBYTE Buffer = NULL;

	/*SHELLCODE_EXECUTION_INFORMATION Sei = { 0 };
	Sei.Payload = (LPBYTE)GenericShellcodeOpenCalcExitThread();
	Sei.dwLengthOfPayloadInBytes = 277;
	Sei.MethodEnum = E_ENUMDESKTOPSW;
	DWORD dwX = 0;*/
	
	PROCESS_INJECTION_INFORMATION Pii = { 0 };

	Pii.Payload = (LPBYTE)GenericShellcodeHelloWorldMessageBoxAEbFbLoop();
	Pii.dwLengthOfPayloadInBytes = 70;
	Pii.ProcessId = 33176;
	Pii.ThreadId = 18600;
	Pii.MethodEnum = E_QUEUE_USER_APC;

	//ShellcodeExecutionViaFunctionCallbackMain(&Sei);
	//ProcessInjectionMain(&Pii);

	MpfExtractMaliciousPayloadFromZipFileW((PWCHAR)L"C:\\Users\\dwThr\\Desktop\\Test.zip", (PWCHAR)L"C:\\Users\\dwThr\\Desktop\\");

	return dwError;
}

