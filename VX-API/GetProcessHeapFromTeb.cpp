#include "Win32Helper.h"

HANDLE GetProcessHeapFromTeb(VOID)
{
	return GetPeb()->ProcessHeap;
}