BOOL RfIsDebuggerPresent(VOID)
{
	return GetPeb()->BeingDebugged;
}
