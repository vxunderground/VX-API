DWORD RfGetCurrentProcessId(VOID)
{
	return HandleToUlong(GetTeb()->ClientId.UniqueProcess);
}
