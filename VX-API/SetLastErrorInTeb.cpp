#include "Win32Helper.h"

VOID SetLastErrorInTeb(_In_ DWORD ErrorCode)
{
	GetTeb()->LastErrorValue = ErrorCode;
}