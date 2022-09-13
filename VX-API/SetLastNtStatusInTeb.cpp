#include "Win32Helper.h"

VOID SetLastNtStatusInTeb(_In_ NTSTATUS Status)
{
	GetTeb()->LastStatusValue = Status;
}