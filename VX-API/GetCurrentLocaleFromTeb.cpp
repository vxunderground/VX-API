#include "Win32Helper.h"

LCID GetCurrentLocaleFromTeb(VOID)
{
	PTEB Teb = (PTEB)GetTeb();

	return (LCID)Teb->CurrentLocale;
}
