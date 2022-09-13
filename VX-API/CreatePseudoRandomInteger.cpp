#include "Win32Helper.h"

INT PseudoRandomIntegerSubroutine(PULONG Context)
{
	return ((*Context = *Context * 1103515245 + 12345) % ((ULONG)RAND_MAX + 1));
}

INT CreatePseudoRandomInteger(_In_ ULONG Seed)
{
	return (PseudoRandomIntegerSubroutine(&Seed));
}