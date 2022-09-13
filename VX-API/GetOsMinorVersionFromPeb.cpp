#include "Win32Helper.h"

ULONG GetOsMinorVersionFromPeb(VOID)
{
	return GetPeb()->OSMinorVersion;
}