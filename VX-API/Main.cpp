#include "MalwareHeader.h"



INT WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ PWSTR pCmdLine, _In_ INT nCmdShow)
{
	RtlInitializeNtdllFunctionsForForwards(TRUE, SH_DJB2);

	IsDllLinkedToModule(SH_DJB2, 0, TRUE);

	return 0;
} 

/*
#pragma comment(linker, "/entry:__EntryPointEx")
#pragma comment(linker, "/subsystem:windows")

INT __EntryPointEx(VOID)
{
	DWORD dwError = ERROR_SUCCESS;
	BOOL bFlag = FALSE;


	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		dwError = GetLastError();

	return dwError;
}
*/
