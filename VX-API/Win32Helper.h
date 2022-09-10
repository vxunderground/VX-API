#pragma once
#include "Internal.h"
#include "StringManipulation.h"

#ifndef NT_SUCCESS
#define NT_SUCCESS(x) ((x)>=0)
#define STATUS_SUCCESS ((NTSTATUS)0)
#endif

#define Get16Bits(d) ((((UINT32)(((CONST UINT8*)(d))[1])) << 8) +(UINT32)(((CONST UINT8*)(d))[0]))

//error handling
DWORD GetLastErrorEx(VOID);
NTSTATUS GetLastNtStatusEx(VOID);
VOID SetLastErrorEx(DWORD ErrorCode);
VOID SetLastNtStatusEx(NTSTATUS Status);
DWORD Win32FromHResult(HRESULT Result);

//cryptography related
DWORD HashStringDjb2A(PCHAR String);
DWORD HashStringDjb2W(PWCHAR String);
ULONG HashStringFowlerNollVoVariant1aA(PCHAR String);
ULONG HashStringFowlerNollVoVariant1aW(PWCHAR String);
UINT32 HashStringJenkinsOneAtATime32BitA(PCHAR String);
UINT32 HashStringJenkinsOneAtATime32BitW(PWCHAR String);
DWORD HashStringLoseLoseA(PCHAR String);
DWORD HashStringLoseLoseW(PWCHAR String);
INT HashStringRotr32A(PCHAR String);
INT HashStringRotr32W(PWCHAR String);
DWORD HashStringSdbmA(PCHAR String);
DWORD HashStringSdbmW(PWCHAR String);
UINT32 HashStringSuperFastHashA(PCHAR String);
UINT32 HashStringSuperFastHashW(PWCHAR String);
INT HashStringUnknownGenericHash1A(PCHAR String);
INT HashStringUnknownGenericHash1W(PWCHAR String);
INT CreatePseudoRandomInteger(ULONG Seed);
PWCHAR CreatePseudoRandomStringW(SIZE_T dwLength, ULONG Seed);
PCHAR CreatePseudoRandomStringA(SIZE_T dwLength, ULONG Seed);
BOOL HashFileByMsiFileHashTableW(PWCHAR Path, PULONG FileHash);
BOOL HashFileByMsiFileHashTableA(PCHAR Path, PULONG FileHash);

