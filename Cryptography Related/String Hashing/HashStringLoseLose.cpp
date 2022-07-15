DWORD HashStringLoseLoseA(PCHAR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash += c;

	return Hash;
}

DWORD HashStringLoseLoseW(PWCHAR String)
{
	ULONG Hash = 0;
	INT c;

	while (c = *String++)
		Hash += c;

	return Hash;
}
