![VXUG logo](logo.png)
managed by [vx-underground](https://vx-underground.org) | follow us on [Twitter](https://twitter.com/vxunderground) | download malware samples at the [VXUG/samples](https://samples.vx-underground.org/) page
  
# VX-API

Version: 2.0.684

Developer: smelly__vx
  
The VX-API is a collection of malicious functionality to aid in malware development. It is recommended you clone and/or download this entire repo then open the Visual Studio solution file to easily explore functionality and concepts.

Some functions may be dependent on other functions present within the solution file. Using the solution file provided here will make it easier to identify which other functionality and/or header data is required.

You're free to use this in any manner you please. You do not need to use this entire solution for your malware proof-of-concepts or Red Team engagements. Strip, copy, paste, delete, or edit this projects contents as much as you'd like.
 
 
</div>

# List of features

| Function Name | Original Author | Section |
| ------------- | --------------- | ------- |
| ByteArrayToCharArray | smelly__vx | String Conversion |
| CharArrayToByteArray | smelly__vx | String Conversion |
| ShlwapiCharStringToWCharString | smelly__vx | String Conversion |
| ShlwapiWCharStringToCharString | smelly__vx | String Conversion |
| CharStringToWCharString | smelly__vx | String Conversion |
| WCharStringToCharString | smelly__vx | String Conversion |
| RtlInitEmptyUnicodeString | ReactOS | Windows Unicode Structure |
| RtlInitUnicodeString | ReactOS | Windows Unicode Structure |
| CaplockString | simonc | String Manipulation |
| CopyMemoryEx | ReactOS | String Manipulation |
| SecureStringCopy | Apple (c) 1999 | String Manipulation |
| StringCompare | Apple (c) 1999 | String Manipulation |
| StringConcat | Apple (c) 1999 | String Manipulation |
| StringCopy | Apple (c) 1999 | String Manipulation |
| StringFindSubstring | Apple (c) 1999 | String Manipulation |
| StringLength | Apple (c) 1999 | String Manipulation |
| StringLocateChar | Apple (c) 1999 | String Manipulation |
| StringRemoveSubstring | smelly__vx | String Manipulation |
| StringTerminateStringAtChar | smelly__vx | String Manipulation |
| StringToken | Apple (c) 1999 | String Manipulation |
| ZeroMemoryEx | ReactOS | String Manipulation | 
| ConvertCharacterStringToIntegerUsingNtdll | smelly__vx | String Manipulation |
| MemoryFindMemory | KamilCuk | String Manipulation |
| AdfCloseHandleOnInvalidAddress | Checkpoint Research | Anti-debug |
| AdfIsCreateProcessDebugEventCodeSet | Checkpoint Research | Anti-debug |
| AdfOpenProcessOnCsrss | Checkpoint Research | Anti-debug |
| CheckRemoteDebuggerPresent2 | ReactOS | Anti-debug |
| IsDebuggerPresentEx | smelly__vx | Anti-debug |
| IsIntelHardwareBreakpointPresent | Checkpoint Research | Anti-debug |
| HashStringDjb2 | Dan Bernstein | String Hashing |
| HashStringFowlerNollVoVariant1a | Glenn Fowler, Landon Curt Noll, and Kiem-Phong Vo | String Hashing |
| HashStringJenkinsOneAtATime32Bit | Bob Jenkins | String Hashing |
| HashStringLoseLose | Brian Kernighan and Dennis Ritchie | String Hashing |
| HashStringRotr32 | T. Oshiba (1972) | String Hashing |
| HashStringSdbm | Ozan Yigit | String Hashing |
| HashStringSuperFastHash | Paul Hsieh | String Hashing |
| HashStringUnknownGenericHash1A | Unknown | String Hashing |
| HashStringSipHash | RistBS | String Hashing | 
| HashStringMurmur | RistBS | String Hashing | 
| CreateMd5HashFromFilePath | Microsoft | Cryptography Related |
| CreatePseudoRandomInteger | Apple (c) 1999 | Cryptography Related |
| CreatePseudoRandomString | smelly__vx | Cryptography Related |
| HashFileByMsiFileHashTable | smelly__vx | Cryptography Related |
| CreatePseudoRandomIntegerFromNtdll | smelly__vx | Cryptography Related |
| LzMaximumCompressBuffer | smelly__vx | Compression |
| LzMaximumDecompressBuffer | smelly__vx | Compression |
| LzStandardCompressBuffer | smelly__vx | Compression |
| LzStandardDecompressBuffer | smelly__vx | Compression |
| XpressHuffMaximumCompressBuffer | smelly__vx | Compression |
| XpressHuffMaximumDecompressBuffer | smelly__vx | Compression |
| XpressHuffStandardCompressBuffer | smelly__vx | Compression |
| XpressHuffStandardDecompressBuffer | smelly__vx | Compression |
| XpressMaximumCompressBuffer | smelly__vx | Compression |
| XpressMaximumDecompressBuffer | smelly__vx | Compression |
| XpressStandardCompressBuffer | smelly__vx | Compression |
| XpressStandardDecompressBuffer | smelly__vx | Compression |
| GetLastErrorFromTeb | smelly__vx | Error Handling |
| GetLastNtStatusFromTeb | smelly__vx | Error Handling |
| RtlNtStatusToDosErrorViaImport | ReactOS | Error Handling |
| GetLastErrorFromTeb | smelly__vx | Error Handling |
| SetLastErrorInTeb | smelly__vx | Error Handling |
| SetLastNtStatusInTeb | smelly__vx | Error Handling |
| Win32FromHResult | Raymond Chen | Error Handling |
| CreateFileFromDsCopyFromSharedFile | Jonas Lyk | Evasion |
| CreateProcessFromIHxHelpPaneServer | James Forshaw | Evasion |
| CreateProcessFromIHxInteractiveUser | James Forshaw | Evasion |
| CreateProcessFromIShellDispatchInvoke | Mohamed Fakroud | Evasion |
| CreateProcessFromShellExecuteInExplorerProcess | Microsoft | Evasion |
| CreateProcessViaNtCreateUserProcess | CaptMeelo | Evasion |
| CreateProcessWithCfGuard | smelly__vx and Adam Chester | Evasion |
| DelayedExecutionExecuteOnDisplayOff | am0nsec and smelly__vx | Evasion |
| MasqueradePebAsExplorer | smelly__vx | Evasion |
| RemoveDllFromPeb | rad9800 | Evasion |
| HookEngineRestoreHeapFree | rad9800 | Evasion |
| HookEngineUnhookHeapFree | rad9800 | Evasion |
| SleepObfuscationViaVirtualProtect | 5pider | Evasion |
| RemoveRegisterDllNotification | Rad98, Peter Winter-Smith | Evasion |
| CreateProcessByWindowsRHotKey | smelly__vx | Evasion |
| CreateProcessByWindowsRHotKeyEx | smelly__vx | Evasion |
| AmsiBypassViaPatternScan | ZeroMemoryEx | Evasion |
| CopyFileViaSetupCopyFile | smelly__vx | Evasion |
| CreateProcessFromINFSectionInstallStringNoCab | smelly__vx | Evasion |
| CreateProcessFromINFSetupCommand | smelly__vx | Evasion |
| CreateProcessFromINFSectionInstallStringNoCab2 | smelly__vx | Evasion |
| CreateProcessFromIeFrameOpenUrl | smelly__vx | Evasion |
| CreateProcessFromPcwUtil | smelly__vx | Evasion |
| CreateProcessFromShdocVwOpenUrl | smelly__vx | Evasion |
| CreateProcessFromShell32ShellExecRunDll | smelly__vx | Evasion |

| CreateProcessFromPcwUtil | smelly__vx | Evasion |
| GetCurrentLocaleFromTeb | 3xp0rt | Fingerprinting |
| GetNumberOfLinkedDlls | smelly__vx | Fingerprinting |
| GetOsBuildNumberFromPeb | smelly__vx | Fingerprinting |
| GetOsMajorVersionFromPeb | smelly__vx | Fingerprinting |
| GetOsMinorVersionFromPeb | smelly__vx | Fingerprinting |
| GetOsPlatformIdFromPeb | smelly__vx | Fingerprinting |
| IsNvidiaGraphicsCardPresent | smelly__vx | Fingerprinting |
| IsProcessRunning | smelly__vx | Fingerprinting |
| IsProcessRunningAsAdmin | Vimal Shekar | Fingerprinting |
| GetPidFromNtQuerySystemInformation | smelly__vx | Fingerprinting |
| GetPidFromWindowsTerminalService | modexp | Fingerprinting |
| GetPidFromWmiComInterface | aalimian and modexp | Fingerprinting |
| GetPidFromEnumProcesses | smelly__vx | Fingerprinting |
| GetPidFromPidBruteForcing | modexp | Fingerprinting |
| GetPidFromNtQueryFileInformation | modexp, Lloyd Davies, Jonas Lyk | Fingerprinting |
| GetPidFromPidBruteForcingExW | smelly__vx, LLoyd Davies, Jonas Lyk, modexp | Fingerprinting |
| CreateLocalAppDataObjectPath | smelly__vx | Helper Functions |
| CreateWindowsObjectPath | smelly__vx | Helper Functions |
| DeleteFileWithCreateFileFlag | smelly__vx | Helper Functions |
| GetCurrentDirectoryFromUserProcessParameters | smelly__vx | Helper Functions |
| GetCurrentProcessIdFromTeb | ReactOS | Helper Functions |
| GetCurrentUserSid | Giovanni Dicanio | Helper Functions |
| GetCurrentWindowTextFromUserProcessParameter | smelly__vx | Helper Functions |
| GetFileSizeFromPath | smelly__vx | Helper Functions |
| GetProcessHeapFromTeb | smelly__vx | Helper Functions |
| GetProcessPathFromLoaderLoadModule | smelly__vx | Helper Functions |
| GetProcessPathFromUserProcessParameters | smelly__vx | Helper Functions |
| GetSystemWindowsDirectory | Geoff Chappell | Helper Functions |
| IsPathValid | smelly__vx | Helper Functions |
| RecursiveFindFile | Luke | Helper Functions |
| SetProcessPrivilegeToken | Microsoft | Helper Functions |
| IsDllLoaded | smelly__vx | Helper Functions | 
| TryLoadDllMultiMethod | smelly__vx | Helper Functions |
| CreateThreadAndWaitForCompletion | smelly__vx | Helper Functions |
| GetProcessBinaryNameFromHwndW | smelly__vx | Helper Functions |
| GetByteArrayFromFile | smelly__vx | Helper Functions |
| Ex_GetHandleOnDeviceHttpCommunication | x86matthew | Helper Functions |
| IsRegistryKeyValid | smelly__vx | Helper Functions |
| FastcallExecuteBinaryShellExecuteEx | smelly__vx | Helper Functions |
| GetCurrentProcessIdFromOffset | RistBS | Helper Functions | 
| GetPeBaseAddress | smelly__vx | Helper Functions | 
| LdrLoadGetProcedureAddress | c5pider | Helper Functions | 
| IsPeSection | smelly__vx | Helper Functions | 
| AddSectionToPeFile | smelly__vx | Helper Functions | 
| WriteDataToPeSection | smelly__vx | Helper Functions | 
| GetPeSectionSizeInByte | smelly__vx | Helper Functions | 
| ReadDataFromPeSection | smelly__vx | Helper Functions | 
| GetCurrentProcessNoForward | ReactOS | Helper Functions | 
| GetCurrentThreadNoForward | ReactOS | Helper Functions | 
| GetKUserSharedData | Geoff Chappell | Library Loading |
| GetModuleHandleEx2 | smelly__vx | Library Loading |
| GetPeb | 29a | Library Loading |
| GetPebFromTeb | ReactOS | Library Loading |
| GetProcAddress | 29a Volume 2, c5pider | Library Loading |
| GetProcAddressDjb2 | smelly__vx | Library Loading |
| GetProcAddressFowlerNollVoVariant1a | smelly__vx | Library Loading |
| GetProcAddressJenkinsOneAtATime32Bit | smelly__vx | Library Loading |
| GetProcAddressLoseLose | smelly__vx | Library Loading |
| GetProcAddressRotr32 | smelly__vx | Library Loading |
| GetProcAddressSdbm | smelly__vx | Library Loading |
| GetProcAddressSuperFastHash | smelly__vx | Library Loading |
| GetProcAddressUnknownGenericHash1 | smelly__vx | Library Loading |
| GetProcAddressSipHash | RistBS | Library Loading |
| GetProcAddressMurmur | RistBS | Library Loading |
| GetRtlUserProcessParameters | ReactOS | Library Loading |
| GetTeb | ReactOS | Library Loading |
| RtlLoadPeHeaders | smelly__vx | Library Loading |
| ProxyWorkItemLoadLibrary | Rad98, Peter Winter-Smith | Library Loading |
| ProxyRegisterWaitLoadLibrary | Rad98, Peter Winter-Smith | Library Loading |
| MpfComModifyShortcutTarget | Unknown | Malcode |
| MpfComVssDeleteShadowVolumeBackups | am0nsec | Malcode |
| OleGetClipboardData | Microsoft | Malcode |
| UacBypassFodHelperMethod | winscripting.blog | Malcode |
| MpfGetLsaPidFromServiceManager | modexp | Malcode |
| MpfGetLsaPidFromRegistry | modexp | Malcode |
| MpfGetLsaPidFromNamedPipe | modexp | Malcode |
| MpfSceViaEnumChildWindows | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaCDefFolderMenu_Create2 | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaCertEnumSystemStore | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaCertEnumSystemStoreLocation | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumDateFormatsW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumDesktopWindows | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumDesktopsW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumDirTreeW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumDisplayMonitors | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumFontFamiliesExW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumFontsW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumLanguageGroupLocalesW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumObjects | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumResourceTypesExW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumSystemCodePagesW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumSystemGeoID | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumSystemLanguageGroupsW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumSystemLocalesEx | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumThreadWindows | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumTimeFormatsEx | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumUILanguagesW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumWindowStationsW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumWindows | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumerateLoadedModules64 | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaK32EnumPageFilesW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaEnumPwrSchemes | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaMessageBoxIndirectW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaChooseColorW | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaClusWorkerCreate | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaSymEnumProcesses | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaImageGetDigestStream | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaVerifierEnumerateResource | alfarom256, aahmad097, wra7h | Malcode |
| MpfSceViaSymEnumSourceFiles | alfarom256, aahmad097, wra7h | Malcode |
| MpfComMonitorChromeSessionOnce | smelly__vx | Malcode |
| MpfExecute64bitPeBinaryInMemoryFromByteArrayNoReloc | aaaddress1 | Malcode |
| MpfLolExecuteRemoteBinaryByAppInstaller | Wade Hickey | Malcode |
| MpfExtractMaliciousPayloadFromZipFileNoPassword | Codu | Malcode |
| MpfPiControlInjection | SafeBreach Labs | Malcode |
| MpfPiQueueUserAPCViaAtomBomb | SafeBreach Labs | Malcode |
| MpfPiWriteProcessMemoryCreateRemoteThread | SafeBreach Labs | Malcode |
| MpfProcessInjectionViaProcessReflection | Deep Instinct | Malcode |
| MpfSceViaImmEnumInputContext | alfarom256, aahmad097 | Malcode |
| MpfSceViaCertFindChainInStore | alfarom256, aahmad097 | Malcode |
| MpfSceViaEnumPropsExW | alfarom256, aahmad097 | Malcode |
| MpfSceViaCreateThreadpoolWait | alfarom256, aahmad097 | Malcode |
| MpfSceViaCryptEnumOIDInfo | alfarom256, aahmad097 | Malcode |
| MpfSceViaDSA_EnumCallback | alfarom256, aahmad097 | Malcode |
| MpfSceViaCreateTimerQueueTimer | alfarom256, aahmad097 | Malcode |
| MpfSceViaEvtSubscribe | alfarom256, aahmad097 | Malcode |
| MpfSceViaFlsAlloc | alfarom256, aahmad097 | Malcode |
| MpfSceViaInitOnceExecuteOnce | alfarom256, aahmad097 | Malcode |
| UrlDownloadToFileSynchronous | Hans Passant | Networking |
| ConvertIPv4IpAddressStructureToString | smelly__vx | Networking |
| ConvertIPv4StringToUnsignedLong | smelly__vx | Networking |
| SendIcmpEchoMessageToIPv4Host | smelly__vx | Networking |
| ConvertIPv4IpAddressUnsignedLongToString | smelly__vx | Networking |
| DnsGetDomainNameIPv4AddressAsString | smelly__vx | Networking |
| DnsGetDomainNameIPv4AddressUnsignedLong | smelly__vx | Networking |
| GetDomainNameFromUnsignedLongIPV4Address | smelly__vx | Networking |
| GetDomainNameFromIPV4AddressAsString | smelly__vx | Networking | 
| InitHardwareBreakpointEngine | rad98 | Hooking Engine |
| ShutdownHardwareBreakpointEngine | rad98 | Hooking Engine |
| ExceptionHandlerCallbackRoutine | rad98 | Hooking Engine |
| SetHardwareBreakpoint | rad98 | Hooking Engine |
| InsertDescriptorEntry | rad98 | Hooking Engine |
| RemoveDescriptorEntry | rad98 | Hooking Engine |
| SnapshotInsertHardwareBreakpointHookIntoTargetThread | rad98 | Hooking Engine |
| GenericShellcodeHelloWorldMessageBoxA | SafeBreach Labs | Generic Shellcode |
| GenericShellcodeHelloWorldMessageBoxAEbFbLoop | SafeBreach Labs | Generic Shellcode |
| GenericShellcodeOpenCalcExitThread | MsfVenom | Generic Shellcode |


# Todo list
| Functionality | Author | Note |
| ------------- | ------ | ---- |
| NtMapViewOfSection LSASS | modexp | N/A |
| WQL Win32_Ping | Martin Friedrich | N/A |
