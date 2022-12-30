#include "Win32Helper.h"

ULONG LzMaximumDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes)
{
	RTLDECOMPRESSBUFFER RtlDecompressBuffer = NULL;
	HMODULE hMod = NULL;
	NTSTATUS Status = STATUS_SUCCESS;
	USHORT CompressionFormatAndEngine = COMPRESSION_FORMAT_LZNT1 | COMPRESSION_ENGINE_MAXIMUM;
	ULONG FinalDecompressedSize = 0;

	hMod = GetModuleHandleEx2W(L"ntdll.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	RtlDecompressBuffer = (RTLDECOMPRESSBUFFER)GetProcAddressA((DWORD64)hMod, "RtlDecompressBuffer");
	if (!RtlDecompressBuffer)
		goto EXIT_ROUTINE;

	Status = RtlDecompressBuffer(CompressionFormatAndEngine, DecompressedBuffer, DecompressedBufferSizeInBytes, CompressedBuffer, SizeOfCompressedBufferInBytes, &FinalDecompressedSize);
	if (Status != STATUS_SUCCESS)
		goto EXIT_ROUTINE;

EXIT_ROUTINE:

	return FinalDecompressedSize;
}