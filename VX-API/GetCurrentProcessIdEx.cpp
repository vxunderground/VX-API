#include "Win32Helper.h"

DWORD GetCurrentProcessIdEx(VOID)
{
	return HandleToUlong(GetTeb()->ClientId.UniqueProcess);
}