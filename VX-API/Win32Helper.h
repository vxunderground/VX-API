#pragma once
#include "Internal.h"
#include "StringManipulation.h"

#ifndef NT_SUCCESS
#define NT_SUCCESS(x) ((x)>=0)
#define STATUS_SUCCESS ((NTSTATUS)0)
#endif

#define Get16Bits(d) ((((UINT32)(((CONST UINT8*)(d))[1])) << 8) +(UINT32)(((CONST UINT8*)(d))[0]))

//error handling
DWORD GetLastErrorFromTeb(VOID);
NTSTATUS GetLastNtStatusEx(VOID);
VOID SetLastErrorInTeb(_In_ DWORD ErrorCode);
VOID SetLastNtStatusInTeb(_In_ NTSTATUS Status);
DWORD Win32FromHResult(_In_ HRESULT Result);

//cryptography related
DWORD HashStringDjb2A(_In_ PCHAR String);
DWORD HashStringDjb2W(_In_ PWCHAR String);
ULONG HashStringFowlerNollVoVariant1aA(_In_ PCHAR String);
ULONG HashStringFowlerNollVoVariant1aW(_In_ PWCHAR String);
UINT32 HashStringJenkinsOneAtATime32BitA(_In_ PCHAR String);
UINT32 HashStringJenkinsOneAtATime32BitW(_In_ PWCHAR String);
DWORD HashStringLoseLoseA(_In_ PCHAR String);
DWORD HashStringLoseLoseW(_In_ PWCHAR String);
INT HashStringRotr32A(_In_ PCHAR String);
INT HashStringRotr32W(_In_ PWCHAR String);
DWORD HashStringSdbmA(_In_ PCHAR String);
DWORD HashStringSdbmW(_In_ PWCHAR String);
UINT32 HashStringSuperFastHashA(_In_ PCHAR String);
UINT32 HashStringSuperFastHashW(_In_ PWCHAR String);
INT HashStringUnknownGenericHash1A(_In_ PCHAR String);
INT HashStringUnknownGenericHash1W(_In_ PWCHAR String);
BOOL CreateMd5HashFromFilePathW(_In_ PWCHAR FilePath, _Inout_ PWCHAR Md5Hash);
BOOL CreateMd5HashFromFilePathA(_In_ PCHAR FilePath, _Inout_ PCHAR Md5Hash);
INT CreatePseudoRandomInteger(_In_ ULONG Seed);
PWCHAR CreatePseudoRandomStringW(_In_ SIZE_T dwLength, _In_ ULONG Seed);
PCHAR CreatePseudoRandomStringA(_In_ SIZE_T dwLength, _In_ ULONG Seed);
BOOL HashFileByMsiFileHashTableW(_In_ PWCHAR Path, _Inout_ PULONG FileHash);
BOOL HashFileByMsiFileHashTableA(_In_ PCHAR Path, _Inout_ PULONG FileHash);


//library loading
PTEB GetTeb(VOID);
PPEB GetPeb(VOID);
PPEB GetPebFromTeb(VOID);
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
HMODULE GetModuleHandleEx2A(LPCSTR lpModuleName);
HMODULE GetModuleHandleEx2W(LPCWSTR lpModuleName);

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
BOOL MasqueradePebAsExplorer(VOID);
BOOL CreateFileFromDsCopyFromSharedFileW(PWCHAR NewFileName, PWCHAR FileToClone);
BOOL CreateFileFromDsCopyFromSharedFileA(PCHAR NewFileName, PCHAR FileToClone);
BOOL UacBypassFodHelperMethodA(PCHAR PathToBinaryToExecute, PPROCESS_INFORMATION Pi);
BOOL UacBypassFodHelperMethodW(PWCHAR PathToBinaryToExecute, PPROCESS_INFORMATION Pi);
BOOL DelayedExecutionExecuteOnDisplayOff(VOID);
DWORD CreateProcessFromShellExecuteInExplorerProcessW(_In_ PWCHAR BinaryPath);
DWORD CreateProcessFromShellExecuteInExplorerProcessA(_In_ PCHAR BinaryPath);
DWORD CreateProcessFromIShellDispatchInvokeW(_In_ PWCHAR BinaryPath);
DWORD CreateProcessFromIShellDispatchInvokeA(_In_ PCHAR BinaryPath);
DWORD CreateProcessViaNtCreateUserProcessW(PWCHAR FullBinaryPath);
DWORD CreateProcessViaNtCreateUserProcessA(PCHAR FullBinaryPath);

//antidebug
BOOL AdfCloseHandleOnInvalidAddress(VOID);
BOOL AdfIsCreateProcessDebugEventCodeSet(VOID);
BOOL AdfOpenProcessOnCsrss(VOID);
BOOL IsIntelHardwareBreakpointPresent(VOID);
BOOL CheckRemoteDebuggerPresentEx(HANDLE hHandle, PBOOL pbDebuggerPresent);
BOOL IsDebuggerPresentEx(VOID);