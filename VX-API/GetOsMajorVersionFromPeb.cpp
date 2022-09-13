#include "Win32Helper.h"

ULONG GetOsMajorVersionFromPeb(VOID)
{
	return GetPeb()->OSMajorVersion;
}