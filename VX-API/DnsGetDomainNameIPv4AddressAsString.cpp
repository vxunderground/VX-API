#include "Win32Helper.h"

DWORD DnsGetDomainNameIPv4AddressAsStringW(_In_ PWCHAR DomainName, _Inout_ PWCHAR IPv4IPAddress)
{
	DNS_STATUS Status = ERROR_SUCCESS;
	PDNS_RECORD DnsRecord = NULL;

	Status = DnsQuery_W(DomainName, DNS_TYPE_A, DNS_QUERY_BYPASS_CACHE, NULL, &DnsRecord, NULL);
	
	if (DnsRecord && DnsRecord->Data.A.IpAddress != 0)
		ConvertIPv4IpAddressUnsignedLongToStringW(DnsRecord->Data.A.IpAddress, IPv4IPAddress);

	if (DnsRecord)
		DnsRecordListFree(DnsRecord, DnsFreeRecordListDeep);

	return Status;
}

DWORD DnsGetDomainNameIPv4AddressAsStringA(_In_ PCHAR DomainName, _Inout_ PCHAR IPv4IPAddress)
{
	DNS_STATUS Status = ERROR_SUCCESS;
	PDNS_RECORD DnsRecord = NULL;

	Status = DnsQuery_A(DomainName, DNS_TYPE_A, DNS_QUERY_BYPASS_CACHE, NULL, &DnsRecord, NULL);

	if (DnsRecord && DnsRecord->Data.A.IpAddress != 0)
		ConvertIPv4IpAddressUnsignedLongToStringA(DnsRecord->Data.A.IpAddress, IPv4IPAddress);

	if (DnsRecord)
		DnsRecordListFree(DnsRecord, DnsFreeRecordListDeep);

	return Status;
}