#include "Win32Helper.h"

NTSTATUS GetLastNtStatusEx(VOID)
{
	return GetTeb()->LastStatusValue;
}