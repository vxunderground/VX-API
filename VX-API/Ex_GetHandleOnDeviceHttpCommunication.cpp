#include "Win32Helper.h"

BOOL Ex_GetHandleOnDeviceHttpCommunication(_Out_ PHANDLE Handle)
{
	typedef struct HTTPCOMMUNICATIONEXTENDEDATTRIBUTES {
		DWORD dwUnknown1;
		WORD wUnknown2;
		WORD wUnknown3;
		BYTE bStr[16];
		WORD wVersionMajor;
		WORD wVersionMinor;
		DWORD dwFlags;
		QWORD qwCommsHandle;
		BYTE bUnknown4[3];
	}HTTPCOMMUNICATIONEXTENDEDATTRIBUTES, * PHTTPCOMMUNICATIONEXTENDEDATTRIBUTES;

	NTCREATEFILE NtCreateFile = NULL;
	HMODULE hModule = NULL;
	HTTPCOMMUNICATIONEXTENDEDATTRIBUTES Http = { 0 };
	UNICODE_STRING ObjectFilePath = { 0 };
	OBJECT_ATTRIBUTES Attributes = { 0 };
	IO_STATUS_BLOCK IoBlock = { 0 };
	NTSTATUS Status = ERROR_SUCCESS;
	HANDLE hHandle = NULL;

	*Handle = NULL;

	hModule = GetModuleHandleEx2W(L"ntdll.dll");
	if (hModule == NULL)
		return FALSE;

	NtCreateFile = (NTCREATEFILE)GetProcAddressA((DWORD64)hModule, "NtCreateFile");
	if (!NtCreateFile)
		return FALSE;

	Http.wUnknown2 = 0xF00;
	Http.wUnknown3 = 0x10;
	StringCopyA((PCHAR)Http.bStr, (PCHAR)"UlOpenPacket000");
	Http.wVersionMajor = 2;

	RtlInitUnicodeString(&ObjectFilePath, L"\\Device\\Http\\Communication");
	InitializeObjectAttributes(&Attributes, &ObjectFilePath, OBJ_CASE_INSENSITIVE, 0, NULL);

	Status = NtCreateFile(Handle, 0xC0100000, &Attributes, &IoBlock, NULL, 0, FILE_SHARE_READ | FILE_SHARE_WRITE, 2, 0, &Http, 0x2b);

	if (NT_SUCCESS(Status)) return TRUE; else return FALSE;
}