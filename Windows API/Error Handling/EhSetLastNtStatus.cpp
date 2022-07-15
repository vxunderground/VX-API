VOID EhSetLastNtStatus(NTSTATUS Status)
{
	GetTeb()->LastStatusValue = Status;
}
