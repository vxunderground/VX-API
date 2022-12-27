#include "Win32Helper.h"
#include <Wincrypt.h>

BOOL CreateMd5HashFromFilePathW(_In_ LPCWSTR FilePath, _Inout_ PWCHAR Md5Hash)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	HCRYPTPROV hProvider = NULL;
	HCRYPTHASH hHash = NULL;
	BYTE FileBuffer[1024] = { 0 };
	BYTE Md5HashBuffer[32] = { 0 };
	DWORD dwRead = 0;
	BOOL bFlag = FALSE;
	DWORD dwHashData = 16;
	CHAR Md5Digits[] = "0123456789abcdef";
	CHAR Md5CharBufferTemp[32] = { 0 };

	if (!IsPathValidW(FilePath))
		return FALSE;

	hHandle = CreateFileW(FilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	if (!CryptAcquireContextW(&hProvider, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		goto EXIT_ROUTINE;

	if (!CryptCreateHash(hProvider, CALG_MD5, 0, 0, &hHash))
		goto EXIT_ROUTINE;

	while (ReadFile(hHandle, FileBuffer, 1024, &dwRead, NULL))
	{
		if (dwRead == 0)
			break;

		if (!CryptHashData(hHash, FileBuffer, dwRead, 0))
			goto EXIT_ROUTINE;
	}

	if (!CryptGetHashParam(hHash, HP_HASHVAL, Md5HashBuffer, &dwHashData, 0))
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0, dwOffset = 0; dwX < dwHashData; dwX++)
	{
		Md5CharBufferTemp[dwOffset] = Md5Digits[Md5HashBuffer[dwX] >> 4];
		dwOffset++;
		Md5CharBufferTemp[dwOffset] = Md5Digits[Md5HashBuffer[dwX] & 0xf];
		dwOffset++;
	}

	CharStringToWCharString(Md5Hash, Md5CharBufferTemp, 32);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hProvider)
		CryptReleaseContext(hProvider, 0);

	if (hHash)
		CryptDestroyHash(hHash);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}

BOOL CreateMd5HashFromFilePathA(_In_ LPCSTR FilePath, _Inout_ PCHAR Md5Hash)
{
	HANDLE hHandle = INVALID_HANDLE_VALUE;
	HCRYPTPROV hProvider = NULL;
	HCRYPTHASH hHash = NULL;
	BYTE FileBuffer[1024] = { 0 };
	BYTE Md5HashBuffer[32] = { 0 };
	DWORD dwRead = 0;
	BOOL bFlag = FALSE;
	DWORD dwHashData = 16;
	CHAR Md5Digits[] = "0123456789abcdef";
	CHAR Md5CharBufferTemp[32] = { 0 };

	if (!IsPathValidA(FilePath))
		return FALSE;

	hHandle = CreateFileA(FilePath, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_FLAG_SEQUENTIAL_SCAN, NULL);
	if (hHandle == INVALID_HANDLE_VALUE)
		return FALSE;

	if (!CryptAcquireContextA(&hProvider, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
		goto EXIT_ROUTINE;

	if (!CryptCreateHash(hProvider, CALG_MD5, 0, 0, &hHash))
		goto EXIT_ROUTINE;

	while (ReadFile(hHandle, FileBuffer, 1024, &dwRead, NULL))
	{
		if (dwRead == 0)
			break;

		if (!CryptHashData(hHash, FileBuffer, dwRead, 0))
			goto EXIT_ROUTINE;
	}

	if (!CryptGetHashParam(hHash, HP_HASHVAL, Md5HashBuffer, &dwHashData, 0))
		goto EXIT_ROUTINE;

	for (DWORD dwX = 0, dwOffset = 0; dwX < dwHashData; dwX++)
	{
		Md5CharBufferTemp[dwOffset] = Md5Digits[Md5HashBuffer[dwX] >> 4];
		dwOffset++;
		Md5CharBufferTemp[dwOffset] = Md5Digits[Md5HashBuffer[dwX] & 0xf];
		dwOffset++;
	}

	StringCopyA(Md5Hash, Md5CharBufferTemp);

	bFlag = TRUE;

EXIT_ROUTINE:

	if (hProvider)
		CryptReleaseContext(hProvider, 0);

	if (hHash)
		CryptDestroyHash(hHash);

	if (hHandle)
		CloseHandle(hHandle);

	return bFlag;
}