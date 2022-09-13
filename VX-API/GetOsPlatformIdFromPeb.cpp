#include "Win32Helper.h"

ULONG GetOsPlatformIdFromPeb(VOID)
{
	return GetPeb()->OSPlatformId;
}