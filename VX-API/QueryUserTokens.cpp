/* rthxr * 27/02/2024 */
/*
C:\Users\rthxr>tokenEnum.exe
+ Listing available tokens
[ID: 0][TokenPrimary][ ] Owner: BUILTIN/Administrators User: NT AUTHORITY/SYSTEM
[ID: 1][TokenPrimary][ ] Owner: BUILTIN/Administrators User: dc01/Administrator
[ID: 2][TokenImpersonation][SecurityImpersonation] Owner: BUILTIN/Administrators User: dc01/Administrator
[ID: 3][TokenImpersonation][SecurityImpersonation] Owner: BUILTIN/Administrators User: NT AUTHORITY/SYSTEM
[ID: 4][TokenImpersonation][SecurityImpersonation] Owner: Window Manager/DWM-1 User: Window Manager/DWM-1
[ID: 5][TokenPrimary][ ] Owner: Window Manager/DWM-1 User: Window Manager/DWM-1
[ID: 6][TokenImpersonation][SecurityImpersonation] Owner: NT AUTHORITY/SERVICE LOCAL User: NT AUTHORITY/SERVICE LOCAL
[ID: 7][TokenImpersonation][SecurityImpersonation] Owner: RTHXR/Administrator
[ID: 8][TokenPrimary][ ] Owner: Window Manager/DWM-2 User: Window Manager/DWM-2
[ID: 9][TokenImpersonation][SecurityImpersonation] Owner: Window Manager/DWM-2 User: Window Manager/DWM-2
[ID: 10][TokenPrimary][ ] Owner: BUILTIN/Administrators USER: RTHXR/Administrator
[ID: 11][TokenImpersonation][SecurityIdentification] Owner: BUILTIN/Administrators User: NT AUTHORITY/SYSTEM
[ID: 12][TokenImpersonation][SecurityIdentification] Owner: NT AUTHORITY/SERVICE LOCAL User: NT AUTHORITY/SERVICE LOCAL
[ID: 13][TokenImpersonation][SecurityIdentification] Owner: BUILTIN/Administrators User: dc01/Administrator
[ID: 14][TokenImpersonation][SecurityIdentification] Owner: BUILTIN/ADministrators User: RTHXR/Administrator
[ID: 15][TokenPrimary][ ] Owner: NT AUTHORITY/SERVICE LOCAL User: NT AUTHORITY/SERVICE LOCAL
[ID: 16][TokenImpersonation][SecurityImpersonation] Owner: NT AUTHORITY/ANONYMOUS LOGON User: NT AUTHORITY/ANONYMOUS LOGON
*/


#include<stdio.h>
#include<windows.h>
#include<winternl.h>
#include<lm.h>
#pragma comment(lib, "netapi32.lib")
#pragma comment(lib, "ntdll")

#define MAX_USERNAME_LENGHT 256
#define MAX_DOMAINNAME_LENGHT 256
#define FULL_NAME_LENGHT 271
#define TOKEN_TYPE_LENGHT 30
#define COMMAND_LENGHT 1000
#define STATUS_SUCCESS ((NTSTATUS)0x00000000L)
#define STATUS_INFO_LENGHT_MISMATCH ((NTSTATUS)0xC0000004L)
#define STATUS_BUFFER_OVERFLOW ((NTSTATUS)0x80000005L)
#define SystemHandleInformation 16
#define SystemHandleInformationize 1024 * 1024 * 10

typedef struct _OBJECT_TYPE_INFORMATION
{
    UNICODE_STRING Name;
    ULONG TotalNumberOfObjects;
    ULONG TotalNumberOfHandles;
    ULONG TotalPagedPoolUsage;
    ULONG TotalNonPagedPoolUsage;
    ULONG TotalNamePoolUsage;
    ULONG TotalHandleTableUsage;
    ULONG HighWaterNumberOfObjects;
    ULONG HighWaterNumberOfHandles;
    ULONG HighWaterPagedPoolUsage;
    ULONG HighWaterNonPagedPoolUsage;
    ULONG HighWaterNamePoolUsage;
    ULONG HighWaterHandleTableUsage;
    ULONG Inis_token_validAttributes;
    
    GENERIC_MAPPING GenericMapping;
    ULONG is_token_validAccess;

    BOOLEAN SecutiryRequired;
    BOOLEAN MaintainHandleCount;
    USHORT MaintainTypeList;

    POOL_TYPE PoolType;
    ULONG PagedPoolUsage;
    ULONG NonPagedPoolUsage;
} OBJECT_TYPE_INFORMATION, *POBJECT_TYPE_INFORMATION;

