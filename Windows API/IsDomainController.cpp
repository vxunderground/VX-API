/*

Originally seen in Trickbot malware in 2017
Re-developed by smelly__vx
*/

DWORD IsDomainController(PBOOL IsDomainController)
{
	typedef enum _DSROLE_PRIMARY_DOMAIN_INFO_LEVEL {
		DsRolePrimaryDomainInfoBasic = 1,
		DsRoleUpgradeStatus,
		DsRoleOperationState
	} DSROLE_PRIMARY_DOMAIN_INFO_LEVEL;

	typedef enum _DSROLE_MACHINE_ROLE {
		DsRole_RoleStandaloneWorkstation,
		DsRole_RoleMemberWorkstation,
		DsRole_RoleStandaloneServer,
		DsRole_RoleMemberServer,
		DsRole_RoleBackupDomainController,
		DsRole_RolePrimaryDomainController
	} DSROLE_MACHINE_ROLE;

	typedef struct _DSROLE_PRIMARY_DOMAIN_INFO_BASIC {
		DSROLE_MACHINE_ROLE MachineRole;
		ULONG               Flags;
		LPWSTR              DomainNameFlat;
		LPWSTR              DomainNameDns;
		LPWSTR              DomainForestName;
		GUID                DomainGuid;
	} DSROLE_PRIMARY_DOMAIN_INFO_BASIC, * PDSROLE_PRIMARY_DOMAIN_INFO_BASIC;

	typedef DWORD(WINAPI* DSROLEGETPRIMARYDOMAININFORMATION)(LPCWSTR, DSROLE_PRIMARY_DOMAIN_INFO_LEVEL, PDSROLE_PRIMARY_DOMAIN_INFO_BASIC);
	typedef VOID(WINAPI* DSROLEFREEMEMORY)(PVOID);

	HMODULE hLibrary = NULL;
	DSROLEGETPRIMARYDOMAININFORMATION DsRoleGetPrimaryDomainInformation = NULL;
	DSROLEFREEMEMORY DsRoleFreeMemory = NULL;
	PDSROLE_PRIMARY_DOMAIN_INFO_BASIC Buffer = 0;
	DWORD dwError = ERROR_SUCCESS;
	*IsDomainController = FALSE;

	hLibrary = LoadLibraryW(L"Netapi32.dll");
	if (hLibrary == NULL)
		goto EXIT_ROUTINE;

	DsRoleGetPrimaryDomainInformation = (DSROLEGETPRIMARYDOMAININFORMATION)GetProcAddress(hLibrary, "DsRoleGetPrimaryDomainInformation");
	DsRoleFreeMemory = (DSROLEFREEMEMORY)GetProcAddress(hLibrary, "DsRoleFreeMemory");

	if (!DsRoleGetPrimaryDomainInformation || !DsRoleFreeMemory)
		goto EXIT_ROUTINE;

	if (DsRoleGetPrimaryDomainInformation(0, DsRolePrimaryDomainInfoBasic, Buffer) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	if (Buffer != NULL)
	{
		if (Buffer->MachineRole == DsRole_RolePrimaryDomainController)
			*IsDomainController = TRUE;
	}
		
EXIT_ROUTINE:

	dwError = EhGetLastError();

	if (hLibrary)
		FreeLibrary(hLibrary);

	if (Buffer)
		DsRoleFreeMemory(&Buffer);

	return dwError;
}
