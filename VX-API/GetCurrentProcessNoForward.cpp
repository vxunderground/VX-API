#include "Win32Helper.h"

HANDLE GetCurrentProcessNoForward(VOID)
{
	return (HANDLE)((HANDLE)-1);
}