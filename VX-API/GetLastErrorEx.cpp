#include "Win32Helper.h"

DWORD GetLastErrorEx(VOID)
{
	return GetTeb()->LastErrorValue;
}