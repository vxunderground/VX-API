#include "Win32Helper.h"

INT32 HashStringMurmurW(_In_ LPCWSTR String)
{
	INT  Length = (INT)StringLengthW(String);
	UINT32 hash = 0;
	PUINT32 Tmp;
	SIZE_T  Idx;
	UINT32  Cnt;

	if (Length > 3) 
  {
		Idx = Length >> 2;
		Tmp = (PUINT32)String;
    
		do {
			Cnt = *Tmp++;

			Cnt *= 0xcc9e2d51;
			Cnt  = (Cnt << 15) | (Cnt >> 17);
			Cnt *= 0x1b873593;

			hash ^= Cnt;
			hash  = (hash << 13) | (hash >> 19);
			hash  = (hash * 5) + 0xe6546b64;

		} while (--Idx);

		String = (PWCHAR)Tmp;
	}

	if (Length & 3) 
  {
		Idx    = Length & 3;
		Cnt    = 0;
		String = &String[Idx - 1];
    
		do {
			Cnt <<= 8;
			Cnt |= *String--;
  
		} while (--Idx);
    
		Cnt  *= 0xcc9e2d51;
		Cnt   = (Cnt << 15) | (Cnt >> 17);
		Cnt  *= 0x1b873593;
		hash ^= Cnt;
	}

	hash ^= Length;
	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;

	return hash;
}

INT32 HashStringMurmurA(_In_ LPCSTR String)
{
	INT  Length = (INT)StringLengthA(String);
	UINT32 hash = 0;
	PUINT32 Tmp;
	SIZE_T  Idx;
	UINT32  Cnt;

	if (Length > 3) 
  {
		Idx = Length >> 2;
		Tmp = (PUINT32)String;
    
		do {
			Cnt = *Tmp++;

			Cnt *= 0xcc9e2d51;
			Cnt = (Cnt << 15) | (Cnt >> 17);
			Cnt *= 0x1b873593;

			hash ^= Cnt;
			hash = (hash << 13) | (hash >> 19);
			hash = (hash * 5) + 0xe6546b64;

		} while (--Idx);

		String = (PCHAR)Tmp;
	}

	if (Length & 3) 
  {
		Idx = Length & 3;
		Cnt = 0;
		String = &String[Idx - 1];
    
		do {
			Cnt <<= 8;
			Cnt |= *String--;

		} while (--Idx);

		Cnt *= 0xcc9e2d51;
		Cnt = (Cnt << 15) | (Cnt >> 17);
		Cnt *= 0x1b873593;
		hash ^= Cnt;
	}

	hash ^= Length;
	hash ^= hash >> 16;
	hash *= 0x85ebca6b;
	hash ^= hash >> 13;
	hash *= 0xc2b2ae35;
	hash ^= hash >> 16;

	return hash;

}
