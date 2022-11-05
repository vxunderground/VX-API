#include "Win32Helper.h"

PPEB GetPeb(VOID)
{
#if defined(_WIN64)
	return (PPEB)__readgsqword(0x60);
#elif define(_WIN32)
	return (PPEB)__readfsdword(0x30);
#endif
}

PPEB GetPebFromTeb(VOID)
{
	PTEB Teb;
#if defined(_WIN64)
	Teb = (PTEB)__readgsqword(0x30);
#elif define(_WIN32)
	Teb = (PTEB)__readfsdword(0x18);
#endif
	return (PPEB)Teb->ProcessEnvironmentBlock;
}

/*

#if defined(_M_X64) || defined(__amd64__)
			return reinterpret_cast<const win::PEB_T*>(__readgsqword(0x60));
#elif defined(_M_IX86) || defined(__i386__)
			return reinterpret_cast<const win::PEB_T*>(__readfsdword(0x30));
#elif defined(_M_ARM) || defined(__arm__)
			return *reinterpret_cast<const win::PEB_T**>(_MoveFromCoprocessor(15, 0, 13, 0, 2) + 0x30);
#elif defined(_M_ARM64) || defined(__aarch64__)
			return *reinterpret_cast<const win::PEB_T**>(__getReg(18) + 0x60);
#elif defined(_M_IA64) || defined(__ia64__)
			return *reinterpret_cast<const win::PEB_T**>(static_cast<char*>(_rdteb()) + 0x60);
#else
#error Unsupported platform.
#endif


*/