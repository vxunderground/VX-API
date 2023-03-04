#include "Win32Helper.h"

INT main(VOID)
{
	DWORD dwSize = 0;
	PCHAR Buffer = GenericShellcodeOpenCalcExitThread(&dwSize);

	//MpfSceViaSymEnumSourceFiles((PBYTE)Buffer, dwSize);
	
	//BOOL bFlag = AmsiBypassViaPatternScan(4288);
	
	CreateProcessFromShell32ShellExecRunDllW(L"C:\\Windows\\System32\\calc.exe");

	return ERROR_SUCCESS;
}

