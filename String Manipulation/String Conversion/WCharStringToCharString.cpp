SIZE_T WCharStringToCharString(PCHAR Destination, PWCHAR Source, SIZE_T MaximumAllowed)
{
	INT Length = (INT)MaximumAllowed;

	while (--Length >= 0)
	{
#pragma warning( push )
#pragma warning( disable : 4244)
		if (!(*Destination++ = *Source++))
			return MaximumAllowed - Length - 1;
#pragma warning( pop ) 
	}

	return MaximumAllowed - Length;
}
