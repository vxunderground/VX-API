#include <Windows.h>
#include "Internal.h"
#include "StringManipulation.h"
#include "Win32Helper.h"


/*
TODO:
	- Ping with 'IcmpSendEcho2Ex'
	- PID stuff: https://www.mdsec.co.uk/2022/08/fourteen-ways-to-read-the-pid-for-the-local-security-authority-subsystem-service-lsass/
	- Run PE in memory https://papers.vx-underground.org/papers/Windows/Evasion%20-%20Systems%20Call%20and%20Memory%20Evasion/Executing%20a%20PE%20File%20in%20Memory.zip
	- Download file options: https://www.x86matthew.com/view_post?id=ntsockets
	- https://learn.microsoft.com/en-us/windows/win32/api/shlwapi/nf-shlwapi-shansitounicode
	- https://learn.microsoft.com/en-us/previous-versions/windows/internet-explorer/ie-developer/platform-apis/aa767757(v=vs.85)

KNOWN ISSUES
	- Work on In / Out / Inout in function calls
	- Various logic improvements
*/


int main(VOID)
{
	DWORD dwError = ERROR_SUCCESS;

	dwError = GetPidFromPidBruteForcingW((PWCHAR)L"cmd.exe");

	return dwError;
}

