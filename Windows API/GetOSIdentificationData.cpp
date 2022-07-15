DWORD GetOSIdentificationData(DWORD Id)
{
	PPEB Peb = GetPeb();

	switch (Id)
	{
		case 0:
			return Peb->OSMajorVersion;

		case 1:
			return Peb->OSMinorVersion;

		case 2:
			return Peb->OSBuildNumber;

		case 3:
			return Peb->OSPlatformId;

		default:
			return 0;

	}

	return 0;
}
