#include "Win32Helper.h"

BOOL SendIcmpEchoMessageToIPv4HostW(
	_In_ PWCHAR IpAddress,					// IP address to ping
	_Inout_ PDWORD Status,					// Returns Status of ping, OPTIONAL
	_Inout_ PDWORD RoundTripTime,			// Returns Roundtrip time, OPTIONAL
	_Inout_ PWCHAR EchoReplyAddress)		// IP address that responded, must be 32 char long, OPTIONAL
{
	HANDLE IcmpHandle = NULL;
	ULONG IpAddressValue = ERROR_SUCCESS, dwReturnValue = ERROR_SUCCESS, ReplySize = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	CHAR IcmpMessage[32] = "Message";
	LPVOID IcmpResponseMessage = NULL;
	PICMP_ECHO_REPLY EchoReplyObject = NULL;
	IN_ADDR ReplyAddressInformation = { 0 };

	if (IpAddress == NULL)
		goto EXIT_ROUTINE;

	IpAddressValue = ConvertIPv4StringToUnsignedLongW(IpAddress);
	if (IpAddressValue == 0)
		goto EXIT_ROUTINE;

	IcmpHandle = IcmpCreateFile();
	if (IcmpHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;
	
	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(IcmpMessage);
	IcmpResponseMessage = HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, ReplySize);
	if (IcmpResponseMessage == NULL)
		goto EXIT_ROUTINE;

#pragma warning( push )
#pragma warning( disable : 28020)
	if(IcmpSendEcho(IcmpHandle, IpAddressValue, IcmpMessage, sizeof(IcmpMessage), NULL, IcmpResponseMessage, ReplySize, 1000))
	{
#pragma warning( pop ) 
		EchoReplyObject = (PICMP_ECHO_REPLY)IcmpResponseMessage;

		if(Status)
			*Status = EchoReplyObject->Status;

		if (RoundTripTime)
			*RoundTripTime = EchoReplyObject->RoundTripTime;

		if (EchoReplyAddress)
		{
			ReplyAddressInformation.S_un.S_addr = EchoReplyObject->Address;
			ConvertIPv4IpAddressStructureToStringW(&ReplyAddressInformation, EchoReplyAddress);
		}

		bFlag = TRUE;
	}

EXIT_ROUTINE:

	if (IcmpHandle)
		IcmpCloseHandle(IcmpHandle);

	if (IcmpResponseMessage)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, IcmpResponseMessage);

	return bFlag;
}

BOOL SendIcmpEchoMessageToIPv4HostA(
	_In_ PCHAR IpAddress,					// IP address to ping
	_Inout_ PDWORD Status,					// Returns Status of ping, OPTIONAL
	_Inout_ PDWORD RoundTripTime,			// Returns Roundtrip time, OPTIONAL
	_Inout_ PCHAR EchoReplyAddress)		// IP address that responded, must be 32 char long, OPTIONAL
{
	HANDLE IcmpHandle = NULL;
	ULONG IpAddressValue = ERROR_SUCCESS, dwReturnValue = ERROR_SUCCESS, ReplySize = ERROR_SUCCESS;
	BOOL bFlag = FALSE;
	CHAR IcmpMessage[32] = "Message";
	LPVOID IcmpResponseMessage = NULL;
	PICMP_ECHO_REPLY EchoReplyObject = NULL;
	IN_ADDR ReplyAddressInformation = { 0 };

	if (IpAddress == NULL)
		goto EXIT_ROUTINE;

	IpAddressValue = ConvertIPv4StringToUnsignedLongA(IpAddress);
	if (IpAddressValue == 0)
		goto EXIT_ROUTINE;

	IcmpHandle = IcmpCreateFile();
	if (IcmpHandle == INVALID_HANDLE_VALUE)
		goto EXIT_ROUTINE;

	ReplySize = sizeof(ICMP_ECHO_REPLY) + sizeof(IcmpMessage);
	IcmpResponseMessage = HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, ReplySize);
	if (IcmpResponseMessage == NULL)
		goto EXIT_ROUTINE;

#pragma warning( push )
#pragma warning( disable : 28020)
	if (IcmpSendEcho(IcmpHandle, IpAddressValue, IcmpMessage, sizeof(IcmpMessage), NULL, IcmpResponseMessage, ReplySize, 1000))
	{
#pragma warning( pop ) 
		EchoReplyObject = (PICMP_ECHO_REPLY)IcmpResponseMessage;

		if (Status)
			*Status = EchoReplyObject->Status;

		if (RoundTripTime)
			*RoundTripTime = EchoReplyObject->RoundTripTime;

		if (EchoReplyAddress)
		{
			ReplyAddressInformation.S_un.S_addr = EchoReplyObject->Address;
			ConvertIPv4IpAddressStructureToStringA(&ReplyAddressInformation, EchoReplyAddress);
		}

		bFlag = TRUE;
	}

EXIT_ROUTINE:

	if (IcmpHandle)
		IcmpCloseHandle(IcmpHandle);

	if (IcmpResponseMessage)
		HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, IcmpResponseMessage);

	return bFlag;
}