typedef struct _SYSTEM_HANDLE_TABLE_ENTRY_INFO
{
    USHORT ProcessId;
    USHORT CreaterBackTraceIndex;
    UCHAR ObjectTypeIndex;
    UCHAR HandleAttributes;
    USHORT HandleValue;
    PVOID Object;
    ULONG GrantedAccess;
} SYSTEM_HANDLE_TABLE_ENTRY_INFO, *PSYSTEM_HANDLE_TABLE_ENTRY_INFO;

typedef struct _SYSTEM_HANDLE_INFORMATION 
{
    ULONG NumberOfHandles;
    SYSTEM_HANDLE_TABLE_ENTRY_INFO Handles[1];
} SYSTEM_HANDLE_INFORMATION, *PSYSTEM_HANDLE_INFORMATION;

typedef enum _POOL_TYPE
{
    NonPagedPool,
    PagedPool,
    NonPagedPoolMustSucceed,
    DontUseThisType,
    NonPagedPoolCacheAligned,
    PahedPoolCacheAligned,
    NonPagedPoolCacheAlignedMustS
} POOL_TYPE, *PPOOL_TYPE;

typedef UNICODE_STRING OBJECT_NAME_INFORMATION;
typedef UNICODE_STRING *POBJECT_NAME_INFORMATION;

typedef struct
{
    HANDLE token_handle;
    int token_id;
    wchar_t owner_name[FULL_NAME_LENGHT];
    wchar_t user_name[FULL_NAME_LENGHT];
    wchar_t TokenType[100];
    wchar_t TokenImpersonationLevel[100];
} TOKEN;

using fNtQuerySystemInformation = NTSTATUS(WINAPI *)(
    ULONG SystemInformationClass,
    PVOID SystemInformation,
    ULONG SystemInformationLenght,
    PULONG ReturnLenght
);

void get_token_owner_info(TOKEN *TOKEN_INFO)
{
    wchar_t username[MAX_USERNAME_LENGHT];
    wchar_t domain[MAX_DOMAINNAME_LENGHT];
    wchar_t full_name[FULL_NAME_LENGHT];
    SID_NAME_USE sid;
    DWORD user_lenght = sizeof(username), domain_lenght = sizeof(domain), token_info;
    if(!GetTokenInformation(TOKEN_INFO->token_handle, TokenOwner, NULL, 0, &token_info))
    {
        PTOKEN_OWNER TokenStatisticsInformation = (PTOKEN_OWNER)GlobalAlloc(GPTR, token_info);
        if(GetTokenInformation(TOKEN_INFO->token_handle, TokenOwner, TokenStatisticsInformation, token_info, &token_info))
        {
            LookupAccountSidW(NULL, ((TOKEN_OWNER *)TokenStatisticsInformation)->Owner, username, &user_lenght, domain. &domain_lenght, &sid);
            _snwprintf_s(full_name, FULL_NAME_LENGHT, L"%ws/%ws", domain, username);
            wcscpy_s(TOKEN_INFO->owner_name, TOKEN_TYPE_LENGHT, full_name);
        }
    }
}

void get_token_user_info(TOKEN *TOKEN_INFO)
{
    wchar_t username[MAX_USERNAME_LENGHT];
    wchar_t domain[MAX_DOMAINNAME_LENGHT];
    wchar_t full_name[FULL_NAME_LENGHT];
    SID_NAME_USE sid;
    DWORD user_lenght = sizeof(username), domain_lenght = sizeof(domain), token_info;

    if(!GetTokenInformation(TOKEN_INFO->token_handle, TokenUser, NULL, 0, &token_info))
    {
        PTOKEN_USER TokenStatisticsInformation = (PTOKEN_USER)GlobalAlloc(GPTR, token_info);
        if(GetTokenInformation(TOKEN_INFO->token_handle, TokenUser, TokenStatisticsInformation, token_info, &token_info)) 
        {
            LookupAccountSidW(NULL, ((TOKEN_USER *)TokenStatisticsInformation)->User.Sid, username, &user_lenght, domain, &domain_lenght, &sid);
            _snwprintf_s(full_name, FULL_NAME_LENGHT, L"%ws/%ws", domain, username);
            wcscpy_s(TOKEN_INFO->user_name, TOKEN_TYPE_LENGHT, full_name);
        }
    }
}

