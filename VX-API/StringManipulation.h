#pragma once
#include "Internal.h"

PCHAR CaplockStringA(PCHAR Ptr);
PWCHAR CaplockStringW(PWCHAR Ptr);
PVOID CopyMemoryEx(PVOID Destination, CONST PVOID Source, SIZE_T Length);
VOID ZeroMemoryEx(PVOID Destination, SIZE_T Size);
PCHAR SecureStringCopyA(PCHAR String1, LPCSTR String2, SIZE_T Size);
PWCHAR SecureStringCopyW(PWCHAR String1, LPCWSTR String2, SIZE_T Size);
INT StringCompareA(LPCSTR String1, LPCSTR String2);
INT StringCompareW(LPCWSTR String1, LPCWSTR String2);
PWCHAR StringConcatW(PWCHAR String, PWCHAR String2);
PCHAR StringConcatA(PCHAR String, PCHAR String2);
PCHAR StringCopyA(PCHAR String1, PCHAR String2);
PWCHAR StringCopyW(PWCHAR String1, PWCHAR String2);
PCHAR StringFindSubstringA(PCHAR String1, PCHAR String2);
PWCHAR StringFindSubstringW(PWCHAR String1, PWCHAR String2);
SIZE_T StringLengthA(LPCSTR String);
SIZE_T StringLengthW(LPCWSTR String);
PCHAR StringLocateCharA(PCHAR String, INT Character);
PWCHAR StringLocateCharW(PWCHAR String, INT Character);
PCHAR StringRemoveSubstringA(PCHAR String, CONST PCHAR Substring);
PWCHAR StringRemoveSubstringW(PWCHAR String, CONST PWCHAR Substring);
PCHAR StringTerminateStringAtCharA(PCHAR String, INT Character);
PWCHAR StringTerminateStringAtCharW(PWCHAR String, INT Character);
PCHAR StringTokenA(PCHAR String, CONST PCHAR Delim);
PWCHAR StringTokenW(PWCHAR String, CONST PWCHAR Delim);
VOID CharArrayToByteArrayA(PCHAR Char, PBYTE Byte, DWORD Length);
VOID CharArrayToByteArrayW(PWCHAR Char, PBYTE Byte, DWORD Length);
VOID RtlInitUnicodeString(PUNICODE_STRING DestinationString, PCWSTR SourceString);
VOID RtlInitEmptyUnicodeString(PUNICODE_STRING UnicodeString, PWCHAR Buffer, USHORT BufferSize);
SIZE_T CharStringToWCharString(PWCHAR Destination, PCHAR Source, SIZE_T MaximumAllowed);
SIZE_T WCharStringToCharString(PCHAR Destination, PWCHAR Source, SIZE_T MaximumAllowed);
VOID ByteArrayToCharArrayA(PCHAR Destination, PBYTE Source, DWORD Length);
VOID ByteArrayToCharArrayW(PWCHAR Destination, PBYTE Source, DWORD Length);