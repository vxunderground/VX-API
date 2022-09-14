![VXUG logo](logo.png)
managed by [vx-underground](https://vx-underground.org) | follow us on [Twitter](https://twitter.com/vxunderground) | download malware samples at the [VXUG/samples](https://samples.vx-underground.org/) page
  
# VX-API
  
The VX-API is a collection of malicious functionality to aid in malware development. It is recommended you clone and/or download this entire repo then open the Visual Studio solution file to easily explore functionality and concepts.

Some functions may be dependent on other functions present within the solution file. Using the solution file provided here will make it easier to identify which other functionality and/or header data is required.

You're free to use this in any manner you please. You do not need to use this entire solution for your malware proof-of-concepts or Red Team engagements. Strip, copy, paste, delete, or edit this projects contents as much as you'd like.
 

</div>

# List of features

| Function Name | Original Author | Section |
| ------------- | --------------- | ------- |
| CharArrayToByteArray | smelly__vx | String Manipulation |
| CharStringToWCharString | smelly__vx | String Manipulation |
| WCharStringToCharString | smelly__vx | String Manipulation |
| RtlInitEmptyUnicodeString | ReactOS | String Manipulation |
| RtlInitUnicodeString | ReactOS | String Manipulation |
| ByteArrayToCharArray | smelly__vx | String Manipulation |
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
| HashFileByMsiFileHashTabl | smelly__vx | Cryptography Related |
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
| GetLastErrorFromTeb | smelly__vx | Error Handling |
| GetLastNtStatusFromTeb | smelly__vx | Error Handling |
| GetLastErrorFromTeb | smelly__vx | Error Handling |
| SetLastErrorInTeb | smelly__vx | Error Handling |
| SetLastNtStatusInTeb | smelly__vx | Error Handling |
| Win32FromHResult | Raymond Chen | Error Handling |





