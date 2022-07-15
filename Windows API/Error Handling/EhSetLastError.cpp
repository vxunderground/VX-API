VOID EhSetLastError(DWORD ErrorCode)
{
	GetTeb()->LastErrorValue = ErrorCode;
}
