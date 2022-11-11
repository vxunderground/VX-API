#include "Win32Helper.h"

#include <stdio.h>

BOOL GetDomainNameFromUnsignedLongIPV4AddressW(_In_ ULONG IpAddress, _Inout_ PWCHAR DomainName)
{
    WSADATA WindowsSocketData = { 0 };
    BOOL bFlag = FALSE;
    SOCKADDR_IN AddressInformation = { 0 };

    if (WSAStartup(MAKEWORD(2, 2), &WindowsSocketData) != ERROR_SUCCESS)
        return FALSE;

    AddressInformation.sin_family = AF_INET;
    AddressInformation.sin_addr.S_un.S_addr = IpAddress;

    if (GetNameInfoW((CONST SOCKADDR*) & AddressInformation, sizeof(SOCKADDR), DomainName, 32, NULL, 0, NI_NUMERICSERV) != ERROR_SUCCESS)
        goto EXIT_ROUTINE;

    bFlag = TRUE;

EXIT_ROUTINE:

    WSACleanup();

    return bFlag;
}

BOOL GetDomainNameFromUnsignedLongIPV4AddressA(_In_ ULONG IpAddress, _Inout_ PCHAR DomainName)
{
    WSADATA WindowsSocketData = { 0 };
    BOOL bFlag = FALSE;
    SOCKADDR_IN AddressInformation = { 0 };

    if (WSAStartup(MAKEWORD(2, 2), &WindowsSocketData) != ERROR_SUCCESS)
        return FALSE;

    AddressInformation.sin_family = AF_INET;
    AddressInformation.sin_addr.S_un.S_addr = IpAddress;

    if (GetNameInfoA((CONST SOCKADDR*) & AddressInformation, sizeof(SOCKADDR), DomainName, 32, NULL, 0, NI_NUMERICSERV) != ERROR_SUCCESS)
        goto EXIT_ROUTINE;

    bFlag = TRUE;

EXIT_ROUTINE:

    WSACleanup();

    return bFlag;
}