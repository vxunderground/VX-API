DWORD HashStringDjb2A(PCHAR String)
{
	ULONG Hash = 5381;
	INT c;

	while (c = *String++)
		Hash = ((Hash << 5) + Hash) + c;

	return Hash;
}

DWORD HashStringDjb2W(PWCHAR String)
{
	ULONG Hash = 5381;
	INT c;

	while (c = *String++)
		Hash = ((Hash << 5) + Hash) + c;

	return Hash;
}
