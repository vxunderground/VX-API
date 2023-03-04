#include "Win32Helper.h"

BOOL IsProcessRunningAsAdmin(VOID)
{
	HANDLE hToken = NULL;
	TOKEN_ELEVATION Elevation = { 0 };
	DWORD dwSize = 0;
	BOOL bFlag = FALSE;

	if (!OpenProcessToken(GetCurrentProcessNoForward(), TOKEN_QUERY, &hToken))
		goto EXIT_ROUTINE;

	if (!GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &dwSize))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (!bFlag)
		SetLastErrorInTeb(ERROR_ACCESS_DENIED);

	if (hToken)
		CloseHandle(hToken);

	return (bFlag ? Elevation.TokenIsElevated : FALSE);
}