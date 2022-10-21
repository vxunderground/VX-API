#include "Win32Helper.h"

DWORD MpfGetLsaPidFromServiceManager(VOID)
{
	SC_HANDLE Manager = NULL, ServiceHandle = NULL;
	DWORD ProcessId = ERROR_SUCCESS, BytesNeeded = ERROR_SUCCESS;
	SERVICE_STATUS_PROCESS ServiceStatus = { 0 };

	Manager = OpenSCManagerW(NULL, NULL, SC_MANAGER_CONNECT);
	if (Manager == NULL)
		return 0;

	ServiceHandle = OpenServiceW(Manager, L"samss", SERVICE_QUERY_STATUS);
	if (ServiceHandle == NULL)
		goto EXIT_ROUTINE;

	if(!QueryServiceStatusEx(ServiceHandle, SC_STATUS_PROCESS_INFO, (LPBYTE)&ServiceStatus, sizeof(ServiceStatus), &BytesNeeded))
		goto EXIT_ROUTINE;

	ProcessId = ServiceStatus.dwProcessId;

EXIT_ROUTINE:

	if(ServiceHandle)
		CloseServiceHandle(ServiceHandle);

	if (Manager)
		CloseServiceHandle(Manager);

	return ProcessId;
}