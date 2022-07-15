VOID CharArrayToByteArrayA(PCHAR Char, PBYTE Byte, DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
	{
		Byte[dwX] = (BYTE)Char[dwX];
	}
}

VOID CharArrayToByteArrayW(PWCHAR Char, PBYTE Byte, DWORD Length)
{
	for (DWORD dwX = 0; dwX < Length; dwX++)
	{
		Byte[dwX] = (BYTE)Char[dwX];
	}
}
