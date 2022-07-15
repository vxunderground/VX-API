DWORD EhGetLastError(VOID)
{
	return GetTeb()->LastErrorValue;
}