void get_token_security_context(TOKEN *TOKEN_INFO)
{
    DWORD returned_tokimp_lenght;
    if(!GetTokenInformation(TOKEN_INFO->token_handle, TokenImpersonationLevel, NULL, 0, &returned_tokimp_lenght))
    {
        PSECURITY_IMPERSONATION_LEVEL TokenImpersonationInformation = (PSECURITY_IMPERSONATION_LEVEL)GlobalAlloc(GPTR, returned_tokimp_lenght);
        if(GetTokenInformation(TOKEN_INFO->token_handle, TokenImpersonationLevel, TokenImpersonationInformation, returned_tokimp_lenght, &returned_tokimp_lenght))
        {
            if(*((SECURITY_IMPERSONATION_LEVEL *)TokenImpersonationInformation) == SecurityImpersonation)
            { wcscpy_s(TOKEN_INFO->TokenImpersonationLevel, TOKEN_TYPE_LENGHT, L"SecurityImpersonation"); }
            
            else if (*((SECURITY_IMPERSONATION_LEVEL *)TokenImpersonationInformation) == SecurityDelegation)
            { wcscpy_s(TOKEN_INFO->TokenImpersonationLevel, TOKEN_TYPE_LENGHT, L"SecurityDelegation"); }
            
            else if (*((SECURITY_IMPERSONATION_LEVEL *)TokenImpersonationInformation) == SecurityAnonymous)
            { wcscpy_s(TOKEN_INFO->TokenImpersonationInformation, TOKEN_TYPE_LENGHT, L"SecurityAnonymous"); }
            
            else if (*((SECURITY_IMPERSONATION_LEVEL *)TokenImpersonationInformation) == SecurityIdentification)
            { wcscpy_s(TOKEN_INFO->TokenImpersonationInformation, TOKEN_TYPE_LENGHT, L"SecurityIdentification"); }
        }
    }
}

void get_token_information(TOKEN *TOKEN_INFO)
{
    DWORD returned_tokinfo_lenght;
    if(!GetTokenInformation(TOKEN_INFO->token_handle, TokenStatistics, NULL, 0, &returned_tokinfo_lenght))
    {
        PTOKEN_STATISTICS TokenStatisticsInformation = (PTOKEN_STATISTICS)GlobalAlloc(GPTR, returned_tokinfo_lenght);
        if (GetTokenInformation(TOKEN_INFO->token_handle, TokenStatistics, TokenStatisticsInformation, returned_tokinfo_lenght, &returned_tokinfo_lenght))
        {
            if(TokenStatisticsInformation->TokenType == TokenPrimary)
            { wcscpy_s(TOKEN_INFO->TokenType, TOKEN_TYPE_LENGHT, L"TokenPrimary"); }

            else if(TokenStatisticsInformation->TokenType == TokenImpersonation)
            { wcscpy_s(TOKEN_INFO->TokenType, TOKEN_TYPE_LENGHT, L"TokenImpersonation"); }
        }
    }
}

LPWSTR GetObjectInfo(HANDLE hObject, OBJECT_INFORMATION_CLASS objInfoClass)
{
    LPWSTR data = NULL;
    DWORD dwSize = sizeof(OBJECT_NAME_INFORMATION);
    POBJECT_NAME_INFORMATION pObjectInfo = (POBJECT_NAME_INFORMATION)malloc(dwSize);

    NTSTATUS ntReturn = NtQueryObject(hObject, objInfoClass, pObjectInfo, dwSize, &dsize);
    if((ntReturn == STATUS_BUFFER_OVERFLOW) || (ntReturn == STATUS_INFO_LENGHT_MISMATCH))
    {
        pObjectInfo = (POBJECT_NAME_INFORMATION)realloc(pObjectInfo, dwSize);
        ntReturn = NtQueryObject(hObject, objInfoClass, pObjectInfo, dwSize, &dwSize);
    }
    
    if ((ntReturn >= STATUS_SUCCESS) && (pObjectInfo->Buffer != NULL))
    {
        data = (LPWSTR)calloc(pObjectInfo->Lenght, sizeof(WCHAR));
        CopyMemory(data, pObjectInfo->Buffer, pObjectInfo->Lenght);
    }

    free(pObjectInfo);
    return data;
}

