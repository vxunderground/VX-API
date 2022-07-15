INT HashStringUnknownGenericHash1A(PCHAR String)
{
	PCHAR Pointer;
	INT Generic;
	INT Hash = 0;

	for (Pointer = String; *Pointer != '\0'; Pointer++)
	{
		Hash = (Hash << 4) + (INT)(*Pointer);
		Generic = Hash & 0xF0000000L;

		if (Generic != 0)
			Hash = Hash ^ (Generic >> 24);

		Hash = Hash & ~Generic;
	}

	return Hash;
}

INT HashStringUnknownGenericHash1W(PWCHAR String)
{
	PWCHAR Pointer;
	INT Generic;
	INT Hash = 0;

	for (Pointer = String; *Pointer != '\0'; Pointer++)
	{
		Hash = (Hash << 4) + (INT)(*Pointer);
		Generic = Hash & 0xF0000000L;

		if (Generic != 0)
			Hash = Hash ^ (Generic >> 24);

		Hash = Hash & ~Generic;
	}

	return Hash;
}
