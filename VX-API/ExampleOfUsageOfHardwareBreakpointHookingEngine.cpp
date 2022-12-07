#include "Win32Helper.h"

VOID SleepInterceptionRoutine(PEXCEPTION_POINTERS ExceptionInfo)
{
	MessageBoxA(NULL, "OK", "OK", MB_OK);

	ExceptionInfo->ContextRecord->EFlags |= (1 << 16); //restore eflags
	ExceptionInfo->ContextRecord->Rcx = 0; 
}

INT __demonstration_WinMain(VOID)
{
	if (!InitHardwareBreakpointEngine())
		return 1;

	InsertDescriptorEntry((PUINT_VAR_T)&Sleep, 0, SleepInterceptionRoutine, 0, TRUE);

	Sleep(100000);

	RemoveDescriptorEntry((PUINT_VAR_T)&Sleep, 0);

	ShutdownHardwareBreakpointEngine();

	return TRUE;
}