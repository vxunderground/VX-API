#include <Windows.h>
#include "Internal.h"
#include "StringManipulation.h"
#include "Win32Helper.h"
#include <initguid.h>

#pragma comment(lib, "shlwapi.lib")
/*
TODO:
	- Ping with 'IcmpSendEcho2Ex'

KNOWN ISSUES
	- Dynamically resolve IUnknown_QueryService in UnusedSubroutineGetShellViewForDesktop in CreateProcessFromShellExecuteInExplorerProcess
*/

int main(VOID)
{
	DWORD dwError = ERROR_SUCCESS;

	return ERROR_SUCCESS;
}

