PCHAR StringLocateCharA(PCHAR String, INT Character)
{
	do
	{
		if (*String == Character)
			return (PCHAR)String;

	} while (*String++);

	return NULL;
}

PWCHAR StringLocateCharW(PWCHAR String, INT Character)
{
	do
	{
		if (*String == Character)
			return (PWCHAR)String;

	} while (*String++);

	return NULL;
}
