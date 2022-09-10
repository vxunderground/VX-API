#include "Win32Helper.h"

VOID SetLastErrorEx(DWORD ErrorCode)
{
	GetTeb()->LastErrorValue = ErrorCode;
}