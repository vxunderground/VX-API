#include "Win32Helper.h"

BOOL SetHardwareBreakpoint(_In_ DWORD ThreadId, _In_ PUINT_VAR_T Address, _In_ UINT Position, _In_ BOOL Init)
{
	CONTEXT Context = { 0 }; Context.ContextFlags = CONTEXT_DEBUG_REGISTERS;
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	BOOL bFlag = FALSE;

	if (ThreadId != GetCurrentThreadId())
	{
		hHandle = OpenThread(THREAD_ALL_ACCESS, FALSE, ThreadId);
		if (hHandle == NULL)
			goto EXIT_ROUTINE;
	}
	else
		hHandle = GetCurrentThreadNoForward();

	if (!GetThreadContext(hHandle, &Context))
		goto EXIT_ROUTINE;

	if (Init)
	{
		(&Context.Dr0)[Position] = Address;
		Context.Dr7 &= ~(3ull << (16 + 4 * Position));
		Context.Dr7 &= ~(3ull << (18 + 4 * Position));
		Context.Dr7 |= 1ull << (2 * Position);
	}
	else {
		if ((&Context.Dr0)[Position] == Address)
		{
			Context.Dr7 &= ~(1ull << (2 * Position));
			(&Context.Dr0)[Position] = 0ull;
		}
	}

	if (!SetThreadContext(hHandle, &Context))
		goto EXIT_ROUTINE;

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}