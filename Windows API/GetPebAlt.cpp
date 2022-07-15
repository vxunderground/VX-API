PPEB GetPebAlt(VOID)
{
	PTEB Teb;
#if defined(_WIN64)
	Teb = (PTEB)__readgsqword(0x30);
#elif define(_WIN32)
	Teb = (PTEB)__readfsdword(0x18);
#endif
	return (PPEB)Teb->ProcessEnvironmentBlock;
}
