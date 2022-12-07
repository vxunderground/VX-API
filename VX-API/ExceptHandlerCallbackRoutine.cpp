#include "Win32Helper.h"

LONG ExceptionHandlerCallbackRoutine(_In_ PEXCEPTION_POINTERS ExceptionInfo)
{
    DESCRIPTOR_ENTRY *TempObject = { 0 };
    BOOL bResolved = FALSE;

    if (ExceptionInfo->ExceptionRecord->ExceptionCode != STATUS_SINGLE_STEP)
        goto EXIT_ROUTINE;

    EnterCriticalSection(&CriticalSection);

    TempObject = Head;

    while (TempObject != NULL)
    {
        if (TempObject->Address == ExceptionInfo->ContextRecord->Rip)
        {
            if (TempObject->Tid != 0 && TempObject->Tid != GetCurrentThreadId()) //need to fix
                continue;

            if (TempObject->Dis)
            {
                if (!SetHardwareBreakpoint(GetCurrentThreadId(), TempObject->Address, TempObject->Position, FALSE))
                    goto EXIT_ROUTINE;
            }

            TempObject->CallbackRoutine(ExceptionInfo);

            if (TempObject->Dis)
            {
                if (!SetHardwareBreakpoint(GetCurrentThreadId(), TempObject->Address, TempObject->Position, TRUE))
                    goto EXIT_ROUTINE;
            }
        }
        TempObject = TempObject->Next;
    }

    LeaveCriticalSection(&CriticalSection);

    bResolved = TRUE;

EXIT_ROUTINE:

    return (bResolved ? EXCEPTION_CONTINUE_EXECUTION : EXCEPTION_CONTINUE_SEARCH);
}