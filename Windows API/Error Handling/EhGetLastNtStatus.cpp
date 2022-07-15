NTSTATUS EhGetLastNtStatus(VOID)
{
	return GetTeb()->LastStatusValue;
}
