#include "Win32Helper.h"

VOID HeapFreeInterceptionRoutine(PEXCEPTION_POINTERS ExceptionInfo)
{
	CONST DWORD dwSize = (DWORD)HeapSize((HANDLE)ExceptionInfo->ContextRecord->Rcx, (DWORD)ExceptionInfo->ContextRecord->Rdx, (LPCVOID)ExceptionInfo->ContextRecord->R8);

	if (dwSize)
		ZeroMemoryEx((PVOID)ExceptionInfo->ContextRecord->R8, dwSize);

	ExceptionInfo->ContextRecord->EFlags |= (1 << 16);
}

BOOL HookEngineUnhookHeapFree(_In_ BOOL StartEngine)
{
	if (StartEngine)
	{
		if (!GlobalHardwareBreakpointObject.IsInit)
			InitHardwareBreakpointEngine();
	}

	return InsertDescriptorEntry((PUINT_VAR_T)&HeapFree, 0, HeapFreeInterceptionRoutine, 0, FALSE);
}

BOOL HookEngineRestoreHeapFree(_In_ BOOL ShutdownEngine)
{
	if (!GlobalHardwareBreakpointObject.IsInit)
		return FALSE;

	RemoveDescriptorEntry((PUINT_VAR_T)&HeapFree, 0);

	if (ShutdownEngine)
		return ShutdownHardwareBreakpointEngine();

	return TRUE;
}

