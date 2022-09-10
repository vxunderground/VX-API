#include "Win32Helper.h"

VOID SetLastNtStatusEx(NTSTATUS Status)
{
	GetTeb()->LastStatusValue = Status;
}