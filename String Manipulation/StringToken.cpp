PCHAR StringTokenA(PCHAR String, CONST PCHAR Delim)
{
	PCHAR Last;
	PCHAR SpanP, Token;
	INT C, SC;

	if (String == NULL)
		return NULL;

CONTINUE:

	C = *String++;

	for (SpanP = (PCHAR)Delim; (SC = *SpanP++) != ERROR_SUCCESS;)
	{
		if (C == SC)
			goto CONTINUE;
	}

	if (C == ERROR_SUCCESS) { Last = NULL; return NULL; }

	Token = String - 1;

	for (;;)
	{
		C = *String++;
		SpanP = (PCHAR)Delim;

		do {
			if ((SC = *SpanP++) == C)
			{
				if (C == ERROR_SUCCESS)
					String = NULL;
				else
					String[-1] = '\0';

				Last = String;
				return Token;
			}
		} while (SC != ERROR_SUCCESS);
	}

	return NULL;

}

PWCHAR StringTokenW(PWCHAR String, CONST PWCHAR Delim)
{
	PWCHAR Last;
	PWCHAR SpanP, Token;
	INT C, SC;

	if (String == NULL)
		return NULL;

CONTINUE:

	C = *String++;

	for (SpanP = (PWCHAR)Delim; (SC = *SpanP++) != ERROR_SUCCESS;)
	{
		if (C == SC)
			goto CONTINUE;
	}

	if (C == ERROR_SUCCESS) { Last = NULL; return NULL; }

	Token = String - 1;

	for (;;)
	{
		C = *String++;
		SpanP = (PWCHAR)Delim;

		do {
			if ((SC = *SpanP++) == C)
			{
				if (C == ERROR_SUCCESS)
					String = NULL;
				else
					String[-1] = '\0';

				Last = String;
				return Token;
			}
		} while (SC != ERROR_SUCCESS);
	}

	return NULL;

}
