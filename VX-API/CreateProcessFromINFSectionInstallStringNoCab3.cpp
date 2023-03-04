#include "Win32Helper.h"

/*

Example .inf file
_______________
///////////////
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
; ----------------------------------------------------------------------
; Required Sections
; ----------------------------------------------------------------------
[Version]
Signature=$CHICAGO$
Provider=test
Class=Printer

[Manufacturer]
HuntressLabs=ModelsSection,NTx86,NTia64,NTamd64

; ----------------------------------------------------------------------
; Models Section
; ----------------------------------------------------------------------
[ModelsSection.NTx86]
UnregisterDlls = Squiblydoo

[ModelsSection.NTia64]
UnregisterDlls = Squiblydoo

[ModelsSection.NTamd64]
UnregisterDlls = Squiblydoo

; ----------------------------------------------------------------------
; Support Sections
; ----------------------------------------------------------------------
[DefaultInstall]
UnregisterDlls = Squiblydoo

[Squiblydoo]
calc.exe
_______________
///////////////
‾‾‾‾‾‾‾‾‾‾‾‾‾‾‾
*/

BOOL CreateProcessFromINFSectionInstallStringNoCab3W(LPCWSTR PathToInfFile, LPCWSTR NameOfSection)
{
	return FALSE;
}

BOOL CreateProcessFromINFSectionInstallStringNoCab3A(LPCSTR PathToInfFile, LPCSTR NameOfSection)
{
	return FALSE;
}