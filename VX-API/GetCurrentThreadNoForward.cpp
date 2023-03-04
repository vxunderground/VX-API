#include "Win32Helper.h"

HANDLE GetCurrentThreadNoForward(VOID)
{
	return ((HANDLE)(LONG_PTR)-2);
}