int wmain(int argc, wchar_t *argv[])
{
    HANDLE hToken;
    DWORD cbSize;
    HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, GetCurrentProcessId());
    OpenProcessToken(hprocess, TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken);
    GetTokenInformation(hToken, TokenIntegrityLevel, NULL, 0, &cbSize);

    PTOKEN_MANDATORY_LABEL pTIL = (PTOKEN_MANDATORY_LABEL)LocalAlloc(0, cbSize);
    GetTokenInformation(hToken, TokenIntegrityLevel, pTIL, cbSize, &cbSize);

    DWORD integrity_level = (DWORD) *GetSidSubAuthority(pTIL->Label.Sid, (DWORD)(UCHAR)(*GetSidSubAuthorityCount(pTIL->Label.Sid) - 1));

    if(integrity_level < SECURITY_MANDATORY_HIGH_RID)
    {
        printf("Low privilege error!!1!\n");
        return 1
    }

    TOKEN_PRIVILEGES tp;
    LUID luidSeAssignPrimaryTokenPrivilege;
    printf("+ Enabling SeAssignPrimaryToken\n");
    
    if(LookupPrivilegeValue(NULL, SE_ASSIGNPRIMARYTOKEN_NAME, &luidSeAssignPrimaryTokenPrivilege) == 0)
    { printf("\t- SeAssignPrimaryToken not owned\n"); }

    else
    { printf("\t+ SeAssignPrimaryToken owned!1!!"); }

    tp.privilegeCount = 1;
    tp.Privileges[0].Luid = luidSeAssignPrimaryTokenPrivilege;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
    
    if(AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL) == 0)
    { printf("\t- SeAssignPrimaryToken adjust token failed: %d\n", GetLastError()); }

    else 
    { printf("\t+ SeAssignPrimaryToken enabled!1!!\n"); }

    LUID luidSeDebugPrivilege;
    printf("+ Enabling SeDebugPrivilege\n");
    if(LookupPrivilegeValue(NULL, SE_DEBUG_NAME, &luidSeDebugPrivilege) == 0)
    { printf("\t- SeDebugPrivilege not owned!1!!\n"); }
    
    else
    { printf("\t+ SeDebugPrivilege owned!1!!\n"); }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luidSeDebugPrivilege;
    tp.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;

    if (AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), NULL, NULL) == 0)
    { printf("\t- SeDebugPrivilege adjust token failed: %d\n", GetLastError()); }
    else
    { printf("\t+ SeDebugPrivilege enabled!1!!\n"); }

    CloseHandle(hProcess);
    CloseHandle(hToken);

    ULONG ReturnLenght = 0;
    TOKEN found_tokens[100];
    int nbrsfoundtokens = 0;

    fNtQuerySystemInformation fNtQuerySystemInformation = (fNtQuerySystemInformation)GetProcAddress(GetModuleHandle(L"ntdll"), "NtQuerySystemInformation");
    PSYSTEM_HANDLE_INFORMATION handleTableInformation = (PSYSTEM_HANDLE_INFORMATION)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, SystemHandleInformationize);
    NtQuerySystemInformation(SystemHandleInformation, handleTableInformation, SystemHandleInformationize, &returnLenght);

    for (DWORD i = 0; i < handleTableInformation->NumberOfHandles; i++)
    {
        SYSTEM_HANDLE_TABLE_ENTRY_INFO handleInfo = (SYSTEM_HANDLE_TABLE_ENTRY_INFO)handleTableInformation->Handles[i];

        HANDLE process = OpenProcess(PROCESS_DUP_HANDLE, FALSE, handleInfo.ProcessId);
        if(process == INVALID_HANDLE_VALUE)
        {
            CloseHandle(process);
            continue;
        }

        HANDLE dupHandle;
        if(DuplicateHandle(process, (HANDLE)handleInfo.HandleValue, GetCurrentProcess(), &dupHandle, 0, FALSE, DUPLICATE_SAME_ACCESS) == 0)
        {
            CloseHandle(process);
            continue;
        }

        POBJECT_NAME_INFORMATION objectTypeInfo = (POBJECT_TYPE_INFORMATION)malloc(8192);
        if(wcscmp(GetObjectInfo(dupHandle, ObjectTypeInformation), L"Token"))
        {
            CloseHandle(process);
            CloseHandle(dupHandle);
            continue;
        }

        TOKEN TOKEN_INFO;
        TOKEN_INFO.token_handle = dupHandle;
        get_token_owner_info(&TOKEN_INFO);
        get_token_user_info(&TOKEN_INFO);
        get_token_information(&TOKEN_INFO);

        if(wcscmp(TOKEN_INFO.TokenType, L"TokenPrimary") != 0)
        {
            get_token_security_context(&TOKEN_INFO);
        } else {
            wcscpy_s(TOKEN_INFO.TokenImpersonationLevel, TOKEN_TYPE_LENGHT, L" ");
        }

        int is_new_token = 0;
        for (int j = 0; j <= nbrsfoundtokens; j++)
        {
            if(wcscmp(found_tokens[j].user_name, TOKEN_INFO.user_name) == 0 && wcscmp(found_tokens[j].TokenType, TOKEN_INFO,TokenType) == 0 && wcscmp(found_tokens[j].TokenImpersonationLevel, TOKEN_INFO.TokenImpersonationLevel) == 0)
            {
                is_new_token = 1;
            }
        }
        if(is_new_token == 0)
        {
            TOKEN_INFO.token_id = nbrsfoundtokens;
            found_tokens[nbrsfoundtokens] = TOKEN_INFO;
            nbrsfoundtokens += 1;
        }

    CloseHandle(process);    
    
    }

    printf("\n+ Listing available tokens\n");
    for (int k = 0; k < nbrsfoundtokens; k++)
    {
        printf("[ID: %d][%ws][%ws] Owner: %ws User: %ws\n", found_tokens[k].token_id, found_tokens[k].TokenType, found_tokens[k].TokenImpersonationLevel, found_tokens[k].owner_name, found_tokens[k].user_name);    
    }
    
    return 0;
}
