#include "Win32Helper.h"

VOID DllLoadCallbackRoutine(ULONG NotificationReason, PLDR_DLL_NOTIFICATION_DATA NotificationData, PVOID Context)
{

}

PLIST_ENTRY UnusedSubroutineGetDllNotification(VOID)
{
	LDRREGISTERDLLNOTIFICATION LdrRegisterDllNotification = NULL;
	LDRUNREGISTERDLLNOTIFICATION LdrUnregisterDllNotification = NULL;
	PVOID Cookie = NULL;
	HMODULE hNtdll = NULL; PBYTE pbNtdll = NULL;;
	PLIST_ENTRY LdrDllNotificationList = NULL;
	PIMAGE_DOS_HEADER Dos = NULL;
	PIMAGE_NT_HEADERS Nt = NULL;
	PIMAGE_FILE_HEADER File = NULL;
	PIMAGE_OPTIONAL_HEADER Optional = NULL;
	PIMAGE_SECTION_HEADER Section = NULL;

	hNtdll = GetModuleHandleEx2W(L"ntdll.dll");
	if (hNtdll == NULL)
		return NULL;
	else
		pbNtdll = (PBYTE)hNtdll;

	LdrRegisterDllNotification = (LDRREGISTERDLLNOTIFICATION)GetProcAddressA((DWORD64)hNtdll, "LdrRegisterDllNotification");
	LdrUnregisterDllNotification = (LDRUNREGISTERDLLNOTIFICATION)GetProcAddressA((DWORD64)hNtdll, "LdrUnregisterDllNotification");

	if (!LdrRegisterDllNotification || !LdrUnregisterDllNotification)
		return NULL;

	if (LdrRegisterDllNotification(0, (LDR_DLL_NOTIFICATION_FUNCTION*)DllLoadCallbackRoutine, NULL, &Cookie) != STATUS_SUCCESS)
		return NULL;
	else
		LdrDllNotificationList = (PLIST_ENTRY)Cookie;

	RtlLoadPeHeaders(&Dos, &Nt, &File, &Optional, &pbNtdll);
	
	Section = IMAGE_FIRST_SECTION(Nt);
	for (DWORD dwX = ERROR_SUCCESS; dwX < File->NumberOfSections; dwX++)
	{
		if (StringCompareA(".data", (PCHAR)Section->Name) == ERROR_SUCCESS)
		{
			PLIST_ENTRY LdrDllNotificationListNext = NULL;
			PVOID BaseAddress = NULL, BaseAddressEnd = NULL;

			BaseAddress = pbNtdll + Section->VirtualAddress;
			BaseAddressEnd = (PVOID)((PULONG)BaseAddress + Section->Misc.VirtualSize);

			LdrDllNotificationListNext = LdrDllNotificationList->Flink;

			while (LdrDllNotificationListNext != LdrDllNotificationList)
			{
				if (LdrDllNotificationListNext >= BaseAddress && LdrDllNotificationListNext <= BaseAddressEnd)
				{
					if (LdrUnregisterDllNotification(Cookie) != STATUS_SUCCESS)
						return NULL;
					else
						return LdrDllNotificationListNext;
				}

				LdrDllNotificationListNext = LdrDllNotificationListNext->Flink;
			}
		}

		Section++;
	}

	return NULL;
}

BOOL RemoveRegisterDllNotification(VOID)
{
	PLIST_ENTRY DllNotifictionList = NULL;
	PLIST_ENTRY Head = NULL, Next = NULL;

	DllNotifictionList = UnusedSubroutineGetDllNotification();
	if (DllNotifictionList == NULL)
		return FALSE;

	Head = DllNotifictionList;
	Next = DllNotifictionList->Flink;

	while (Next != Head)
	{
		PLIST_ENTRY PreviousFlink = NULL, PreviousBlink = NULL;

		PreviousFlink = Next->Flink;
		PreviousBlink = Next->Blink;

		PreviousFlink->Blink = PreviousBlink;
		PreviousBlink->Flink = PreviousFlink;

		Next->Flink = NULL;
		Next->Blink = NULL;

		Next = PreviousFlink;
	}

	return TRUE;
}