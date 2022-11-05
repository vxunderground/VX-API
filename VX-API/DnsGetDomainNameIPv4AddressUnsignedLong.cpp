#include "Win32Helper.h"

ULONG DnsGetDomainNameIPv4AddressUnsignedLongW(_In_ PWCHAR DomainName)
{
	DNS_STATUS Status = ERROR_SUCCESS;
	PDNS_RECORD DnsRecord = NULL;
	ULONG ReturnValue = ERROR_SUCCESS;

	DnsQuery_W(DomainName, DNS_TYPE_A, DNS_QUERY_BYPASS_CACHE, NULL, &DnsRecord, NULL);

	if (DnsRecord && DnsRecord->Data.A.IpAddress != 0)
		ReturnValue = DnsRecord->Data.A.IpAddress;

	if (DnsRecord)
		DnsRecordListFree(DnsRecord, DnsFreeRecordListDeep);

	return ReturnValue;
}

ULONG DnsGetDomainNameIPv4AddressUnsignedLongA(_In_ PCHAR DomainName)
{
	DNS_STATUS Status = ERROR_SUCCESS;
	PDNS_RECORD DnsRecord = NULL;
	ULONG ReturnValue = ERROR_SUCCESS;

	DnsQuery_A(DomainName, DNS_TYPE_A, DNS_QUERY_BYPASS_CACHE, NULL, &DnsRecord, NULL);

	if (DnsRecord && DnsRecord->Data.A.IpAddress != 0)
		ReturnValue = DnsRecord->Data.A.IpAddress;

	if (DnsRecord)
		DnsRecordListFree(DnsRecord, DnsFreeRecordListDeep);

	return ReturnValue;
}