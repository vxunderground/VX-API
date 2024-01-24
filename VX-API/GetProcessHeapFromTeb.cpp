#include "Win32Helper.h"

HANDLE GetProcessHeapFromPeb(VOID)
{
	return GetPeb()->ProcessHeap;
}
