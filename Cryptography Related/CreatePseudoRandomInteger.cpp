ULONG Next = 2; //seed

INT PseudoRandomIntegerSubroutine(PULONG Context)
{
	return ((*Context = *Context * 1103515245 + 12345) % ((ULONG)RAND_MAX + 1));
}

INT CreatePseudoRandomInteger(VOID)
{
	return (PseudoRandomIntegerSubroutine(&Next));
}
