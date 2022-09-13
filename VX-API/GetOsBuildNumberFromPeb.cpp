#include "Win32Helper.h"

ULONG GetOsBuildNumberFromPeb(VOID)
{
	return GetPeb()->OSBuildNumber;
}