#include "Win32Helper.h"

INT main(VOID)
{
	PCHAR Buffer = NULL;
	DWORD dwSize = 0;
	HMODULE hMod = NULL;

	Buffer = GenericShellcodeOpenCalcExitThread(&dwSize);

	//MpfPiControlInjection((PBYTE)Buffer, dwSize, 19768);

	//MpfSceViaInitOnceExecuteOnce((PBYTE)Buffer, dwSize);

	if (Buffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Buffer);

	return ERROR_SUCCESS;
}

