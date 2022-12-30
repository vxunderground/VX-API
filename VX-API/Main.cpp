#include "Win32Helper.h"

INT main(VOID)
{
	PCHAR Buffer = NULL;
	DWORD dwSize = 0;
	HMODULE hMod = NULL;
	BYTE CompressedBuffer[512] = { 0 };
	ULONG Size = 512;
	ULONG Out = 0;

	BYTE DecompressedBuffer[512] = { 0 };

	Buffer = GenericShellcodeOpenCalcExitThread(&dwSize);

	Out = LzStandardCompressBuffer((PBYTE)Buffer, dwSize, CompressedBuffer, Size);

	Out = LzStandardDecompressBuffer(CompressedBuffer, Out, DecompressedBuffer, Size);

	if (Buffer)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Buffer);

	return ERROR_SUCCESS;
}

