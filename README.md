![VXUG logo](logo.png)
managed by [vx-underground](https://vx-underground.org) | follow us on [Twitter](https://twitter.com/vxunderground) | download malware samples at the [VXUG/samples](https://samples.vx-underground.org/) page
  
# VX-API

Version: 2.01.015

Developer: smelly__vx
  
The VX-API is a collection of malicious functionality to aid in malware development. It is recommended you clone and/or download this entire repo then open the Visual Studio solution file to easily explore functionality and concepts.

Some functions may be dependent on other functions present within the solution file. Using the solution file provided here will make it easier to identify which other functionality and/or header data is required.

You're free to use this in any manner you please. You do not need to use this entire solution for your malware proof-of-concepts or Red Team engagements. Strip, copy, paste, delete, or edit this projects contents as much as you'd like.
 
 
</div>

# List of features

## Anti-debug
| Function Name | Original Author |
| ------------- | --------------- |
| AdfCloseHandleOnInvalidAddress | Checkpoint Research |
| AdfIsCreateProcessDebugEventCodeSet | Checkpoint Research |
| AdfOpenProcessOnCsrss | Checkpoint Research |
| CheckRemoteDebuggerPresent2 | ReactOS |
| IsDebuggerPresentEx | smelly__vx |
| IsIntelHardwareBreakpointPresent | Checkpoint Research |


## Cryptography Related
| Function Name | Original Author |
| ------------- | --------------- |
| HashStringDjb2 | Dan Bernstein |
| HashStringFowlerNollVoVariant1a | Glenn Fowler, Landon Curt Noll, and Kiem-Phong Vo |
| HashStringJenkinsOneAtATime32Bit | Bob Jenkins |
| HashStringLoseLose | Brian Kernighan and Dennis Ritchie |
| HashStringRotr32 | T. Oshiba (1972) |
| HashStringSdbm | Ozan Yigit |
| HashStringSuperFastHash | Paul Hsieh |
| HashStringUnknownGenericHash1A | Unknown |
| HashStringSipHash | RistBS | 
| HashStringMurmur | RistBS | 
| CreateMd5HashFromFilePath | Microsoft |
| CreatePseudoRandomInteger | Apple (c) 1999 |
| CreatePseudoRandomString | smelly__vx |
| HashFileByMsiFileHashTable | smelly__vx |
| CreatePseudoRandomIntegerFromNtdll | smelly__vx |
| LzMaximumCompressBuffer | smelly__vx |
| LzMaximumDecompressBuffer | smelly__vx |
| LzStandardCompressBuffer | smelly__vx |
| LzStandardDecompressBuffer | smelly__vx |
| XpressHuffMaximumCompressBuffer | smelly__vx |
| XpressHuffMaximumDecompressBuffer | smelly__vx |
| XpressHuffStandardCompressBuffer | smelly__vx |
| XpressHuffStandardDecompressBuffer | smelly__vx |
| XpressMaximumCompressBuffer | smelly__vx |
| XpressMaximumDecompressBuffer | smelly__vx |
| XpressStandardCompressBuffer | smelly__vx |
| XpressStandardDecompressBuffer | smelly__vx |
| ExtractFilesFromCabIntoTarget | smelly__vx |


## Error Handling
| Function Name | Original Author |
| ------------- | --------------- |
| GetLastErrorFromTeb | smelly__vx |
| GetLastNtStatusFromTeb | smelly__vx |
| RtlNtStatusToDosErrorViaImport | ReactOS |
| GetLastErrorFromTeb | smelly__vx |
| SetLastErrorInTeb | smelly__vx |
| SetLastNtStatusInTeb | smelly__vx |
| Win32FromHResult | Raymond Chen |


## Evasion
| Function Name | Original Author |
| ------------- | --------------- |
| AmsiBypassViaPatternScan | ZeroMemoryEx |
| DelayedExecutionExecuteOnDisplayOff | am0nsec and smelly__vx |
| HookEngineRestoreHeapFree | rad9800 |
| MasqueradePebAsExplorer | smelly__vx |
| RemoveDllFromPeb | rad9800 |
| RemoveRegisterDllNotification | Rad98, Peter Winter-Smith |
| SleepObfuscationViaVirtualProtect | 5pider |
| RtlSetBaseUnicodeCommandLine | TheWover |


## Fingerprinting
| Function Name | Original Author |
| ------------- | --------------- |
| GetCurrentLocaleFromTeb | 3xp0rt |
| GetNumberOfLinkedDlls | smelly__vx |
| GetOsBuildNumberFromPeb | smelly__vx |
| GetOsMajorVersionFromPeb | smelly__vx |
| GetOsMinorVersionFromPeb | smelly__vx |
| GetOsPlatformIdFromPeb | smelly__vx |
| IsNvidiaGraphicsCardPresent | smelly__vx |
| IsProcessRunning | smelly__vx |
| IsProcessRunningAsAdmin | Vimal Shekar |
| GetPidFromNtQuerySystemInformation | smelly__vx |
| GetPidFromWindowsTerminalService | modexp |
| GetPidFromWmiComInterface | aalimian and modexp |
| GetPidFromEnumProcesses | smelly__vx |
| GetPidFromPidBruteForcing | modexp |
| GetPidFromNtQueryFileInformation | modexp, Lloyd Davies, Jonas Lyk |
| GetPidFromPidBruteForcingExW | smelly__vx, LLoyd Davies, Jonas Lyk, modexp |


## Helper Functions
| Function Name | Original Author |
| ------------- | --------------- |
| CreateLocalAppDataObjectPath | smelly__vx |
| CreateWindowsObjectPath | smelly__vx |
| GetCurrentDirectoryFromUserProcessParameters | smelly__vx |
| GetCurrentProcessIdFromTeb | ReactOS |
| GetCurrentUserSid | Giovanni Dicanio |
| GetCurrentWindowTextFromUserProcessParameter | smelly__vx |
| GetFileSizeFromPath | smelly__vx |
| GetProcessHeapFromTeb | smelly__vx |
| GetProcessPathFromLoaderLoadModule | smelly__vx |
| GetProcessPathFromUserProcessParameters | smelly__vx |
| GetSystemWindowsDirectory | Geoff Chappell |
| IsPathValid | smelly__vx |
| RecursiveFindFile | Luke |
| SetProcessPrivilegeToken | Microsoft |
| IsDllLoaded | smelly__vx | 
| TryLoadDllMultiMethod | smelly__vx |
| CreateThreadAndWaitForCompletion | smelly__vx |
| GetProcessBinaryNameFromHwndW | smelly__vx |
| GetByteArrayFromFile | smelly__vx |
| Ex_GetHandleOnDeviceHttpCommunication | x86matthew |
| IsRegistryKeyValid | smelly__vx |
| FastcallExecuteBinaryShellExecuteEx | smelly__vx |
| GetCurrentProcessIdFromOffset | RistBS | 
| GetPeBaseAddress | smelly__vx | 
| LdrLoadGetProcedureAddress | c5pider | 
| IsPeSection | smelly__vx | 
| AddSectionToPeFile | smelly__vx | 
| WriteDataToPeSection | smelly__vx | 
| GetPeSectionSizeInByte | smelly__vx | 
| ReadDataFromPeSection | smelly__vx | 
| GetCurrentProcessNoForward | ReactOS | 
| GetCurrentThreadNoForward | ReactOS | 


## Library Loading
| Function Name | Original Author |
| ------------- | --------------- |
| GetKUserSharedData | Geoff Chappell |
| GetModuleHandleEx2 | smelly__vx |
| GetPeb | 29a |
| GetPebFromTeb | ReactOS |
| GetProcAddress | 29a Volume 2, c5pider |
| GetProcAddressDjb2 | smelly__vx |
| GetProcAddressFowlerNollVoVariant1a | smelly__vx |
| GetProcAddressJenkinsOneAtATime32Bit | smelly__vx |
| GetProcAddressLoseLose | smelly__vx |
| GetProcAddressRotr32 | smelly__vx |
| GetProcAddressSdbm | smelly__vx |
| GetProcAddressSuperFastHash | smelly__vx |
| GetProcAddressUnknownGenericHash1 | smelly__vx |
| GetProcAddressSipHash | RistBS |
| GetProcAddressMurmur | RistBS |
| GetRtlUserProcessParameters | ReactOS |
| GetTeb | ReactOS |
| RtlLoadPeHeaders | smelly__vx |
| ProxyWorkItemLoadLibrary | Rad98, Peter Winter-Smith |
| ProxyRegisterWaitLoadLibrary | Rad98, Peter Winter-Smith |


## Lsass Dumping
| Function Name | Original Author |
| ------------- | --------------- |
| MpfGetLsaPidFromServiceManager | modexp |
| MpfGetLsaPidFromRegistry | modexp |
| MpfGetLsaPidFromNamedPipe | modexp |


## Network Connectivity
| Function Name | Original Author |
| ------------- | --------------- |
| UrlDownloadToFileSynchronous | Hans Passant |
| ConvertIPv4IpAddressStructureToString | smelly__vx |
| ConvertIPv4StringToUnsignedLong | smelly__vx |
| SendIcmpEchoMessageToIPv4Host | smelly__vx |
| ConvertIPv4IpAddressUnsignedLongToString | smelly__vx |
| DnsGetDomainNameIPv4AddressAsString | smelly__vx |
| DnsGetDomainNameIPv4AddressUnsignedLong | smelly__vx |
| GetDomainNameFromUnsignedLongIPV4Address | smelly__vx |
| GetDomainNameFromIPV4AddressAsString | smelly__vx | 


## Other
| Function Name | Original Author |
| ------------- | --------------- |
| OleGetClipboardData | Microsoft |
| MpfComVssDeleteShadowVolumeBackups | am0nsec |
| MpfComModifyShortcutTarget | Unknown |
| MpfComMonitorChromeSessionOnce | smelly__vx |
| MpfExtractMaliciousPayloadFromZipFileNoPassword | Codu |


## Process Creation
| Function Name | Original Author |
| ------------- | --------------- |
| CreateProcessFromIHxHelpPaneServer | James Forshaw |
| CreateProcessFromIHxInteractiveUser | James Forshaw |
| CreateProcessFromIShellDispatchInvoke | Mohamed Fakroud |
| CreateProcessFromShellExecuteInExplorerProcess | Microsoft |
| CreateProcessViaNtCreateUserProcess | CaptMeelo |
| CreateProcessWithCfGuard | smelly__vx and Adam Chester |
| CreateProcessByWindowsRHotKey | smelly__vx |
| CreateProcessByWindowsRHotKeyEx | smelly__vx |
| CreateProcessFromINFSectionInstallStringNoCab | smelly__vx |
| CreateProcessFromINFSetupCommand | smelly__vx |
| CreateProcessFromINFSectionInstallStringNoCab2 | smelly__vx |
| CreateProcessFromIeFrameOpenUrl | smelly__vx |
| CreateProcessFromPcwUtil | smelly__vx |
| CreateProcessFromShdocVwOpenUrl | smelly__vx |
| CreateProcessFromShell32ShellExecRun | smelly__vx |
| MpfExecute64bitPeBinaryInMemoryFromByteArrayNoReloc | aaaddress1 |
| CreateProcessFromWmiWin32_ProcessW | CIA |
| CreateProcessFromZipfldrRouteCall | smelly__vx |
| CreateProcessFromUrlFileProtocolHandler | smelly__vx | 
| CreateProcessFromUrlOpenUrl | smelly__vx |
| CreateProcessFromMsHTMLW | smelly__vx |


## Process Injection
| Function Name | Original Author |
| ------------- | --------------- |
| MpfPiControlInjection | SafeBreach Labs |
| MpfPiQueueUserAPCViaAtomBomb | SafeBreach Labs |
| MpfPiWriteProcessMemoryCreateRemoteThread | SafeBreach Labs |
| MpfProcessInjectionViaProcessReflection | Deep Instinct |


## Proxied Functions
| Function Name | Original Author |
| ------------- | --------------- |
| IeCreateFile | smelly__vx |
| CopyFileViaSetupCopyFile | smelly__vx |
| CreateFileFromDsCopyFromSharedFile | Jonas Lyk |
| DeleteDirectoryAndSubDataViaDelNode | smelly__vx |
| DeleteFileWithCreateFileFlag | smelly__vx |
| IsProcessRunningAsAdmin2 | smelly__vx |
| IeCreateDirectory | smelly__vx |
| IeDeleteFile | smelly__vx |
| IeFindFirstFile | smelly__vx |
| IEGetFileAttributesEx | smelly__vx |
| IeMoveFileEx | smelly__vx |
| IeRemoveDirectory | smelly__vx |


## Shellcode Execution
| Function Name | Original Author |
| ------------- | --------------- |
| MpfSceViaImmEnumInputContext | alfarom256, aahmad097 |
| MpfSceViaCertFindChainInStore | alfarom256, aahmad097 |
| MpfSceViaEnumPropsExW | alfarom256, aahmad097 |
| MpfSceViaCreateThreadpoolWait | alfarom256, aahmad097 |
| MpfSceViaCryptEnumOIDInfo | alfarom256, aahmad097 |
| MpfSceViaDSA_EnumCallback | alfarom256, aahmad097 |
| MpfSceViaCreateTimerQueueTimer | alfarom256, aahmad097 |
| MpfSceViaEvtSubscribe | alfarom256, aahmad097 |
| MpfSceViaFlsAlloc | alfarom256, aahmad097 |
| MpfSceViaInitOnceExecuteOnce | alfarom256, aahmad097 |
| MpfSceViaEnumChildWindows | alfarom256, aahmad097, wra7h |
| MpfSceViaCDefFolderMenu_Create2 | alfarom256, aahmad097, wra7h |
| MpfSceViaCertEnumSystemStore | alfarom256, aahmad097, wra7h |
| MpfSceViaCertEnumSystemStoreLocation | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumDateFormatsW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumDesktopWindows | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumDesktopsW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumDirTreeW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumDisplayMonitors | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumFontFamiliesExW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumFontsW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumLanguageGroupLocalesW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumObjects | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumResourceTypesExW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumSystemCodePagesW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumSystemGeoID | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumSystemLanguageGroupsW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumSystemLocalesEx | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumThreadWindows | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumTimeFormatsEx | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumUILanguagesW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumWindowStationsW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumWindows | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumerateLoadedModules64 | alfarom256, aahmad097, wra7h |
| MpfSceViaK32EnumPageFilesW | alfarom256, aahmad097, wra7h |
| MpfSceViaEnumPwrSchemes | alfarom256, aahmad097, wra7h |
| MpfSceViaMessageBoxIndirectW | alfarom256, aahmad097, wra7h |
| MpfSceViaChooseColorW | alfarom256, aahmad097, wra7h |
| MpfSceViaClusWorkerCreate | alfarom256, aahmad097, wra7h |
| MpfSceViaSymEnumProcesses | alfarom256, aahmad097, wra7h |
| MpfSceViaImageGetDigestStream | alfarom256, aahmad097, wra7h |
| MpfSceViaVerifierEnumerateResource | alfarom256, aahmad097, wra7h |
| MpfSceViaSymEnumSourceFiles | alfarom256, aahmad097, wra7h |


## String Manipulation
| Function Name | Original Author |
| ------------- | --------------- |
| ByteArrayToCharArray | smelly__vx |
| CharArrayToByteArray | smelly__vx |
| ShlwapiCharStringToWCharString | smelly__vx |
| ShlwapiWCharStringToCharString | smelly__vx |
| CharStringToWCharString | smelly__vx |
| WCharStringToCharString | smelly__vx |
| RtlInitEmptyUnicodeString | ReactOS |
| RtlInitUnicodeString | ReactOS |
| CaplockString | simonc |
| CopyMemoryEx | ReactOS |
| SecureStringCopy | Apple (c) 1999 |
| StringCompare | Apple (c) 1999 |
| StringConcat | Apple (c) 1999 |
| StringCopy | Apple (c) 1999 |
| StringFindSubstring | Apple (c) 1999 |
| StringLength | Apple (c) 1999 |
| StringLocateChar | Apple (c) 1999 |
| StringRemoveSubstring | smelly__vx |
| StringTerminateStringAtChar | smelly__vx |
| StringToken | Apple (c) 1999 |
| ZeroMemoryEx | ReactOS |
| ConvertCharacterStringToIntegerUsingNtdll | smelly__vx |
| MemoryFindMemory | KamilCuk |


## UAC Bypass
| Function Name | Original Author |
| ------------- | --------------- |
| UacBypassFodHelperMethod | winscripting.blog |


## Rad98 Hooking Engine
| Function Name | Original Author |
| ------------- | --------------- |
| InitHardwareBreakpointEngine | rad98 |
| ShutdownHardwareBreakpointEngine | rad98 |
| ExceptionHandlerCallbackRoutine | rad98 |
| SetHardwareBreakpoint | rad98 |
| InsertDescriptorEntry | rad98 |
| RemoveDescriptorEntry | rad98 |
| SnapshotInsertHardwareBreakpointHookIntoTargetThread | rad98 |


## Generic Shellcode
| Function Name | Original Author |
| ------------- | --------------- |
| GenericShellcodeHelloWorldMessageBoxA | SafeBreach Labs |
| GenericShellcodeHelloWorldMessageBoxAEbFbLoop | SafeBreach Labs |
| GenericShellcodeOpenCalcExitThread | MsfVenom |