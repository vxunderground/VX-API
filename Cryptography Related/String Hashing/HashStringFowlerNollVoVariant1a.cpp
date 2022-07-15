ULONG HashStringFowlerNollVoVariant1aA(PCHAR String)
{
	ULONG Hash = 0x811c9dc5;

	while (*String)
	{
		Hash ^= (UCHAR)*String++;
		Hash *= 0x01000193;
	}

	return Hash;
}

ULONG HashStringFowlerNollVoVariant1aW(PWCHAR String)
{
	ULONG Hash = 0x811c9dc5;

	while (*String)
	{
		Hash ^= (UCHAR)*String++;
		Hash *= 0x01000193;
	}

	return Hash;
}
