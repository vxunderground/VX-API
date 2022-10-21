#pragma once
#include "Internal.h"
#include "StringManipulation.h"

#ifndef NT_SUCCESS
#define NT_SUCCESS(x) ((x)>=0)
#define STATUS_SUCCESS ((NTSTATUS)0)
#endif

#define Get16Bits(d) ((((UINT32)(((CONST UINT8*)(d))[1])) << 8) +(UINT32)(((CONST UINT8*)(d))[0]))

#define InlineGetCurrentThread ((HANDLE)(LONG_PTR)-2)
#define InlineGetCurrentProcess (HANDLE)((HANDLE)-1)

//error handling
DWORD GetLastErrorFromTeb(VOID);
NTSTATUS GetLastNtStatusFromTeb(VOID);
VOID SetLastErrorInTeb(_In_ DWORD ErrorCode);
VOID SetLastNtStatusInTeb(_In_ NTSTATUS Status);
DWORD Win32FromHResult(_In_ HRESULT Result);
DWORD RtlNtStatusToDosErrorViaImport(_In_ NTSTATUS Status);

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
DWORD64 __stdcall GetProcAddressDjb2(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressFowlerNollVoVariant1a(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressJenkinsOneAtATime32Bit(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressLoseLose(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressRotr32(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressSdbm(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressSuperFastHash(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressUnknownGenericHash1(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 __stdcall GetProcAddressA(_In_ DWORD64 ModuleBase, _In_ LPCSTR lpProcName);
DWORD64 __stdcall GetProcAddressW(_In_ DWORD64 ModuleBase, _In_ LPCWSTR lpProcName);
BOOL RtlLoadPeHeaders(_Inout_ PIMAGE_DOS_HEADER* Dos, _Inout_ PIMAGE_NT_HEADERS* Nt, _Inout_ PIMAGE_FILE_HEADER* File, _Inout_ PIMAGE_OPTIONAL_HEADER* Optional, _Inout_ PBYTE* ImageBase);
HMODULE GetModuleHandleEx2A(_In_ LPCSTR lpModuleName);
HMODULE GetModuleHandleEx2W(_In_ LPCWSTR lpModuleName);

//helper functions
BOOL IsPathValidA(_In_ PCHAR FilePath);
BOOL IsPathValidW(_In_ PWCHAR FilePath);
BOOL CreateLocalAppDataObjectPathW(_Inout_ PWCHAR pBuffer, _In_ PWCHAR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist);
BOOL CreateLocalAppDataObjectPathA(_Inout_ PCHAR pBuffer, _In_ PCHAR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist);
BOOL GetSystemWindowsDirectoryA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
BOOL GetSystemWindowsDirectoryW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
BOOL CreateWindowsObjectPathW(_Inout_ PWCHAR pBuffer, _In_ PWCHAR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist);
BOOL CreateWindowsObjectPathA(_Inout_ PCHAR pBuffer, _In_ PCHAR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist);
HANDLE GetProcessHeapFromTeb(VOID);
LPWSTR GetCurrentUserSidW(VOID);
LPSTR GetCurrentUserSidA(VOID);
DWORD GetProcessPathFromLoaderLoadModuleA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
DWORD GetProcessPathFromLoaderLoadModuleW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
DWORD GetProcessPathFromUserProcessParametersA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
DWORD GetProcessPathFromUserProcessParametersW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
BOOL RecursiveFindFileA(_In_ LPCSTR Path, _In_ LPCSTR Pattern);
BOOL RecursiveFindFileW(_In_ LPCWSTR Path, _In_ LPCWSTR Pattern);
BOOL DeleteFileWithCreateFileFlagA(_In_ PCHAR Path);
BOOL DeleteFileWithCreateFileFlagW(_In_ PWCHAR Path);
DWORD GetCurrentDirectoryFromUserProcessParametersA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
DWORD GetCurrentDirectoryFromUserProcessParametersW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
DWORD GetCurrentProcessIdFromTeb(VOID);
DWORD GetCurrentWindowTextFromUserProcessParametersA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
DWORD GetCurrentWindowTextFromUserProcessParametersW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
LONGLONG GetFileSizeFromPathW(_In_ PWCHAR Path, _In_ DWORD dwFlagsAndAttributes);
LONGLONG GetFileSizeFromPathA(_In_ PCHAR Path, _In_ DWORD dwFlagsAndAttributes);
DWORD UrlDownloadToFileSynchronousW(_In_ PWCHAR Url, _In_ PWCHAR SavePath);
DWORD UrlDownloadToFileSynchronousA(_In_ PCHAR Url, _In_ PCHAR SavePath);
BOOL SetProcessPrivilegeToken(_In_ DWORD PrivilegeEnum);
BOOL IsDllLoadedW(_In_ LPCWSTR DllName);
BOOL IsDllLoadedA(_In_ LPCSTR DllName);

//fingerprinting
LCID GetCurrentLocaleFromTeb(VOID);
DWORD GetNumberOfLinkedDlls(VOID);
BOOL IsNvidiaGraphicsCardPresentA(VOID);
BOOL IsNvidiaGraphicsCardPresentW(VOID);
BOOL IsProcessRunningA(_In_ PCHAR ProcessNameWithExtension);
BOOL IsProcessRunningW(_In_ PWCHAR ProcessNameWithExtension);
BOOL IsProcessRunningAsAdmin(VOID);
ULONG GetOsMajorVersionFromPeb(VOID);
ULONG GetOsMinorVersionFromPeb(VOID);
ULONG GetOsBuildNumberFromPeb(VOID);
ULONG GetOsPlatformIdFromPeb(VOID);
DWORD GetPidFromNtQuerySystemInformationW(_In_ PWCHAR BinaryNameWithFileExtension);
DWORD GetPidFromNtQuerySystemInformationA(_In_ PCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWindowsTerminalServiceW(_In_ PWCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWindowsTerminalServiceA(_In_ PCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWmiComInterface(_In_ PWCHAR BinaryNameWithFileExtension);
DWORD GetPidFromEnumProcessesW(_In_ PWCHAR ProcessNameWithExtension);
DWORD GetPidFromEnumProcessesA(_In_ PCHAR ProcessNameWithExtension);

//malicious capabilities
DWORD OleGetClipboardDataA(_Inout_ PCHAR Buffer);
DWORD OleGetClipboardDataW(_Inout_ PWCHAR Buffer);
DWORD MpfComVssDeleteShadowVolumeBackups(_In_ BOOL CoUninitializeAfterCompletion);
BOOL MpfComModifyShortcutTargetW(_In_ PWCHAR LnkPath, _In_  PWCHAR LnkExecutionProperty);
BOOL MpfComModifyShortcutTargetA(_In_ PCHAR LnkPath, _In_  PCHAR LnkExecutionProperty);
BOOL UacBypassFodHelperMethodA(_In_ PCHAR PathToBinaryToExecute, _Inout_ PPROCESS_INFORMATION Pi);
BOOL UacBypassFodHelperMethodW(_In_ PWCHAR PathToBinaryToExecute, _Inout_ PPROCESS_INFORMATION Pi);

//evasion
BOOL CreateProcessWithCfGuardW(_Inout_ PPROCESS_INFORMATION Pi, _In_ PWCHAR Path);
BOOL CreateProcessWithCfGuardA(_Inout_ PPROCESS_INFORMATION Pi, _In_ PCHAR Path);
HRESULT CreateProcessFromIHxInteractiveUserW(_In_ PWCHAR UriFile);
HRESULT CreateProcessFromIHxInteractiveUserA(_In_ PCHAR UriFile);
HRESULT CreateProcessFromIHxHelpPaneServerW(_In_ PWCHAR UriFile);
HRESULT CreateProcessFromIHxHelpPaneServerA(_In_ PCHAR UriFile);
BOOL MasqueradePebAsExplorer(VOID);
BOOL CreateFileFromDsCopyFromSharedFileW(_In_ PWCHAR NewFileName, _In_ PWCHAR FileToClone);
BOOL CreateFileFromDsCopyFromSharedFileA(_In_ PCHAR NewFileName, _In_ PCHAR FileToClone);
BOOL DelayedExecutionExecuteOnDisplayOff(VOID);
DWORD CreateProcessFromShellExecuteInExplorerProcessW(_In_ PWCHAR BinaryPath);
DWORD CreateProcessFromShellExecuteInExplorerProcessA(_In_ PCHAR BinaryPath);
DWORD CreateProcessFromIShellDispatchInvokeW(_In_ PWCHAR BinaryPath);
DWORD CreateProcessFromIShellDispatchInvokeA(_In_ PCHAR BinaryPath);
DWORD CreateProcessViaNtCreateUserProcessW(PWCHAR FullBinaryPath);
DWORD CreateProcessViaNtCreateUserProcessA(PCHAR FullBinaryPath);
BOOL RemoveDllFromPebA(_In_ LPCSTR lpModuleName);
BOOL RemoveDllFromPebW(_In_ LPCWSTR lpModuleName);

//antidebug
BOOL AdfCloseHandleOnInvalidAddress(VOID);
BOOL AdfIsCreateProcessDebugEventCodeSet(VOID);
BOOL AdfOpenProcessOnCsrss(VOID);
BOOL IsIntelHardwareBreakpointPresent(VOID);
BOOL CheckRemoteDebuggerPresent2(_In_ HANDLE hHandle, _Inout_ PBOOL pbDebuggerPresent);
BOOL IsDebuggerPresentEx(VOID);