#include "Win32Helper.h"

BOOL InsertDescriptorEntry(_In_ PUINT_VAR_T Address, _In_ DWORD Position, _In_ EXCEPTION_CALLBACK CallbackRoutine, _In_ DWORD Tid, _In_ BOOL Dis)
{
	DESCRIPTOR_ENTRY *NewEntry = NULL;
	DWORD Index = ERROR_SUCCESS;

	NewEntry = (DESCRIPTOR_ENTRY*)HeapAlloc(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, sizeof(DESCRIPTOR_ENTRY));
	if (NewEntry == NULL)
		return FALSE;

	EnterCriticalSection(&CriticalSection);

	NewEntry->Address = Address;
	NewEntry->Position = Index;
	NewEntry->Tid = Tid;
	NewEntry->CallbackRoutine = CallbackRoutine;
	NewEntry->Dis = Dis;
	NewEntry->Next = Head;
	NewEntry->Previous = NULL;

	if (Head != NULL)
		Head->Previous = NewEntry;

	Head = NewEntry;

	LeaveCriticalSection(&CriticalSection);

	return SnapshotInsertHardwareBreakpointHookIntoTargetThread(Address, Index, TRUE, Tid);
}