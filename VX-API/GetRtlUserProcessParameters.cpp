#include "Win32Helper.h"

PRTL_USER_PROCESS_PARAMETERS GetRtlUserProcessParameters(VOID)
{
	return GetPeb()->ProcessParameters;
}