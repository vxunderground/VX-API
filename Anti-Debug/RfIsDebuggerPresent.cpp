BOOL IsBeingDebuggedAlt(VOID)
{
	return GetPeb()->BeingDebugged;
}
