#include "Win32Helper.h"

INT main(VOID)
{
	DWORD dwSize = 0;
	PCHAR Buffer = GenericShellcodeOpenCalcExitThread(&dwSize);

	//MpfSceViaSymEnumSourceFiles((PBYTE)Buffer, dwSize);
	
	//BOOL bFlag = AmsiBypassViaPatternScan(4288);
	
	CreateProcessFromINFSectionInstallStringNoCabA("C:\\Users\\dwThr\\Desktop\\demo.inf", "DefaultInstall_SingleUser");

	return ERROR_SUCCESS;
}

