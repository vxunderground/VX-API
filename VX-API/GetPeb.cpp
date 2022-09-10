#include "Win32Helper.h"

PPEB GetPeb(VOID)
{
#if defined(_WIN64)
	return (PPEB)__readgsqword(0x60);
#elif define(_WIN32)
	return (PPEB)__readfsdword(0x30);
#endif
}

PPEB GetPebEx(VOID)
{
	PTEB Teb;
#if defined(_WIN64)
	Teb = (PTEB)__readgsqword(0x30);
#elif define(_WIN32)
	Teb = (PTEB)__readfsdword(0x18);
#endif
	return (PPEB)Teb->ProcessEnvironmentBlock;
}