//library loading
PTEB GetTeb(VOID);
PPEB GetPeb(VOID);
PPEB GetPebEx(VOID);
PKUSER_SHARED_DATA GetKUserSharedData(VOID);
PRTL_USER_PROCESS_PARAMETERS GetRtlUserProcessParameters(VOID);
DWORD64 __stdcall GetProcAddressDjb2(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressFowlerNollVoVariant1a(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressJenkinsOneAtATime32Bit(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressLoseLose(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressRotr32(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressSdbm(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressSuperFastHash(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressUnknownGenericHash1(DWORD64 ModuleBase, DWORD64 Hash);
DWORD64 __stdcall GetProcAddressA(DWORD64 ModuleBase, LPCSTR lpProcName);
DWORD64 __stdcall GetProcAddressW(DWORD64 ModuleBase, LPCWSTR lpProcName);
BOOL RtlLoadPeHeaders(PIMAGE_DOS_HEADER* Dos, PIMAGE_NT_HEADERS* Nt, PIMAGE_FILE_HEADER* File, PIMAGE_OPTIONAL_HEADER* Optional, PBYTE* ImageBase);
HMODULE GetModuleHandleExA(LPCSTR lpModuleName);
HMODULE GetModuleHandleExW(LPCWSTR lpModuleName);

//helper functions
BOOL IsPathValidA(PCHAR FilePath);
BOOL IsPathValidW(PWCHAR FilePath);
BOOL CreateLocalAppDataObjectPathW(PWCHAR pBuffer, PWCHAR Path, DWORD Size, BOOL bDoesObjectExist);
BOOL CreateLocalAppDataObjectPathA(PCHAR pBuffer, PCHAR Path, DWORD Size, BOOL bDoesObjectExist);
BOOL GetSystemWindowsDirectoryA(DWORD nBufferLength, PCHAR lpBuffer);
BOOL GetSystemWindowsDirectoryW(DWORD nBufferLength, PWCHAR lpBuffer);
BOOL CreateWindowsObjectPathW(PWCHAR pBuffer, PWCHAR Path, DWORD Size, BOOL bDoesObjectExist);
BOOL CreateWindowsObjectPathA(PCHAR pBuffer, PCHAR Path, DWORD Size, BOOL bDoesObjectExist);
HANDLE GetProcessHeapEx(VOID);
HANDLE GetCurrentProcessEx(VOID);
LPWSTR GetCurrentUserSidW(HANDLE hToken, BOOL DisposeProcessHandle);
LPSTR GetCurrentUserSidA(HANDLE hToken, BOOL DisposeProcessHandle);
DWORD GetProcessPathFromLoaderLoadModuleA(DWORD nBufferLength, PCHAR lpBuffer);
DWORD GetProcessPathFromLoaderLoadModuleW(DWORD nBufferLength, PWCHAR lpBuffer);
DWORD GetProcessPathFromProcessParametersA(DWORD nBufferLength, PCHAR lpBuffer);
DWORD GetProcessPathFromProcessParametersW(DWORD nBufferLength, PWCHAR lpBuffer);
DWORD GetNumberOfLinkedDlls(VOID);
DWORD GetOSIdentificationData(DWORD Id);
BOOL IsNvidiaGraphicsCardPresentA(VOID);
BOOL IsNvidiaGraphicsCardPresentW(VOID);
BOOL IsProcessRunningA(PCHAR ProcessNameWithExtension, BOOL IsCaseSensitive);
BOOL IsProcessRunningW(PWCHAR ProcessNameWithExtension, BOOL IsCaseSensitive);
BOOL IsProcessRunningAsAdmin(VOID);
BOOL RecursiveFindFileA(LPCSTR Path, LPCSTR Pattern);
BOOL RecursiveFindFileW(LPCWSTR Path, LPCWSTR Pattern);
BOOL DeleteFileExA(PCHAR Path);
BOOL DeleteFileExW(PWCHAR Path);
DWORD GetCurrentDirectoryExA(DWORD nBufferLength, PCHAR lpBuffer);
DWORD GetCurrentDirectoryExW(DWORD nBufferLength, PWCHAR lpBuffer);
DWORD GetCurrentProcessIdEx(VOID);
HANDLE GetCurrentThreadEx(VOID);
DWORD GetCurrentWindowTextA(DWORD nBufferLength, PCHAR lpBuffer);
DWORD GetCurrentWindowTextW(DWORD nBufferLength, PWCHAR lpBuffer);
LONGLONG GetFileSizeFromPathW(PWCHAR Path, DWORD dwFlagsAndAttributes);
LONGLONG GetFileSizeFromPathA(PCHAR Path, DWORD dwFlagsAndAttributes);
BOOL RemoveDllFromPebA(LPCSTR lpModuleName);
BOOL RemoveDllFromPebW(LPCWSTR lpModuleName);
DWORD UrlDownloadToFileSynchronousW(PWCHAR Url, PWCHAR SavePath);
DWORD UrlDownloadToFileSynchronousA(PCHAR Url, PCHAR SavePath);
BOOL SetProcessPrivilegeToken(DWORD PrivilegeEnum);

//malicious capabilities
DWORD OleGetClipboardDataA(PCHAR Buffer);
DWORD OleGetClipboardDataW(PWCHAR Buffer);
DWORD MpfComVssDeleteShadowVolumeBackups(BOOL CoUninitializeAfterCompletion);
BOOL MpfComModifyShortcutTargetW(PWCHAR LnkPath, PWCHAR LnkExecutionProperty);
BOOL MpfComModifyShortcutTargetA(PCHAR LnkPath, PCHAR LnkExecutionProperty);

//evasion
BOOL CreateProcessWithCfGuardW(PPROCESS_INFORMATION Pi, PWCHAR Path);
BOOL CreateProcessWithCfGuardA(PPROCESS_INFORMATION Pi, PCHAR Path);
HRESULT CreateProcessFromIHxInteractiveUserW(PWCHAR UriFile);
HRESULT CreateProcessFromIHxInteractiveUserA(PCHAR UriFile);
HRESULT CreateProcessFromIHxHelpPaneServerW(PWCHAR UriFile);
HRESULT CreateProcessFromIHxHelpPaneServerA(PCHAR UriFile);
BOOL MasqueradePebAsExplorerEx(VOID);
BOOL CreateFileFromDsCopyFromSharedFileW(PWCHAR NewFileName, PWCHAR FileToClone);
BOOL CreateFileFromDsCopyFromSharedFileA(PCHAR NewFileName, PCHAR FileToClone);
BOOL UacBypassFodHelperMethodA(PCHAR PathToBinaryToExecute, PPROCESS_INFORMATION Pi);
BOOL UacBypassFodHelperMethodW(PWCHAR PathToBinaryToExecute, PPROCESS_INFORMATION Pi);
BOOL DelayedExecutionExecuteOnDisplayOff(VOID);

//antidebug
BOOL AdfCloseHandleOnInvalidAddress(VOID);
BOOL AdfIsCreateProcessDebugEventCodeSet(VOID);
BOOL AdfOpenProcessOnCsrss(VOID);
BOOL IsIntelHardwareBreakpointPresent(VOID);
BOOL CheckRemoteDebuggerPresentEx(HANDLE hHandle, PBOOL pbDebuggerPresent);
BOOL IsDebuggerPresentEx(VOID);