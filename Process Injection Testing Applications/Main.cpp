#include <Windows.h>
#include <stdio.h>

BOOL PrintBanner(VOID)
{
	
	puts("");
	puts("       vx-underground.org Process Injection Testing Application (PITA)");
	puts("");
	puts("\t8b           d8  8b        d8  88        88    ,ad8888ba,   ");
	puts("\t`8b         d8'   Y8,    ,8P   88        88   d8\"'    `\"8b  ");
	puts("\t `8b       d8'     `8b  d8'    88        88  d8'            ");
	puts("\t  `8b     d8'        Y88P      88        88  88             ");
	puts("\t   `8b   d8'         d88b      88        88  88      88888  ");
	puts("\t    `8b d8'        ,8P  Y8,    88        88  Y8,        88  ");
	puts("\t     `888'        d8'    `8b   Y8a.   . a8P   Y8a.     a88  ");
	puts("\t      `8'        8P        Y8   `\"Y8888Y\"'     `\"Y88888P\"");
	puts("");
	
	puts("   Built for process injection testing && based on the research conducted by SafeBreach Labs");
	puts("");
	puts("");

	return TRUE;
}

DWORD WndProcCallbackRoutine(_In_ LPVOID lpParameter)
{
	MSG Msg;
	BOOL bRet;

	printf("Message loop Thread ID = %ld\r\n", GetCurrentThreadId());
	while ((bRet = GetMessage(&Msg, NULL, 0, 0)) != 0)
	{
		if (bRet == -1)
			return GetLastError();

		TranslateMessage(&Msg);
		DispatchMessageW(&Msg);
	}

	return (DWORD)Msg.wParam;
}

INT main(VOID)
{
	HANDLE hThread = NULL;
	PrintBanner();

	hThread = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)WndProcCallbackRoutine, NULL, 0, NULL);
	if (hThread == NULL)
		return GetLastError();

	while (TRUE)
	{
		printf("Process ID = %ld, Thread ID = %ld -- Application is in an alertable state\r\n", GetCurrentProcessId(), GetCurrentThreadId());
		SleepEx(10000, TRUE);
	}

	return ERROR_SUCCESS;
}