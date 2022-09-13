#include "Win32Helper.h"

DWORD GetCurrentProcessIdFromTeb(VOID)
{
	return HandleToUlong(GetTeb()->ClientId.UniqueProcess);
}