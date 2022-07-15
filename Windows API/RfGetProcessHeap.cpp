HANDLE RfGetProcessHeap(VOID)
{
	return GetPeb()->ProcessHeap;
}
