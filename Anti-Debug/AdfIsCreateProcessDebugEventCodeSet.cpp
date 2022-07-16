/*

When the CREATE_PROCESS_DEBUG_EVENT event occurs, the handle of the debugged file is stored in 
the CREATE_PROCESS_DEBUG_INFO structure. Therefore, debuggers can read the debug information 
from this file. If this handle is not closed by the debugger, the file won’t be opened with 
exclusive access. Some debuggers can forget to close the handle.

This trick uses kernel32!CreateFileW() (or kernel32!CreateFileA()) to exclusively open the 
file of the current process. If the call fails, we can consider that the current process is being 
run in the presence of a debugger.

Credit: Checkpoint Research
*/

BOOL AdfIsCreateProcessDebugEventCodeSet(VOID)
{
	WCHAR FilePath[MAX_PATH * sizeof(WCHAR)] = { 0 };
	HANDLE hHandle = INVALID_HANDLE_VALUE;

	if (GetInMemoryModulePathFromProcessParametersW((MAX_PATH * sizeof(WCHAR)), FilePath) == 0)
		return FALSE;

	hHandle = CreateFileW(FilePath, GENERIC_READ, 0, NULL, OPEN_EXISTING, 0, 0);
	if (hHandle == INVALID_HANDLE_VALUE)
		return TRUE;

	if (hHandle)
		CloseHandle(hHandle);

	return FALSE;
}
