#include "Win32Helper.h"

BOOL RemoveDescriptorEntry(_In_ PUINT_VAR_T Address, _In_ DWORD Tid)
{
	DESCRIPTOR_ENTRY *TempObject = NULL;
	DWORD Position = ERROR_SUCCESS;
	BOOL bFlag = FALSE, Found = FALSE;

	EnterCriticalSection(&CriticalSection);

	TempObject = Head;

	while (TempObject != NULL)
	{
		if (TempObject->Address == Address && TempObject->Tid == Tid)
		{
			Found = TRUE;

			Position = TempObject->Position;

			if (Head == TempObject)
				Head = TempObject->Next;

			if (TempObject->Next != NULL)
				TempObject->Next->Previous = TempObject->Previous;

			if (TempObject->Previous != NULL)
				TempObject->Previous->Next = TempObject->Next;

			if(TempObject)
				HeapFree(GetProcessHeapFromTeb(), HEAP_ZERO_MEMORY, TempObject);
		}

		if(TempObject)
			TempObject = TempObject->Next;
	}

	LeaveCriticalSection(&CriticalSection);

	if (Found)
		bFlag = SnapshotInsertHardwareBreakpointHookIntoTargetThread(Address, Position, FALSE, Tid);

	return bFlag;
}