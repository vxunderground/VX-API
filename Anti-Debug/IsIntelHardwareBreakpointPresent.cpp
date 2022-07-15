BOOL IsIntelHardwareBreakpointPresent(VOID)
{
	BOOL bFlag = FALSE;
	PCONTEXT Context = NULL;

	Context = (PCONTEXT)VirtualAlloc(NULL, sizeof(CONTEXT), MEM_COMMIT, PAGE_READWRITE);
	if (Context == NULL)
		return FALSE;

	RtlZeroMemory(Context, sizeof(Context));

	Context->ContextFlags = CONTEXT_DEBUG_REGISTERS;

	if (!GetThreadContext(RfGetCurrentThread(), Context))
		goto EXIT_ROUTINE;

	if (Context->Dr0 || Context->Dr1 || Context->Dr2 || Context->Dr3)
		bFlag = TRUE;

EXIT_ROUTINE:

	if (Context)
		VirtualFree(Context, 0, MEM_RELEASE);

	return bFlag;
}
