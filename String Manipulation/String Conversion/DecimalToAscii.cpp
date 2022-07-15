DWORD DecimalToAsciiA(PCHAR String, LPDWORD dwArray, DWORD dwLength)
{
	DWORD dwX = ERROR_SUCCESS;

	if (String == NULL)
		return dwX;

	for (; dwX < dwLength; dwX++) { String[dwX] = (CHAR)dwArray[dwX]; }

	return dwX;
}

DWORD DecimalToAsciiW(PWCHAR String, LPDWORD dwArray, DWORD dwLength)
{
	DWORD dwX = ERROR_SUCCESS;

	if (String == NULL)
		return dwX;

	for (; dwX < dwLength; dwX++) { String[dwX] = (WCHAR)dwArray[dwX]; }

	return dwX;
}
