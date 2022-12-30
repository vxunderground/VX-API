#include "Win32Helper.h"

ULONG XpressHuffStandardCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes)
{
	RTLCOMPRESSBUFFER RtlCompressBuffer = NULL;
	RTLGETCOMPRESSIONWORKSPACESIZE RtlGetCompressionWorkSpaceSize = NULL;
	HMODULE hMod = NULL;
	NTSTATUS Status = STATUS_SUCCESS;
	USHORT CompressionFormatAndEngine = COMPRESSION_FORMAT_XPRESS_HUFF | COMPRESSION_ENGINE_STANDARD;
	ULONG CompressBufferWorkSpaceSize = 0;
	ULONG CompressFragmentWorkSpaceSize = 0;
	PVOID Workspace = NULL;
	ULONG FinalCompressedSize = 0;

	hMod = GetModuleHandleEx2W(L"ntdll.dll");
	if (hMod == NULL)
		goto EXIT_ROUTINE;

	RtlCompressBuffer = (RTLCOMPRESSBUFFER)GetProcAddressA((DWORD64)hMod, "RtlCompressBuffer");
	RtlGetCompressionWorkSpaceSize = (RTLGETCOMPRESSIONWORKSPACESIZE)GetProcAddressA((DWORD64)hMod, "RtlGetCompressionWorkSpaceSize");

	if (!RtlCompressBuffer || !RtlGetCompressionWorkSpaceSize)
		goto EXIT_ROUTINE;

	Status = RtlGetCompressionWorkSpaceSize(CompressionFormatAndEngine, &CompressBufferWorkSpaceSize, &CompressFragmentWorkSpaceSize);
	if (Status != STATUS_SUCCESS)
		goto EXIT_ROUTINE;

	if (CompressBufferWorkSpaceSize == 0)
		goto EXIT_ROUTINE;

	Workspace = HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, CompressBufferWorkSpaceSize);
	if (Workspace == NULL)
		goto EXIT_ROUTINE;

	Status = RtlCompressBuffer(CompressionFormatAndEngine, UncompressedBuffer, SizeOfUncompressedBufferInBytes, CompressedBuffer, CompressedBufferSizeInBytes, 4096, &FinalCompressedSize, Workspace);
	if (Status != STATUS_SUCCESS)
		goto EXIT_ROUTINE;

EXIT_ROUTINE:

	if (Workspace)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, Workspace);

	return FinalCompressedSize;
}