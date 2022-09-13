#include "Win32Helper.h"

DWORD GetLastErrorFromTeb(VOID)
{
	return GetTeb()->LastErrorValue;
}