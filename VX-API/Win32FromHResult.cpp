#include "Win32Helper.h"

DWORD Win32FromHResult(_In_ HRESULT Result)
{
	if ((Result & 0xFFFF0000) == MAKE_HRESULT(SEVERITY_ERROR, FACILITY_WIN32, 0))
		return HRESULT_CODE(Result);

	if (Result == S_OK)
		return ERROR_SUCCESS;

	return ERROR_CAN_NOT_COMPLETE;
}