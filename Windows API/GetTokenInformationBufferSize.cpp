DWORD GetTokenInformationBufferSize(HANDLE hToken)
{
	PTOKEN_GROUPS TokenGroup = NULL;
	DWORD dwReturn = ERROR_SUCCESS;

	GetTokenInformation(hToken, TokenGroups, (LPVOID)TokenGroup, 0, &dwReturn);

	return dwReturn;
}
