#include "Win32Helper.h"

BOOL GetDomainNameFromIPV4AddressAsStringW(_In_ PWCHAR IpAddress, _Inout_ PWCHAR DomainName)
{
    WSADATA WindowsSocketData = { 0 };
    BOOL bFlag = FALSE;
    SOCKADDR_IN AddressInformation = { 0 };

    if (WSAStartup(MAKEWORD(2, 2), &WindowsSocketData) != ERROR_SUCCESS)
        return FALSE;

    AddressInformation.sin_family = AF_INET;
    AddressInformation.sin_addr.S_un.S_addr = ConvertIPv4StringToUnsignedLongW(IpAddress);

    if (GetNameInfoW((CONST SOCKADDR*) & AddressInformation, sizeof(SOCKADDR), DomainName, 32, NULL, 0, NI_NUMERICSERV) != ERROR_SUCCESS)
        goto EXIT_ROUTINE;

    bFlag = TRUE;

EXIT_ROUTINE:

    WSACleanup();

    return bFlag;
}

BOOL GetDomainNameFromIPV4AddressAsStringA(_In_ PCHAR IpAddress, _Inout_ PCHAR DomainName)
{
    WSADATA WindowsSocketData = { 0 };
    BOOL bFlag = FALSE;
    SOCKADDR_IN AddressInformation = { 0 };

    if (WSAStartup(MAKEWORD(2, 2), &WindowsSocketData) != ERROR_SUCCESS)
        return FALSE;

    AddressInformation.sin_family = AF_INET;
    AddressInformation.sin_addr.S_un.S_addr = ConvertIPv4StringToUnsignedLongA(IpAddress);

    if (GetNameInfoA((CONST SOCKADDR*) & AddressInformation, sizeof(SOCKADDR), DomainName, 32, NULL, 0, NI_NUMERICSERV) != ERROR_SUCCESS)
        goto EXIT_ROUTINE;

    bFlag = TRUE;

EXIT_ROUTINE:

    WSACleanup();

    return bFlag;
}