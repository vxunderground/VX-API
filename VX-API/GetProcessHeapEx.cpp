#include "Win32Helper.h"

HANDLE GetProcessHeapEx(VOID)
{
	return GetPeb()->ProcessHeap;
}