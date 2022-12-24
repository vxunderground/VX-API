#include "Win32Helper.h"

INT main(VOID)
{
	PCHAR Buffer = NULL;
	DWORD dwSize = 0;

	Buffer = GenericShellcodeHelloWorldMessageBoxA(&dwSize);

	MpfSceViaMessageBoxIndirectW((PBYTE)Buffer, dwSize);

	if (Buffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Buffer);

	return ERROR_SUCCESS;
}

