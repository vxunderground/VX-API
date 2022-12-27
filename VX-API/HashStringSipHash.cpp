#include "Win32Helper.h"

#define ROTL64(x,r) (((UINT64)x << r) | ((UINT64)x >> (64 - r)))

#define SIPROUND \
	do {				\
		v0 += v1;		\
		v1 = ROTL64(v1, 13);	\
		v1 ^= v0;		\
		v0 = ROTL64(v0, 32);	\
		v2 += v3;		\
		v3 = ROTL64(v3, 16);	\
		v3 ^= v2;		\
		v0 += v3;		\
		v3 = ROTL64(v3, 21);	\
		v3 ^= v0;		\
		v2 += v1;		\
		v1 = ROTL64(v1, 17);	\
		v1 ^= v2;		\
		v2 = ROTL64(v2, 32);	\
	} while (0)


INT32 HashStringSipHashW(_In_ LPCWSTR String)
{
		INT    Length = (INT)StringLengthW(String);
		UINT64 hash   = ((UINT64)Length) << 56;
		PWCHAR end    = (PWCHAR)String + Length - (Length % sizeof(UINT64));
		INT    left   = Length & 7;


		UINT64 k0 = 0;
		UINT64 k1 = 0;
		UINT64 m;

		UINT64 v0 = 0x736f6d6570736575;
		UINT64 v1 = 0x646f72616e646f6d;
		UINT64 v2 = 0x6c7967656e657261;
		UINT64 v3 = 0x7465646279746573;

		v3 ^= k1;
		v2 ^= k0;
		v1 ^= k1;
		v0 ^= k0;

		for (; String != end; String += 8) {
			m = (((UINT64)((String)[0]))      | ((UINT64)((String)[1]) << 8)  |
				((UINT64)((String)[2]) << 16) | ((UINT64)((String)[3]) << 24) |
				((UINT64)((String)[4]) << 32) | ((UINT64)((String)[5]) << 40) |
				((UINT64)((String)[6]) << 48) | ((UINT64)((String)[7]) << 56));

			v3 ^= m;
			SIPROUND;
			SIPROUND;
			v0 ^= m;
		}

		switch (left) {

		case 7:
			hash |= ((UINT64)String[6]) << 48;
		case 6:
			hash |= ((UINT64)String[5]) << 40;
		case 5:
			hash |= ((UINT64)String[4]) << 32;
		case 4:
			hash |= ((UINT64)String[3]) << 24;
		case 3:
			hash |= ((UINT64)String[2]) << 16;
		case 2:
			hash |= ((UINT64)String[1]) << 8;
		case 1:
			hash |= ((UINT64)String[0]);
			break;

		case 0:
			break;
		}

		v3 ^= hash;
		SIPROUND;
		SIPROUND;
		v0 ^= hash;
		v2 ^= 0xff;

		SIPROUND;
		SIPROUND;
		SIPROUND;
		SIPROUND;

		hash = v0 ^ v1 ^ v2 ^ v3;
		return (INT32)hash;
}


INT32 HashStringSipHashA(_In_ LPCSTR String)
{
	INT    Length = (INT)StringLengthA(String);
	UINT64 hash = ((UINT64)Length) << 56;
	PCHAR  end = (PCHAR)String + Length - (Length % sizeof(UINT64));
	INT    left = Length & 7;

	UINT64 m;
	UINT64 k0 = 0;
	UINT64 k1 = 0;

	UINT64 v0 = 0x736f6d6570736575;
	UINT64 v1 = 0x646f72616e646f6d;
	UINT64 v2 = 0x6c7967656e657261;
	UINT64 v3 = 0x7465646279746573;

	v3 ^= k1;
	v2 ^= k0;
	v1 ^= k1;
	v0 ^= k0;

	for (; String != end; String += 8) {
		m = (((UINT64)((String)[0]))      | ((UINT64)((String)[1]) << 8)  |
			((UINT64)((String)[2]) << 16) | ((UINT64)((String)[3]) << 24) |
			((UINT64)((String)[4]) << 32) | ((UINT64)((String)[5]) << 40) |
			((UINT64)((String)[6]) << 48) | ((UINT64)((String)[7]) << 56));

		v3 ^= m;
		SIPROUND;
		SIPROUND;
		v0 ^= m;
	}

	switch (left) {

	case 7:
		hash |= ((UINT64)String[6]) << 48;
	case 6:
		hash |= ((UINT64)String[5]) << 40;
	case 5:
		hash |= ((UINT64)String[4]) << 32;
	case 4:
		hash |= ((UINT64)String[3]) << 24;
	case 3:
		hash |= ((UINT64)String[2]) << 16;
	case 2:
		hash |= ((UINT64)String[1]) << 8;
	case 1:
		hash |= ((UINT64)String[0]);
		break;

	case 0:
		break;
	}

	v3 ^= hash;
	SIPROUND;
	SIPROUND;
	v0 ^= hash;
	v2 ^= 0xff;

	SIPROUND;
	SIPROUND;
	SIPROUND;
	SIPROUND;

	hash = v0 ^ v1 ^ v2 ^ v3;
	return (INT32)hash;
}
