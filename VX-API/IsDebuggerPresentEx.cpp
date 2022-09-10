#include "Win32Helper.h"

BOOL IsDebuggerPresentEx(VOID)
{
	return GetPeb()->BeingDebugged;
}