#include "Win32Helper.h"

BOOL SnapshotInsertHardwareBreakpointHookIntoTargetThread(_In_ PUINT_VAR_T Address, _In_ DWORD Position, _In_ BOOL Init, _In_ DWORD Tid)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	BOOL bFlag = FALSE;
	THREADENTRY32 Entry = { 0 };
	Entry.dwSize = sizeof(THREADENTRY32);

	hHandle = CreateToolhelp32Snapshot(TH32CS_SNAPTHREAD, 0);
	if (hHandle == INVALID_HANDLE_VALUE)
		Sleep(1);

	if (!Thread32Next(hHandle, &Entry))
		goto EXIT_ROUTINE;

	do {
		if ((Entry.dwSize >= FIELD_OFFSET(THREADENTRY32, th32OwnerProcessID) + sizeof(Entry.th32OwnerProcessID)) && Entry.th32OwnerProcessID == GetCurrentProcessIdFromTeb())
		{
			if (Tid != 0 && Tid != Entry.th32ThreadID)
				continue;

			if (!SetHardwareBreakpoint(Entry.th32ThreadID, Address, Position, Init))
				goto EXIT_ROUTINE;
		}

		Entry.dwSize = sizeof(Entry);

	} while (Thread32Next(hHandle, &Entry));


	bFlag = TRUE;

EXIT_ROUTINE:

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}