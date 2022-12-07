#include "Win32Helper.h"

BOOL InitHardwareBreakpointEngine(VOID)
{
	if (GlobalHardwareBreakpointObject.IsInit)
		return TRUE;

	GlobalHardwareBreakpointObject.HandlerObject = AddVectoredExceptionHandler(1, ExceptionHandlerCallbackRoutine);
	if (!GlobalHardwareBreakpointObject.HandlerObject)
		return FALSE;

	InitializeCriticalSection(&CriticalSection);

	GlobalHardwareBreakpointObject.IsInit = TRUE;

	return TRUE;
}