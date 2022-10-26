![VXUG logo](logo.png)
managed by [vx-underground](https://vx-underground.org) | follow us on [Twitter](https://twitter.com/vxunderground) | download malware samples at the [VXUG/samples](https://samples.vx-underground.org/) page
  
# VX-API

Version: 2.0.266

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
| CreateMd5HashFromFilePath | Microsoft | Cryptography Related |
| CreatePseudoRandomInteger | Apple (c) 1999 | Cryptography Related |
| CreatePseudoRandomString | smelly__vx | Cryptography Related |
| HashFileByMsiFileHashTable | smelly__vx | Cryptography Related |
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
| UrlDownloadToFileSynchronous | Hans Passant | Helper Functions |
| IsDllLoaded | smelly__vx | Helper Functions | 
| TryLoadDllMultiMethod | smelly__vx | Helper Functions |
| CreateThreadAndWaitForCompletion | smelly__vx | Helper Functions |
| GetKUserSharedData | Geoff Chappell | Library Loading |
| GetModuleHandleEx2 | smelly__vx | Library Loading |
| GetPeb | 29a | Library Loading |
| GetPebFromTeb | ReactOS | Library Loading |
| GetProcAddress | 29a Volume 2 | Library Loading |
| GetProcAddressDjb2 | smelly__vx | Library Loading |
| GetProcAddressFowlerNollVoVariant1a | smelly__vx | Library Loading |
| GetProcAddressJenkinsOneAtATime32Bit | smelly__vx | Library Loading |
| GetProcAddressLoseLose | smelly__vx | Library Loading |
| GetProcAddressRotr32 | smelly__vx | Library Loading |
| GetProcAddressSdbm | smelly__vx | Library Loading |
| GetProcAddressSuperFastHash | smelly__vx | Library Loading |
| GetProcAddressUnknownGenericHash1 | smelly__vx | Library Loading |
| GetRtlUserProcessParameters | ReactOS | Library Loading |
| GetTeb | ReactOS | Library Loading |
| RtlLoadPeHeaders | smelly__vx | Library Loading |
| MpfComModifyShortcutTarget | Unknown | Malicious Capability |
| MpfComVssDeleteShadowVolumeBackups | am0nsec | Malicious Capability |
| OleGetClipboardData | Microsoft | Malicious Capability |
| UacBypassFodHelperMethod | winscripting.blog | Malicious Capability |
| MpfGetLsaPidFromServiceManager | modexp | Malicious Capability |
| MpfGetLsaPidFromRegistry | modexp | Malicious Capability |
| MpfGetLsaPidFromNamedPipe | modexp | Malicious Capability |
| ShellcodeExecViaCertEnumSystemStore | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaCDefFolderMenu_Create2 | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaCertEnumSystemStoreLocation | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaCertFindChainInStore | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaEnumChildWindows | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaEnumDateFormatsW | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaEnumDesktopsW | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaEnumDesktopWindows | alfarom256 and aahmad097| Malicious Capability |
| ShellcodeExecViaEnumDirTreeW | alfarom256 and aahmad097| Malicious Capability |


# Todo list
| Functionality | Author | Note |
| ------------- | ------ | ---- |
| NtQueryOpenSubKeysEx | modexp | sam |
| RegQueryValueExW | modexp | Performance data |
| NtDeviceIoControlFile | modexp | TCP table |
| EvtQuery | modexp | Security Event Log |
| NtMapViewOfSection lsass | modexp | NtMapViewOfSection |
| IcmpSendEcho | N/A | Sync PING |
| IcmpSendEcho2Ex | N/A | Async PING w/ APC |
| WMI PING | N/A | Sync/Async PING with COM |
| Run PE in memory | N/A | N/A |
| Process Injection | N/A | N/A |
| More string manipulation from MSDN | N/A | N/A |
| More hashing algorithms | N/A | N/A |

# Notes
| Function Name | Note | Fixed |
| ------------- | ---- | ----- |
| StringToken | Needs revision, buggy | N/A |
| CreateProcessFromIShellDispatchInvoke | TryDllMultiMethod | N/A |
| UnusedSubroutineGetShellViewForDesktop | TryDllMultiMethod | N/A |
| DelayedExecutionExecuteOnDisplayOff | TryDllMultiMethod | N/A |
| GetPidFromWindowsTerminalService | TryDllMultiMethod | N/A |
| GetCurrentUserSid | TryDllMultiMethod | N/A |
| ShellcodeExecViaEnumDesktopsW | Fix abstraction | N/A |
| ShellcodeExecViaEnumDesktopWindows | Fix abstraction | N/A |
| ~~ShellcodeExecViaCertFindChainInStore~~ | ~~Buggy, unstable~~ | October 23rd, 2022 |
| ~~RecursiveFindFile~~ | ~~TryDllMultiMethod~~ | October 21th, 2022 |
| ~~UrlDownloadToFileSynchronous~~ | ~~TryDllMultiMethod~~ | October 21th, 2022 |
| ~~CreateFileFromDsCopyFromSharedFileW~~ | ~~Never unloads dll~~ | October 21th, 2022 |
| ~~HashFileByMsiFileHashTable~~ | ~~TryDllMultiMethod~~ | October 21th, 2022 |
| ~~RtlInitEmptyUnicodeString~~ | ~~Needs revision~~ | October 21th, 2022 |
| ~~CreateProcessByNotepadProxy~~ | ~~Removed, unstable~~ | October 16th, 2022 |
| ~~SystemFunction036~~ | ~~Removed, unstable~~ | October 16th, 2022 |
