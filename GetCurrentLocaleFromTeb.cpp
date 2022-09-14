#include "Win32Helper.h"

LCID GetCurrentLocale(VOID)
{
	PTEB Teb = (PTEB)GetTeb();

	return (LCID)Teb->CurrentLocale;
}
