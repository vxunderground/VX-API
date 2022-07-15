INT StringCompareStringRegionA(PCHAR String1, PCHAR String2, SIZE_T Count)
{
	UCHAR Block1, Block2;
	while (Count-- > 0)
	{
		Block1 = (UCHAR)*String1++;
		Block2 = (UCHAR)*String2++;

		if (Block1 != Block2)
			return Block1 - Block2;

		if (Block1 == '\0')
			return 0;
	}

	return 0;
}

INT StringCompareStringRegionW(PWCHAR String1, PWCHAR String2, SIZE_T Count)
{
	UCHAR Block1, Block2;
	while (Count-- > 0)
	{
		Block1 = (UCHAR)*String1++;
		Block2 = (UCHAR)*String2++;

		if (Block1 != Block2)
			return Block1 - Block2;

		if (Block1 == '\0')
			return 0;
	}

	return 0;
}


PCHAR StringFindSubstringA(PCHAR String1, PCHAR String2)
{
	PCHAR pPointer = String1;
	DWORD Length = (DWORD)StringLengthA(String2);

	for (; (pPointer = StringLocateCharA(pPointer, *String2)) != 0; pPointer++)
	{
		if (StringCompareStringRegionA(pPointer, String2, Length) == 0)
			return (PCHAR)pPointer;
	}

	return NULL;
}

PWCHAR StringFindSubstringW(PWCHAR String1, PWCHAR String2)
{
	PWCHAR pPointer = String1;
	DWORD Length = (DWORD)StringLengthW(String2);

	for (; (pPointer = StringLocateCharW(pPointer, *String2)) != 0; pPointer++)
	{
		if (StringCompareStringRegionW(pPointer, String2, Length) == 0)
			return (PWCHAR)pPointer;
	}

	return NULL;
}
