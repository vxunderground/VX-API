PWCHAR StringConcatW(PWCHAR String, PWCHAR String2)
{
	StringCopyW(&String[StringLengthW(String)], String2);

	return String;
}

PCHAR StringConcatA(PCHAR String, PCHAR String2)
{
	StringCopyA(&String[StringLengthA(String)], String2);

	return String;
}
