#pragma once
#include "Internal.h"

PCHAR CaplockStringA(_In_ PCHAR Ptr);
PWCHAR CaplockStringW(_In_ PWCHAR Ptr);
PVOID CopyMemoryEx(_Inout_ PVOID Destination, _In_ CONST PVOID Source, _In_ SIZE_T Length);
VOID ZeroMemoryEx(_Inout_ PVOID Destination, _In_ SIZE_T Size);
PCHAR SecureStringCopyA(_Inout_ PCHAR String1, _In_ LPCSTR String2, _In_ SIZE_T Size);
PWCHAR SecureStringCopyW(_Inout_ PWCHAR String1, _In_ LPCWSTR String2, _In_ SIZE_T Size);
INT StringCompareA(_In_ LPCSTR String1, _In_ LPCSTR String2);
INT StringCompareW(_In_ LPCWSTR String1, _In_ LPCWSTR String2);
PWCHAR StringConcatW(_Inout_ PWCHAR String, _In_ PWCHAR String2);
PCHAR StringConcatA(_Inout_ PCHAR String, _In_ PCHAR String2);
PCHAR StringCopyA(_Inout_ PCHAR String1, _In_ PCHAR String2);
PWCHAR StringCopyW(_Inout_ PWCHAR String1, _In_ PWCHAR String2);
PCHAR StringFindSubstringA(_In_ PCHAR String1, _In_ PCHAR String2);
PWCHAR StringFindSubstringW(_In_ PWCHAR String1, _In_ PWCHAR String2);
SIZE_T StringLengthA(_In_ LPCSTR String);
SIZE_T StringLengthW(_In_ LPCWSTR String);
PCHAR StringLocateCharA(_Inout_ PCHAR String, _In_ INT Character);
PWCHAR StringLocateCharW(_Inout_ PWCHAR String, _In_ INT Character);
PCHAR StringRemoveSubstringA(_Inout_ PCHAR String, _In_ CONST PCHAR Substring);
PWCHAR StringRemoveSubstringW(_Inout_ PWCHAR String, _In_ CONST PWCHAR Substring);
PCHAR StringTerminateStringAtCharA(_Inout_ PCHAR String, _In_ INT Character);
PWCHAR StringTerminateStringAtCharW(_Inout_ PWCHAR String, _In_ INT Character);
PCHAR StringTokenA(_In_ PCHAR String, _In_ CONST PCHAR Delim);
PWCHAR StringTokenW(_In_ PWCHAR String, _In_ CONST PWCHAR Delim);
VOID CharArrayToByteArrayA(PCHAR Char, PBYTE Byte, DWORD Length);
VOID CharArrayToByteArrayW(PWCHAR Char, PBYTE Byte, DWORD Length);
VOID RtlInitUnicodeString(_Inout_ PUNICODE_STRING DestinationString, _In_ PCWSTR SourceString);
VOID RtlInitEmptyUnicodeString(_Inout_ PUNICODE_STRING UnicodeString, _In_ PWCHAR Buffer, _In_ USHORT BufferSize);
SIZE_T CharStringToWCharString(_Inout_ PWCHAR Destination, _In_ PCHAR Source, _In_ SIZE_T MaximumAllowed);
SIZE_T WCharStringToCharString(_Inout_ PCHAR Destination, _In_ PWCHAR Source, _In_ SIZE_T MaximumAllowed);
VOID ByteArrayToCharArrayA(_Inout_ PCHAR Destination, _In_ PBYTE Source, _In_ DWORD Length);
VOID ByteArrayToCharArrayW(_Inout_ PWCHAR Destination, _In_ PBYTE Source, _In_ DWORD Length);