#include "Win32Helper.h"

PTEB GetTeb(VOID)
{
#if defined(_WIN64)
	return (PTEB)__readgsqword(0x30);
#elif defined(_WIN32)
	return (PTEB)__readfsdword(0x18);
#endif
}
