HRESULT ComDisableGlobalSeh(VOID)
{
	HRESULT Result = S_OK;
	IGlobalOptions* GlobalOptions;

#pragma warning( push )
#pragma warning( disable : 6387)
	Result = CoCreateInstance(CLSID_GlobalOptions, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&GlobalOptions));
#pragma warning( pop )
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = GlobalOptions->Set(COMGLB_EXCEPTION_HANDLING, COMGLB_EXCEPTION_DONOT_HANDLE);

	GlobalOptions->Release();

EXIT_ROUTINE:

	return Result;
}

DWORD InitializeComWithSecurityContextDefault(BOOL DisableSeh)
{
	HRESULT Result = S_OK;

	Result = CoInitializeEx(NULL, 0);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	Result = CoInitializeSecurity(NULL, -1, NULL, NULL, RPC_C_AUTHN_LEVEL_PKT_PRIVACY, RPC_C_IMP_LEVEL_IDENTIFY, NULL, EOAC_NONE, NULL);
	if (!SUCCEEDED(Result))
		goto EXIT_ROUTINE;

	if (DisableSeh)
		Result = ComDisableGlobalSeh();

EXIT_ROUTINE:

	return EhWin32FromHResult(Result);
}

DWORD ComVssDeleteShadowVolumeBackups(BOOL CoUninitializeAfterCompletion)
{
	HRESULT Result = S_OK;
	IVssCoordinator* VssCoordinator = NULL;
	VSS_OBJECT_PROP* Snapshots = NULL;
	IVssEnumObject* EnumObject = NULL;
	LONG NumberOfSnapshots = 0;
	ULONG Objects = 16, Retrieved = 0;
	PWCHAR ShadowCopySetId = NULL, ShadowCopyId = NULL;

	if (InitializeComWithSecurityContextDefault(TRUE) != ERROR_SUCCESS)
		goto EXIT_ROUTINE;

	if (!SetProcessPrivilegeToken(MW_SEBACKUP_PRIVILEGE))
		return FALSE;

#pragma warning( push )
#pragma warning( disable : 6387)
	if (!SUCCEEDED(Result = CoCreateInstance(CLSID_CVssCoordinator, NULL, CLSCTX_LOCAL_SERVER, IID_PPV_ARGS(&VssCoordinator))))
		goto EXIT_ROUTINE;
#pragma warning( pop )

	if (!SUCCEEDED(Result = VssCoordinator->SetContext(-1)))
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(Result = VssCoordinator->Query(GUID_NULL, VSS_OBJECT_NONE, VSS_OBJECT_SNAPSHOT, &EnumObject)))
		goto EXIT_ROUTINE;

	Snapshots = (VSS_OBJECT_PROP*)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (sizeof(VSS_OBJECT_PROP) * Objects));
	if (Snapshots == NULL)
		goto EXIT_ROUTINE;

	if (!SUCCEEDED(Result = EnumObject->Next(Objects, Snapshots, (PULONG)&NumberOfSnapshots)))
		goto EXIT_ROUTINE;

	ShadowCopySetId = (PWCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (32 * sizeof(WCHAR)));
	if (ShadowCopySetId == NULL)
		goto EXIT_ROUTINE;

	ShadowCopyId = (PWCHAR)HeapAlloc(GetProcessHeap(), HEAP_ZERO_MEMORY, (32 * sizeof(WCHAR)));
	if (ShadowCopyId == NULL)
		goto EXIT_ROUTINE;

	while (NumberOfSnapshots--)
	{
		VSS_OBJECT_PROP Element = Snapshots[NumberOfSnapshots];
		LONG Dispose = 0;
		GUID SnapshotDipose = { 0 };
		if (Element.Type != VSS_OBJECT_SNAPSHOT)
			continue;

		RtlZeroMemory(ShadowCopyId, (32 * sizeof(WCHAR)));
		RtlZeroMemory(ShadowCopySetId, (32 * sizeof(WCHAR)));

		if (StringFromGUID2(Element.Obj.Snap.m_SnapshotId, ShadowCopyId, (32 * sizeof(WCHAR))) == ERROR_FAILURE_RETURN)
			continue;

		if (StringFromGUID2(Element.Obj.Snap.m_SnapshotSetId, ShadowCopySetId, (32 * sizeof(WCHAR))) == ERROR_FAILURE_RETURN)
			continue;

		VssCoordinator->DeleteSnapshots(Element.Obj.Snap.m_SnapshotId, VSS_OBJECT_SNAPSHOT, 1, &Dispose, &SnapshotDipose);
	}


EXIT_ROUTINE:

	if (ShadowCopyId)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, ShadowCopyId);

	if (ShadowCopySetId)
		HeapFree(GetProcessHeap(), HEAP_ZERO_MEMORY, ShadowCopySetId);

	if (EnumObject)
		EnumObject->Release();

	if (VssCoordinator)
		VssCoordinator->Release();

	if (CoUninitializeAfterCompletion)
		CoUninitialize();

	return EhWin32FromHResult(Result);
}

