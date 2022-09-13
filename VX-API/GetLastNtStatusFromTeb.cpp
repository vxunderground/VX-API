#include "Win32Helper.h"

NTSTATUS GetLastNtStatusFromTeb(VOID)
{
	return GetTeb()->LastStatusValue;
}