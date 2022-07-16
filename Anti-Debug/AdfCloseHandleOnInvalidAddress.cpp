/*
If a process is running under a debugger and an invalid handle is passed to the ntdll!NtClose() or kernel32!CloseHandle() 
function, then the EXCEPTION_INVALID_HANDLE (0xC0000008) exception will be raised. The exception can be cached by 
an exception handler. If the control is passed to the exception handler, it indicates that a debugger is present.

Credit: Checkpoint Research

*/
BOOL AdfCloseHandleOnInvalidAddress(VOID)
{
	__try
	{
		CloseHandle((HANDLE)0xDEADBEEF);
		return FALSE;
	}
	__except (EXCEPTION_INVALID_HANDLE == GetExceptionCode() ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH)
	{
		return TRUE;
	}
	
	return FALSE;
}
